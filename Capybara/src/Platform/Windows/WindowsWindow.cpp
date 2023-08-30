#include "precomp.h"
#include "WindowsWindow.h"

#include "Capybara/Log.h"

namespace Capybara
{
    static bool s_GLFWInitialized = false;

    Window* Window::Create(const WindowProps& props)
    {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props)
    {
        Init(props);
    }

    WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    void WindowsWindow::Init(const WindowProps& props)
    {
        m_Data.Title = props.Title;
        m_Data.Height = props.Height;
        m_Data.Width = props.Width;

        CPBR_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);
        if (!s_GLFWInitialized)
        {
            // TODO: glfwTerminal on system shutdown
            int success = glfwInit();
            CPBR_CORE_ASSERT(success, "Couldn't initialize GLFW!");

            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow(static_cast<int>(m_Data.Width), static_cast<int>(m_Data.Height), m_Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVsync(true);
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void WindowsWindow::SetVsync(bool enabled)
    {
        if (enabled)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(0);
        }
        m_Data.Vsync = enabled;
    }

    bool WindowsWindow::IsVsync() const
    {
        return m_Data.Vsync;
    }

}
