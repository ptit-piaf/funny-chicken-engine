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

        mat4 viewMatrix;
        float xCameraAxis;
        float yCameraAxis;
        vec3 position;

        bool opengl;
} S_event;

void fn_windowCloseCallback(GLFWwindow* window);
void fn_windowSizeCallback(GLFWwindow* window, int width, int height);

#endif
