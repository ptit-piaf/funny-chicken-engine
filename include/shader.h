#ifndef SHADER_H
#define SHADER_H

#include <GL/glad.h>

GLuint fn_compileOpenglShader(const char* shaderPath, GLenum shaderType);
GLuint fn_createOpenglShaderProgram(GLuint* v_shader, u32 shaderCount);

#endif
