#version_placeholder

#ifdef GL_ES
precision mediump float;
#endif

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec4 aColor;
out vec2 aTexCoord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(position.x, position.y, position.z, 1.0);
    aColor = vec4(color, 1.0);
    aTexCoord = texCoord;
}