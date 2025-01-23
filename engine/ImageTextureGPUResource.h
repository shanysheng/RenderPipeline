#pragma once
#include "IGPUResource.h"

#include "Common.h"

namespace pipeline {

	class kRHIContext;

	struct kImageInfo {
        uint32_t m_Width;
		uint32_t m_Height;
		uint32_t m_Components;
		uint32_t m_DataSize;
		uint8_t* m_pData;
	};

	class kTexture
	{
	public:
		kTexture() {};
		virtual ~kTexture() {};

		void createTexture(kRHIContext& contextref, const std::string& filename);

		VkImage getImage() { return textureImage; };
		VkImageView getImageView() { return textureImageView; };
		VkSampler getImageSampler() { return textureSampler; };

		void cleanupTexture(kRHIContext& contextref);

	protected:
		void createTextureImage(kRHIContext& contextref, const std::string& filename);
		void createTextureImageView(kRHIContext& contextref);
		void createTextureSampler(kRHIContext& contextref);

	protected:
		VkImage							textureImage;
		VkDeviceMemory					textureImageMemory;
		VkImageView						textureImageView;
		VkSampler						textureSampler;
	};
}