#include "shader.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

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
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        std::cout << "Error linking shader program\n" << infoLog << std::endl;
        exit(-1);
    }
}

Shader::Shader(const char *vert_path, const char *frag_path) {
    // load shaders
    unsigned int vert_shader = load_shader_from_file(vert_path, GL_VERTEX_SHADER);
    unsigned int frag_shader = load_shader_from_file(frag_path, GL_FRAGMENT_SHADER);

    // create and link shader program
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vert_shader);
    glAttachShader(shader_program, frag_shader);
    link_shader_program(shader_program);

    // cleanup
    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);
}

void Shader::use() {
    glUseProgram(shader_program);
}

template<>
void Shader::set_uniform<bool>(const std::string &name, bool value) {
    glUniform1i(glGetUniformLocation(shader_program, name.c_str()), (int)value); 
}


template<>
void Shader::set_uniform<int>(const std::string &name, int value) {
    glUniform1i(glGetUniformLocation(shader_program, name.c_str()), value); 
}

template<>
void Shader::set_uniform<float>(const std::string &name, float value) {
    glUniform1f(glGetUniformLocation(shader_program, name.c_str()), value); 
}