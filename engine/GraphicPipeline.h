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
		kGraphicPipeline();
		virtual ~kGraphicPipeline();

		void CreateGraphicsPipeline(kRHIContext& contextref, kGraphicsPipelineCreateInfo& info);
		void ReleaseGraphicsPipeline(kRHIContext& contextref);

		VkPipeline GetPipeline() { return m_GraphicsPipeline; }
		VkPipelineLayout GetPipelineLayout() { return m_PipelineLayout; }
		VkDescriptorSetLayout GetDescriptorSetLayout() { return m_DescriptorSetLayout; }

	protected:
		void CreateDescriptorSetLayout(kRHIContext& contextref);

	protected:
		VkPipelineLayout				m_PipelineLayout;
		VkDescriptorSetLayout			m_DescriptorSetLayout;
		VkPipeline						m_GraphicsPipeline;
	};
}


