#include "glad/glad.h"
#include <cglm/cglm.h>
#include <cgltf/cgltf.h>
#include <stb_image.h>
#include <yyjson.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "file.h"
#include "render.h"
#include "shader.h"
#include "math3d.h"
#include "context.h"

S_gltfSceneFileData fn_loadGltfSceneFileFormat(const char* filePath, u32 sceneIndex)
{
        S_gltfSceneFileData gltfSceneFileData = {0};

        char* dirPath = HOL_getDirPathFromFilePath(filePath);

        if(!filePath)
        {
                gltfSceneFileData.error = HOL_NULL_FILE_PATH;
                return gltfSceneFileData;
        }

        cgltf_options option = {0};
        cgltf_data* fileData = NULL;
        cgltf_result cgltfResult = cgltf_parse_file(&option, filePath, &fileData);
        if(cgltfResult != cgltf_result_success)
        {
                gltfSceneFileData.error = HOL_FILE_NOT_FIND;
                return gltfSceneFileData;
        }

        if(fileData->scenes_count <= sceneIndex)
        {
                gltfSceneFileData.error = HOL_PARSING_FAILED;
                gltfSceneFileData.advancement = ADVANCEMENT_NULL;
                goto GO_END;
        }

        u32 sceneMeshCount = 0;
        cgltf_mesh** vp_sceneMesh = NULL;
        for(u32 i=0; i<fileData->scenes[sceneIndex].nodes_count; i++)
        {
                if(!fileData->scenes[sceneIndex].nodes[i])
                        continue;
                bool meshInSceneMesh = false;
                for(u32 j=0; j<sceneMeshCount; j++)
                        if(vp_sceneMesh[j] == fileData->scenes[sceneIndex].nodes[i]->mesh)
                        {
                                meshInSceneMesh = true;
                                break;
                        }

                if(!meshInSceneMesh)
                {
                        sceneMeshCount++;
                        vp_sceneMesh = realloc(vp_sceneMesh, sceneMeshCount);
                        vp_sceneMesh[i] = fileData->scenes[sceneIndex].nodes[i]->mesh;
                }
        }

        for(u32 i=0; i<sceneMeshCount; i++)
                gltfSceneFileData.primitiveCount += vp_sceneMesh[i]->primitives_count;

        // INFO : the following malloc that allow array of pointer are not very optimize.
        // Those ptr may point to a NULL adress when a functionnality is not used.
        gltfSceneFileData.v_VBOdata = malloc(sizeof(void*) * gltfSceneFileData.primitiveCount);
        gltfSceneFileData.v_UBOdata = malloc(sizeof(void*) * gltfSceneFileData.primitiveCount);
        gltfSceneFileData.v_SSBOdata = malloc(sizeof(void*) * gltfSceneFileData.primitiveCount);
        gltfSceneFileData.v_EBOdata = malloc(sizeof(u32*) * gltfSceneFileData.primitiveCount);
        gltfSceneFileData.v_texturePath = malloc(sizeof(char*) * gltfSceneFileData.primitiveCount);
        gltfSceneFileData.v_primitiveType = malloc(sizeof(u32) * gltfSceneFileData.primitiveCount);
        gltfSceneFileData.v_verticeCount = malloc(sizeof(u32) * gltfSceneFileData.primitiveCount);
        gltfSceneFileData.v_indiceCount = malloc(sizeof(u32) * gltfSceneFileData.primitiveCount);

        cgltf_load_buffers(&option, fileData, filePath);
        // TODO : the fn to get a mat from a quaternion glm_quat_mat4



        u32 primitiveIndex = 0;
        for(u32 i=0; i<sceneMeshCount; i++)
        {
                mat4* v_modelMat = NULL;
                u32 nodeCountPerMesh = 1;
                for(u32 j=0; j<fileData->scenes[sceneIndex].nodes_count; j++)
                {
                        if(fileData->nodes[j].mesh != vp_sceneMesh[i])
                                continue;
                        nodeCountPerMesh++;
                        v_modelMat = realloc(v_modelMat, sizeof(mat4) * nodeCountPerMesh);

                        vec3 scaleVec = {1.0f, 1.0f, 1.0f};
                        vec4 rotationVec = {1.0f, 0.0f, 0.0f, 0.0f}; // WARNING : I'm not sure that this is the correct quaternion
                        vec3 translationVec = {0.0f, 0.0f, 0.0f};

                        if(fileData->scenes[sceneIndex].nodes[j]->has_scale)
                        {
                                scaleVec[0] = fileData->scenes[sceneIndex].nodes[j]->scale[0];
                                scaleVec[1] = fileData->scenes[sceneIndex].nodes[j]->scale[1];
                                scaleVec[2] = fileData->scenes[sceneIndex].nodes[j]->scale[2];
                        }
                        if(fileData->scenes[sceneIndex].nodes[j]->has_rotation)
                        {
                                rotationVec[0] = fileData->scenes[sceneIndex].nodes[j]->rotation[0];
                                rotationVec[1] = fileData->scenes[sceneIndex].nodes[j]->rotation[1];
                                rotationVec[2] = fileData->scenes[sceneIndex].nodes[j]->rotation[2];
                                rotationVec[3] = fileData->scenes[sceneIndex].nodes[j]->rotation[3];
                        }
                        if(fileData->scenes[sceneIndex].nodes[j]->has_translation)
                        {
                                translationVec[0] = fileData->scenes[sceneIndex].nodes[j]->translation[0];
                                translationVec[1] = fileData->scenes[sceneIndex].nodes[j]->translation[1];
                                translationVec[2] = fileData->scenes[sceneIndex].nodes[j]->translation[2];
                        }

                        fn_createModelMat(translationVec, rotationVec, scaleVec, v_modelMat[j]);
                }



                // TODO : implemente other extra variable (only if necessary)
                b8 meshTypeFound = false;
                E_error result;
                E_primitiveType meshType = fn_getJsonProp(vp_sceneMesh[i]->extras.data, &result);
                if(result == HOLY_SUCCESS)
                        meshTypeFound = true;

                for(u32 j=0; j<vp_sceneMesh[i]->primitives_count; j++, primitiveIndex++)
                {

                        b8 primitiveTypeFound = false;
                        gltfSceneFileData.v_primitiveType[primitiveIndex].a = fn_getJsonProp(vp_sceneMesh[i]->primitives[j].extras.data, &result) | meshType;

                        if(vp_sceneMesh[i]->primitives[j].indices)
                                gltfSceneFileData.v_primitiveType[primitiveIndex].a |= VERTEX_INDICE;

                        cgltf_attribute positionAttribute = {0};
                        cgltf_attribute normalAttribute = {0};
                        cgltf_attribute uvAttribute = {0};
                        cgltf_attribute colorAttribute = {0};
                        for(u32 o=0; o<vp_sceneMesh[i]->primitives[j].attributes_count; o++)
                                switch(vp_sceneMesh[i]->primitives[j].attributes[o].type)
                                {
                                        case cgltf_attribute_type_position:
                                                if(!primitiveTypeFound)
                                                        gltfSceneFileData.v_primitiveType[primitiveIndex].a |= VERTEX_POSITION;
                                                positionAttribute = vp_sceneMesh[i]->primitives[j].attributes[o];
                                                break;
                                        case cgltf_attribute_type_texcoord:
                                                if(!primitiveTypeFound)
                                                        gltfSceneFileData.v_primitiveType[primitiveIndex].a |= VERTEX_TEXTURE_COORD;
                                                uvAttribute = vp_sceneMesh[i]->primitives[j].attributes[o];
                                                break;

                                        case cgltf_attribute_type_normal:
                                                if(!primitiveTypeFound)
                                                        gltfSceneFileData.v_primitiveType[primitiveIndex].a |= VERTEX_NORMAL;
                                                normalAttribute = vp_sceneMesh[i]->primitives[j].attributes[o];
                                                break;

                                        case cgltf_attribute_type_color:
                                                if(!primitiveTypeFound)
                                                        gltfSceneFileData.v_primitiveType[primitiveIndex].a |= VERTEX_COLOR;
                                                colorAttribute = vp_sceneMesh[i]->primitives[j].attributes[o];
                                                break;
                                }

                        if((gltfSceneFileData.v_primitiveType[primitiveIndex].a & VERTEX_POSITION && !positionAttribute.data) ||
                                (gltfSceneFileData.v_primitiveType[primitiveIndex].a & VERTEX_TEXTURE_COORD && !uvAttribute.data) ||
                                (gltfSceneFileData.v_primitiveType[primitiveIndex].a & VERTEX_NORMAL && !normalAttribute.data) ||
                                (gltfSceneFileData.v_primitiveType[primitiveIndex].a & VERTEX_COLOR && !colorAttribute.data))
                        {
                                gltfSceneFileData.v_primitiveType[primitiveIndex].a |= PRIMITVE_FATAL_ERROR;
                                continue;
                        }

                        if(vp_sceneMesh[i]->primitives[j].material)
                                if(!primitiveTypeFound && vp_sceneMesh[i]->primitives[j].material->pbr_metallic_roughness.base_color_texture.texture)
                                {
                                        if(!(gltfSceneFileData.v_primitiveType[primitiveIndex].a & VERTEX_TEXTURE_COORD))
                                                gltfSceneFileData.v_primitiveType[primitiveIndex].a |= UV_MISSING | PRIMITVE_ERROR;
                                        gltfSceneFileData.v_primitiveType[primitiveIndex].a |= BASE_COLOR_TEXTURE;
                                }






                        size_t VBOoffset = 0;
                        gltfSceneFileData.v_VBOdata[primitiveIndex] = malloc(fn_getVBOstride(gltfSceneFileData.v_primitiveType[i].a) * positionAttribute.data->count);
                        gltfSceneFileData.v_verticeCount[primitiveIndex] = positionAttribute.data->count;
                        if(gltfSceneFileData.v_primitiveType[primitiveIndex].a & VERTEX_POSITION)
                        {
                                for(u32 o=0; o<positionAttribute.data->count; o++)
                                        cgltf_accessor_read_float(positionAttribute.data, o, gltfSceneFileData.v_VBOdata[primitiveIndex]+ o*fn_getVBOstride(gltfSceneFileData.v_primitiveType[i].a) + VBOoffset, 3);
                                VBOoffset += sizeof(vec3);
                        }

                        if(gltfSceneFileData.v_primitiveType[primitiveIndex].a & VERTEX_TEXTURE_COORD)
                        {
                                for(u32 o=0; o<uvAttribute.data->count; o++)
                                {
                                        cgltf_accessor_read_float(uvAttribute.data, o, gltfSceneFileData.v_VBOdata[primitiveIndex]+ o*fn_getVBOstride(gltfSceneFileData.v_primitiveType[i].a) + VBOoffset, 2);
                                }
                                VBOoffset += sizeof(vec2);
                        }

                        if(gltfSceneFileData.v_primitiveType[primitiveIndex].a & VERTEX_NORMAL)
                        {
                                for(u32 o=0; o<normalAttribute.data->count; o++)
                                {
                                        cgltf_accessor_read_float(normalAttribute.data, o, gltfSceneFileData.v_VBOdata[primitiveIndex]+ o*fn_getVBOstride(gltfSceneFileData.v_primitiveType[i].a) + VBOoffset, 3);
                                }

                                VBOoffset += sizeof(vec3);
                        }

                        if(gltfSceneFileData.v_primitiveType[primitiveIndex].a & VERTEX_COLOR)
                        {
                                for(u32 o=0; o<colorAttribute.data->count; o++)
                                {
                                        cgltf_accessor_read_float(colorAttribute.data, o, gltfSceneFileData.v_VBOdata[primitiveIndex]+ o*fn_getVBOstride(gltfSceneFileData.v_primitiveType[i].a) + VBOoffset, 4);
                                }
                                VBOoffset += sizeof(vec4);
                        }



                        if(gltfSceneFileData.v_primitiveType[primitiveIndex].a & VERTEX_INDICE)
                        {
                                gltfSceneFileData.v_indiceCount[primitiveIndex] = vp_sceneMesh[i]->primitives[j].indices->count;
                                gltfSceneFileData.v_EBOdata[primitiveIndex] = malloc(sizeof(u32) * vp_sceneMesh[i]->primitives[j].indices->count);
                                for(u32 o=0; o<vp_sceneMesh[i]->primitives[j].indices->count; o++)
                                {
                                        cgltf_accessor_read_uint(vp_sceneMesh[i]->primitives[j].indices, o, &gltfSceneFileData.v_EBOdata[primitiveIndex][o], 1);
                                }
                        }







                        if(gltfSceneFileData.v_primitiveType[primitiveIndex].a & BASE_COLOR_TEXTURE)
                        {
                                char filePathFromUri[512];
                                E_error result = HOL_getUnixFilePathFromUri(vp_sceneMesh[i]->primitives[j].material->pbr_metallic_roughness.base_color_texture.texture->image->uri,
                                                                            filePathFromUri, 512);
                                if(result != HOLY_SUCCESS)
                                {
                                        if(gltfSceneFileData.v_primitiveType[primitiveIndex].a & BASE_COLOR_TEXTURE)
                                                gltfSceneFileData.v_primitiveType[primitiveIndex].a |= BASE_COLOR_TEXTURE_MISSING | PRIMITVE_ERROR;
                                        continue;
                                }

                                if(filePathFromUri[0] == '/')
                                {
                                        gltfSceneFileData.v_texturePath[primitiveIndex] = malloc(strlen(filePathFromUri)+1);
                                        strcpy(gltfSceneFileData.v_texturePath[primitiveIndex], filePathFromUri);
                                }
                                else
                                {
                                        u32 offset = 0;
                                        if(dirPath)
                                                offset = strlen(dirPath);
                                        gltfSceneFileData.v_texturePath[primitiveIndex] = malloc(offset + strlen(filePathFromUri)+1);
                                        if(dirPath)
                                                strcpy(gltfSceneFileData.v_texturePath[primitiveIndex], dirPath);
                                        strcat(gltfSceneFileData.v_texturePath[primitiveIndex], filePathFromUri);
                                }
                        }


                }
                free(v_modelMat);
        }

// WARNING : do not forget to free all allocated buffer.

        free(vp_sceneMesh);

GO_END:
        free(dirPath);
        cgltf_free(fileData);
        return gltfSceneFileData;
}

void fn_printGltfFileData(S_gltfSceneFileData gltfSceneFileData)
{
        printf("gltf file data :\n");
        printf("primitive count = %d\n", gltfSceneFileData.primitiveCount);
        printf("SSBO in construction\n");
        for(u32 i=0; i<gltfSceneFileData.primitiveCount; i++)
        {
                printf("primitive[%d]\n", i);
                printf("\tvbo :\n\t\tposition\n");
                for(u32 j=0; j<gltfSceneFileData.v_verticeCount[i]; j++)
                {
                        printf("j=%d\n", j);
                        printf("\t\t\t(%f, %f, %f)\n", ((vec3*)gltfSceneFileData.v_VBOdata[i])[j][0], ((vec3*)gltfSceneFileData.v_VBOdata[i])[j][1], ((vec3*)gltfSceneFileData.v_VBOdata[i])[j][2]);
                }
                printf("\t\tebo\n\t\t\t[ ");
                for(u32 j=0; j<gltfSceneFileData.v_indiceCount[i]; j++)
                        printf("%d ",gltfSceneFileData.v_EBOdata[i][j]);
                printf("]\n");
        }
}



void fn_freeGltfFileData(S_gltfSceneFileData gltfSceneFileData) // TODO : 
{
        switch(gltfSceneFileData.advancement)
        {
                case ADVANCEMENT_COMPLETE:
                        for(u32 i=0; i<gltfSceneFileData.primitiveCount; i++)
                        {
                                if(gltfSceneFileData.v_VBOdata[i])
                                        free(gltfSceneFileData.v_VBOdata[i]);
                                if(gltfSceneFileData.v_SSBOdata[i])
                                        free(gltfSceneFileData.v_SSBOdata[i]);
                                if(gltfSceneFileData.v_UBOdata[i])
                                        free(gltfSceneFileData.v_UBOdata[i]);
                                if(gltfSceneFileData.v_EBOdata[i])
                                        free(gltfSceneFileData.v_EBOdata[i]);
                                if(gltfSceneFileData.v_texturePath[i])
                                        free(gltfSceneFileData.v_texturePath[i]);
                        }

                        free(gltfSceneFileData.v_VBOdata);
                        free(gltfSceneFileData.v_UBOdata);
                        free(gltfSceneFileData.v_SSBOdata);
                        free(gltfSceneFileData.v_EBOdata);
                        free(gltfSceneFileData.v_texturePath);
                        free(gltfSceneFileData.v_primitiveType);
                        free(gltfSceneFileData.v_verticeCount);
                        free(gltfSceneFileData.v_indiceCount);

                case ADVANCEMENT_NULL:
        }
        return;
}

S_openGLscene fn_gltfSceneFileDataToOpenGLscene(S_gltfSceneFileData gltfSceneFileData) // INFO : The function do not check if the parameter are ok
{
        S_openGLscene scene = {0};

        scene.v_VBO = malloc(sizeof(GLuint) * gltfSceneFileData.primitiveCount);
        scene.v_SSBO = NULL;
        scene.v_EBO = malloc(sizeof(GLuint) * gltfSceneFileData.primitiveCount);
        scene.v_VAO = malloc(sizeof(GLuint) * gltfSceneFileData.primitiveCount);

        scene.v_verticeCount = malloc(sizeof(GLuint) * gltfSceneFileData.primitiveCount);
        scene.v_indiceCount = malloc(sizeof(GLuint) * gltfSceneFileData.primitiveCount);
        scene.v_TBO = malloc(sizeof(GLuint) * gltfSceneFileData.primitiveCount);
        scene.primitiveCount = gltfSceneFileData.primitiveCount;
        scene.v_primitiveType = malloc(sizeof(E_primitiveType) * gltfSceneFileData.primitiveCount);

        glGenBuffers(gltfSceneFileData.primitiveCount, scene.v_VBO);
        glGenBuffers(gltfSceneFileData.primitiveCount, scene.v_EBO);


        for(u32 i=0; i<gltfSceneFileData.primitiveCount; i++)
        glGenVertexArrays(gltfSceneFileData.primitiveCount, scene.v_VAO);

        for(u32 i=0; i<gltfSceneFileData.primitiveCount; i++)
        {
                scene.v_verticeCount[i] = gltfSceneFileData.v_verticeCount[i];
                scene.v_indiceCount[i] = gltfSceneFileData.v_indiceCount[i];
                scene.v_primitiveType[i].a = gltfSceneFileData.v_primitiveType[i].a;
                printf("primitive = %x\n", scene.v_primitiveType[i].a);

                glBindVertexArray(scene.v_VAO[i]);

                void* vertexOffset = (void*) 0;
                size_t VBOstride = fn_getVBOstride(scene.v_primitiveType[i].a);


                glBindBuffer(GL_ARRAY_BUFFER, scene.v_VBO[i]);
                glBufferData(GL_ARRAY_BUFFER, scene.v_verticeCount[i] * VBOstride, gltfSceneFileData.v_VBOdata[i], GL_STATIC_DRAW);

                glVertexAttribPointer(POSITION_VERTEX_BUFFER_LOCATION, 3, GL_FLOAT, GL_FALSE, VBOstride, vertexOffset);
                glEnableVertexAttribArray(POSITION_VERTEX_BUFFER_LOCATION);

                vertexOffset += sizeof(vec3);

                if(gltfSceneFileData.v_primitiveType[i].a & VERTEX_TEXTURE_COORD)
                {
                        glVertexAttribPointer(TEXTURE_COORD_VERTEX_BUFFER_LOCATION, 2, GL_FLOAT, GL_FALSE, VBOstride, vertexOffset);
                        glEnableVertexAttribArray(TEXTURE_COORD_VERTEX_BUFFER_LOCATION);

                        vertexOffset += sizeof(vec2);
                }
                if(gltfSceneFileData.v_primitiveType[i].a & VERTEX_NORMAL) // TODO:
                {
                        glVertexAttribPointer(NORMAL_VERTEX_BUFFER_LOCATION, 3, GL_FLOAT, GL_FALSE, VBOstride, vertexOffset);
                        glEnableVertexAttribArray(NORMAL_VERTEX_BUFFER_LOCATION);

                        vertexOffset += sizeof(vec3);
                }

                if(gltfSceneFileData.v_primitiveType[i].a & VERTEX_COLOR)
                {
                        glVertexAttribPointer(COLOR_VERTEX_BUFFER_LOCATION, 4, GL_FLOAT, GL_FALSE, VBOstride, vertexOffset);
                        glEnableVertexAttribArray(COLOR_VERTEX_BUFFER_LOCATION);

                        vertexOffset += sizeof(vec2);
                }
                if(gltfSceneFileData.v_primitiveType[i].a & VERTEX_INDICE)
                {
                        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, scene.v_EBO[i]);
                        glBufferData(GL_ELEMENT_ARRAY_BUFFER, scene.v_indiceCount[i]*sizeof(u32), gltfSceneFileData.v_EBOdata[i], GL_STATIC_DRAW);
                }
                else
                        scene.v_EBO[i] = 0;

                if(gltfSceneFileData.v_primitiveType[i].a & BASE_COLOR_TEXTURE)   // TODO : create a way to custom texture creation
                {
                        glGenTextures(1, &scene.v_TBO[i]);
                        glBindTexture(GL_TEXTURE_2D, scene.v_TBO[i]);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                        i32 textureWidth, textureHeight;
                        i32 nrChannel;
                        void* textureData = stbi_load(gltfSceneFileData.v_texturePath[i], &textureWidth, &textureHeight, &nrChannel, 0);
                        GLint pixelFormat = nrChannel==3 ? GL_RGB : GL_RGBA;  // INFO : do not include format like GL_BGR and 10bit color
                        glTexImage2D(GL_TEXTURE_2D, 0, pixelFormat, textureWidth, textureHeight, 0, pixelFormat, GL_UNSIGNED_BYTE, textureData);
                        glGenerateMipmap(GL_TEXTURE_2D);
                        stbi_image_free(textureData);
                }
        }

        return scene;
}

E_primitiveType fn_getJsonProp(char* jsonString, E_error* p_error)
{
        E_primitiveType returnValue = 0;
        *p_error = HOLY_SUCCESS;
        if(!jsonString)
        {
                *p_error = HOL_INVALID_ARGUMENT;
                return 0;
        }

        yyjson_doc* jsonDoc = yyjson_read(jsonString, strlen(jsonString), 0);
        if(!jsonDoc)
        {
                *p_error = HOL_PARSING_FAILED;
                return 0;
        }
        yyjson_val* jsonRoot = yyjson_doc_get_root(jsonDoc);
        if(!jsonRoot &&
                jsonRoot->tag & YYJSON_TYPE_MASK != YYJSON_TYPE_OBJ)
        {
                *p_error = HOL_PARSING_FAILED;
                yyjson_doc_free(jsonDoc);
                return 0;
        }

        yyjson_val* jsonProp = yyjson_obj_get(jsonRoot, "prop");
        if(jsonRoot->tag & YYJSON_TYPE_MASK == YYJSON_TYPE_NUM &&
                jsonRoot->tag & YYJSON_SUBTYPE_MASK == YYJSON_SUBTYPE_UINT)
                returnValue |= yyjson_get_uint(jsonProp);
        else
                *p_error = HOL_PARSING_FAILED;


        yyjson_doc_free(jsonDoc);

        return returnValue;
}
