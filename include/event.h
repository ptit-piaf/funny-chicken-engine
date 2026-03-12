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
} S_event;

void fn_windowCloseCallback(GLFWwindow* window);

#endif
