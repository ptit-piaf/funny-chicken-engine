#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "event.h"

void fn_windowCloseCallback(GLFWwindow* window)
{
        S_event* p_event = glfwGetWindowUserPointer(window);

        p_event->type |= EVENT_QUIT;
}
