#include <GLFW/glfw3.h>

#include "Shape.hpp"

void Shape::draw() const{
    object->bind();

    execute();
}

void Shape::execute() const{
    glDrawArrays(GL_LINE_LOOP,0,vertexcount);
}
