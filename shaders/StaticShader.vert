#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

uniform mat4 projectionTransformation;
uniform mat4 modelTransformation;

out vec2 uvCoord;
out vec3 pos;

void main()
{
    vec4 world_Position = projectionTransformation * modelTransformation * vec4(position, 1.0f);
    gl_Position = world_Position;

    pos         = position.xyz;
    uvCoord     = texCoords;
}
