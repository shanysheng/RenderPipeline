#pragma once

#include "Common.h"


#include "RHIBuffer.h"
#include "RHITexture2D.h"
#include "RHIGraphicPipeline.h"
#include "RHIComputePipeline.h"

#include "Mesh.h"

namespace pipeline {

	class kMeshParticles : public kMeshBase
	{
	public:
        kMeshParticles();
        virtual ~kMeshParticles();

        void Load(kRHIDevice& rhidevicet);
        void Unload(kRHIDevice& rhidevice);

        void BuildComputeCommandBuffer(VkCommandBuffer commandBuffer, kCamera& camera);

        void UpdateUniformBuffer(kRHIDevice& rhidevice, kCamera& camera);
        void BuildGraphicCommandBuffer(VkCommandBuffer commandBuffer, kCamera& camera);

        glm::vec3 GetBBoxCenter() { return m_BBoxCenter; }
        glm::vec3 GetBBoxSize() { return m_BBoxSize; }

    protected:

        struct ParticleUBO {
            alignas(16) glm::mat4 model;
            alignas(16) glm::mat4 view;
            alignas(16) glm::mat4 proj;
            float deltaTime = 1.0f;
        };

        struct Particle {
            glm::vec3 position;
            glm::vec3 velocity;
            glm::vec4 color;

            static VkVertexInputBindingDescription getBindingDescription() {
                VkVertexInputBindingDescription bindingDescription{};
                bindingDescription.binding = 0;
                bindingDescription.stride = sizeof(Particle);
                bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

                return bindingDescription;
            }

            static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
                std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

                attributeDescriptions[0].binding = 0;
                attributeDescriptions[0].location = 0;
                attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
                attributeDescriptions[0].offset = offsetof(Particle, position);

                attributeDescriptions[1].binding = 0;
                attributeDescriptions[1].location = 1;
                attributeDescriptions[1].format = VK_FORMAT_R32G32B32A32_SFLOAT;
                attributeDescriptions[1].offset = offsetof(Particle, color);

                return attributeDescriptions;
            }
        };

        std::vector<VkDescriptorSetLayout> PrepareComputeDSLayout(kRHIDevice& rhidevice);
        void SetupComputeDescSets(kRHIDevice& rhidevice);
        void CreateComputeComputePipeline(kRHIDevice& rhidevice);

        std::vector<VkDescriptorSetLayout> PrepareRenderingDSLayout(kRHIDevice& rhidevice);
        void SetupRenderingDescSets(kRHIDevice& rhidevice);
        void CreateRenderingPipeline(kRHIDevice& rhidevice);

    protected:
        glm::vec3       m_BBoxCenter;
        glm::vec3       m_BBoxSize;

        std::shared_ptr<kRHIBuffer>     m_UniformBuffer;

        VkDescriptorSetLayout	        m_RenderingDSLayout;
        VkDescriptorSet	                m_RenderingDS;
        kRHIGraphicPipeline				m_RenderingPipeline;

        VkDescriptorSetLayout	        m_ComputeDSLayout;
        VkDescriptorSet	                m_ComputeDS;
        kRHIComputePipeline             m_ComputeComp;
	};


}
