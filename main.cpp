#include <cstdlib>
#include <vector>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

// シェーダプログラムのコンパイル結果表示
GLboolean printShaderInfoLog(GLuint shader,const char* str){
    GLint status;
    glGetShaderiv(shader,GL_COMPILE_STATUS,&status);
    if(status == GL_FALSE){
        std::cerr << "コンパイルエラー:" << str << std::endl;
    }

    GLsizei bufSize;
    glGetShaderiv(shader,GL_INFO_LOG_LENGTH, &bufSize);
    if(bufSize > 1){
        std::vector<GLchar> infoLog(bufSize);
        GLsizei length;
        glGetShaderInfoLog(shader,bufSize,&length,&infoLog[0]);
        std::cerr << &infoLog[0] << std::endl;
    }

    return static_cast<GLboolean>(status);
}

// リンク結果表示
GLboolean printProgramInfoLog(GLuint program){
    GLint status;
    glGetProgramiv(program,GL_LINK_STATUS,&status);
    if(status == GL_FALSE){
        std::cerr << "リンクエラー" << '\n';
    }

    GLsizei bufSize;
    glGetProgramiv(program,GL_INFO_LOG_LENGTH,&bufSize);

    if(bufSize > 1){
        std::vector<GLchar> infoLog(bufSize);
        GLsizei length;
        glGetProgramInfoLog(program,bufSize,&length,&infoLog[0]);
        std::cerr << &infoLog[0] << std::endl;
    }

    return static_cast<GLboolean>(status);
}


//シェーダプログラムオブジェクト作成
GLuint createProgram(const char* vsrc, const char* fsrc){
    //空のプログラムオブジェクトを作成
    const GLuint program(glCreateProgram());

    if(vsrc != NULL){ //バーテックスシェーダ作成
        const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
        glShaderSource(vobj,1,&vsrc,NULL);
        glCompileShader(vobj);

        if(printShaderInfoLog(vobj,"vertex shader"))
            glAttachShader(program,vobj);
        glDeleteShader(vobj);
    }

    if(fsrc != NULL){ //フラグメントシェーダ
        const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
        glShaderSource(fobj,1,&fsrc,NULL);
        glCompileShader(fobj);

        if(printShaderInfoLog(fobj,"fragment shader"))
            glAttachShader(program,fobj);
        glDeleteShader(fobj);
    }

    // オブジェクトリンク
    glBindAttribLocation(program,0,"position");
    glBindFragDataLocation(program,0,"fragment");
    glLinkProgram(program);

    if (printProgramInfoLog(program))
        return program;

    glDeleteProgram(program);
    return program;
}

bool readShaderSource(const char* name, std::vector<GLchar> &buffer){
    if (name == NULL) return false;

    std::ifstream file(name,std::ios::binary);
    if(file.fail()){
        std::cerr << "ソースファイルを開けませんでした:" << name << std::endl;
        return false;
    }

    file.seekg(0L,std::ios::end);
    GLsizei length = static_cast<GLsizei>(file.tellg());

    buffer.resize(length + 1);

    file.seekg(0L,std::ios::beg);
    file.read(buffer.data(),length);
    buffer[length] = '\0';

    if (file.fail()){
        std::cerr << "ソースファイルを読めませんでした:" << name << std::endl;
        file.close();
        return false;
    }
    file.close();
    return true;
}

GLuint loadProgram(const char* vert, const char* frag){
    std::vector<GLchar> vsrc;
    bool vstat = readShaderSource(vert,vsrc);
    std::vector<GLchar> fsrc;
    bool fstat = readShaderSource(frag,fsrc);
    return vstat && fstat ? createProgram(vsrc.data(),fsrc.data()) : 0;
}

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

    const GLuint program(loadProgram("point.vert","point.frag"));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    return 0;
}
