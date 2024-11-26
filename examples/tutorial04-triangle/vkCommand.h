#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>

class vkContext;


// 渲染过程是异步的，获取swap chain image，执行command buffer，并把结果写入swap chain image，写入完成后可以进行present
// 这里存在几个问题：
// 1、获取swap chain image可能还在使用，需要等待被使用完；
// 2、执行command buffer，执行完需要告知后续的流程，完成了写入；
// 3、presnet流程的时候，需要等待被告知swap chain image已经写入完成，可以进行呈现；

// 所以分成两个流程：渲染流程和呈现流程；
// 渲染流程需要两个VkSemaphore：
// 1、等待swap chain image获取成功，可以写入的imageAvailableSemaphore
// 2、执行command buffer，渲染结果写入swap chain image完成，告知其他流程的renderFinishedSemaphore
// 呈现流程需要一个VkSemaphore：
// 1、swap chain image渲染结果写入完成，可被呈现renderFinishedSemaphore

// 绘制流程：
// 获取可用的swap chain image index；
// reset command buffer
// 开始记录command buffer（指定render pass、pipeline、image index指定的framebuffer）
// 构建VkSubmitInfo，指定imageAvailableSemaphore和renderFinishedSemaphore，提交执行vkQueueSubmit
// 
// 呈现流程：
// 构建VkPresentInfoKHR，指定renderFinishedSemaphore，vkQueuePresentKHR

void createCommandPool(vkContext& contextref);
void createCommandBuffers(vkContext& contextref);
void recordCommandBuffer(vkContext& contextref, uint32_t imageIndex);



VkCommandBuffer beginSingleTimeCommands(vkContext& contextref);

void endSingleTimeCommands(vkContext& contextref, VkCommandBuffer commandBuffer);
void copyBuffer(vkContext& contextref, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
