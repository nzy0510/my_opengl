#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<fstream> //文件流
#include<string>
#include<sstream>//字符串流
#include<cassert>
//#include<tuple>//元组，可用于为函数实现两个返回值

#include"Renderer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"

#include"VertexArray.h"
#include"Shader.h"
// CPU 端：创建窗口，定义数据数组。
// 传输：把数据塞给 GPU(VBO)。
// 设置：告诉 GPU 怎么读这些数据(VertexAttribPointer)。
// 编程：写 Shader 告诉 GPU 怎么画(Vertex Shader 定点, Fragment Shader 上色)。
// 绘制：在循环中不断调用 DrawCall。


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "Nzy_OpenGl", NULL, NULL);//创建一个窗口，并同时创建该窗口对应的OpenGL 上下文
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);//将刚创建的窗口的 OpenGL 上下文设置为 “当前上下文”。
    glfwSwapInterval(2);

    glewInit();
	{//新建作用域，方便析构，释放资源
        // 数据：位置
        float vertices[] = {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f,  0.5f,
            -0.5f,  0.5f
        };

        unsigned int indices[] = {
            0,1,2,
            2,3,0
        };


        VertexArray va;
        VertexBuffer vb(vertices, 4 * 2 * sizeof(float));//创建顶点缓冲区对象，并传入数据

        VertexBufferLayout layout;
		layout.Push<float>(2);//位置属性
		va.AddBuffer(vb,layout);

        IndexBuffer ib(indices, 6);//创建索引缓冲区对象，并传入数据

		Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		shader.SetUniform4f("u_color", 0.2f, 0.3f, 0.8f, 1.0f); 

		va.Unbind();
		shader.Unbind();
		vb.Unbind();
		ib.Unbind();

        float r = 0.0f;
        float increment = 0.05f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            GlCall(glClear(GL_COLOR_BUFFER_BIT));//清除颜色 

			shader.Bind();
            shader.SetUniform4f("u_color", r, 0.3f, 0.8f, 1.0f);

            va.Bind();
            ib.Bind();
            if (r > 1.0f) {
                increment = -0.05f;
            }
            else if (r < 0.0f) {
                increment = 0.05f;
            }
            r += increment;

            GlCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));//绘制正方形，6代表索引的数量，不是顶点的数量
            /* Swap front and back buffers */
            GlCall(glfwSwapBuffers(window));//交换前缓冲区和后缓冲区的内容：将后台渲染好的完整画面 “一次性” 显示到屏幕上，避免了渲染过程中（画面不完整时）的闪烁问题。

            /* Poll for and process events */
            GlCall(glfwPollEvents());//检查并处理所有待处理的事件
        }
    }
    glfwTerminate();//释放资源
    return 0;
}