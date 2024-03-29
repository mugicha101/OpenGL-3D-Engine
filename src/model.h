// responsible for tracking and updating the game state each tick

# pragma once

namespace model {
    extern int tick;
    extern bool exit_requested;
    extern bool debug;

    void tick_step(); // advances a tick, updating the game state
}