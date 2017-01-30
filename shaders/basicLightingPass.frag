#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

struct Light
{
    vec3 Position;
    vec3 Color;

    float Linear;
    float Quadratic;
};

const int NR_LIGHTS = 32;
uniform Light lights[NR_LIGHTS];
uniform vec3 viewPos;

void main()
{
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal  = texture(gNormal, TexCoords).rgb;
    vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;

    vec3 lighting = Diffuse * 0.1;
    vec3 viewDir  = normalize(viewPos - FragPos);
    for (int i = 0; i < NR_LIGHTS; ++i)
    {
        // Diffuse Lighting
        vec3 lightDir = normalize(lights[i].Position - FragPos);
        vec3 diffuse  = max(dot(Normal, lightDir), 0.0) * Diffuse * lights[i].Color;

        // Attenuation
        float distance = length(lights[i].Position - FragPos);
        float attenuation = 1.0 / (1.05 * (distance / 20)); //(1.0 + lights[i].Linear * distance + lights[i].Quadratic * distance * distance);
        diffuse  *= attenuation;
        lighting += diffuse;
    }

    FragColor = vec4(lighting, 1.0);
}