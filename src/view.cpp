#include "view.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

namespace view {
    unsigned int test_shader_program;
    unsigned int test_vao;

    // loads shader from file and returns shader object
    unsigned int load_shader_from_file(const char *path, GLenum shader_type) {
        // read file
        std::ifstream fs(path);
        if (!fs.good()) {
            std::cout << "File not found at path " << path << std::endl;
            exit(-1);
        }
        std::stringstream buffer;
        buffer << fs.rdbuf();
        fs.close();
        std::string buffer_str = buffer.str();
        const char *content = buffer_str.c_str();

        // create and compile shader
        unsigned int shader = glCreateShader(shader_type);
        glShaderSource(shader, 1, &content, NULL);
        glCompileShader(shader);
        int  success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "Error compiling shader loaded from path " << path << "\n" << infoLog << "\n\ncontent:\n" << content << std::endl;
            exit(-1);
        }
        return shader;
    }

    // links a shader program
    void link_shader_program(unsigned int shader_program) {
        int success;
        char infoLog[512];
        glLinkProgram(test_shader_program);
        glGetProgramiv(test_shader_program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(test_shader_program, 512, NULL, infoLog);
            std::cout << "Error linking shader program\n" << infoLog << std::endl;
            exit(-1);
        }
    }

    void init(GLFWwindow *window) {
        unsigned int vert_shader = load_shader_from_file("resources/test_vert_shader.glsl", GL_VERTEX_SHADER);
        unsigned int frag_shader = load_shader_from_file("resources/test_frag_shader.glsl", GL_FRAGMENT_SHADER);

        // link shader program
        test_shader_program = glCreateProgram();
        glAttachShader(test_shader_program, vert_shader);
        glAttachShader(test_shader_program, frag_shader);
        link_shader_program(test_shader_program);

        // cleanup compiled shaders
        glDeleteShader(vert_shader);
        glDeleteShader(frag_shader);

        // create test vao
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
        };
        unsigned int test_vbo;
        glGenBuffers(1, &test_vbo);
        glGenVertexArrays(1, &test_vao);
        glBindVertexArray(test_vao);
        glBindBuffer(GL_ARRAY_BUFFER, test_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
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

        // draw test vao
        glUseProgram(test_shader_program);
        glBindVertexArray(test_vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}