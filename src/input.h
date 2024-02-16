// updates input tracking variables

# pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace input {
    class InputState {
        bool state = false;
        bool fresh = false;
    public:
        void update_state(bool new_state);
        bool pressed() const;
        bool released() const;
        bool just_pressed() const;
        bool just_released() const;
    };

    extern InputState escape;
    extern InputState left;
    extern InputState right;
    extern InputState up;
    extern InputState down;

    void update(GLFWwindow *window);
}