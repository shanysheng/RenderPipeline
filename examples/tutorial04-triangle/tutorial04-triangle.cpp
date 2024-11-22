// tutorial01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

#include "vkInstance.h"
#include "vkLayer.h"
#include "vkDevice.h"
#include "vkSwapchain.h"
#include "vkGraphicsPipeline.h"
#include "vkCommand.h"
#include "vkContext.h"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const int MAX_FRAMES_IN_FLIGHT = 2;



VkSemaphore imageAvailableSemaphore;
VkSemaphore renderFinishedSemaphore;
VkFence inFlightFence;



void initWindow(vkContext& contextref) {

    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    contextref.window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}



void createSyncObjects(vkContext& contextref) {
    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    if (vkCreateSemaphore(contextref.logicaldevice, &semaphoreInfo, nullptr, &imageAvailableSemaphore) != VK_SUCCESS ||
        vkCreateSemaphore(contextref.logicaldevice, &semaphoreInfo, nullptr, &renderFinishedSemaphore) != VK_SUCCESS ||
        vkCreateFence(contextref.logicaldevice, &fenceInfo, nullptr, &inFlightFence) != VK_SUCCESS) {
        throw std::runtime_error("failed to create synchronization objects for a frame!");
    }
}


void initVulkan(vkContext& contextref) {

    createInstance(contextref);
    setupDebugMessenger(contextref.instance);
    createSurface(contextref);

    pickPhysicalDevice(contextref);
    createLogicalDevice(contextref);
    createSwapChain(contextref);
    createImageViews(contextref);

    createRenderPass(contextref);
    createGraphicsPipeline(contextref);
    createFramebuffers(contextref);

    createCommandPool(contextref);
    createCommandBuffer(contextref);
    createSyncObjects(contextref);
}


void drawFrame(vkContext& contextref) {
    vkWaitForFences(contextref.logicaldevice, 1, &inFlightFence, VK_TRUE, UINT64_MAX);
    vkResetFences(contextref.logicaldevice, 1, &inFlightFence);

    uint32_t imageIndex;
    vkAcquireNextImageKHR(contextref.logicaldevice, contextref.swapChain, UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

    vkResetCommandBuffer(contextref.commandBuffer, /*VkCommandBufferResetFlagBits*/ 0);
    recordCommandBuffer(contextref, imageIndex);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = { imageAvailableSemaphore };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &contextref.commandBuffer;

    VkSemaphore signalSemaphores[] = { renderFinishedSemaphore };
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(contextref.graphicsQueue, 1, &submitInfo, inFlightFence) != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = { contextref.swapChain };
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;

    presentInfo.pImageIndices = &imageIndex;

    vkQueuePresentKHR(contextref.presentQueue, &presentInfo);
}


void mainLoop(vkContext& contextref) {

    while (!glfwWindowShouldClose(contextref.window)) {
        glfwPollEvents();
        drawFrame(contextref);
    }

    vkDeviceWaitIdle(contextref.logicaldevice);
}

void cleanup(vkContext& contextref) {
    vkDestroySemaphore(contextref.logicaldevice, renderFinishedSemaphore, nullptr);
    vkDestroySemaphore(contextref.logicaldevice, imageAvailableSemaphore, nullptr);
    vkDestroyFence(contextref.logicaldevice, inFlightFence, nullptr);

    vkDestroyCommandPool(contextref.logicaldevice, contextref.commandPool, nullptr);

    for (auto framebuffer : contextref.swapChainFramebuffers) {
        vkDestroyFramebuffer(contextref.logicaldevice, framebuffer, nullptr);
    }

    vkDestroyPipeline(contextref.logicaldevice, contextref.graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(contextref.logicaldevice, contextref.pipelineLayout, nullptr);
    vkDestroyRenderPass(contextref.logicaldevice, contextref.renderPass, nullptr);

    for (auto imageView : contextref.swapChainImageViews) {
        vkDestroyImageView(contextref.logicaldevice, imageView, nullptr);
    }

    vkDestroySwapchainKHR(contextref.logicaldevice, contextref.swapChain, nullptr);
    vkDestroyDevice(contextref.logicaldevice, nullptr);

    cleanupDebugMessenger(contextref.instance);
    //cleanupSurface(instance, logicaldevice);

    vkDestroySurfaceKHR(contextref.instance, contextref.surface, nullptr);
    vkDestroyInstance(contextref.instance, nullptr);

    glfwDestroyWindow(contextref.window);

    glfwTerminate();
}



int main()
{
    std::cout << "Hello vulkan world!\n";


    vkContext global_context;


    initWindow(global_context);
    initVulkan(global_context);
    mainLoop(global_context);
    cleanup(global_context);

}
