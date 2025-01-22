/*
 * Copyright 2017 sheng chongshan. All rights reserved.
 * email: shany.sheng@qq.com
 * License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
 */

#ifndef PIPELINE_RENDERQUEUE_H_GUARD
#define PIPELINE_RENDERQUEUE_H_GUARD

#include <deque>
#include "SGNode.h"

namespace pipeline{
    
    class IRenderQueueExtension
    {
    public:
        virtual ~IRenderQueueExtension(){};
    };
    
    class kRenderQueue
    {
    public:
        kRenderQueue();
        virtual ~kRenderQueue();
        
        bool IsMatrixAggregated();
        int GetRenderQueueTag();
        IRenderQueueExtension*	GetRenderQueueExtension();
        
        void SetRenderQueueTag(int tag);
        void SetRenderQueeuExtension(IRenderQueueExtension* pExtension);
        
        void PushBack( kSGNode* pEntity);
        void PushFront( kSGNode* pEntity);
        
        kSGNode* operator [](int index);
        const kSGNode* operator [](int index) const;
        
        int Size() const;
        void Clear();
        
        void SetMatrixAggregated();
        
    protected:
        std::deque<kSGNode*> 	m_Queue;
        
        int                     m_Tag;
        IRenderQueueExtension*  m_pExtension;
        
        friend class kRenderQueueManager;
    };
}

#endif
