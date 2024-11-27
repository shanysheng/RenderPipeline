#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>



#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <array>


#include "vkContext.h"
#include "trangles.h"


const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;


class ComputeShaderApplication {
public:
    void run() {
        initWindow(global_context);
        initVulkan(global_context);
        mainLoop(global_context);
        cleanup(global_context);
    }

private:
    vkContext   global_context;

    float		lastFrameTime = 0.0f;
    bool        framebufferResized = false;
    double		lastTime = 0.0f;


    void initWindow(vkContext& contextref) {

        lastTime = glfwGetTime();

        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        contextref.window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
        glfwSetWindowUserPointer(contextref.window, this);
        glfwSetFramebufferSizeCallback(contextref.window, framebufferResizeCallback);
    }

    static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
        auto app = reinterpret_cast<ComputeShaderApplication*>(glfwGetWindowUserPointer(window));
        app->framebufferResized = true;
    }



    void initVulkan(vkContext& contextref) {

        contextref.initContext();
    }

    void drawFrame(vkContext& contextref) {
        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        // Compute submission        
        vkWaitForFences(contextref.logicaldevice, 1, &contextref.computeInFlightFences[contextref.currentFrame], VK_TRUE, UINT64_MAX);

        contextref.updateUniformBuffer(contextref.currentFrame, lastFrameTime);

        vkResetFences(contextref.logicaldevice, 1, &contextref.computeInFlightFences[contextref.currentFrame]);

        vkResetCommandBuffer(contextref.computeCommandBuffers[contextref.currentFrame], /*VkCommandBufferResetFlagBits*/ 0);
        recordComputeCommandBuffer(contextref, contextref.computeCommandBuffers[contextref.currentFrame]);

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &contextref.computeCommandBuffers[contextref.currentFrame];
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = &contextref.computeFinishedSemaphores[contextref.currentFrame];

        if (vkQueueSubmit(contextref.computeQueue, 1, &submitInfo, contextref.computeInFlightFences[contextref.currentFrame]) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit compute command buffer!");
        };

        // Graphics submission
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

        VkSemaphore waitSemaphores[] = { contextref.computeFinishedSemaphores[contextref.currentFrame], contextref.imageAvailableSemaphores[contextref.currentFrame] };
        VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_VERTEX_INPUT_BIT, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
        submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        submitInfo.waitSemaphoreCount = 2;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &contextref.commandBuffers[contextref.currentFrame];
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = &contextref.renderFinishedSemaphores[contextref.currentFrame];

        if (vkQueueSubmit(contextref.graphicsQueue, 1, &submitInfo, contextref.inFlightFences[contextref.currentFrame]) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit draw command buffer!");
        }

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = &contextref.renderFinishedSemaphores[contextref.currentFrame];

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

            // We want to animate the particle system using the last frames time to get smooth, frame-rate independent animation
            double currentTime = glfwGetTime();
            lastFrameTime = (currentTime - lastTime) * 1000.0;
            lastTime = currentTime;
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
        contextref.cleanContext();
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