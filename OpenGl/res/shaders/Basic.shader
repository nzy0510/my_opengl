#shader vertex
#version 330 core
layout(location=0) in vec4 position;//0与glVertexAttribPoint中的index对应
layout(location=1) in vec2 texCrood;//在顶点着色器中，要将每个顶点的纹理坐标，传递给片段着色器

out vec2 v_TexCrood;//纹理坐标传递给片段着色器
void main()
{
   gl_Position = position;
   v_TexCrood=texCrood;
};

#shader fragment
#version 330 core

layout(location=0) out vec4 color;

in vec2 v_TexCrood;//从顶点着色器传递过来的纹理坐标

//uniform vec4 u_color;//每次绘制的,和属性的根本区别
uniform sampler2D u_texture;//纹理采样器

void main()
{
    vec4 texColor=texture(u_texture,v_TexCrood);
    color = texColor;
};