#include "utility.h"


void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLCheckError(const char* functionName, const char* file, int line)
{
    bool success = true;

    while (GLenum error = glGetError())
    {
        std::cout << "[OPENGL ERROR] (" << error << ")\n"
            << "FUNCTION NAME: " << functionName << '\n'
            << "FILE: " << file << '\n'
            << "LINE: " << line << '\n'
            << std::endl;

        success = false;
    }

    return success;
}

