#pragma once

class AbstractSpriteRenderer {
protected:
    AbstractSpriteRenderer(float viewportWidth, float viewportHeight);
    virtual ~AbstractSpriteRenderer() {};
    virtual void render() const = 0;

    float viewportWidth = 1024;
    float viewportHeight = 576;
};
