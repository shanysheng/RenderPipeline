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

        rhidevice.CreateBuffer( VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, 
                                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, buffersize, m_Buffer, m_BufferMemory);

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        rhidevice.CreateBuffer( VK_BUFFER_USAGE_TRANSFER_SRC_BIT, 
                                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                                buffersize, stagingBuffer, stagingBufferMemory);

        void* data;
        vkMapMemory(rhidevice.GetLogicDevice(), stagingBufferMemory, 0, buffersize, 0, &data);
        memcpy(data, pbuffer, (size_t)buffersize);
        vkUnmapMemory(rhidevice.GetLogicDevice(), stagingBufferMemory);

        rhidevice.CopyBuffer(stagingBuffer, m_Buffer, buffersize);

        vkDestroyBuffer(rhidevice.GetLogicDevice(), stagingBuffer, nullptr);
        vkFreeMemory(rhidevice.GetLogicDevice(), stagingBufferMemory, nullptr);
    }

    void kRHIBuffer::CreateIndexBuffer(kRHIDevice& rhidevice, const char* pbuffer, size_t buffersize) {

        rhidevice.CreateBuffer( VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, 
                                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, buffersize, m_Buffer, m_BufferMemory);

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        rhidevice.CreateBuffer( VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                                buffersize, stagingBuffer, stagingBufferMemory);

        void* data;
        vkMapMemory(rhidevice.GetLogicDevice(), stagingBufferMemory, 0, buffersize, 0, &data);
        memcpy(data, pbuffer, (size_t)buffersize);
        vkUnmapMemory(rhidevice.GetLogicDevice(), stagingBufferMemory);

        rhidevice.CopyBuffer(stagingBuffer, m_Buffer, buffersize);

        vkDestroyBuffer(rhidevice.GetLogicDevice(), stagingBuffer, nullptr);
        vkFreeMemory(rhidevice.GetLogicDevice(), stagingBufferMemory, nullptr);
    }


    void kRHIBuffer::CreateUniformBuffer(kRHIDevice& rhidevice, VkDeviceSize bufferSize) {

        rhidevice.CreateBuffer( VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                                bufferSize, m_Buffer, m_BufferMemory);

        vkMapMemory(rhidevice.GetLogicDevice(), m_BufferMemory, 0, bufferSize, 0, &m_BufferMapped);
    }


    void  kRHIBuffer::ReleaseBuffer(kRHIDevice& rhidevice) {
        vkDestroyBuffer(rhidevice.GetLogicDevice(), m_Buffer, nullptr);
        vkFreeMemory(rhidevice.GetLogicDevice(), m_BufferMemory, nullptr);

        m_Buffer = nullptr;
        m_BufferMemory = nullptr;

        std::cout << "cleanup kBuffer" << std::endl;
    }

    void kRHIBuffer::UpdateBuffer(const void* pbuffer, uint32_t bufferSize) {
        memcpy(m_BufferMapped, pbuffer, bufferSize);
    }

}