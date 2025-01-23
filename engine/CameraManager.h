#ifndef PIPELINE_CAMERAMANAGER_H_GUARD
#define PIPELINE_CAMERAMANAGER_H_GUARD

#include "Common.h"
#include "Camera.h"

namespace pipeline{
    
    class kCamera;
    class kCameraManager
    {
    public:
        kCameraManager();
        virtual ~kCameraManager();
        
        kCamera* Give( const std::string& name );
        kCamera* operator [](const std::string& name );
        
        void	Clear();
        
    protected:
        kCamera m_Current;
        kCamera m_Main;
        
        std::map<std::string, kCamera*> m_Cameras;
    };
}

#endif
