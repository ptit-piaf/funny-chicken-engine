#ifndef FILE_H
#define FILE_H

#include <GL/glad.h>
#include <cglm/cglm.h>

typedef enum
{
        PRE_DEPTH_TEST = 1,
        PRE_CLIP_FACE = (1<<2),
        BASE_COLOR_TEXTURE = (1<<3),

        

        MODEL_MAT_IN_VBO = (1<<16),  // NOTE : I still hate this name

        ERROR_MODE = 0XFFFFFFFF
} E_primitiveType;

typedef enum
{
        NONE,
        COMPLETE
} E_gltfSceneFileDataAdvancement;

typedef enum
{
        SUCCESS = 0,
        NOT_VALID_URI = 1,
        NOT_SUPPORTED = (1<<2),
} E_uriToFileSystem;

typedef struct
{
        GLuint* v_VBO;
        GLuint* v_SSBO;
        GLuint* v_TBO;
        GLuint* v_EBO;
        GLuint* v_VAO;

        u32* v_verticeCount;
        u32* v_indiceCount;
        mat4** vv_modelMat;
        u32 primitiveCount;

        E_error error;
} S_openGLscene; // TODO : I need to find a more appropriate header

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

S_gltfSceneFileData fn_loadGltfSceneFileFormat(const char* filePath, u32 sceneIndex);
void fn_freeGltfFileData(S_gltfSceneFileData gltfSceneFileData); // TODO : maybe in wrong header
void fn_printGltfFileData(S_gltfSceneFileData gltfSceneFileData);
S_openGLscene fn_gltfSceneFileDataToOpenGLscene(S_gltfSceneFileData gltfSceneFileData);
E_uriToFileSystem fn_uriToFileSystem(char* uri, char* filePath); // File path can reach 512 char  WARNING : I prefer yuri than uri

#endif
