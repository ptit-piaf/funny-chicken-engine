#version 460 core

layout(location = 0) in vec3 inNormal;

out vec4 color;

void main()
{
        color = vec4(inNormal, 1.0f);
}
