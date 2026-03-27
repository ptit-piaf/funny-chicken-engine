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
                return model
        }
        cgltf_load_buffers(&option, fileData, filePath);

        model.v_vao = malloc(sizeof(*model.vao) * fileData->mesh->primitives_count);
        model.v_vbo = malloc(sizeof(*model.vbo) * fileData->mesh->primitives_count);
        model.v_ebo = malloc(sizeof(*model.ebo) * fileData->mesh->primitives_count);

        model.primitiveCount = fileData->mesh->primitives_count;
        glGenVertexArrays(model.primitiveCount, model.v_vao);
        glGenBuffers(model.primitiveCount, model.v_vbo);
        glGenBuffers(model.primitiveCount, model.v_ebo);

        cgltf_primitive* primitive = fileData->mesh->primitives;

        for(u32 i=0; i<fileData->mesh->primitives_count; i++)
        {
                primitive[i].indices;

                vec4* vboBuffer = malloc(sizeof(vec4) * primitive[i].attributes_count);

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

                for(u32 j=0; j<positionAttribute.data->count; j++)
                {
                        cgltf_accessor_read_float(positionAttribute, j, vboBuffer[j], 3);
                        vboBuffer[j][3] = 1.0f;
                }

                // INFO : GPU allocation

                
        }
        fileData->mesh->primitives

        cgltf_free(fileData);
        return model;
}
