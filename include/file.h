#ifndef FILE_H
#define FILE_H

#include <GL/glad.h>
#include <cglm/cglm.h>

typedef struct  // TODO : See in the future is This struct should be in an other header
{
        GLuint* v_vbo;
        GLuint* v_vao;
        GLuint* v_ebo;

        u32 primitiveCount;
        u32* v_verticeCount;
        u32* v_indiceCount;

        E_error error;
} S_model;  // INFO : I considere a model as only one mesh with multiple primitive

S_model fn_loadGltfFileFormat(const char* filePath);

#endif
