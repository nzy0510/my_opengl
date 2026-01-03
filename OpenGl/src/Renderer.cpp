#include "Renderer.h"
#include <iostream>

void GlClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

const char* GlErrorToString(GLenum error)
{
    switch (error) {
    case GL_NO_ERROR: return "GL_NO_ERROR";
    case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
    case GL_STACK_OVERFLOW: return "GL_STACK_OVERFLOW";
    case GL_STACK_UNDERFLOW: return "GL_STACK_UNDERFLOW";
    case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
    case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
    default: return "UNKNOWN_GL_ERROR";
    }
}

// Check for errors and print contextual information. Returns true if no error found.
bool GlLogCall(const char* functionCall, const char* file, int line)
{
    bool ok = true;
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
        std::cout << "[OpenGL Error] (" << GlErrorToString(error) << ") "
            << "after call: '" << functionCall << "' "
            << "at " << file << ":" << line << std::endl;
        ok = false;
    }
    return ok;
}

// Wrapper macro: usage GlCall(glSomeFunction(...));
#define GlCall(x) (GlClearError(), (x), GlLogCall(#x, __FILE__, __LINE__))