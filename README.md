# RenderPipeline 
RenderPipeline is an open-source implementation of the book 'Real-Time Graphics Rendering Engine' (《实时图形绘制引擎技术》) framework.

# Table of contents

- [Overview](#Overview)
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

# Implementations

### vulkan
- [x] Device: VkInstance, VkPhysicalDevice, VkDevice, VkQueue
- [x] Swapchain: VkSwapchainKHR, VkImage, VkImageView, VkFramebuffer, VkRenderPass
- [ ] Texture: VkImage, VkImageView, VkDeviceMemory, VkSampler
- [ ] Buffer: VkBuffer, VkDeviceMemory
- [ ] Shader:
- [ ] Graphic Pipeline: VkPipeline, VkPipelineLayout, VkDescriptorSetLayout
- [ ] Computer Pipeline: VkPipeline, VkPipelineLayout, VkDescriptorSetLayout
### framework
- [ ] RenderPipeline
- [ ] PreRender
- [ ] RenderModule
- [ ] GPUManager
### io
- [ ] obj
- [ ] 3dgs
- [ ] gltf


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

