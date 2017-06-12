/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/bob/master/LICENSE
*/

#ifndef PIPELINE_VECTOR4_H_GUARD
#define PIPELINE_VECTOR4_H_GUARD

namespace pipeline{
    
    class Vector4f
    {
    public:
        float x,y,z,w;
        
        Vector4f():x(0.0f), y(0.0f), z(0.0f), w(1.0f){};
    };
}

#endif
