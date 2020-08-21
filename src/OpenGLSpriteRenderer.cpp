#include "OpenGLSpriteRenderer.h"

OpenGLSpriteRenderer::OpenGLSpriteRenderer(float viewportWidth, float viewportHeight)
        : AbstractSpriteRenderer(viewportWidth, viewportHeight) {
    const GLchar *vertexShaderSource = "#version 300 es\n"
                                       "layout (location = 0) in vec2 position;\n"
                                       "void main()\n"
                                       "{\n"
                                       "gl_Position = vec4(position.x, position.y, 0.0, 1.0);\n"
                                       "}\0";
    const GLchar *fragmentShaderSource = "#version 300 es\n"
                                         "precision mediump float;\n"
                                         "out vec4 color;\n"
                                         "void main()\n"
                                         "{\n"
                                         "color = vec4(1.0, 0.0, 1.0, 1.0);\n"
                                         "}\n\0";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    program = glCreateProgram();
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);;

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);


    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
}

OpenGLSpriteRenderer::~OpenGLSpriteRenderer() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void OpenGLSpriteRenderer::render() const {

    glUseProgram(program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, sprites.size()*6);
    glBindVertexArray(0);

}

void OpenGLSpriteRenderer::submit(Sprite sprite) {
    sprites.push_back(sprite);
    auto bufferData = getBufferData();

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*bufferData.size(), &bufferData[0], GL_STATIC_DRAW);

    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid *) 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


}

std::vector<float> OpenGLSpriteRenderer::getBufferData() {
    std::vector<float> vertices(sprites.size() * 6 * 2);

    for (auto it = 0; it < sprites.size(); it++) {
        auto sprite = sprites[it];

        //Top left
        vertices[it + 0] = sprite.position.x;
        vertices[it + 1] = sprite.position.y;

        //Top right
        vertices[it + 2] = sprite.position.x + sprite.size.x;
        vertices[it + 3] = sprite.position.x;

        //Bottom right
        vertices[it + 4] = sprite.position.x + sprite.size.x;
        vertices[it + 5] = sprite.position.x + sprite.size.y;

        //Bottom right
        vertices[it + 6] = sprite.position.x + sprite.size.x;
        vertices[it + 7] = sprite.position.x + sprite.size.y;

        //Bottom left
        vertices[it + 8] = sprite.position.x;
        vertices[it + 9] = sprite.position.x + sprite.size.y;

        //Top left
        vertices[it + 10] = sprite.position.x;
        vertices[it + 11] = sprite.position.x;
    }

    return vertices;
}
