#include <GLFW/glfw3.h>

#include <stdio.h>

#include "error.h"

void fn_glfwErrorCallback(int errorCode, const char* errorName)
{
        fprintf(stderr, ANSI_RED_TEXT("GLFW error ") "[%d] %s\n", errorCode, errorName);
}
