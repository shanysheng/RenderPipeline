#pragma once



#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

class kContext;

class kTexture
{
public:
	kTexture() {};
	virtual ~kTexture() {};

	void createTexture(kContext& contextref, const std::string& filename);

	VkImage getImage() {return textureImage;};
	VkImageView getImageView() { return textureImageView; };
	VkSampler getImageSampler() { return textureSampler; };

	void cleanupTexture(kContext& contextref);

protected:
	void createTextureImage(kContext& contextref, const std::string& filename);
	void createTextureImageView(kContext& contextref);
	void createTextureSampler(kContext& contextref);

protected:
	VkImage							textureImage;
	VkDeviceMemory					textureImageMemory;
	VkImageView						textureImageView;
	VkSampler						textureSampler;
};

