#include "objModel.h"
#include "RHIContext.h"

#include "tiny_obj_loader.h"

template<> struct std::hash<pipeline::Vertex> {
    size_t operator()(pipeline::Vertex const& vertex) const {
        return ((std::hash<glm::vec3>()(vertex.pos) ^ (std::hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (std::hash<glm::vec2>()(vertex.texCoord) << 1);
    }
};

namespace pipeline {


	void Model::Load(kRHIContext& contextref, VkDescriptorSetLayout layout) {

		loadModelFromfile();

		m_VertexBuffer.createVertexBuffer(contextref, (const char*)m_Vertex.data(), m_Vertex.size() * sizeof(Vertex));
		m_IndexBuffer.createIndexBuffer(contextref, (const char*)m_Indices.data(), m_Indices.size() * sizeof(uint32_t));

		m_Texture.createTexture(contextref, TEXTURE_PATH);

		createUniformBuffers(contextref, sizeof(UniformBufferObject));
		createDescriptorSets(contextref, sizeof(UniformBufferObject), layout);
	}

	void Model::Unload(kRHIContext& contextref) {

		m_Texture.cleanupTexture(contextref);
		m_IndexBuffer.cleanupBuffer(contextref);
		m_VertexBuffer.cleanupBuffer(contextref);

		m_UniformBuffer.cleanupGPUResource(contextref);
	}

    void Model::loadModelFromfile() {
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
                    uniqueVertices[vertex] = static_cast<uint32_t>(m_Vertex.size());
                    m_Vertex.push_back(vertex);
                }

                m_Indices.push_back(uniqueVertices[vertex]);
            }
        }
    }


	void Model::createDescriptorSets(kRHIContext& contextref, VkDeviceSize bufferSize, VkDescriptorSetLayout layout) {

		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = contextref.descriptorPool;
		allocInfo.descriptorSetCount = 1;
		allocInfo.pSetLayouts = &layout;

		if (vkAllocateDescriptorSets(contextref.logicaldevice, &allocInfo, &descriptorSet) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate descriptor sets!");
		}

		VkDescriptorBufferInfo bufferInfo{};
		bufferInfo.buffer = m_UniformBuffer.getBuffer();
		bufferInfo.offset = 0;
		bufferInfo.range = bufferSize;

		VkDescriptorImageInfo imageInfo{};
		imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		imageInfo.imageView = getTexture().getImageView();
		imageInfo.sampler = getTexture().getImageSampler();

		std::array<VkWriteDescriptorSet, 2> descriptorWrites{};

		descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[0].dstSet = descriptorSet;
		descriptorWrites[0].dstBinding = 0;
		descriptorWrites[0].dstArrayElement = 0;
		descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrites[0].descriptorCount = 1;
		descriptorWrites[0].pBufferInfo = &bufferInfo;

		descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[1].dstSet = descriptorSet;
		descriptorWrites[1].dstBinding = 1;
		descriptorWrites[1].dstArrayElement = 0;
		descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		descriptorWrites[1].descriptorCount = 1;
		descriptorWrites[1].pImageInfo = &imageInfo;

		vkUpdateDescriptorSets(contextref.logicaldevice, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
	}

	void Model::createUniformBuffers(kRHIContext& contextref, VkDeviceSize bufferSize) {
		
		m_UniformBuffer.createUniformBuffers(contextref, bufferSize);
	}

	void Model::updateUniformBuffer(kRHIContext& contextref, uint32_t currentImage) {
		static auto startTime = std::chrono::high_resolution_clock::now();

		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

		UniformBufferObject ubo{};
		ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		ubo.proj = glm::perspective(glm::radians(45.0f), 1280.0f/720.f, 0.1f, 10.0f);
		ubo.proj[1][1] *= -1;

		m_UniformBuffer.updateBuffer(&ubo, sizeof(ubo));
	}
}
