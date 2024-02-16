#include "view.h"

namespace view {
    void render(GLFWwindow *window) {
        // handle exit request
        if (model::exit_requested) {
            glfwSetWindowShouldClose(window, true);
            return;
        }
    }
}