#version_placeholder

#ifdef GL_ES
precision mediump float;
#endif

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec4 aColor;

void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
    aColor = vec4(color, 1.0);
}