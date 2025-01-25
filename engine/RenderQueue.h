#ifndef PIPELINE_RENDERQUEUE_H_GUARD
#define PIPELINE_RENDERQUEUE_H_GUARD

#include <deque>
#include "SGNode.h"

namespace pipeline{
    
    //------------------------------------------------------------------------------
    //	Desc:		The class CRenderQueue specifies a render queue which 
    //				consists of entities. In most cases, these entities are 
    //				supposed to be rendered in the following render pipelines. 
    //
    //------------------------------------------------------------------------------
    class kRenderQueue
    {
    public:
        kRenderQueue();
        virtual ~kRenderQueue();

        bool IsMatrixAggregated();
        void SetMatrixAggregated();

        int GetRenderQueueTag();
        void SetRenderQueueTag(int tag);
        
        void PushBack( kSGNode* pEntity);
        void PushFront( kSGNode* pEntity);
        
        kSGNode* operator [](int index);
        const kSGNode* operator [](int index) const;
        
        int Size() const;
        void Clear();


    protected:
        int                     m_Tag;
        bool                    m_bMatrixAggregated;
        std::deque<kSGNode*> 	m_Queue;
        
        friend class kRenderQueueManager;
    };
}

#endif
