// engine01-model.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>



#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>



#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <array>


#include "RenderingEngine.h"


const uint32_t WINDOW_WIDTH = 1280;
const uint32_t WINDOW_HEIGHT = 720;

bool firstMouse = true;
float lastX = WINDOW_WIDTH / 2.0f;
float lastY = WINDOW_HEIGHT / 2.0f;

namespace pipeline {

    struct {
        struct {
            bool left = false;
            bool right = false;
            bool middle = false;
        } buttons;
        glm::vec2 position;
    } mouseState;

    class baseApplication 
    {
    public:
        void run() {
            initWindow();
            mainLoop();
            cleanup();
        }

    private:
        GLFWwindow* window;
        kRenderingEngine m_Engine;


        void initWindow() {

            glfwInit();
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "RenderPipelie, Vulkan, 3dgs rendering", nullptr, nullptr);

            glfwSetWindowUserPointer(window, this);
            glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
            glfwSetCursorPosCallback(window, mouse_pos_callback);
            glfwSetMouseButtonCallback(window, mouse_button_callback);
            glfwSetScrollCallback(window, scroll_callback);

            int width, height;
            glfwGetFramebufferSize(window, &width, &height);

            kWinInfo wininfo;
            wininfo.pwindow = window;
            wininfo.width = width;
            wininfo.height = height;

            m_Engine.Initialize(wininfo);
        }

        static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {

            auto app = reinterpret_cast<baseApplication*>(glfwGetWindowUserPointer(window));
            app->m_Engine.FrameChanged();
        }

        static void mouse_pos_callback(GLFWwindow* window, double x, double y) {

            auto app = reinterpret_cast<baseApplication*>(glfwGetWindowUserPointer(window));

            kCamera& camera = app->m_Engine.GetCamera();

            float dx = (float)mouseState.position.x - (float)x;
            float dy = (float)mouseState.position.y - (float)y;

            bool handled = false;

            if (handled) {
                mouseState.position = glm::vec2((float)x, (float)y);
                return;
            }

            if (mouseState.buttons.left) {
                camera.RotateModel(-dx, -dy);
            }

            if (mouseState.buttons.right) {
                camera.Zoom(dy*0.005f);
            }

            if (mouseState.buttons.middle) {
                camera.Pan(dx * 0.005f, dy * 0.005f);
            }

            mouseState.position = glm::vec2((float)x, (float)y);
        }

        static void mouse_button_callback(GLFWwindow* window, int button, int pressed, int flags) {

            auto app = reinterpret_cast<baseApplication*>(glfwGetWindowUserPointer(window));

            switch (button)
            {
            case GLFW_MOUSE_BUTTON_LEFT: {
                if (pressed == GLFW_PRESS)
                    mouseState.buttons.left = true;
                else
                    mouseState.buttons.left = false;

                break;
            }
            case GLFW_MOUSE_BUTTON_MIDDLE: {
                if (pressed == GLFW_PRESS)
                    mouseState.buttons.middle = true;
                else
                    mouseState.buttons.middle = false;

                break;
            }
            case GLFW_MOUSE_BUTTON_RIGHT: {
                if (pressed == GLFW_PRESS)
                    mouseState.buttons.right = true;
                else
                    mouseState.buttons.right = false;

                break;
            }
            default:
                return;
            }

        }

        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

            auto app = reinterpret_cast<baseApplication*>(glfwGetWindowUserPointer(window));
            app->m_Engine.GetCamera().Zoom( yoffset * 0.5f);
        }

        void mainLoop() {

            while (!glfwWindowShouldClose(window)) {
                glfwPollEvents();
                m_Engine.DoRendering();
                m_Engine.SwapBuffers();
            }
        }

        void cleanup() {
            m_Engine.Finalize();

            glfwDestroyWindow(window);
            glfwTerminate();
        }

    };


}

int main()
{
    std::cout << "Hello pipeline engine World!\n";

    pipeline::baseApplication app;
    app.run();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
