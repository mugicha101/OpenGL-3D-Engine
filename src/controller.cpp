#include <chrono>
#include <stdint.h>
#include <iostream>

#include "controller.h"
#include "model.h"
#include "view.h"
#include "input.h"

void main_loop(GLFWwindow *window) {
    uint64_t next_frame = 0;
    uint64_t curr_time;
    while (!glfwWindowShouldClose(window)) {
        // handle input
        input::update(window);

        // tick until next_frame > current time
        // this separates calc ticks from render calls
        bool ticked = false;
        while (next_frame <= (curr_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()) && curr_time < FRAME_CATCHUP_LIMIT + next_frame) {
            ticked = true;
            model::tick_step();
            next_frame += frame_duration;
        }
        if (curr_time > next_frame + FRAME_CATCHUP_LIMIT)
            next_frame = curr_time + frame_duration;
        if (!ticked) continue; // don't render if nothing changed

        // render
        view::render(window);

        // update screen
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}