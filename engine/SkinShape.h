/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

#ifndef PIPELINE_SKINSHAPE_H_GUARD
#define PIPELINE_SKINSHAPE_H_GUARD

namespace pipeline {
    class SkinShape{
    public:
        //
        // Properties
        //
        Transform actualRootBone ;
        
        Transform[] bones ;
        
        Bounds localBounds ;
        
        SkinQuality quality ;
        
        Transform rootBone ;
        
        Mesh sharedMesh ;
        bool skinnedMotionVectors ;
        bool updateWhenOffscreen ;

        void BakeMesh (Mesh mesh);
        
        float GetBlendShapeWeight (int index);
        void SetBlendShapeWeight (int index, float value);
    };
}

#endif
