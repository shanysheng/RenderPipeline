#ifndef PIPELINE_GPURESOURCEMANAGER_H_GUARD
#define PIPELINE_GPURESOURCEMANAGER_H_GUARD

#include "Common.h"

namespace pipeline {
    
    class kBufferInfo;
    class kImageInfo;

    class kRHIBuffer;
    class kRHITexture2D;

    class kRHIResourceManager
    {
    public:
        kRHIResourceManager(void);
        virtual ~kRHIResourceManager(void);
        
        kRHIBuffer* GiveResource(kBufferInfo*);
        kRHITexture2D* GiveResource(kImageInfo*);
    };
}

#endif
