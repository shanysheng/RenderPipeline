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
    class Shader;
    class Texture;

    
    class CGPUResourceManipulator
    {
    public:
        CGPUResourceManipulator(void);
        virtual ~CGPUResourceManipulator(void);
        
    };
}

#endif
