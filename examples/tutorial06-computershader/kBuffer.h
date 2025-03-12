#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class kContext;

class kBuffer
{
public:
	kBuffer();
	virtual ~kBuffer();

	void createVertexBuffer(kContext& contextref, const char* pbuffer, size_t buffersize);
	void createIndexBuffer(kContext& contextref, const char* pbuffer, size_t buffersize);
	void createShaderStorageBuffer(kContext& rhidevice, const char* pbuffer, size_t buffersize);

	void cleanupBuffer(kContext& contextref);

	VkBuffer getBuffer() { return m_vkBuffer; }

protected:


protected:
	VkBuffer			m_vkBuffer;
	VkDeviceMemory		m_vkBufferMemory;
};

