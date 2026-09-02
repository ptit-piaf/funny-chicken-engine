#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"

// INFO : v_shader buffers index
#define DEFAULT_SHADER_INDEX 0

// INFO : shader uniform layout location
#define PROJECTION_VIEW_UNIFORM_LOCATION 0

// INFO : shader vertex buffer layout location
#define POSITION_VERTEX_BUFFER_LOCATION         0
#define TEXTURE_COORD_VERTEX_BUFFER_LOCATION    1
#define NORMAL_VERTEX_BUFFER_LOCATION           2
#define COLOR_VERTEX_BUFFER_LOCATION            3

GLuint fn_compileOpenglShader(const char* shaderPath, GLenum shaderType);
GLuint fn_createOpenglShaderProgram(GLuint* v_shader, u32 shaderCount);

GLuint* fn_getOpenGLshaderDefault();

#endif
