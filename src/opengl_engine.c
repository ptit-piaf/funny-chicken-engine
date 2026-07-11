#include <nuklear.h>
#include <GL/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <stb_image.h>
#include <stb_truetype.h>

#include <stdio.h>
#include <stdlib.h>

#include "engine.h"
#include "fn_state.h"
#include "event.h"
#include "shader.h"
#include "file.h"
#include "error.h"
#include "math3d.h"

E_main fn_openglEngineLoop()
{
        E_main returnValue = END;

        GLFWwindow* window = fn_createOpenglWindow();
        if(!window)
                goto GO_END;
        S_event event = {0};
        glfwSetWindowUserPointer(window, &event);
        glfwGetWindowSize(window, &event.windowWidth, &event.windowHeight);

        i32 version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if(!version)
        {
                fprintf(stderr, "glad failed to load\n");
                returnValue = HOL_CREATION_FAILED;
                goto GO_END_WINDOW;
        }

        glEnable(GL_DEBUG_OUTPUT);

        glDebugMessageCallback((GLDEBUGPROC)fn_openglErrorCallback, NULL);

        glViewport(0, 0, event.windowWidth, event.windowHeight);


        S_model model3d = fn_loadGltfFileFormat("cube.glb");
        if(model3d.error != HOLY_SUCCESS)
        {
                fprintf(stderr, "3D scene loading failed.\n");
                returnValue = HOL_CREATION_FAILED;
                goto GO_END_WINDOW;
        }

        mat4 projectionMat = GLM_MAT4_IDENTITY_INIT;
        glm_perspective(M_PI_2, (float)event.windowWidth/(float)event.windowHeight, 0.0001f, 1000.0f, projectionMat);

        mat4 viewMat = GLM_MAT4_IDENTITY_INIT;






























        char charTable[128];
        for(u32 i=0; i<128; i++)
        {
                charTable[i] = i;
        }
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        i32 width, height, nrChannels;
        void* data = stbi_load("test.png", &width, &height, &nrChannels, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);


















        GLuint vertexShader, fragmentShader;
        vertexShader = fn_compileOpenglShader("test.vert", GL_VERTEX_SHADER);
        fragmentShader = fn_compileOpenglShader("test.frag", GL_FRAGMENT_SHADER);

        GLuint shaderProgram = fn_createOpenglShaderProgram((GLuint[2]) {vertexShader, fragmentShader}, 2);

        GLuint matrixLocation = glGetUniformLocation(shaderProgram, "modelMat");

        glfwSwapInterval(1);

        float xRotation = 0.0f;
        float yRotation = 0.0f;

        vec3 position = {0.0f, 0.0f, 0.0f};

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glClearColor(0.0, 1.0, 0.0, 0.0);
        bool running = true;
        while(running)
        {
                if(glfwGetKey(window, GLFW_KEY_A))
                {
                        position[0] -= cos(xRotation+M_PI_2)*0.01;
                        position[2] -= sin(xRotation+M_PI_2)*0.01;
                }
                if(glfwGetKey(window, GLFW_KEY_D))
                {
                        position[0] += cos(xRotation+M_PI_2)*0.01;
                        position[2] += sin(xRotation+M_PI_2)*0.01;
                }
                if(glfwGetKey(window, GLFW_KEY_W))
                {
                        position[0] += cos(xRotation)*0.01;
                        position[2] += sin(xRotation)*0.01;
                }
                if(glfwGetKey(window, GLFW_KEY_S))
                {
                        position[0] -= cos(xRotation)*0.01;
                        position[2] -= sin(xRotation)*0.01;
                }

                // INFO : event handling
                if(event.type & EVENT_QUIT)
                {
                        running = false;
                }
                if(event.type & EVENT_WINDOW_SIZE)
                {
                        glm_perspective(M_PI_2, (float)event.windowWidth/(float)event.windowHeight, 0.00001f, 1000.0f, projectionMat);
                        glViewport(0, 0, event.windowWidth, event.windowHeight);
                }
                if(event.type & EVENT_MOUSE_POS)
                {
                        fn_updateViewMat(position, (vec3){0.0f,1.0f,0.0f}, xRotation, yRotation, viewMat);
                        xRotation += event.xMouseMov*0.01f;
                        if(yRotation + event.yMouseMov*0.01f > M_PI_2-0.0001f)
                                yRotation = M_PI_2-0.0001;
                        else if(yRotation + event.yMouseMov*0.01f < -M_PI_2+0.0001f)
                                yRotation = -M_PI_2+0.0001;
                        else
                                yRotation += event.yMouseMov*0.01f;

                        event.xMouseMov = 0;
                        event.yMouseMov = 0;
                }








                // INFO : Rendering
                mat4 projectionViewMat;
                glm_mat4_mul(projectionMat, viewMat, projectionViewMat);

                glClear(GL_COLOR_BUFFER_BIT);
                glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projectionViewMat"), 1, GL_FALSE, *projectionViewMat);
                glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, *model3d.modelMat);

                glUseProgram(shaderProgram);
                for(u32 i=0; i<model3d.primitiveCount; i++)
                {
                        glBindVertexArray(model3d.v_vao[i]);
                        glDrawElements(GL_TRIANGLES, model3d.v_indiceCount[i],  GL_UNSIGNED_INT, NULL);
                }

                glfwSwapBuffers(window);
                glfwPollEvents();
        }

        fn_free3DModel(&model3d);

        glDeleteProgram(shaderProgram);

GO_END_WINDOW:
        glfwDestroyWindow(window);

GO_END:
        return returnValue;
}
