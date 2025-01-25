#ifndef PIPELINE_RENDERPIPELINEMANAGER_H_GUARD
#define PIPELINE_RENDERPIPELINEMANAGER_H_GUARD


#include "Common.h"
#include "IRenderPipeline.h"
#include "RenderModuleManager.h"

namespace pipeline{
    

    //------------------------------------------------------------------------------
    //	Desc:		Similar to CPreRenderManager, the class CRenderPipelineManager
    //				manages the life periods of a set of render pipelines.
    //
    //				There is only one thing that should be pointed out. The class 
    //				CRenderPipelineManager aggregates one CRenderModuleManager 
    //				instance to provide the capability to manage render modules.
    //
    //				There are two reasons why we place a render module manager 
    //				here. One is that we hope any render module instance can be 
    //				shared among multiple render pipelines. The other is that we 
    //				want to lower the coupling of render modules with other 
    //				components in the rendering engine.
    //
    //------------------------------------------------------------------------------
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
