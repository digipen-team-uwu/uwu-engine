#pragma once
#include <GL/glew.h>

class FBO;

namespace FBOModule
{
    FBO CreateFBO();
}

class FBO
{
public:
    FBO() = default;
    ~FBO() = default;

    GLuint GetHandleFBO();
    bool ValidateFBO();
    void UseFBO();
    void UnUseFBO();
    void DeleteFBO();
private:
    GLuint fbo_handler_;
};