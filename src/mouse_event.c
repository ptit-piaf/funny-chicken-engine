#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include <stdio.h>
#include <stdlib.h>

#include "event.h"

void fn_scene3DCursorPosCallback(GLFWwindow* window, double x, double y)
{
        S_event* p_event = glfwGetWindowUserPointer(window);
        fprintf(stdout, ANSI_BLUE_TEXT("GLFW event") " : Cursor pose [%lf, %lf] event called\n", x, y);

        p_event->xMouseMov = x-p_event->windowWidth/2;
        p_event->yMouseMov = y-p_event->windowHeight/2;
        glfwSetCursorPos(window, p_event->windowWidth/2, p_event->windowHeight/2);

        p_event->type |= EVENT_MOUSE_POS;
}
