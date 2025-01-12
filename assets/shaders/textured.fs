#version_placeholder

#ifdef GL_ES
precision mediump float;
#endif

in vec4 aColor;
in vec2 aTexCoord;
out vec4 color;

uniform sampler2D texture_0;
uniform sampler2D texture_1;

void main()
{
    color = aColor * mix(texture(texture_0, aTexCoord), texture(texture_1, aTexCoord), 0.5);
}