#pragma once


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class vkContext;

class kRenderpaas
{
public:
	kRenderpaas() {};
	virtual ~kRenderpaas() {}

	void createRenderpass(vkContext& contextref);
	void cleanupRenderpass(vkContext& contextref);

	operator VkRenderPass() const;

protected:

	VkRenderPass	m_RenderPass;
};

