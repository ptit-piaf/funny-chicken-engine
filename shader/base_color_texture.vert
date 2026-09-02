#version 460 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 aTextureCoord;

out vec2 textureCoord;

uniform mat4 modelMat;
layout(location = 0) uniform mat4 projectionViewMat;

void main()
{
        textureCoord = aTextureCoord;
        gl_Position = projectionViewMat * vec4(pos, 1.0);
}
