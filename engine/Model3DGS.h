#pragma once

#include "Common.h"


#include "RHIBuffer.h"
#include "RHITexture2D.h"

#include "Mesh.h"

namespace pipeline {

    struct kSplatPoint
    {
        float pos[3];
        float scale[3];
        uint8_t color[4];
        uint8_t rot[4];
    };

    struct kSplatScene
    {
        uint32_t point_count;

        glm::vec3 bb_min;
        glm::vec3 bb_max;

        std::vector<float> position_buf;
        std::vector<float> cov3d_buf;
        std::vector<float> color_buf;

        void resize(uint32_t count) {
            point_count = count;
            position_buf.resize(point_count * 3);
            cov3d_buf.resize(point_count * 6);
            color_buf.resize(point_count * 4);
        }
    };

	class Model3DGS : public IModel
	{
	public:
        Model3DGS();
        virtual ~Model3DGS();

        VkVertexInputBindingDescription getBindingDescription() ;
        std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions() ;

        std::vector<VkDescriptorSetLayout> PrepareDescriptorSetLayout(kRHIDevice& rhidevice) ;
        std::vector<VkPushConstantRange> PreparePushConstantRange(kRHIDevice& rhidevice);

        void Load(kRHIDevice& rhidevicet);
        void Unload(kRHIDevice& rhidevice);

        void UpdateUniformBuffer(kRHIDevice& rhidevice, uint32_t currentImage) ;
        void BuildCommandBuffer(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, kCamera& camera) ;

        bool LoadGSSplatFile(const std::string& filepath, kSplatScene& splatscene);

    protected:


    protected:
        kSplatScene     m_SplatScene;
	};





}

