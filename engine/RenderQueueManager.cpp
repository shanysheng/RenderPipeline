#include "RenderQueueManager.h"
#include "RenderQueue.h"

namespace pipeline{
    
    kRenderQueueManager::kRenderQueueManager()
    {
        
    }
    
    kRenderQueueManager::~kRenderQueueManager()
    {
        ClearResources();
    }
    
    kRenderQueue* kRenderQueueManager::Give( const std::string& QueueName)
    {
        std::unordered_map<std::string, kRenderQueue*>::iterator mit;
        mit = m_RenderQueues.find(QueueName);
        if (mit == m_RenderQueues.end())
        {
            kRenderQueue* pRenderQueue = new kRenderQueue;
            m_RenderQueues.insert(std::make_pair(QueueName, pRenderQueue));
            return pRenderQueue;
        }
        
        return mit->second;
    }
    
    bool kRenderQueueManager::IsExisting( const std::string& QueueName ) const
    {
        std::unordered_map<std::string, kRenderQueue*>::const_iterator mit;
        mit = m_RenderQueues.find(QueueName);
        if (mit == m_RenderQueues.end())
        {
            return false;
        }
        
        return true;
    }
    
    kRenderQueue* kRenderQueueManager::operator [](const std::string& QueueName )
    {
        std::unordered_map<std::string, kRenderQueue*>::iterator mit;
        mit = m_RenderQueues.find(QueueName);
        if(mit == m_RenderQueues.end())
            return NULL;
        
        return mit->second;
    }
    
    void kRenderQueueManager::ClearResources()
    {
        std::unordered_map<std::string, kRenderQueue*>::iterator pos ;
        pos = m_RenderQueues.begin();
        while (pos!=m_RenderQueues.end())
        {
            delete pos->second;
            pos->second = NULL;
            
            ++pos;
        }
        
        m_RenderQueues.clear();
    }
}
