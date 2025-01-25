#pragma once
#include "IGPUResource.h"

#include "Common.h"

namespace pipeline {

	class kRHIDevice;

	struct kImageInfo {
        uint32_t m_Width;
		uint32_t m_Height;
		uint32_t m_Components;
		uint32_t m_DataSize;
		uint8_t* m_pData;
	};

	class kRHITexture2D
	{
	public:
		kRHITexture2D() {};
		virtual ~kRHITexture2D() {};

		void CreateTexture(kRHIDevice& rhidevice, const std::string& filename);
		void CreateTextureFromBuffer(kRHIDevice& rhidevice, void* buffer, VkDeviceSize bufferSize, VkFormat format, uint32_t texWidth, uint32_t texHeight);

		void ReleaseTexture(kRHIDevice& rhidevice);

		VkImage GetImage() { return m_TextureImage; };
		VkImageView GetImageView() { return m_TextureImageView; };
		VkSampler GetImageSampler() { return m_TextureSampler; };


	protected:
		void CreateTextureImage(kRHIDevice& rhidevice, const std::string& filename);
		void CreateTextureImageFromBuffer(kRHIDevice& rhidevice, void* buffer, VkDeviceSize bufferSize, VkFormat format, uint32_t texWidth, uint32_t texHeight);

		void CreateTextureImageView(kRHIDevice& rhidevice);
		void CreateTextureSampler(kRHIDevice& rhidevice);

		void CopyBufferToImage(kRHIDevice& rhidevice, VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
		void TransitionImageLayout(kRHIDevice& rhidevice, VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);


	protected:
		VkImage				m_TextureImage;
		VkDeviceMemory		m_TextureImageMemory;

		VkImageView			m_TextureImageView;
		VkSampler			m_TextureSampler;
	};
}