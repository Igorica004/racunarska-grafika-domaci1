#version 330 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;

const float amplitude = 0.1;
const float frequency = 10.0;

void main()
{
    vec2 uv = TexCoords;
    uv.y += sin(uv.x * frequency) * amplitude;
    color = texture(image, uv);
}

