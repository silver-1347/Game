#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "shader.hpp"

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

bool readShaderSource(const std::string& name, std::vector<GLchar> &buffer){
    if (name.size() == 0) return false;

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

GLuint loadProgram(const std::string& vert, const std::string& frag){
    std::vector<GLchar> vsrc;
    bool vstat = readShaderSource(vert,vsrc);
    std::vector<GLchar> fsrc;
    bool fstat = readShaderSource(frag,fsrc);
    return vstat && fstat ? createProgram(vsrc.data(),fsrc.data()) : 0;
}
