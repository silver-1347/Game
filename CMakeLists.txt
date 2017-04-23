cmake_minimum_required(VERSION 2.8)

project( Main ) # this is case sensitive

add_executable( Main main.cpp )
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    target_link_libraries(Main ${OPENGL_LIBRARIES})
endif()

find_package(glfw3 3.2 REQUIRED)
if(GLFW_FOUND)
    include_directories(${GLFW_INCLUDE_DIRS})
    target_link_libraries(Main ${GLFW_LIBRARIES})
endif()

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    target_link_libraries(Main ${GLEW_LIBRARIES})
endif()
