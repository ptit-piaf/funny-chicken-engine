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

        fprintf(stderr, ANSI_RED_TEXT("Start gltf parsing\n"));
        //S_model model = fn_loadGltfFileFormat("cube.gltf");
        //printf("the model is %d\n", model.error);

        glEnable(GL_DEBUG_OUTPUT);

        glDebugMessageCallback((GLDEBUGPROC)fn_openglErrorCallback, NULL);

        glViewport(0, 0, event.windowWidth, event.windowHeight);

        vec3 vertices [] =
                {
                        {-1.0f, -1.0f, 0.0},
                        {1.0f, -1.0f, 0.0},
                        {0.0f, 1.0f, 0.0}
                };
        vec3 cameraPosition = {0.0f, 0.0f, 0.0f};

        mat4 viewMatrix = GLM_MAT4_IDENTITY_INIT;
        mat4 projectionMatrix = GLM_MAT4_IDENTITY_INIT;
        glm_perspective(90.0f, 800.0f/500.0f, 0.01f, 100.0f, projectionMatrix);

        //mat4 viewMatrix = GLM_MAT4_IDENTITY_INIT;

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

        mat4 test2 = GLM_MAT4_IDENTITY_INIT;

        glClearColor(0.0, 1.0, 0.0, 0.0);
        bool running = true;
        while(running)
        {

                if(glfwGetKey(window, GLFW_KEY_W))
                        cameraPosition[2]+=0.01;
                if(glfwGetKey(window, GLFW_KEY_S))
                        cameraPosition[2]-=0.01;
                if(glfwGetKey(window, GLFW_KEY_A))
                        cameraPosition[0]-=0.01;
                if(glfwGetKey(window, GLFW_KEY_D))
                        cameraPosition[0]+=0.01;

                if(event.type & EVENT_QUIT)
                {
                        running = false;
                }
                else if(event.type & EVENT_MOUSE_POS)
                {
                        vec3 up = {0.0f, 1.0f, 0.0f}; //TODO : may be to adapte later

                        vec3 lookPoint =
                                {
                                        sin(event.xMouseMov * 0.001),
                                        0,
                                        cos(event.xMouseMov* 0.001)
                                };
                        mat4 test = GLM_MAT4_IDENTITY_INIT;
                        glm_lookat(cameraPosition, ADD_VEC3(cameraPosition, lookPoint), up, test);
                }

                glClear(GL_COLOR_BUFFER_BIT);

                test2[3][0] = cameraPosition[0];
                test2[3][1] = cameraPosition[1];
                test2[3][2] = cameraPosition[2];

                mat4 blabla = GLM_MAT4_IDENTITY_INIT;
                mat4 blabla2 = GLM_MAT4_IDENTITY_INIT;

                //glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "viewProjectionMatrix"), 0, GL_FALSE, (float*) blabla2);
                GLuint a = glGetUniformLocation(shaderProgram, "modelMatrix");
                fprintf(stderr, "a = %d\n", a);
                glUniformMatrix4fv(a, 0, GL_FALSE, (float*)blabla);

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
