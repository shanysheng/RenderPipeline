#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class vkContext;


class kUniformBuffer
{
public:
	kUniformBuffer() {};
	virtual ~kUniformBuffer() {};

	void createUniformBuffers(vkContext& contextref, VkDeviceSize bufferSize);
	void cleanupGPUResource(vkContext& contextref);


	VkBuffer getBuffer() { return m_UniformBuffer; }
	void* getMappedBuffer() { return m_UniformBuffersMapped; }

protected:
	VkBuffer		m_UniformBuffer;
	VkDeviceMemory	m_UniformBuffersMemory;
	void*			m_UniformBuffersMapped;
};

