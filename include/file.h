#ifndef FILE_H
#define FILE_H

#include "glad/glad.h"
#include <cglm/cglm.h>

#include "render.h"

typedef enum
{
        tmp
} E_gltfSceneFileDataAdvancement;

typedef struct S_gltfSceneFileData
{
        void** v_VBOdata;
        void** v_SSBOdata;
        void** v_UBOdata;
        u32** v_EBOdata;
        char** v_texturePath;
        u32* v_verticeCount;
        u32* v_indiceCount;

        U_primitiveType* v_primitiveType;
        u32 primitiveCount;

        E_gltfSceneFileDataAdvancement advancement;
        E_error error;
} S_gltfSceneFileData;

S_gltfSceneFileData fn_loadGltfSceneFileFormat(const char* filePath, u32 sceneIndex);
E_primitiveType fn_getJsonProp(char* jsonString, E_error* p_error);
void fn_freeGltfFileData(S_gltfSceneFileData gltfSceneFileData);

void fn_printGltfFileData(S_gltfSceneFileData gltfSceneFileData);

S_openGLscene fn_gltfSceneFileDataToOpenGLscene(S_gltfSceneFileData gltfSceneFileData);

#endif
