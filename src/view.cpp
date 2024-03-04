#include "view.h"
#include "shader.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace view {
    Shader shader;
    unsigned int test_vao;
    unsigned int test_ebo;

    void init(GLFWwindow *window) {
        shader = Shader("resources/test_vert_shader.glsl", "resources/test_frag_shader.glsl");

        // create test polygon
        float vertices[] = {
            // positions         // colors
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
        };
        unsigned int indices[] = {  // note that we start from 0
            0, 1, 2,   // first triangle
        };
        unsigned int test_vbo;
        glGenBuffers(1, &test_vbo);

        glGenVertexArrays(1, &test_vao);
        glBindVertexArray(test_vao);
        glBindBuffer(GL_ARRAY_BUFFER, test_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &test_ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, test_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // attribute 0: pos
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        // attribute 1: color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

    void render(GLFWwindow *window) {
        // handle exit request
        if (model::exit_requested) {
            glfwSetWindowShouldClose(window, true);
            return;
        }

        // clear screen
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        // transform scene graph points to world space

        // transform world space to view space

        // transform view space to projection space

        // transform projection space to normalized device coordinates

        // draw test poly
        glPolygonMode(GL_FRONT_AND_BACK, model::debug ? GL_LINE : GL_FILL);
        shader.use();
        glBindVertexArray(test_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, test_ebo);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}