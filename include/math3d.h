#ifndef MATH3D_H
#define MATH3D_H

#include <cglm/cglm.h>

void fn_updateViewMat(vec3 position, vec3 up, float xRotation, float yRotation, mat4 dest);

void fn_printMat4(mat4 matrix);

#endif
