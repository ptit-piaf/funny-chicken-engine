#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include <stdio.h>
#include <stdlib.h>

#include "event.h"

void fn_scene3DCursorPosCallback(GLFWwindow* window, double x, double y)
{
        S_event* p_event = glfwGetWindowUserPointer(window);
        fprintf(stdout, ANSI_BLUE_TEXT("GLFW event") " : Cursor pose [%lf, %lf] event called\n", x, y);

        vec3 up = {0.0f, 1.0f, 0.0f};

        vec3 lookPoint =
                {
                        cos(x),

                }
        glm_lookat(p_event->position, ADD_VEC(p_event->position, lookPoint),)

        p_event->type |= EVENT_MOUSE_POS;
}
