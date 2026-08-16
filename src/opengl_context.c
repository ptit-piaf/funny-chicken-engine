#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "engine.h"
#include "render.h"
#include "event.h"

GLFWwindow* fn_createOpenglWindow()     // TODO : implement config file and argument to change window Hint
{
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

        GLFWwindow* window = glfwCreateWindow(800, 500, "funny chiken engine", NULL, NULL);
        glfwMakeContextCurrent(window);

        glfwSetWindowCloseCallback(window, fn_windowCloseCallback);
        glfwSetWindowSizeCallback(window, fn_openGLWindowSizeCallback);
        glfwSetCursorPosCallback(window, fn_scene3DCursorPosCallback);  // TODO : to change when UI is implemented

        return window;
}

void fn_freeOpenGLscene(S_openGLscene scene)
{
        switch(scene.advancement)
        {
                case ADVANCEMENT_SUCCESS:

                        glDeleteBuffers(primitiveCount, scene.v_VBO);
                        glDeleteBuffers(primitiveCount, scene.v_UBO);
                        glDeleteVertexArrays(primitiveCount, scene.v_VAO);
                        GLuint lastVBO = 0;
                        GLuint lastUBO = 0;
                        GLuint lastVAO = 0;
                        for(u32 i=0; i<primitiveCount; i++)
                        {
                                if(scene.v_VBO != lastVBO)
                                        glDeleteBuffers(1, &scene.v_VBO);
                                if(scene.v_UBO != lastUBO)
                                        glDeleteBuffers(1, &scene.v_UBO);
                                if(scene.v_VAO != lastVAO)
                                        glDeleteVertexArrays(1, &scene.v_VAO);
                        }

                        free(v_VBO);
                        free(v_VAO);
                        free(v_SSBO);
                        free(v_TBO);
                        free(v_EBO);
                        free(v_shader);
                        free(v_verticeCount);
                        free(v_indiceCount);
                        free(vv_modelMat);

                case ADVANCEMENT_NULL:
        }
}
