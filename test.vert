#version 460 core

vec4 test[3] = {vec4(-1.0f, -1.0f, 0.0f, 0.0f), vec4(0.0f, 1.0f, 0.0f, 0.0f), vec4(1.0f, -1.0f, 0.0f, 0.0f)};

void main()
{
        gl_Position = test[gl_VertexID % 3];
}
