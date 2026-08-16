#define HOL_IMPLEMENTATION
#include <HOL/HOL.h>

#define CGLTF_IMPLEMENTATION
#include <cgltf/cgltf.h>

//considere the nuklear lib

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <GL/glad.h>
#include <GLFW/glfw3.h>
#include <yyjson.h>

#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "fn_state.h"
#include "engine.h"
#include "global_variable.h"

/*
        * TODO : A prepossesor option to choose between Opengl Vulkan or both
        * TODO : Manage main argument
        * TODO : Create some global variable to manage text output

        * WARNING : some functionnality are posix only
*/

i32 main(i32 argc, char** v_argv)
{
        u32 returnValue = 0;

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
                                state = fn_openGLEngineLoop();
                                break;

                        case VULKAN_ENGINE:
                                state = END;
                                break;

                        case END:
                                running = false;
                                break;

                        default:
                                fprintf(stderr, ANSI_RED_TEXT("Error : ") "funny chicken engine ended with error code [%d].\n", state);
                                returnValue = state;
                                running = false;
                }
        }

        glfwTerminate();

        return returnValue;
}
