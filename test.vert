#version 410 core

layout(location = 0) in vec3 pos;

uniform mat4 modelMat;
uniform mat4 projectionViewMat;

void main()
{
        gl_Position = projectionViewMat * modelMat * vec4(pos, 1.0);
}
