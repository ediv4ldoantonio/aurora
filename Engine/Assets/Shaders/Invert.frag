#version 330 core

in vec2 v_TexCoord;

uniform sampler2D u_ScreenTexture;
uniform float u_Brightness;

out vec4 o_Color;

void main()
{
    vec4 color =
        texture(
            u_ScreenTexture,
            v_TexCoord);

    color.rgb =
        vec3(1.0) -
        color.rgb;

    color.rgb +=
        vec3(u_Brightness);

    o_Color =
        color;
}