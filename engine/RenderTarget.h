/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

#ifndef PIPELINE_RENDERTARGET_H_GUARD
#define PIPELINE_RENDERTARGET_H_GUARD

#include "Common.h"

namespace pipeline {
    
    class CWinInfo
    {
    public:
        
    };
    
    class kRenderTarget
    {
    public:
        kRenderTarget(){}
        virtual ~kRenderTarget(){}
        
        virtual int		GetType() = 0;
        
        virtual void	BindRenderTarget() = 0;
        virtual void	UnBindRenderTarget() = 0;
        
        virtual int		SetOutputDepthTexture(uint32_t){ return false; }
        virtual int		SetOutputColorTextureCount(uint32_t Count ) {return false;}
        
        virtual uint32_t GetRenderTargetTextureId() const {return 0;}
        virtual uint32_t GetDepthTargetTextureId() const {return 0;}
        
        virtual int		CreateRenderTarget(uint32_t in_Width, uint32_t in_Height) {return false;}
        virtual int     ResizeRenderTarget(uint32_t in_Width, uint32_t in_Height) {return false;}
        
        virtual int		CreateRenderWindow( const CWinInfo& WinInfo) {return false;}
    };
}

#endif
