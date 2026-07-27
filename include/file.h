#ifndef FILE_H
#define FILE_H

#include <GL/glad.h>
#include <cglm/cglm.h>

typedef enum
{
        PRE_DEPTH_TEST = 1,
        PRE_CLIP_FACE = 2,

        MODEL_MAT_IN_VBO = 4,  // INFO : I hate this name
} E_primitiveType;

typedef struct
{
        GLuint* v_VBO;
        GLuint* v_SSBO;
        GLuint* v_EBO;
        GLuint* v_VAO;

        u32* v_verticeCount;
        u32* v_indiceCount;
        u32 primitiveCount;

        E_error error;
} S_openGLscene; // INFO : I need to find a more appropriate header

typedef struct S_gltfFileData
{
        void** v_VBOdata;
        void** v_SSBOdata;
        u32** v_EBOdata;
        u32* v_verticeCount;
        u32* v_indiceCount;

        E_primitiveType* v_primitiveType;
        u32 primitiveCount;

        E_error error;
} S_gltfFileData;

S_gltfFileData fn_loadGltfFileFormat(const char* filePath);
void fn_freeGltfFileData(S_gltfFileData gltfFileData); // TODO : maybe in wrong header
void fn_printGltfFileData(S_gltfFileData gltfFileData);
S_openGLscene fn_gltfFileDataToOpenGLscene(S_gltfFileData gltfFileData);

#endif
