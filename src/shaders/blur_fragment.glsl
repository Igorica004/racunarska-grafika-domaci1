#version 330 core
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D image;
uniform float playerX;
uniform float playerY;

const float kernel[25] = float[](
    1,  4,  6,  4, 1,
    4, 16, 24, 16, 4,
    6, 24, 36, 24, 6,
    4, 16, 24, 16, 4,
    1,  4,  6,  4, 1
);

void main()
{
    vec2 texSize = textureSize(image, 0);
    float aspect = float(texSize.x)/float(texSize.y);
    vec2 texel = 1.0 / vec2(texSize);
    
    float dist = distance(vec2(TexCoords.x*aspect,TexCoords.y), vec2(playerX*aspect, playerY));

    float radius = 0.4;
    float softness = 0.05;
    float maxStrength = 5.0;

    float blurFactor = smoothstep(radius, radius + softness, dist);
    float dynamicSpread = blurFactor * maxStrength; 

    vec3 color = vec3(0.0);
    int idx = 0;

    for(int i = -2; i <= 2; i++)
    {
        for(int j = -2; j <= 2; j++)
        {
            vec2 offset = vec2(float(i), float(j)) * texel * dynamicSpread;
            color += texture(image, TexCoords + offset).rgb * kernel[idx];
            idx++;
        }
    }

    FragColor = vec4(color / 256.0, 1.0);
}
