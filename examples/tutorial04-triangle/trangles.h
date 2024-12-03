#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


#include "kBuffer.h"
#include "kTexture.h"

#include <vector>
#include <array>



struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};


struct Vertex {
    glm::vec2 pos;
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
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
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
};


class Model
{
public:
    Model() {
        const std::vector<Vertex> vertices = {
            {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
            {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
            {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
            {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}
        };

        const std::vector<uint16_t> indices = {
            0, 1, 2, 2, 3, 0
        };

        m_Vertex.assign(vertices.begin(), vertices.end());
        m_Indices.assign(indices.begin(), indices.end());
    };

    void Load(kContext& contextref) {
        m_VertexBuffer.createVertexBuffer(contextref, (const char*)m_Vertex.data(), m_Vertex.size() * sizeof(Vertex));
        m_IndexBuffer.createIndexBuffer(contextref, (const char*)m_Indices.data(), m_Indices.size() * sizeof(uint16_t));

        m_Texture.createTextureImage(contextref);
        m_Texture.createTextureImageView(contextref);
        m_Texture.createTextureSampler(contextref);
    }

    void Unload(kContext& contextref) {

        m_Texture.cleanupTexture(contextref);
        m_IndexBuffer.cleanupBuffer(contextref);
        m_VertexBuffer.cleanupBuffer(contextref);
    }

    VkBuffer getVertexBuffer() { return m_VertexBuffer.getBuffer(); }
    VkBuffer getIndexBuffer() { return m_IndexBuffer.getBuffer(); }
    uint32_t getIndiesCount() { return (uint32_t)m_Indices.size(); }

    kTexture& getTexture() { return m_Texture; }
    const kTexture& getTexture()const { return m_Texture; }

public:
    std::vector<Vertex>     m_Vertex;
    std::vector<uint16_t>   m_Indices;


    kBuffer     m_VertexBuffer;
    kBuffer     m_IndexBuffer;

    kTexture	m_Texture;

};

