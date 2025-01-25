#include "RenderQueue.h"

namespace pipeline{
    
    
    kRenderQueue::kRenderQueue()
    {
        m_Tag = 0;
        m_bMatrixAggregated = false;
    }
    
    kRenderQueue::~kRenderQueue()
    {
        Clear();
    }
    
    int kRenderQueue::GetRenderQueueTag()
    {
        return m_Tag;
    }
    
    void kRenderQueue::SetRenderQueueTag(int tag)
    {
        m_Tag = tag;
    }
    
    void kRenderQueue::PushBack(kSGNode* pEntity)
    {
        m_Queue.push_back(pEntity);
    }
    
    void kRenderQueue::PushFront( kSGNode* pEntity)
    {
        m_Queue.push_front(pEntity);
    }
    
    kSGNode* kRenderQueue::operator [](int index)
    {
        return m_Queue[index];
    }
    
    const kSGNode* kRenderQueue::operator [](int index) const
    {
        return  m_Queue[index];
    }
    
    int kRenderQueue::Size() const
    {
        return (int)m_Queue.size();
    }
    
    void kRenderQueue::Clear()
    {
        m_Queue.clear();
    }
}
