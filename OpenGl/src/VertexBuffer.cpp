#include"VertexBuffer.h"
#include"Renderer.h"
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GlCall(glGenBuffers(1, &m_RendererID));//创建顶点缓冲区
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));//绑定缓冲区，操作都在这上面进行
    GlCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));//加入数据（顶点信息）
}

VertexBuffer::~VertexBuffer()
{
	GlCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}


