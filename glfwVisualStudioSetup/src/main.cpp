#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <openglErrorReporting.h>

#include <iostream>

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

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);

        glVertex2f(0, 1);
        glColor3f(1, 0, 0);

        glVertex2f(-1, -1);
        glColor3f(0, 1, 0);

        glVertex2f(1, -1);
        glColor3f(0, 0, 1);

        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}