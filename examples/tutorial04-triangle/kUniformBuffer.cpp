#include "kUniformBuffer.h"
#include "vkContext.h"


void kUniformBuffer::createUniformBuffers(vkContext& contextref, VkDeviceSize bufferSize) {

	createBuffer(contextref, bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, 
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
				m_UniformBuffer, m_UniformBuffersMemory);

	vkMapMemory(contextref.logicaldevice, m_UniformBuffersMemory, 0, bufferSize, 0, &m_UniformBuffersMapped);
}

void kUniformBuffer::cleanupGPUResource(vkContext& contextref) {
	vkDestroyBuffer(contextref.logicaldevice, m_UniformBuffer, nullptr);
	vkFreeMemory(contextref.logicaldevice, m_UniformBuffersMemory, nullptr);
}

