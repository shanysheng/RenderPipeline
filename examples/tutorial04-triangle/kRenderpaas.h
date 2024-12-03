#pragma once


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class kContext;

class kRenderpaas
{
public:
	kRenderpaas() {};
	virtual ~kRenderpaas() {}

	void createRenderpass(kContext& contextref, VkFormat format);
	void cleanupRenderpass(kContext& contextref);

	operator VkRenderPass() const;

protected:

	VkRenderPass	m_RenderPass;
};

