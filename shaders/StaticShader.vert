#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tex_color;

uniform mat4 projectionTransformation;
uniform mat4 viewTransformation;
uniform mat4 modelTransformation;

out vec2 uvCoord;
out vec3 pos;
out vec4 outColor;

// Variables
vec3 light_Position = vec3(-100.0, 400.0, -1.0);
vec3 light_Color   = vec3(0.7, 0.7, 0.7);

void main()
{
    vec4 world_position = modelTransformation * vec4(position, 1.0f);
    gl_Position = projectionTransformation * viewTransformation * world_position;

    vec3 surfaceNormal   = (modelTransformation * vec4(normal, 0.0)).xyz;
    vec3 toCameraVector  = (inverse(viewTransformation) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - world_position.xyz;
    vec3 normalDirection = normalize(surfaceNormal);
    vec3 lightDirection  = normalize(light_Position - world_position.xyz);
    vec3 cameraDirection = normalize(toCameraVector);

    vec3 fixed_tex_color = vec3(tex_color.x / 255, tex_color.y / 255, tex_color.z / 255);
    vec3 diffuse         = (light_Color * max(0.0, dot(normalDirection, lightDirection)) + vec3(0.3, 0.3, 0.3)) * fixed_tex_color;

    outColor    = vec4(diffuse, 1.0);
    pos         = position.xyz;
    uvCoord     = texCoords;
}
