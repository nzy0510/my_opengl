#shader vertex
#version 330 core
layout(location=0) in vec4 position;//0与glVertexAttribPoint中的index对应
// layout(location=1) in vec3 aColor;
// out vec3 vColor;
void main()
{
   gl_Position = position;
   // vColor=aColor;
};

#shader fragment
#version 330 core
layout(location=0) out vec4 color;
 // in vec3 vColor;
 uniform vec4 u_color;//每次绘制的,和属性的根本区别

 void main()
 {
    color=u_color;
 };