#version 330 core
in vec2 fboTexCoords;
out vec4 color;

uniform sampler2D screenTexture;
uniform int theme;

const float offset = 1.0 / 300;

vec2 offsets[9] = vec2[](
    vec2(-offset, offset),  // top-left
    vec2(0.0f,    offset),  // top-center
    vec2(offset,  offset),  // top-right
    vec2(-offset, 0.0f),    // center-left
    vec2(0.0f,    0.0f),    // center-center
    vec2(offset,  0.0f),    // center-right
    vec2(-offset, -offset), // bottom-left
    vec2(0.0f,    -offset), // bottom-center
    vec2(offset,  -offset)  // bottom-right
);

// 3x3 matrix kernels

// Blur
/*
float kernel[9] = float[](
    1.0 / 16, 2.0 / 16, 1.0 / 16,
    2.0 / 16, 4.0 / 16, 2.0 / 16,
    1.0 / 16, 2.0 / 16, 1.0 / 16
);*/

// Weird effect
/*
float kernel[9] = float[](
    0.0 / 9, 7.0 / 9, 3.0 / 9,
    6.0 / 9, 5.0 / 9, 2.0 / 9,
    4.0 / 9, 1.0 / 9, 8.0 / 9
);*/

// Floyd-Steinberg Dithering
float kernel[9] = float[](
    0.0 / 16, 0.0 / 16, 0.0 / 16,
    0.0 / 16, 16.0 / 16, 7.0 / 16,
    3.0 / 16, 5.0 / 16, 1.0 / 16
);

void main()
{
    vec3 sampleTex[9];
    for (int i = 0; i < 9; i++)
    {
       // sampleTex[i] = vec3(texture(screenTexture, fboTexCoords.st + offsets[i]));
    }

    vec3 col = vec3(0.0);
    for (int i = 0; i < 9; i++)
    {
        col += ((sampleTex[i] / 255) * kernel[i]) * 255;
    }

    col = vec3(texture(screenTexture, fboTexCoords.st).xyz);

    switch(theme)
    {
        case 1: color = vec4(col.r, col.g, col.b, 1.0);                   break;
        case 2: color = vec4(col.r * 0.3, col.g * 0.3, col.b * 0.3, 1.0); break;
        case 3: color = vec4(col.r * 0.9, col.g * 0.1, col.b * 0.1, 1.0); break;
    }

    // Inverted Colors
    // color = vec4(vec3(1.0 - texture(screenTexture, fboTexCoords)), 1.0);

    // No Post FX
    //color = texture(screenTexture, fboTexCoords);
}
