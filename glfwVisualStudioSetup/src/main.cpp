#include "shader.h"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <openglErrorReporting.h>

#include <iostream>

float triangleData[] = {
    // Positions       Colors
    // x    y    z     r  g  b
       0.5, 0.5,  0,   1, 0, 0,
      -0.5, 0.5,  0,   0, 1, 0,
      -0.5, -0.5, 0,   0, 0, 1,
       0.5, -0.5, 0,   0, 0, 1
};

unsigned short indices[] = {
    0,1,2,
    0,2,3
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

#pragma region vao

    // Before we bind our buffers, we can set up this thing called a vertex array object.
    // This can encapsulate the state of the vertex buffer, index buffer, and attribute
    // configuration. So, when we set up our buffers after this, since this vao is bound,
    // they can later be used via this vao.

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

#pragma endregion

#pragma region buffer
    // Create a variable that will hold the handle to the buffer in VRAM.
    GLuint buffer = 0; 

    { // Create the buffer in VRAM.
        glGenBuffers(1, &buffer); // Generate 1 buffer in VRAM and set the handle.
    }

    { // Send the data to the buffer in VRAM.
        // Set our buffer as the one current active.
        glBindBuffer(GL_ARRAY_BUFFER, buffer);

        // Set the data in the currently bound buffer to the triangle data. This is the part that actually sends the
        // data from the CPU to the GPU.
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW); 
    }

    { // Configure the attribute representing position.
        // Tell OpenGL that we want to use the 0th vertex attribute (attributes essentially being the fields for vertices).
        glEnableVertexAttribArray(0);

        // Tell OpenGL how the data is laid out in the buffer for our vertex attribute since there is no standard convention.
        glVertexAttribPointer(
            0,        // The vertex attribute for which we are specifying the data layout.
            3,        // How many components (by count, NOT by size) there are in this attribute. Since we have x,y,z data, this should be 3.
            GL_FLOAT, // What type the data is. TODO: why do we have to tell it this?
            GL_FALSE, // Are we sending float data represented as integers?
            sizeof(float) * 6, // Stride, i.e. how many bytes of data are in each "row".
            0 // Offset from the beginning of the "row" that this vertex attribute begins.
        );
    }

    { // Configure the attribute representing color.
        // Tell OpenGL that we want to use the 1st vertex attribute (attributes essentially being the fields for vertices).
        glEnableVertexAttribArray(1);

        // Tell OpenGL how the data is laid out in the buffer for our vertex attribute since there is no standard convention.
        glVertexAttribPointer(
            1,        // The vertex attribute for which we are specifying the data layout.
            3,        // How many components there are in this attribute. Since we have x,y,z data, this should be 3.
            GL_FLOAT, // What type the data is. TODO: why do we have to tell it this?
            GL_FALSE, // Are we sending float data represented as integers?
            sizeof(float) * 6, // Stride, i.e. how many bytes of data are in each "row".
            (void*)(sizeof(float) * 3) // Offset from the beginning of the "row" that this vertex attribute begins.
        );
    }
#pragma endregion

#pragma region index buffer

    // Create buffer
    GLuint indexBuffer = 0;
    glGenBuffers(1, &indexBuffer);

    // Populate buffer
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

#pragma endregion

    // Here we unbind the vao (by binding to 0) since we are done putting stuff into it.
    glBindVertexArray(0);

#pragma region shader loading
    Shader shader;
    shader.loadShaderProgramFromFile("resources/myshader.vert", "resources/myshader.frag");
    shader.bind();
#pragma endregion

    const float background_color = uint8ToFloat(24);
    glClearColor(background_color, background_color, background_color, 1.0);

    while (!glfwWindowShouldClose(window)) {
        int w = 0, h = 0;
        glfwGetWindowSize(window, &w, &h);
        glViewport(0, 0, w, h);

        glClear(GL_COLOR_BUFFER_BIT);

        // Here we just have to bind the vao (not the vertex array, index array, or attributes individually).
        glBindVertexArray(vao);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}