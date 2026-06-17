#include <cglm/cglm.h>

#include <stdio.h>
#include <stdlib.h>

#include "math3d.h"

void fn_updateViewMat(vec3 position, vec3 up, float xRotation, float yRotation, mat4 dest)
{
        vec3 center =
                {
                        cos(xRotation) * cos(yRotation),
                        sin(yRotation),
                        sin(xRotation) * cos(yRotation),
                };
        glm_lookat(position, ADD_VEC3(center, position), up, dest);
}

void fn_printMat4(mat4 matrix)
{
        for(u32 i=0; i<4; i++)
        {
                printf("| ");
                REPEAT(printf("%.4f\t",matrix[i][_]), 4);
                printf("|\n");
        }
}
