#ifndef INCLUDED_SHAPE_HPP
#define INCLUDED_SHAPE_HPP

#include <memory>

#include "Object.hpp"

class Shape{
public:
    Shape(GLint size,GLsizei vertexcount,const Object::Vertex* vertex):
    object(new Object(size,vertexcount,vertex)),
    vertexcount(vertexcount){}

    void draw() const; //描画
    virtual void execute() const; //描画実行
protected:
    GLsizei vertexcount;
private:
    std::shared_ptr<const Object> object;
};

#endif
