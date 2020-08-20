

#include <cstdio>
#include <functional>

// GLEW
#ifdef __EMSCRIPTEN__
#include <GLES3/gl3.h>
#include <emscripten.h>
#else
#define GLEW_STATIC
#include <GL/glew.h>
#endif

// GLFW
#include <GLFW/glfw3.h>
#include <cstring>
#include <GLFWWindow.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Shaders
const GLchar* vertexShaderSource = "#version 300 es\n"
                                   "layout (location = 0) in vec3 position;\n"
                                   "void main()\n"
                                   "{\n"
                                   "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
                                   "}\0";
const GLchar* fragmentShaderSource = "#version 300 es\n"
                                     "precision mediump float;\n"
                                      "out vec4 color;\n"
                                      "void main()\n"
                                      "{\n"
                                      "color = vec4(1.0, 0.0, 1.0, 1.0);\n"
                                      "}\n\0";

std::function<void()> loop;
void main_loop() { loop(); }
// The MAIN function, from here we start the application and run the game loop
int main()
{


    GLFWWindow window("Index");

#ifndef __EMSCRIPTEN__
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();
#endif

    // Define the viewport dimensions
    auto [width, height] = window.getFrameBufferSize();
    glViewport(0, 0, width, height);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint shaderProgram = glCreateProgram();
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Link the first program object
    glAttachShader(shaderProgram, vertexShader);

    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);
    char log[2048];
    glGetProgramInfoLog(shaderProgram, sizeof(log), 0, log);


    // Set up vertex data (and buffer(s)) and attribute pointers
    // We add a new set of vertices to form a second triangle (a total of 6 vertices); the vertex attribute configuration remains the same (still one 3-float position vector per vertex)
    GLfloat triangle[] = {
            -0.5f, -0.5f, 0.0f,  // Left
             0.5f, -0.5f, 0.0f,  // Right
             0.0f, 0.5f, 0.0f,  // Top
    };

    GLuint vbo, vao;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    // ================================
    // First Triangle setup
    // ===============================
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    // Game loop

    //GUI
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

#ifdef __EMSCRIPTEN__
    io.IniFilename = NULL;
    const char* glslVersion = "#version 300 es";
#else
    const char* glslVersion = "#version 460";
#endif

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window.getRawWindowPtr(), true);
    ImGui_ImplOpenGL3_Init(glslVersion);

    bool open = true;
loop = [&] {// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow(&open);


        ImGui::Render();
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        window.update();
 };
#ifdef __EMSCRIPTEN__
 emscripten_set_main_loop(main_loop, 0, true);
#else
    while (!window.shouldClose()){ main_loop(); }
#endif
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    return 0;
}
