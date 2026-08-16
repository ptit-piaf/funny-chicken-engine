#include <GL/glad.h>
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
                glUseProgram(scene.v_shader[i]);
                glBindVertexArray(scene.v_VAO[i]);
                if(scene.v_TBO[i])
                        glBindTexture(GL_TEXTURE_2D, scene.v_TBO[i]);
                glDrawElements(GL_TRIANGLES, scene.v_indiceCount[i], GL_UNSIGNED_INT, NULL);
        }

        return returnValue;
}
