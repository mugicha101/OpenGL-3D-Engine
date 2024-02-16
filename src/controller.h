// responsible for handling high level main loop control flow

# pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void main_loop(GLFWwindow *window);

const uint64_t NS_PER_SEC = 1000000000;
static uint64_t frame_duration = NS_PER_SEC / 60; // dynamically changable frame duration (in ns)
const uint64_t FRAME_CATCHUP_LIMIT = NS_PER_SEC; // once current time - next frame time reaches this (in ns) will stop catching up and set next frame to current time + frame offset