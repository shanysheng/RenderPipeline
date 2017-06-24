#include "PreRenderManager.h"
#include "IPreRender.h"

namespace pipeline
{
    CPreRenderManager::CPreRenderManager()
    {
        
    }
    
    CPreRenderManager::~CPreRenderManager()
    {
        ClearPreRenders();
        ClearPrototypes();
    }
    
    IPreRender * CPreRenderManager::Give( const std::string& PreRenderMame, const std::string& PrototypeName )
    {
        std::unordered_map< std::string, IPreRender *>::iterator pos;
        pos = m_PreRenders.find(PreRenderMame);
        if (pos!=m_PreRenders.end())
        {
            return pos->second;
        }
        
        pos = m_Prototypes.find(PrototypeName);
        if (pos!=m_Prototypes.end())
        {
            IPreRender* pPreRender = pos->second->Clone();
            m_PreRenders[PreRenderMame] = pPreRender;
            return pPreRender;
        }
        
        return NULL;
    }
    
    IPreRender* CPreRenderManager::operator [](const std::string& PreRenderName )
    {
        std::unordered_map< std::string, IPreRender *>::iterator pos;
        pos = m_PreRenders.find(PreRenderName);
        if(pos == m_PreRenders.end())
            return NULL;
        
        return pos->second;
    }
    
    void CPreRenderManager::Register(const std::string& PrototypeName, IPreRender* pPrototype )
    {
        std::unordered_map< std::string, IPreRender *>::iterator pos;
        pos = m_Prototypes.find(PrototypeName);
        if (pos!=m_Prototypes.end())
        {
            if(pos->second != NULL)
                delete pos->second;
            
            pos->second = pPrototype;
            return ;
        }
        
        m_Prototypes[PrototypeName] = pPrototype;
    }
    
    void CPreRenderManager::ClearPreRenders()
    {
        std::unordered_map< std::string, IPreRender *>::iterator pos;
        pos = m_PreRenders.begin();
        while (pos!=m_PreRenders.end())
        {
            if (pos->second)
                delete pos->second;
            
            ++pos;
        }
        
        m_PreRenders.clear();
    }
    
    void CPreRenderManager::ClearPrototypes()
    {
        std::unordered_map< std::string, IPreRender *>::iterator pos ;
        pos = m_Prototypes.begin();
        while (pos!=m_Prototypes.end())
        {
            if (pos->second)
                delete pos->second;
            
            ++pos;
        }
        
        m_Prototypes.clear();
    }
}
