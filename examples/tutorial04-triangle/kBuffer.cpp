#include "kBuffer.h"
#include "vkContext.h"

kBuffer::kBuffer() {
    m_vkBuffer = nullptr;
    m_vkBufferMemory = nullptr;
}

kBuffer::~kBuffer()
{

}

void  kBuffer::cleanupBuffer(vkContext& contextref) {
    vkDestroyBuffer(contextref.logicaldevice, m_vkBuffer, nullptr);
    vkFreeMemory(contextref.logicaldevice, m_vkBufferMemory, nullptr);
}

void kBuffer::createVertexBuffer(vkContext& contextref, const char* pbuffer, size_t buffersize) {

    this->createBuffer(contextref, buffersize, 
                VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, 
                m_vkBuffer, m_vkBufferMemory);

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    createBuffer(contextref, buffersize, 
                VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, 
                stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(contextref.logicaldevice, stagingBufferMemory, 0, buffersize, 0, &data);
    memcpy(data, pbuffer, (size_t)buffersize);
    vkUnmapMemory(contextref.logicaldevice, stagingBufferMemory);

    copyBuffer(contextref, stagingBuffer, m_vkBuffer, buffersize);

    vkDestroyBuffer(contextref.logicaldevice, stagingBuffer, nullptr);
    vkFreeMemory(contextref.logicaldevice, stagingBufferMemory, nullptr);
}

void kBuffer::createIndexBuffer(vkContext& contextref, const char* pbuffer, size_t buffersize) {

    createBuffer(contextref, buffersize, 
                VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, 
                m_vkBuffer, m_vkBufferMemory);

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    createBuffer(contextref, buffersize, 
                 VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, 
                stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(contextref.logicaldevice, stagingBufferMemory, 0, buffersize, 0, &data);
    memcpy(data, pbuffer, (size_t)buffersize);
    vkUnmapMemory(contextref.logicaldevice, stagingBufferMemory);

    copyBuffer(contextref, stagingBuffer, m_vkBuffer, buffersize);

    vkDestroyBuffer(contextref.logicaldevice, stagingBuffer, nullptr);
    vkFreeMemory(contextref.logicaldevice, stagingBufferMemory, nullptr);
}

bool kBuffer::createBuffer(vkContext& contextref, size_t buffersize,
				VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, 
                VkBuffer& buffer, VkDeviceMemory& bufferMemory)
{

    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = buffersize;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(contextref.logicaldevice, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to create buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(contextref.logicaldevice, buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(contextref, memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(contextref.logicaldevice, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate buffer memory!");
    }

    vkBindBufferMemory(contextref.logicaldevice, buffer, bufferMemory, 0);

	return true;
}

uint32_t kBuffer::findMemoryType(vkContext& contextref, uint32_t typeFilter, VkMemoryPropertyFlags properties) {
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(contextref.physicalDevice, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("failed to find suitable memory type!");
}