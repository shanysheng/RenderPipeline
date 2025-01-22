#pragma once
#include "IGPUResource.h"


namespace pipeline {


	struct kImageInfo {
        uint32_t m_Width;
		uint32_t m_Height;
		uint32_t m_Components;
		uint32_t m_DataSize;
		uint8_t* m_pData;
	};

	class kImageTextureGPUResource : public IGPUResource
	{
	public:
		kImageTextureGPUResource();
		virtual ~kImageTextureGPUResource();

	protected:

	};
}