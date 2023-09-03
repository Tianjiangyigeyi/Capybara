#pragma once

#include "Capybara/Window.h"
#include <GLFW/glfw3.h>

#include "Capybara/Renderer/GraphicsContext.h"

namespace Capybara
{
    class WindowsWindow :public Window
    {
    public:
        WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        inline unsigned int GetWidth() const override { return m_Data.Width; }
        inline unsigned int GetHeight() const override { return m_Data.Height; }

        // Window properties
        inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
        void SetVsync(bool enabled) override;
        bool IsVsync() const override;
        inline void* GetNativeWindow() const { return m_Window; }
    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();

        GLFWwindow* m_Window;
        GraphicsContext* m_Context;
            
        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool Vsync;

            EventCallbackFn EventCallback;
        };
        WindowData m_Data;
    };

}
