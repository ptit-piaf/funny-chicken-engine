#version 460 core
// INFO : IN
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 inUv;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec4 inColor;

// INFO : OUT
layout(location = 0) out flat float lightStrenght;
layout(location = 1) out vec2 outUv;
layout(location = 2) out vec4 outColor;

// INFO : UNIFORM
layout(location = 0) uniform mat4 projectionViewMat;
layout(location = 2) uniform vec3 sunLight;

void main()
{
        lightStrenght = dot(normal, sunLight)-inColor.w;
        if(lightStrenght < 0.0f)
                lightStrenght = 0.0f;


        gl_Position = projectionViewMat * vec4(pos, 1.0f);
}
