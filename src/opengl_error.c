#include <GL/glad.h>

#include <stdio.h>
#include <stdlib.h>

#include "error.h"

void fn_openglErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, void* userParam)
{
        fprintf(stderr, ANSI_RED_TEXT("openGL error [%s]")" : type = %s\n%s\n",
                (severity == GL_DEBUG_SEVERITY_HIGH ? (severity == GL_DEBUG_SEVERITY_MEDIUM ? "GL_DEBUG_SEVERITY_MEDIUM" : "GL_DEBUG_SEVERITY_LOW" ) : "GL_DEBUG_SEVERITY_HIGH"),
                fn_openGLErrorTypeName(type), message);
}

const char* fn_openGLErrorTypeName(GLenum type)
{
        switch(type)
        {
                case GL_DEBUG_TYPE_ERROR:
                        return "GL_DEBUG_TYPE_ERROR";
                case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
                        return "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
                case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                        return "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";
                case GL_DEBUG_TYPE_PORTABILITY:
                        return "GL_DEBUG_TYPE_PORTABILITY";
                case GL_DEBUG_TYPE_PERFORMANCE:
                        return "GL_DEBUG_TYPE_PERFORMANCE";
                case GL_DEBUG_TYPE_OTHER:
                        return "GL_DEBUG_TYPE_OTHER";
        }
        return "GL_DEBUG_TYPE_UNDEFINED";
}
