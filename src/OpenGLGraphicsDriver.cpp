#include "OpenGLGraphicsDriver.h"

OpenGLGraphicsDriver::OpenGLGraphicsDriver(const int viewportWidth, const int viewportHeight) :
        AbstractGraphicsDriver(viewportWidth, viewportHeight) {
#ifndef __EMSCRIPTEN__
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback([](GLenum source,
                              GLenum type,
                              GLuint id,
                              GLenum severity,
                              GLsizei length,
                              const GLchar *message,
                              const void *userParam) {
        if (type == GL_DEBUG_TYPE_ERROR) {
            INDEX_ERROR("OpenGL Debug: severity({}). message({})", severity, message);
        } else {
            INDEX_INFO("OpenGL Debug: severity({}). message({})", severity, message);
        }
    }, 0);
#endif

    glViewport(0, 0, viewportWidth, viewportHeight);
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
}

OpenGLGraphicsDriver::~OpenGLGraphicsDriver() {

}

void OpenGLGraphicsDriver::setClearColor(const glm::vec4 color) {
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
}

void OpenGLGraphicsDriver::clearColorBuffer() const {
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLGraphicsDriver::setViewportSize(const int width, const int height) {
    viewportWidth = width;
    viewportHeight = height;
    glViewport(0, 0, viewportWidth, viewportHeight);

}