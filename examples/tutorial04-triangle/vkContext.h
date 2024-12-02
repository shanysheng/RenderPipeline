#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <iostream>
#include <chrono>

#include "vkInstance.h"
#include "vkLayer.h"
#include "vkDevice.h"
#include "vkGraphicsPipeline.h"
#include "vkCommand.h"

#include "kBuffer.h"
#include "kSwapchain.h"
#include "kUniformBuffer.h"

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
	VkQueue						presentQueue;

	kSwapchain					m_Swapchain;



	VkRenderPass					renderPass;
	VkPipelineLayout				pipelineLayout;
	VkPipeline						graphicsPipeline;
	VkDescriptorSetLayout			descriptorSetLayout;
	VkDescriptorPool				descriptorPool;

	std::vector<VkDescriptorSet>	descriptorSets;


	VkCommandPool					commandPool;
	std::vector<VkCommandBuffer>	commandBuffers;

	std::vector<VkSemaphore>		imageAvailableSemaphores;
	std::vector<VkSemaphore>		renderFinishedSemaphores;
	std::vector<VkFence>			inFlightFences;
	uint32_t						currentFrame = 0;

	Model							m_Model;

	std::vector<kUniformBuffer*>	m_UniformBuffers;





	void initContext() {
		createInstance(*this);
		setupDebugMessenger(this->instance);
		createSurface(*this);

		pickPhysicalDevice(*this);
		createLogicalDevice(*this);
		m_Swapchain.createSwapChain(*this);
		m_Swapchain.createImageViews(*this);

		createRenderPass(*this);

		createDescriptorSetLayout();

		createGraphicsPipeline(*this);
		m_Swapchain.createFramebuffers(*this);

		createCommandPool(*this);



		m_Model.Load(*this);

		//createVertexBuffer(*this, vertices.data(), vertices.size());
		//createIndexBuffer(*this, indices.data(), indices.size());
		createUniformBuffers(*this, sizeof(UniformBufferObject));
		createDescriptorPool(*this);
		createDescriptorSets(*this, sizeof(UniformBufferObject));

		createCommandBuffers(*this);
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
		contextref.inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

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
		}
	}


	void createDescriptorSetLayout() {
		VkDescriptorSetLayoutBinding uboLayoutBinding{};
		uboLayoutBinding.binding = 0;
		uboLayoutBinding.descriptorCount = 1;
		uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		uboLayoutBinding.pImmutableSamplers = nullptr;
		uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

		VkDescriptorSetLayoutBinding samplerLayoutBinding{};
		samplerLayoutBinding.binding = 1;
		samplerLayoutBinding.descriptorCount = 1;
		samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		samplerLayoutBinding.pImmutableSamplers = nullptr;
		samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

		std::array<VkDescriptorSetLayoutBinding, 2> bindings = { uboLayoutBinding, samplerLayoutBinding };
		VkDescriptorSetLayoutCreateInfo layoutInfo{};
		layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
		layoutInfo.pBindings = bindings.data();

		if (vkCreateDescriptorSetLayout(logicaldevice, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
			throw std::runtime_error("failed to create descriptor set layout!");
		}
	}


	void createDescriptorPool(vkContext& contextref) {
		std::array<VkDescriptorPoolSize, 2> poolSizes{};
		poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		poolSizes[0].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
		poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		poolSizes[1].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

		VkDescriptorPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
		poolInfo.pPoolSizes = poolSizes.data();
		poolInfo.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

		if (vkCreateDescriptorPool(contextref.logicaldevice, &poolInfo, nullptr, &contextref.descriptorPool) != VK_SUCCESS) {
			throw std::runtime_error("failed to create descriptor pool!");
		}
	}


	void createDescriptorSets(vkContext& contextref, VkDeviceSize bufferSize) {

		std::vector<VkDescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT, contextref.descriptorSetLayout);
		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = contextref.descriptorPool;
		allocInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
		allocInfo.pSetLayouts = layouts.data();

		contextref.descriptorSets.resize(MAX_FRAMES_IN_FLIGHT);
		if (vkAllocateDescriptorSets(contextref.logicaldevice, &allocInfo, contextref.descriptorSets.data()) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate descriptor sets!");
		}

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			VkDescriptorBufferInfo bufferInfo{};
			bufferInfo.buffer = contextref.m_UniformBuffers[i]->getBuffer();
			bufferInfo.offset = 0;
			bufferInfo.range = sizeof(UniformBufferObject);

			VkDescriptorImageInfo imageInfo{};
			imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			imageInfo.imageView = m_Model.getTexture().getImageView();
			imageInfo.sampler = m_Model.getTexture().getImageSampler();

			std::array<VkWriteDescriptorSet, 2> descriptorWrites{};

			descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrites[0].dstSet = contextref.descriptorSets[i];
			descriptorWrites[0].dstBinding = 0;
			descriptorWrites[0].dstArrayElement = 0;
			descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			descriptorWrites[0].descriptorCount = 1;
			descriptorWrites[0].pBufferInfo = &bufferInfo;

			descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrites[1].dstSet = contextref.descriptorSets[i];
			descriptorWrites[1].dstBinding = 1;
			descriptorWrites[1].dstArrayElement = 0;
			descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			descriptorWrites[1].descriptorCount = 1;
			descriptorWrites[1].pImageInfo = &imageInfo;

			vkUpdateDescriptorSets(contextref.logicaldevice, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
		}
	}


	void recordCommandBuffer(vkContext& contextref, uint32_t imageIndex) {
		VkCommandBuffer commandBuffer = contextref.commandBuffers[contextref.currentFrame];

		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
			throw std::runtime_error("failed to begin recording command buffer!");
		}

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = contextref.renderPass;
		renderPassInfo.framebuffer = contextref.m_Swapchain.getFramebuffer(imageIndex);
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = contextref.m_Swapchain.getSwapExtent();

		VkClearValue clearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, contextref.graphicsPipeline);

			VkViewport viewport{};
			viewport.x = 0.0f;
			viewport.y = 0.0f;
			viewport.width = (float)contextref.m_Swapchain.getSwapExtent().width;
			viewport.height = (float)contextref.m_Swapchain.getSwapExtent().height;
			viewport.minDepth = 0.0f;
			viewport.maxDepth = 1.0f;
			vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

			VkRect2D scissor{};
			scissor.offset = { 0, 0 };
			scissor.extent = contextref.m_Swapchain.getSwapExtent();
			vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

			VkBuffer vertexBuffers[] = { contextref.m_Model.getVertexBuffer() };
			VkDeviceSize offsets[] = { 0 };
			vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
			vkCmdBindIndexBuffer(commandBuffer, contextref.m_Model.getIndexBuffer(), 0, VK_INDEX_TYPE_UINT16);
			vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, contextref.pipelineLayout, 0, 1, &contextref.descriptorSets[contextref.currentFrame], 0, nullptr);
			vkCmdDrawIndexed(commandBuffer, contextref.m_Model.getIndiesCount(), 1, 0, 0, 0);

		vkCmdEndRenderPass(commandBuffer);

		if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
			throw std::runtime_error("failed to record command buffer!");
		}
	}


	void createUniformBuffers(vkContext& contextref, VkDeviceSize bufferSize) {

		contextref.m_UniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			kUniformBuffer* puniform = new kUniformBuffer();
			puniform->createUniformBuffers(contextref, bufferSize);
			contextref.m_UniformBuffers[i] = puniform;
		}
	}


	void updateUniformBuffer(uint32_t currentImage) {
		static auto startTime = std::chrono::high_resolution_clock::now();

		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

		UniformBufferObject ubo{};
		ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		ubo.proj = glm::perspective(glm::radians(45.0f), m_Swapchain.getSwapExtent().width / (float)m_Swapchain.getSwapExtent().height, 0.1f, 10.0f);
		ubo.proj[1][1] *= -1;

		memcpy(m_UniformBuffers[currentImage]->getMappedBuffer(), &ubo, sizeof(ubo));
	}


	void cleanContext() {
		m_Swapchain.cleanupSwapChain(*this);

		vkDestroyPipeline(logicaldevice, graphicsPipeline, nullptr);
		vkDestroyPipelineLayout(logicaldevice, pipelineLayout, nullptr);

		vkDestroyRenderPass(logicaldevice, renderPass, nullptr);

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			m_UniformBuffers[i]->cleanupGPUResource(*this);
		}

		vkDestroyDescriptorPool(logicaldevice, descriptorPool, nullptr);

		m_Model.Unload(*this);

		vkDestroyDescriptorSetLayout(logicaldevice, descriptorSetLayout, nullptr);

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			vkDestroySemaphore(logicaldevice, renderFinishedSemaphores[i], nullptr);
			vkDestroySemaphore(logicaldevice, imageAvailableSemaphores[i], nullptr);
			vkDestroyFence(logicaldevice, inFlightFences[i], nullptr);
		}

		vkDestroyCommandPool(logicaldevice, commandPool, nullptr);

		vkDestroyDevice(logicaldevice, nullptr);

		cleanupDebugMessenger(instance);

		vkDestroySurfaceKHR(instance, surface, nullptr);
		vkDestroyInstance(instance, nullptr);

		glfwDestroyWindow(window);

	}


};

