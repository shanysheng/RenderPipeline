#ifndef PIPELINE_RENDERQUEUEMANAGER_H_GUARD
#define PIPELINE_RENDERQUEUEMANAGER_H_GUARD


#include "Common.h"

namespace pipeline{
    
    class kRenderQueue;
    
    //------------------------------------------------------------------------------
    //	Desc:		A CRenderQueueManager instance is a render queue container. 
    //				Inside the container, there is a map, the key of which is the
    //				unique name of the render queue. The overridden operator []
    //				(QueueName ) is used to search the corresponding 
    //				render queue whose name is specified by the input parameter.
    //
    //------------------------------------------------------------------------------
    class kRenderQueueManager
    {
    public:
        kRenderQueueManager();
        virtual ~kRenderQueueManager();
        
        bool IsExisting( const std::string& queueName ) const;
        kRenderQueue * Give( const std::string& queueName);
        kRenderQueue * operator [](const std::string& queueName);
        
        void ClearResources();
    protected:
        std::unordered_map<std::string, kRenderQueue*> m_RenderQueues;
    };
}

#endif
