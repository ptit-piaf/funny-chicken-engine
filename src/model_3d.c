#include <GL/glad.h>
#include <cglm/cglm.h>
#include <cgltf/cgltf.h>

#include <stdio.h>
#include <stdlib.h>

#include "file.h"

S_model fn_loadGltfFileFormat(const char* filePath)
{
        S_model model = {0};

        if(!filePath)
        {
                model.error = HOL_NULL_FILE_PATH;
                return model;
        }

        cgltf_options option = {0};
        cgltf_data* fileData = NULL;
        cgltf_result result = cgltf_parse_file(&option, filePath, &fileData);
        if(result != cgltf_result_success)
        {
                model.error = HOL_FILE_NOT_FIND;
                return model;
        }
        cgltf_load_buffers(&option, fileData, filePath);

        model.v_vao = malloc(sizeof(*model.v_vao) * fileData->meshes->primitives_count);
        model.v_vbo = malloc(sizeof(*model.v_vbo) * fileData->meshes->primitives_count);
        model.v_ebo = malloc(sizeof(*model.v_ebo) * fileData->meshes->primitives_count);
        model.v_verticeCount = malloc(sizeof(*model.v_verticeCount) * fileData->meshes->primitives_count);

        model.primitiveCount = fileData->meshes->primitives_count;
        glGenVertexArrays(model.primitiveCount, model.v_vao);
        glGenBuffers(model.primitiveCount, model.v_vbo);
        glGenBuffers(model.primitiveCount, model.v_ebo);

        cgltf_primitive* primitive = fileData->meshes->primitives;

        for(u32 i=0; i<fileData->meshes->primitives_count; i++)
        {

                cgltf_attribute positionAttribute = {0};

                for(u32 j=0; j<primitive[i].attributes_count; j++)
                {
                        switch(primitive[i].attributes[j].type)
                        {
                                case cgltf_attribute_type_position:
                                        positionAttribute = primitive[i].attributes[j];
                                        break;
                        }
                }
                model.v_verticeCount[i] = positionAttribute.data->count;

                vec3* vboBuffer = malloc(sizeof(vec3) * positionAttribute.data->count);
                //u32* eboBuffer = malloc(sizeof(u32) * primitive[i].indices->count);  // INFO : for now all indices are automaticly in a u32
                //model.v_indiceCount[i] = primitive[i].indices->count; WARNING : in the only file I have, there are no indices 

                for(u32 j=0; j<positionAttribute.data->count; j++)
                        cgltf_accessor_read_float((const cgltf_accessor*)&positionAttribute, j, vboBuffer[j], 3);

                /*for(u32 j=0; j<primitive[i].indices->count; j++)
                        cgltf_accessor_read_uint((const cgltf_accessor*)&primitive[i].indices, j, &eboBuffer[j], 1);*/


                glBindVertexArray(model.v_vao[i]);
                glBindBuffer(GL_ARRAY_BUFFER, model.v_vbo[i]);
                glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * positionAttribute.data->count, vboBuffer, GL_STATIC_DRAW);

                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);

                /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.v_ebo[i]);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * primitive[i].indices->count, vboBuffer, GL_STATIC_DRAW);*/

        }

        cgltf_free(fileData);
        return model;
}
