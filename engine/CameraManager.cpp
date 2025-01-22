#include "CameraManager.h"

namespace pipeline{
    
    kCameraManager::kCameraManager()
    {
        
    }
    
    kCameraManager::~kCameraManager()
    {
        Clear();
    }
    
    kCamera* kCameraManager::Give( const std::string& CameraName )
    {
        std::map<std::string, kCamera*>::iterator pos ;
        pos = m_Cameras.find(CameraName);
        if (pos==m_Cameras.end())
        {
            kCamera* pCamera = new kCamera();
            m_Cameras.insert(std::make_pair(CameraName, pCamera));
            return pCamera;
        }
        
        return pos->second;
    }
    
    kCamera* kCameraManager::operator [](const std::string& CameraName )
    {
        std::map<std::string, kCamera*>::iterator pos ;
        pos = m_Cameras.find(CameraName);
        if (pos!=m_Cameras.end())
        {
            return pos->second;
        }
        
        return NULL;
        
    }
    
    void kCameraManager::Clear()
    {
        std::map<std::string, kCamera*>::iterator pos ;
        pos = m_Cameras.begin();
        while(pos!=m_Cameras.end())
        {
            delete (pos->second);
            ++pos;
        }
        m_Cameras.clear();
    }
}
