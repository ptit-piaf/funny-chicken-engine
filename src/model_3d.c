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

        model.vao = malloc(sizeof(*model.vao) * fileData->mesh->primitives_count);
        model.vbo = malloc(sizeof(*model.vbo) * fileData->mesh->primitives_count);
        model.ebo = malloc(sizeof(*model.ebo) * fileData->mesh->primitives_count);

        cgltf_primitive* primitive = fileData->mesh->primitives;

        for(u32 i=0; i<fileData->mesh->primitives_count; i++)
        {
                primitive[i].indices;
                for(u32 i=0; i<primitive[i].attributes_count; i++)
                {
                        primitive[i].attributes
                }
        }
        fileData->mesh->primitives

        cgltf_free(fileData);
        return model;
}
