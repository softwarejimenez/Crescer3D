#version 150

in vec2 uv;
uniform sampler2D tex;
out vec4 outColor;

void main(void)
{
    vec4 surface = texture(tex, uv);
    outColor = vec4(surface.rgb, surface.a);
}