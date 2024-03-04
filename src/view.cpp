#include "view.h"
#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
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
    unsigned int test_tex;

    void init(GLFWwindow *window) {
        shader = Shader("resources/test_vert_shader.glsl", "resources/test_frag_shader.glsl");

        // create test polygon
        float vertices[] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
        };
        unsigned int indices[] = {  
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        // attribute 1: color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // attribute 2: tex coord
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // generate texture
        glGenTextures(1, &test_tex);
        glBindTexture(GL_TEXTURE_2D, test_tex);
        float border_color[] = { 0.f, 0.f, 0.f, 0.f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load("resources/reimu_fumo.jpg", &width, &height, &nrChannels, 0);
        if (!data) {
            std::cout << "could not load texture source file" << std::endl;
            exit(-1);
        }
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);

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
        glBindTexture(GL_TEXTURE_2D, test_tex);
        shader.use();
        glBindVertexArray(test_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, test_ebo);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}