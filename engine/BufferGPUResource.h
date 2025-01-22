#pragma once

#include "IGPUResource.h"


namespace pipeline {


	class kBufferGPUResource :public IGPUResource
	{
	public:
		kBufferGPUResource();
		virtual ~kBufferGPUResource();
	};


}
