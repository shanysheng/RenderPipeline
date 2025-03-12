#ifndef PIPELINE_SHAPE_H_GUARD
#define PIPELINE_SHAPE_H_GUARD

#include "Common.h"
#include "Color.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"
#include "Bound.h"

namespace pipeline {

    class kRHIDevice;
    //
    //// The vertex layout for the samples' model
    //struct Vertex {
    //    glm::vec3 pos;
    //    glm::vec3 normal;
    //    glm::vec2 uv;
    //    glm::vec3 color;
    //};

    //// A primitive contains the data for a single draw call
    //struct Primitive {
    //    uint32_t firstIndex;
    //    uint32_t indexCount;
    //    int32_t materialIndex;
    //};

    //// Contains the node's (optional) geometry and can be made up of an arbitrary number of primitives
    //struct Mesh {
    //    std::vector<Primitive> primitives;
    //};

    //// A node represents an object in the glTF scene graph
    //struct Node {
    //    Node* parent;
    //    std::vector<Node*> children;
    //    Mesh mesh;
    //    glm::mat4 matrix;
    //    ~Node() {
    //        for (auto& child : children) {
    //            delete child;
    //        }
    //    }
    //};

    //// A glTF material stores information in e.g. the texture that is attached to it and colors
    //struct Material {
    //    glm::vec4 baseColorFactor = glm::vec4(1.0f);
    //    uint32_t baseColorTextureIndex;
    //};

    //// Contains the texture for a single glTF image
    //// Images may be reused by texture objects and are as such separated
    //struct Image {
    //    kRHITexture2D texture;
    //    // We also store (and create) a descriptor set that's used to access this texture from the fragment shader
    //    VkDescriptorSet descriptorSet;
    //};

    //// A glTF texture stores a reference to the image and a sampler
    //// In this sample, we are only interested in the image
    //struct Texture {
    //    int32_t imageIndex;
    //};

    class kCamera;

    class kMeshBase {
    public:
        virtual ~kMeshBase() {};

        virtual void Load(kRHIDevice& rhidevicet) = 0;
        virtual void Unload(kRHIDevice& rhidevice) = 0;

        virtual void BuildComputeCommandBuffer(VkCommandBuffer commandBuffer, kCamera& camera) = 0;
        virtual void UpdateUniformBuffer(kRHIDevice& rhidevice, kCamera& camera) = 0;
        virtual void BuildGraphicCommandBuffer(VkCommandBuffer commandBuffer, kCamera& camera) = 0;

        virtual glm::vec3 GetBBoxCenter() = 0;
        virtual glm::vec3 GetBBoxSize() = 0;
    };
}

#endif
