#ifndef INCLUDED_SHADER_HPP
#define INCLUDED_SHADER_HPP

extern GLboolean printShaderInfoLog(GLuint shader,const char* str);
extern GLboolean printProgramInfoLog(GLuint program);
extern GLuint createProgram(const std::string& vsrc, const std::string& fsrc);
extern bool readShaderSource(const std::string& name, std::vector<GLchar> &buffer);
extern GLuint loadProgram(const std::string& vert, const std::string& frag);

#endif
