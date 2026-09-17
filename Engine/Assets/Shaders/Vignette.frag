#version 330 core

in vec2 v_TexCoord;

uniform sampler2D u_ScreenTexture;
uniform float u_Strength;

out vec4 o_Color;

void main()
{
    vec4 color =
        texture(
            u_ScreenTexture,
            v_TexCoord);

    vec2 centered =
        v_TexCoord - vec2(0.5);

    float distance =
        length(centered);

    float vignette =
        smoothstep(
            0.0,
            0.7071,
            distance);

    vignette *= u_Strength;

    color.rgb *=
        1.0 - vignette;

    o_Color =
        color;
}