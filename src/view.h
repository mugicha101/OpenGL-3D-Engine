// responsible for rendering the model onto the screen

# pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "model.h"

namespace view {
    void init(GLFWwindow *window);
    void render(GLFWwindow *window);
}