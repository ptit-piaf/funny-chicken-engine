#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "engine.h"
#include "event.h"

GLFWwindow* fn_createOpenglWindow()     // TODO : implement config file and argument to change window Hint
{
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

        GLFWwindow* window = glfwCreateWindow(800, 500, "funny chiken engine", NULL, NULL);
        glfwMakeContextCurrent(window);

        glfwSetWindowCloseCallback(window, fn_windowCloseCallback);
        glfwSetWindowSizeCallback(window, fn_openGLWindowSizeCallback);
        glfwSetCursorPosCallback(window, fn_scene3DCursorPosCallback);  // TODO : to change when UI is implemented

        return window;
}
