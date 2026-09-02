#version 460 core

layout(location = 0) in vec3 pos;
layout(location = 2) in vec3 normal;

layout(location = 0) out vec3 outNormal;

uniform mat4 modelMat;
layout(location = 0) uniform mat4 projectionViewMat;

void main()
{
        outNormal = normal;
        gl_Position = projectionViewMat * vec4(pos, 1.0);
}
