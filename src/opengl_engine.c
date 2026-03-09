#include <GL/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "engine.h"
#include "fn_state.h"

E_main fn_openglEngineLoop()
{
        E_main returnValue = END;

        GLFWwindow* window = fn_createOpenglWindow();

        glfwSetWindowUserPointer(window, NULL);

        bool running = true;
        while(running)
        {

        }

        return returnValue;
}
