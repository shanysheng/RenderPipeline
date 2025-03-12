#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class kContext;


class kUniformBuffer
{
public:
	kUniformBuffer() {};
	virtual ~kUniformBuffer() {};

	void createUniformBuffers(kContext& contextref, VkDeviceSize bufferSize);
	void cleanupGPUResource(kContext& contextref);

	void updateBuffer(const void* pbuffer, uint32_t bufferSize);

	VkBuffer getBuffer() { return m_UniformBuffer; }
	void* getMappedBuffer() { return m_UniformBuffersMapped; }

protected:
	VkBuffer		m_UniformBuffer;
	VkDeviceMemory	m_UniformBuffersMemory;
	void*			m_UniformBuffersMapped;
};

