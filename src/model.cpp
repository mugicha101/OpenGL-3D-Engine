#include "model.h"
#include "input.h"
#include <iostream>

namespace model {
    int tick = 0;
    bool exit_requested = false;
    bool debug = false;

    void tick_step() {
        // handle exit request
        if (input::escape.pressed()) {
            exit_requested = true;
            return;
        }

        // toggle debug mode
        if (input::debug.just_pressed())
            debug = !debug;

        // update tick at end
        ++tick;
    }
}