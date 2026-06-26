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
        model.v_indiceCount = malloc(sizeof(*model.v_indiceCount) * fileData->meshes->primitives_count);

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
                u32* eboBuffer = malloc(sizeof(u32) * primitive[i].indices->count);  // INFO : for now all indices are automaticly in a u32
                model.v_indiceCount[i] = primitive[i].indices->count; // WARNING : in the only file I have, there are no indices 

                for(u32 j=0; j<positionAttribute.data->count; j++)
                        cgltf_accessor_read_float(positionAttribute.data, j, vboBuffer[j], 3);

                for(u32 j=0; j<primitive[i].indices->count; j++)
                        cgltf_accessor_read_uint(primitive[i].indices, j, &eboBuffer[j], 1);

                printf("vbo buffer :\n");
                for(u32 j=0; j<positionAttribute.data->count; j++)
                        printf("%d {%f, %f, %f}\n", j, vboBuffer[j][0], vboBuffer[j][1], vboBuffer[j][2]);

                printf("ebo buffer :\n");
                for(u32 j=0; j<primitive[i].indices->count; j++)
                        printf("%d ", eboBuffer[j]);
                printf("\n");







                










                
                printf("line = %d\n", __LINE__);glBindVertexArray(model.v_vao[i]);
                printf("line = %d\n", __LINE__);glBindBuffer(GL_ARRAY_BUFFER, model.v_vbo[i]);
                printf("line = %d\n", __LINE__);glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * positionAttribute.data->count, vboBuffer, GL_STATIC_DRAW);

                printf("line = %d\n", __LINE__);glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);
                glEnableVertexAttribArray(0);

                printf("line = %d\n", __LINE__);glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.v_ebo[i]);
                printf("line = %d\n", __LINE__);glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * primitive[i].indices->count, eboBuffer, GL_STATIC_DRAW);

        }























        printf("vao = [ ");
        for(u32 i=0; i<fileData->meshes->primitives_count; i++)
                printf("%d, ", model.v_vao[i]);
        printf("\n");


        printf("vbo = [ ");
        for(u32 i=0; i<fileData->meshes->primitives_count; i++)
                printf("%d, ", model.v_vbo[i]);
        printf("\n");

        printf("ebo = [ ");
        for(u32 i=0; i<fileData->meshes->primitives_count; i++)
                printf("%d, ", model.v_ebo[i]);
        printf("\n");


        printf("verticeCount = [ ");
        for(u32 i=0; i<fileData->meshes->primitives_count; i++)
                printf("%d, ", model.v_verticeCount[i]);
        printf("\n");


        printf("indice count = [ ");
        for(u32 i=0; i<fileData->meshes->primitives_count; i++)
                printf("%d, ", model.v_indiceCount[i]);
        printf("\n");

// WARNING : do not forget to free all alocated buffer.

        cgltf_free(fileData);
        return model;
}
