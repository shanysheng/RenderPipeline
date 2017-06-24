/*
 * Copyright 2017 sheng chongshan. All rights reserved.
 * email: shany.sheng@qq.com
 * License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
 */


#ifndef PIPELINE_IRENDERPIPELINE_H_GUARD
#define PIPELINE_IRENDERPIPELINE_H_GUARD


#include "IRenderControlUnit.h"
#include "RenderQueue.h"


namespace pipeline{
    
    class IRenderTarget;
    class CCamera;
    class CRenderQueue;
    class CRenderQueueManager;
    class CPreRenderManager;
    class CRenderPipelineManager;
    class SceneManager;
    
    class IRenderPipeline: public IRenderControlUnit
    {
    public:
        IRenderPipeline();
        virtual ~IRenderPipeline();
        
        virtual IRenderPipeline * Clone() const = 0;
        
        //	virtual void PerFrame( CFrameInfo * pFI);
        //	virtual void BeforeFirstFrame( CFrameInfo * pFI);
        // 	virtual void AfterLastFrame( CFrameInfo * pFI);
        // 	virtual void PostChildrenPerFrame(CFrameInfo * pFI);
        // 	virtual void PostChildrenBeforeFirstFrame( CFrameInfo * pFI);
        // 	virtual void PostChildrenAfterLastFrame( CFrameInfo * pFI);
        
        virtual void PerFrame( CFrameInfo * pFI);
        virtual void DrawAllRenderQueues( CFrameInfo * pFI);
        virtual void DrawRenderQueue ( CFrameInfo * pFI, int32_t QueueIndex);
        virtual void DrawElement(CFrameInfo*, SGNode*);
        
        void SetInCamera( CCamera* pCamera);
        void SetInRenderTarget( int i, IRenderTarget * pRT);
        void SetInRenderQueue( int i, CRenderQueue * pRenderQueue);
        void SetOutRenderTarget ( IRenderTarget * pRenderTarget);
        void SetOutRenderQueue( int i, CRenderQueue* pRenderQueue);
        
        void SetContext( CRenderingEngine * pRE);
        void SetContext( IRenderPipeline* pRight);
        
        void SetSceneManager(SceneManager*);
        void SetRenderQueueManager(CRenderQueueManager*);
        void SetPreRenderManager(CPreRenderManager*);
        void SetRenderPipelineManager(CRenderPipelineManager*);
        
        uint32_t  GetInRenderTargetCount() const;
        uint32_t  GetInRenderQueueCount() const;
        uint32_t  GetOutRenderQueueCount() const;
    protected:
        
        virtual void  _DoPerFrame( CFrameInfo * pFI);
        
    protected:
        SceneManager*               m_pSceneModelMpr;
        CRenderQueueManager*        m_pRenderQueueMgr;
        CPreRenderManager*          m_pPreRenderMgr;
        CRenderPipelineManager*     m_pRenderPipelineMgr;
        
        CCamera*                    m_pInCamera;
        IRenderTarget*              m_pOutRenderTarget;
        
        std::vector<CRenderQueue*>  m_InRenderQueues;
        std::vector<CRenderQueue*>  m_OutRenderQueues;
    };
    
    
    inline uint32_t  IRenderPipeline::GetInRenderQueueCount() const
    {
        return  (uint32_t)m_InRenderQueues.size();
    }
    
    inline uint32_t  IRenderPipeline::GetOutRenderQueueCount() const
    {
        return  (uint32_t)m_OutRenderQueues.size();
    }
}

#endif
