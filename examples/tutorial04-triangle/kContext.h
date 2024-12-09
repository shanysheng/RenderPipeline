#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <optional>
#include <set>

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsAndComputeFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsAndComputeFamily.has_value() && presentFamily.has_value();
	}
};


struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};



class kContext
{
public:
	kContext() {
		instance = nullptr;
		physicalDevice = VK_NULL_HANDLE;
	}

	virtual ~kContext() {}

	void createContext(GLFWwindow* pwindow);
	void cleanupContext();

	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	VkShaderModule createShaderModule(const std::string& filename);

	void createImage(uint32_t width, uint32_t height, VkFormat format, 
					VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties,
					VkImage& image, VkDeviceMemory& imageMemory);


	VkCommandBuffer beginSingleTimeCommands();
	void endSingleTimeCommands( VkCommandBuffer commandBuffer);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

	uint32_t findMemoryType(kContext& contextref, uint32_t typeFilter, VkMemoryPropertyFlags properties);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice pphysicalDev, VkSurfaceKHR psurface);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice pphysicalDev, VkSurfaceKHR psurface);

	uint32_t getSwapchainImageCount() { return swapchainImageCount; }
	VkPresentModeKHR getPresentMode() { return presentMode; }
	VkSurfaceFormatKHR getSwapchainSurfaceFormat() { return swapchainSurfaceFormat; }
	VkFormat getDepthFormat() { return swapchainDepthFormat; }

protected:
	void createInstance();
	void setupDebugMessenger(VkInstance pinst);
	void createSurface(GLFWwindow* pwindow);
	void pickPhysicalDevice();
	void createLogicalDevice();

	void createCommandPool();
	void createDescriptorPool();

	void chooseSwapchainFormat();
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkFormat chooseDepthFormat();

	void cleanupDebugMessenger(VkInstance pinst);

	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	bool hasStencilComponent(VkFormat format);

	bool checkDeviceExtensionSupport(VkPhysicalDevice pphysicaldevice);
	bool isDeviceSuitable(VkPhysicalDevice pphysicaldevice, VkSurfaceKHR psurface);

public:
	VkSurfaceKHR				surface;
	VkInstance					instance;

	VkPhysicalDevice			physicalDevice;
	VkDevice					logicaldevice;

	VkQueue						graphicsQueue;
	VkQueue						presentQueue;

	VkDescriptorPool			descriptorPool;
	VkCommandPool				commandPool;

protected:
	VkPresentModeKHR			presentMode;
	VkFormat					swapchainDepthFormat;
	VkSurfaceFormatKHR			swapchainSurfaceFormat;
	uint32_t					swapchainImageCount;
};

