#include "objModel.h"
#include "RHIDevice.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

template<> struct std::hash<pipeline::Vertex> {
    size_t operator()(pipeline::Vertex const& vertex) const {
        return ((std::hash<glm::vec3>()(vertex.pos) ^ (std::hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (std::hash<glm::vec2>()(vertex.texCoord) << 1);
    }
};

namespace pipeline {

	Model::Model() {

	}

	Model::~Model() {

	}

	void Model::Load(kRHIDevice& rhidevice, VkDescriptorSetLayout layout) {

		std::vector<Vertex>    vertex;
		std::vector<uint32_t>  indices;
		LoadModelFromfile(vertex, indices);
		m_IndexCount = indices.size();

		m_VertexBuffer.CreateVertexBuffer(rhidevice, (const char*)vertex.data(), vertex.size() * sizeof(Vertex));
		m_IndexBuffer.CreateIndexBuffer(rhidevice, (const char*)indices.data(), indices.size() * sizeof(uint32_t));

		m_Texture.CreateTexture(rhidevice, TEXTURE_PATH);
		m_UniformBuffer.CreateUniformBuffer(rhidevice, sizeof(UniformBufferObject));

		CreateDescriptorSets(rhidevice, sizeof(UniformBufferObject), layout);
	}

	void Model::UpdateUniformBuffer(kRHIDevice& rhidevice, uint32_t currentImage) {
		static auto startTime = std::chrono::high_resolution_clock::now();

		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

		UniformBufferObject ubo{};
		ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		ubo.proj = glm::perspective(glm::radians(45.0f), 1280.0f / 720.f, 0.1f, 10.0f);
		ubo.proj[1][1] *= -1;

		m_UniformBuffer.UpdateBuffer(&ubo, sizeof(ubo));
	}

	void Model::BuildCommandBuffer(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout) {
		VkBuffer vertexBuffers[] = { m_VertexBuffer.GetBuffer()};
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
		vkCmdBindIndexBuffer(commandBuffer, m_IndexBuffer.GetBuffer(), 0, VK_INDEX_TYPE_UINT32);
		vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &m_DescriptorSet, 0, nullptr);
		vkCmdDrawIndexed(commandBuffer, m_IndexCount, 1, 0, 0, 0);
	}

	void Model::Unload(kRHIDevice& rhidevice) {

		m_Texture.ReleaseTexture(rhidevice);
		m_IndexBuffer.ReleaseBuffer(rhidevice);
		m_VertexBuffer.ReleaseBuffer(rhidevice);
		m_UniformBuffer.ReleaseBuffer(rhidevice);
	}

	void Model::CreateDescriptorSets(kRHIDevice& rhidevice, VkDeviceSize bufferSize, VkDescriptorSetLayout layout) {

		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = rhidevice.descriptorPool;
		allocInfo.descriptorSetCount = 1;
		allocInfo.pSetLayouts = &layout;

		if (vkAllocateDescriptorSets(rhidevice.logicaldevice, &allocInfo, &m_DescriptorSet) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate descriptor sets!");
		}

		VkDescriptorBufferInfo bufferInfo{};
		bufferInfo.buffer = m_UniformBuffer.GetBuffer();
		bufferInfo.offset = 0;
		bufferInfo.range = bufferSize;

		VkDescriptorImageInfo imageInfo{};
		imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		imageInfo.imageView = m_Texture.GetImageView();
		imageInfo.sampler = m_Texture.GetImageSampler();

		std::array<VkWriteDescriptorSet, 2> descriptorWrites{};

		descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[0].dstSet = m_DescriptorSet;
		descriptorWrites[0].dstBinding = 0;
		descriptorWrites[0].dstArrayElement = 0;
		descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrites[0].descriptorCount = 1;
		descriptorWrites[0].pBufferInfo = &bufferInfo;

		descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[1].dstSet = m_DescriptorSet;
		descriptorWrites[1].dstBinding = 1;
		descriptorWrites[1].dstArrayElement = 0;
		descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		descriptorWrites[1].descriptorCount = 1;
		descriptorWrites[1].pImageInfo = &imageInfo;

		// In Vulkan, a descriptor set (VkDescriptorSet) is a container used to store descriptors. 
		// Descriptors are mechanisms in Vulkan for binding resources (such as uniform buffers, 
		// storage buffers, textures, samplers, etc.) to shaders. Each descriptor set corresponds 
		// to one or more binding points in the shader, and vkUpdateDescriptorSets is the function
		// used to update these binding relationships.
		vkUpdateDescriptorSets(rhidevice.logicaldevice, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
	}

	void Model::LoadModelFromfile(std::vector<Vertex>& vertex_array, std::vector<uint32_t>& index_array) {
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn, err;

		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, MODEL_PATH.c_str())) {
			throw std::runtime_error(warn + err);
		}

		std::unordered_map<Vertex, uint32_t> uniqueVertices{};

		for (const auto& shape : shapes) {
			for (const auto& index : shape.mesh.indices) {

				Vertex vertex{};
				vertex.pos = {
					attrib.vertices[3 * index.vertex_index + 0],
					attrib.vertices[3 * index.vertex_index + 1],
					attrib.vertices[3 * index.vertex_index + 2]
				};

				vertex.texCoord = {
					attrib.texcoords[2 * index.texcoord_index + 0],
					1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
				};

				vertex.color = { 1.0f, 1.0f, 1.0f };

				if (uniqueVertices.count(vertex) == 0) {
					uniqueVertices[vertex] = static_cast<uint32_t>(vertex_array.size());
					vertex_array.push_back(vertex);
				}

				index_array.push_back(uniqueVertices[vertex]);
			}
		}
	}
}
