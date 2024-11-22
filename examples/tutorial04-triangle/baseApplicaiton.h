#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

#include "vkContext.h"
#include "vkWindow.h"
#include "vkInstance.h"
#include "vkLayer.h"
#include "vkDevice.h"
#include "vkSwapchain.h"
#include "vkGraphicsPipeline.h"
#include "vkCommand.h"


const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;


class HelloTriangleApplication {
public:
    void run() {
        initWindow(global_context);
        initVulkan(global_context);
        mainLoop(global_context);
        cleanup(global_context);
    }

private:
    bool framebufferResized = false;
    vkContext global_context;


    void initWindow(vkContext& contextref) {

        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        contextref.window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
        glfwSetWindowUserPointer(contextref.window, this);
        glfwSetFramebufferSizeCallback(contextref.window, framebufferResizeCallback);
    }

    static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
        auto app = reinterpret_cast<HelloTriangleApplication*>(glfwGetWindowUserPointer(window));
        app->framebufferResized = true;
    }

    void createSurface(vkContext& contextref) {
        if (glfwCreateWindowSurface(contextref.instance, contextref.window, nullptr, &contextref.surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }

    void createSyncObjects(vkContext& contextref) {
        contextref.imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        contextref.renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        contextref.inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

        VkSemaphoreCreateInfo semaphoreInfo{};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fenceInfo{};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            if (vkCreateSemaphore(contextref.logicaldevice, &semaphoreInfo, nullptr, &contextref.imageAvailableSemaphores[i]) != VK_SUCCESS ||
                vkCreateSemaphore(contextref.logicaldevice, &semaphoreInfo, nullptr, &contextref.renderFinishedSemaphores[i]) != VK_SUCCESS ||
                vkCreateFence(contextref.logicaldevice, &fenceInfo, nullptr, &contextref.inFlightFences[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create synchronization objects for a frame!");
            }
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
        createCommandBuffers(contextref);
        createSyncObjects(contextref);
    }

    void drawFrame(vkContext& contextref) {
        vkWaitForFences(contextref.logicaldevice, 1, &contextref.inFlightFences[contextref.currentFrame], VK_TRUE, UINT64_MAX);

        uint32_t imageIndex;
        VkResult result = vkAcquireNextImageKHR(contextref.logicaldevice, contextref.swapChain, UINT64_MAX, contextref.imageAvailableSemaphores[contextref.currentFrame], VK_NULL_HANDLE, &imageIndex);

        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            recreateSwapChain(contextref);
            return;
        }
        else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("failed to acquire swap chain image!");
        }

        vkResetFences(contextref.logicaldevice, 1, &contextref.inFlightFences[contextref.currentFrame]);

        vkResetCommandBuffer(contextref.commandBuffers[contextref.currentFrame], /*VkCommandBufferResetFlagBits*/ 0);
        recordCommandBuffer(contextref, imageIndex);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = { contextref.imageAvailableSemaphores[contextref.currentFrame] };
        VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &contextref.commandBuffers[contextref.currentFrame];

        VkSemaphore signalSemaphores[] = { contextref.renderFinishedSemaphores[contextref.currentFrame] };
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        if (vkQueueSubmit(contextref.graphicsQueue, 1, &submitInfo, contextref.inFlightFences[contextref.currentFrame]) != VK_SUCCESS) {
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

        result = vkQueuePresentKHR(contextref.presentQueue, &presentInfo);

        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
            framebufferResized = false;
            recreateSwapChain(contextref);
        }
        else if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to present swap chain image!");
        }

        contextref.currentFrame = (contextref.currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
    }


    void mainLoop(vkContext& contextref) {

        while (!glfwWindowShouldClose(contextref.window)) {
            glfwPollEvents();
            drawFrame(contextref);
        }

        vkDeviceWaitIdle(contextref.logicaldevice);
    }


    void cleanupSwapChain(vkContext& contextref) {
        for (auto framebuffer : contextref.swapChainFramebuffers) {
            vkDestroyFramebuffer(contextref.logicaldevice, framebuffer, nullptr);
        }

        for (auto imageView : contextref.swapChainImageViews) {
            vkDestroyImageView(contextref.logicaldevice, imageView, nullptr);
        }

        vkDestroySwapchainKHR(contextref.logicaldevice, contextref.swapChain, nullptr);
    }

    void cleanup(vkContext& contextref) {
        cleanupSwapChain(contextref);

        vkDestroyPipeline(contextref.logicaldevice, contextref.graphicsPipeline, nullptr);
        vkDestroyPipelineLayout(contextref.logicaldevice, contextref.pipelineLayout, nullptr);

        vkDestroyRenderPass(contextref.logicaldevice, contextref.renderPass, nullptr);

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            vkDestroySemaphore(contextref.logicaldevice, contextref.renderFinishedSemaphores[i], nullptr);
            vkDestroySemaphore(contextref.logicaldevice, contextref.imageAvailableSemaphores[i], nullptr);
            vkDestroyFence(contextref.logicaldevice, contextref.inFlightFences[i], nullptr);
        }

        vkDestroyCommandPool(contextref.logicaldevice, contextref.commandPool, nullptr);

        vkDestroyDevice(contextref.logicaldevice, nullptr);

        cleanupDebugMessenger(contextref.instance);

        vkDestroySurfaceKHR(contextref.instance, contextref.surface, nullptr);
        vkDestroyInstance(contextref.instance, nullptr);

        glfwDestroyWindow(contextref.window);

        glfwTerminate();
    }


    void recreateSwapChain(vkContext& contextref) {
        int width = 0, height = 0;
        glfwGetFramebufferSize(contextref.window, &width, &height);
        while (width == 0 || height == 0) {
            glfwGetFramebufferSize(contextref.window, &width, &height);
            glfwWaitEvents();
        }

        vkDeviceWaitIdle(contextref.logicaldevice);

        cleanupSwapChain(contextref);

        createSwapChain(contextref);
        createImageViews(contextref);
        createFramebuffers(contextref);
    }


};