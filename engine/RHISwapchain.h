#pragma once

#include "Common.h"

namespace pipeline {

	class kRHIContext;

	class kRHISwapchain
	{
	public:
		kRHISwapchain();
		virtual ~kRHISwapchain();

		void CreateSwapchain(kRHIContext& contextref, VkExtent2D extent);
		void RecreateSwapchain(kRHIContext& contextref, VkExtent2D extent);
		void ReleaseSwapchain(kRHIContext& contextref);

		VkSwapchainKHR GetSwapchain() { return m_Swapchain; }
		VkRenderPass GetRenderPass() { return m_RenderPass; }
		VkFramebuffer GetFramebuffer(int index) { return m_SwapchainFramebuffers[index]; }

	protected:

		void CreateRenderpass(kRHIContext& contextref);
		void CreateSwapchainColorImageViews(kRHIContext& contextref);
		void CreateSwapchainDepthImageView(kRHIContext& contextref);
		void CreateFramebuffers(kRHIContext& contextref);


	protected:
		VkRenderPass				m_RenderPass;

		VkSwapchainKHR				m_Swapchain;
		VkExtent2D					m_SwapchainExtent;

		VkFormat					m_SwapchainColorImageFormat;
		std::vector<VkImage>		m_SwapchainColorImages;
		std::vector<VkImageView>	m_SwapchainColorImageViews;

		VkFormat					m_SwapchainDepthFormat;
		VkImage						m_SwapchainDepthImage;
		VkDeviceMemory				m_SwapchainDepthImageMemory;
		VkImageView					m_SwapchainDepthImageView;

		std::vector<VkFramebuffer>	m_SwapchainFramebuffers;
	};

}
