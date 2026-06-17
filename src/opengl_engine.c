#include <GL/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <HOL/HOL_standard.h>

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
        if(version == 0)
        {
                fprintf(stderr, "glad failed to load\n");
                return HOL_CREATION_FAILED;
        }

        glEnable(GL_DEBUG_OUTPUT);

        glDebugMessageCallback((GLDEBUGPROC)fn_openglErrorCallback, NULL);

        glViewport(0, 0, event.windowWidth, event.windowHeight);


        S_model model3d = fn_loadGltfFileFormat("cube.glb");
        printf("primitive = %d\n", model3d.primitiveCount);
        for(u32 i=0; i<model3d.primitiveCount; i++)
        {
                printf("vertice count = %d", model3d.v_verticeCount[i]);
                //printf("vertice count = %d", model.v_indiceCount[i]);
        }

        mat4 projectionMat = GLM_MAT4_IDENTITY_INIT;
        glm_perspective(M_PI_2, (float)event.windowWidth/(float)event.windowHeight, 0.191919f, 10.0f, projectionMat);

        mat4 viewMat = GLM_MAT4_IDENTITY_INIT;













/*
        // INFO : temporary code

        vec3 vertices [] =
                {
                        {-1.0f, -1.0f, 0.0},
                        {1.0f, -1.0f, 0.0},
                        {1.0f, 1.0f, 0.0},
                        {-1.0, 1.0, 0.0}
                };

        u32 indice [] =
                {
                        0, 1, 2,
                        0, 2, 3
                };


        u32 test[1]={0};
        u32 test1[1]={0};
        u32 test2[1]={0};
        u32 test3[1]={6};
        u32 test4[1]={0};

        S_model model3d = 
                {
                        .v_vbo = test,
                        .v_vao = test1,
                        .v_ebo = test2,

                        .primitiveCount = 1,
                        .v_verticeCount = test3,
                        .v_indiceCount = test4,
                };

        glGenBuffers(1, &model3d.v_vbo[0]);
        glBindBuffer(GL_ARRAY_BUFFER, model3d.v_vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glGenVertexArrays(1, &model3d.v_vao[0]);
        glBindVertexArray(model3d.v_vao[0]);
        glBindBuffer(GL_ARRAY_BUFFER, model3d.v_vbo[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &model3d.v_ebo[0]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model3d.v_ebo[0]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indice), indice, GL_STATIC_DRAW);
*/



















        GLuint vertexShader, fragmentShader;
        vertexShader = fn_compileOpenglShader("test.vert", GL_VERTEX_SHADER);
        fragmentShader = fn_compileOpenglShader("test.frag", GL_FRAGMENT_SHADER);

        GLuint shaderProgram = fn_createOpenglShaderProgram((GLuint[2]) {vertexShader, fragmentShader}, 2);

        GLuint matrixLocation = glGetUniformLocation(shaderProgram, "modelMat");
        mat4 var = GLM_MAT4_IDENTITY_INIT;

        glfwSwapInterval(1);

        float xRotation = 0.0f;
        float yRotation = 0.0f;

        vec3 position = {0.0f, 0.0f, 0.0f};

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glClearColor(0.0, 1.0, 0.0, 0.0);
        bool running = true;
        while(running)
        {
                if(glfwGetKey(window, GLFW_KEY_D))
                {
                        position[0] += cos(xRotation+M_PI_2)*0.01;
                        position[2] += sin(xRotation+M_PI_2)*0.01;
                }
                if(glfwGetKey(window, GLFW_KEY_A))
                {
                        position[0] -= cos(xRotation+M_PI_2)*0.01;
                        position[2] -= sin(xRotation+M_PI_2)*0.01;
                }
                if(glfwGetKey(window, GLFW_KEY_S))
                {
                        position[0] -= cos(xRotation)*0.01;
                        position[2] -= sin(xRotation)*0.01;
                }
                if(glfwGetKey(window, GLFW_KEY_W))
                {
                        position[0] += cos(xRotation)*0.01;
                        position[2] += sin(xRotation)*0.01;
                }

                // INFO : event handling
                if(event.type & EVENT_QUIT)
                {
                        running = false;
                }
                if(event.type & EVENT_WINDOW_SIZE)
                {
                        glm_perspective(M_PI_2, (float)event.windowWidth/(float)event.windowHeight, 0.191919f, 10.0f, projectionMat);
                        glViewport(0, 0, event.windowWidth, event.windowHeight);
                }
                if(event.type & EVENT_MOUSE_POS)
                {
                        fn_updateViewMat(position, (vec3){0.0f,1.0f,0.0f}, xRotation, yRotation, viewMat);
                        xRotation += event.xMouseMov*0.01f;
                        yRotation += event.yMouseMov*0.01f;
                        event.xMouseMov = 0;
                        event.yMouseMov = 0;
                }








                // INFO : Rendering
                mat4 projectionViewMat;
                glm_mat4_mul(projectionMat, viewMat, projectionViewMat);

                glClear(GL_COLOR_BUFFER_BIT);
                glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projectionViewMat"), 1, GL_FALSE, *projectionViewMat);
                glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, *var);

                glUseProgram(shaderProgram);
                for(u32 i=0; i<model3d.primitiveCount; i++)
                {
                        glBindVertexArray(model3d.v_vao[i]);
                        glDrawElements(GL_TRIANGLES, 6,  GL_UNSIGNED_INT, NULL);
                }

                glfwSwapBuffers(window);
                glfwPollEvents();
        }

        glDeleteProgram(shaderProgram);

        glfwDestroyWindow(window);

GO_END:
        return returnValue;
}
