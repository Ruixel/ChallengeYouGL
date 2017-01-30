#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tex_color;

uniform mat4 projectionTransformation;
uniform mat4 viewTransformation;
uniform mat4 modelTransformation;

uniform bool isEntity;
uniform bool enableLighting;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;

out vec3 Color;

// Variables
vec3 light_Position = vec3(100.0, 400.0, 400.0);
vec3 light_Color   = vec3(0.7, 0.78, 0.7);

void main()
{
    vec4 world_position = modelTransformation * vec4(position, 1.0f);
    gl_Position = projectionTransformation * viewTransformation * world_position;

    //mat3 normalMatrix = transpose(inverse(mat3(modelTransformation)));

    vec3 fixed_tex_color = vec3(tex_color.x / 255, tex_color.y / 255, tex_color.z / 255);
    fixed_tex_color = pow(fixed_tex_color, vec3(1.0/1.4));
    Color = fixed_tex_color;

    FragPos     = world_position.xyz;
    TexCoords   = texCoords;
    Normal      = normal;
}
