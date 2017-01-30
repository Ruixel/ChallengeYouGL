#version 330 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpecular;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
in vec3 Color;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;

void main()
{
    gPosition = FragPos;

    gNormal = normalize(Normal);

    gAlbedoSpecular.rgb = Color * texture(texture_diffuse, TexCoords).rgb;
    gAlbedoSpecular.a   = 1.0; //texture(texture_specular, TexCoords).r;
}

