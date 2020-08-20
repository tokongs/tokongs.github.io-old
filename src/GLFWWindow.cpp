#include "GLFWWindow.h"
GLFWWindow::GLFWWindow(std::string title, int width, int height, bool resizable)
: AbstractWindow(std::move(title), width, height, resizable)
{
    glfwSetErrorCallback([](int error, const char* description){
        INDEX_WARN("GLFWError({}): {}", error, description);
    });

    if(!glfwInit()){
        INDEX_ERROR("Failed to initialize GLFW.");
        glfwTerminate();
        return;
    }

    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    INDEX_INFO("Running aginst GLFW {}.{}.{}", major, minor, revision);

#ifdef __EMSCRIPTEN__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
#endif

    window = std::unique_ptr<GLFWwindow, DestroyGLFWwindow>(glfwCreateWindow(width, height, title.c_str(), NULL, NULL));
    if(!window){
        INDEX_ERROR("Failed to create GLFW WINDOW");
    }
    INDEX_INFO("Window was successfully created.");

    glfwMakeContextCurrent(window.get());
    glfwSwapInterval(1);
}

GLFWWindow::~GLFWWindow(){
    glfwTerminate();
    INDEX_INFO("GLFW was terminated");
}

void GLFWWindow::close() const {
    glfwSetWindowShouldClose(window.get(), true);
}

void GLFWWindow::update() const {
    glfwSwapBuffers(window.get());
}

bool GLFWWindow::shouldClose() const {
    return glfwWindowShouldClose(window.get());
}

std::tuple<int, int> GLFWWindow::getFrameBufferSize() const {
    int width, height;
    glfwGetFramebufferSize(window.get(), &width, &height);
    return {width, height};
}

GLFWwindow* GLFWWindow::getRawWindowPtr() const {
    return window.get();
}