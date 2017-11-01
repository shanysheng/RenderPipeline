/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

#ifndef PIPELINE_SKINSHAPE_H_GUARD
#define PIPELINE_SKINSHAPE_H_GUARD

#include "Transform.h"
#include "Bound.h"
#include "Geometry.h"

namespace pipeline {
    class SkinShape{
    public:
        //
        // Properties
        //
        Transform actualRootBone ;
        
        Transform* bones ;
        
        Bound localBounds ;
        
        //SkinQuality quality ;
        
        Transform rootBone ;
        
        Geometry* sharedMesh ;
        bool skinnedMotionVectors ;
        bool updateWhenOffscreen ;

        
        float GetBlendShapeWeight (int index);
        void SetBlendShapeWeight (int index, float value);
    };
}

#endif
