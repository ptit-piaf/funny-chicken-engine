#ifndef CONTEXT_H
#define CONTEXT_H

#include <GLFW/glfw3.h>
#include <cgltf/cgltf.h>
#include "glad/glad.h"

#include <stdio.h>

#include "render.h"

size_t fn_getVBOstride(E_primitiveType primitiveType); // TODO : find a better header

GLenum fn_getPrimitiveTypeFromCgltfPrimitiveType(cgltf_primitive_type cgltfPrimitiveType);

//S_vulkanContext fn_createVulkanContext();

GLFWwindow* fn_createOpenglWindow();

#endif
