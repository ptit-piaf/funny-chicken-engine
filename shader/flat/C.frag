// INFO : IN
layout(location = 0) in float lightStrenght;
layout(location = 1) in vec4 inColor;

// INFO : OUT
layout(location = 0) out vec4 outColor;

void main()
{
        outColor = inColor * lightStrenght;
}
