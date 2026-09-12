#include <cglm/cglm.h>

#include <stdio.h>

#include "render.h"
#include "context.h"

size_t fn_getVBOstride(E_primitiveType primitiveType)
{
        size_t returnValue = 0;

        if(primitiveType & VERTEX_POSITION)
                returnValue += sizeof(vec3);
        if(primitiveType & VERTEX_TEXTURE_COORD)
                returnValue += sizeof(vec2);
        if(primitiveType & VERTEX_NORMAL)
                returnValue += sizeof(vec3);
        if(primitiveType & VERTEX_COLOR)
                returnValue += sizeof(vec4);


        return returnValue;
}

GLenum fn_getPrimitiveTypeFromCgltfPrimitiveType(cgltf_primitive_type cgltfPrimitiveType)
{
        switch (cgltfPrimitiveType)
        {
                case cgltf_primitive_type_invalid:
                        return 0;
                case cgltf_primitive_type_points:
                        return GL_POINTS;
                case cgltf_primitive_type_lines:
                        return GL_LINES;
                case cgltf_primitive_type_line_loop:
                        return GL_LINE_LOOP;
                case cgltf_primitive_type_line_strip:
                        return GL_LINE_STRIP;
                case cgltf_primitive_type_triangles:
                        return GL_TRIANGLES;
                case cgltf_primitive_type_triangle_strip:
                        return GL_TRIANGLE_STRIP;
                case cgltf_primitive_type_triangle_fan:
                        return GL_TRIANGLE_FAN;
        }
        return 0;
}
