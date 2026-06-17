#ifndef MATH3D_H
#define MATH3D_H

#include <cglm/cglm.h>

#define ADD_VEC3(x, y) ((vec3){x[0]+y[0], x[1]+y[1], x[2]+y[2]})

void fn_updateViewMat(vec3 position, vec3 up, float xRotation, float yRotation, mat4 dest);

void fn_printMat4(mat4 matrix);

#endif
