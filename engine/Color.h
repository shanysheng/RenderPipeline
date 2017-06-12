/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/bob/master/LICENSE
*/

#ifndef PIPELINE_COLOR_H_GUARD
#define PIPELINE_COLOR_H_GUARD

namespace pipeline{
    
    class Color
    {
    public:
        float r,g,b,a;

    public:
        Color():r(1.0f),g(1.0f),b(1.0f),a(1.0f){}
    };
}

#endif
