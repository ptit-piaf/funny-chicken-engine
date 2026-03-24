#ifndef EVENT_H
#define EVENT_H

typedef enum
{
        EVENT_QUIT = 1,
        E_EVENT_TYPE_MAX = 0XFFFFFFFFFFFFFFFF
} E_eventType;

typedef struct
{
        E_eventType type;
        u32 windowWidth;
        u32 windowHeight;
        bool opengl;
} S_event;

void fn_windowCloseCallback(GLFWwindow* window);
void fn_windowSizeCallback(GLFWwindow* window, int width, int height);

#endif
