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

        mat4 projectionMat = GLM_MAT4_IDENTITY_INIT;
        glm_perspective(M_PI_2, (float)event.windowWidth/(float)event.windowHeight, 0.191919f, 10.0f, projectionMat);

        mat4 viewMat = GLM_MAT4_IDENTITY_INIT;

        // INFO : temporary code

        vec3 vertices [] =
                {
                        {-1.0f, -1.0f, 0.0},
                        {1.0f, -1.0f, 0.0},
                        {0.0f, 1.0f, 0.0}
                };

        GLuint vao, vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);
        glEnableVertexAttribArray(0);

        GLuint vertexShader, fragmentShader;
        vertexShader = fn_compileOpenglShader("test.vert", GL_VERTEX_SHADER);
        fragmentShader = fn_compileOpenglShader("test.frag", GL_FRAGMENT_SHADER);

        GLuint shaderProgram = fn_createOpenglShaderProgram((GLuint[2]) {vertexShader, fragmentShader}, 2);

        GLuint matrixLocation = glGetUniformLocation(shaderProgram, "modelMat");
        mat4 var = GLM_MAT4_IDENTITY_INIT;

        glfwSwapInterval(1);

        float xRotation = 0.0f;
        float yRotation = 0.0f;

        vec3 // 

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glClearColor(0.0, 1.0, 0.0, 0.0);
        bool running = true;
        while(running)
        {
                printf(ANSI_YELLOW_TEXT("start of while loop\n"));

                if(glfwGetKey(window, GLFW_KEY_D))
                        var[3][0] += 0.01f;
                if(glfwGetKey(window, GLFW_KEY_A))
                        var[3][0] -= 0.01f;
                if(glfwGetKey(window, GLFW_KEY_S))
                        var[3][2] -= 0.01f;
                if(glfwGetKey(window, GLFW_KEY_W))
                        var[3][2] += 0.01f;

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
                        fn_updateViewMat((vec3){0.0f,0.0f,0.0f}, (vec3){0.0f,1.0f,0.0f}, xRotation+event.xMouseMov*0.01f,yRotation+event.yMouseMov*0.01f , viewMat);
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
                glBindVertexArray(vao);
                glDrawArrays(GL_TRIANGLES, 0, 3);

                glfwSwapBuffers(window);

                glfwPollEvents();

        }

        glDeleteProgram(shaderProgram);

        glfwDestroyWindow(window);

GO_END:
        return returnValue;
}
