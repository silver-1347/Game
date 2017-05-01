#ifndef INCLUDED_SHADER_HPP
#define INCLUDED_SHADER_HPP

extern GLboolean printShaderInfoLog(GLuint shader,const char* str);
extern GLboolean printProgramInfoLog(GLuint program);
extern GLuint createProgram(const char* vsrc, const char* fsrc);
extern bool readShaderSource(const char* name, std::vector<GLchar> &buffer);
extern GLuint loadProgram(const char* vert, const char* frag);

#endif
