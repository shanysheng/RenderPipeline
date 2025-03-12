#include "MeshParticles.h"
#include "RHIDevice.h"
#include "Camera.h"
#include "RHIGraphicPipeline.h"

namespace pipeline {

	kMeshParticles::kMeshParticles() {

	}

	kMeshParticles::~kMeshParticles() {

	}

	void kMeshParticles::Load(kRHIDevice& rhidevicet) {

	}

	void kMeshParticles::Unload(kRHIDevice& rhidevice){

	}

	void kMeshParticles::BuildComputeCommandBuffer(VkCommandBuffer commandBuffer, kCamera& camera) {

	}

	void kMeshParticles::UpdateUniformBuffer(kRHIDevice& rhidevice, kCamera& camera) {

	}

	void kMeshParticles::BuildGraphicCommandBuffer(VkCommandBuffer commandBuffer, kCamera& camera) {

	}

	std::vector<VkDescriptorSetLayout> kMeshParticles::PrepareComputeDSLayout(kRHIDevice& rhidevice) {
		return std::vector<VkDescriptorSetLayout> {};
	}

	void kMeshParticles::SetupComputeDescSets(kRHIDevice& rhidevice) {

	}

	void kMeshParticles::CreateComputeComputePipeline(kRHIDevice& rhidevice) {

	}


	std::vector<VkDescriptorSetLayout> kMeshParticles::PrepareRenderingDSLayout(kRHIDevice& rhidevice) {
		return std::vector<VkDescriptorSetLayout> {};
	}

	void kMeshParticles::SetupRenderingDescSets(kRHIDevice& rhidevice) {

	}

	void kMeshParticles::CreateRenderingPipeline(kRHIDevice& rhidevice) {

	}



}

