#ifndef PIPELINE_GPURESOURCEMANAGER_H_GUARD
#define PIPELINE_GPURESOURCEMANAGER_H_GUARD

#include "Common.h"

namespace pipeline {
    
    class kBufferInfo;
    class kImageInfo;

    class kShader;
    class kBufferGPUResource;
    class kImageTextureGPUResource;

    class kGPUResourceManager
    {
    public:
        kGPUResourceManager(void);
        virtual ~kGPUResourceManager(void);
        
        kBufferGPUResource* GiveResource(kBufferInfo*);
        kImageTextureGPUResource* GiveResource(kImageInfo*);
    };
}

#endif
