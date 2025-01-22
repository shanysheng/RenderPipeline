#pragma once

#include "IGPUResource.h"


namespace pipeline {

	struct kBufferInfo {
		uint32_t			m_DataSize;
		int8_t*				m_pData;
		kGPU_BUFFER_TYPE	m_Type;
	};

	class kBufferGPUResource :public IGPUResource
	{
	public:
		kBufferGPUResource();
		virtual ~kBufferGPUResource();
	};


}
