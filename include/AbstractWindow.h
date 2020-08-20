#pragma once
#include <string>
#include <tuple>

class AbstractWindow{

public:
    AbstractWindow(std::string title, int width, int height, bool resizable);
    virtual ~AbstractWindow() {};

    virtual bool shouldClose() const = 0;
    virtual void close() const = 0;
    virtual std::tuple<int, int> getFrameBufferSize() const = 0;
    virtual void update() const = 0;

protected:
    int width;
    int height;
    bool resizable;
    const std::string title;
};
