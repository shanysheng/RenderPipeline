/*
 * Copyright 2017 sheng chongshan. All rights reserved.
 * email: shany.sheng@qq.com
 * License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
 */

#ifndef PIPELINE_BUFFERGPURESROUCE_H_GUARD
#define PIPELINE_BUFFERGPURESROUCE_H_GUARD

namespace pipeline {
    
    class CGPUChunkInfo
    {
    public:
        CGPUChunkInfo();
        
    public:
        
    };
    
    class CBufferGPUResource :public IGPUResource
    {
    public:
        CBufferGPUResource();
        CBufferGPUResource(int32_t indexbufferid, int32_t vertexbufferid);
        
        virtual ~CBufferGPUResource();
        
        virtual void Bind()const;
        virtual void Unbind()const;
        
        void SetVertexBufferID(int32_t p_VertexBufferID);
        void SetVertexBufferStride(int32_t stride);
        void SetVertexCount(uint32_t vertexCount);
        int32_t GetVertexBufferID() { return m_VertexBufferID ; };
        int32_t GetVertexBufferStride(){return m_Stride;};
        uint32_t GetVertexCount(){return m_VertexCount;}
        
        void SetIndexBufferID(int32_t p_IndexBufferID);
        void SetIndexBufferComponentType(int32_t type);
        void SetIndexCount(int32_t count);
        int32_t GetIndexBufferID() { return m_IndexBufferID; };
        int32_t GetIndexBufferComponentType(){return m_IndexComponentType;};
        int32_t GetIndexCount();
        
        CGPUChunkInfo& GetColorGPUChunkInfo();
        CGPUChunkInfo& GetNormalGPUChunkInfo();
        CGPUChunkInfo& GetCoordGPUChunkInfo();
        std::vector<CGPUChunkInfo>& GetTexCoodrsGPUChunkInfo();
        
    protected:
        
        CGPUChunkInfo		m_Color;
        CGPUChunkInfo		m_Normal;
        CGPUChunkInfo		m_Coord;
        
        std::vector<CGPUChunkInfo>	m_TexCoords;
        
        int32_t				m_Stride;
        int32_t				m_VertexBufferID;
        uint32_t              m_VertexCount;
        
        int32_t         m_IndexComponentType;
        int32_t         m_IndexBufferID;
        uint32_t        m_IndexCount;
    };
    
    inline void CBufferGPUResource::SetVertexBufferID(int32_t p_VertexBufferID)
    {
        m_VertexBufferID = p_VertexBufferID;
    }
    
    inline void CBufferGPUResource::SetIndexBufferID(int32_t p_IndexBufferID)
    {
        m_IndexBufferID = p_IndexBufferID;
    }
    
    inline void CBufferGPUResource::SetVertexCount(uint32_t vertexCount)
    {
        m_VertexCount   = vertexCount;
    }
    
    inline void CBufferGPUResource::SetIndexBufferComponentType(int32_t type)
    {
        m_IndexComponentType = type;
    }
    
    inline void CBufferGPUResource::SetVertexBufferStride(int32_t stride)
    {
        m_Stride = stride;
    }
    
    inline void CBufferGPUResource::SetIndexCount(int32_t count)
    {
        m_IndexCount = count ;
    }
    
    inline int32_t CBufferGPUResource::GetIndexCount()
    {
        return m_IndexCount;
    }
}
#endif
