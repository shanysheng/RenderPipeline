#include "vkInstance.h"


#include <vector>
#include <iostream>
#include "vkLayer.h"

void enumExtension() {

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

std::vector<const char*> getRequiredExtensions() {
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::cout << "required instance extensions:" << glfwExtensionCount << "\n";
    for (size_t i = 0; i < glfwExtensionCount; ++i)
        std::cout << '\t' << (*(glfwExtensions + i)) << "\n";
    std::cout << std::endl;

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    // add validation layer extension
    if (enableValidationLayers) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}

void createInstance(vkContext& contextref) {

    enumExtension();

    // check validation layers
    if (enableValidationLayers && !checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }

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

    auto extensions = getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    // add debug layer when create instance
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();

        populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    }
    else {
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = nullptr;
    }

    createInfo.enabledLayerCount = 0;

    if (vkCreateInstance(&createInfo, nullptr, &contextref.instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}
