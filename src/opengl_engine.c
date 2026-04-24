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

        glDepthRange(-100.0f, 100.0f);

        GLuint matrixLocation = glGetUniformLocation(shaderProgram, "modelMat");
        mat4 var = GLM_MAT4_IDENTITY_INIT;

        mat4 var2 = GLM_MAT4_IDENTITY_INIT;
        printf("event aspect = %f\n", event.windowWidth/event.windowHeight);
        glm_perspective(M_PI_2, (float)event.windowWidth/(float)event.windowHeight, 0.191919f, 10.0f, var2);
        for(int i=0; i<4; i++)
        {
                printf("|[");
                REPEAT(printf("%f, ", var2[i][_]), 3);
                printf("]\n");
                printf("|\n");
        }

        glfwSwapInterval(1);

        glClearColor(0.0, 1.0, 0.0, 0.0);
        bool running = true;
        while(running)
        {
                if(glfwGetKey(window, GLFW_KEY_D))
                        var[3][0] += 0.01f;
                if(glfwGetKey(window, GLFW_KEY_A))
                        var[3][0] -= 0.01f;
                if(glfwGetKey(window, GLFW_KEY_S))
                        var[3][2] -= 0.01f;
                if(glfwGetKey(window, GLFW_KEY_W))
                        var[3][2] += 0.01f;

                if(event.type & EVENT_QUIT)
                {
                        running = false;
                }

                glm_perspective(M_PI_2, (float)event.windowWidth/(float)event.windowHeight, 0.191919f, 10.0f, var2);

                glClear(GL_COLOR_BUFFER_BIT);
                glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projectionViewMat"), 1, GL_FALSE, *var2);
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
