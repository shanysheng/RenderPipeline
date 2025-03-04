#pragma once

#include "Common.h"


#include "RHIBuffer.h"
#include "RHITexture2D.h"

#include "Mesh.h"

namespace pipeline {


    struct kSplatRaw
    {
        float pos[3];
        float scale[3];
        uint8_t color[4];
        uint8_t rot[4];
    };

    struct kSplatVertex {
        glm::vec3 pos;
        glm::vec4 color;
        glm::vec3 cov3d_1;
        glm::vec3 cov3d_2;
    };

    struct kSplatQuad {
        glm::vec3 pos;      // position
        glm::vec3 obb;      // size and rotate
        glm::vec4 color;    // color and opacity
    };

    struct kSplatScene
    {
        uint32_t gs_count;

        glm::vec3 bb_min;
        glm::vec3 bb_max;

        std::vector<kSplatVertex> gs_points;

        void resize(uint32_t count) {
            gs_count = count;
            gs_points.resize(gs_count);
        }
    };

	class kMesh3DGS : public kMeshBase
	{
	public:
        kMesh3DGS();
        virtual ~kMesh3DGS();

        VkVertexInputBindingDescription getBindingDescription() ;
        std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions() ;

        std::vector<VkDescriptorSetLayout> PrepareDescriptorSetLayout(kRHIDevice& rhidevice) ;
        std::vector<VkPushConstantRange> PreparePushConstantRange(kRHIDevice& rhidevice);

        void Load(kRHIDevice& rhidevicet);
        void Unload(kRHIDevice& rhidevice);

        void UpdateUniformBuffer(kRHIDevice& rhidevice, uint32_t currentImage) ;
        void BuildCommandBuffer(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, kCamera& camera) ;

        glm::vec3 GetBBoxCenter();
        glm::vec3 GetBBoxSize();
    protected:
        struct ModelObjShaderData {
            alignas(16) glm::mat4 model;
            alignas(16) glm::mat4 view;
            alignas(16) glm::mat4 proj;
        };

        bool LoadGSSplatFile(const std::string& filepath, kSplatScene& splatscene);

        void SetupRenderingDescSets(kRHIDevice& rhidevice);
        void CreateGraphicPipeline();
        void BuildRenderingCommandBuffer(VkCommandBuffer commandBuffer);

        void SetupSortDescSets(kRHIDevice& rhidevice);
        void CreateSortComputePipeline();
        void BuildSortCommandBuffer(VkCommandBuffer commandBuffer);

        void SetupProjectionDescSets(kRHIDevice& rhidevice);
        void CreateProjectionComputePipeline();
        void BuildProjectionCommandBuffer(VkCommandBuffer commandBuffer);
    protected:
        kSplatScene     m_SplatScene;

        std::shared_ptr<kRHIBuffer>     m_UniformBuffer;
        std::shared_ptr<kRHIBuffer>     m_3DGSVertexBuffer;
        std::shared_ptr<kRHIBuffer>     m_QuadVertexBuffer;
        std::shared_ptr<kRHIBuffer>     m_QuadIndexBuffer;

        VkDescriptorSetLayout	        m_RenderingDescSetLayout;
        VkDescriptorSet	                m_RenderingDescSet;
	};





}

