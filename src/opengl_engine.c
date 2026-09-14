#include "glad/glad.h"
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
#include "context.h"

E_main fn_openGLEngineLoop()
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

        glDebugMessageCallback((GLDEBUGPROC)fn_openGLErrorCallback, NULL);

        glViewport(0, 0, event.windowWidth, event.windowHeight);


        //S_gltfSceneFileData gltfSceneFileData = fn_loadGltfSceneFileFormat("model_3d/Untitled.gltf", 0);
        S_gltfSceneFileData gltfSceneFileData = fn_loadGltfSceneFileFormat("cube.gltf", 0);
        if(gltfSceneFileData.error != HOLY_SUCCESS)
        {
                fprintf(stderr, "3D scene loading failed.\n");
                returnValue = HOL_CREATION_FAILED;
                goto GO_END_WINDOW;
        }
        //fn_printGltfFileData(gltfSceneFileData);

        S_openGLscene scene = fn_gltfSceneFileDataToOpenGLscene(gltfSceneFileData);



        mat4 projectionMat = GLM_MAT4_IDENTITY_INIT;
        glm_perspective(M_PI_2, (float)event.windowWidth/(float)event.windowHeight, 0.1f, 1000.0f, projectionMat);

        mat4 viewMat = GLM_MAT4_IDENTITY_INIT;





























/*
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
*/









        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        GLuint shaderProgram[2];
        GLuint vertexShader, fragmentShader;

        printf(ANSI_GREEN_TEXT("shader/flat/debug.vert")"\n");
        vertexShader = fn_compileOpenglShader("shader/flat/debug.vert", GL_VERTEX_SHADER);
        printf(ANSI_GREEN_TEXT("shader/flat/debug.frag\n")"\n");
        fragmentShader = fn_compileOpenglShader("shader/flat/debug.frag", GL_FRAGMENT_SHADER);
        printf("notnotnot\n");
        shaderProgram[0] = fn_createOpenglShaderProgram((GLuint[2]) {vertexShader, fragmentShader}, 2);

        glfwSwapInterval(1);

        float xRotation = 0.0f;
        float yRotation = 0.0f;

        vec3 position = {0.0f, 0.0f, 0.0f};

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glClearColor(0.2, 0.2, 0.2, 0.0);
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
                if(glfwGetKey(window, GLFW_KEY_SPACE))
                        position[Y] += 0.01;
                if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL))
                        position[Y] -= 0.01;


                // INFO : event handling
                if(event.type & EVENT_QUIT)
                {
                        running = false;
                }
                if(event.type & EVENT_WINDOW_SIZE)
                {
                        glm_perspective(M_PI_2, (float)event.windowWidth/(float)event.windowHeight, 0.1f, 1000.0f, projectionMat);
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
                glm_mat4_mul(projectionMat, viewMat, scene.projectionViewMat);
                scene.v_shader = shaderProgram;


                fn_openGLrender(scene);

                glfwSwapBuffers(window);
                glfwPollEvents();
        }

        fn_freeOpenGLscene(scene);
        glDeleteProgram(shaderProgram[0]);
        glDeleteProgram(shaderProgram[1]);

GO_END_WINDOW:
        glfwDestroyWindow(window);

GO_END:
        return returnValue;
}
