#include <GL/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "engine.h"

GLFWwindow* fn_createOpenglWindow()     // TODO : implement config file and argument to change window Hint
{
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        GLFWwindow* window = glfwCreateWindow(800, 500, "funny chiken engine", NULL, NULL);

        glfwSetWindowCloseCallback(window, )

        return window;
}
