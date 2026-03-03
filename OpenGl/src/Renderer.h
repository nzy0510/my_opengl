#pragma once

#include<GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define Assert(x) if(!(x)) __debugbreak();
#define GLCall(x) GlClearError();\
	x;\
	Assert(GlLogCall(#x, __FILE__, __LINE__))

void GlClearError();
bool GlLogCall(const char* functionCall, const char* file, int line);

class Renderer 
{
public:
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};