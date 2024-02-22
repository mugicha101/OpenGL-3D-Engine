cmake_minimum_required(VERSION 3.5)
project(CMakeProject LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(
    GLFW
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.9
)

FetchContent_Declare(
    GLAD
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v0.1.36
)
set(GLAD_PROFILE "core"	CACHE STRING "OpenGL profile")
set(GLAD_GENERATOR "c"	CACHE STRING "Language to generate the binding for")

FetchContent_Declare(
    GLM
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.0
)


FetchContent_MakeAvailable(GLFW GLAD GLM)

file(GLOB src CONFIGURE_DEPENDS "src/main.cpp src/*.h" "src/*.cpp")
set(GCC_COVERAGE_COMPILE_FLAGS  "-lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl")
add_executable(CMakeProject ${src})
target_link_libraries(CMakeProject PRIVATE glfw glad glm::glm-header-only)
target_compile_features(CMakeProject PRIVATE cxx_std_17)
add_compile_definitions(_USE_MATH_DEFINES)

add_custom_command(
    TARGET CMakeProject PRE_BUILD
    COMMENT "Copying Resource Folder"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/src/resources $<TARGET_FILE_DIR:CMakeProject>/resources)

install(TARGETS CMakeProject)