#include "RenderingEngine.h"

#include "Mesh.h"
#include "MeshGltf.h"
#include "MeshObj.h"
#include "Mesh3DGS.h"

namespace pipeline {

	const int MAX_FRAMES_IN_FLIGHT = 1;
    
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
		m_RHIDevice.CreateDevice(m_WinInfo.pwindow, m_WinInfo.width, m_WinInfo.height);


		bool yaxis_up = true;

		switch (1) {
			case 1: {
				//// obj model
				m_pModel = new kMeshObj();
				yaxis_up = true;
				break;
			}
			case 2: {
				/// 3dgs model
				m_pModel = new kMesh3DGS();
				yaxis_up = false;
				break;
			}
			case 3: {
				// gltf model
				m_pModel = new kMeshGltf();
				yaxis_up = false;
				break;
			}
			default: {
				break;
			}
		}

		m_pModel->Load(m_RHIDevice);

		// set camera
		glm::vec3 bbcenter = m_pModel->GetBBoxCenter();
		glm::vec3 bbsize = m_pModel->GetBBoxSize();
		glm::vec3 eyetarget = bbcenter;
		glm::vec3 eyeposition = bbcenter + bbsize;
		glm::vec3 updir = yaxis_up ? glm::vec3(0.0f, 0.0f, 1.0f) : glm::vec3(0.0f, 1.0f, 0.0f);
		m_Camera.LookAt(eyeposition, eyetarget, updir);
		m_Camera.Perspective(60.0f, (float)m_WinInfo.width / (float)m_WinInfo.height, 0.1f, 256.0f);

		CreateCommandBuffers();
		CreateSyncObjects();

        return 1;
    }

    void  kRenderingEngine::Finalize() {

		m_pModel->Unload(m_RHIDevice);

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			vkDestroySemaphore(m_RHIDevice.GetLogicDevice(), m_RenderFinishedSems[i], nullptr);
			vkDestroySemaphore(m_RHIDevice.GetLogicDevice(), m_ImageAvailableSems[i], nullptr);
			vkDestroySemaphore(m_RHIDevice.GetLogicDevice(), m_ComputeFinishedSems[i], nullptr);
		}

		m_RHIDevice.ReleaseDevice();
    }

    int kRenderingEngine::OpenSceneModel(const std::string& SceneModelName, int ActiveSceneGraph ) {
        return 1;
    }

    void kRenderingEngine::CloseSceneModel() {

    }

	void kRenderingEngine::DoRendering() {

		VkCommandBuffer computeCmdBuffer = m_ComputeCommandBuffers[m_CurrentFrame];
		vkResetCommandBuffer(computeCmdBuffer, /*VkCommandBufferResetFlagBits*/ 0);

		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		if (vkBeginCommandBuffer(computeCmdBuffer, &beginInfo) != VK_SUCCESS) {
			throw std::runtime_error("failed to begin recording command buffer!");
		}

		m_pModel->BuildComputeCommandBuffer(computeCmdBuffer, m_Camera);

		vkEndCommandBuffer(computeCmdBuffer);

		// Submit compute commands
		VkSubmitInfo computeSubmitInfo{};
		computeSubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		computeSubmitInfo.commandBufferCount = 1;
		computeSubmitInfo.pCommandBuffers = &computeCmdBuffer;
		computeSubmitInfo.signalSemaphoreCount = 1;
		computeSubmitInfo.pSignalSemaphores = &m_ComputeFinishedSems[m_CurrentFrame];
		if (vkQueueSubmit(m_RHIDevice.GetComputeQueue(), 1, &computeSubmitInfo, VK_NULL_HANDLE) != VK_SUCCESS) {
			throw std::runtime_error("failed to submit draw command buffer!");
		}

		uint32_t imageIndex;
		VkResult result = vkAcquireNextImageKHR(m_RHIDevice.GetLogicDevice(), m_RHIDevice.GetSwapchain(),
												UINT64_MAX, m_ImageAvailableSems[m_CurrentFrame],
												VK_NULL_HANDLE, &imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || m_FramebufferResized) {
			m_FramebufferResized = false;
			RecreateSwapChain();
		}
		else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
			throw std::runtime_error("failed to acquire swap chain image!");
		}

		{
			VkCommandBuffer graphicCmdBuffer = m_GraphicCommandBuffers[m_CurrentFrame];
			vkResetCommandBuffer(graphicCmdBuffer, /*VkCommandBufferResetFlagBits*/ 0);
			BuildCommandBuffer(graphicCmdBuffer, m_RHIDevice.GetFramebuffer(imageIndex));

			// submit command wait image available semaphore and signal render finished semaphore
			VkSemaphore render_waitSems[] = { m_ComputeFinishedSems[m_CurrentFrame], m_ImageAvailableSems[m_CurrentFrame] };
			VkSemaphore render_signalSems[] = { m_RenderFinishedSems[m_CurrentFrame] };

			VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_VERTEX_INPUT_BIT,  VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
			VkSubmitInfo submitInfo{};
			submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submitInfo.waitSemaphoreCount = 2;
			submitInfo.pWaitSemaphores = render_waitSems;
			submitInfo.pWaitDstStageMask = waitStages;
			submitInfo.commandBufferCount = 1;
			submitInfo.pCommandBuffers = &graphicCmdBuffer;
			submitInfo.signalSemaphoreCount = 1;
			submitInfo.pSignalSemaphores = render_signalSems;

			if (vkQueueSubmit(m_RHIDevice.GetGraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS) {
				throw std::runtime_error("failed to submit draw command buffer!");
			}
		}

		{
			// present command wait render finished semaphore 
			VkSwapchainKHR swapChains[] = { m_RHIDevice.GetSwapchain() };
			VkSemaphore present_waitSems[] = { m_RenderFinishedSems[m_CurrentFrame] };

			VkPresentInfoKHR presentInfo{};
			presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
			presentInfo.waitSemaphoreCount = 1;
			presentInfo.pWaitSemaphores = present_waitSems;
			presentInfo.swapchainCount = 1;
			presentInfo.pSwapchains = swapChains;
			presentInfo.pImageIndices = &imageIndex;

			result = vkQueuePresentKHR(m_RHIDevice.GetPresentQueue(), &presentInfo);
		}

		m_CurrentFrame = (m_CurrentFrame + 1) % MAX_FRAMES_IN_FLIGHT;

	}

	void kRenderingEngine::SwapBuffers() {
		vkDeviceWaitIdle(m_RHIDevice.GetLogicDevice());
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

		m_ImageAvailableSems.resize(MAX_FRAMES_IN_FLIGHT);
		m_RenderFinishedSems.resize(MAX_FRAMES_IN_FLIGHT);
		m_ComputeFinishedSems.resize(MAX_FRAMES_IN_FLIGHT);

		VkSemaphoreCreateInfo semaphoreInfo{};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			if (vkCreateSemaphore(m_RHIDevice.GetLogicDevice(), &semaphoreInfo, nullptr, &m_ImageAvailableSems[i]) != VK_SUCCESS ||
				vkCreateSemaphore(m_RHIDevice.GetLogicDevice(), &semaphoreInfo, nullptr, &m_RenderFinishedSems[i]) != VK_SUCCESS ||
				vkCreateSemaphore(m_RHIDevice.GetLogicDevice(), &semaphoreInfo, nullptr, &m_ComputeFinishedSems[i]) != VK_SUCCESS ) {
				throw std::runtime_error("failed to create synchronization objects for a frame!");
			}
		}
	}

	void kRenderingEngine::CreateCommandBuffers() {

		// graphic cmd buffers
		m_GraphicCommandBuffers.resize(MAX_FRAMES_IN_FLIGHT);
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = m_RHIDevice.GetCommandPool();
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = (uint32_t)m_GraphicCommandBuffers.size();
		if (vkAllocateCommandBuffers(m_RHIDevice.GetLogicDevice(), &allocInfo, m_GraphicCommandBuffers.data()) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate command buffers!");
		}

		// compute cmd buffers
		m_ComputeCommandBuffers.resize(MAX_FRAMES_IN_FLIGHT);
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = m_RHIDevice.GetCommandPool();
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = (uint32_t)m_ComputeCommandBuffers.size();
		if (vkAllocateCommandBuffers(m_RHIDevice.GetLogicDevice(), &allocInfo, m_ComputeCommandBuffers.data()) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate compute command buffers!");
		}
	}

	void kRenderingEngine::BuildCommandBuffer(VkCommandBuffer commandBuffer, VkFramebuffer framebuffer) {


		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
			throw std::runtime_error("failed to begin recording command buffer!");
		}

		{
			VkRenderPassBeginInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = m_RHIDevice.GetRenderPass();
			renderPassInfo.framebuffer = framebuffer;
			renderPassInfo.renderArea.offset = { 0, 0 };
			renderPassInfo.renderArea.extent.width = m_WinInfo.width;
			renderPassInfo.renderArea.extent.height = m_WinInfo.height;

			std::array<VkClearValue, 2> clearValues{};
			clearValues[0].color = { {0.1f, 0.1f, 0.1f, 1.0f} };
			clearValues[1].depthStencil = { 1.0f, 0 };

			renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
			renderPassInfo.pClearValues = clearValues.data();

			vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			{
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

				m_pModel->UpdateUniformBuffer(m_RHIDevice, m_Camera);
				m_pModel->BuildGraphicCommandBuffer(commandBuffer, m_Camera);
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
		vkDeviceWaitIdle(m_RHIDevice.GetLogicDevice());

		m_WinInfo.width = width;
		m_WinInfo.height = height;

		VkExtent2D actualExtent = {
			static_cast<uint32_t>(width),
			static_cast<uint32_t>(height)
		};

		m_RHIDevice.RecreateSwapchain(actualExtent);
	}

}
