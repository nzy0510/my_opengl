#pragma once

#include <GL/glew.h>
void GlClearError();
const char* GlErrorToString(GLenum error);

// Check for errors and print contextual information. Returns true if no error found.
bool GlLogCall(const char* functionCall, const char* file, int line);

// Wrapper macro: usage GlCall(glSomeFunction(...));
#define GlCall(x) (GlClearError(), (x), GlLogCall(#x, __FILE__, __LINE__))