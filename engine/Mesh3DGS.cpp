#include "Mesh3DGS.h"
#include "RHIDevice.h"
#include "Camera.h"


namespace pipeline {

    //--------------------------------------------------------------------------------------------------

    kMesh3DGS::kMesh3DGS() {

    }

    kMesh3DGS::~kMesh3DGS() {

    }

    VkVertexInputBindingDescription kMesh3DGS::getBindingDescription() {
		VkVertexInputBindingDescription bindingDescription{};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(kSplatPointVertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;

        return bindingDescription;
    }

    std::vector<VkVertexInputAttributeDescription> kMesh3DGS::getAttributeDescriptions() {
		std::vector<VkVertexInputAttributeDescription> attributeDescriptions(4);

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(kSplatPointVertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32A32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(kSplatPointVertex, color);

		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(kSplatPointVertex, cov3d_1);

		attributeDescriptions[3].binding = 0;
		attributeDescriptions[3].location = 3;
		attributeDescriptions[3].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[3].offset = offsetof(kSplatPointVertex, cov3d_2);

        return attributeDescriptions;
    }


	void kMesh3DGS::SetupDescriptorSets(kRHIDevice& rhidevice) {
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

		std::vector<VkWriteDescriptorSet> descriptorWrites(1);

		descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[0].dstSet = m_DescriptorSet;
		descriptorWrites[0].dstBinding = 0;
		descriptorWrites[0].dstArrayElement = 0;
		descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrites[0].descriptorCount = 1;
		descriptorWrites[0].pBufferInfo = &bufferInfo;

		// In Vulkan, a descriptor set (VkDescriptorSet) is a container used to store descriptors. 
		// Descriptors are mechanisms in Vulkan for binding resources (such as uniform buffers, 
		// storage buffers, textures, samplers, etc.) to shaders. Each descriptor set corresponds 
		// to one or more binding points in the shader, and vkUpdateDescriptorSets is the function
		// used to update these binding relationships.
		vkUpdateDescriptorSets(rhidevice.GetLogicDevice(), static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
	}

    std::vector<VkDescriptorSetLayout> kMesh3DGS::PrepareDescriptorSetLayout(kRHIDevice& rhidevice) {

		VkDescriptorSetLayoutBinding uboLayoutBinding{};
		uboLayoutBinding.binding = 0;
		uboLayoutBinding.descriptorCount = 1;
		uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		uboLayoutBinding.pImmutableSamplers = nullptr;
		uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

		std::vector<VkDescriptorSetLayoutBinding> bindings = { uboLayoutBinding};

		VkDescriptorSetLayoutCreateInfo layoutInfo{};
		layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
		layoutInfo.pBindings = bindings.data();

		if (vkCreateDescriptorSetLayout(rhidevice.GetLogicDevice(), &layoutInfo, nullptr, &m_DescriptorSetLayout) != VK_SUCCESS) {
			throw std::runtime_error("failed to create descriptor set layout!");
		}

		return std::vector<VkDescriptorSetLayout> {m_DescriptorSetLayout};
    }

    std::vector<VkPushConstantRange> kMesh3DGS::PreparePushConstantRange(kRHIDevice& rhidevice) {

        return std::vector<VkPushConstantRange>{};
    }

    void kMesh3DGS::Load(kRHIDevice& rhidevice) {

		m_VertexBuffer = std::make_shared<kRHIBuffer>();
		m_UniformBuffer = std::make_shared<kRHIBuffer>();

		LoadGSSplatFile("./models/3dgs/dianli.splat", m_SplatScene);

		m_VertexBuffer->CreateVertexBuffer(rhidevice, (const char*)m_SplatScene.gs_points.data(), m_SplatScene.gs_points.size() * sizeof(kSplatPointVertex));
		m_UniformBuffer->CreateUniformBuffer(rhidevice, sizeof(ModelObjShaderData));

		SetupDescriptorSets(rhidevice);
    }

    void kMesh3DGS::Unload(kRHIDevice& rhidevice) {

		vkDestroyDescriptorSetLayout(rhidevice.GetLogicDevice(), m_DescriptorSetLayout, nullptr);

		m_VertexBuffer.reset();
		m_UniformBuffer.reset();
    }

    void kMesh3DGS::UpdateUniformBuffer(kRHIDevice& rhidevice, uint32_t currentImage) {

    }

    void kMesh3DGS::BuildCommandBuffer(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, kCamera& camera) {

		ModelObjShaderData temp_shaderdat{};
		temp_shaderdat.model = glm::mat4(1.0f);
		temp_shaderdat.view = camera.GetViewMat();
		temp_shaderdat.proj = camera.GetProjMat();

		m_UniformBuffer->UpdateBuffer(&temp_shaderdat, sizeof(temp_shaderdat));

		VkDeviceSize offsets[] = { 0 };
		VkBuffer vertexBuffers[] = { m_VertexBuffer->GetBuffer() };

		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
		vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &m_DescriptorSet, 0, nullptr);
		vkCmdDraw(commandBuffer, m_SplatScene.gs_count, 100000, 0, 0);
    }

	bool kMesh3DGS::LoadGSSplatFile(const std::string& filepath, kSplatScene& splatscene){

		std::ifstream splatstream(filepath, std::ios_base::binary);
		if (!splatstream.good())
			return false;
		
		splatstream.seekg(0, splatstream.end);
		uint64_t filesize = splatstream.tellg();
		int point_count = (int)filesize / 32;

		std::vector< kSplatPointRaw> splat_array;
		splat_array.resize(point_count);
		splatscene.resize(point_count);

		splatstream.seekg(0, splatstream.beg);
		splatstream.read((char*)splat_array.data(), point_count * sizeof(kSplatPointRaw));

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

}