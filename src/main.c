#define CGLTF_IMPLEMENTATION
#include <cgltf/cgltf.h>

#define HOL_IMPLEMENTATION
#include <HOL/HOL_standard.h>

//considere the nuklear lib

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <yyjson.h>

#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "fn_state.h"
#include "engine.h"
#include "global_variable.h"

/*
 * INFO : MUST
        * TODO : A prepossesor option to choose between Opengl Vulkan or both
        * TODO : Manage main argument
        * TODO : Create some global variable to manage text output
        * TODO : Implement vulkan
        * TODO : BCT_C.vert BCT_flC.vert BCT_C.frag

 * INFO : OPTIONNAL
        * TODO : Implement config file
        * TODO : Improve primitive type. It may not be flexible enought.

        * WARNING : some functionnality are posix only
        * WARNING : review HOL uri function
        * WARNING : vertex allocation for all the vertex attribute should be always be in the same order
        * WARNING : The code only handle vec4 vertex color
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
