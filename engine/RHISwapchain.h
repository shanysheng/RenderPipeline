#pragma once

#include "Common.h"

namespace pipeline {

	class kRHIContext;

	class kRHISwapchain
	{
	public:
		kRHISwapchain();
		virtual ~kRHISwapchain();

		void createSwapchain(kRHIContext& contextref, VkExtent2D extent);

		void cleanupSwapChain(kRHIContext& contextref);
		void recreateSwapChain(kRHIContext& contextref, VkExtent2D extent);

		VkSwapchainKHR getSwapchain() { return swapChain; }
		VkRenderPass getRenderPass() { return m_RenderPass; }
		VkFramebuffer getFramebuffer(int index) { return swapChainFramebuffers[index]; }

	protected:

		void createRenderpass(kRHIContext& contextref);
		void cleanupRenderpass(kRHIContext& contextref);

		void createFramebuffers(kRHIContext& contextref);
		void createSwapchainImageViews(kRHIContext& contextref);
		void createDepthResources(kRHIContext& contextref);


	protected:
		VkSwapchainKHR				swapChain;
		std::vector<VkImage>		swapChainImages;
		VkFormat					swapChainImageFormat;
		VkExtent2D					swapChainExtent;
		std::vector<VkImageView>	swapChainImageViews;
		std::vector<VkFramebuffer>	swapChainFramebuffers;

		VkRenderPass				m_RenderPass;

		VkImage						depthImage;
		VkFormat					depthFormat;
		VkDeviceMemory				depthImageMemory;
		VkImageView					depthImageView;
	};

}
