#include "kEngine.h"
#include "particle.h"

void kEngine::createEngine(GLFWwindow* pwindow) {

	m_pWindow = pwindow;
	lastTime = glfwGetTime();

	int width, height;
	glfwGetFramebufferSize(m_pWindow, &width, &height);
	m_Extent = {
		static_cast<uint32_t>(width),
		static_cast<uint32_t>(height)
	};


	m_Context.createContext(m_pWindow);
	m_Renderpass.createRenderpass(m_Context);
	m_Swapchain.createSwapchain(m_Context, m_Extent, m_Renderpass);

	GraphicsPipelineCreateInfo createinfo;
	createinfo.render_pass = m_Renderpass;
	createinfo.vertex_shader_file = "shaders/particles_vert.spv";
	createinfo.frag_shader_file = "shaders/particles_frag.spv";
	createinfo.input_binding = Particle::getBindingDescription();
	createinfo.input_attributes = Particle::getAttributeDescriptions();
	m_GraphicPipeline.createGraphicsPipeline(m_Context, createinfo);

	ComputePipelineCreateInfo computeCreateInfo;
	m_ComputePipeline.createComputePipeline(m_Context, computeCreateInfo);

	createUniformBuffers(sizeof(particleUniformBufferObject));
	createShaderStorageBuffers();

	createGraphicDescriptorSets(sizeof(particleUniformBufferObject));
	createGraphicCommandBuffers();

	createComputeDescriptorSets(sizeof(particleUniformBufferObject));
	createComputeCommandBuffers();

	createSyncObjects();
}

VkExtent2D kEngine::chooseSwapExtent(GLFWwindow* pwindow, const VkSurfaceCapabilitiesKHR& capabilities) {
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
		return capabilities.currentExtent;
	}
	else {
		int width, height;
		glfwGetFramebufferSize(pwindow, &width, &height);

		VkExtent2D actualExtent = {
			static_cast<uint32_t>(width),
			static_cast<uint32_t>(height)
		};

		actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
		actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

		return actualExtent;
	}
}

void kEngine::createSyncObjects() {
	imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	computeFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);

	inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
	computeInFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

	VkSemaphoreCreateInfo semaphoreInfo{};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	VkFenceCreateInfo fenceInfo{};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		if (vkCreateSemaphore(m_Context.logicaldevice, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
			vkCreateSemaphore(m_Context.logicaldevice, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
			vkCreateFence(m_Context.logicaldevice, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
			throw std::runtime_error("failed to create synchronization objects for a frame!");
		}
		if (vkCreateSemaphore(m_Context.logicaldevice, &semaphoreInfo, nullptr, &computeFinishedSemaphores[i]) != VK_SUCCESS ||
			vkCreateFence(m_Context.logicaldevice, &fenceInfo, nullptr, &computeInFlightFences[i]) != VK_SUCCESS) {
			throw std::runtime_error("failed to create compute synchronization objects for a frame!");
		}
	}
}


void kEngine::createShaderStorageBuffers() {

	const uint32_t WIDTH = 1280;
	const uint32_t HEIGHT = 720;

	// Initialize particles
	std::default_random_engine rndEngine((unsigned)time(nullptr));
	std::uniform_real_distribution<float> rndDist(0.0f, 1.0f);

	// Initial particle positions on a circle
	std::vector<Particle> particles(PARTICLE_COUNT);
	for (auto& particle : particles) {
		// 球坐标生成（保证均匀分布）
		float u = rndDist(rndEngine);
		float v = rndDist(rndEngine);
		float w = rndDist(rndEngine);

		// 半径：立方根变换保证体积均匀分布
		float r = powf(w, 1.0f / 3.0f);  // 等效于 cbrt(w)

		// 角度分布：
		float theta = acos(2.0f * u - 1.0f); // 极角 [0, π]
		float phi = 2.0f * 3.1415926f * v;           // 方位角 [0, 2π)

		// 转换为笛卡尔坐标
		float sinTheta = sin(theta);
		float x = r * sinTheta * cos(phi);
		float y = r * sinTheta * sin(phi);
		float z = r * cos(theta);

		particle.position = glm::vec3(x, y, z);

		// 速度方向沿法线方向（可改为切向或随机方向）
		particle.velocity = glm::normalize(particle.position) * 0.00025f;

		// 颜色保持随机
		particle.color = glm::vec4(rndDist(rndEngine), rndDist(rndEngine), rndDist(rndEngine), 1.0f);
	}

	VkDeviceSize bufferSize = sizeof(Particle) * PARTICLE_COUNT;

	// Copy initial particle data to all storage buffers
	shaderStorageBuffers.resize(MAX_FRAMES_IN_FLIGHT);
	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		shaderStorageBuffers[i].createShaderStorageBuffer(m_Context, (const char*)particles.data(), bufferSize);
	}
}

void kEngine::createUniformBuffers(VkDeviceSize bufferSize) {

	m_UniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		kUniformBuffer* puniform = new kUniformBuffer();
		puniform->createUniformBuffers(m_Context, bufferSize);
		m_UniformBuffers[i] = puniform;
	}
}

void kEngine::updateUniformBuffer(uint32_t currentImage) {

	particleUniformBufferObject ubo{};

	ubo.model = glm::rotate(glm::mat4(1.0f), (float)lastTime * glm::radians(10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	ubo.proj = glm::perspective(glm::radians(45.0f), m_Extent.width / (float)m_Extent.height, 0.1f, 100.0f);
	ubo.proj[1][1] *= -1;

	ubo.deltaTime = deltaTime;
	m_UniformBuffers[currentImage]->updateBuffer(&ubo, sizeof(ubo));
}

void kEngine::createGraphicCommandBuffers() {
	graphicCommandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = m_Context.commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t)graphicCommandBuffers.size();

	if (vkAllocateCommandBuffers(m_Context.logicaldevice, &allocInfo, graphicCommandBuffers.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate command buffers!");
	}
}


void kEngine::createGraphicDescriptorSets(VkDeviceSize bufferSize) {

	std::vector<VkDescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT, m_GraphicPipeline.getDescriptorSetLayout());
	VkDescriptorSetAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = m_Context.descriptorPool;
	allocInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
	allocInfo.pSetLayouts = layouts.data();

	graphicDescriptorSets.resize(MAX_FRAMES_IN_FLIGHT);
	if (vkAllocateDescriptorSets(m_Context.logicaldevice, &allocInfo, graphicDescriptorSets.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate descriptor sets!");
	}

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		VkDescriptorBufferInfo bufferInfo{};
		bufferInfo.buffer = m_UniformBuffers[i]->getBuffer();
		bufferInfo.offset = 0;
		bufferInfo.range = bufferSize;

		std::array<VkWriteDescriptorSet, 1> descriptorWrites{};

		descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[0].dstSet = graphicDescriptorSets[i];
		descriptorWrites[0].dstBinding = 0;
		descriptorWrites[0].dstArrayElement = 0;
		descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrites[0].descriptorCount = 1;
		descriptorWrites[0].pBufferInfo = &bufferInfo;

		vkUpdateDescriptorSets(m_Context.logicaldevice, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
	}
}


void kEngine::recordGraphicCommandBuffer(uint32_t imageIndex) {
	VkCommandBuffer commandBuffer = graphicCommandBuffers[currentFrame];

	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

	if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
		throw std::runtime_error("failed to begin recording command buffer!");
	}

	{
		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = m_Renderpass;
		renderPassInfo.framebuffer = m_Swapchain.getFramebuffer(imageIndex);
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = m_Extent;

		std::array<VkClearValue, 2> clearValues{};
		clearValues[0].color = { {0.0f, 0.0f, 0.0f, 1.0f} };
		clearValues[1].depthStencil = { 1.0f, 0 };

		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();

		vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		{
			VkViewport viewport{};
			viewport.x = 0.0f;
			viewport.y = 0.0f;
			viewport.width = (float)m_Extent.width;
			viewport.height = (float)m_Extent.height;
			viewport.minDepth = 0.0f;
			viewport.maxDepth = 1.0f;
			vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

			VkRect2D scissor{};
			scissor.offset = { 0, 0 };
			scissor.extent = m_Extent;
			vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

			VkDeviceSize offsets[] = { 0 };
			VkBuffer vertexBuffers[] = { shaderStorageBuffers[currentFrame].getBuffer() };
			vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_GraphicPipeline.getPipeline());
			vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_GraphicPipeline.getPipelineLayout(), 0, 1, &graphicDescriptorSets[currentFrame], 0, nullptr);
			vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
			vkCmdDraw(commandBuffer, PARTICLE_COUNT, 1, 0, 0);
		}

		vkCmdEndRenderPass(commandBuffer);
	}

	if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to record command buffer!");
	}
}

void kEngine::createComputeCommandBuffers() {
	computeCommandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = m_Context.commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t)computeCommandBuffers.size();

	if (vkAllocateCommandBuffers(m_Context.logicaldevice, &allocInfo, computeCommandBuffers.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate compute command buffers!");
	}
}

void kEngine::createComputeDescriptorSets(VkDeviceSize bufferSize) {

	std::vector<VkDescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT, m_ComputePipeline.getDescriptorSetLayout());
	VkDescriptorSetAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = m_Context.descriptorPool;
	allocInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
	allocInfo.pSetLayouts = layouts.data();

	computeDescriptorSets.resize(MAX_FRAMES_IN_FLIGHT);
	if (vkAllocateDescriptorSets(m_Context.logicaldevice, &allocInfo, computeDescriptorSets.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate descriptor sets!");
	}

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		VkDescriptorBufferInfo uniformBufferInfo{};
		uniformBufferInfo.buffer = m_UniformBuffers[i]->getBuffer();
		uniformBufferInfo.offset = 0;
		uniformBufferInfo.range = bufferSize;

		std::array<VkWriteDescriptorSet, 3> descriptorWrites{};
		descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[0].dstSet = computeDescriptorSets[i];
		descriptorWrites[0].dstBinding = 0;
		descriptorWrites[0].dstArrayElement = 0;
		descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrites[0].descriptorCount = 1;
		descriptorWrites[0].pBufferInfo = &uniformBufferInfo;

		VkDescriptorBufferInfo storageBufferInfoLastFrame{};
		storageBufferInfoLastFrame.buffer = shaderStorageBuffers[(i - 1) % MAX_FRAMES_IN_FLIGHT].getBuffer();
		storageBufferInfoLastFrame.offset = 0;
		storageBufferInfoLastFrame.range = sizeof(Particle) * PARTICLE_COUNT;

		descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[1].dstSet = computeDescriptorSets[i];
		descriptorWrites[1].dstBinding = 1;
		descriptorWrites[1].dstArrayElement = 0;
		descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		descriptorWrites[1].descriptorCount = 1;
		descriptorWrites[1].pBufferInfo = &storageBufferInfoLastFrame;

		VkDescriptorBufferInfo storageBufferInfoCurrentFrame{};
		storageBufferInfoCurrentFrame.buffer = shaderStorageBuffers[i].getBuffer();
		storageBufferInfoCurrentFrame.offset = 0;
		storageBufferInfoCurrentFrame.range = sizeof(Particle) * PARTICLE_COUNT;

		descriptorWrites[2].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[2].dstSet = computeDescriptorSets[i];
		descriptorWrites[2].dstBinding = 2;
		descriptorWrites[2].dstArrayElement = 0;
		descriptorWrites[2].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		descriptorWrites[2].descriptorCount = 1;
		descriptorWrites[2].pBufferInfo = &storageBufferInfoCurrentFrame;

		vkUpdateDescriptorSets(m_Context.logicaldevice, 3, descriptorWrites.data(), 0, nullptr);
	}
}

void kEngine::recordComputeCommandBuffer(VkCommandBuffer commandBuffer) {

	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

	if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
		throw std::runtime_error("failed to begin recording compute command buffer!");
	}

	vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, m_ComputePipeline.getPipeline());
	vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, m_ComputePipeline.getPipelineLayout(), 0, 1, &computeDescriptorSets[currentFrame], 0, nullptr);
	vkCmdDispatch(commandBuffer, PARTICLE_COUNT / 256, 1, 1);

	if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to record compute command buffer!");
	}
}


void kEngine::drawFrame() {

	// We want to animate the particle system using the last frames time to get smooth, frame-rate independent animation
	double currentTime = glfwGetTime();
	deltaTime = (float)(currentTime - lastTime) * 1000.0f;
	lastTime = currentTime;

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	// Compute submission        
	vkWaitForFences(m_Context.logicaldevice, 1, &computeInFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

	updateUniformBuffer(currentFrame);

	vkResetFences(m_Context.logicaldevice, 1, &computeInFlightFences[currentFrame]);

	vkResetCommandBuffer(computeCommandBuffers[currentFrame], /*VkCommandBufferResetFlagBits*/ 0);
	recordComputeCommandBuffer(computeCommandBuffers[currentFrame]);

	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &computeCommandBuffers[currentFrame];
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = &computeFinishedSemaphores[currentFrame];

	if (vkQueueSubmit(m_Context.computeQueue, 1, &submitInfo, computeInFlightFences[currentFrame]) != VK_SUCCESS) {
		throw std::runtime_error("failed to submit compute command buffer!");
	};

	vkWaitForFences(m_Context.logicaldevice, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

	uint32_t imageIndex;
	VkResult result = vkAcquireNextImageKHR(m_Context.logicaldevice, m_Swapchain.getSwapchain(), UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);
	if (result == VK_ERROR_OUT_OF_DATE_KHR) {
		recreateSwapChain();
		return;
	}
	else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
		throw std::runtime_error("failed to acquire swap chain image!");
	}


	// submit command wait image available semaphore and signal render finished semaphore
	VkSemaphore waitSemaphores[] = { computeFinishedSemaphores[currentFrame], imageAvailableSemaphores[currentFrame] };

	{
		vkResetFences(m_Context.logicaldevice, 1, &inFlightFences[currentFrame]);

		vkResetCommandBuffer(graphicCommandBuffers[currentFrame], /*VkCommandBufferResetFlagBits*/ 0);
		recordGraphicCommandBuffer(imageIndex);

		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_VERTEX_INPUT_BIT, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

		submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.waitSemaphoreCount = 2;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &graphicCommandBuffers[currentFrame];
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = &renderFinishedSemaphores[currentFrame];

		if (vkQueueSubmit(m_Context.graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
			throw std::runtime_error("failed to submit draw command buffer!");
		}
	}

	{
		// present command wait render finished semaphore 
		VkSwapchainKHR swapChains[] = { m_Swapchain.getSwapchain() };

		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = &renderFinishedSemaphores[currentFrame];
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

	currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void kEngine::cleanEngine() {

	vkDeviceWaitIdle(m_Context.logicaldevice);

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		vkDestroySemaphore(m_Context.logicaldevice, renderFinishedSemaphores[i], nullptr);
		vkDestroySemaphore(m_Context.logicaldevice, imageAvailableSemaphores[i], nullptr);
		vkDestroySemaphore(m_Context.logicaldevice, computeFinishedSemaphores[i], nullptr);

		vkDestroyFence(m_Context.logicaldevice, inFlightFences[i], nullptr);
		vkDestroyFence(m_Context.logicaldevice, computeInFlightFences[i], nullptr);
	}

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		shaderStorageBuffers[i].cleanupBuffer(m_Context);
	}

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		m_UniformBuffers[i]->cleanupGPUResource(m_Context);
	}

	m_Swapchain.cleanupSwapChain(m_Context);
	m_GraphicPipeline.cleanupGraphicsPipeline(m_Context);
	m_ComputePipeline.cleanupComputePipeline(m_Context);
	m_Renderpass.cleanupRenderpass(m_Context);
	m_Context.cleanupContext();

}

void kEngine::recreateSwapChain() {
	int width = 0, height = 0;
	glfwGetFramebufferSize(m_pWindow, &width, &height);
	while (width == 0 || height == 0) {
		glfwGetFramebufferSize(m_pWindow, &width, &height);
		glfwWaitEvents();
	}
	vkDeviceWaitIdle(m_Context.logicaldevice);

	VkExtent2D actualExtent = {
		static_cast<uint32_t>(width),
		static_cast<uint32_t>(height)
	};

	m_Swapchain.recreateSwapChain(m_Context, actualExtent, m_Renderpass);
}

