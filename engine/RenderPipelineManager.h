/*
 * Copyright 2017 sheng chongshan. All rights reserved.
 * email: shany.sheng@qq.com
 * License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
 */

#ifndef PIPELINE_RENDERPIPELINEMANAGER_H_GUARD
#define PIPELINE_RENDERPIPELINEMANAGER_H_GUARD


#include "Common.h"
#include "IRenderPipeline.h"
#include "RenderModuleManager.h"

namespace pipeline{
    
    class CRenderPipelineManager
    {
    public:
        CRenderPipelineManager();
        virtual ~CRenderPipelineManager();
        
        IRenderPipeline*		Give( const std::string& Name, const std::string& PrototypeName);
        IRenderPipeline*		operator [] (const std::string& Name);
        
        CRenderModuleManager&	GetRenderModuleManager();
        
        void	SetRenderingEngine( CRenderingEngine * pRE ){ m_pRenderingEngine = pRE; }
        void	Register(const std::string& PrototypeName, IRenderPipeline * pPrototype);
        
        void	ClearPrototypes();
        void	ClearRenderPipeline();
        
    protected:
        CRenderingEngine*   	m_pRenderingEngine;
        CRenderModuleManager	m_RenderModuleMgr;
        
        std::unordered_map< std::string, IRenderPipeline *> 	m_Prototypes;
        std::unordered_map< std::string, IRenderPipeline *> 	m_RenderPipelines;
    };
}

#endif
