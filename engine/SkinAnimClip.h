/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

#ifndef PIPELINE_SKINANIMCLIP_H_GUARD
#define PIPELINE_SKINANIMCLIP_H_GUARD

namespace pipeline {
    
    class SkinAnimClip
    {
    public:
        float length ;
        float startTime ;
        float stopTime;
        float frameRate;

        bool humanMotion ;

        //WrapMode wrapMode ;
    };
}

#endif
