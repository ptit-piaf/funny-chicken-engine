#include <GL/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include <stdio.h>
#include <stdlib.h>

#include "engine.h"
#include "fn_state.h"
#include "event.h"

const char* vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

E_main fn_openglEngineLoop()
{
        E_main returnValue = END;

        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        GLFWwindow* window = fn_createOpenglWindow();

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
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glGenV

        bool running = true;
        while(running)
        {
                if(event.type & EVENT_QUIT)
                        running = false;

                glUseProgram(shaderProgram);
                glBindVertexArray(vao);
                glDrawArrays(GL_TRIANGLES, 0, 3);

                glfwPollEvents();
        }

        glfwDestroyWindow(window);
        return returnValue;
}
