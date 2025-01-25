# RenderPipeline 
RenderPipeline is an open-source implementation of the book 'Real-Time Graphics Rendering Engine' (《实时图形绘制引擎技术》) framework.

# Table of contents

- [Overview](#Overview)
- [Resource](#Resource)
- [Implementations](#implementations)
- [Architecture](#Architecture)
- - [RenderEngine](#RenderEngine)
- - [RenderUnit](#RenderUnit)
- - [PreRender](#PreRender)
- - [RenderPipeline](#RenderPipeline)
- [Samples](#Samples)

# Overview
* graphic: vulkan
* framework: render pipeline

# Resource
* [vulkan](https://github.com/SaschaWillems/Vulkan): C++ examples for the Vulkan graphics API.
* [vulkan tutorial](https://github.com/Overv/VulkanTutorial): Tutorial for the Vulkan graphics and compute API.
* [vulkan 3dgs](https://github.com/jaesung-cs/vkgs): Vulkan-based Gaussian Splatting viewer.

# Implementations

### vulkan
- [x] Device: VkInstance, VkPhysicalDevice, VkDevice, VkQueue
- [x] Swapchain: VkSwapchainKHR, VkImage, VkImageView, VkFramebuffer, VkRenderPass
- [x] Texture: VkImage, VkImageView, VkDeviceMemory, VkSampler
- [x] Buffer: VkBuffer, VkDeviceMemory
- [x] Graphic Pipeline: VkPipeline, VkPipelineLayout, VkDescriptorSetLayout
- [ ] Computer Pipeline: VkPipeline, VkPipelineLayout, VkDescriptorSetLayout
### framework
- [ ] RenderPipeline
- [ ] PreRender
- [ ] RenderModule
- [ ] GPUManager
### io
- [x] obj
- [ ] 3dgs
- [ ] gltf
### samples
- [x] model
- [ ] 3dgs



# Architecture

## RenderEngine
<img src=./doc/images/renderengine.jpg  /><br>

## RenderUnit
<img src=./doc/images/renderunit.jpg  /><br>

## PreRender
<img src=./doc/images/prerender.jpg  /><br>

## RenderPipeline
<img src=./doc/images/renderpipeline.jpg  /><br>


# Samples

