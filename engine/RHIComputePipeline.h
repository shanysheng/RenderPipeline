#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <string>

namespace pipeline {


	class kRHIDevice;

	struct kComputePipelineCreateInfo {
		VkRenderPass render_pass = VK_NULL_HANDLE;

		std::string comp_shader_file;

		VkVertexInputBindingDescription  input_binding;
		std::vector<VkVertexInputAttributeDescription> input_attributes;

		std::vector<VkDescriptorSetLayout> descriptor_set_layouts;
		std::vector<VkPushConstantRange>  push_constant_ranges;
	};

	class kRHIComputePipeline
	{
	public:
		kRHIComputePipeline();
		virtual ~kRHIComputePipeline();

		void CreateGraphicsPipeline(kRHIDevice& rhidevice, kComputePipelineCreateInfo& info);
		void ReleaseGraphicsPipeline(kRHIDevice& rhidevice);

		VkPipeline GetPipeline() { return m_Pipeline; }
		VkPipelineLayout GetPipelineLayout() { return m_PipelineLayout; }

	protected:

		VkPipelineLayout				m_PipelineLayout;
		VkPipeline						m_Pipeline;
	};

}