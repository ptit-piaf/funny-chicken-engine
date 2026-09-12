// INFO : IN
layout(location = 0) in vec3 pos;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec4 inColor;

// INFO : OUT
layout(location = 0) out flat float lightStrenght;
layout(location = 1) out flat vec4 outColor;

// INFO : UNIFORM
layout(location = 0) uniform mat4 projectionViewMat;

void main()
{
        outColor = inColor;
        lightStrenght = dot();
        gl_Position = vec4(pos, 1.0f) * projectionViewMat;
}
