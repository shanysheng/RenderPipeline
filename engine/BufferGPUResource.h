#pragma once

#include "IGPUResource.h"


namespace pipeline {

	class kRHIContext;


	struct kBufferInfo {
		uint32_t			m_DataSize;
		int8_t*				m_pData;
		kGPU_BUFFER_TYPE	m_Type;
	};


	class kBuffer
	{
	public:
		kBuffer();
		virtual ~kBuffer();

		void createVertexBuffer(kRHIContext& contextref, const char* pbuffer, size_t buffersize);
		void createIndexBuffer(kRHIContext& contextref, const char* pbuffer, size_t buffersize);

		void cleanupBuffer(kRHIContext& contextref);

		VkBuffer getBuffer() { return m_vkBuffer; }

	protected:


	protected:
		VkBuffer			m_vkBuffer;
		VkDeviceMemory		m_vkBufferMemory;
	};



	class kUniformBuffer
	{
	public:
		kUniformBuffer() {};
		virtual ~kUniformBuffer() {};

		void createUniformBuffers(kRHIContext& contextref, VkDeviceSize bufferSize);
		void cleanupGPUResource(kRHIContext& contextref);

		void updateBuffer(const void* pbuffer, uint32_t bufferSize);

		VkBuffer getBuffer() { return m_UniformBuffer; }

	protected:
		VkBuffer		m_UniformBuffer;
		VkDeviceMemory	m_UniformBuffersMemory;
		void* m_UniformBuffersMapped;
	};



}
