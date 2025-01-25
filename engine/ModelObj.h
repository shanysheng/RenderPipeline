#pragma once

#include "Common.h"



#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>


#include "RHIBuffer.h"
#include "RHITexture2D.h"


namespace pipeline {



    class ModelObj
    {
    public:
        struct Vertex {
            glm::vec3 pos;
            glm::vec3 color;
            glm::vec2 texCoord;

            static VkVertexInputBindingDescription getBindingDescription() {
                VkVertexInputBindingDescription bindingDescription{};
                bindingDescription.binding = 0;
                bindingDescription.stride = sizeof(Vertex);
                bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

                return bindingDescription;
            }

            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions() {
                std::vector<VkVertexInputAttributeDescription> attributeDescriptions(3);

                attributeDescriptions[0].binding = 0;
                attributeDescriptions[0].location = 0;
                attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
                attributeDescriptions[0].offset = offsetof(Vertex, pos);

                attributeDescriptions[1].binding = 0;
                attributeDescriptions[1].location = 1;
                attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
                attributeDescriptions[1].offset = offsetof(Vertex, color);

                attributeDescriptions[2].binding = 0;
                attributeDescriptions[2].location = 2;
                attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
                attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

                return attributeDescriptions;
            }

            bool operator==(const Vertex& other) const {
                return pos == other.pos && color == other.color && texCoord == other.texCoord;
            }
        };

        struct UniformBufferObject {
            alignas(16) glm::mat4 model;
            alignas(16) glm::mat4 view;
            alignas(16) glm::mat4 proj;
        };

    public:
        ModelObj();
        virtual ~ModelObj();

        VkDescriptorSetLayout PrepareDescriptorSetLayout(kRHIDevice& rhidevice);

        void Load(kRHIDevice& rhidevicet);
        void Unload(kRHIDevice& rhidevice);

        void UpdateUniformBuffer(kRHIDevice& rhidevice, uint32_t currentImage);
        void BuildCommandBuffer(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout);

    protected:
        void LoadModelFromfile(std::vector<Vertex>& vertex_array, std::vector<uint32_t>& index_array);
        void SetupDescriptorSets(kRHIDevice& rhidevice);


    protected:

        kRHIBuffer              m_VertexBuffer;
        kRHIBuffer              m_IndexBuffer;
        size_t                  m_IndexCount;

        kRHIBuffer              m_UniformBuffer;
        kRHITexture2D           m_Texture;

        VkDescriptorSetLayout	m_DescriptorSetLayout;
        VkDescriptorSet	        m_DescriptorSet;
    };

}

