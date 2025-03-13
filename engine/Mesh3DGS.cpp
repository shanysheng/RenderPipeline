#include "Mesh3DGS.h"
#include "RHIDevice.h"
#include "Camera.h"
#include "RHIGraphicPipeline.h"


namespace pipeline {

	//--------------------------------------------------------------------------------------------------------------------

    kMesh3DGS::kMesh3DGS() {

    }

    kMesh3DGS::~kMesh3DGS() {

    }


	//--------------------------------------------------------------------------------------------------------------------

	void kMesh3DGS::SetupSortDescSets(kRHIDevice& rhidevice) {
	
	}

	void kMesh3DGS::CreateSortComputePipeline(kRHIDevice& rhidevice) {
	
	}

	void kMesh3DGS::BuildSortCommandBuffer(VkCommandBuffer commandBuffer) {
	
	}

	//--------------------------------------------------------------------------------------------------------------------

	std::vector<VkDescriptorSetLayout> kMesh3DGS::PrepareProjectionDSLayout(kRHIDevice& rhidevice) {

		std::array<VkDescriptorSetLayoutBinding, 3> layoutBindings{};

		layoutBindings[0].binding = 0;
		layoutBindings[0].descriptorCount = 1;
		layoutBindings[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		layoutBindings[0].pImmutableSamplers = nullptr;
		layoutBindings[0].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

		layoutBindings[1].binding = 1;
		layoutBindings[1].descriptorCount = 1;
		layoutBindings[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		layoutBindings[1].pImmutableSamplers = nullptr;
		layoutBindings[1].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

		layoutBindings[2].binding = 2;
		layoutBindings[2].descriptorCount = 1;
		layoutBindings[2].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		layoutBindings[2].pImmutableSamplers = nullptr;
		layoutBindings[2].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

		VkDescriptorSetLayoutCreateInfo layoutInfo{};
		layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo.bindingCount = 3;
		layoutInfo.pBindings = layoutBindings.data();

		if (vkCreateDescriptorSetLayout(rhidevice.GetLogicDevice(), &layoutInfo, nullptr, &m_ProjectionDSLayout) != VK_SUCCESS) {
			throw std::runtime_error("failed to create descriptor set layout!");
		}

		return std::vector<VkDescriptorSetLayout> {m_ProjectionDSLayout};
	}

	void kMesh3DGS::SetupProjectionDescSets(kRHIDevice& rhidevice) {

		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = rhidevice.GetDescriptorPool();
		allocInfo.descriptorSetCount = 1;
		allocInfo.pSetLayouts = &m_ProjectionDSLayout;

		if (vkAllocateDescriptorSets(rhidevice.GetLogicDevice(), &allocInfo, &m_ProjectionDS) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate descriptor sets!");
		}

		std::vector<VkWriteDescriptorSet> descriptorWrites{};
		descriptorWrites.resize(3);

		VkDescriptorBufferInfo buffer0_Info = m_UniformBuffer->GetBufferInfo();
		descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[0].dstSet = m_ProjectionDS;
		descriptorWrites[0].dstBinding = 0;
		descriptorWrites[0].dstArrayElement = 0;
		descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrites[0].descriptorCount = 1;
		descriptorWrites[0].pBufferInfo = &buffer0_Info;

		VkDescriptorBufferInfo buffer1_info = m_3DGSVertexBuffer->GetBufferInfo();
		descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[1].dstSet = m_ProjectionDS;
		descriptorWrites[1].dstBinding = 1;
		descriptorWrites[1].dstArrayElement = 0;
		descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		descriptorWrites[1].descriptorCount = 1;
		descriptorWrites[1].pBufferInfo = &buffer1_info;

		VkDescriptorBufferInfo buffer2_info = m_QuadVertexBuffer->GetBufferInfo();
		descriptorWrites[2].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[2].dstSet = m_ProjectionDS;
		descriptorWrites[2].dstBinding = 2;
		descriptorWrites[2].dstArrayElement = 0;
		descriptorWrites[2].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		descriptorWrites[2].descriptorCount = 1;
		descriptorWrites[2].pBufferInfo = &buffer2_info;

		// In Vulkan, a descriptor set (VkDescriptorSet) is a container used to store descriptors. 
		// Descriptors are mechanisms in Vulkan for binding resources (such as uniform buffers, 
		// storage buffers, textures, samplers, etc.) to shaders. Each descriptor set corresponds 
		// to one or more binding points in the shader, and vkUpdateDescriptorSets is the function
		// used to update these binding relationships.
		vkUpdateDescriptorSets(rhidevice.GetLogicDevice(), static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);

	}

	void kMesh3DGS::CreateProjectionComputePipeline(kRHIDevice& rhidevice) {

		kComputePipelineCreateInfo computeCreateInfo;
		computeCreateInfo.comp_shader_file = "shaders/gs_projection_comp.spv";
		computeCreateInfo.descriptor_set_layouts = PrepareProjectionDSLayout(rhidevice);
		m_ProjectionComp.CreateComputePipeline(rhidevice, computeCreateInfo);

		SetupProjectionDescSets(rhidevice);
	}

	void kMesh3DGS::BuildProjectionCommandBuffer(VkCommandBuffer commandBuffer, kCamera& camera) {

		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, m_ProjectionComp.GetPipeline());
		vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, m_ProjectionComp.GetPipelineLayout(), 0, 1, &m_ProjectionDS, 0, nullptr);

		constexpr int local_size = 256;
		uint32_t group_size_x = (uint32_t)(m_SplatScene.gs_points.size() + local_size - 1) / local_size;
		vkCmdDispatch(commandBuffer, group_size_x, 1, 1);

		VkMemoryBarrier barrier;
		barrier = { VK_STRUCTURE_TYPE_MEMORY_BARRIER };
		barrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
		barrier.dstAccessMask = VK_ACCESS_INDIRECT_COMMAND_READ_BIT | VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT;
		vkCmdPipelineBarrier(commandBuffer, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT | VK_PIPELINE_STAGE_VERTEX_INPUT_BIT, 0, 1, &barrier, 0, NULL, 0, NULL);
	}

	//--------------------------------------------------------------------------------------------------------------------

	std::vector<VkDescriptorSetLayout> kMesh3DGS::PrepareRenderingDSLayout(kRHIDevice& rhidevice) {

		VkDescriptorSetLayoutBinding uboLayoutBinding{};
		uboLayoutBinding.binding = 0;
		uboLayoutBinding.descriptorCount = 1;
		uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		uboLayoutBinding.pImmutableSamplers = nullptr;
		uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

		std::vector<VkDescriptorSetLayoutBinding> bindings = { uboLayoutBinding };

		VkDescriptorSetLayoutCreateInfo layoutInfo{};
		layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
		layoutInfo.pBindings = bindings.data();

		if (vkCreateDescriptorSetLayout(rhidevice.GetLogicDevice(), &layoutInfo, nullptr, &m_RenderingDSLayout) != VK_SUCCESS) {
			throw std::runtime_error("failed to create descriptor set layout!");
		}

		return std::vector<VkDescriptorSetLayout> {m_RenderingDSLayout};
	}

	void kMesh3DGS::SetupRenderingDescSets(kRHIDevice& rhidevice) {
		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = rhidevice.GetDescriptorPool();
		allocInfo.descriptorSetCount = 1;
		allocInfo.pSetLayouts = &m_RenderingDSLayout;

		if (vkAllocateDescriptorSets(rhidevice.GetLogicDevice(), &allocInfo, &m_RenderingDS) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate descriptor sets!");
		}

		std::vector<VkWriteDescriptorSet> descriptorWrites(1);
		VkDescriptorBufferInfo buffer0_Info = m_UniformBuffer->GetBufferInfo();
		descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[0].dstSet = m_RenderingDS;
		descriptorWrites[0].dstBinding = 0;
		descriptorWrites[0].dstArrayElement = 0;
		descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrites[0].descriptorCount = 1;
		descriptorWrites[0].pBufferInfo = &buffer0_Info;

		// In Vulkan, a descriptor set (VkDescriptorSet) is a container used to store descriptors. 
		// Descriptors are mechanisms in Vulkan for binding resources (such as uniform buffers, 
		// storage buffers, textures, samplers, etc.) to shaders. Each descriptor set corresponds 
		// to one or more binding points in the shader, and vkUpdateDescriptorSets is the function
		// used to update these binding relationships.
		vkUpdateDescriptorSets(rhidevice.GetLogicDevice(), static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
	}

	void kMesh3DGS::CreateRenderingPipeline(kRHIDevice& rhidevice) {

		VkVertexInputBindingDescription bindingDescription{};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(kSplatQuad);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		std::vector<VkVertexInputAttributeDescription> attributeDescriptions(3);

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32A32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(kSplatQuad, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32A32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(kSplatQuad, color);

		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32B32A32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(kSplatQuad, obb);

		kGraphicsPipelineCreateInfo createinfo;
		createinfo.vert_shader_file = "shaders/gs_point_vert.spv";
		createinfo.frag_shader_file = "shaders/gs_point_frag.spv";
		createinfo.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;

		createinfo.render_pass = rhidevice.GetRenderPass();
		createinfo.descriptor_set_layouts = this->PrepareRenderingDSLayout(rhidevice);
		//createinfo.push_constant_ranges = this->PreparePushConstantRange(rhidevice);
		createinfo.input_binding = bindingDescription;
		createinfo.input_attributes = attributeDescriptions;
		m_RenderingPipeline.CreateGraphicsPipeline(rhidevice, createinfo);

		SetupRenderingDescSets(rhidevice);
	}

	void kMesh3DGS::BuildRenderingCommandBuffer(VkCommandBuffer commandBuffer, kCamera& camera) {


		VkDeviceSize offsets[] = { 0 };
		VkBuffer vertexBuffers[] = { m_QuadVertexBuffer->GetBuffer() };

		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_RenderingPipeline.GetPipeline());
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
		vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_RenderingPipeline.GetPipelineLayout(), 0, 1, &m_RenderingDS, 0, nullptr);
		vkCmdDraw(commandBuffer, m_SplatScene.gs_count, 1, 0, 0);
	}
	//--------------------------------------------------------------------------------------------------------------------

	void kMesh3DGS::BuildComputeCommandBuffer(VkCommandBuffer commandBuffer, kCamera& camera) {

		BuildProjectionCommandBuffer(commandBuffer, camera);
	}

    void kMesh3DGS::UpdateUniformBuffer(kRHIDevice& rhidevice, kCamera& camera) {
		ModelObjShaderData temp_shaderdat{};
		temp_shaderdat.model = glm::mat4(1.0f);
		temp_shaderdat.view = camera.GetViewMat();
		temp_shaderdat.proj = camera.GetProjMat();
		temp_shaderdat.params.x = (float)rhidevice.GetExtent().width;
		temp_shaderdat.params.y = (float)rhidevice.GetExtent().height;
		temp_shaderdat.params.z = (float)m_SplatScene.gs_points.size();

		m_UniformBuffer->UpdateBuffer(&temp_shaderdat, sizeof(temp_shaderdat));
    }

    void kMesh3DGS::BuildGraphicCommandBuffer(VkCommandBuffer commandBuffer, kCamera& camera) {

		BuildRenderingCommandBuffer(commandBuffer, camera);
    }

	void kMesh3DGS::Load(kRHIDevice& rhidevice) {

		LoadGSSplatFile("./models/3dgs/dianli.splat", m_SplatScene);

		m_UniformBuffer = std::make_shared<kRHIBuffer>();
		m_UniformBuffer->CreateUniformBuffer(rhidevice, sizeof(ModelObjShaderData));

		m_3DGSVertexBuffer = std::make_shared<kRHIBuffer>();
		m_3DGSVertexBuffer->CreateShaderStorageBuffer(rhidevice, (const char*)m_SplatScene.gs_points.data(), m_SplatScene.gs_points.size() * sizeof(kSplatVertex));


		size_t buffer_size = m_SplatScene.gs_points.size() * sizeof(kSplatQuad);
		char* pbuffer = new char[buffer_size];
		memset(pbuffer, 0, buffer_size);
		m_QuadVertexBuffer = std::make_shared<kRHIBuffer>();
		m_QuadVertexBuffer->CreateShaderStorageBuffer(rhidevice, pbuffer, buffer_size);

		//std::vector<kSplatQuad> quads;
		//quads.resize(m_SplatScene.gs_points.size());
		//for (size_t i = 0; i < m_SplatScene.gs_points.size(); ++i) {
		//	quads[i].pos = m_SplatScene.gs_points[i].pos;
		//	quads[i].color = m_SplatScene.gs_points[i].color;
		//}
		//m_QuadVertexBuffer = std::make_shared<kRHIBuffer>();
		//m_QuadVertexBuffer->CreateStageBuffer(rhidevice, (const char*)quads.data(), quads.size() * sizeof(kSplatQuad));

		CreateProjectionComputePipeline(rhidevice);
		CreateRenderingPipeline(rhidevice);
	}

	void kMesh3DGS::Unload(kRHIDevice& rhidevice) {

		m_3DGSVertexBuffer.reset();
		m_QuadVertexBuffer.reset();
		m_UniformBuffer.reset();

		vkDestroyDescriptorSetLayout(rhidevice.GetLogicDevice(), m_RenderingDSLayout, nullptr);
		vkDestroyDescriptorSetLayout(rhidevice.GetLogicDevice(), m_ProjectionDSLayout, nullptr);

		m_ProjectionComp.ReleaseComputePipeline(rhidevice);
		m_RenderingPipeline.ReleaseGraphicsPipeline(rhidevice);
	}

	bool kMesh3DGS::LoadGSSplatFile(const std::string& filepath, kSplatScene& splatscene){

		std::ifstream splatstream(filepath, std::ios_base::binary);
		if (!splatstream.good())
			return false;
		
		splatstream.seekg(0, splatstream.end);
		uint64_t filesize = splatstream.tellg();
		int point_count = (int)filesize / 32;

		std::vector< kSplatRaw> splat_array;
		splat_array.resize(point_count);
		splatscene.resize(point_count);

		splatstream.seekg(0, splatstream.beg);
		splatstream.read((char*)splat_array.data(), point_count * sizeof(kSplatRaw));

		// convert color to sh coefficient
		const float sh_C0 = 0.28209479177387814f;

		uint32_t ptsize = sizeof(float) * 3;
		uint32_t cov3dsize = sizeof(float) * 6;
		uint32_t colorsize = sizeof(float) * 4;

		glm::vec3 tmpscale;
		glm::quat tmpquat;
		glm::vec4 tmpcolor;

		splatscene.bb_min = glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX);
		splatscene.bb_max = -glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX);
		for (int k = 0; k < point_count; ++k)
		{
			splatscene.bb_min.x = std::min(splatscene.bb_min.x, splat_array[k].pos[0]);
			splatscene.bb_min.y = std::min(splatscene.bb_min.y, splat_array[k].pos[1]);
			splatscene.bb_min.z = std::min(splatscene.bb_min.z, splat_array[k].pos[2]);

			splatscene.bb_max.x = std::max(splatscene.bb_max.x, splat_array[k].pos[0]);
			splatscene.bb_max.y = std::max(splatscene.bb_max.y, splat_array[k].pos[1]);
			splatscene.bb_max.z = std::max(splatscene.bb_max.z, splat_array[k].pos[2]);

			// position
			memcpy(&(splatscene.gs_points[k].pos), splat_array[k].pos, sizeof(float) * 3);


			// color, convert color to sh coefficient
			tmpcolor.r = ((splat_array[k].color[0] / 255.0f) - 0.5f) / sh_C0;
			tmpcolor.g = ((splat_array[k].color[1] / 255.0f) - 0.5f) / sh_C0;
			tmpcolor.b = ((splat_array[k].color[2] / 255.0f) - 0.5f) / sh_C0;
			tmpcolor.a = (float)log((255.0 / splat_array[k].color[3]) - 1);
			tmpcolor.a = (float)1.0f / (1.0f + exp(tmpcolor.a));
			memcpy(&(splatscene.gs_points[k].color), &tmpcolor, sizeof(float) * 4);

			// rotate
			tmpquat.w = (splat_array[k].rot[0] - 128) / 128.0f;
			tmpquat.x = (splat_array[k].rot[1] - 128) / 128.0f;
			tmpquat.y = (splat_array[k].rot[2] - 128) / 128.0f;
			tmpquat.z = (splat_array[k].rot[3] - 128) / 128.0f;

			// scale
			tmpscale.x = splat_array[k].scale[0];
			tmpscale.y = splat_array[k].scale[1];
			tmpscale.z = splat_array[k].scale[2];

			// conv3d
			glm::mat3 rot;
			float xx = tmpquat.x * tmpquat.x;
			float yy = tmpquat.y * tmpquat.y;
			float zz = tmpquat.z * tmpquat.z;
			float xy = tmpquat.x * tmpquat.y;
			float xz = tmpquat.x * tmpquat.z;
			float yz = tmpquat.y * tmpquat.z;
			float wx = tmpquat.w * tmpquat.x;
			float wy = tmpquat.w * tmpquat.y;
			float wz = tmpquat.w * tmpquat.z;
			rot[0][0] = 1.f - 2.f * (yy + zz);
			rot[0][1] = 2.f * (xy + wz);
			rot[0][2] = 2.f * (xz - wy);
			rot[1][0] = 2.f * (xy - wz);
			rot[1][1] = 1.f - 2.f * (xx + zz);
			rot[1][2] = 2.f * (yz + wx);
			rot[2][0] = 2.f * (xz + wy);
			rot[2][1] = 2.f * (yz - wx);
			rot[2][2] = 1.f - 2.f * (xx + yy);

			glm::mat3 ss = glm::mat3(0.f);
			ss[0][0] = tmpscale[0] * tmpscale[0];
			ss[1][1] = tmpscale[1] * tmpscale[1];
			ss[2][2] = tmpscale[2] * tmpscale[2];
			glm::mat3 cov3d = rot * ss * transpose(rot);

			splatscene.gs_points[k].cov3d_1[0] = cov3d[0][0];
			splatscene.gs_points[k].cov3d_1[1] = cov3d[1][0];
			splatscene.gs_points[k].cov3d_1[2] = cov3d[2][0];
			splatscene.gs_points[k].cov3d_2[0] = cov3d[1][1];
			splatscene.gs_points[k].cov3d_2[1] = cov3d[2][1];
			splatscene.gs_points[k].cov3d_2[2] = cov3d[2][2];
		}
		
		glm::vec3 bbcenter = (splatscene.bb_max + splatscene.bb_min) * 0.5f;
		glm::vec3 bbsize = (splatscene.bb_max - splatscene.bb_min);

		std::cout << "bbox center:" << bbcenter.x << " , " << bbcenter.y << " , " << bbcenter.z << std::endl;
		std::cout << "bbox size  :" << bbsize.x << " , " << bbsize.y << " , " << bbsize.z << std::endl;

		return true;
    }

	glm::vec3 kMesh3DGS::GetBBoxCenter() {

		glm::vec3 bbcenter = (m_SplatScene.bb_max + m_SplatScene.bb_min) * 0.5f;
		return bbcenter;
	}

	glm::vec3 kMesh3DGS::GetBBoxSize() {

		glm::vec3 bbsize = (m_SplatScene.bb_max - m_SplatScene.bb_min);
		return bbsize;
	}


}