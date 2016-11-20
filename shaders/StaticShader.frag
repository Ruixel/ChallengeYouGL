#version 330 core

in vec3 pos;
in vec2 uvCoord;
in vec4 outColor;

uniform sampler2D textureSampler;

out vec4 Color;

void main()
{
    Color = outColor * texture(textureSampler, uvCoord);
}
