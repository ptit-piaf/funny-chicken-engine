#version 460 core
// INFO : IN
layout(location = 0) in float lightStrenght;
layout(location = 1) in vec4 inColor;

// INFO : OUT
out vec4 color;

void main()
{
        color = vec4(vec3(inColor)*lightStrenght + vec3(inColor)*inColor.w, 1.0f);
}
