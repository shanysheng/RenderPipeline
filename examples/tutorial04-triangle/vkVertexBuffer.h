#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <vector>
#include <array>

class vkContext;


void createBuffer(vkContext& contextref, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

//void createVertexBuffer(vkContext& contextref, const Vertex* pvertex, size_t vertexCount);

//void createIndexBuffer(vkContext& contextref, const uint16_t* pindices, size_t indexCount);

void createUniformBuffers(vkContext& contextref, VkDeviceSize bufferSize);

void createDescriptorPool(vkContext& contextref);

void createDescriptorSets(vkContext& contextref, VkDeviceSize bufferSize);