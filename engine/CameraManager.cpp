#include "CameraManager.h"

namespace pipeline{
    
    CameraManager::CameraManager()
    {
        
    }
    
    CameraManager::~CameraManager()
    {
        Clear();
    }
    
    Camera* CameraManager::Give( const std::string& CameraName )
    {
        std::map<std::string, Camera*>::iterator pos ;
        pos = m_Cameras.find(CameraName);
        if (pos==m_Cameras.end())
        {
            Camera* pCamera = new Camera();
            m_Cameras.insert(std::make_pair(CameraName, pCamera));
            return pCamera;
        }
        
        return pos->second;
    }
    
    Camera* CameraManager::operator [](const std::string& CameraName )
    {
        std::map<std::string, Camera*>::iterator pos ;
        pos = m_Cameras.find(CameraName);
        if (pos!=m_Cameras.end())
        {
            return pos->second;
        }
        
        return NULL;
        
    }
    
    void CameraManager::Clear()
    {
        std::map<std::string, Camera*>::iterator pos ;
        pos = m_Cameras.begin();
        while(pos!=m_Cameras.end())
        {
            delete (pos->second);
            ++pos;
        }
        m_Cameras.clear();
    }
}
