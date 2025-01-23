#pragma once

#include "Common.h"

namespace pipeline {

	class kRHIContext;

	class kRenderpaas
	{
	public:
		kRenderpaas() {};
		virtual ~kRenderpaas() {}

		void createRenderpass(kRHIContext& contextref);
		void cleanupRenderpass(kRHIContext& contextref);

		operator VkRenderPass() const;

	protected:

		VkRenderPass	m_RenderPass;
	};



	class kRHISwapchain
	{
	public:
		kRHISwapchain();
		virtual ~kRHISwapchain();

		void createSwapchain(kRHIContext& contextref, VkExtent2D extent, VkRenderPass renderpass);

		void cleanupSwapChain(kRHIContext& contextref);
		void recreateSwapChain(kRHIContext& contextref, VkExtent2D extent, VkRenderPass renderpass);

		VkSwapchainKHR getSwapchain() { return swapChain; }
		VkFramebuffer getFramebuffer(int index) { return swapChainFramebuffers[index]; }


	protected:
		void createFramebuffers(kRHIContext& contextref, VkRenderPass renderpass);
		void createSwapchainImageViews(kRHIContext& contextref);
		void createDepthResources(kRHIContext& contextref);


	protected:
		VkSwapchainKHR				swapChain;
		std::vector<VkImage>		swapChainImages;
		VkFormat					swapChainImageFormat;
		VkExtent2D					swapChainExtent;
		std::vector<VkImageView>	swapChainImageViews;
		std::vector<VkFramebuffer>	swapChainFramebuffers;


		VkImage						depthImage;
		VkFormat					depthFormat;
		VkDeviceMemory				depthImageMemory;
		VkImageView					depthImageView;
	};



}
