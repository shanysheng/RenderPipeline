#include "Model3DGS.h"

namespace pipeline {



    //--------------------------------------------------------------------------------------------------

    Model3DGS::Model3DGS() {

    }

    Model3DGS::~Model3DGS() {

    }

    VkVertexInputBindingDescription Model3DGS::getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};

        return bindingDescription;
    }

    std::vector<VkVertexInputAttributeDescription> Model3DGS::getAttributeDescriptions() {
        std::vector<VkVertexInputAttributeDescription> attributeDescriptions(3);

        return attributeDescriptions;
    }

    std::vector<VkDescriptorSetLayout> Model3DGS::PrepareDescriptorSetLayout(kRHIDevice& rhidevice) {

        return std::vector<VkDescriptorSetLayout> {};
    }

    std::vector<VkPushConstantRange> Model3DGS::PreparePushConstantRange(kRHIDevice& rhidevice) {

        return std::vector<VkPushConstantRange>{};
    }

    void Model3DGS::Load(kRHIDevice& rhidevicet) {

    }

    void Model3DGS::Unload(kRHIDevice& rhidevice) {

    }

    void Model3DGS::UpdateUniformBuffer(kRHIDevice& rhidevice, uint32_t currentImage) {

    }

    void Model3DGS::BuildCommandBuffer(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, kCamera& camera) {

    }

	bool Model3DGS::LoadGSSplatFile(const std::string& filepath, kSplatScene& splatscene){

		std::ifstream splatstream(filepath, std::ios_base::binary);
		if (!splatstream.good())
			return false;
		
		splatstream.seekg(0, splatstream.end);
		uint64_t filesize = splatstream.tellg();
		int point_count = filesize / 32;

		std::vector< kSplatPoint> splat_array;
		splat_array.resize(point_count);
		splatscene.resize(point_count);

		splatstream.seekg(0, splatstream.beg);
		splatstream.read((char*)splat_array.data(), point_count * sizeof(kSplatPoint));

		// convert color to sh coefficient
		const float sh_C0 = 0.28209479177387814;

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
			// position
			memcpy(splatscene.position_buf.data() + 3 * k, splat_array[k].pos, sizeof(float) * 3);

			splatscene.bb_min.x = std::min(splatscene.bb_min.x, splat_array[k].pos[0]);
			splatscene.bb_min.y = std::min(splatscene.bb_min.y, splat_array[k].pos[1]);
			splatscene.bb_min.z = std::min(splatscene.bb_min.z, splat_array[k].pos[2]);

			splatscene.bb_max.x = std::max(splatscene.bb_max.x, splat_array[k].pos[0]);
			splatscene.bb_max.y = std::max(splatscene.bb_max.y, splat_array[k].pos[1]);
			splatscene.bb_max.z = std::max(splatscene.bb_max.z, splat_array[k].pos[2]);

			// color, convert color to sh coefficient
			tmpcolor.r = ((splat_array[k].color[0] / 255.0f) - 0.5f) / sh_C0;
			tmpcolor.g = ((splat_array[k].color[1] / 255.0f) - 0.5f) / sh_C0;
			tmpcolor.b = ((splat_array[k].color[2] / 255.0f) - 0.5f) / sh_C0;
			tmpcolor.a = ((splat_array[k].color[3] / 255.0f) - 0.5f) / sh_C0;

			memcpy(splatscene.color_buf.data() + 4 * k, &tmpcolor, sizeof(float) * 4);

			// scale
			tmpscale.x = splat_array[k].scale[0];
			tmpscale.y = splat_array[k].scale[1];
			tmpscale.z = splat_array[k].scale[2];

			// rotate
			tmpquat.w = (splat_array[k].rot[0] - 128) / 128.0f;
			tmpquat.x = (splat_array[k].rot[1] - 128) / 128.0f;
			tmpquat.y = (splat_array[k].rot[2] - 128) / 128.0f;
			tmpquat.z = (splat_array[k].rot[3] - 128) / 128.0f;

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

			splatscene.cov3d_buf[6 * k + 0] = cov3d[0][0];
			splatscene.cov3d_buf[6 * k + 1] = cov3d[1][0];
			splatscene.cov3d_buf[6 * k + 2] = cov3d[2][0];
			splatscene.cov3d_buf[6 * k + 3] = cov3d[1][1];
			splatscene.cov3d_buf[6 * k + 4] = cov3d[2][1];
			splatscene.cov3d_buf[6 * k + 5] = cov3d[2][2];
		}

		return true;
    }

}