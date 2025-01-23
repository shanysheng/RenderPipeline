#ifndef PIPELINE_TEXTURE_H_GUARD
#define PIPELINE_TEXTURE_H_GUARD

#include "IGPUResource.h"

namespace pipeline {
    

    class ITexture : public IGPUResource
    {
    public:
        ITexture();
        ITexture(int32_t id);
        virtual ~ITexture();
        
        virtual void Bind() const ;
        virtual void Unbind() const ;
        
        int32_t GetTextureID();
        void   SetTextureID(int32_t id);
        
    protected:
        int32_t m_TextureID;
    };
        
    inline int32_t ITexture::GetTextureID()
    {
        return m_TextureID;
    }
    
    inline void   ITexture::SetTextureID(int32_t id)
    {
        m_TextureID = id;
    }
}

#endif
