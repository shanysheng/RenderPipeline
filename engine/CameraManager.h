/*
 * Copyright 2017 sheng chongshan. All rights reserved.
 * email: shany.sheng@qq.com
 * License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
 */


#ifndef PIPELINE_CAMERAMANAGER_H_GUARD
#define PIPELINE_CAMERAMANAGER_H_GUARD

#include "Common.h"
#include "Camera.h"

namespace pipeline{
    
    class Camera;
    class CameraManager
    {
    public:
        CameraManager();
        virtual ~CameraManager();
        
        Camera * Give( const std::string& name );
        Camera * operator [](const std::string& name );
        
        void	Clear();
        
    protected:
        Camera m_Current;
        Camera m_Main;
        
        std::map<std::string, Camera*> m_Cameras;
    };
}

#endif
