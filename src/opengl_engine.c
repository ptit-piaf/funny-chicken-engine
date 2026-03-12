#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "engine.h"
#include "fn_state.h"
#include "event.h"

E_main fn_openglEngineLoop()
{
        E_main returnValue = END;

        GLFWwindow* window = fn_createOpenglWindow();

        S_event event = {0};
        glfwSetWindowUserPointer(window, &event);

        bool running = true;
        while(running)
        {
                if(event.type & EVENT_QUIT)
                        running = false;
        }

        glfwDestroyWindow(window);
        return returnValue;
}
