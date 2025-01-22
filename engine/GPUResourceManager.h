/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

#ifndef PIPELINE_GPURESOURCEMANAGER_H_GUARD
#define PIPELINE_GPURESOURCEMANAGER_H_GUARD

#include "Common.h"

namespace pipeline {
    
    class kBufferInfo;
    class kImageInfo;

    class kShader;
    class kBufferGPUResource;
    class kImageTextureGPUResource;

    class kGPUResourceManipulator
    {
    public:
        kGPUResourceManipulator(void);
        virtual ~kGPUResourceManipulator(void);
        
        kBufferGPUResource* GiveResource(kBufferInfo*);
        kImageTextureGPUResource* GiveResource(kImageInfo*);
    };
}

#endif
