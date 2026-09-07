#version 330 core

in vec2 v_TexCoord;
in vec4 v_Color;
flat in int v_MaterialIndex;

uniform sampler2D u_Textures[16];
uniform vec4 u_MaterialTints[16];

out vec4 o_Color;

vec4 SampleTexture(int index, vec2 uv)
{
    switch (index)
    {
        case 0:
            return texture(u_Textures[0], uv);

        case 1:
            return texture(u_Textures[1], uv);

        case 2:
            return texture(u_Textures[2], uv);

        case 3:
            return texture(u_Textures[3], uv);

        case 4:
            return texture(u_Textures[4], uv);

        case 5:
            return texture(u_Textures[5], uv);

        case 6:
            return texture(u_Textures[6], uv);

        case 7:
            return texture(u_Textures[7], uv);

        case 8:
            return texture(u_Textures[8], uv);

        case 9:
            return texture(u_Textures[9], uv);

        case 10:
            return texture(u_Textures[10], uv);

        case 11:
            return texture(u_Textures[11], uv);

        case 12:
            return texture(u_Textures[12], uv);

        case 13:
            return texture(u_Textures[13], uv);

        case 14:
            return texture(u_Textures[14], uv);

        case 15:
            return texture(u_Textures[15], uv);

        default:
            return vec4(1.0);
    }
}

void main()
{
    vec4 textureColor =
        SampleTexture(
            v_MaterialIndex,
            v_TexCoord);

    o_Color =
        textureColor
        * v_Color
        * u_MaterialTints[v_MaterialIndex];
}