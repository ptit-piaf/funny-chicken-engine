#include <GL/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "global_variable.h"
#include "event.h"

void fn_windowCloseCallback(GLFWwindow* window)
{
        S_event* p_event = glfwGetWindowUserPointer(window);
        fprintf(g_eventFStream, ANSI_BLUE_TEXT("GLFW event") " : Window close event called\n");

        p_event->type |= EVENT_QUIT;
}

void fn_openGLWindowSizeCallback(GLFWwindow* window, int width, int height)
{
        S_event* p_event = glfwGetWindowUserPointer(window);
        fprintf(g_eventFStream, ANSI_BLUE_TEXT("GLFW event") " : Window size[%d, %d] event called\n", width, height);

        glViewport(0, 0, width, height);

        p_event->windowWidth = width;
        p_event->windowHeight = height;

        p_event->type |= EVENT_WINDOW_SIZE;
}
