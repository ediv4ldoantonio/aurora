#version 330 core

in vec2 v_TexCoord;
in vec4 v_Color;
flat in int v_MaterialIndex;

uniform sampler2D u_Textures[16];

uniform vec4 u_MaterialTints[16];

out vec4 o_Color;

void main()
{
   o_Color =
    texture(
        u_Textures[v_MaterialIndex],
        v_TexCoord)
    * v_Color
    * u_MaterialTints[v_MaterialIndex];
}