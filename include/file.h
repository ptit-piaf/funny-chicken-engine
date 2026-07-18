#ifndef FILE_H
#define FILE_H

#include <GL/glad.h>
#include <cglm/cglm.h>

typedef enum
{
         TEST
}test;

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

typedef struct S_scene //INFO : Need to improve the file format to include vulkan and to implente it more propely
{
        
} S_scene;

typedef struct S_gltfFileData
{
        /*void** v_preDethTestVboData;
        u32 preDethTestVboDataCount;
        void** v_preDethTestUboData;
        u32 preDethTestUboDataCount;

        void** v_preCullFaceTestVboData;
        u32 preCullFaceTestVboDataCount;
        void** v_preCullFaceTestUboData;
        u32 preCullFaceTestUboDataCount;

        void** v_vbodata;
        u32 v_vbodatacount;
        void** v_ubodata;
        u32 v_ubodatacount;*/

        void** vboData;
        u32* uboData;
        u32 primitiveCount;

        

        E_error error;
} S_gltfFileData;

S_model fn_loadGltfFileFormat(const char* filePath);
//S_gltfFileData fn_loadGltfFileFormat(const char* filePath);
void fn_free3DModel(S_model* model); // TODO : maybe in wrong header

#endif
