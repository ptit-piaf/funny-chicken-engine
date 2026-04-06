#ifndef EVENT_H
#define EVENT_H

#include <cglm/cglm.h>

typedef enum
{
        EVENT_QUIT = 1,
        EVENT_WINDOW_SIZE = 2,
        EVENT_MOUSE_POS = 4,
        E_EVENT_TYPE_MAX = 0XFFFFFFFFFFFFFFFF
} E_eventType;

typedef struct
{
        E_eventType type;

        u32 windowWidth;
        u32 windowHeight;

        double xMouseMov;
        double yMouseMov;
} S_event;

void fn_windowCloseCallback(GLFWwindow* window);
void fn_openGLWindowSizeCallback(GLFWwindow* window, int width, int height);
void fn_scene3DCursorPosCallback(GLFWwindow* window, double x, double y);

#endif
