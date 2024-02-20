#include <chrono>
#include <stdint.h>
#include <iostream>

#include "controller.h"
#include "model.h"
#include "view.h"
#include "input.h"
#include "timing.h"

void main_loop(GLFWwindow *window) {
    DurationBuffer<60> input_timing;
    DurationBuffer<60> tick_timing;
    DurationBuffer<60> render_timing;
    
    uint64_t next_frame = 0;
    uint64_t curr_time;
    view::init(window);
    while (!glfwWindowShouldClose(window)) {
        // tick until next_frame > current time
        // this separates calc ticks from render calls
        bool ticked = false;
        while (next_frame <= (curr_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()) && curr_time < FRAME_CATCHUP_LIMIT + next_frame) {
            ticked = true;
            input_timing.start_duration();
            input::update(window);
            input_timing.end_duration();
            tick_timing.start_duration();
            model::tick_step();
            tick_timing.end_duration();
            next_frame += frame_duration;

            double input_ns = input_timing.get_average_duration();
            double tick_ns = tick_timing.get_average_duration();
            double render_ns = render_timing.get_average_duration();
            if (model::tick % 60 == 0) printf("frame util: %.2lf - input: %.5lf tick: %.5lf render: %.5lf\n", (input_ns + tick_ns + render_ns) / NS_PER_SEC, input_ns / NS_PER_SEC, tick_ns / NS_PER_SEC, render_ns / NS_PER_SEC);
        }
        if (curr_time > next_frame + FRAME_CATCHUP_LIMIT)
            next_frame = curr_time + frame_duration;
        if (!ticked) continue; // don't render if nothing changed

        // render
        render_timing.start_duration();
        view::render(window);
        render_timing.end_duration();

        // update screen
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}