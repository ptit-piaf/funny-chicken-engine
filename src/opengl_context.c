#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "engine.h"
#include "context.h"
#include "render.h"
#include "event.h"

GLFWwindow* fn_createOpenglWindow()     // TODO : implement config file and argument to change window Hint
{
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
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
                case ADVANCEMENT_COMPLETE:

                        GLuint lastVBO = 0;
                        GLuint lastUBO = 0;
                        GLuint lastVAO = 0;
                        for(u32 i=0; i<scene.primitiveCount; i++)
                        {
                                glDeleteBuffers(1, &scene.v_VBO[i]);
                                glDeleteVertexArrays(1, &scene.v_VAO[i]);
                        }

                        free(scene.v_VBO);
                        free(scene.v_VAO);
                        free(scene.v_SSBO);
                        free(scene.v_TBO);
                        free(scene.v_EBO);
                        free(scene.v_shader);
                        free(scene.v_verticeCount);
                        free(scene.v_indiceCount);
                        free(scene.vv_modelMat);

                case ADVANCEMENT_NULL:
        }
}
