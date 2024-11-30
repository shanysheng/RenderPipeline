#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class vkContext;

class kBuffer
{
public:
	kBuffer();
	virtual ~kBuffer();

	void createVertexBuffer(vkContext& contextref, const char* pbuffer, size_t buffersize);
	void createIndexBuffer(vkContext& contextref, const char* pbuffer, size_t buffersize);

	void cleanupBuffer(vkContext& contextref);

	VkBuffer getBuffer() { return m_vkBuffer; }

protected:

	bool createBuffer(vkContext& contextref,  size_t buffersize, 
					VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, 
					VkBuffer& buffer, VkDeviceMemory& bufferMemory);

	uint32_t findMemoryType(vkContext& contextref, uint32_t typeFilter, VkMemoryPropertyFlags properties);


protected:
	VkBuffer			m_vkBuffer;
	VkDeviceMemory		m_vkBufferMemory;
};

