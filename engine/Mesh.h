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
