#include "precomp.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

struct GLFWwindow;

namespace Capybara
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle)
    {
        CPBR_CORE_ASSERT(windowHandle, "Window handle is null");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        CPBR_CORE_ASSERT(status, "Failed to Initialize Glad!");


        CPBR_CORE_INFO("OpenGL Info:");
        CPBR_CORE_INFO("    Vendor: {0}", (const char*)glGetString(GL_VENDOR));
        CPBR_CORE_INFO("    Renderer: {0}",(const char*)glGetString(GL_RENDERER));
        CPBR_CORE_INFO("    Version: {0}",(const char*)glGetString(GL_VERSION));

    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }
}
