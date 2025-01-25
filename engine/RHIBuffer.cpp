#include "RHIBuffer.h"
#include "RHIDevice.h"

namespace pipeline {


    kRHIBuffer::kRHIBuffer() {
        m_Buffer = nullptr;
        m_BufferMemory = nullptr;
        m_BufferMapped = nullptr;
    }

    kRHIBuffer::~kRHIBuffer()
    {

    }

    void kRHIBuffer::CreateVertexBuffer(kRHIDevice& rhidevice, const char* pbuffer, size_t buffersize) {

        rhidevice.CreateBuffer(buffersize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, 
                                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_Buffer, m_BufferMemory);

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        rhidevice.CreateBuffer(buffersize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, 
                                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                                stagingBuffer, stagingBufferMemory);

        void* data;
        vkMapMemory(rhidevice.logicaldevice, stagingBufferMemory, 0, buffersize, 0, &data);
        memcpy(data, pbuffer, (size_t)buffersize);
        vkUnmapMemory(rhidevice.logicaldevice, stagingBufferMemory);

        rhidevice.CopyBuffer(stagingBuffer, m_Buffer, buffersize);

        vkDestroyBuffer(rhidevice.logicaldevice, stagingBuffer, nullptr);
        vkFreeMemory(rhidevice.logicaldevice, stagingBufferMemory, nullptr);
    }

    void kRHIBuffer::CreateIndexBuffer(kRHIDevice& rhidevice, const char* pbuffer, size_t buffersize) {

        rhidevice.CreateBuffer(buffersize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, 
                                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_Buffer, m_BufferMemory);

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        rhidevice.CreateBuffer(buffersize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                                stagingBuffer, stagingBufferMemory);

        void* data;
        vkMapMemory(rhidevice.logicaldevice, stagingBufferMemory, 0, buffersize, 0, &data);
        memcpy(data, pbuffer, (size_t)buffersize);
        vkUnmapMemory(rhidevice.logicaldevice, stagingBufferMemory);

        rhidevice.CopyBuffer(stagingBuffer, m_Buffer, buffersize);

        vkDestroyBuffer(rhidevice.logicaldevice, stagingBuffer, nullptr);
        vkFreeMemory(rhidevice.logicaldevice, stagingBufferMemory, nullptr);
    }


    void kRHIBuffer::CreateUniformBuffer(kRHIDevice& rhidevice, VkDeviceSize bufferSize) {

        rhidevice.CreateBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                                m_Buffer, m_BufferMemory);

        vkMapMemory(rhidevice.logicaldevice, m_BufferMemory, 0, bufferSize, 0, &m_BufferMapped);
    }


    void  kRHIBuffer::ReleaseBuffer(kRHIDevice& rhidevice) {
        vkDestroyBuffer(rhidevice.logicaldevice, m_Buffer, nullptr);
        vkFreeMemory(rhidevice.logicaldevice, m_BufferMemory, nullptr);

        m_Buffer = nullptr;
        m_BufferMemory = nullptr;

        std::cout << "cleanup kBuffer" << std::endl;
    }

    void kRHIBuffer::UpdateBuffer(const void* pbuffer, uint32_t bufferSize) {
        memcpy(m_BufferMapped, pbuffer, bufferSize);
    }

}