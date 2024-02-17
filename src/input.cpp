#include "input.h"
#include <iostream>

namespace input {
    InputState escape;
    InputState left;
    InputState right;
    InputState up;
    InputState down;
    InputState debug;

    void InputState::update_state(bool new_state) {
        fresh = state != new_state;
        state = new_state;
    }

    bool InputState::just_pressed() const {
        return state && fresh;
    }

    bool InputState::just_released() const {
        return !state && fresh;
    }

    bool InputState::pressed() const {
        return state;
    }

    bool InputState::released() const {
        return !state;
    }

    void update(GLFWwindow *window) {
        escape.update_state(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS);
        up.update_state(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS);
        left.update_state(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS);
        down.update_state(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS);
        right.update_state(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS);
        debug.update_state(glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS);
    }
}