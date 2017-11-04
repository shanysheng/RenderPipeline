/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

#ifndef PIPELINE_SHAPE_H_GUARD
#define PIPELINE_SHAPE_H_GUARD

#include "Common.h"
#include "Color.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"
#include "Bound.h"

namespace pipeline {
    
    class Material;
    
    class Shape
    {
    public:
        
        bool isVisible ;
        
        bool isPartOfStaticBatch ;
        int staticBatchIndex ;

        int lightmapIndex ;
        Vector4f lightmapScaleOffset ;
       
        Material* material ;
        bool receiveShadows ;


        int sortingGroupID ;
        int sortingLayerID ;
        std::string sortingLayerName;
        
        Bound bounds ;
        
        Matrix4x4f localToWorldMatrix ;
        Matrix4x4f worldToLocalMatrix;
        
       
        void RenderNow (int material);
    };
}

#endif
