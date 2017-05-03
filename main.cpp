#include <cstdlib>
#include <vector>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <memory>

#include "shader.hpp"

#include "Shape.hpp"

const std::string shader_dir = "shader/";

const Object::Vertex rectangleVertex[] ={
    {-0.5f,-0.5f},
    { 0.5f,-0.5f},
    { 0.5f, 0.5f},
    {-0.5f, 0.5f}
};

int main(void)
{
    /* Initialize the library */
    if (!glfwInit()){
        std::cerr << "GLFW初期化に失敗" << std::endl;
        return 1;
    }

    atexit(glfwTerminate);

    // Core Profileを設定
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    auto window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window){
        std::cerr << "ウインドウの作成に失敗" << std::endl;
        glfwTerminate();
        return 1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK){
        std::cerr << "GLEWの初期化に失敗" << '\n';
        return 1;
    }

    //同期タイミング
    glfwSwapInterval(1);

    glClearColor(1.0f,1.0f,1.0f,0.0f);

    const GLuint program(loadProgram(shader_dir + "point.vert", shader_dir + "point.frag"));

    //図形データ作成
    std::unique_ptr<const Shape> shape(new Shape(2,4,rectangleVertex));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);

        // 図形描画
        shape->draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    return 0;
}
