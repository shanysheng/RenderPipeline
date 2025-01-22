/*
 * Copyright 2017 sheng chongshan. All rights reserved.
 * email: shany.sheng@qq.com
 * License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
 */

#ifndef PIPELINE_RENDERQUEUEMANAGER_H_GUARD
#define PIPELINE_RENDERQUEUEMANAGER_H_GUARD


#include "Common.h"

namespace pipeline{
    
    class kRenderQueue;
    
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
