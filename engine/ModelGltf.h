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

#include "Mesh.h"


namespace tinygltf {
    class Node;
    class Model;
}



namespace pipeline {


    class ModelGltf : public IModel
    {
    public:
        ModelGltf();
        virtual ~ModelGltf();

        VkVertexInputBindingDescription getBindingDescription();
        std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();

        std::vector<VkDescriptorSetLayout> PrepareDescriptorSetLayout(kRHIDevice& rhidevice);
        std::vector<VkPushConstantRange> PreparePushConstantRange(kRHIDevice& rhidevice);

        void Load(kRHIDevice& rhidevice);
        void Unload(kRHIDevice& rhidevice);

        void UpdateUniformBuffer(kRHIDevice& rhidevice, uint32_t currentImage);
        void BuildCommandBuffer(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, kCamera& camera);

    protected:
        void SetupDescriptorSets(kRHIDevice& rhidevice);
        void SetupMatrixDescriptorSets(kRHIDevice& rhidevice);
        void SetupMaterialDescriptorSets(kRHIDevice& rhidevice);


    protected:
        // The vertex layout for the samples' model
        struct Vertex {
            glm::vec3 pos;
            glm::vec3 normal;
            glm::vec2 uv;
            glm::vec3 color;

        };

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

        struct ModelGltfShaderData {
            glm::mat4 projection;
            glm::mat4 view;
            glm::vec4 lightPos = glm::vec4(5.0f, 5.0f, -5.0f, 1.0f);
            glm::vec4 viewPos;
        };


        void loadImages(kRHIDevice& rhidevice, tinygltf::Model& input);
        void loadTextures(kRHIDevice& rhidevice, tinygltf::Model& input);
        void loadMaterials(kRHIDevice& rhidevice, tinygltf::Model& input);
        void loadNode(kRHIDevice& rhidevice, const tinygltf::Node& inputNode, const tinygltf::Model& input, Node* parent, std::vector<uint32_t>& indexBuffer, std::vector<Vertex>& vertexBuffer);

        void drawNode(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, Node* node);
        void draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout);
    protected:

        //Model data
        std::vector<Image> images;
        std::vector<Texture> textures;
        std::vector<Material> materials;
        std::vector<Node*> nodes;

        //// Single vertex buffer for all primitives
        //struct {
        //    VkBuffer buffer;
        //    VkDeviceMemory memory;
        //} vertices;

        //// Single index buffer for all primitives
        //struct {
        //    int count;
        //    VkBuffer buffer;
        //    VkDeviceMemory memory;
        //} indices;

        // vertex and index buffer;
        size_t                          m_IndexCount;
        std::shared_ptr<kRHIBuffer>     m_IndexBuffer;
        std::shared_ptr<kRHIBuffer>     m_VertexBuffer;
        std::shared_ptr<kRHIBuffer>     m_MatrixBuffer;

        // ds layout
        VkDescriptorSetLayout	m_MatrixDSLayout;
        VkDescriptorSetLayout	m_SamplerDSLayout;

        // model matrix
        glm::mat4               m_ModelMat;
        VkDescriptorSet	        m_MatrixDSet;

    };

}

