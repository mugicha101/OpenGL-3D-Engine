#include "model.h"
#include "input.h"

namespace model {
    bool exit_requested = false;

    int tick = 0;

    void tick_step() {
        // handle exit request
        if (input::escape.pressed()) {
            exit_requested = true;
            return;
        }

        // update tick at end
        ++tick;
    }
}