#include "Sprite.h"

Sprite::Sprite(glm::vec2 position, glm::vec2 size)
: position(position), size(size){

}

Sprite::Sprite(glm::vec2 position, glm::vec4 color, glm::vec2 size)
: position(position), size(size), color(color){

}

Sprite::~Sprite() {

}


