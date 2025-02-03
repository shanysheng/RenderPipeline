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
    
    //class kMaterial;

    //class kGPUChunkInfo
    //{
    //public:
    //    kGPUChunkInfo();

    //public:

    //};
    //
    //class kMesh
    //{
    //public:
    //    kMesh();
    //    virtual ~kMesh();

    //    kGPUChunkInfo& GetColorGPUChunkInfo();
    //    kGPUChunkInfo& GetNormalGPUChunkInfo();
    //    kGPUChunkInfo& GetCoordGPUChunkInfo();
    //    std::vector<kGPUChunkInfo>& GetTexCoodrsGPUChunkInfo();

    //    void RenderNow(int material);

    //protected:

    //    kMaterial* material ;
    //    bool receiveShadows ;
    //    
    //    kBound bounds ;
    //    
    //    kMatrix4x4f localToWorldMatrix ;
    //    kMatrix4x4f worldToLocalMatrix;
    //    
    //    kGPUChunkInfo		m_Color;
    //    kGPUChunkInfo		m_Normal;
    //    kGPUChunkInfo		m_Coord;

    //    std::vector<kGPUChunkInfo>	m_TexCoords;
    //   
    //    int32_t         m_Stride;
    //    int32_t         m_VertexBufferID;
    //    uint32_t        m_VertexCount;

    //    int32_t         m_IndexComponentType;
    //    int32_t         m_IndexBufferID;
    //    uint32_t        m_IndexCount;
    //};

    class kCamera;

    class IModel {
    public:
        virtual ~IModel() {};

        virtual VkVertexInputBindingDescription getBindingDescription() = 0;
        virtual std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions() = 0;

        virtual std::vector<VkDescriptorSetLayout> PrepareDescriptorSetLayout(kRHIDevice& rhidevice) = 0;
        virtual std::vector<VkPushConstantRange> PreparePushConstantRange(kRHIDevice& rhidevice) = 0;

        virtual void Load(kRHIDevice& rhidevicet) = 0;
        virtual void Unload(kRHIDevice& rhidevice) = 0;

        virtual void UpdateUniformBuffer(kRHIDevice& rhidevice, uint32_t currentImage) = 0;
        virtual void BuildCommandBuffer(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, kCamera& camera) = 0;
    };
}

#endif
