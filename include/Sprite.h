#pragma once
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
class Sprite {
public:
    explicit Sprite(glm::vec2 position, glm::vec2 size = {10.0f, 10.f});
    Sprite(glm::vec2 position, glm::vec4 color, glm::vec2 size = {10.0f, 10.f});
    ~Sprite();

    glm::vec2 size;
    glm::vec2 position;
    float rotation = 0;
    glm::vec4 color = {0.0f, 1.0f, 0.0f, 1.0f};
};