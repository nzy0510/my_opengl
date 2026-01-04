#pragma once
#include<vector>
#include"Renderer.h"
#include<GL/glew.h>
struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	bool normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		}
		_ASSERT(false);
		return 0;
	}
};
class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;//可存储多个属性
	unsigned int m_Stride;
public:
	VertexBufferLayout() 
		:m_Stride(0)
	{}
	~VertexBufferLayout() {}
	template<typename T>//模板类必须在头文件定义
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	inline const std::vector<VertexBufferElement> GetElements() const& { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};
// 模板特化必须在类外实现
template<>
inline void VertexBufferLayout::Push<float>(unsigned int count)
{
	m_Elements.push_back({ GL_FLOAT, count, false });
	m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT)*count;
}

template<>
inline void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
	m_Elements.push_back({ GL_UNSIGNED_INT, count, false });
	m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT)*count;
}

template<>
inline void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
	m_Elements.push_back({ GL_UNSIGNED_BYTE, count, true });
	m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE)*count;
}