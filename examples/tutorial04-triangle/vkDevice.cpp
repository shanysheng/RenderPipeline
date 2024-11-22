#include "vkDevice.h"
#include "vkSwapchain.h"


QueueFamilyIndices findQueueFamilies(VkPhysicalDevice pphysicalDev, VkSurfaceKHR psurface) {
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(pphysicalDev, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(pphysicalDev, &queueFamilyCount, queueFamilies.data());

    std::cout << "device queue family properies count:" << queueFamilyCount << std::endl;
    for (size_t i = 0; i < queueFamilyCount; ++i)
        std::cout << queueFamilies[i].queueFlags << std::endl;
    std::cout << std::endl;

    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(pphysicalDev, i, psurface, &presentSupport);

        if (presentSupport) {
            indices.presentFamily = i;
        }

        if (indices.isComplete()) {
            break;
        }

        i++;
    }

    return indices;
}


bool checkDeviceExtensionSupport(VkPhysicalDevice pphysicaldevice) {
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

bool isDeviceSuitable(VkPhysicalDevice pphysicaldevice, VkSurfaceKHR psurface) {

    QueueFamilyIndices indices = findQueueFamilies(pphysicaldevice, psurface);
    bool extensionsSupported = checkDeviceExtensionSupport(pphysicaldevice);

    bool swapChainAdequate = false;
    if (extensionsSupported) {
        SwapChainSupportDetails swapChainSupport = querySwapChainSupport(pphysicaldevice, psurface);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }

    return indices.isComplete() && extensionsSupported && swapChainAdequate;
}


void pickPhysicalDevice(vkContext& contextref) {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(contextref.instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(contextref.instance, &deviceCount, devices.data());

    std::cout << "device count:" << deviceCount << std::endl;
    for (const auto& device : devices) {
        if (isDeviceSuitable(device, contextref.surface)) {
            contextref.physicalDevice = device;
            break;
        }
    }

    if (contextref.physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}


void createLogicalDevice(vkContext& contextref) {
    QueueFamilyIndices indices = findQueueFamilies(contextref.physicalDevice, contextref.surface);

    // queue creation infos for graphic queue and present queue 
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {
        indices.graphicsFamily.value(),
        indices.presentFamily.value()
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

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();

    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = 0;

    // add logical device extensions
    createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();

    //if (enableValidationLayers) {
    //    createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
    //    createInfo.ppEnabledLayerNames = validationLayers.data();
    //}
    //else 
    {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(contextref.physicalDevice, &createInfo, nullptr, &contextref.logicaldevice) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }

    vkGetDeviceQueue(contextref.logicaldevice, indices.graphicsFamily.value(), 0, &contextref.graphicsQueue);
    vkGetDeviceQueue(contextref.logicaldevice, indices.presentFamily.value(), 0, &contextref.presentQueue);
}

