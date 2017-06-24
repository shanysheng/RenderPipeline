/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

#ifndef PIPELINE_TEXTUREGPURESOURCE_H_GUARD
#define PIPELINE_TEXTUREGPURESOURCE_H_GUARD

namespace pipeline {
    

    class TextureGPUResource : public IGPUResource
    {
    public:
        TextureGPUResource();
        TextureGPUResource(int32_t id);
        virtual ~TextureGPUResource();
        
        virtual void Bind() const ;
        virtual void Unbind() const ;
        
        int32_t GetTextureID();
        void   SetTextureID(int32_t id);
        
    protected:
        int32_t m_TextureID;
    };
        
    inline int32_t CImageTextureGPUResource::GetTextureID()
    {
        return m_TextureID;
    }
    
    inline void   CImageTextureGPUResource::SetTextureID(int32_t id)
    {
        m_TextureID = id;
    }
    
}

#endif
