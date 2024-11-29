#include "vkVertexBuffer.h"
#include "vkContext.h"




void createBuffer(vkContext& contextref, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
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
}

//void createVertexBuffer(vkContext& contextref, const Vertex* pvertex, size_t vertexCount) {
//    VkDeviceSize bufferSize = sizeof(pvertex[0]) * vertexCount;
//
//    VkBuffer stagingBuffer;
//    VkDeviceMemory stagingBufferMemory;
//    createBuffer(contextref, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);
//
//    void* data;
//    vkMapMemory(contextref.logicaldevice, stagingBufferMemory, 0, bufferSize, 0, &data);
//    memcpy(data, pvertex, (size_t)bufferSize);
//    vkUnmapMemory(contextref.logicaldevice, stagingBufferMemory);
//
//    createBuffer(contextref, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, contextref.vertexBuffer, contextref.vertexBufferMemory);
//
//    copyBuffer(contextref, stagingBuffer, contextref.vertexBuffer, bufferSize);
//
//    vkDestroyBuffer(contextref.logicaldevice, stagingBuffer, nullptr);
//    vkFreeMemory(contextref.logicaldevice, stagingBufferMemory, nullptr);
//}
//
//void createIndexBuffer(vkContext& contextref, const uint16_t* pindices, size_t indexCount) {
//    VkDeviceSize bufferSize = sizeof(pindices[0]) * indexCount;
//
//    VkBuffer stagingBuffer;
//    VkDeviceMemory stagingBufferMemory;
//    createBuffer(contextref, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);
//
//    void* data;
//    vkMapMemory(contextref.logicaldevice, stagingBufferMemory, 0, bufferSize, 0, &data);
//    memcpy(data, pindices, (size_t)bufferSize);
//    vkUnmapMemory(contextref.logicaldevice, stagingBufferMemory);
//
//    createBuffer(contextref, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, contextref.indexBuffer, contextref.indexBufferMemory);
//
//    copyBuffer(contextref, stagingBuffer, contextref.indexBuffer, bufferSize);
//
//    vkDestroyBuffer(contextref.logicaldevice, stagingBuffer, nullptr);
//    vkFreeMemory(contextref.logicaldevice, stagingBufferMemory, nullptr);
//}

void createUniformBuffers(vkContext& contextref, VkDeviceSize bufferSize) {

    contextref.uniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
    contextref.uniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
    contextref.uniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        createBuffer(contextref, bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, contextref.uniformBuffers[i], contextref.uniformBuffersMemory[i]);

        vkMapMemory(contextref.logicaldevice, contextref.uniformBuffersMemory[i], 0, bufferSize, 0, &contextref.uniformBuffersMapped[i]);
    }
}
