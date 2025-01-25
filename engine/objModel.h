#pragma once

#include "Common.h"



#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>


#include "BufferGPUResource.h"
#include "ImageTextureGPUResource.h"


namespace pipeline {

    const std::string MODEL_PATH = "resources/viking_room.obj";
    const std::string TEXTURE_PATH = "resources/viking_room.png";

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

        static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

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

    class Model
    {
    public:
        Model();
        virtual ~Model();

        void Load(kRHIContext& contextref, VkDescriptorSetLayout layout);
        void Unload(kRHIContext& contextref);

        void UpdateUniformBuffer(kRHIContext& contextref, uint32_t currentImage);
        void BuildCommandBuffer(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout);

    protected:
        void LoadModelFromfile(std::vector<Vertex>& vertex_array, std::vector<uint32_t>& index_array);
        void CreateDescriptorSets(kRHIContext& contextref, VkDeviceSize bufferSize, VkDescriptorSetLayout layout);

    protected:

        kBuffer                 m_VertexBuffer;
        kBuffer                 m_IndexBuffer;
        uint32_t                m_IndexCount;

        kUniformBuffer          m_UniformBuffer;
        kTexture	            m_Texture;

        VkDescriptorSet	        m_DescriptorSet;
    };

}

