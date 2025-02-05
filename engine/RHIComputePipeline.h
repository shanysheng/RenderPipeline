#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <string>

namespace pipeline {


	class kRHIDevice;

	struct kComputePipelineCreateInfo {

	};

	class kRHIComputePipeline
	{
	public:
		kRHIComputePipeline();
		virtual ~kRHIComputePipeline();


	protected:
	};

}