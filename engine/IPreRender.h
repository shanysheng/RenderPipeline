#ifndef PIPELINE_IPRERENDER_H_GUARD
#define PIPELINE_IPRERENDER_H_GUARD

#include "Common.h"
#include "SGNode.h"
#include "IRenderControlUnit.h"


namespace pipeline{
    
    class CCamera;
    class kRenderQueue;
    class IRenderTarget;
    class SceneManager;
    class kRenderQueueManager;
    class kPreRenderManager;
    class kRenderingEngine;
    
    //------------------------------------------------------------------------------
    //	Desc:		A CPreRenderManager manages one or multiple pre-renders. Every
    //				pre-render has the same interface of IPreRender. Pre-renders 
    //				provide pre rendering, which is,
    //				1.modifying scene model, i.e., updating scene graph/spatial 
    //				  index nodes or features, adding new attributes to some 
    //				  nodes or features.
    //				2.generating new render queues, in which there are 
    //				  to-be-rendered entities. 
    //				3.performing a certain computation, and the results can be 
    //				  accessed by other parts inside the render engine.
    //
    //------------------------------------------------------------------------------
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
        void SetInTraverseRoot( const std::vector<kSGNode*>& roots);
        void SetInCamera( CCamera* pCamera);
        void SetInRenderTarget( IRenderTarget * pRT);
        void SetInRenderQueue( int i, kRenderQueue * pRenderQueue);
        void SetOutRenderQueue( int i, kRenderQueue * pRenderQueue);
        
        void SetContext( kRenderingEngine * pRE);
        
        void SetSceneManager(SceneManager*);
        void SetRenderQueueManager(kRenderQueueManager*);
        void SetPreRenderManager(kPreRenderManager*);
        
        uint32_t  GetInRenderQueueCount() const;
        uint32_t  GetOutRenderQueueCount() const;
        
        
    protected:
        
        CCamera*                    m_pInCamera;
        IRenderTarget *             m_pInRenderTarget;
        
        SceneManager *              m_pSceneModelMpr;
        kRenderQueueManager *       m_pRenderQueueMgr;
        kPreRenderManager *         m_pPreRenderMgr;
        
        std::vector<kRenderQueue*>  m_InRenderQueues;
        std::vector<kRenderQueue*>  m_OutRenderQueues;
        std::vector<kSGNode*>        m_TraverseRoots;
    };
}

#endif
