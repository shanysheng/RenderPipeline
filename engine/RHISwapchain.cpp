#include "RHISwapchain.h"

#include "RHIDevice.h"


namespace pipeline {

    kRHISwapchain::kRHISwapchain() {
    }

    kRHISwapchain::~kRHISwapchain() {
    }


    void kRHISwapchain::CreateSwapchain(kRHIDevice& rhidevice, VkExtent2D extent) {

        m_SwapchainExtent = extent;

        ChooseSwapchainFormat(rhidevice);

        CreateRenderpass(rhidevice);


        std::cout << "swapchain imageCount:" << m_SwapchainImageCount << ", extent width:" << extent.width << ", height:" << extent.height << std::endl;


        VkSwapchainCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = rhidevice.GetSurface();
        createInfo.minImageCount = m_SwapchainImageCount;
        createInfo.imageFormat = m_SwapchainSurfaceFormat.format;
        createInfo.imageColorSpace = m_SwapchainSurfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        QueueFamilyIndices indices = rhidevice.GetQueueFamilyIndices();
        uint32_t queueFamilyIndices[] = { indices.graphicsAndComputeFamily.value(), indices.presentFamily.value() };

        if (indices.graphicsAndComputeFamily != indices.presentFamily) {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        }
        else {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        }

        SwapChainSupportDetails swapChainSupport = rhidevice.GetSwapchainSupportDetails();

        createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = m_PresentMode;
        createInfo.clipped = VK_TRUE;

        if (vkCreateSwapchainKHR(rhidevice.GetLogicDevice(), &createInfo, nullptr, &m_Swapchain) != VK_SUCCESS) {
            throw std::runtime_error("failed to create swap chain!");
        }

        uint32_t imageCount;
        vkGetSwapchainImagesKHR(rhidevice.GetLogicDevice(), m_Swapchain, &imageCount, nullptr);
        m_SwapchainColorImages.resize(imageCount);
        vkGetSwapchainImagesKHR(rhidevice.GetLogicDevice(), m_Swapchain, &imageCount, m_SwapchainColorImages.data());

        CreateSwapchainColorImageViews(rhidevice);
        CreateSwapchainDepthImageView(rhidevice);
        CreateFramebuffers(rhidevice);
    }

    void kRHISwapchain::CreateRenderpass(kRHIDevice& rhidevice) {
        VkAttachmentDescription colorAttachment{};
        colorAttachment.format = m_SwapchainSurfaceFormat.format;
        colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentDescription depthAttachment{};
        depthAttachment.format = m_SwapchainDepthFormat;
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

        if (vkCreateRenderPass(rhidevice.GetLogicDevice(), &renderPassInfo, nullptr, &m_RenderPass) != VK_SUCCESS) {
            throw std::runtime_error("failed to create render pass!");
        }
    }

    void kRHISwapchain::CreateSwapchainColorImageViews(kRHIDevice& rhidevice) {

        m_SwapchainColorImageViews.resize(m_SwapchainColorImages.size());
        for (size_t i = 0; i < m_SwapchainColorImages.size(); i++) {
            m_SwapchainColorImageViews[i] = rhidevice.CreateImageView(m_SwapchainColorImages[i], m_SwapchainSurfaceFormat.format, VK_IMAGE_ASPECT_COLOR_BIT);
        }
    }

    void kRHISwapchain::CreateSwapchainDepthImageView(kRHIDevice& rhidevice) {

        rhidevice.CreateImage(m_SwapchainExtent.width, m_SwapchainExtent.height, m_SwapchainDepthFormat,
                                VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, 
                                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_SwapchainDepthImage, m_SwapchainDepthImageMemory);

        m_SwapchainDepthImageView = rhidevice.CreateImageView(m_SwapchainDepthImage, m_SwapchainDepthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);
    }


    void kRHISwapchain::CreateFramebuffers(kRHIDevice& rhidevice) {

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

            if (vkCreateFramebuffer(rhidevice.GetLogicDevice(), &framebufferInfo, nullptr, &m_SwapchainFramebuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create framebuffer!");
            }
        }
    }


    void kRHISwapchain::ReleaseSwapchain(kRHIDevice& rhidevice) {

        vkDestroyImage(rhidevice.GetLogicDevice(), m_SwapchainDepthImage, nullptr);
        vkFreeMemory(rhidevice.GetLogicDevice(), m_SwapchainDepthImageMemory, nullptr);
        vkDestroyImageView(rhidevice.GetLogicDevice(), m_SwapchainDepthImageView, nullptr);

        for (auto imageView : m_SwapchainColorImageViews) {
            vkDestroyImageView(rhidevice.GetLogicDevice(), imageView, nullptr);
        }

        for (auto framebuffer : m_SwapchainFramebuffers) {
            vkDestroyFramebuffer(rhidevice.GetLogicDevice(), framebuffer, nullptr);
        }

        vkDestroySwapchainKHR(rhidevice.GetLogicDevice(), m_Swapchain, nullptr);
        vkDestroyRenderPass(rhidevice.GetLogicDevice(), m_RenderPass, nullptr);

        std::cout << "cleanup kSwapchain" << std::endl;
    }

    void kRHISwapchain::RecreateSwapchain(kRHIDevice& rhidevice, VkExtent2D extent) {

        ReleaseSwapchain(rhidevice);
        CreateSwapchain(rhidevice, extent);
    }


    VkFormat kRHISwapchain::FindSupportedFormat(kRHIDevice& rhidevice, const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features) {
        for (VkFormat format : candidates) {
            VkFormatProperties props;
            vkGetPhysicalDeviceFormatProperties(rhidevice.GetPhysicalDevice(), format, &props);

            if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
                return format;
            }
            else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
                return format;
            }
        }

        throw std::runtime_error("failed to find supported format!");
    }

    VkFormat kRHISwapchain::ChooseDepthFormat(kRHIDevice& rhidevice) {
        return FindSupportedFormat(rhidevice,
            { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
            VK_IMAGE_TILING_OPTIMAL,
            VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
        );
    }

    VkSurfaceFormatKHR kRHISwapchain::ChooseSwapSurfaceFormat(kRHIDevice& rhidevice, const std::vector<VkSurfaceFormatKHR>& availableFormats) {
        for (const auto& availableFormat : availableFormats) {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                return availableFormat;
            }
        }

        return availableFormats[0];
    }

    VkPresentModeKHR kRHISwapchain::ChooseSwapPresentMode(kRHIDevice& rhidevice, const std::vector<VkPresentModeKHR>& availablePresentModes) {
        for (const auto& availablePresentMode : availablePresentModes) {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
                return availablePresentMode;
            }
        }

        return VK_PRESENT_MODE_FIFO_KHR;
    }

    void kRHISwapchain::ChooseSwapchainFormat(kRHIDevice& rhidevice) {

        SwapChainSupportDetails swapChainSupport = rhidevice.GetSwapchainSupportDetails();

        m_SwapchainImageCount = swapChainSupport.capabilities.minImageCount;
        if (swapChainSupport.capabilities.maxImageCount > 0 && m_SwapchainImageCount > swapChainSupport.capabilities.maxImageCount) {
            m_SwapchainImageCount = swapChainSupport.capabilities.maxImageCount;
        }

        m_PresentMode = ChooseSwapPresentMode(rhidevice, swapChainSupport.presentModes);
        m_SwapchainSurfaceFormat = ChooseSwapSurfaceFormat(rhidevice, swapChainSupport.formats);
        m_SwapchainDepthFormat = ChooseDepthFormat(rhidevice);
    }

}