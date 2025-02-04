#include "Model3DGS.h"

namespace pipeline {

    Model3DGS::Model3DGS() {

    }

    Model3DGS::~Model3DGS() {

    }

    VkVertexInputBindingDescription Model3DGS::getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};

        return bindingDescription;
    }

    std::vector<VkVertexInputAttributeDescription> Model3DGS::getAttributeDescriptions() {
        std::vector<VkVertexInputAttributeDescription> attributeDescriptions(3);

        return attributeDescriptions;
    }

    std::vector<VkDescriptorSetLayout> Model3DGS::PrepareDescriptorSetLayout(kRHIDevice& rhidevice) {

        return std::vector<VkDescriptorSetLayout> {};
    }

    std::vector<VkPushConstantRange> Model3DGS::PreparePushConstantRange(kRHIDevice& rhidevice) {

        return std::vector<VkPushConstantRange>{};
    }

    void Model3DGS::Load(kRHIDevice& rhidevicet) {

    }

    void Model3DGS::Unload(kRHIDevice& rhidevice) {

    }

    void Model3DGS::UpdateUniformBuffer(kRHIDevice& rhidevice, uint32_t currentImage) {

    }

    void Model3DGS::BuildCommandBuffer(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, kCamera& camera) {

    }

}