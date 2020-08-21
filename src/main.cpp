#include <functional>

#include <OpenGLGraphicsDriver.h>
#include <OpenGLSpriteRenderer.h>
#include <GLFWWindow.h>
#include <AbstractGraphicsDriver.h>
#include <Sprite.h>

void gui();
void renderGui();

std::function<void()> loop;

void main_loop() { loop(); }

// The MAIN function, from here we start the application and run the game loop
int main() {


    GLFWWindow window("Index");

    // Define the viewport dimensions
    auto[width, height] = window.getFrameBufferSize();
    std::unique_ptr<AbstractGraphicsDriver> driver = std::make_unique<OpenGLGraphicsDriver>(width, height);
    OpenGLSpriteRenderer renderer(width, height);

    Sprite s1({0.3, 0.3}, {0.5, 0.5});
    renderer.submit(s1);

    loop = [&] {
        glfwPollEvents();
        gui();
        driver->clearColorBuffer();
        renderer.render();

        renderGui();
        window.update();
    };


#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(main_loop, 0, true);
#else
    while (!window.shouldClose()) { main_loop(); }
#endif

    return 0;
}

void gui(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    bool open = true;
    ImGui::ShowDemoWindow(&open);
    ImGui::Render();
}

void renderGui(){
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
