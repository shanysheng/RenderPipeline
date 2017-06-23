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

		class CRenderQueue
		{ 
		public:
			CRenderQueue();
			virtual ~CRenderQueue();

			bool IsMatrixAggregated();
			int GetRenderQueueTag();
			IRenderQueueExtension*	GetRenderQueueExtension();

			void SetRenderQueueTag(int tag);
			void SetRenderQueeuExtension(IRenderQueueExtension* pExtension);

			void PushBack( SGNode* pEntity);
			void PushFront( SGNode* pEntity);

			SGNode* operator [](int index);
            const SGNode* operator [](int index) const;

			int Size() const;
			void Clear();

			void SetMatrixAggregated();
            
		protected:
			std::deque<SGNode*> 	m_Queue;

            int                     m_Tag;
			IRenderQueueExtension*  m_pExtension;

			friend class CRenderQueueManager;
		};
}

#endif
