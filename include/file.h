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

        mat4 modelMat;

        E_error error;
} S_model;  // INFO : I considere a model as only one mesh with multiple primitive

/*typedef struct S_scene INFO : Need to improve the file format to include vulkan and to implente it more propely
{
        
} S_scene;

typedef struct S_gltfFileData
{
        GLuint vbo;
} S_gltfFileData;*/

S_model fn_loadGltfFileFormat(const char* filePath);
void fn_free3DModel(S_model* model); // TODO : maybe in wrong header

#endif
