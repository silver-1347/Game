#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "object.hpp"


Object::Object(GLint size, GLuint vertexcount, const Vertex *vertex){
    //頂点配列オブジェクト
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);

    //頂点バッファオブジェクト
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,vertexcount * sizeof(Vertex),vertex,GL_STATIC_DRAW);

    glVertexAttribPointer(0,size,GL_FLOAT,GL_FALSE,0,0);
    glEnableVertexAttribArray(0);
}

Object::~Object(){
    glDeleteBuffers(1,&vao);
    glDeleteBuffers(1,&vbo);
}

void Object::bind() const{
    glBindVertexArray(vao);
}
