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

		m_Context.createContext(m_WinInfo.pwindow);
		m_Swapchain.CreateSwapchain(m_Context, extent);

		kGraphicsPipelineCreateInfo createinfo;
		createinfo.vertex_shader_file = "shaders/model_depth_vert.spv";
		createinfo.frag_shader_file = "shaders/model_depth_frag.spv";
		createinfo.input_binding = Vertex::getBindingDescription();
		createinfo.input_attributes = Vertex::getAttributeDescriptions();
		m_GraphicPipeline.createGraphicsPipeline(m_Context, createinfo);

		m_Model.Load(m_Context);

		createUniformBuffers(sizeof(UniformBufferObject));
		createDescriptorSets(sizeof(UniformBufferObject));

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

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			m_UniformBuffers[i]->cleanupGPUResource(m_Context);
		}

		m_Swapchain.ReleaseSwapchain(m_Context);
		m_GraphicPipeline.cleanupGraphicsPipeline(m_Context);
		m_Context.cleanupContext();

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

		drawFrame();

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

    void kRenderingEngine::UpdateSynClockMillSecondTime() {

    }

    void kRenderingEngine::UpdateFrameIndex() {

    }


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

	void kRenderingEngine::createDescriptorSets(VkDeviceSize bufferSize) {

		std::vector<VkDescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT, m_GraphicPipeline.getDescriptorSetLayout());
		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = m_Context.descriptorPool;
		allocInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
		allocInfo.pSetLayouts = layouts.data();

		descriptorSets.resize(MAX_FRAMES_IN_FLIGHT);
		if (vkAllocateDescriptorSets(m_Context.logicaldevice, &allocInfo, descriptorSets.data()) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate descriptor sets!");
		}

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			VkDescriptorBufferInfo bufferInfo{};
			bufferInfo.buffer = m_UniformBuffers[i]->getBuffer();
			bufferInfo.offset = 0;
			bufferInfo.range = bufferSize;

			VkDescriptorImageInfo imageInfo{};
			imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			imageInfo.imageView = m_Model.getTexture().getImageView();
			imageInfo.sampler = m_Model.getTexture().getImageSampler();

			std::array<VkWriteDescriptorSet, 2> descriptorWrites{};

			descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrites[0].dstSet = descriptorSets[i];
			descriptorWrites[0].dstBinding = 0;
			descriptorWrites[0].dstArrayElement = 0;
			descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			descriptorWrites[0].descriptorCount = 1;
			descriptorWrites[0].pBufferInfo = &bufferInfo;

			descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrites[1].dstSet = descriptorSets[i];
			descriptorWrites[1].dstBinding = 1;
			descriptorWrites[1].dstArrayElement = 0;
			descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			descriptorWrites[1].descriptorCount = 1;
			descriptorWrites[1].pImageInfo = &imageInfo;

			vkUpdateDescriptorSets(m_Context.logicaldevice, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
		}
	}

	void kRenderingEngine::createUniformBuffers(VkDeviceSize bufferSize) {

		m_UniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			kUniformBuffer* puniform = new kUniformBuffer();
			puniform->createUniformBuffers(m_Context, bufferSize);
			m_UniformBuffers[i] = puniform;
		}
	}

	void kRenderingEngine::updateUniformBuffer(uint32_t currentImage) {
		static auto startTime = std::chrono::high_resolution_clock::now();

		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

		UniformBufferObject ubo{};
		ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		ubo.proj = glm::perspective(glm::radians(45.0f), m_WinInfo.width / (float)m_WinInfo.height, 0.1f, 10.0f);
		ubo.proj[1][1] *= -1;

		m_UniformBuffers[currentImage]->updateBuffer(&ubo, sizeof(ubo));
	}

	void kRenderingEngine::recordCommandBuffer(uint32_t imageIndex) {
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
				vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_GraphicPipeline.getPipeline());

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

				VkBuffer vertexBuffers[] = { m_Model.getVertexBuffer() };
				VkDeviceSize offsets[] = { 0 };
				vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
				vkCmdBindIndexBuffer(commandBuffer, m_Model.getIndexBuffer(), 0, VK_INDEX_TYPE_UINT32);
				vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_GraphicPipeline.getPipelineLayout(), 0, 1, &descriptorSets[m_CurrentFrame], 0, nullptr);
				vkCmdDrawIndexed(commandBuffer, m_Model.getIndiesCount(), 1, 0, 0, 0);
			}

			vkCmdEndRenderPass(commandBuffer);
		}

		if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
			throw std::runtime_error("failed to record command buffer!");
		}
	}


	void kRenderingEngine::drawFrame() {

		// Acquire an image from the swap chain
		// Execute commands that draw onto the acquired image
		// Present that image to the screen for presentation, returning it to the swapchain
		//
		// Semaphore
		// 
		// A semaphore is either unsignaled or signaled. It begins life as unsignaled. The way 
		// we use a semaphore to order queue operations is by providing the same semaphore as 
		// a 'signal' semaphore in one queue operation and as a 'wait' semaphore in another 
		// queue operation. For example, lets say we have semaphore S and queue operations A 
		// and B that we want to execute in order. What we tell Vulkan is that operation A will 
		// 'signal' semaphore S when it finishes executing, and operation B will 'wait' on 
		// semaphore S before it begins executing. When operation A finishes, semaphore S 
		// will be signaled, while operation B wont start until S is signaled. After operation 
		// B begins executing, semaphore S is automatically reset back to being unsignaled, 
		// allowing it to be used again.
		// Note that in this code snippet, both calls to vkQueueSubmit() return immediately - 
		// the waiting only happens on the GPU. The CPU continues running without blocking. 
		// To make the CPU wait, we need a different synchronization primitive, Fence.
		//
		// Fence
		//
		// A fence has a similar purpose, in that it is used to synchronize execution, but 
		// it is for ordering the execution on the CPU, otherwise known as the host. Simply 
		// put, if the host needs to know when the GPU has finished something, we use a fence.
		// A concrete example is taking a screenshot. Say we have already done the necessary 
		// work on the GPU. Now need to transfer the image from the GPU over to the host and 
		// then save the memory to a file. We have command buffer A which executes the transfer 
		// and fence F. We submit command buffer A with fence F, then immediately tell the host 
		// to wait for F to signal. This causes the host to block until command buffer A finishes 
		// execution. Thus we are safe to let the host save the file to disk, as the memory 
		// transfer has completed.
		// Unlike the semaphore example, this example does block host execution. This means the 
		// host won't do anything except wait until execution has finished. For this case, we 
		// had to make sure the transfer was complete before we could save the screenshot to disk.


		vkWaitForFences(m_Context.logicaldevice, 1, &m_InFlightFences[m_CurrentFrame], VK_TRUE, UINT64_MAX);

		uint32_t imageIndex;
		VkResult result = vkAcquireNextImageKHR(m_Context.logicaldevice, m_Swapchain.GetSwapchain(), UINT64_MAX, m_ImageAvailableSemaphores[m_CurrentFrame], VK_NULL_HANDLE, &imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR) {
			recreateSwapChain();
			return;
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

			updateUniformBuffer(m_CurrentFrame);
			recordCommandBuffer(imageIndex);

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
			if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
				framebufferResized = false;
				recreateSwapChain();
			}
			else if (result != VK_SUCCESS) {
				throw std::runtime_error("failed to present swap chain image!");
			}
		}

		m_CurrentFrame = (m_CurrentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
	}

	void kRenderingEngine::recreateSwapChain() {
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
