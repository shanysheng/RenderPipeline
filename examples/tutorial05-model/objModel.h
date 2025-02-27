#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>

#include "kBuffer.h"
#include "kTexture.h"

#include <vector>
#include <array>
#include <string>
#include <unordered_map>


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

    template<> struct std::hash<Vertex> {
        size_t operator()(Vertex const& vertex) const {
            return ((std::hash<glm::vec3>()(vertex.pos) ^ (std::hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (std::hash<glm::vec2>()(vertex.texCoord) << 1);
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
    Model() {

    };

    void Load(kContext& contextref) {

        loadModelFromfile();

        m_VertexBuffer.createVertexBuffer(contextref, (const char*)m_Vertex.data(), m_Vertex.size() * sizeof(Vertex));
        m_IndexBuffer.createIndexBuffer(contextref, (const char*)m_Indices.data(), m_Indices.size() * sizeof(uint32_t));

        m_Texture.createTexture(contextref, TEXTURE_PATH);
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

protected:
    void loadModelFromfile();

public:
    std::vector<Vertex>     m_Vertex;
    std::vector<uint32_t>   m_Indices;


    kBuffer     m_VertexBuffer;
    kBuffer     m_IndexBuffer;

    kTexture	m_Texture;

};



