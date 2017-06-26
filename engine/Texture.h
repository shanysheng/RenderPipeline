/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

#ifndef PIPELINE_TEXTURE_H_GUARD
#define PIPELINE_TEXTURE_H_GUARD

#include "IGPUResource.h"

namespace pipeline {
    

    class Texture : public IGPUResource
    {
    public:
        Texture();
        Texture(int32_t id);
        virtual ~Texture();
        
        virtual void Bind() const ;
        virtual void Unbind() const ;
        
        int32_t GetTextureID();
        void   SetTextureID(int32_t id);
        
    protected:
        int32_t m_TextureID;
    };
        
    inline int32_t Texture::GetTextureID()
    {
        return m_TextureID;
    }
    
    inline void   Texture::SetTextureID(int32_t id)
    {
        m_TextureID = id;
    }
    
}

#endif
