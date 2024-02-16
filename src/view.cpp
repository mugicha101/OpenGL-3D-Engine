#include "view.h"

namespace view {
    void render(GLFWwindow *window) {
        // handle exit request
        if (model::exit_requested) {
            glfwSetWindowShouldClose(window, true);
            return;
        }

        // clear screen
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}