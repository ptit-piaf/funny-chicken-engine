#include <GL/glad.h>

#include <stdio.h>
#include <stdlib.h>

#include "error.h"

void fn_openglErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, void* userParam)
{
        fprintf(stderr, "the error is %s\n", message);
}
