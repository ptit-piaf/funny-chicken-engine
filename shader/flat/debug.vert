#version 460 core
// INFO : IN
layout(location = 0) in vec3 pos;
layout(location = 2) in vec3 normal;

// INFO : OUT
layout(location = 0) out flat float lightStrenght;

// INFO : UNIFORM
layout(location = 0) uniform mat4 projectionViewMat;
layout(location = 2) uniform vec3 sunLight;

void main()
{
        lightStrenght = (dot(normal, sunLight)+1.0f)/2.0f;
        gl_Position = projectionViewMat * vec4(pos, 1.0f);
}
