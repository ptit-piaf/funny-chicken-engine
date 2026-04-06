#version 410 core

layout(location = 0) in vec3 pos;

uniform mat4 modelMatrix;

void main()
{
        gl_Position = mat4(1.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 1.0f, 0.0f, 
                        0.0f, 0.0f, 0.0f, 1.0f)*vec4(pos, 1.0);
}
