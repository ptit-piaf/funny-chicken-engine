#ifndef CONTEXT_H
#define CONTEXT_H

#include <GLFW/glfw3.h>
#include <GL/glad.h>

#include <stdio.h>

#include "render.h"

size_t fn_getVBOstride(E_primitiveType primitiveType); // TODO : find a better header
//S_vulkanContext fn_createVulkanContext();

GLFWwindow* fn_createOpenglWindow();

#endif
