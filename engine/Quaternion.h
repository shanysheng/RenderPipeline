/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/bob/master/LICENSE
*/

#ifndef PIPELINE_QUATERNION_H_GUARD
#define PIPELINE_QUATERNION_H_GUARD

namespace pipeline{
    
    class Quaternionf
    {
    public:
        float x,y,z,w;
        
    public:
        Quaternionf():x(0.0f), y(0.0f), z(0.0f), w(1.0f){};
    };
}

#endif
