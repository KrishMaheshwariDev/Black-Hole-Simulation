#version 330 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in float aAlpha;
layout(location = 2) in float aSize;

uniform mat4 uProjection;

out float vAlpha;

void main()
{
    gl_Position = uProjection * vec4(aPos, 0.0, 1.0);
    gl_PointSize = aSize;
    vAlpha = aAlpha;
}
