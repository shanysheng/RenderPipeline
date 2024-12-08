#pragma once


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <array>


class kContext;

struct ComputePipelineCreateInfo {
	VkRenderPass render_pass = VK_NULL_HANDLE;
	VkVertexInputBindingDescription  input_binding;
	std::array<VkVertexInputAttributeDescription, 3> input_attributes;
};

class kComputePipeline
{
public:
	kComputePipeline() {};
	virtual ~kComputePipeline() {};

	void createComputePipeline(kContext& contextref, ComputePipelineCreateInfo& info);
	void cleanupComputePipeline(kContext& contextref);

	VkPipeline getPipeline() { return computePipeline; }
	VkPipelineLayout getPipelineLayout() { return pipelineLayout; }
	VkDescriptorSetLayout getDescriptorSetLayout() { return descriptorSetLayout; }

protected:
	void createDescriptorSetLayout(kContext& contextref);


protected:
	VkPipelineLayout				pipelineLayout;
	VkDescriptorSetLayout			descriptorSetLayout;
	VkPipeline						computePipeline;
};

