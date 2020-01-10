#include <UWUEngine/Graphics/FBO/FBOModule.h>

FBO FBOModule::CreateFBO()
{
    FBO fbo;
    GLuint fbo_handle = fbo.GetHandleFBO();
    glGenFramebuffers(1, &fbo_handle);
    // read/write to frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_handle);

    return fbo;
}

GLuint FBO::GetHandleFBO()
{
    return fbo_handler_;
}

bool FBO::ValidateFBO()
{
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
    {
        return true;
    }
    return false;
}

void FBO::UseFBO()
{
}

void FBO::UnUseFBO()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::DeleteFBO()
{
    glDeleteFramebuffers(1, &fbo_handler_);
}
