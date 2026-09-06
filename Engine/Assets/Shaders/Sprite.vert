#version 330 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec4 a_Color;
layout(location = 3) in float a_MaterialIndex;

out vec2 v_TexCoord;
out vec4 v_Color;
flat out int v_MaterialIndex;

uniform mat4 u_ViewProjection;

void main()
{
    v_TexCoord = a_TexCoord;
    v_Color = a_Color;
    v_MaterialIndex = int(a_MaterialIndex);

    gl_Position =
        u_ViewProjection *
        vec4(a_Position, 0.0, 1.0);
}