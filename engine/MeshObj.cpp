#include "MeshObj.h"
#include "RHIDevice.h"
#include "Camera.h"
#include "RHIGraphicPipeline.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"


template<> struct std::hash<pipeline::kMeshObj::Vertex> {
	size_t operator()(pipeline::kMeshObj::Vertex const& vertex) const {
		return ((std::hash<glm::vec3>()(vertex.pos) ^ (std::hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (std::hash<glm::vec2>()(vertex.texCoord) << 1);
	}
};

namespace pipeline {

	const std::string OBJ_MODEL_PATH = "resources/viking_room.obj";
	const std::string OBJ_TEXTURE_PATH = "resources/viking_room.png";

	kMeshObj::kMeshObj() {
		m_BBoxSize = glm::vec3(1.0f, 1.0f, 1.0f);


	}

	kMeshObj::~kMeshObj() {

	}

	std::vector<VkDescriptorSetLayout> kMeshObj::PrepareDescriptorSetLayout(kRHIDevice& rhidevice) {

		VkDescriptorSetLayoutBinding uboLayoutBinding{};
		uboLayoutBinding.binding = 0;
		uboLayoutBinding.descriptorCount = 1;
		uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		uboLayoutBinding.pImmutableSamplers = nullptr;
		uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

		VkDescriptorSetLayoutBinding samplerLayoutBinding{};
		samplerLayoutBinding.binding = 1;
		samplerLayoutBinding.descriptorCount = 1;
		samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		samplerLayoutBinding.pImmutableSamplers = nullptr;
		samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

		std::vector<VkDescriptorSetLayoutBinding> bindings = { uboLayoutBinding, samplerLayoutBinding };

		VkDescriptorSetLayoutCreateInfo layoutInfo{};
		layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
		layoutInfo.pBindings = bindings.data();

		if (vkCreateDescriptorSetLayout(rhidevice.GetLogicDevice(), &layoutInfo, nullptr, &m_DescriptorSetLayout) != VK_SUCCESS) {
			throw std::runtime_error("failed to create descriptor set layout!");
		}

		return std::vector<VkDescriptorSetLayout> {m_DescriptorSetLayout};
	}

	std::vector<VkPushConstantRange> kMeshObj::PreparePushConstantRange(kRHIDevice& rhidevice) {

		return std::vector<VkPushConstantRange>{};
	}

	void kMeshObj::SetupDescriptorSets(kRHIDevice& rhidevice) {

		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = rhidevice.GetDescriptorPool();
		allocInfo.descriptorSetCount = 1;
		allocInfo.pSetLayouts = &m_DescriptorSetLayout;

		if (vkAllocateDescriptorSets(rhidevice.GetLogicDevice(), &allocInfo, &m_DescriptorSet) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate descriptor sets!");
		}

		VkDescriptorBufferInfo bufferInfo{};
		bufferInfo.buffer = m_UniformBuffer->GetBuffer();
		bufferInfo.offset = 0;
		bufferInfo.range = sizeof(ModelObjShaderData);

		VkDescriptorImageInfo imageInfo{};
		imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		imageInfo.imageView = m_Texture->GetImageView();
		imageInfo.sampler = m_Texture->GetImageSampler();

		std::vector<VkWriteDescriptorSet> descriptorWrites(2);

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
		vkUpdateDescriptorSets(rhidevice.GetLogicDevice(), static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
	}

	void kMeshObj::CreateGraphicPipeline(kRHIDevice& rhidevice)
	{
		VkVertexInputBindingDescription vertex_bindingDesc{};
		vertex_bindingDesc.binding = 0;
		vertex_bindingDesc.stride = sizeof(Vertex);
		vertex_bindingDesc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;


		std::vector<VkVertexInputAttributeDescription> vertex_attributeDescs(3);

		vertex_attributeDescs[0].binding = 0;
		vertex_attributeDescs[0].location = 0;
		vertex_attributeDescs[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		vertex_attributeDescs[0].offset = offsetof(Vertex, pos);

		vertex_attributeDescs[1].binding = 0;
		vertex_attributeDescs[1].location = 1;
		vertex_attributeDescs[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		vertex_attributeDescs[1].offset = offsetof(Vertex, color);

		vertex_attributeDescs[2].binding = 0;
		vertex_attributeDescs[2].location = 2;
		vertex_attributeDescs[2].format = VK_FORMAT_R32G32_SFLOAT;
		vertex_attributeDescs[2].offset = offsetof(Vertex, texCoord);


		kGraphicsPipelineCreateInfo createinfo;
		createinfo.vert_shader_file = "shaders/model_texture_vert.spv";
		createinfo.frag_shader_file = "shaders/model_texture_frag.spv";
		createinfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

		createinfo.render_pass = rhidevice.GetRenderPass();
		createinfo.descriptor_set_layouts = this->PrepareDescriptorSetLayout(rhidevice);
		createinfo.push_constant_ranges = this->PreparePushConstantRange(rhidevice);
		createinfo.input_binding = vertex_bindingDesc;
		createinfo.input_attributes = vertex_attributeDescs;
		m_GraphicPipeline.CreateGraphicsPipeline(rhidevice, createinfo);

		SetupDescriptorSets(rhidevice);
	}

	void kMeshObj::Load(kRHIDevice& rhidevice) {

		m_VertexBuffer = std::make_shared<kRHIBuffer>();
		m_IndexBuffer = std::make_shared<kRHIBuffer>();
		m_UniformBuffer = std::make_shared<kRHIBuffer>();
		m_Texture = std::make_shared<kRHITexture2D>();

		std::vector<Vertex>    vertex;
		std::vector<uint32_t>  indices;
		LoadModelFromfile(vertex, indices);

		m_IndexCount = indices.size();
		m_VertexCount = vertex.size();

		m_VertexBuffer->CreateVertexBuffer(rhidevice, (const char*)vertex.data(), vertex.size() * sizeof(Vertex));
		m_IndexBuffer->CreateIndexBuffer(rhidevice, (const char*)indices.data(), indices.size() * sizeof(uint32_t));

		m_Texture->CreateTexture(rhidevice, OBJ_TEXTURE_PATH);
		m_UniformBuffer->CreateUniformBuffer(rhidevice, sizeof(ModelObjShaderData));

		CreateGraphicPipeline(rhidevice);
	}

	void kMeshObj::UpdateUniformBuffer(kRHIDevice& rhidevice, kCamera& camera) {
		static auto startTime = std::chrono::high_resolution_clock::now();

		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

		ModelObjShaderData temp_shaderdat{};
		temp_shaderdat.model = glm::mat4(1.0f);
		//temp_shaderdat.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		temp_shaderdat.view = camera.GetViewMat();
		//temp_shaderdat.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		temp_shaderdat.proj = camera.GetProjMat();

		m_UniformBuffer->UpdateBuffer(&temp_shaderdat, sizeof(temp_shaderdat));
	}

	void kMeshObj::BuildCommandBuffer(VkCommandBuffer commandBuffer, kCamera& camera) {

		VkDeviceSize offsets[] = { 0 };
		VkBuffer vertexBuffers[] = { m_VertexBuffer->GetBuffer()};

		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_GraphicPipeline.GetPipeline());
		vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_GraphicPipeline.GetPipelineLayout(), 0, 1, &m_DescriptorSet, 0, nullptr);

		// triangle
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
		vkCmdBindIndexBuffer(commandBuffer, m_IndexBuffer->GetBuffer(), 0, VK_INDEX_TYPE_UINT32);
		vkCmdDrawIndexed(commandBuffer, m_IndexCount, 1, 0, 0, 0);

		// points
		//vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
		//vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &m_DescriptorSet, 0, nullptr);
		//vkCmdDraw(commandBuffer, m_VertexCount, 1, 0, 0);
	}

	void kMeshObj::Unload(kRHIDevice& rhidevice) {

		vkDestroyDescriptorSetLayout(rhidevice.GetLogicDevice(), m_DescriptorSetLayout, nullptr);

		m_Texture.reset();
		m_IndexBuffer.reset();
		m_VertexBuffer.reset();
		m_UniformBuffer.reset();

		m_GraphicPipeline.ReleaseGraphicsPipeline(rhidevice);
	}


	void kMeshObj::LoadModelFromfile(std::vector<Vertex>& vertex_array, std::vector<uint32_t>& index_array) {
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn, err;

		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, OBJ_MODEL_PATH.c_str())) {
			throw std::runtime_error(warn + err);
		}

		glm::vec3 bb_min = glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX);
		glm::vec3 bb_max = -glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX);

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

					bb_min.x = std::min(bb_min.x, vertex.pos[0]);
					bb_min.y = std::min(bb_min.y, vertex.pos[1]);
					bb_min.z = std::min(bb_min.z, vertex.pos[2]);

					bb_max.x = std::max(bb_max.x, vertex.pos[0]);
					bb_max.y = std::max(bb_max.y, vertex.pos[1]);
					bb_max.z = std::max(bb_max.z, vertex.pos[2]);

					uniqueVertices[vertex] = static_cast<uint32_t>(vertex_array.size());
					vertex_array.push_back(vertex);
				}

				index_array.push_back(uniqueVertices[vertex]);
			}
		}

		m_BBoxCenter = (bb_max + bb_min) * 0.5f;
		m_BBoxSize = (bb_max - bb_min);
	}
}
