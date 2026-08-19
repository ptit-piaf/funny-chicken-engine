#include <cglm/cglm.h>

#include <stdio.h>

#include "render.h"

size_t fn_getVBOstride(E_primitiveType primitiveType)
{
        size_t returnValue = sizeof(vec3);      // INFO : sizeof(vec3) is for the vertex position

        if(primitiveType & VERTEX_TEXTURE_COORD)
                returnValue += sizeof(vec2);
        if(primitiveType & VERTEX_NORMAL)
                returnValue += sizeof(vec3);
        if(primitiveType & VERTEX_COLOR)
                returnValue += sizeof(vec3);


        return returnValue;
}
