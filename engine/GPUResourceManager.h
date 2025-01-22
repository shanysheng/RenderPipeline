/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

#ifndef PIPELINE_GPURESOURCEMANAGER_H_GUARD
#define PIPELINE_GPURESOURCEMANAGER_H_GUARD

#include "Common.h"

namespace pipeline {
    
    
    class GeometryBuffer;
    class kShader;
    class kTexture;

    
    class kGPUResourceManipulator
    {
    public:
        kGPUResourceManipulator(void);
        virtual ~kGPUResourceManipulator(void);
        
    };
}

#endif
