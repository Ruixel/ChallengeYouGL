#version 330 core

in vec3 pos;

out vec4 Color;

void main()
{
    Color = vec4(1.f, 1.f, 0.f+(pos.z/2), 1.f);
}
