#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<fstream> //文件流
#include<string>
#include<sstream>//字符串流
//#include<tuple>//元组，可用于为函数实现两个返回值
//CPU 端：创建窗口，定义数据数组。
//传输：把数据塞给 GPU(VBO)。
//设置：告诉 GPU 怎么读这些数据(VertexAttribPointer)。
//编程：写 Shader 告诉 GPU 怎么画(Vertex Shader 定点, Fragment Shader 上色)。
//绘制：在循环中不断调用 DrawCall。
static void GlClearError() {
    while (glGetError() != GL_NO_ERROR);
}
static void GlCheckError() {
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
        std::cout << "OpenGL Error: " << error << std::endl;
    }
}
struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};
static ShaderProgramSource ParseShader(const std::string& filepath) {
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGEMENT = 1
    };
    std::string line;
    ShaderType type = ShaderType::NONE;
    std::stringstream ss[2];
    while (getline(stream, line)) { 
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                //set mode to vertex
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                //set mode to fragment
                type = ShaderType::FRAGEMENT;
            }
        }
        else {
            ss[int(type)] << line << '\n';
        }
    }
    return { ss[0].str(),ss[1].str() };//将缓冲区内容转化为std::string
}
static unsigned int CompileShader(unsigned int type, const std::string& source) {//source 代表源码
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    //错误输出
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile"<<
            (type == GL_VERTEX_SHADER? "vertex":"fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        delete []message;
        glDeleteShader(id);
        return 0;
    }
    return id;
}
static unsigned int CreateShader(const std::string& vertexshader, const std::string& fragmentshader) {//编写着色器shader
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexshader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentshader);
     
    glAttachShader(program,vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
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
    unsigned int buffer;
    glGenBuffers(1, &buffer);//创建顶点缓冲区
    glBindBuffer(GL_ARRAY_BUFFER, buffer);//绑定缓冲区，操作都在这上面进行
    glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(float), vertices, GL_STATIC_DRAW);//加入数据（顶点信息）

    glEnableVertexAttribArray(0);// 一定要启用，否则黑屏
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);//告知opengl数据的内存布局,即告诉gpu如何理解数据

    unsigned int ibo;
    glGenBuffers(1, &ibo);//创建索引缓冲区
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);//绑定缓冲区
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),(const void*)(2*sizeof(float)));

    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
    //std::cout << "Vertex" << std::endl;  //测试
    //std::cout << source.VertexSource << std::endl;
    //std::cout <<"Fragement" << std::endl;
    //std::cout << source.FragmentSource << std::endl;
    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);

    int location = glGetUniformLocation(shader, "u_color");
    _ASSERT(location != -1);
    glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f);
    float r = 0.0f;
    float increment = 0.05f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);//清除颜色 

        glUniform4f(location, r , 0.3f, 0.8f, 1.0f);
        if (r > 1.0f) {
            increment = -0.05f;
        }
        else if(r < 0.0f){
            increment = 0.05f;
        }
        r += increment;
        GlClearError();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,nullptr);//绘制正方形，6代表索引的数量，不是顶点的数量
        GlCheckError();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);//交换前缓冲区和后缓冲区的内容：将后台渲染好的完整画面 “一次性” 显示到屏幕上，避免了渲染过程中（画面不完整时）的闪烁问题。

        /* Poll for and process events */
        glfwPollEvents();//检查并处理所有待处理的事件
    }
    glDeleteProgram(shader);
    glfwTerminate();//释放资源
    return 0;
}