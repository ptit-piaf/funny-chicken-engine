#include <GL/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "event.h"

void fn_windowCloseCallback(GLFWwindow* window)
{
        S_event* p_event = glfwGetWindowUserPointer(window);
        fprintf(stdout, ANSI_BLUE_TEXT("GLFW event") " : Window close event called\n");  // TODO : maybe use a other file ptr

        p_event->type |= EVENT_QUIT;
}

void fn_windowSizeCallback(GLFWwindow* window, int width, int height)
{
        S_event* p_event = glfwGetWindowUserPointer(window);
        fprintf(stdout, ANSI_BLUE_TEXT("GLFW event") " : Window size[%d, %d] event called\n", width, height);

        if(p_event->opengl)
                glViewport(0, 0, width, height);

        p_event->windowWidth = width;
        p_event->windowHeight = height;

        p_event->type |= EVENT_WINDOW_SIZE;
}
