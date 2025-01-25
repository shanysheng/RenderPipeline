#include "RenderingEngine.h"

namespace pipeline {

	const int MAX_FRAMES_IN_FLIGHT = 2;
    
    kRenderingEngine::kRenderingEngine(void) {
		m_CurrentFrame = 0;
    }

    kRenderingEngine::~kRenderingEngine(void) {

    }


    int kRenderingEngine::Configure(const std::string& ConfigFileName) {
		OnConfigure();

        return 1;
    }

    int kRenderingEngine::Initialize(const kWinInfo& wininfo) {

		m_WinInfo = wininfo;

		VkExtent2D extent = { m_WinInfo.width, m_WinInfo.height };

		m_Context.CreateDevice(m_WinInfo.pwindow);
		m_Swapchain.CreateSwapchain(m_Context, extent);

		VkDescriptorSetLayout descr_set_layout = m_Model.PrepareDescriptorSetLayout(m_Context);

		kGraphicsPipelineCreateInfo createinfo;
		createinfo.descriptor_set_layout = descr_set_layout;
		createinfo.vertex_shader_file = "shaders/model_depth_vert.spv";
		createinfo.frag_shader_file = "shaders/model_depth_frag.spv";
		createinfo.input_binding = ModelObj::Vertex::getBindingDescription();
		createinfo.input_attributes = ModelObj::Vertex::getAttributeDescriptions();

		m_GraphicPipeline.CreateGraphicsPipeline(m_Context, createinfo);

		m_Model.Load(m_Context);

		CreateCommandBuffers();
		CreateSyncObjects();

        return 1;
    }

    void  kRenderingEngine::Finalize() {

		m_Model.Unload(m_Context);

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			vkDestroySemaphore(m_Context.logicaldevice, m_RenderFinishedSemaphores[i], nullptr);
			vkDestroySemaphore(m_Context.logicaldevice, m_ImageAvailableSemaphores[i], nullptr);
			vkDestroyFence(m_Context.logicaldevice, m_InFlightFences[i], nullptr);
		}


		m_Swapchain.ReleaseSwapchain(m_Context);
		m_GraphicPipeline.ReleaseGraphicsPipeline(m_Context);
		m_Context.ReleaseDevice();

    }

    int kRenderingEngine::OpenSceneModel(const std::string& SceneModelName, int ActiveSceneGraph ) {
        return 1;
    }

    void kRenderingEngine::CloseSceneModel() {

    }

    void kRenderingEngine::SetRenderTraverseRoot(const std::vector<kSGNode*>& roots) {

    }

    void kRenderingEngine::SetCamera(kCamera& Camera) {

    }

    void kRenderingEngine::GetCamera(kCamera& Camera) {

    }


	void kRenderingEngine::ClearScreen(float r, float g, float b, float a) {

	}

	void kRenderingEngine::DoRendering() {

		vkWaitForFences(m_Context.logicaldevice, 1, &m_InFlightFences[m_CurrentFrame], VK_TRUE, UINT64_MAX);

		uint32_t imageIndex;
		VkResult result = vkAcquireNextImageKHR(m_Context.logicaldevice, m_Swapchain.GetSwapchain(),
												UINT64_MAX, m_ImageAvailableSemaphores[m_CurrentFrame],
												VK_NULL_HANDLE, &imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || m_FramebufferResized) {
			m_FramebufferResized = false;
			RecreateSwapChain();
		}
		else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
			throw std::runtime_error("failed to acquire swap chain image!");
		}

		// submit command wait image available semaphore and signal render finished semaphore
		VkSemaphore signalSemaphores[] = { m_RenderFinishedSemaphores[m_CurrentFrame] };
		VkSemaphore waitSemaphores[] = { m_ImageAvailableSemaphores[m_CurrentFrame] };

		{
			vkResetFences(m_Context.logicaldevice, 1, &m_InFlightFences[m_CurrentFrame]);
			vkResetCommandBuffer(m_CommandBuffers[m_CurrentFrame], /*VkCommandBufferResetFlagBits*/ 0);

			BuildCommandBuffer(imageIndex);

			VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
			VkSubmitInfo submitInfo{};
			submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submitInfo.waitSemaphoreCount = 1;
			submitInfo.pWaitSemaphores = waitSemaphores;
			submitInfo.pWaitDstStageMask = waitStages;
			submitInfo.commandBufferCount = 1;
			submitInfo.pCommandBuffers = &m_CommandBuffers[m_CurrentFrame];
			submitInfo.signalSemaphoreCount = 1;
			submitInfo.pSignalSemaphores = signalSemaphores;

			if (vkQueueSubmit(m_Context.graphicsQueue, 1, &submitInfo, m_InFlightFences[m_CurrentFrame]) != VK_SUCCESS) {
				throw std::runtime_error("failed to submit draw command buffer!");
			}
		}


		{
			// present command wait render finished semaphore 
			VkSwapchainKHR swapChains[] = { m_Swapchain.GetSwapchain() };

			VkPresentInfoKHR presentInfo{};
			presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
			presentInfo.waitSemaphoreCount = 1;
			presentInfo.pWaitSemaphores = signalSemaphores;
			presentInfo.swapchainCount = 1;
			presentInfo.pSwapchains = swapChains;
			presentInfo.pImageIndices = &imageIndex;

			result = vkQueuePresentKHR(m_Context.presentQueue, &presentInfo);
		}

		m_CurrentFrame = (m_CurrentFrame + 1) % MAX_FRAMES_IN_FLIGHT;

	}

	void kRenderingEngine::SwapBuffers() {

	}


    int kRenderingEngine::RegisterPreRenderPrototypes() {
        return 1;
    }

    int kRenderingEngine::RegisterRenderPipelinePrototypes() {
        return 1;
    }

    // user override functions
    int kRenderingEngine::OnConfigure() { return 0; }
    int kRenderingEngine::OnRegisterPreRenderPrototypes() { return 0; }
    int kRenderingEngine::OnRegisterRenderPipelinePrototypes() { return 0; }


	void kRenderingEngine::CreateSyncObjects() {

		m_ImageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		m_RenderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		m_InFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

		VkSemaphoreCreateInfo semaphoreInfo{};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo fenceInfo{};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			if (vkCreateSemaphore(m_Context.logicaldevice, &semaphoreInfo, nullptr, &m_ImageAvailableSemaphores[i]) != VK_SUCCESS ||
				vkCreateSemaphore(m_Context.logicaldevice, &semaphoreInfo, nullptr, &m_RenderFinishedSemaphores[i]) != VK_SUCCESS ||
				vkCreateFence(m_Context.logicaldevice, &fenceInfo, nullptr, &m_InFlightFences[i]) != VK_SUCCESS) {
				throw std::runtime_error("failed to create synchronization objects for a frame!");
			}
		}
	}

	void kRenderingEngine::CreateCommandBuffers() {
		m_CommandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = m_Context.commandPool;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = (uint32_t)m_CommandBuffers.size();

		if (vkAllocateCommandBuffers(m_Context.logicaldevice, &allocInfo, m_CommandBuffers.data()) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate command buffers!");
		}
	}

	void kRenderingEngine::BuildCommandBuffer(uint32_t imageIndex) {
		VkCommandBuffer commandBuffer = m_CommandBuffers[m_CurrentFrame];

		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
			throw std::runtime_error("failed to begin recording command buffer!");
		}

		{
			VkRenderPassBeginInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = m_Swapchain.GetRenderPass();
			renderPassInfo.framebuffer = m_Swapchain.GetFramebuffer(imageIndex);
			renderPassInfo.renderArea.offset = { 0, 0 };
			renderPassInfo.renderArea.extent.width = m_WinInfo.width;
			renderPassInfo.renderArea.extent.height = m_WinInfo.height;

			std::array<VkClearValue, 2> clearValues{};
			clearValues[0].color = { {0.0f, 0.0f, 0.0f, 1.0f} };
			clearValues[1].depthStencil = { 1.0f, 0 };

			renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
			renderPassInfo.pClearValues = clearValues.data();

			vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			{
				vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_GraphicPipeline.GetPipeline());

				VkViewport viewport{};
				viewport.x = 0.0f;
				viewport.y = 0.0f;
				viewport.width = (float)m_WinInfo.width;
				viewport.height = (float)m_WinInfo.height;
				viewport.minDepth = 0.0f;
				viewport.maxDepth = 1.0f;
				vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

				VkRect2D scissor{};
				scissor.offset = { 0, 0 };
				scissor.extent.width = m_WinInfo.width;
				scissor.extent.height = m_WinInfo.height;
				vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

				m_Model.UpdateUniformBuffer(m_Context, m_CurrentFrame);
				m_Model.BuildCommandBuffer(commandBuffer, m_GraphicPipeline.GetPipelineLayout());
			}

			vkCmdEndRenderPass(commandBuffer);
		}

		if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
			throw std::runtime_error("failed to record command buffer!");
		}
	}

	void kRenderingEngine::RecreateSwapChain() {
		int width = 0, height = 0;
		glfwGetFramebufferSize(m_WinInfo.pwindow, &width, &height);
		while (width == 0 || height == 0) {
			glfwGetFramebufferSize(m_WinInfo.pwindow, &width, &height);
			glfwWaitEvents();
		}
		vkDeviceWaitIdle(m_Context.logicaldevice);

		m_WinInfo.width = width;
		m_WinInfo.height = height;

		VkExtent2D actualExtent = {
			static_cast<uint32_t>(width),
			static_cast<uint32_t>(height)
		};

		m_Swapchain.RecreateSwapchain(m_Context, actualExtent);
	}

}
