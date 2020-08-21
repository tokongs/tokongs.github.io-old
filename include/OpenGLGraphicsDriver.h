#pragma once
#ifdef __EMSCRIPTEN__
#include <GLES3/gl3.h>
#include <emscripten.h>
#else
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#include "Logging.h"
#include "AbstractGraphicsDriver.h"

class OpenGLGraphicsDriver : public AbstractGraphicsDriver {
public:
    OpenGLGraphicsDriver(const int viewportWidth, const int viewportHeight);
    ~OpenGLGraphicsDriver();

    void setClearColor(const glm::vec4 color) override;
    void clearColorBuffer() const override;
    void setViewportSize(const int width, const int height) override;
};