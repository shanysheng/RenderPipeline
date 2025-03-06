#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <string>

namespace pipeline {


	class kRHIDevice;

	struct kComputePipelineCreateInfo {
		std::string comp_shader_file;
		std::vector<VkDescriptorSetLayout> descriptor_set_layouts;
		std::vector<VkPushConstantRange>  push_constant_ranges;
	};

	class kRHIComputePipeline
	{
	public:
		kRHIComputePipeline();
		virtual ~kRHIComputePipeline();

		void CreateComputePipeline(kRHIDevice& rhidevice, kComputePipelineCreateInfo& info);
		void ReleaseComputePipeline(kRHIDevice& rhidevice);

		VkPipeline GetPipeline() { return m_Pipeline; }
		VkPipelineLayout GetPipelineLayout() { return m_PipelineLayout; }

	protected:

		VkPipelineLayout				m_PipelineLayout;
		VkPipeline						m_Pipeline;
	};

}