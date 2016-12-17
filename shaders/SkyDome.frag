#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;

uniform mat4 projectionTransformation;
uniform mat4 viewTransformation;
uniform mat4 modelTransformation;

out vec2 uvCoord;

void main()
{
    vec4 world_position = modelTransformation * vec4(position, 1.0f);
    gl_Position = projectionTransformation * viewTransformation * world_position;

    uvCoord = texCoords;
}
