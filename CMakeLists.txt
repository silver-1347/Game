cmake_minimum_required(VERSION 2.8)

project( Main ) # this is case sensitive

add_executable( Main main.cpp )
find_package(OpenGL REQUIRED)
find_package(glfw3 3.2 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(Main ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES})
