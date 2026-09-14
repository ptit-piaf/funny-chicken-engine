#version 460 core

// INFO : IN
layout(location = 0) in float lightStrenght;
layout(location = 1) in vec2 inUv;

// INFO : OUT
out vec4 color;

uniform sampler2D uTexture;

void main()
{
        color = texture(uTexture, inUv) * lightStrenght;
}
