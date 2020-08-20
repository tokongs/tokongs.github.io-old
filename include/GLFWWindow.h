#pragma once
#include <cstdio>
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "AbstractWindow.h"
#include "Logging.h"

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

    GLFWwindow* getRawWindowPtr() const;

private:
    std::unique_ptr<GLFWwindow, DestroyGLFWwindow> window;
};
