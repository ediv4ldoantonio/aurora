#version 330 core

in vec2 v_TexCoord;

uniform sampler2D u_ScreenTexture;

out vec4 o_Color;

void main()
{
    o_Color =
        texture(
            u_ScreenTexture,
            v_TexCoord);
}