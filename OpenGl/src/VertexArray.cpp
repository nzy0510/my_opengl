#include"VertexArray.h"
#include"Renderer.h"
VertexArray::VertexArray()
{
	GlCall(glGenVertexArrays(1, &m_RendererID));
	GlCall(glBindVertexArray(m_RendererID));
}

VertexArray::~VertexArray()
{
	GlCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)//绑定缓冲区并设置布局
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for(unsigned int i=0;i<elements.size();i++)
	{
		const auto& element = elements[i];
		GlCall(glEnableVertexAttribArray(i));
		GlCall(glVertexAttribPointer(i, element.count, element.type, element.normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)offset));//设置布局
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);//计算偏移量，为可能有的下一个属性做准备，进行下一轮循环
	}

}

void VertexArray::Bind()
{
	GlCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind()
{
	GlCall(glBindVertexArray(0));
}
