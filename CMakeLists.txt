cmake_minimum_required(VERSION 2.8)

project( Main ) # this is case sensitive

add_subdirectory(lib)

add_executable( Main main.cpp )
add_definitions("-std=c++11")

include_directories(${Main_SOURCE_DIR}/lib/include)
target_link_libraries(Main lib)

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    message("OpenGL_FOUND")
    include_directories(${OPENGL_INCLUDE_DIRS})
    target_link_libraries(Main ${OPENGL_LIBRARIES})
    target_link_libraries(Main glfw)
endif()

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    message("GLEW_FOUND")
    include_directories(${GLEW_INCLUDE_DIRS})
    target_link_libraries(Main ${GLEW_LIBRARIES})
endif()
