#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <iostream>
#include <chrono>
#include <algorithm>

#include "kBuffer.h"
#include "kSwapchain.h"
#include "kUniformBuffer.h"
#include "kRenderpaas.h"
#include "kContext.h"
#include "kGraphicPipeline.h"
#include "kComputerPipeline.h"

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
// VkPipelineLayout包括VkDescriptorSetLayout和push const 
// VkDescriptorSetLayout描述了通过VkDescriptorSetLayoutBinding描述VkPipelineLayout的Descriptor的布局；
// 一般VkPipeline对应一个VkPipelineLayout，一个VkPipelineLayout对应一个或者多个VkDescriptorSetLayout；
// 
// VkDescriptorSet则是具体绘制过程（一个drawcall）对应的uniform buffer、textrue sampe等信息，通过VkDescriptorSetLayout布局进行穿件；
// 每个drawcall，绑定VkPipeline和对应的VkPipelineLayout，以及具体VkDescriptorSet
// 比如10个不同的模型采用同意个pipeline绘制，则会采用相同的VkPipeline和VkPipelineLayout，
// 已经每个模型各自的VkDescriptorSet，其中包含了各自的sample、uniform buffer、shader storage buffer等特有参数


// 渲染过程是异步的，获取swap chain image，执行command buffer，并把结果写入swap chain image，写入完成后可以进行present
// 这里存在几个问题：
// 1、获取swap chain image可能还在使用，需要等待被使用完；
// 2、执行command buffer，执行完需要告知后续的流程，完成了写入；
// 3、presnet流程的时候，需要等待被告知swap chain image已经写入完成，可以进行呈现；

// 所以分成两个流程：渲染流程和呈现流程；
// 渲染流程需要两个VkSemaphore：
// 1、等待swap chain image获取成功，可以写入的imageAvailableSemaphore
// 2、执行command buffer，渲染结果写入swap chain image完成，告知其他流程的renderFinishedSemaphore
// 呈现流程需要一个VkSemaphore：
// 1、swap chain image渲染结果写入完成，可被呈现renderFinishedSemaphore

// 绘制流程：
// 获取可用的swap chain image index；
// reset command buffer
// 开始记录command buffer（指定render pass、pipeline、image index指定的framebuffer）
// 构建VkSubmitInfo，指定imageAvailableSemaphore和renderFinishedSemaphore，提交执行vkQueueSubmit
// 
// 呈现流程：
// 构建VkPresentInfoKHR，指定renderFinishedSemaphore，vkQueuePresentKHR


const int MAX_FRAMES_IN_FLIGHT = 2;


class kEngine
{
public:
	kEngine() {
		m_pWindow = nullptr;
		currentFrame = 0;
	}

	virtual ~kEngine() {
	}

	void createEngine(GLFWwindow* pwindow);
	void drawFrame();
	void cleanEngine();

	void frameChanged() { framebufferResized = true; }

protected:
	void createSyncObjects();
	void recreateSwapChain();
	VkExtent2D chooseSwapExtent(GLFWwindow* pwindow, const VkSurfaceCapabilitiesKHR& capabilities);

	void createUniformBuffers(VkDeviceSize bufferSize);
	void updateUniformBuffer(uint32_t currentImage);

	void createCommandBuffers();
	//void createDescriptorSets(VkDeviceSize bufferSize);
	void recordCommandBuffer(uint32_t imageIndex);

	void createComputeCommandBuffers();
	void createComputeDescriptorSets(VkDeviceSize bufferSize);
	void recordComputeCommandBuffer(VkCommandBuffer commandBuffer);

	void createShaderStorageBuffers();

protected:

	GLFWwindow*						m_pWindow;

	kContext						m_Context;

	kGraphicPipeline				m_GraphicPipeline;
	kComputePipeline				m_ComputePipeline;

	kSwapchain						m_Swapchain;
	kRenderpaas						m_Renderpass;

	VkExtent2D						m_Extent;
	//Model							m_Model;

	std::vector<kUniformBuffer*>	m_UniformBuffers;

	//std::vector<VkDescriptorSet>	graphicDescriptorSets;
	std::vector<VkCommandBuffer>	graphicCommandBuffers;

	std::vector<VkDescriptorSet>	computeDescriptorSets;
	std::vector<VkCommandBuffer>	computeCommandBuffers;

	std::vector<VkBuffer>			shaderStorageBuffers;
	std::vector<VkDeviceMemory>		shaderStorageBuffersMemory;

	std::vector<VkSemaphore>		imageAvailableSemaphores;
	std::vector<VkSemaphore>		renderFinishedSemaphores;
	std::vector<VkSemaphore>		computeFinishedSemaphores;
	std::vector<VkFence>			inFlightFences;
	std::vector<VkFence>			computeInFlightFences;


	uint32_t						currentFrame = 0;
	float							lastFrameTime = 0.0f;
	double							lastTime = 0.0f;

	bool							framebufferResized = false;
};

