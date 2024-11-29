#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class vkContext;

class kBuffer
{
public:
	kBuffer();
	virtual ~kBuffer();

	void createVertexBuffer(vkContext& contextref, const char* pbuffer, size_t buffersize);
	void createIndexBuffer(vkContext& contextref, const char* pbuffer, size_t buffersize);

	VkBuffer getBuffer() { return m_vkBuffer; }

protected:

	bool createBuffer(vkContext& contextref,  size_t buffersize, 
					VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, 
					VkBuffer& buffer, VkDeviceMemory& bufferMemory);

	uint32_t findMemoryType(vkContext& contextref, uint32_t typeFilter, VkMemoryPropertyFlags properties);


protected:
	vkContext*			m_pContext;
	VkBuffer			m_vkBuffer;
	VkDeviceMemory		m_vkBufferMemory;
};

