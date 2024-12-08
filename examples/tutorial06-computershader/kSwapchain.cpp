#include "kSwapchain.h"

#include "kContext.h"

#include <vector>
#include <limits>
#include <algorithm>
#include <array>

kSwapchain::kSwapchain() {
}

kSwapchain::~kSwapchain() {
}


void kSwapchain::createSwapchain(kContext& contextref, VkExtent2D extent, VkRenderPass renderpass) {

    SwapChainSupportDetails swapChainSupport = contextref.querySwapChainSupport(contextref.physicalDevice, contextref.surface);

    VkSurfaceFormatKHR surfaceFormat = contextref.getSwapchainSurfaceFormat();
    VkPresentModeKHR presentMode = contextref.getPresentMode();

    std::cout << "extent width:" << extent.width << ", height:" << extent.height << std::endl;

    uint32_t imageCount = contextref.getSwapchainImageCount();

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = contextref.surface;

    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamilyIndices indices = contextref.findQueueFamilies(contextref.physicalDevice, contextref.surface);
    uint32_t queueFamilyIndices[] = { indices.graphicsAndComputeFamily.value(), indices.presentFamily.value() };

    if (indices.graphicsAndComputeFamily != indices.presentFamily) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    }

    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;

    if (vkCreateSwapchainKHR(contextref.logicaldevice, &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
        throw std::runtime_error("failed to create swap chain!");
    }

    vkGetSwapchainImagesKHR(contextref.logicaldevice, swapChain, &imageCount, nullptr);

    swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(contextref.logicaldevice, swapChain, &imageCount, swapChainImages.data());

    swapChainImageFormat = surfaceFormat.format;
    swapChainExtent = extent;

    createSwapchainImageViews(contextref);
    createDepthResources(contextref);
    createFramebuffers(contextref, renderpass);
}


void kSwapchain::createSwapchainImageViews(kContext& contextref) {
    swapChainImageViews.resize(swapChainImages.size());

    for (size_t i = 0; i < swapChainImages.size(); i++) {
        swapChainImageViews[i] = contextref.createImageView(swapChainImages[i], swapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT);
    }
}


void kSwapchain::createDepthResources(kContext& contextref) {
    
    depthFormat = contextref.getDepthFormat();

    contextref.createImage(swapChainExtent.width, swapChainExtent.height, depthFormat, 
                            VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, 
                            depthImage, depthImageMemory);

    depthImageView = contextref.createImageView(depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);
}



void kSwapchain::createFramebuffers(kContext& contextref, VkRenderPass renderpass) {
    swapChainFramebuffers.resize(swapChainImageViews.size());

    for (size_t i = 0; i < swapChainImageViews.size(); i++) {
        std::array<VkImageView, 2> attachments = {
            swapChainImageViews[i],
            depthImageView
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = renderpass;
        framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        framebufferInfo.pAttachments = attachments.data();
        framebufferInfo.width = swapChainExtent.width;
        framebufferInfo.height = swapChainExtent.height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(contextref.logicaldevice, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create framebuffer!");
        }
    }
}


void kSwapchain::cleanupSwapChain(kContext& contextref) {

    vkDestroyImageView(contextref.logicaldevice, depthImageView, nullptr);
    vkDestroyImage(contextref.logicaldevice, depthImage, nullptr);
    vkFreeMemory(contextref.logicaldevice, depthImageMemory, nullptr);

    for (auto framebuffer : swapChainFramebuffers) {
        vkDestroyFramebuffer(contextref.logicaldevice, framebuffer, nullptr);
    }

    for (auto imageView : swapChainImageViews) {
        vkDestroyImageView(contextref.logicaldevice, imageView, nullptr);
    }

    vkDestroySwapchainKHR(contextref.logicaldevice, swapChain, nullptr);

    std::cout << "cleanup kSwapchain" << std::endl;
}

void kSwapchain::recreateSwapChain(kContext& contextref, VkExtent2D extent, VkRenderPass renderpass) {

    cleanupSwapChain(contextref);
    createSwapchain(contextref, extent, renderpass);
}

