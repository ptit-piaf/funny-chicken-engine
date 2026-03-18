#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "engine.h"
#include "event.h"

GLFWwindow* fn_createOpenglWindow()     // TODO : implement config file and argument to change window Hint
{
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

        GLFWwindow* window = glfwCreateWindow(800, 500, "funny chiken engine", NULL, NULL);
        glfwMakeContextCurrent(window);

        glfwSetWindowCloseCallback(window, fn_windowCloseCallback);

        return window;
}
