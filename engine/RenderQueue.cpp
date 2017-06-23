#include "RenderQueue.h"

namespace pipeline{
    
    
    CRenderQueue::CRenderQueue()
    {
        m_Tag = 0;
        m_bMatrixAggregated = false;
        m_pExtension = NULL;
    }
    
    CRenderQueue::~CRenderQueue()
    {
        Clear();
    }
    
    int CRenderQueue::GetRenderQueueTag()
    {
        return m_Tag;
    }
    
    IRenderQueueExtension* CRenderQueue::GetRenderQueueExtension()
    {
        return m_pExtension;
    }
    
    void CRenderQueue::SetRenderQueueTag(int tag)
    {
        m_Tag = tag;
    }
    
    void CRenderQueue::SetRenderQueeuExtension(IRenderQueueExtension* pExtension)
    {
        m_pExtension = pExtension;
    }
    
    void CRenderQueue::PushBack(SGNode* pEntity)
    {
        m_Queue.push_back(pEntity);
    }
    
    void CRenderQueue::PushFront( SGNode* pEntity)
    {
        m_Queue.push_front(pEntity);
    }
    
    SGNode* CRenderQueue::operator [](int index)
    {
        return m_Queue[index];
    }
    
    const SGNode* CRenderQueue::operator [](int index) const
    {
        return  m_Queue[index];
    }
    
    int CRenderQueue::Size() const
    {
        return (int)m_Queue.size();
    }
    
    void CRenderQueue::Clear()
    {
        m_Queue.clear();
    }
}
