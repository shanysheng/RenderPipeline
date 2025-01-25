#pragma once

#include "Common.h"



#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "RHIBuffer.h"
#include "RHITexture2D.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "tiny_gltf.h"

namespace pipeline {


    class ModelGltf
    {
    public:
        // The vertex layout for the samples' model
        struct Vertex {
            glm::vec3 pos;
            glm::vec3 normal;
            glm::vec2 uv;
            glm::vec3 color;


            static VkVertexInputBindingDescription getBindingDescription() {
                VkVertexInputBindingDescription bindingDescription{};
                bindingDescription.binding = 0;
                bindingDescription.stride = sizeof(Vertex);
                bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

                return bindingDescription;
            }

            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions() {
                std::vector<VkVertexInputAttributeDescription> attributeDescriptions(4);

                attributeDescriptions[0].binding = 0;
                attributeDescriptions[0].location = 0;
                attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
                attributeDescriptions[0].offset = offsetof(Vertex, pos);

                attributeDescriptions[1].binding = 0;
                attributeDescriptions[1].location = 1;
                attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
                attributeDescriptions[1].offset = offsetof(Vertex, normal);

                attributeDescriptions[2].binding = 0;
                attributeDescriptions[2].location = 2;
                attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
                attributeDescriptions[2].offset = offsetof(Vertex, uv);

                attributeDescriptions[3].binding = 0;
                attributeDescriptions[3].location = 2;
                attributeDescriptions[3].format = VK_FORMAT_R32G32_SFLOAT;
                attributeDescriptions[3].offset = offsetof(Vertex, color);

                return attributeDescriptions;
            }
        };

        // Single vertex buffer for all primitives
        struct {
            VkBuffer buffer;
            VkDeviceMemory memory;
        } vertices;

        // Single index buffer for all primitives
        struct {
            int count;
            VkBuffer buffer;
            VkDeviceMemory memory;
        } indices;

        // A primitive contains the data for a single draw call
        struct Primitive {
            uint32_t firstIndex;
            uint32_t indexCount;
            int32_t materialIndex;
        };

        // Contains the node's (optional) geometry and can be made up of an arbitrary number of primitives
        struct Mesh {
            std::vector<Primitive> primitives;
        };

        // A node represents an object in the glTF scene graph
        struct Node {
            Node* parent;
            std::vector<Node*> children;
            Mesh mesh;
            glm::mat4 matrix;
            ~Node() {
                for (auto& child : children) {
                    delete child;
                }
            }
        };

        // A glTF material stores information in e.g. the texture that is attached to it and colors
        struct Material {
            glm::vec4 baseColorFactor = glm::vec4(1.0f);
            uint32_t baseColorTextureIndex;
        };

        // Contains the texture for a single glTF image
        // Images may be reused by texture objects and are as such separated
        struct Image {
            kRHITexture2D texture;
            // We also store (and create) a descriptor set that's used to access this texture from the fragment shader
            VkDescriptorSet descriptorSet;
        };

        // A glTF texture stores a reference to the image and a sampler
        // In this sample, we are only interested in the image
        struct Texture {
            int32_t imageIndex;
        };


    public:
        ModelGltf();
        virtual ~ModelGltf();

        VkDescriptorSetLayout PrepareDescriptorSetLayout(kRHIDevice& rhidevice);

        void Load(kRHIDevice& rhidevice, VkDescriptorSetLayout layout);
        void Unload(kRHIDevice& rhidevice);

        void UpdateUniformBuffer(kRHIDevice& rhidevice, uint32_t currentImage);
        void BuildCommandBuffer(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout);

    protected:
        void SetupDescriptorSets(kRHIDevice& rhidevice);

        void loadImages(kRHIDevice& rhidevice, tinygltf::Model& input);
        void loadTextures(kRHIDevice& rhidevice, tinygltf::Model& input);
        void loadMaterials(kRHIDevice& rhidevice, tinygltf::Model& input);
        void loadNode(kRHIDevice& rhidevice, const tinygltf::Node& inputNode, const tinygltf::Model& input, Node* parent, std::vector<uint32_t>& indexBuffer, std::vector<Vertex>& vertexBuffer);

        VkResult createBuffer(VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize size, VkBuffer* buffer, VkDeviceMemory* memory, void* data);

    protected:

        //Model data
        std::vector<Image> images;
        std::vector<Texture> textures;
        std::vector<Material> materials;
        std::vector<Node*> nodes;

        // RHI resources
        kRHIBuffer              m_VertexBuffer;
        kRHIBuffer              m_IndexBuffer;
        uint32_t                m_IndexCount;

        kRHIBuffer              m_UniformBuffer;
        kRHITexture2D           m_Texture;

        VkDescriptorSetLayout	m_DescriptorSetLayout;
        VkDescriptorSet	        m_DescriptorSet;
    };


}

