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
* [tinygltf](https://github.com/syoyo/tinygltf): Header only C++11 tiny glTF 2.0 library
* [tinyobjloader](https://github.com/tinyobjloader/tinyobjloader): Tiny but powerful single file wavefront obj loader

# Todo

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
  - [ ] NodeClassify
- [ ] RenderModule
- [ ] RenderQueue
- [ ] RenderTarget
- [ ] RHIResource, RHIResourceManager
- [ ] Scene, SGNode, MeshBuilder, Mesh, Material
### model files
- [x] obj
- [x] gltf
- [ ] 3dgs
  - [ ] Load .splat file
  - [ ] projection, drawing quad
  - [ ] sort splat, color blending
  - [ ] optimize: computer shader parser
### samples
- [x] model
- [ ] 3dgs
- [ ] ray tracer

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

<img src=./doc/images/obj.jpg width=450 /> <img src=./doc/images/gltf.jpg width=450 />
