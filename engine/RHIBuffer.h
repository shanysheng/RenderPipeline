#pragma once

#include "IRHIResource.h"


namespace pipeline {

	class kRHIDevice;


	struct kBufferInfo {
		uint32_t			m_DataSize;
		int8_t*				m_pData;
		kGPU_BUFFER_TYPE	m_Type;
	};

	class kRHIBuffer
	{
	public:
		kRHIBuffer();
		virtual ~kRHIBuffer();

		void CreateVertexBuffer(kRHIDevice& rhidevice, const char* pbuffer, size_t buffersize);
		void CreateIndexBuffer(kRHIDevice& rhidevice, const char* pbuffer, size_t buffersize);
		void CreateShaderStorageBuffer(kRHIDevice& rhidevice, const char* pbuffer, size_t buffersize);

		void CreateUniformBuffer(kRHIDevice& rhidevice, VkDeviceSize bufferSize);
		void UpdateBuffer(const void* pbuffer, uint32_t bufferSize);

		void ReleaseBuffer();

		VkBuffer GetBuffer() { return m_Buffer; }
		VkDescriptorBufferInfo GetBufferInfo();

	protected:
		VkDevice			m_Device;

		size_t				m_BufferSize;

		VkBuffer			m_Buffer;
		VkDeviceMemory		m_BufferMemory;
		void*				m_BufferMapped;
	};
}
