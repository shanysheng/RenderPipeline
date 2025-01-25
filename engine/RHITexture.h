#ifndef PIPELINE_TEXTURE_H_GUARD
#define PIPELINE_TEXTURE_H_GUARD

#include "IGPUResource.h"

namespace pipeline {
    

    class kRHITexture : public IGPUResource
    {
    public:
        kRHITexture();
        kRHITexture(int32_t id);
        virtual ~kRHITexture();
        
        virtual void Bind() const ;
        virtual void Unbind() const ;
        
        int32_t GetTextureID() { return m_TextureID; }
        void   SetTextureID(int32_t id) { m_TextureID = id; }
        
    protected:
        int32_t m_TextureID;
    };

}

#endif
