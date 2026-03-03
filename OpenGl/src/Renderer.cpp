#include "Renderer.h"
#include <iostream>

void GlClearError()
{
    while (glGetError() != GL_NO_ERROR);
}
bool GlLogCall(const char* functionCall, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGl Error] (" << error << "): " << functionCall <<
            " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}