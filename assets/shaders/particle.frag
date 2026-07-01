#version 330 core

in float vAlpha;

uniform vec4 uColor;

out vec4 FragColor;

void main()
{
    vec2 centered = gl_PointCoord - vec2(0.5);
    float distanceToCenter = length(centered);
    float radialFade = 1.0 - smoothstep(0.2, 0.5, distanceToCenter);

    FragColor = vec4(uColor.rgb, uColor.a * vAlpha * radialFade);
}
