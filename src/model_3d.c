#include <GL/glad.h>
#include <cglm/cglm.h>
#include <cgltf/cgltf.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "math3d.h"

S_gltfFileData fn_loadGltfFileFormat(const char* filePath)
{
        S_gltfFileData gltfFileData = {0};

        if(!filePath)
        {
                gltfFileData.error = HOL_NULL_FILE_PATH;
                return gltfFileData;
        }

        cgltf_options option = {0};
        cgltf_data* fileData = NULL;
        cgltf_result result = cgltf_parse_file(&option, filePath, &fileData);
        if(result != cgltf_result_success)
        {
                gltfFileData.error = HOL_FILE_NOT_FIND;
                return gltfFileData;
        }
        cgltf_load_buffers(&option, fileData, filePath);

        printf("is it  working ??? %d\n", fileData->meshes[1].primitives[0].indices->count);

        for(u32 i=0; i<fileData->meshes_count; i++)
                gltfFileData.primitiveCount += fileData->meshes[i].primitives_count;

        u32* v_modelMatCount = calloc(sizeof(u32) * fileData->meshes_count, 1);
        mat4** vv_modelMat = malloc(sizeof(mat4*) * gltfFileData.primitiveCount);

        for(u32 i=0; i<fileData->nodes_count; i++)
        {
                if(!fileData->nodes[i].mesh)
                        continue;
                v_modelMatCount[fileData->nodes[i].mesh - fileData->nodes[0].mesh]++;  // WARNING : Maybe not very safe
        }

        for(u32 i=0; i<fileData->meshes_count; i++)
        {
                if(!fileData->nodes[i].mesh)
                        continue;

                if(v_modelMatCount[i] == 0)
                        v_modelMatCount[i] = 1;

                vv_modelMat[i] = malloc(sizeof(mat4) * v_modelMatCount[i]);

                // WARNING : Not good loop to change
                for(u32 j=0; j<1; j++)
                {
                        if(!fileData->nodes[j].mesh)
                                continue;
                        if(fileData->nodes[j].has_matrix)
                        {
                                memcpy(vv_modelMat[i][j], fileData->nodes[j].matrix, sizeof(mat4));
                                continue;
                        }

                        vec3 translation = {0.0f, 0.0f, 0.0f};
                        vec4 rotation = {0.0f, 0.0f, 0.0f, 1.0f};
                        vec3 scale = {1.0f, 1.0f, 1.0f};

                        if(fileData->nodes[j].has_translation)
                        {
                                translation[0] = fileData->nodes[j].translation[0];
                                translation[1] = fileData->nodes[j].translation[1];
                                translation[2] = fileData->nodes[j].translation[2];
                        }
                        if(fileData->nodes[j].has_rotation)
                        {
                                rotation[0] = fileData->nodes[j].rotation[0];
                                rotation[1] = fileData->nodes[j].rotation[1];
                                rotation[2] = fileData->nodes[j].rotation[2];
                        }
                        if(fileData->nodes[j].has_scale)
                        {
                                scale[0] = fileData->nodes[j].scale[0];
                                scale[1] = fileData->nodes[j].scale[1];
                                scale[2] = fileData->nodes[j].scale[2];
                        }

                        fn_createModelMat(translation, rotation, scale, vv_modelMat[i][j]);
                }
                for(u32 j=0; j<fileData->nodes_count; j++)
                {
                        fn_printMat4(vv_modelMat[i][j]);
                        printf("\n");
                }
                free(vv_modelMat[i]);
        }
        gltfFileData.v_SSBOdata = NULL; // TODO :


        gltfFileData.v_VBOdata = malloc(sizeof(void*) * gltfFileData.primitiveCount);
        gltfFileData.v_EBOdata = malloc(sizeof(u32*) * gltfFileData.primitiveCount);
        gltfFileData.v_verticeCount = malloc(sizeof(u32) * gltfFileData.primitiveCount);
        gltfFileData.v_indiceCount = malloc(sizeof(u32) * gltfFileData.primitiveCount);


        printf("meshes count %d\n", fileData->meshes_count);

        u32 primitiveIndex = 0;
        for(u32 i=0; i<fileData->meshes_count; i++)
        {
                for(u32 j=0; j<fileData->meshes[i].primitives_count; j++)
                {

                        printf("primitive count %d\n", fileData->meshes[0].primitives_count);
                        cgltf_attribute positionAttribute, normalAttribute, uvAttribute;
                        for(u32 o=0; o<fileData->meshes[i].primitives[j].attributes_count; o++)
                                switch(fileData->meshes[i].primitives[j].attributes[o].type)
                                {
                                        case cgltf_attribute_type_position:
                                                positionAttribute = fileData->meshes[i].primitives[j].attributes[o];
                                                break;
                                }

                        gltfFileData.v_verticeCount[primitiveIndex] = positionAttribute.data->count;
                        gltfFileData.v_indiceCount[primitiveIndex] = fileData->meshes[i].primitives[j].indices->count;
                        fprintf(stderr, "vertice count = %d\n", positionAttribute.data->count);
                        gltfFileData.v_VBOdata[primitiveIndex] = malloc(sizeof(vec3) * positionAttribute.data->count);
                        for(u32 o=0; o<positionAttribute.data->count; o++)
                                cgltf_accessor_read_float(positionAttribute.data, o, ((vec3*)gltfFileData.v_VBOdata[primitiveIndex])[o], 3);



                        gltfFileData.v_EBOdata[primitiveIndex] = malloc(sizeof(u32) * fileData->meshes[i].primitives[j].indices->count);
                        printf("what ??????? %d\n", fileData->meshes[1].primitives[0].indices->is_sparse);
                        for(u32 o=0; o<fileData->meshes[i].primitives[j].indices->count; o++)
                                cgltf_accessor_read_uint(fileData->meshes[i].primitives[j].indices, o, &gltfFileData.v_EBOdata[primitiveIndex][o], 1);

                        primitiveIndex++;
                        printf("i = %d\n", i);
                }
        }

// WARNING : do not forget to free all allocated buffer.

        cgltf_free(fileData);
        return gltfFileData;
}

void fn_printGltfFileData(S_gltfFileData gltfFileData)
{
        printf("gltf file data :\n");
        printf("primitive count = %d\n", gltfFileData.primitiveCount);
        printf("SSBO in construction\n");
        for(u32 i=0; i<gltfFileData.primitiveCount; i++)
        {
                printf("primitive[%d]\n", i);
                printf("\tvbo :\n\t\tposition\n");
                for(u32 j=0; j<gltfFileData.v_verticeCount[i]; j++)
                {
                        printf("j=%d\n", j);
                        printf("\t\t\t(%f, %f, %f)\n", ((vec3*)gltfFileData.v_VBOdata[i])[j][0], ((vec3*)gltfFileData.v_VBOdata[i])[j][1], ((vec3*)gltfFileData.v_VBOdata[i])[j][2]);
                }
                printf("\t\tebo\n\t\t\t[ ");
                for(u32 j=0; j<gltfFileData.v_verticeCount[i]; j++)
                        printf("%d ",gltfFileData.v_EBOdata[i][j]);
                printf("]\n");
        }
}



void fn_freeGltfFileData(S_gltfFileData gltfFileData) // TODO : 
{
        return;
}

S_openGLscene fn_gltfFileDataToOpenGLscene(S_gltfFileData gltfFileData) // INFO : The function do not check if the parameter are ok
{
        S_openGLscene scene = {0};

        scene.v_VBO = malloc(sizeof(u32) * gltfFileData.primitiveCount);
        scene.v_SSBO = NULL;
        scene.v_EBO = malloc(sizeof(u32) * gltfFileData.primitiveCount);
        scene.v_VAO = malloc(sizeof(u32) * gltfFileData.primitiveCount);

        scene.v_verticeCount = malloc(sizeof(u32) * gltfFileData.primitiveCount);
        scene.v_indiceCount = malloc(sizeof(u32) * gltfFileData.primitiveCount);
        scene.primitiveCount = gltfFileData.primitiveCount;

        glGenBuffers(gltfFileData.primitiveCount, scene.v_VBO);
        glGenBuffers(gltfFileData.primitiveCount, scene.v_EBO);

        glGenVertexArrays(gltfFileData.primitiveCount, scene.v_VAO);

        for(u32 i=0; i<gltfFileData.primitiveCount; i++)
        {
                scene.v_verticeCount[i] = gltfFileData.v_verticeCount[i];
                scene.v_indiceCount[i] = gltfFileData.v_indiceCount[i];

                glBindVertexArray(scene.v_VAO[i]);

                glBindBuffer(GL_ARRAY_BUFFER, scene.v_VBO[i]);
                glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * scene.v_verticeCount[i], gltfFileData.v_VBOdata[i], GL_STATIC_DRAW);

                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);
                glEnableVertexAttribArray(0);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, scene.v_EBO[i]);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * scene.v_indiceCount[i], gltfFileData.v_EBOdata[i], GL_STATIC_DRAW);
        }

        return scene;
}
