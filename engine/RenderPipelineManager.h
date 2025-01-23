#ifndef PIPELINE_RENDERPIPELINEMANAGER_H_GUARD
#define PIPELINE_RENDERPIPELINEMANAGER_H_GUARD


#include "Common.h"
#include "IRenderPipeline.h"
#include "RenderModuleManager.h"

namespace pipeline{
    
    class kRenderPipelineManager
    {
    public:
        kRenderPipelineManager();
        virtual ~kRenderPipelineManager();
        
        IRenderPipeline*		Give( const std::string& Name, const std::string& PrototypeName);
        IRenderPipeline*		operator [] (const std::string& Name);
        
        kRenderModuleManager&	GetRenderModuleManager();
        
        void	SetRenderingEngine( kRenderingEngine * pRE ){ m_pRenderingEngine = pRE; }
        void	Register(const std::string& PrototypeName, IRenderPipeline * pPrototype);
        
        void	ClearPrototypes();
        void	ClearRenderPipeline();
        
    protected:
        kRenderingEngine*   	m_pRenderingEngine;
        kRenderModuleManager	m_RenderModuleMgr;
        
        std::unordered_map< std::string, IRenderPipeline *> 	m_Prototypes;
        std::unordered_map< std::string, IRenderPipeline *> 	m_RenderPipelines;
    };
}

#endif
