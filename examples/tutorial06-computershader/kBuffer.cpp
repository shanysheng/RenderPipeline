#include "kBuffer.h"
#include "kContext.h"

kBuffer::kBuffer() {
    m_vkBuffer = nullptr;
    m_vkBufferMemory = nullptr;
}

kBuffer::~kBuffer()
{

}

void  kBuffer::cleanupBuffer(kContext& contextref) {
    vkDestroyBuffer(contextref.logicaldevice, m_vkBuffer, nullptr);
    vkFreeMemory(contextref.logicaldevice, m_vkBufferMemory, nullptr);

    std::cout << "cleanup kBuffer" << std::endl;
}

void kBuffer::createVertexBuffer(kContext& contextref, const char* pbuffer, size_t buffersize) {

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

void kBuffer::createIndexBuffer(kContext& contextref, const char* pbuffer, size_t buffersize) {

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
