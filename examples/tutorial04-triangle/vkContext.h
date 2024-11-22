#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

// 创建vulkan应用所需要的windows
// 创建vulkan instance实例，可以指定所需要的vulkan实例扩展
// 根据window和instance，获取所需要的surface对象；
// 选择物理设备对象
// 创建逻辑设备对象，可以指定逻辑设备所需要的扩展接口，例如swapchain
// 构建逻辑设备对应的swapchain、swapchainimage
// 构建渲染framebuffer，framebuffer需要通过image view去操作swap chain image


// command pool 包含 command buffer
// command buffer 绑定render pass， frame buffer， graphic pipeline
// render pass 指定 color attachment的操作方式
// frame buffer指定swap chain中的image view -》swap chain对应的image
// graphic pipeline指定fixed pipeline中的状态和shader module
//

const int MAX_FRAMES_IN_FLIGHT = 2;


class vkContext
{
public:
	vkContext() {
		window = nullptr;
		instance = nullptr;
		physicalDevice = VK_NULL_HANDLE;
		currentFrame = 0;
	}

	virtual ~vkContext() {

	}

	GLFWwindow*					window;
	VkInstance					instance;

	VkPhysicalDevice			physicalDevice;
	VkDevice					logicaldevice;
	VkQueue						graphicsQueue;

	VkSurfaceKHR				surface;
	VkQueue						presentQueue;

	VkSwapchainKHR				swapChain;
	std::vector<VkImage>		swapChainImages;
	VkFormat					swapChainImageFormat;
	VkExtent2D					swapChainExtent;
	std::vector<VkImageView>	swapChainImageViews;
	std::vector<VkFramebuffer>	swapChainFramebuffers;

	VkRenderPass				renderPass;
	VkPipelineLayout			pipelineLayout;
	VkPipeline					graphicsPipeline;


	VkCommandPool					commandPool;
	std::vector<VkCommandBuffer>	commandBuffers;

	std::vector<VkSemaphore>		imageAvailableSemaphores;
	std::vector<VkSemaphore>		renderFinishedSemaphores;
	std::vector<VkFence>			inFlightFences;
	uint32_t						currentFrame = 0;
};

