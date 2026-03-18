#include <GL/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include <stdio.h>
#include <stdlib.h>

#include "engine.h"
#include "fn_state.h"
#include "event.h"
#include "shader.h"

E_main fn_openglEngineLoop()
{
        E_main returnValue = END;

        GLFWwindow* window = fn_createOpenglWindow();
        if(!window)
                goto GO_END;

        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        S_event event = {0};
        glfwSetWindowUserPointer(window, &event);

        vec3 vertices [] =
                {
                        {-1.0f, 0.0f, -1.0f},
                        {1.0f, 0.0f, -1.0f},
                        {0.0f, 0.0f, 1.0f}
                };

        GLuint vao, vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*9, vertices, GL_STATIC_DRAW);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        GLuint vertexShader, fragmentShader;
        vertexShader = fn_compileOpenglShader("test.vert", GL_VERTEX_SHADER);
        fragmentShader = fn_compileOpenglShader("test.frag", GL_FRAGMENT_SHADER);

        GLuint shaderProgram = fn_createOpenglShaderProgram((GLuint[2]) {vertexShader, fragmentShader}, 2);

        glClearColor(0.0, 1.0, 0.0, 0.0);
        bool running = true;
        while(running)
        {
                if(event.type & EVENT_QUIT)
                        running = false;

                glClear(GL_COLOR_BUFFER_BIT);

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
