#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <openglErrorReporting.h>

#include <iostream>

float triangleData[] = {
    // Positions       Colors
    // x   y   z       r  g  b
       0,  1,  0,      1, 0, 0,
      -1, -1,  0,      0, 1, 0,
       1, -1,  0,      0, 0, 1,
};

const std::uint8_t floatToUint8(const float f) {
    return f * 255.0;
}

const float uint8ToFloat(const std::uint8_t u) {
    return u / 255.0;
}

int main() {
    if (!glfwInit()) {
        std::cout << "GLFW Init Error!\n";
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window) {
        std::cout << "Window error\n";
        return 1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD glfwGetProcAddress error\n";
        return 1;
    }

    enableReportGlErrors();

    // Buffer
#pragma region buffer
    // Create a variable that will hold the handle to the buffer in VRAM.
    GLuint buffer = 0; 

    // Generate 1 buffer in VRAM and set the handle.
    glGenBuffers(1, &buffer); 

    // Set our buffer as the one current active.
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    // Set the data in the currently bound buffer to the triangle data.
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW); 
#pragma endregion

    const float background_color = uint8ToFloat(24);
    std::cout << "background_color: " << background_color << "\n";

    while (!glfwWindowShouldClose(window)) {
        glClearColor(background_color, background_color, background_color, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}