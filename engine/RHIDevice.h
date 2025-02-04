#pragma once

#include "Common.h"

namespace pipeline {

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


	class kRHIDevice
	{
	public:
		kRHIDevice();
		virtual ~kRHIDevice();

		void CreateDevice(GLFWwindow* pwindow);
		void ReleaseDevice();

		VkSurfaceKHR GetSurface() { return m_Surface; }
		VkDevice GetLogicDevice() { return m_Logicaldevice; }
		VkPhysicalDevice GetPhysicalDevice() { return m_PhysicalDevice; }
		VkDescriptorPool GetDescriptorPool() { return m_DescriptorPool; }
		VkQueue GetGraphicsQueue() { return m_GraphicsQueue; }
		VkQueue GetPresentQueue() { return m_PresentQueue; }
		VkCommandPool GetCommandPool() { return m_CommandPool; }

		/**
		* Create a buffer
		*
		* @param image
		* @param format
		* @param aspectFlags
		*
		* @return VK_SUCCESS if
		*/
		void CreateBuffer( VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize size, VkBuffer& buffer, VkDeviceMemory& memory);


		/**
		* Create a buffer
		*
		* @param image
		* @param format
		* @param aspectFlags
		*
		* @return VK_SUCCESS if
		*/
		VkResult CreateBuffer(VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize size, VkBuffer* buffer, VkDeviceMemory* memory, void* data = nullptr);


		/**
		* Create a image view
		*
		* @param image 
		* @param format 
		* @param aspectFlags 
		*
		* @return VK_SUCCESS if
		*/
		VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

		/**
		* Create a shader  module
		*
		* @param image
		* @param format
		* @param aspectFlags
		*
		* @return VK_SUCCESS if
		*/
		VkShaderModule CreateShaderModule(const std::string& filename);

		/**
		* Create a image
		*
		* @param image
		* @param format
		* @param aspectFlags
		*
		* @return VK_SUCCESS if
		*/
		void CreateImage(uint32_t width, uint32_t height, VkFormat format,
							VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties,
							VkImage& image, VkDeviceMemory& imageMemory);


		VkCommandBuffer BeginSingleTimeCommands();
		void EndSingleTimeCommands(VkCommandBuffer commandBuffer);
		void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);


		const QueueFamilyIndices GetQueueFamilyIndices()const { return m_QueueFamilyIndices; }
		const SwapChainSupportDetails GetSwapchainSupportDetails() const { return m_SwapchainDetails; }

	protected:
		void CreateInstance(GLFWwindow* pwindow);

		void PickPhysicalDevice();
		
		void CreateLogicalDevice();
		void CreateCommandPool();
		void CreateDescriptorPool();


		void EnumerateVulkanExtension();
		std::vector<const char*> GetRequiredExtensions();

		void CreateDebugMessenger(VkInstance pinst);
		void ReleaseDebugMessenger(VkInstance pinst);
		void InitDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		bool CheckValidationLayerSupport();


		uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

		bool CheckDeviceExtensionSupport(VkPhysicalDevice pphysicaldevice);
		bool IsDeviceSuitable(VkPhysicalDevice pphysicaldevice, VkSurfaceKHR psurface);

		QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice pphysicalDev, VkSurfaceKHR psurface);
		SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice pphysicalDev, VkSurfaceKHR psurface);


	protected:
		VkSurfaceKHR				m_Surface;
		VkInstance					m_Instance;
		VkPhysicalDevice			m_PhysicalDevice;
		VkDevice					m_Logicaldevice;

		VkQueue						m_GraphicsQueue;
		VkQueue						m_PresentQueue;

		VkDescriptorPool			m_DescriptorPool;
		VkCommandPool				m_CommandPool;

		QueueFamilyIndices			m_QueueFamilyIndices;
		SwapChainSupportDetails		m_SwapchainDetails;
	};

}
