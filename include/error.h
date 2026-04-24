#ifndef ERROR
#define ERROR

#include <GLFW/glfw3.h>

void fn_glfwErrorCallback(int errorCode, const char* errorName);
void fn_openglErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, void* userParam);
const char* fn_openGLErrorTypeName(GLenum type);

#endif
