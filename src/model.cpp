#include "model.h"
#include "input.h"

namespace model {
    bool exit_requested = false;

    int tick = 0;

    void tick_step() {
        if (input::escape.pressed()) exit_requested = true;

        // update tick at end
        ++tick;
    }
}