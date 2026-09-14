#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"

// INFO : v_shader buffers index
#define DEFAULT_SHADER_INDEX 0
//#define 

// INFO : shader uniform layout location
#define PROJECTION_VIEW_UNIFORM_LOCATION        0       // mat4
#define MODEL_UNIFORM_LOCATION                  1       // mat4
#define SUN_LIGHT_UNIFORM_LOCATION              2       // vec3

// INFO : shader vertex buffer layout location
#define POSITION_VERTEX_BUFFER_LOCATION         0       // vec3
#define TEXTURE_COORD_VERTEX_BUFFER_LOCATION    1       // vec2
#define NORMAL_VERTEX_BUFFER_LOCATION           2       // vec3
#define COLOR_VERTEX_BUFFER_LOCATION            3       // vec4

typedef struct
{
        char* vertexPath;
        char** v_fragPath;
        u32 fragCount;
} S_shaderProgramDescriptor;

GLuint fn_compileOpenglShader(const char* shaderPath, GLenum shaderType);
GLuint fn_createOpenglShaderProgram(GLuint* v_shader, u32 shaderCount);
GLuint* fn_getOpenGLshader(u32* p_shaderProgramCount);

GLuint* fn_getOpenGLshaderDefault();

#endif
