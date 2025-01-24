#include "RHISwapchain.h"

#include "RHIContext.h"


namespace pipeline {

    kRHISwapchain::kRHISwapchain() {
    }

    kRHISwapchain::~kRHISwapchain() {
    }


    void kRHISwapchain::CreateSwapchain(kRHIContext& contextref, VkExtent2D extent) {

        CreateRenderpass(contextref);
        
        SwapChainSupportDetails swapChainSupport = contextref.querySwapChainSupport(contextref.physicalDevice, contextref.surface);
        VkSurfaceFormatKHR surfaceFormat = contextref.getSwapchainSurfaceFormat();
        VkPresentModeKHR presentMode = contextref.getPresentMode();
        uint32_t imageCount = contextref.getSwapchainImageCount();

        m_SwapchainColorImageFormat = surfaceFormat.format;
        m_SwapchainExtent = extent;

        std::cout << "swapchain imageCount:" << imageCount << ", extent width:" << extent.width << ", height:" << extent.height << std::endl;


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

        if (vkCreateSwapchainKHR(contextref.logicaldevice, &createInfo, nullptr, &m_Swapchain) != VK_SUCCESS) {
            throw std::runtime_error("failed to create swap chain!");
        }

        vkGetSwapchainImagesKHR(contextref.logicaldevice, m_Swapchain, &imageCount, nullptr);
        m_SwapchainColorImages.resize(imageCount);
        vkGetSwapchainImagesKHR(contextref.logicaldevice, m_Swapchain, &imageCount, m_SwapchainColorImages.data());

        CreateSwapchainColorImageViews(contextref);
        CreateSwapchainDepthImageView(contextref);
        CreateFramebuffers(contextref);
    }

    void kRHISwapchain::CreateRenderpass(kRHIContext& contextref) {
        VkAttachmentDescription colorAttachment{};
        colorAttachment.format = contextref.getSwapchainSurfaceFormat().format;
        colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentDescription depthAttachment{};
        depthAttachment.format = contextref.getDepthFormat();
        depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        VkAttachmentReference colorAttachmentRef{};
        colorAttachmentRef.attachment = 0;
        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkAttachmentReference depthAttachmentRef{};
        depthAttachmentRef.attachment = 1;
        depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass{};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorAttachmentRef;
        subpass.pDepthStencilAttachment = &depthAttachmentRef;

        VkSubpassDependency dependency{};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
        dependency.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

        std::array<VkAttachmentDescription, 2> attachments = { colorAttachment, depthAttachment };
        VkRenderPassCreateInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        renderPassInfo.pAttachments = attachments.data();
        renderPassInfo.subpassCount = 1;
        renderPassInfo.pSubpasses = &subpass;
        renderPassInfo.dependencyCount = 1;
        renderPassInfo.pDependencies = &dependency;

        if (vkCreateRenderPass(contextref.logicaldevice, &renderPassInfo, nullptr, &m_RenderPass) != VK_SUCCESS) {
            throw std::runtime_error("failed to create render pass!");
        }
    }

    void kRHISwapchain::CreateSwapchainColorImageViews(kRHIContext& contextref) {

        m_SwapchainColorImageViews.resize(m_SwapchainColorImages.size());
        for (size_t i = 0; i < m_SwapchainColorImages.size(); i++) {
            m_SwapchainColorImageViews[i] = contextref.createImageView(m_SwapchainColorImages[i], m_SwapchainColorImageFormat, VK_IMAGE_ASPECT_COLOR_BIT);
        }
    }

    void kRHISwapchain::CreateSwapchainDepthImageView(kRHIContext& contextref) {

        m_SwapchainDepthFormat = contextref.getDepthFormat();

        contextref.createImage(m_SwapchainExtent.width, m_SwapchainExtent.height, m_SwapchainDepthFormat,
                                VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, 
                                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_SwapchainDepthImage, m_SwapchainDepthImageMemory);

        m_SwapchainDepthImageView = contextref.createImageView(m_SwapchainDepthImage, m_SwapchainDepthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);
    }


    void kRHISwapchain::CreateFramebuffers(kRHIContext& contextref) {

        m_SwapchainFramebuffers.resize(m_SwapchainColorImageViews.size());
        for (size_t i = 0; i < m_SwapchainColorImageViews.size(); i++) {
            std::array<VkImageView, 2> attachments = {
                m_SwapchainColorImageViews[i],
                m_SwapchainDepthImageView
            };

            VkFramebufferCreateInfo framebufferInfo{};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = m_RenderPass;
            framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
            framebufferInfo.pAttachments = attachments.data();
            framebufferInfo.width = m_SwapchainExtent.width;
            framebufferInfo.height = m_SwapchainExtent.height;
            framebufferInfo.layers = 1;

            if (vkCreateFramebuffer(contextref.logicaldevice, &framebufferInfo, nullptr, &m_SwapchainFramebuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create framebuffer!");
            }
        }
    }


    void kRHISwapchain::ReleaseSwapchain(kRHIContext& contextref) {

        vkDestroyImage(contextref.logicaldevice, m_SwapchainDepthImage, nullptr);
        vkFreeMemory(contextref.logicaldevice, m_SwapchainDepthImageMemory, nullptr);
        vkDestroyImageView(contextref.logicaldevice, m_SwapchainDepthImageView, nullptr);

        for (auto imageView : m_SwapchainColorImageViews) {
            vkDestroyImageView(contextref.logicaldevice, imageView, nullptr);
        }

        for (auto framebuffer : m_SwapchainFramebuffers) {
            vkDestroyFramebuffer(contextref.logicaldevice, framebuffer, nullptr);
        }

        vkDestroySwapchainKHR(contextref.logicaldevice, m_Swapchain, nullptr);
        vkDestroyRenderPass(contextref.logicaldevice, m_RenderPass, nullptr);

        std::cout << "cleanup kSwapchain" << std::endl;
    }

    void kRHISwapchain::RecreateSwapchain(kRHIContext& contextref, VkExtent2D extent) {

        ReleaseSwapchain(contextref);
        CreateSwapchain(contextref, extent);
    }

}