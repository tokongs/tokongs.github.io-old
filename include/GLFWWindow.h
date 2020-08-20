#pragma once
#include <cstdio>
#include <memory>
#include <GLFW/glfw3.h>
#include "AbstractWindow.h"
#include "Logging.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

struct DestroyGLFWwindow {
    void operator()(GLFWwindow* window){
        glfwDestroyWindow(window);
    }
};

class GLFWWindow : AbstractWindow {
public:
    explicit GLFWWindow(std::string title, int width = 1024, int height = 576, bool resizable = false);
    ~GLFWWindow() override;

    bool shouldClose() const override;
    std::tuple<int, int> getFrameBufferSize() const override;
    void close() const override;
    void update() const override;

private:
    void initGui();
    std::unique_ptr<GLFWwindow, DestroyGLFWwindow> window;

};
