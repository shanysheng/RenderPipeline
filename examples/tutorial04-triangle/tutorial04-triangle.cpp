// tutorial01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

#include "vkLayer.h"
#include "vkDevice.h"
#include "vkSwapchain.h"
#include "vkGraphicsPipeline.h"
#include "vkCommand.h"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const int MAX_FRAMES_IN_FLIGHT = 2;


GLFWwindow* window = nullptr;
VkInstance instance = nullptr;


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


void initWindow() {

    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}


void createInstance() {

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

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}

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

void initVulkan() {

    createInstance();
    setupDebugMessenger(instance);
    createSurface(instance, window);

    pickPhysicalDevice(instance);
    createLogicalDevice();
    createSwapChain(window, physicalDevice, logicaldevice);
    createImageViews(logicaldevice);

    createRenderPass(logicaldevice, swapChainImageFormat);
    createGraphicsPipeline(logicaldevice);
    createFramebuffers(logicaldevice, renderPass);

    //createCommandPool();
    //createCommandBuffer();
}

void mainLoop() {

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void cleanup() {
    //vkDestroyCommandPool(logicaldevice, commandPool, nullptr);

    for (auto framebuffer : swapChainFramebuffers) {
        vkDestroyFramebuffer(logicaldevice, framebuffer, nullptr);
    }

    vkDestroyPipeline(logicaldevice, graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(logicaldevice, pipelineLayout, nullptr);
    vkDestroyRenderPass(logicaldevice, renderPass, nullptr);

    for (auto imageView : swapChainImageViews) {
        vkDestroyImageView(logicaldevice, imageView, nullptr);
    }

    vkDestroySwapchainKHR(logicaldevice, swapChain, nullptr);
    vkDestroyDevice(logicaldevice, nullptr);

    cleanupDebugMessenger(instance);
    //cleanupSurface(instance, logicaldevice);

    vkDestroySurfaceKHR(instance, surface, nullptr);
    vkDestroyInstance(instance, nullptr);

    glfwDestroyWindow(window);

    glfwTerminate();
}

int main()
{
    std::cout << "Hello vulkan world!\n";

    enumExtension();

    initWindow();
    initVulkan();
    mainLoop();
    cleanup();

}
