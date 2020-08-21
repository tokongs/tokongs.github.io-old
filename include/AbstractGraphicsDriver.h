#pragma once
#include <glm/vec4.hpp>

class AbstractGraphicsDriver{
public:
    AbstractGraphicsDriver(const int viewportWidth, const int viewportHeight);
    virtual ~AbstractGraphicsDriver() {};

    virtual void clearColorBuffer() const = 0;
    virtual void setClearColor(const glm::vec4 color) = 0;
    virtual void setViewportSize(const int viewportWidth, const int viewportHeight) = 0;

protected:
    glm::vec4 clearColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    int viewportWidth;
    int viewportHeight;
};