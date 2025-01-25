#include "RHIDevice.h"
#include "FileManager.h"

namespace pipeline {

    const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    kRHIDevice::kRHIDevice() {
        instance = nullptr;
        physicalDevice = VK_NULL_HANDLE;
    }

    kRHIDevice::~kRHIDevice() {
    
    }

    void kRHIDevice::EnumerateVulkanExtension() {

        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        std::cout << "available extensions:" << extensionCount << "\n";
        for (const auto& extension : extensions) {
            std::cout << '\t' << extension.extensionName << '\n';
        }
        std::cout << std::endl;
    }

    std::vector<const char*> kRHIDevice::GetRequiredExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::cout << "required instance extensions:" << glfwExtensionCount << "\n";
        for (size_t i = 0; i < glfwExtensionCount; ++i)
            std::cout << '\t' << (*(glfwExtensions + i)) << "\n";
        std::cout << std::endl;

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        return extensions;
    }

    void kRHIDevice::CreateDevice(GLFWwindow* pwindow) {

        CreateInstance(pwindow);

        PickPhysicalDevice();
        CreateLogicalDevice();

        CreateCommandPool();
        CreateDescriptorPool();

    }

    void kRHIDevice::ReleaseDevice() {

        vkDestroyDescriptorPool(logicaldevice, descriptorPool, nullptr);
        vkDestroyCommandPool(logicaldevice, commandPool, nullptr);
        vkDestroyDevice(logicaldevice, nullptr);

        vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyInstance(instance, nullptr);

        std::cout << "cleanup kContext" << std::endl;
    }

    void kRHIDevice::CreateInstance(GLFWwindow* pwindow) {

        EnumerateVulkanExtension();

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello vulkan 3dgs";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Render Pipeline";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = GetRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = nullptr;

        createInfo.enabledLayerCount = 0;

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }

        if (glfwCreateWindowSurface(instance, pwindow, nullptr, &surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }


    void kRHIDevice::PickPhysicalDevice() {

        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
        std::cout << "device count:" << deviceCount << std::endl;
        if (deviceCount == 0) {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
        for (const auto& device : devices) {
            if (IsDeviceSuitable(device, surface)) {

                physicalDevice = device;
                m_QueueFamilyIndices = FindQueueFamilies(physicalDevice, surface);
                m_SwapchainDetails = QuerySwapChainSupport(physicalDevice, surface);
                break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE) {
            throw std::runtime_error("failed to find a suitable GPU!");
        }
    }

    void kRHIDevice::CreateLogicalDevice() {

        // queue creation infos for graphic queue and present queue 
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = {
            m_QueueFamilyIndices.graphicsAndComputeFamily.value(),
            m_QueueFamilyIndices.presentFamily.value()
        };

        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{};
        deviceFeatures.samplerAnisotropy = VK_TRUE;

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount =(uint32_t)(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.pEnabledFeatures = &deviceFeatures;
        createInfo.enabledExtensionCount = (uint32_t)(deviceExtensions.size()); // add logical device extensions
        createInfo.ppEnabledExtensionNames = deviceExtensions.data(); 
        createInfo.enabledLayerCount = 0;

        if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &logicaldevice) != VK_SUCCESS) {
            throw std::runtime_error("failed to create logical device!");
        }

        vkGetDeviceQueue(logicaldevice, m_QueueFamilyIndices.graphicsAndComputeFamily.value(), 0, &graphicsQueue);
        vkGetDeviceQueue(logicaldevice, m_QueueFamilyIndices.presentFamily.value(), 0, &presentQueue);
    }

    void kRHIDevice::CreateCommandPool() {

        VkCommandPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        poolInfo.queueFamilyIndex = m_QueueFamilyIndices.graphicsAndComputeFamily.value();

        if (vkCreateCommandPool(logicaldevice, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create command pool!");
        }
    }

    void kRHIDevice::CreateDescriptorPool() {

        std::vector<VkDescriptorPoolSize> pool_sizes = {
            {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 2048},
            {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 64},
            {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 2048},
            {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 64},
            {VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 64},
        };

        VkDescriptorPoolCreateInfo descriptor_pool_info = { VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO };
        descriptor_pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
        descriptor_pool_info.maxSets = 2048;
        descriptor_pool_info.poolSizeCount = pool_sizes.size();
        descriptor_pool_info.pPoolSizes = pool_sizes.data();

        if (vkCreateDescriptorPool(logicaldevice, &descriptor_pool_info, nullptr, &descriptorPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor pool!");
        }
    }

    QueueFamilyIndices  kRHIDevice::FindQueueFamilies(VkPhysicalDevice pphysicalDev, VkSurfaceKHR psurface) {

        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(pphysicalDev, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(pphysicalDev, &queueFamilyCount, queueFamilies.data());

        std::cout << "device queue family properies count:" << queueFamilyCount << std::endl;


        int i = 0;
        for (const auto& queueFamily : queueFamilies) {

            if ((queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) && 
                (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)) {
                indices.graphicsAndComputeFamily = i;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(pphysicalDev, i, psurface, &presentSupport);

            if (presentSupport) 
                indices.presentFamily = i;

            if (indices.isComplete())
                break;

            i++;
        }

        return indices;
    }


    SwapChainSupportDetails  kRHIDevice::QuerySwapChainSupport(VkPhysicalDevice pphysicalDev, VkSurfaceKHR psurface) {
        SwapChainSupportDetails details;

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(pphysicalDev, psurface, &details.capabilities);

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(pphysicalDev, psurface, &formatCount, nullptr);
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(pphysicalDev, psurface, &formatCount, details.formats.data());

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(pphysicalDev, psurface, &presentModeCount, nullptr);
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(pphysicalDev, psurface, &presentModeCount, details.presentModes.data());

        return details;
    }


    bool kRHIDevice::CheckDeviceExtensionSupport(VkPhysicalDevice pphysicaldevice) {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(pphysicaldevice, nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(pphysicaldevice, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());
        for (const auto& extension : availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }

    bool kRHIDevice::IsDeviceSuitable(VkPhysicalDevice pphysicaldevice, VkSurfaceKHR psurface) {

        QueueFamilyIndices indices = FindQueueFamilies(pphysicaldevice, psurface);
        bool extensionsSupported = CheckDeviceExtensionSupport(pphysicaldevice);

        bool swapChainAdequate = false;
        if (extensionsSupported) {
            SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(pphysicaldevice, psurface);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }

        VkPhysicalDeviceFeatures supportedFeatures;
        vkGetPhysicalDeviceFeatures(pphysicaldevice, &supportedFeatures);

        return indices.isComplete() && extensionsSupported && swapChainAdequate && supportedFeatures.samplerAnisotropy;
    }


    uint32_t  kRHIDevice::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(this->physicalDevice, &memProperties);

        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
            if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                return i;
            }
        }

        throw std::runtime_error("failed to find suitable memory type!");
    }


    VkImageView kRHIDevice::CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags) {
        VkImageViewCreateInfo viewInfo{};
        viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        viewInfo.image = image;
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        viewInfo.format = format;
        viewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        viewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        viewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        viewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        viewInfo.subresourceRange.aspectMask = aspectFlags;
        viewInfo.subresourceRange.baseMipLevel = 0;
        viewInfo.subresourceRange.levelCount = 1;
        viewInfo.subresourceRange.baseArrayLayer = 0;
        viewInfo.subresourceRange.layerCount = 1;

        VkImageView imageView;
        if (vkCreateImageView(logicaldevice, &viewInfo, nullptr, &imageView) != VK_SUCCESS) {
            throw std::runtime_error("failed to create image view!");
        }

        return imageView;
    }

    void kRHIDevice::CreateBuffer(VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize size, VkBuffer& buffer, VkDeviceMemory& memory) {

        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        bufferInfo.usage = usageFlags;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateBuffer(logicaldevice, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
            throw std::runtime_error("failed to create buffer!");
        }

        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(logicaldevice, buffer, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, memoryPropertyFlags);

        if (vkAllocateMemory(logicaldevice, &allocInfo, nullptr, &memory) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate buffer memory!");
        }

        vkBindBufferMemory(logicaldevice, buffer, memory, 0);
    }

    VkResult kRHIDevice::CreateBuffer(VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize size, VkBuffer* buffer, VkDeviceMemory* memory, void* data) {

        // Create the buffer handle
        VkBufferCreateInfo bufferCreateInfo{};
        bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferCreateInfo.size = size;
        bufferCreateInfo.usage = usageFlags;
        bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        (vkCreateBuffer(logicaldevice, &bufferCreateInfo, nullptr, buffer));

        // Create the memory backing up the buffer handle
        VkMemoryRequirements memReqs;
        vkGetBufferMemoryRequirements(logicaldevice, *buffer, &memReqs);

        VkMemoryAllocateInfo memAlloc{};
        memAlloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        memAlloc.allocationSize = memReqs.size;
        memAlloc.memoryTypeIndex = FindMemoryType(memReqs.memoryTypeBits, memoryPropertyFlags);


        // If the buffer has VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT set we also need to enable the appropriate flag during allocation
        VkMemoryAllocateFlagsInfoKHR allocFlagsInfo{};
        if (usageFlags & VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT) {
            allocFlagsInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO_KHR;
            allocFlagsInfo.flags = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT_KHR;
            memAlloc.pNext = &allocFlagsInfo;
        }
        (vkAllocateMemory(logicaldevice, &memAlloc, nullptr, memory));

        // If a pointer to the buffer data has been passed, map the buffer and copy over the data
        if (data != nullptr)
        {
            void* mapped;
            (vkMapMemory(logicaldevice, *memory, 0, size, 0, &mapped));
            memcpy(mapped, data, size);
            // If host coherency hasn't been requested, do a manual flush to make writes visible
            if ((memoryPropertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) == 0)
            {
                VkMappedMemoryRange mappedRange{};
                mappedRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
                mappedRange.memory = *memory;
                mappedRange.offset = 0;
                mappedRange.size = size;
                vkFlushMappedMemoryRanges(logicaldevice, 1, &mappedRange);
            }
            vkUnmapMemory(logicaldevice, *memory);
        }

        // Attach the memory to the buffer object
        (vkBindBufferMemory(logicaldevice, *buffer, *memory, 0));

        return VK_SUCCESS;
    }


    VkShaderModule kRHIDevice::CreateShaderModule(const std::string& filename) {

        auto vertShaderCode = kFileManager::LoadFile(filename);

        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = vertShaderCode.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(vertShaderCode.data());

        VkShaderModule shaderModule;
        if (vkCreateShaderModule(logicaldevice, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
            throw std::runtime_error("failed to create shader module!");
        }

        return shaderModule;
    }


    VkCommandBuffer kRHIDevice::BeginSingleTimeCommands() {
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = commandPool;
        allocInfo.commandBufferCount = 1;

        VkCommandBuffer commandBuffer;
        vkAllocateCommandBuffers(logicaldevice, &allocInfo, &commandBuffer);

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(commandBuffer, &beginInfo);

        return commandBuffer;
    }

    void kRHIDevice::EndSingleTimeCommands(VkCommandBuffer commandBuffer) {
        vkEndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
        vkQueueWaitIdle(graphicsQueue);

        vkFreeCommandBuffers(logicaldevice, commandPool, 1, &commandBuffer);
    }

    void kRHIDevice::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
        VkCommandBuffer commandBuffer = BeginSingleTimeCommands();

        VkBufferCopy copyRegion{};
        copyRegion.size = size;
        vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

        EndSingleTimeCommands(commandBuffer);
    }


    void kRHIDevice::CreateImage(uint32_t width, uint32_t height, VkFormat format,
        VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties,
        VkImage& image, VkDeviceMemory& imageMemory) {

        VkImageCreateInfo imageInfo{};
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        imageInfo.extent.width = width;
        imageInfo.extent.height = height;
        imageInfo.extent.depth = 1;
        imageInfo.mipLevels = 1;
        imageInfo.arrayLayers = 1;
        imageInfo.format = format;
        imageInfo.tiling = tiling;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageInfo.usage = usage;
        imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateImage(logicaldevice, &imageInfo, nullptr, &image) != VK_SUCCESS) {
            throw std::runtime_error("failed to create image!");
        }

        VkMemoryRequirements memRequirements;
        vkGetImageMemoryRequirements(logicaldevice, image, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, properties);

        if (vkAllocateMemory(logicaldevice, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate image memory!");
        }

        vkBindImageMemory(logicaldevice, image, imageMemory, 0);
    }


}
