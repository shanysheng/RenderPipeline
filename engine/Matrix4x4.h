/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/bob/master/LICENSE
*/

#ifndef PIPELINE_MATRIX4X4_H_GUARD
#define PIPELINE_MATRIX4X4_H_GUARD

namespace pipeline{
    
    // Matrix elements are accessed with m[row][column].
    class Matrix4x4f
    {
    public:
        float m[4][4];
    };
}

#endif
