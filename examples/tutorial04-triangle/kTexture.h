#pragma once



#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


class vkContext;

class kTexture
{
public:
	kTexture() {};
	virtual ~kTexture() {};


	void createTextureImage(vkContext& contextref);
	void createTextureImageView(vkContext& contextref);
	void createTextureSampler(vkContext& contextref);

	VkImage getImage() {return textureImage;};
	VkImageView getImageView() { return textureImageView; };
	VkSampler getImageSampler() { return textureSampler; };

	void cleanupTexture(vkContext& contextref);

protected:

protected:
	VkImage							textureImage;
	VkDeviceMemory					textureImageMemory;
	VkImageView						textureImageView;
	VkSampler						textureSampler;
};

