#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>



#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <array>


#include "kEngine.h"
#include "trangles.h"


const uint32_t WIDTH = 1280;
const uint32_t HEIGHT = 720;


class baseApplication {
public:
    void run() {
        initWindow();
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow* window;
    kEngine     m_Engine;


    void initWindow() {

        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);

        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

        m_Engine.createEngine(window);
    }

    static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
        auto app = reinterpret_cast<baseApplication*>(glfwGetWindowUserPointer(window));
        app->m_Engine.frameChanged();
    }

    void mainLoop() {

        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            m_Engine.drawFrame();
        }

        //vkDeviceWaitIdle(kEngine.logicaldevice);
    }

    void cleanup() {
        m_Engine.cleanEngine();

        glfwDestroyWindow(window);
        glfwTerminate();
    }

};