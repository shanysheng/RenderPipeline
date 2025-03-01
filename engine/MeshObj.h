#pragma once

#include "Common.h"


#include "RHIBuffer.h"
#include "RHITexture2D.h"

#include "Mesh.h"

namespace pipeline {

    class kMeshObj : public kMeshBase
    {
    public:
        kMeshObj();
        virtual ~kMeshObj();

        VkVertexInputBindingDescription getBindingDescription();
        std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();

        std::vector<VkDescriptorSetLayout> PrepareDescriptorSetLayout(kRHIDevice& rhidevice);
        std::vector<VkPushConstantRange> PreparePushConstantRange(kRHIDevice& rhidevice);

        void Load(kRHIDevice& rhidevicet);
        void Unload(kRHIDevice& rhidevice);

        void UpdateUniformBuffer(kRHIDevice& rhidevice, uint32_t currentImage);
        void BuildCommandBuffer(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, kCamera& camera);

        glm::vec3 GetBBoxCenter() { return m_BBoxCenter; }
        glm::vec3 GetBBoxSize() { return m_BBoxSize; }

        struct Vertex {
            glm::vec3 pos;
            glm::vec3 color;
            glm::vec2 texCoord;

            bool operator==(const Vertex& other) const {
                return pos == other.pos && color == other.color && texCoord == other.texCoord;
            }
        };
    protected:

        struct ModelObjShaderData {
            alignas(16) glm::mat4 model;
            alignas(16) glm::mat4 view;
            alignas(16) glm::mat4 proj;
        };

        void LoadModelFromfile(std::vector<Vertex>& vertex_array, std::vector<uint32_t>& index_array);
        void SetupDescriptorSets(kRHIDevice& rhidevice);

    protected:
        glm::vec3       m_BBoxCenter;
        glm::vec3       m_BBoxSize;

        size_t                          m_IndexCount;
        size_t                          m_VertexCount;
        std::shared_ptr<kRHIBuffer>     m_IndexBuffer;
        std::shared_ptr<kRHIBuffer>     m_VertexBuffer;

        std::shared_ptr<kRHIBuffer>     m_UniformBuffer;
        std::shared_ptr<kRHITexture2D>  m_Texture;

        VkDescriptorSetLayout	        m_DescriptorSetLayout;
        VkDescriptorSet	                m_DescriptorSet;
    };

}

