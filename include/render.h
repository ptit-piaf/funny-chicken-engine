#ifndef RENDER_H
#define RENDER_H

#include "glad/glad.h"
#include <cglm/cglm.h>

#include <stdint.h>

typedef enum
{
        TMP,
} E_openGLsceneAdvancement;

typedef enum
{
        // TODO : remove those 3(the sorting should do the work)
        PRE_DEPTH_TEST =                UINT64_C(1)<<0, // 1
        PRE_CLIP_FACE =                 UINT64_C(1)<<1, // 2
        VERTEX_INDICE =                 UINT64_C(1)<<2, // 4

        VERTEX_POSITION =               UINT64_C(1)<<3, // 8
        VERTEX_TEXTURE_COORD =          UINT64_C(1)<<4, // 10
        VERTEX_NORMAL =                 UINT64_C(1)<<5, // 20
        VERTEX_COLOR =                  UINT64_C(1)<<6, // 40

        BASE_COLOR_TEXTURE =            UINT64_C(1)<<10,

        MODEL_MAT_IN_VBO =              UINT64_C(1)<<32,                // NOTE : I still hate this name

        // render mode 48
        POINTS =                        (u64)GL_POINTS                     <<48,
        LINE_STRIP =                    (u64)GL_LINE_STRIP                 <<48,
        LINE_LOOP =                     (u64)GL_LINE_LOOP                  <<48,
        LINES =                         (u64)GL_LINES                      <<48,
        LINE_STRIP_ADJACENCY =          (u64)GL_LINE_STRIP_ADJACENCY       <<48,
        LINES_ADJACENCY =               (u64)GL_LINES_ADJACENCY            <<48,
        TRIANGLE_STRIP =                (u64)GL_TRIANGLE_STRIP             <<48,
        TRIANGLE_FAN =                  (u64)GL_TRIANGLE_FAN               <<48,
        TRIANGLES =                     (u64)GL_TRIANGLES                  <<48,
        TRIANGLE_STRIP_ADJACENCY =      (u64)GL_TRIANGLE_STRIP_ADJACENCY   <<48,
        TRIANGLES_ADJACENCY =           (u64)GL_TRIANGLES_ADJACENCY        <<48,
        PATCHES =                       (u64)GL_PATCHES                    <<48,


        // error 56
        UV_MISSING =                    UINT64_C(1)<<56,
        BASE_COLOR_TEXTURE_MISSING =    UINT64_C(1)<<57,

        PRIMITVE_ERROR =                UINT64_C(1)<<62,
        PRIMITVE_FATAL_ERROR =          UINT64_C(1)<<63,

        PRIMITIVE_TYPE_MAX =            UINT64_C(0XFFFFFFFFFFFFFFFF)    // INFO : 64 bit enum
} E_primitiveType;

typedef union
{
        E_primitiveType a;
        struct
        {
                u8 b1;
                u8 b2;
                u8 b3;
                u8 b4;
                u8 b5;
                u8 b6;
                u8 renderMode;
                u8 error;
        };
} U_primitiveType;

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
        u32* v_shaderIndex;

        GLuint* v_shader;

        u32* v_verticeCount;
        u32* v_indiceCount;
        U_primitiveType* v_primitiveType;
        mat4** vv_modelMat;

        mat4 projectionViewMat;

        u32 primitiveCount;
        E_openGLsceneAdvancement advancement;
        E_error error;
} S_openGLscene;

E_error fn_openGLrender(S_openGLscene scene);
void fn_freeOpenGLscene(S_openGLscene scene);

/*
 * TODO : a function to put in a order the opengl scene buffer for reducing the CPU/GPU over head
 */

#endif
