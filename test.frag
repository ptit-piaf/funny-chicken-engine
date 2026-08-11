#version 410 core

in vec2 textureCoord;

uniform sampler2D uTexture;

out vec4 color;

void main()
{
        color = texture(uTexture, textureCoord);
}
