#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;

uniform mat4 projectionTransformation;
uniform mat4 modelTransformation;

out vec2 uvCoord;
out vec3 pos;
out vec4 outColor;

// Variables
vec3 light_Position = vec3(-1.0, 1.0, -1.0);
vec3 light_Color   = vec3(1.0, 1.0, 1.0);

void main()
{
    vec4 wPos = projectionTransformation * modelTransformation * vec4(position, 1.0f);
    gl_Position = wPos;

    vec3 normalDirection = normalize(normal);
    vec3 lightDirection  = normalize(light_Position);
    vec3 diffuse = light_Color * max(0.0, dot(normalDirection, lightDirection)) + vec3(0.3, 0.3, 0.3);

    outColor    = vec4(diffuse, 1.0);
    pos         = position.xyz;
    uvCoord     = texCoords;
}
