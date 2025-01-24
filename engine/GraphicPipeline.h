#pragma once


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <array>
#include <string>

namespace pipeline {


	class kRHIContext;

	struct kGraphicsPipelineCreateInfo {
		VkRenderPass render_pass = VK_NULL_HANDLE;
		std::string vertex_shader_file;
		std::string frag_shader_file;
		VkVertexInputBindingDescription  input_binding;
		std::array<VkVertexInputAttributeDescription, 3> input_attributes;
	};

	class kGraphicPipeline
	{
	public:
		kGraphicPipeline() {};
		virtual ~kGraphicPipeline() {};

		void createGraphicsPipeline(kRHIContext& contextref, kGraphicsPipelineCreateInfo& info);
		void cleanupGraphicsPipeline(kRHIContext& contextref);

		VkPipeline getPipeline() { return graphicsPipeline; }
		VkPipelineLayout getPipelineLayout() { return pipelineLayout; }
		VkDescriptorSetLayout getDescriptorSetLayout() { return descriptorSetLayout; }

	protected:
		void createDescriptorSetLayout(kRHIContext& contextref);


	protected:
		VkPipelineLayout				pipelineLayout;
		VkDescriptorSetLayout			descriptorSetLayout;
		VkPipeline						graphicsPipeline;
	};
}


