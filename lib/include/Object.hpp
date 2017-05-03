#ifndef INCLUDED_OBJECT_HPP
#define INCLUDED_OBJECT_HPP

class Object{
public:
    struct Vertex{
        GLfloat position[2];
    };

    Object(GLint size, GLuint vertexcount, const Vertex *vertex);
    virtual ~Object();

    void bind() const;
private:
    //コピー禁止
    Object(const Object &o);
    Object &operator=(const Object& o);

    GLuint vao; //頂点配列オブジェクト
    GLuint vbo; //頂点バッファオブジェクト
};

#endif
