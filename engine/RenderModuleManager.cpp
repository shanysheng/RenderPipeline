#include "IRenderModule.h"
#include "RenderModuleManager.h"

namespace pipeline{
    
    kRenderModuleManager::kRenderModuleManager()
    {
        
    }
    
    kRenderModuleManager::~kRenderModuleManager()
    {
        ClearRenderModules();
        ClearPrototypes();
    }
    
    IRenderModule* kRenderModuleManager::Give( const std::string& Name, const std::string& PrototypeName )
    {
        std::unordered_map< std::string, IRenderModule *>::iterator pos;
        pos = m_RenderModules.find(Name);
        if (pos!=m_RenderModules.end())
        {
            return pos->second;
        }
        
        pos = m_Prototypes.find(PrototypeName);
        if(pos != m_Prototypes.end())
        {
            IRenderModule* pRenderModule = pos->second->Clone();
            m_RenderModules.insert(std::make_pair(Name, pRenderModule));
            return pRenderModule;
        }
        
        return NULL;
    }
    
    void kRenderModuleManager::Register(const std::string& PrototypeName, IRenderModule * pPrototype )
    {
        std::unordered_map< std::string, IRenderModule *>::iterator pos;
        pos = m_Prototypes.find(PrototypeName);
        if (pos!=m_Prototypes.end())
        {
            if (pos->second)
                delete pos->second;
            
            pos->second = pPrototype;
        }
        
        m_Prototypes.insert(std::make_pair(PrototypeName, pPrototype));
    }
    
    IRenderModule* kRenderModuleManager::operator [](const std::string& Name)
    {
        std::unordered_map< std::string, IRenderModule *>::iterator pos;
        pos = m_RenderModules.find(Name);
        if(pos == m_RenderModules.end())
            return NULL;
        
        return pos->second;
    }
    
    void kRenderModuleManager::ClearPrototypes()
    {
        std::unordered_map< std::string, IRenderModule *>::iterator pos;
        pos = m_Prototypes.begin();
        while (pos!=m_Prototypes.end())
        {
            if (pos->second)
                delete pos->second;
            
            ++pos;
        }
        
        m_Prototypes.clear();
    }
    
    void kRenderModuleManager::ClearRenderModules()
    {
        std::unordered_map< std::string, IRenderModule *>::iterator pos;
        pos = m_RenderModules.begin();
        while (pos!=m_RenderModules.end())
        {
            if (pos->second)
                delete pos->second;
            
            ++pos;
        }
        
        m_RenderModules.clear();
    }
}
