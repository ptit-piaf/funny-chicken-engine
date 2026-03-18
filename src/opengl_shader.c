#include <GL/glad.h>

#include <stdio.h>
#include <stdlib.h>

#include "shader.h"

GLuint fn_compileOpenglShader(const char* shaderPath, GLenum shaderType)
{
        HOL_buffer buffer = HOL_readFile(shaderPath);
        if(buffer.error != HOLY_SUCCESS)
        {
                return 0;
        }

        GLuint shader = glCreateShader(shaderType);
        const GLint tmp = (const GLint) buffer.size;
        glShaderSource(shader, 1, (const char**)&buffer.buffer, &tmp);
        glCompileShader(shader);

        GLint result;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
        if(!result)
        {
                char errorString [512];
                glGetShaderInfoLog(shader, sizeof(errorString), NULL, errorString);
                fprintf(stderr, ANSI_RED_TEXT("OpenGL compilation error") " [%s] : %.512s\n", shaderPath, errorString);
                shader = 0;
        }

        free(buffer.buffer);
        return shader;
}

GLuint fn_createOpenglShaderProgram(GLuint* v_shader, u32 shaderCount)
{
        GLuint shaderProgram = glCreateProgram();

        REPEAT(glAttachShader(shaderProgram, v_shader[_]), shaderCount);
        glLinkProgram(shaderProgram);

        GLint result;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
        if(!result)
        {
                char errorString [512];
                glGetProgramInfoLog(shaderProgram, sizeof(errorString), NULL, errorString);
                fprintf(stderr, ANSI_RED_TEXT("OpenGL linking error") " : %.512s\n", errorString);
                shaderProgram = 0;
        }

        REPEAT(glDeleteShader(v_shader[_]), shaderCount);
        return shaderProgram;
}
