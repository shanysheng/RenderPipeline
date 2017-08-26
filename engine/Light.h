/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

#ifndef PIPELINE_LIGHT_H_GUARD
#define PIPELINE_LIGHT_H_GUARD

namespace pipeline {
    
    class Light
    {
    public:
        // Fields
        //
        private int m_BakedIndex;
     
        
        
        //
        // Properties
        //
        bool alreadyLightmapped ;
        
        Vector2 areaSize;
        
        
        
        float bounceIntensity;
        
        Color color ;
        
        float colorTemperature;
        int commandBufferCount;
        Texture cookie ;
        
        float cookieSize ;
        
        int cullingMask ;
        
        Flare flare;
        float intensity ;
        
        bool isBaked ;
        
        LightmapBakeType lightmapBakeType;
        
        
        float range ;
        
        LightRenderMode renderMode;
        
        
        float shadowBias;
        
        int shadowCustomResolution ;
        
        float shadowNearPlane;
        float shadowNormalBias ;
        
        LightShadowResolution shadowResolution ;
        
        LightShadows shadows ;
        
        float shadowStrength;
        
        float spotAngle ;
        
        LightType type;
    };
}
#endif
