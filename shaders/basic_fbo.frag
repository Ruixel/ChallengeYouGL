#version 330 core
in vec2 fboTexCoords;
out vec4 color;

uniform sampler2D screenTexture;

void main()
{
    color = vec4(vec3(1.0 - texture(screenTexture, fboTexCoords)), 1.0);
}
