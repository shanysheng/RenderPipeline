/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

#ifndef PIPELINE_LIGHT_H_GUARD
#define PIPELINE_LIGHT_H_GUARD


#include "Common.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4x4.h"
#include "Color.h"
#include "Rect.h"
#include "Ray.h"

namespace pipeline {
    
    enum LightType
    {
        LightType_Point,
        LightType_Spot,
        LightType_Directional
    };
    
    enum LightRenderMode
    {
        RenderMode_PerVertex,
        RenderMode_PerPixel,
    };
    
    enum LightShadows
    {
        None_Shadow,
        Soft_Shadow,
        Hard_Shadow,
    };
    
    class kLight
    {
    public:
        kLight();
        virtual ~kLight();

    public:

        LightType type;

        kColor m_Color ;
        float m_Intensity ;
        float m_Range ;
        float m_SpotAngle ;
        
        LightRenderMode renderMode;
        int m_CullingMask ;

        LightShadows shadows ;
        float m_ShadowBias;
        float m_ShadowNearPlane;
        float m_ShadowNormalBias ;
        float m_ShadowStrength;
    };
}
#endif
