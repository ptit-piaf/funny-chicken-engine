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

void fn_createModelMat(vec3 translation, vec3 rotation, vec3 scale, mat4 dest)
{
        mat4 scaleMat = GLM_MAT4_IDENTITY_INIT;
        mat4 xRotationMat = GLM_MAT4_IDENTITY_INIT;
        mat4 yRotationMat = GLM_MAT4_IDENTITY_INIT;
        mat4 zRotationMat = GLM_MAT4_IDENTITY_INIT;
        mat4 translationMat = GLM_MAT4_IDENTITY_INIT;

        glm_scale(scaleMat, scale);
        glm_rotate_x(xRotationMat, rotation[0], xRotationMat);
        glm_rotate_y(yRotationMat, rotation[1], yRotationMat);
        glm_rotate_z(zRotationMat, rotation[2], zRotationMat);
        glm_translate(translationMat, translation);

        glm_mat4_mulN((mat4* []){&translationMat, &xRotationMat, &yRotationMat, &zRotationMat, &scaleMat}, 5, dest);
}
