#pragma once

#include "Common.h"

namespace pipeline {

	class kRHIDevice;

	class kRHISwapchain
	{
	public:
		kRHISwapchain();
		virtual ~kRHISwapchain();

		void CreateSwapchain(kRHIDevice& rhidevice, VkExtent2D extent);
		void RecreateSwapchain(kRHIDevice& rhidevice, VkExtent2D extent);
		void ReleaseSwapchain(kRHIDevice& rhidevice);

		VkSwapchainKHR GetSwapchain() { return m_Swapchain; }
		VkRenderPass GetRenderPass() { return m_RenderPass; }
		VkFramebuffer GetFramebuffer(int index) { return m_SwapchainFramebuffers[index]; }

	protected:

		void CreateRenderpass(kRHIDevice& rhidevice);
		void CreateSwapchainColorImageViews(kRHIDevice& rhidevice);
		void CreateSwapchainDepthImageView(kRHIDevice& rhidevice);
		void CreateFramebuffers(kRHIDevice& rhidevice);

		void ChooseSwapchainFormat(kRHIDevice& rhidevice);
		VkSurfaceFormatKHR ChooseSwapSurfaceFormat(kRHIDevice& rhidevice, const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR ChooseSwapPresentMode(kRHIDevice& rhidevice, const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkFormat FindSupportedFormat(kRHIDevice& rhidevice, const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
		VkFormat ChooseDepthFormat(kRHIDevice& rhidevice);

	protected:
		VkRenderPass				m_RenderPass;

		VkSwapchainKHR				m_Swapchain;
		VkExtent2D					m_SwapchainExtent;

		VkPresentModeKHR			m_PresentMode;

		uint32_t					m_SwapchainImageCount;
		VkSurfaceFormatKHR			m_SwapchainSurfaceFormat;
		std::vector<VkImage>		m_SwapchainColorImages;
		std::vector<VkImageView>	m_SwapchainColorImageViews;

		VkFormat					m_SwapchainDepthFormat;
		VkImage						m_SwapchainDepthImage;
		VkDeviceMemory				m_SwapchainDepthImageMemory;
		VkImageView					m_SwapchainDepthImageView;

		std::vector<VkFramebuffer>	m_SwapchainFramebuffers;
	};

}
