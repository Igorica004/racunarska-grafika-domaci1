#version 330 core
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D image;
uniform float time;

void main()
{
    vec4 texColor = texture(image, TexCoords);
    
    float t = time * 0.006;
    float r = sin(t + TexCoords.x * 6.0 + sin(t * 0.4 + TexCoords.y * 4.0)) * 0.5 + 0.5;
    float g = cos(t * 0.7 + TexCoords.y * 5.0 + sin(t * 1.1 + TexCoords.x * 3.0)) * 0.5 + 0.5;
    float b = sin(t * 1.3 - (TexCoords.x + TexCoords.y) * 4.0 + cos(t * 0.6)) * 0.5 + 0.5;
    vec3 noiseColor = vec3(r, g, b);

    float gray = dot(texColor.rgb, vec3(0.299, 0.587, 0.114));
    vec3 grayscale = vec3(gray);

    vec3 colored = grayscale * noiseColor * 2.5;

    vec3 finalColor = mix(texColor.rgb, colored, 0.4);

    FragColor = vec4(finalColor, texColor.a);
}
