#pragma once

#include "Common.h"


#include "RHIBuffer.h"
#include "RHITexture2D.h"
#include "RHIGraphicPipeline.h"
#include "RHIComputePipeline.h"

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
        glm::vec4 color;    // color and opacity
        glm::vec3 obb;      // size and rotate
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

        void Load(kRHIDevice& rhidevicet);
        void Unload(kRHIDevice& rhidevice);

        void BuildComputeCommandBuffer(VkCommandBuffer commandBuffer, kCamera& camera);

        void UpdateUniformBuffer(kRHIDevice& rhidevice, kCamera& camera) ;
        void BuildGraphicCommandBuffer(VkCommandBuffer commandBuffer, kCamera& camera);

        glm::vec3 GetBBoxCenter();
        glm::vec3 GetBBoxSize();
    protected:
        struct ModelObjShaderData {
            alignas(16) glm::mat4 model;
            alignas(16) glm::mat4 view;
            alignas(16) glm::mat4 proj;
            uint32_t particleCount;
        };

        bool LoadGSSplatFile(const std::string& filepath, kSplatScene& splatscene);

        void SetupSortDescSets(kRHIDevice& rhidevice);
        void CreateSortComputePipeline(kRHIDevice& rhidevice);
        void BuildSortCommandBuffer(VkCommandBuffer commandBuffer);

        std::vector<VkDescriptorSetLayout> PrepareProjectionDSLayout(kRHIDevice& rhidevice);
        void SetupProjectionDescSets(kRHIDevice& rhidevice);
        void CreateProjectionComputePipeline(kRHIDevice& rhidevice);
        void BuildProjectionCommandBuffer(VkCommandBuffer commandBuffer, kCamera& camera);

        std::vector<VkDescriptorSetLayout> PrepareRenderingDSLayout(kRHIDevice& rhidevice);
        void SetupRenderingDescSets(kRHIDevice& rhidevice);
        void CreateRenderingPipeline(kRHIDevice& rhidevice);
        void BuildRenderingCommandBuffer(VkCommandBuffer commandBuffer, kCamera& camera);
    protected:
        kSplatScene     m_SplatScene;

        std::shared_ptr<kRHIBuffer>     m_UniformBuffer;
        std::shared_ptr<kRHIBuffer>     m_3DGSVertexBuffer;
        std::shared_ptr<kRHIBuffer>     m_QuadVertexBuffer;
        std::shared_ptr<kRHIBuffer>     m_QuadIndexBuffer;

        VkDescriptorSetLayout	        m_RenderingDSLayout;
        VkDescriptorSet	                m_RenderingDS;
        kRHIGraphicPipeline				m_RenderingPipeline;


        VkDescriptorSetLayout	        m_ProjectionDSLayout;
        VkDescriptorSet	                m_ProjectionDS;
        kRHIComputePipeline             m_ProjectionComp;
	};





}

