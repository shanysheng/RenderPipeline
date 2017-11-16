/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/bob/master/LICENSE
*/

#ifndef PIPELINE_BOUND_H_GUARD
#define PIPELINE_BOUND_H_GUARD

#include "Common.h"
#include "Vector3.h"

namespace pipeline{
    
    class Bound
    {
    public:
        Bound();
        Bound(const Vector3f& minpt, const Vector3f& maxpt);

        Vector3f m_Min;
        Vector3f m_Max;
    };
}

#endif
