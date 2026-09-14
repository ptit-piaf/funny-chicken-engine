#version 460 core
// INFO : IN
layout(location = 0) in flat float lightStrenght;

// INFO : OUT
out vec4 color;

void main()
{
        color = vec4(vec3(1.0f, 0.0f, 1.0f)*lightStrenght, 1.0f);
}
