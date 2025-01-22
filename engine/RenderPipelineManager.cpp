#include "RenderPipelineManager.h"


namespace pipeline{
    
    kRenderPipelineManager::kRenderPipelineManager():m_pRenderingEngine(NULL)
    {
    }
    
    kRenderPipelineManager::~kRenderPipelineManager()
    {
        ClearRenderPipeline();
        ClearPrototypes();
    }
    
    IRenderPipeline*kRenderPipelineManager::Give( const std::string& Name, const std::string& PrototypeName )
    {
        std::unordered_map< std::string, IRenderPipeline *>::iterator pos;
        pos = m_RenderPipelines.find(Name);
        if (pos!=m_RenderPipelines.end())
        {
            return pos->second;
        }
        
        pos = m_Prototypes.find(PrototypeName);
        if (pos!=m_Prototypes.end())
        {
            IRenderPipeline* pRenderPipeline = pos->second->Clone();
            pRenderPipeline->SetContext(this->m_pRenderingEngine);
            m_RenderPipelines.insert(std::make_pair(Name, pRenderPipeline));
            return pRenderPipeline;
        }
        
        return NULL;
    }
    
    void kRenderPipelineManager::Register(const std::string& PrototypeName, IRenderPipeline * pPrototype )
    {
        std::unordered_map< std::string, IRenderPipeline *>::iterator pos;
        pos = m_Prototypes.find(PrototypeName);
        if (pos!=m_Prototypes.end())
        {
            if (pos->second)
                delete pos->second;
            
            pos->second = pPrototype;
            return ;
        }
        
        m_Prototypes.insert(std::make_pair(PrototypeName, pPrototype));
    }
    
    IRenderPipeline * kRenderPipelineManager::operator [](const std::string& Name)
    {
        std::unordered_map< std::string, IRenderPipeline *>::iterator pos;
        pos = m_RenderPipelines.find(Name);
        if(pos == m_RenderPipelines.end())
            return NULL;
        
        return pos->second;
        
    }
    
    void kRenderPipelineManager::ClearPrototypes()
    {
        std::unordered_map< std::string, IRenderPipeline *>::iterator pos;
        pos = m_Prototypes.begin();
        while (pos!=m_Prototypes.end())
        {
            if (pos->second)
                delete pos->second;
            
            ++pos;
        }
        
        m_Prototypes.clear();
    }
    
    void kRenderPipelineManager::ClearRenderPipeline()
    {
        std::unordered_map< std::string, IRenderPipeline *>::iterator pos;
        pos = m_RenderPipelines.begin();
        while (pos!=m_RenderPipelines.end())
        {
            if (pos->second)
                delete pos->second;
            
            ++pos;
        }
        
        m_RenderPipelines.clear();
    }
    
    
    kRenderModuleManager& kRenderPipelineManager::GetRenderModuleManager()
    {
        return m_RenderModuleMgr;
    }
}
