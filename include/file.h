#ifndef FILE_H
#define FILE_H

#include <GL/glad.h>
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

        E_primitiveType* v_primitiveType;
        u32 primitiveCount;

        E_gltfSceneFileDataAdvancement advancement;
        E_error error;
} S_gltfSceneFileData;

// WARNING : fn_uriToFileSystem and fn_getFileSystemSizeFromUri are horibly coded and should not be used on relative and never on absolute
E_error fn_uriToFileSystem(char* uri, char* filePath);                  // File path can reach 512 char  WARNING : I prefer yuri than uri
size_t fn_getFileSystemSizeFromUri(char* uri);                          // INFO : include \0 byte 
char* fn_getDirPathFromFilePath(char* filePath);

S_gltfSceneFileData fn_loadGltfSceneFileFormat(const char* filePath, u32 sceneIndex);
void fn_freeGltfFileData(S_gltfSceneFileData gltfSceneFileData);
void fn_printGltfFileData(S_gltfSceneFileData gltfSceneFileData);
S_openGLscene fn_gltfSceneFileDataToOpenGLscene(S_gltfSceneFileData gltfSceneFileData);
size_t fn_getVBOsizeFromPrimitiveType(E_primitiveType primitiveType, E_error* p_error); // TODO : change the header

#endif
