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


// ����vulkanӦ������Ҫ��windows
// ����vulkan instanceʵ��������ָ������Ҫ��vulkanʵ����չ
// ����window��instance����ȡ����Ҫ��surface����
// ѡ�������豸����
// �����߼��豸���󣬿���ָ���߼��豸����Ҫ����չ�ӿڣ�����swapchain
// �����߼��豸��Ӧ��swapchain��swapchainimage
// ������Ⱦframebuffer��framebuffer��Ҫͨ��image viewȥ����swap chain image


// command pool ���� command buffer
// command buffer ��render pass�� frame buffer�� graphic pipeline
// render pass ָ�� color attachment�Ĳ�����ʽ
// frame bufferָ��swap chain�е�image view -��swap chain��Ӧ��image
// graphic pipelineָ��fixed pipeline�е�״̬��shader module
//

// VkPipelineLayout��VkPipeline�Ĺ��ܲ���
// VkPipelineLayout����VkDescriptorSetLayout��push const 
// VkDescriptorSetLayout������ͨ��VkDescriptorSetLayoutBinding����VkPipelineLayout��Descriptor�Ĳ��֣�
// һ��VkPipeline��Ӧһ��VkPipelineLayout��һ��VkPipelineLayout��Ӧһ�����߶��VkDescriptorSetLayout��
// 
// VkDescriptorSet���Ǿ�����ƹ��̣�һ��drawcall����Ӧ��uniform buffer��textrue sampe����Ϣ��ͨ��VkDescriptorSetLayout���ֽ��д�����
// ÿ��drawcall����VkPipeline�Ͷ�Ӧ��VkPipelineLayout���Լ�����VkDescriptorSet
// ����10����ͬ��ģ�Ͳ���ͬ���pipeline���ƣ���������ͬ��VkPipeline��VkPipelineLayout��
// �Ѿ�ÿ��ģ�͸��Ե�VkDescriptorSet�����а����˸��Ե�sample��uniform buffer��shader storage buffer�����в���


// ��Ⱦ�������첽�ģ���ȡswap chain image��ִ��command buffer�����ѽ��д��swap chain image��д����ɺ���Խ���present
// ������ڼ������⣺
// 1����ȡswap chain image���ܻ���ʹ�ã���Ҫ�ȴ���ʹ���ꣻ
// 2��ִ��command buffer��ִ������Ҫ��֪���������̣������д�룻
// 3��presnet���̵�ʱ����Ҫ�ȴ�����֪swap chain image�Ѿ�д����ɣ����Խ��г��֣�

// ���Էֳ��������̣���Ⱦ���̺ͳ������̣�
// ��Ⱦ������Ҫ����VkSemaphore��
// 1���ȴ�swap chain image��ȡ�ɹ�������д���imageAvailableSemaphore
// 2��ִ��command buffer����Ⱦ���д��swap chain image��ɣ���֪�������̵�renderFinishedSemaphore
// ����������Ҫһ��VkSemaphore��
// 1��swap chain image��Ⱦ���д����ɣ��ɱ�����renderFinishedSemaphore

// �������̣�
// ��ȡ���õ�swap chain image index��
// reset command buffer
// ��ʼ��¼command buffer��ָ��render pass��pipeline��image indexָ����framebuffer��
// ����VkSubmitInfo��ָ��imageAvailableSemaphore��renderFinishedSemaphore���ύִ��vkQueueSubmit
// 
// �������̣�
// ����VkPresentInfoKHR��ָ��renderFinishedSemaphore��vkQueuePresentKHR


const int MAX_FRAMES_IN_FLIGHT = 1;


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

	void createShaderStorageBuffers();
	void createUniformBuffers(VkDeviceSize bufferSize);
	void updateUniformBuffer(uint32_t currentImage);

	void createGraphicCommandBuffers();
	void createGraphicDescriptorSets(VkDeviceSize bufferSize);
	void recordGraphicCommandBuffer(uint32_t imageIndex);

	void createComputeCommandBuffers();
	void createComputeDescriptorSets(VkDeviceSize bufferSize);
	void recordComputeCommandBuffer(VkCommandBuffer commandBuffer);


protected:

	GLFWwindow*						m_pWindow;

	kContext						m_Context;

	kGraphicPipeline				m_GraphicPipeline;
	kComputePipeline				m_ComputePipeline;

	kSwapchain						m_Swapchain;
	kRenderpaas						m_Renderpass;

	VkExtent2D						m_Extent;

	std::vector<kUniformBuffer*>	m_UniformBuffers;
	std::vector<kBuffer>			shaderStorageBuffers;

	std::vector<VkDescriptorSet>	graphicDescriptorSets;
	std::vector<VkCommandBuffer>	graphicCommandBuffers;

	std::vector<VkDescriptorSet>	computeDescriptorSets;
	std::vector<VkCommandBuffer>	computeCommandBuffers;


	std::vector<VkSemaphore>		imageAvailableSemaphores;
	std::vector<VkSemaphore>		renderFinishedSemaphores;
	std::vector<VkFence>			inFlightFences;

	std::vector<VkSemaphore>		computeFinishedSemaphores;
	std::vector<VkFence>			computeInFlightFences;

	uint32_t						currentFrame = 0;
	float							deltaTime = 0.0f;
	double							lastTime = 0.0f;

	bool							framebufferResized = false;
};

