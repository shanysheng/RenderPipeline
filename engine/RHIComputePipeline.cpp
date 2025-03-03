#include "RHIComputePipeline.h"


#include "RHIDevice.h"
#include "RHIBuffer.h"

#include <iostream>

namespace pipeline {

	kRHIComputePipeline::kRHIComputePipeline() {
        m_PipelineLayout = nullptr;
        m_Pipeline = nullptr;
	}

	kRHIComputePipeline::~kRHIComputePipeline() {

	}

	void kRHIComputePipeline::CreateGraphicsPipeline(kRHIDevice& rhidevice, kComputePipelineCreateInfo& info) 
	{
        VkShaderModule computeShaderModule = rhidevice.CreateShaderModule(info.comp_shader_file);

        VkPipelineShaderStageCreateInfo computeShaderStageInfo{};
        computeShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        computeShaderStageInfo.stage = VK_SHADER_STAGE_COMPUTE_BIT;
        computeShaderStageInfo.module = computeShaderModule;
        computeShaderStageInfo.pName = "main";

        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = info.descriptor_set_layouts.size();
        pipelineLayoutInfo.pSetLayouts = info.descriptor_set_layouts.data();

        if (vkCreatePipelineLayout(rhidevice.GetLogicDevice(), &pipelineLayoutInfo, nullptr, &m_PipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create compute pipeline layout!");
        }

        VkComputePipelineCreateInfo pipelineInfo{};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
        pipelineInfo.layout = m_PipelineLayout;
        pipelineInfo.stage = computeShaderStageInfo;

        if (vkCreateComputePipelines(rhidevice.GetLogicDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_Pipeline) != VK_SUCCESS) {
            throw std::runtime_error("failed to create compute pipeline!");
        }

        vkDestroyShaderModule(rhidevice.GetLogicDevice(), computeShaderModule, nullptr);
	}

	void kRHIComputePipeline::ReleaseGraphicsPipeline(kRHIDevice& rhidevice) 
	{
        vkDestroyPipeline(rhidevice.GetLogicDevice(), m_Pipeline, nullptr);
        vkDestroyPipelineLayout(rhidevice.GetLogicDevice(), m_PipelineLayout, nullptr);
	}

}	