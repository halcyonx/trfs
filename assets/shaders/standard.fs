#version_placeholder

#ifdef GL_ES
precision mediump float;
#endif

in vec4 aColor;
out vec4 color;

void main()
{
    color = aColor;
}