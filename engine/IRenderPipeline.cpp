#include "IRenderPipeline.h"

namespace pipeline{
    
    IRenderPipeline::IRenderPipeline()
    {
        m_pSceneModelMpr = NULL;
        m_pRenderQueueMgr = NULL;
        m_pPreRenderMgr = NULL;
        m_pRenderPipelineMgr = NULL;
        
        m_pInCamera = NULL;
        m_pOutRenderTarget = NULL;
        
    }
    
    IRenderPipeline::~IRenderPipeline()
    {
        m_pSceneModelMpr = NULL;
        m_pRenderQueueMgr = NULL;
        m_pPreRenderMgr = NULL;
        m_pRenderPipelineMgr = NULL;
        
        m_pInCamera = NULL;
        m_pOutRenderTarget = NULL;
        
        m_InRenderQueues.clear();
        m_OutRenderQueues.clear();
    }
    
    void IRenderPipeline::_DoPerFrame( CFrameInfo * pFI )
    {
        IRenderControlUnit::_DoPerFrame(pFI);
    }
    
    void IRenderPipeline::PerFrame( CFrameInfo * pFI )
    {
        DrawAllRenderQueues( pFI);
    }
    
    void IRenderPipeline::DrawAllRenderQueues( CFrameInfo * pFI )
    {
        uint32_t count = m_InRenderQueues.size();
        for(uint32_t i = 0;i<count;++i)
        {
            DrawRenderQueue(pFI,i);
        }
    }
    
    void IRenderPipeline::DrawRenderQueue( CFrameInfo * pFI, int32_t QueueIndex )
    {
        if( QueueIndex < 0 || ((size_t)QueueIndex) >= m_InRenderQueues.size() || m_InRenderQueues[QueueIndex] == NULL )
            return;
    }

    void IRenderPipeline::DrawElement(CFrameInfo*, kSGNode*)
    {

    }
    
    void IRenderPipeline::SetInCamera( CCamera* pCamera )
    {
        m_pInCamera = pCamera;
    }
    
    void IRenderPipeline::SetInRenderTarget( int i, IRenderTarget * pRT )
    {
    }
    
    void IRenderPipeline::SetOutRenderTarget( IRenderTarget * pRenderTarget )
    {
        m_pOutRenderTarget = pRenderTarget;
    }
    
    void IRenderPipeline::SetInRenderQueue( int i, kRenderQueue * pRenderQueue )
    {
 
    }
    
    void IRenderPipeline::SetOutRenderQueue( int i, kRenderQueue* pRenderQueue )
    {

    }
    
    void IRenderPipeline::SetContext( kRenderingEngine * pRE )
    {
        
    }
    
    void IRenderPipeline::SetContext( IRenderPipeline* pRight)
    {
        
    }
    
    void IRenderPipeline::SetSceneManager(SceneManager*pSceneModel)
    {
        m_pSceneModelMpr = pSceneModel;
    }
    
    void IRenderPipeline::SetRenderQueueManager(kRenderQueueManager*pRenderQueueMgr)
    {
        m_pRenderQueueMgr = pRenderQueueMgr;
    }
    
    void IRenderPipeline::SetPreRenderManager(kPreRenderManager* pPreRenderMgr)
    {
        m_pPreRenderMgr = pPreRenderMgr;
    }
}
