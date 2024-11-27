#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <iostream>
#include <chrono>

#include "vkInstance.h"
#include "vkLayer.h"
#include "vkDevice.h"
#include "vkSwapchain.h"
#include "vkGraphicsPipeline.h"
#include "vkCommand.h"
#include "vkTexture.h"


#include "trangles.h"

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

// VkPipelineLayout，VkPipeline的功能差异
// VkDescriptorSetLayout， VkDescriptorPool和VkDescriptorSet功能差异



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
	VkSurfaceKHR				surface;

	VkPhysicalDevice			physicalDevice;
	VkDevice					logicaldevice;

	VkQueue						graphicsQueue;
	VkQueue						computeQueue;
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


	VkDescriptorSetLayout		computeDescriptorSetLayout;
	VkPipelineLayout			computePipelineLayout;
	VkPipeline					computePipeline;

	VkCommandPool				commandPool;

	std::vector<VkBuffer>		shaderStorageBuffers;
	std::vector<VkDeviceMemory> shaderStorageBuffersMemory;


	std::vector<VkBuffer>			uniformBuffers;
	std::vector<VkDeviceMemory>		uniformBuffersMemory;
	std::vector<void*>				uniformBuffersMapped;


	VkDescriptorPool				descriptorPool;
	std::vector<VkDescriptorSet>	computeDescriptorSets;

	std::vector<VkCommandBuffer>	commandBuffers;
	std::vector<VkCommandBuffer>	computeCommandBuffers;

	std::vector<VkSemaphore>		imageAvailableSemaphores;
	std::vector<VkSemaphore>		renderFinishedSemaphores;
	std::vector<VkSemaphore>		computeFinishedSemaphores;

	std::vector<VkFence>			inFlightFences;
	std::vector<VkFence>			computeInFlightFences;

	uint32_t						currentFrame = 0;


	void initContext() {

		createInstance(*this);
		setupDebugMessenger(this->instance);
		createSurface(*this);

		pickPhysicalDevice(*this);
		createLogicalDevice(*this);

		createSwapChain(*this);
		createImageViews(*this);

		createRenderPass(*this);
		createComputeDescriptorSetLayout();
		createGraphicsPipeline(*this);
		createComputePipeline(*this);
		createFramebuffers(*this);
		createCommandPool(*this);

		createShaderStorageBuffers(*this);

		createUniformBuffers(*this, sizeof(UniformBufferObject));
		createDescriptorPool(*this);
		createComputeDescriptorSets(*this, sizeof(UniformBufferObject));

		createCommandBuffers(*this);
		createComputeCommandBuffers(*this);

		createSyncObjects(*this);
	}

	void createSurface(vkContext& contextref) {
		if (glfwCreateWindowSurface(contextref.instance, contextref.window, nullptr, &contextref.surface) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}
	}

	void createSyncObjects(vkContext& contextref) {
		contextref.imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		contextref.renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		contextref.computeFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		contextref.inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
		contextref.computeInFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

		VkSemaphoreCreateInfo semaphoreInfo{};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo fenceInfo{};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			if (vkCreateSemaphore(contextref.logicaldevice, &semaphoreInfo, nullptr, &contextref.imageAvailableSemaphores[i]) != VK_SUCCESS ||
				vkCreateSemaphore(contextref.logicaldevice, &semaphoreInfo, nullptr, &contextref.renderFinishedSemaphores[i]) != VK_SUCCESS ||
				vkCreateFence(contextref.logicaldevice, &fenceInfo, nullptr, &contextref.inFlightFences[i]) != VK_SUCCESS) {
				throw std::runtime_error("failed to create synchronization objects for a frame!");
			}
			if (vkCreateSemaphore(contextref.logicaldevice, &semaphoreInfo, nullptr, &contextref.computeFinishedSemaphores[i]) != VK_SUCCESS ||
				vkCreateFence(contextref.logicaldevice, &fenceInfo, nullptr, &contextref.computeInFlightFences[i]) != VK_SUCCESS) {
				throw std::runtime_error("failed to create compute synchronization objects for a frame!");
			}
		}
	}


	void createComputeDescriptorSetLayout() {
		std::array<VkDescriptorSetLayoutBinding, 3> layoutBindings{};
		layoutBindings[0].binding = 0;
		layoutBindings[0].descriptorCount = 1;
		layoutBindings[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		layoutBindings[0].pImmutableSamplers = nullptr;
		layoutBindings[0].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

		layoutBindings[1].binding = 1;
		layoutBindings[1].descriptorCount = 1;
		layoutBindings[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		layoutBindings[1].pImmutableSamplers = nullptr;
		layoutBindings[1].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

		layoutBindings[2].binding = 2;
		layoutBindings[2].descriptorCount = 1;
		layoutBindings[2].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		layoutBindings[2].pImmutableSamplers = nullptr;
		layoutBindings[2].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

		VkDescriptorSetLayoutCreateInfo layoutInfo{};
		layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo.bindingCount = 3;
		layoutInfo.pBindings = layoutBindings.data();

		if (vkCreateDescriptorSetLayout(logicaldevice, &layoutInfo, nullptr, &computeDescriptorSetLayout) != VK_SUCCESS) {
			throw std::runtime_error("failed to create compute descriptor set layout!");
		}
	}

	void updateUniformBuffer(uint32_t currentImage, float time_stamp) {


		UniformBufferObject ubo{};
		ubo.deltaTime = time_stamp * 2.0f;

		memcpy(uniformBuffersMapped[currentImage], &ubo, sizeof(ubo));
	}


	void cleanupSwapChain() {
		for (auto framebuffer : swapChainFramebuffers) {
			vkDestroyFramebuffer(logicaldevice, framebuffer, nullptr);
		}

		for (auto imageView : swapChainImageViews) {
			vkDestroyImageView(logicaldevice, imageView, nullptr);
		}

		vkDestroySwapchainKHR(logicaldevice, swapChain, nullptr);
	}


	void cleanContext() {
		cleanupSwapChain();

		vkDestroyPipeline(logicaldevice, graphicsPipeline, nullptr);
		vkDestroyPipelineLayout(logicaldevice, pipelineLayout, nullptr);

		vkDestroyPipeline(logicaldevice, computePipeline, nullptr);
		vkDestroyPipelineLayout(logicaldevice, computePipelineLayout, nullptr);

		vkDestroyRenderPass(logicaldevice, renderPass, nullptr);

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			vkDestroyBuffer(logicaldevice, uniformBuffers[i], nullptr);
			vkFreeMemory(logicaldevice, uniformBuffersMemory[i], nullptr);
		}

		vkDestroyDescriptorPool(logicaldevice, descriptorPool, nullptr);
		vkDestroyDescriptorSetLayout(logicaldevice, computeDescriptorSetLayout, nullptr);

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			vkDestroyBuffer(logicaldevice, shaderStorageBuffers[i], nullptr);
			vkFreeMemory(logicaldevice, shaderStorageBuffersMemory[i], nullptr);
		}

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			vkDestroySemaphore(logicaldevice, renderFinishedSemaphores[i], nullptr);
			vkDestroySemaphore(logicaldevice, imageAvailableSemaphores[i], nullptr);
			vkDestroySemaphore(logicaldevice, computeFinishedSemaphores[i], nullptr);

			vkDestroyFence(logicaldevice, inFlightFences[i], nullptr);
			vkDestroyFence(logicaldevice, computeInFlightFences[i], nullptr);

		}

		vkDestroyCommandPool(logicaldevice, commandPool, nullptr);

		vkDestroyDevice(logicaldevice, nullptr);

		cleanupDebugMessenger(instance);

		vkDestroySurfaceKHR(instance, surface, nullptr);
		vkDestroyInstance(instance, nullptr);

		glfwDestroyWindow(window);

	}

};

