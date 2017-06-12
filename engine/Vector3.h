/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/bob/master/LICENSE
*/

#ifndef PIPELINE_VECTOR3_H_GUARD
#define PIPELINE_VECTOR3_H_GUARD

namespace pipeline{
    
    class Vector3f
    {
    public:
        float x,y,z;
        
        Vector3f():x(0.0f), y(0.0f), z(1.0f){};
    };
}

#endif
