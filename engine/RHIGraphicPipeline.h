#pragma once


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <string>

namespace pipeline {


	class kRHIDevice;

	struct kGraphicsPipelineCreateInfo {
		VkRenderPass render_pass = VK_NULL_HANDLE;
		std::vector<VkDescriptorSetLayout> descriptor_set_layouts;

		std::string vertex_shader_file;
		std::string frag_shader_file;
		
		VkVertexInputBindingDescription  input_binding;
		std::vector<VkVertexInputAttributeDescription> input_attributes;
	};

	class kRHIGraphicPipeline
	{
	public:
		kRHIGraphicPipeline();
		virtual ~kRHIGraphicPipeline();

		void CreateGraphicsPipeline(kRHIDevice& rhidevice, kGraphicsPipelineCreateInfo& info);
		void ReleaseGraphicsPipeline(kRHIDevice& rhidevice);

		VkPipeline GetPipeline() { return m_Pipeline; }
		VkPipelineLayout GetPipelineLayout() { return m_PipelineLayout; }
		//VkDescriptorSetLayout GetDescriptorSetLayout() { return m_DescriptorSetLayout; }

	protected:
		//void CreateDescriptorSetLayout(kRHIDevice& rhidevice);

	protected:
		VkPipelineLayout				m_PipelineLayout;
		//VkDescriptorSetLayout			m_DescriptorSetLayout;
		VkPipeline						m_Pipeline;
	};
}


