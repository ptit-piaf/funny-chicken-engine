#ifndef RENDER_H
#define RENDER_H

#include <GL/glad.h>
#include <cglm/cglm.h>

typedef enum
{
        TMP,
} E_openGLsceneAdvancement;

typedef struct
{
        vec3 position;
        vec2 uv;
} S_VBO;

typedef struct
{
        GLuint* v_VBO;
        GLuint* v_VAO;
        GLuint* v_SSBO;
        GLuint* v_TBO;
        GLuint* v_EBO;
        GLuint* v_shader;

        u32* v_verticeCount;
        u32* v_indiceCount;
        mat4** vv_modelMat;

        mat4 projectionViewMat;

        u32 primitiveCount;
        E_openGLsceneAdvancement advancement;
        E_error error;
} S_openGLscene;

typedef enum
{
        PRE_DEPTH_TEST =                (1LL<<0),
        PRE_CLIP_FACE =                 (1LL<<2),

        BASE_COLOR_TEXTURE =            (1LL<<3),

        UV_MISSING =                    (1LL<<30),
        BASE_COLOR_TEXTURE_MISSING =    (1LL<<31),

        MODEL_MAT_IN_VBO =              (1LL<<32),                // NOTE : I still hate this name

        PRIMITVE_ERROR =                (1LL<<62),
        PRIMITVE_FATAL_ERROR =          (1LL<<63),

        PRIMITIVE_TYPE_MAX =            0XFFFFFFFFFFFFFFFFLL    // INFO : 64 bit enum
} E_primitiveType;

E_error fn_openGLrender(S_openGLscene scene);
void fn_freeOpenGLscene(S_openGLscene scene);

/*
 * TODO : a function to put in a order the opengl scene buffer for reducing the CPU/GPU over head
 */

#endif
