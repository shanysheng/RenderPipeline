#include "IPreRender.h"

namespace pipeline{
    
    IPreRender::IPreRender()
    {
        m_pInCamera = NULL;
        m_pInRenderTarget = NULL;
    }
    
    IPreRender::~IPreRender()
    {
        m_pSceneModelMpr = NULL;
        m_pRenderQueueMgr = NULL;
        m_pPreRenderMgr = NULL;
        
        m_pInCamera = NULL;
        m_pInRenderTarget = NULL;
        
        m_InRenderQueues.clear();
        m_OutRenderQueues.clear();
    }
    
    void IPreRender::SetInTraverseRoot(const std::vector<kSGNode*>& roots  )
    {
        m_TraverseRoots = roots;
        IPreRender* pPreRender = dynamic_cast<IPreRender*>(m_pNextRCU);
        if (pPreRender)
            pPreRender->SetInTraverseRoot(roots);
        
        size_t count = m_ChildrenRCU.size();
        for (size_t i = 0; i < count; ++i)
        {
            pPreRender = dynamic_cast<IPreRender*>(m_ChildrenRCU[i]);
            if (pPreRender)
                pPreRender->SetInTraverseRoot(roots);
        }
    }
    
    
    void IPreRender::SetContext( kRenderingEngine * pRE )
    {
    }
    
    void IPreRender::SetInCamera( CCamera* pCamera )
    {
        m_pInCamera = pCamera;
    }
    
    void IPreRender::SetSceneManager(SceneManager*pSceneModel)
    {
        m_pSceneModelMpr = pSceneModel;
    }
    
    void IPreRender::SetRenderQueueManager(kRenderQueueManager*pRenderQueueMgr)
    {
        m_pRenderQueueMgr = pRenderQueueMgr;
    }
    
    void IPreRender::SetPreRenderManager(kPreRenderManager* pPreRenderMgr)
    {
        m_pPreRenderMgr = pPreRenderMgr;
    }
    
    void IPreRender::SetInRenderTarget( IRenderTarget * pRT )
    {
        m_pInRenderTarget = pRT;
    }
    
    void IPreRender::SetInRenderQueue( int i, kRenderQueue * pRenderQueue )
    {
        uint32_t count = i+1;
        if(count > m_InRenderQueues.size())
            m_InRenderQueues.resize(count,NULL);
        
        m_InRenderQueues[i] = pRenderQueue;
    }
    
    uint32_t  IPreRender::GetInRenderQueueCount() const
    {
        return  (uint32_t)m_InRenderQueues.size();
    }
    
    void IPreRender::SetOutRenderQueue( int i, kRenderQueue * pRenderQueue )
    {
        uint32_t count = i+1;
        if(count > m_OutRenderQueues.size())
            m_OutRenderQueues.resize(count,NULL);
        
        m_OutRenderQueues[i]= pRenderQueue;
    }
    
    uint32_t  IPreRender::GetOutRenderQueueCount() const
    {
        return  (uint32_t)m_OutRenderQueues.size();
    }
    
}
