/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

#ifndef PIPELINE_IFEATURE_H_GUARD
#define PIPELINE_IFEATURE_H_GUARD

#include "Common.h"

namespace pipeline {

    class IFeature
    {
    public:
        virtual ~IFeature(){}
        int32_t FeatureType(){return -1;}
    };
}

#endif
