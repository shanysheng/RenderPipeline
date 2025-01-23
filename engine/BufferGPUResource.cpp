#include "BufferGPUResource.h"
#include "RHIContext.h"

namespace pipeline {


    kBuffer::kBuffer() {
        m_vkBuffer = nullptr;
        m_vkBufferMemory = nullptr;
    }

    kBuffer::~kBuffer()
    {

    }

    void  kBuffer::cleanupBuffer(kRHIContext& contextref) {
        vkDestroyBuffer(contextref.logicaldevice, m_vkBuffer, nullptr);
        vkFreeMemory(contextref.logicaldevice, m_vkBufferMemory, nullptr);

        m_vkBuffer = nullptr;
        m_vkBufferMemory = nullptr;

        std::cout << "cleanup kBuffer" << std::endl;
    }

    void kBuffer::createVertexBuffer(kRHIContext& contextref, const char* pbuffer, size_t buffersize) {

        contextref.createBuffer(buffersize,
            VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
            m_vkBuffer, m_vkBufferMemory);

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        contextref.createBuffer(buffersize,
            VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            stagingBuffer, stagingBufferMemory);

        void* data;
        vkMapMemory(contextref.logicaldevice, stagingBufferMemory, 0, buffersize, 0, &data);
        memcpy(data, pbuffer, (size_t)buffersize);
        vkUnmapMemory(contextref.logicaldevice, stagingBufferMemory);

        contextref.copyBuffer(stagingBuffer, m_vkBuffer, buffersize);

        vkDestroyBuffer(contextref.logicaldevice, stagingBuffer, nullptr);
        vkFreeMemory(contextref.logicaldevice, stagingBufferMemory, nullptr);
    }

    void kBuffer::createIndexBuffer(kRHIContext& contextref, const char* pbuffer, size_t buffersize) {

        contextref.createBuffer(buffersize,
            VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
            m_vkBuffer, m_vkBufferMemory);

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        contextref.createBuffer(buffersize,
            VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            stagingBuffer, stagingBufferMemory);

        void* data;
        vkMapMemory(contextref.logicaldevice, stagingBufferMemory, 0, buffersize, 0, &data);
        memcpy(data, pbuffer, (size_t)buffersize);
        vkUnmapMemory(contextref.logicaldevice, stagingBufferMemory);

        contextref.copyBuffer(stagingBuffer, m_vkBuffer, buffersize);

        vkDestroyBuffer(contextref.logicaldevice, stagingBuffer, nullptr);
        vkFreeMemory(contextref.logicaldevice, stagingBufferMemory, nullptr);
    }


    void kUniformBuffer::createUniformBuffers(kRHIContext& contextref, VkDeviceSize bufferSize) {

        contextref.createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            m_UniformBuffer, m_UniformBuffersMemory);

        vkMapMemory(contextref.logicaldevice, m_UniformBuffersMemory, 0, bufferSize, 0, &m_UniformBuffersMapped);
    }

    void kUniformBuffer::cleanupGPUResource(kRHIContext& contextref) {
        vkDestroyBuffer(contextref.logicaldevice, m_UniformBuffer, nullptr);
        vkFreeMemory(contextref.logicaldevice, m_UniformBuffersMemory, nullptr);
    }

    void kUniformBuffer::updateBuffer(const void* pbuffer, uint32_t bufferSize) {
        memcpy(m_UniformBuffersMapped, pbuffer, bufferSize);
    }


}