#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

struct Shader {
    unsigned int shader_program;

    Shader(const char *vert_path, const char *frag_path);
    Shader() = default;

    void use(); // use shader

    template<class T>
    void set_uniform(const std::string &name, T value);
};