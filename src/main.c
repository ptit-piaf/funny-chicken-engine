#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "error.h"
#include "fn_state.h"
#include "engine.h"
#include "global_variable.h"

int main(int argc, char** v_argv)
{
        int returnValue = 0;

        fn_manageMainArg();

        glfwSetErrorCallback(fn_glfwErrorCallback);

        glfwInit();

        E_main state = OPENGL_ENGINE;
        bool running = true;
        while(running)
        {
                switch(state)
                {
                        case OPENGL_ENGINE:
                                state = fn_openglEngineLoop();
                                break;

                        case VULKAN_ENGINE:
                                state = END;
                                break;

                        case END:
                                running = false;
                                break;

                        default:
                                fprintf(stderr, ANSI_RED_TEXT("Error : ") "little rat end with error code [%d].\n", state);
                                returnValue = state;
                                running = false;
                }
        }

        glfwTerminate();

        return returnValue;
}
