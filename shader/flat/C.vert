// INFO : IN
layout(location = 0) in vec3 pos;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec4 inColor;

// INFO : OUT
layout(location = 0) out flat float lightStrenght;
layout(location = 1) out vec4 outColor;

// INFO : UNIFORM
layout(location = 0) uniform mat4 projectionViewMat;
layout(location = 2) uniform vec3 sunLight;

void main()
{
        outColor = inColor;
        lightStrenght = dot(normal, sunLight);
        gl_Position = vec4(pos, 1.0f) * projectionViewMat;
}
