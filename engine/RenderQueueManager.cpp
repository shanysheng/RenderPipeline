#include "RenderQueueManager.h"
#include "RenderQueue.h"

namespace pipeline{
    
    CRenderQueueManager::CRenderQueueManager()
    {
        
    }
    
    CRenderQueueManager::~CRenderQueueManager()
    {
        ClearResources();
    }
    
    CRenderQueue* CRenderQueueManager::Give( const std::string& QueueName)
    {
        std::unordered_map<std::string, CRenderQueue*>::iterator mit;
        mit = m_RenderQueues.find(QueueName);
        if (mit == m_RenderQueues.end())
        {
            CRenderQueue* pRenderQueue = new CRenderQueue;
            m_RenderQueues.insert(std::make_pair(QueueName, pRenderQueue));
            return pRenderQueue;
        }
        
        return mit->second;
    }
    
    bool CRenderQueueManager::IsExisting( const std::string& QueueName ) const
    {
        std::unordered_map<std::string, CRenderQueue*>::const_iterator mit;
        mit = m_RenderQueues.find(QueueName);
        if (mit == m_RenderQueues.end())
        {
            return false;
        }
        
        return true;
    }
    
    CRenderQueue* CRenderQueueManager::operator [](const std::string& QueueName )
    {
        std::unordered_map<std::string, CRenderQueue*>::iterator mit;
        mit = m_RenderQueues.find(QueueName);
        if(mit == m_RenderQueues.end())
            return NULL;
        
        return mit->second;
    }
    
    void CRenderQueueManager::ClearResources()
    {
        std::unordered_map<std::string, CRenderQueue*>::iterator pos ;
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
