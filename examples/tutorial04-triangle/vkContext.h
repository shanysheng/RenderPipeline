#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

class vkContext
{
public:
	vkContext() {
		window = nullptr;
		instance = nullptr;
		physicalDevice = VK_NULL_HANDLE;

	}

	virtual ~vkContext() {

	}

	GLFWwindow*		window;
	VkInstance		instance;

	VkPhysicalDevice	physicalDevice;
	VkDevice			logicaldevice;
	VkQueue				graphicsQueue;

	VkSurfaceKHR		surface;
	VkQueue				presentQueue;

	VkSwapchainKHR				swapChain;
	std::vector<VkImage>		swapChainImages;
	VkFormat					swapChainImageFormat;
	VkExtent2D					swapChainExtent;
	std::vector<VkImageView>	swapChainImageViews;
	std::vector<VkFramebuffer>	swapChainFramebuffers;

	VkRenderPass				renderPass;
	VkPipelineLayout			pipelineLayout;
	VkPipeline					graphicsPipeline;


	VkCommandPool				commandPool;
	VkCommandBuffer				commandBuffer;
};

