#version 330 core

in float vAlpha;

uniform vec4 uColor;
uniform float uRenderAsPoint;

out vec4 FragColor;

void main()
{
    float shapeFade = 1.0;
    if (uRenderAsPoint > 0.5)
    {
        vec2 centered = gl_PointCoord - vec2(0.5);
        float distanceToCenter = length(centered);
        shapeFade = 1.0 - smoothstep(0.2, 0.5, distanceToCenter);
    }

    FragColor = vec4(uColor.rgb, uColor.a * vAlpha * shapeFade);
}
