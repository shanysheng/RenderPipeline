#pragma once


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <array>


class kContext;

struct GraphicsPipelineCreateInfo {
	VkRenderPass render_pass = VK_NULL_HANDLE;
	VkVertexInputBindingDescription  input_binding;
	std::array<VkVertexInputAttributeDescription, 2> input_attributes;
};

class kGraphicPipeline
{
public:
	kGraphicPipeline() {};
	virtual ~kGraphicPipeline() {};

	void createGraphicsPipeline(kContext& contextref, GraphicsPipelineCreateInfo& info);
	void cleanupGraphicsPipeline(kContext& contextref);

	VkPipeline getPipeline() { return graphicsPipeline; }
	VkPipelineLayout getPipelineLayout() { return pipelineLayout; }
	//VkDescriptorSetLayout getDescriptorSetLayout() { return descriptorSetLayout; }

protected:
	//void createDescriptorSetLayout(kContext& contextref);


protected:
	VkPipelineLayout				pipelineLayout;
	//VkDescriptorSetLayout			descriptorSetLayout;
	VkPipeline						graphicsPipeline;
};

