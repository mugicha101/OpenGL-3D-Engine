#pragma once

#include <chrono>
#include <stdint.h>

using namespace std::chrono;

inline int64_t curr_time() {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

// circular buffer holding SIZE durations (in ns)
template<size_t SIZE>
class DurationBuffer {
    int64_t durations[SIZE] = {};
    int64_t total_duration = 0;
    int next_index = 0;
    int64_t dur_start;
public:
    void start_duration() {
        dur_start = curr_time();
    }
    void end_duration() {
        int64_t duration = curr_time() - dur_start;
        total_duration += duration - durations[next_index];
        durations[next_index] = duration;
        next_index = (next_index + 1) % SIZE;
    }
    inline int64_t get_total_duration() const {
        return total_duration;
    }
    constexpr size_t get_size() const {
        return SIZE;
    }
    inline double get_average_duration() const {
        return (double)total_duration / (double)SIZE;
    }
};