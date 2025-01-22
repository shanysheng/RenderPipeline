/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

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
    
    class kMaterial;

    class kGPUChunkInfo
    {
    public:
        kGPUChunkInfo();

    public:

    };
    
    class kMesh
    {
    public:
        kGPUChunkInfo& GetColorGPUChunkInfo();
        kGPUChunkInfo& GetNormalGPUChunkInfo();
        kGPUChunkInfo& GetCoordGPUChunkInfo();
        std::vector<kGPUChunkInfo>& GetTexCoodrsGPUChunkInfo();

        void RenderNow(int material);

    protected:

        kMaterial* material ;
        bool receiveShadows ;
        
        kBound bounds ;
        
        kMatrix4x4f localToWorldMatrix ;
        kMatrix4x4f worldToLocalMatrix;
        
        kGPUChunkInfo		m_Color;
        kGPUChunkInfo		m_Normal;
        kGPUChunkInfo		m_Coord;

        std::vector<kGPUChunkInfo>	m_TexCoords;
       
        int32_t         m_Stride;
        int32_t         m_VertexBufferID;
        uint32_t        m_VertexCount;

        int32_t         m_IndexComponentType;
        int32_t         m_IndexBufferID;
        uint32_t        m_IndexCount;
    };
}

#endif
