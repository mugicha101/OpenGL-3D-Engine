#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>

#include "controller.h"

int window_width = 0;
int window_height = 0;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    window_width = width;
    window_height = height;
    glViewport(0, 0, window_width, window_height);
}

int main(int argc, char *argv[]) {
    // init glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *video_mode = glfwGetVideoMode(monitor);

    // create window
    window_width = video_mode->width * 0.9;
    window_height = video_mode->height * 0.9;
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "GLFW Window", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // init glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // check that GPU has enough vertex attributes
    if (GL_MAX_VERTEX_ATTRIBS < 16) {
        std::cout << "GPU needs to support at least 16 vertex attributes" << std::endl;
        return -1;
    }

    // setup viewport
    glViewport(0, 0, window_width, window_height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // main loop
    main_loop(window);

    // cleanup
    glfwTerminate();
}