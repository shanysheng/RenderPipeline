#include "RHIGraphicPipeline.h"

#include "RHIDevice.h"
#include "RHIBuffer.h"

#include <iostream>

namespace pipeline {

    kRHIGraphicPipeline::kRHIGraphicPipeline() {};
    kRHIGraphicPipeline::~kRHIGraphicPipeline() {};

    void kRHIGraphicPipeline::CreateGraphicsPipeline(kRHIDevice& rhidevice, kGraphicsPipelineCreateInfo& createinfo) {

        //CreateDescriptorSetLayout(rhidevice);

        std::vector<VkPipelineShaderStageCreateInfo> shaderStages;

        VkShaderModule vertShaderModule = rhidevice.CreateShaderModule(createinfo.vert_shader_file);
        VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
        vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vertShaderStageInfo.module = vertShaderModule;
        vertShaderStageInfo.pName = "main";

        shaderStages.push_back(vertShaderStageInfo);

        VkShaderModule fragShaderModule = rhidevice.CreateShaderModule(createinfo.frag_shader_file);
        VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
        fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        fragShaderStageInfo.module = fragShaderModule;
        fragShaderStageInfo.pName = "main";

        shaderStages.push_back(fragShaderStageInfo);

        VkShaderModule geomShaderModule = VK_NULL_HANDLE;
        if (createinfo.geom_shader_file != "") {

            geomShaderModule = rhidevice.CreateShaderModule(createinfo.geom_shader_file);
            VkPipelineShaderStageCreateInfo geomShaderStageInfo{};
            geomShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            geomShaderStageInfo.stage = VK_SHADER_STAGE_GEOMETRY_BIT;
            geomShaderStageInfo.module = geomShaderModule;
            geomShaderStageInfo.pName = "main";

            shaderStages.push_back(geomShaderStageInfo);
        }


        VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
        vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

        //auto bindingDescription = Vertex::getBindingDescription();
        //auto attributeDescriptions = Vertex::getAttributeDescriptions();

        vertexInputInfo.vertexBindingDescriptionCount = 1;
        vertexInputInfo.pVertexBindingDescriptions = &createinfo.input_binding;
        vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(createinfo.input_attributes.size());
        vertexInputInfo.pVertexAttributeDescriptions = createinfo.input_attributes.data();

        VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
        inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        inputAssembly.topology = createinfo.topology;
        inputAssembly.primitiveRestartEnable = VK_FALSE;

        VkPipelineViewportStateCreateInfo viewportState{};
        viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportState.viewportCount = 1;
        viewportState.scissorCount = 1;

        VkPipelineRasterizationStateCreateInfo rasterizer{};
        rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizer.depthClampEnable = VK_FALSE;
        rasterizer.rasterizerDiscardEnable = VK_FALSE;
        rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
        rasterizer.lineWidth = 1.0f;
        rasterizer.cullMode = VK_CULL_MODE_NONE;
        rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        rasterizer.depthBiasEnable = VK_FALSE;

        VkPipelineMultisampleStateCreateInfo multisampling{};
        multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisampling.sampleShadingEnable = VK_FALSE;
        multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

        VkPipelineDepthStencilStateCreateInfo depthStencil{};
        depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        depthStencil.depthTestEnable = VK_TRUE;
        depthStencil.depthWriteEnable = VK_TRUE;
        depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
        depthStencil.depthBoundsTestEnable = VK_FALSE;
        depthStencil.stencilTestEnable = VK_FALSE;

        VkPipelineColorBlendAttachmentState colorBlendAttachment{};
        colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        //colorBlendAttachment.blendEnable = VK_FALSE;
        colorBlendAttachment.blendEnable = VK_TRUE;
        colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
        colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
        colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
        colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;

        VkPipelineColorBlendStateCreateInfo colorBlending{};
        colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        colorBlending.logicOpEnable = VK_FALSE;
        colorBlending.logicOp = VK_LOGIC_OP_COPY;
        colorBlending.attachmentCount = 1;
        colorBlending.pAttachments = &colorBlendAttachment;
        colorBlending.blendConstants[0] = 0.0f;
        colorBlending.blendConstants[1] = 0.0f;
        colorBlending.blendConstants[2] = 0.0f;
        colorBlending.blendConstants[3] = 0.0f;

        std::vector<VkDynamicState> dynamicStates = {
            VK_DYNAMIC_STATE_VIEWPORT,
            VK_DYNAMIC_STATE_SCISSOR
        };
        VkPipelineDynamicStateCreateInfo dynamicState{};
        dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
        dynamicState.pDynamicStates = dynamicStates.data();

        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = (uint32_t)createinfo.descriptor_set_layouts.size();
        pipelineLayoutInfo.pSetLayouts = createinfo.descriptor_set_layouts.data();
        pipelineLayoutInfo.pushConstantRangeCount = (uint32_t)createinfo.push_constant_ranges.size();
        pipelineLayoutInfo.pPushConstantRanges = createinfo.push_constant_ranges.data();;

        if (vkCreatePipelineLayout(rhidevice.GetLogicDevice(), &pipelineLayoutInfo, nullptr, &m_PipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline layout!");
        }

        VkGraphicsPipelineCreateInfo pipelineInfo{};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineInfo.stageCount = (uint32_t)shaderStages.size();
        pipelineInfo.pStages = shaderStages.data();
        pipelineInfo.pVertexInputState = &vertexInputInfo;
        pipelineInfo.pInputAssemblyState = &inputAssembly;
        pipelineInfo.pViewportState = &viewportState;
        pipelineInfo.pRasterizationState = &rasterizer;
        pipelineInfo.pMultisampleState = &multisampling;
        pipelineInfo.pDepthStencilState = &depthStencil;
        pipelineInfo.pColorBlendState = &colorBlending;
        pipelineInfo.pDynamicState = &dynamicState;
        pipelineInfo.layout = m_PipelineLayout;
        pipelineInfo.renderPass = createinfo.render_pass;
        pipelineInfo.subpass = 0;
        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

        VkResult vkresult = vkCreateGraphicsPipelines(rhidevice.GetLogicDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_Pipeline);
        if (vkresult != VK_SUCCESS) {
            throw std::runtime_error("failed to create graphics pipeline!");
        }

        vkDestroyShaderModule(rhidevice.GetLogicDevice(), fragShaderModule, nullptr);
        vkDestroyShaderModule(rhidevice.GetLogicDevice(), vertShaderModule, nullptr);

        if(geomShaderModule!=VK_NULL_HANDLE)
            vkDestroyShaderModule(rhidevice.GetLogicDevice(), geomShaderModule, nullptr);
    }


    //void kRHIGraphicPipeline::CreateDescriptorSetLayout(kRHIDevice& rhidevice) {

    //    VkDescriptorSetLayoutBinding uboLayoutBinding{};
    //    uboLayoutBinding.binding = 0;
    //    uboLayoutBinding.descriptorCount = 1;
    //    uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    //    uboLayoutBinding.pImmutableSamplers = nullptr;
    //    uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

    //    VkDescriptorSetLayoutBinding samplerLayoutBinding{};
    //    samplerLayoutBinding.binding = 1;
    //    samplerLayoutBinding.descriptorCount = 1;
    //    samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    //    samplerLayoutBinding.pImmutableSamplers = nullptr;
    //    samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

    //    std::array<VkDescriptorSetLayoutBinding, 2> bindings = { uboLayoutBinding, samplerLayoutBinding };

    //    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    //    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    //    layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
    //    layoutInfo.pBindings = bindings.data();

    //    if (vkCreateDescriptorSetLayout(rhidevice.logicaldevice, &layoutInfo, nullptr, &m_DescriptorSetLayout) != VK_SUCCESS) {
    //        throw std::runtime_error("failed to create descriptor set layout!");
    //    }
    //}

    void kRHIGraphicPipeline::ReleaseGraphicsPipeline(kRHIDevice& rhidevice) {

        vkDestroyPipeline(rhidevice.GetLogicDevice(), m_Pipeline, nullptr);
        vkDestroyPipelineLayout(rhidevice.GetLogicDevice(), m_PipelineLayout, nullptr);
        //vkDestroyDescriptorSetLayout(rhidevice.logicaldevice, m_DescriptorSetLayout, nullptr);

        std::cout << "cleanup cleanupGraphicsPipeline" << std::endl;
    }
}

