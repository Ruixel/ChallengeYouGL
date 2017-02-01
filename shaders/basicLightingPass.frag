#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;
uniform sampler2D shadowMap;

struct Light
{
    vec3 Position;
    vec3 Color;

    float Linear;
    float Quadratic;
};

const int NR_LIGHTS = 16;
uniform Light lights[NR_LIGHTS];
uniform vec3 viewPos;

uniform mat4 lightSpaceMatrix;

float ShadowCalculation(vec4 fragPosLightSpace, float shadow_bias)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;

    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;

    float shadow = (currentDepth - shadow_bias) > closestDepth ? 1.0 : 0.0;
    return shadow;
}

void main()
{
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal  = texture(gNormal, TexCoords).rgb;
    vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
    vec4 FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);

    vec3 ambience = Diffuse * 0.3;
    vec3 diffuse_lighting;
    vec3 viewDir  = normalize(viewPos - FragPos);
    for (int i = 0; i < NR_LIGHTS; ++i)
    {
        // Diffuse Lighting
        vec3 lightDir = normalize(lights[i].Position - FragPos);
        vec3 diffuse  = max(dot(Normal, lightDir), 0.0) * Diffuse * lights[i].Color;

        // Light[0] is ambience lighting
        if (i != 0)
        {
            // Attenuation
            float distance = length(lights[i].Position - FragPos);
            float attenuation = 1.0 / (1.0 + lights[i].Linear * distance + lights[i].Quadratic * distance * distance); //(1.05 * (distance / 20));
            diffuse *= attenuation;
        } else {
            diffuse *= 1.1f;
        }

        diffuse_lighting += diffuse;
    }

    float shadow_bias = max(0.05 * (1.0 - dot(Normal, normalize(lights[0].Position - FragPos))), 0.005);
    float shadow = ShadowCalculation(FragPosLightSpace, shadow_bias);

    //vec3 lighting = (ambience + (1.0 - shadow) * (diffuse_lighting));
    vec3 lighting = ambience + diffuse_lighting - shadow*0.3 - 0.15;

    FragColor = vec4(lighting, 1.0);
}
