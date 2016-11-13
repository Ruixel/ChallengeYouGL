#version 330 core

in vec3 pos;
in vec2 uvCoord;

uniform sampler2D textureSampler;

out vec4 Color;

void main()
{
    Color = texture(textureSampler, uvCoord) * vec4(1, 1, 1, 1);
}
