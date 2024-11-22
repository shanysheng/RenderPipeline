#include "vkWindow.h"

#include <iostream>


void initWindow(vkContext& contextref) {

    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    contextref.window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}


void createSurface(vkContext& contextref) {
    if (glfwCreateWindowSurface(contextref.instance, contextref.window, nullptr, &contextref.surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}