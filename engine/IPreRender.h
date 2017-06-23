/*
 * Copyright 2017 sheng chongshan. All rights reserved.
 * email: shany.sheng@qq.com
 * License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
 */


#ifndef PIPELINE_IPRERENDER_H_GUARD
#define PIPELINE_IPRERENDER_H_GUARD

#include "Common.h"
#include "SGNode.h"
#include "IRenderControlUnit.h"


namespace pipeline{
    
    
    class CCamera;
    class CRenderQueue;
    
    class IRenderTarget;
    
    class SceneManager;
    
    class CRenderQueueManager;
    
    class CPreRenderManager;
    
    
    class IPreRender : public IRenderControlUnit
    {
    public:
        IPreRender();
        virtual ~IPreRender();
        
        virtual IPreRender * Clone() const = 0;
        
        // 	virtual void PerFrame( CFrameInfo * pFI);
        
        //	virtual void BeforeFirstFrame( CFrameInfo * pFI);
        
        // 	virtual void AfterLastFrame( CFrameInfo * pFI);
        
        // 	virtual void PostChildrenPerFrame(CFrameInfo * pFI);
        
        // 	virtual void PostChildrenBeforeFirstFrame( CFrameInfo * pFI);
        
        // 	virtual void PostChildrenAfterLastFrame( CFrameInfo * pFI);
    public:
        void SetInTraverseRoot( const std::vector<SGNode*>& roots);
        void SetInCamera( CCamera* pCamera);
        void SetInRenderTarget( IRenderTarget * pRT);
        void SetInRenderQueue( int i, CRenderQueue * pRenderQueue);
        void SetOutRenderQueue( int i, CRenderQueue * pRenderQueue);
        
        void SetContext( CRenderingEngine * pRE);
        
        void SetSceneManager(SceneManager*);
        void SetRenderQueueManager(CRenderQueueManager*);
        void SetPreRenderManager(CPreRenderManager*);
        
        uint32_t  GetInRenderQueueCount() const;
        uint32_t  GetOutRenderQueueCount() const;
        
        
    protected:
        
        CCamera*                    m_pInCamera;
        IRenderTarget *             m_pInRenderTarget;
        
        SceneManager *              m_pSceneModelMpr;
        CRenderQueueManager *       m_pRenderQueueMgr;
        CPreRenderManager *         m_pPreRenderMgr;
        
        std::vector<CRenderQueue*>  m_InRenderQueues;
        std::vector<CRenderQueue*>  m_OutRenderQueues;
        std::vector<SGNode*>        m_TraverseRoots;
    };
}

#endif
