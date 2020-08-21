#pragma once
#ifdef __EMSCRIPTEN__
#include <GLES3/gl3.h>
#include <emscripten.h>
#else
#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
#endif
#include "Logging.h"
#include "AbstractSpriteRenderer.h"
#include "Sprite.h"

class OpenGLSpriteRenderer : AbstractSpriteRenderer {
public:
    OpenGLSpriteRenderer(float viewportWidth, float viewportHeight);
    ~OpenGLSpriteRenderer();

    void render() const override;
    void submit(Sprite sprite);
private:

    std::vector<float> getBufferData();

    GLuint program;
    std::vector<Sprite> sprites;
    GLuint vao;
    GLuint vbo;
};