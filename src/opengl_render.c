#include "glad/glad.h"
#include <cglm/cglm.h>

#include "render.h"
#include "file.h"
#include "shader.h"

E_error fn_openGLrender(S_openGLscene scene)
{
        E_error returnValue = HOLY_SUCCESS;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // TODO : manage this line with some shit

        glUniformMatrix4fv(PROJECTION_VIEW_UNIFORM_LOCATION, 1, GL_FALSE, *scene.projectionViewMat);

        for(u32 i=0; i<scene.primitiveCount; i++)
        {
                if(scene.v_primitiveType[i].a & PRIMITVE_FATAL_ERROR)
                        continue;

                if(i==2)
                        glUseProgram(scene.v_shader[1]); // TODO:
                else
                        glUseProgram(scene.v_shader[0]); // TODO:
                glUniformMatrix4fv(PROJECTION_VIEW_UNIFORM_LOCATION, 1, GL_FALSE, *scene.projectionViewMat); // INFO : I have to update it because ever time it get unbind 

                glBindVertexArray(scene.v_VAO[i]);

                if(scene.v_primitiveType[i].a & BASE_COLOR_TEXTURE)
                        glBindTexture(GL_TEXTURE_2D, scene.v_TBO[i]);

                GLuint program, vao, ebo;
                glGetIntegerv(GL_CURRENT_PROGRAM, &program);
                glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vao);
                glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &ebo);
                printf("Primitive id = %d\nprogram = %d   vao = %d    ebo = %d\n", i, program, vao, ebo);

                if(scene.v_primitiveType[i].a & VERTEX_INDICE)
                        glDrawElements(GL_TRIANGLES/*scene.v_primitiveType[i].renderMode*/, scene.v_indiceCount[i], GL_UNSIGNED_INT, NULL); // TODO:

                else
                        glDrawArrays(scene.v_primitiveType[i].renderMode, 0, scene.v_indiceCount[i]);
        }
        printf("\n\n");

        return returnValue;
}
