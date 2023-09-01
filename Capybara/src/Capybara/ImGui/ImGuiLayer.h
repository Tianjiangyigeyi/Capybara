#pragma once

#include "Capybara/Layer.h"
#include "Capybara/Events/ApplicationEvent.h"
#include "Capybara/Events/MouseEvent.h"
#include "Capybara/Events/KeyEvent.h"

namespace Capybara
{
    class CAPYBARA_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Event& event) override;
    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
        bool OnMouseMovedEvent(MouseMovedEvent& event);
        bool OnMouseScrolledEvent(MouseScrolledEvent& event);
        bool OnKeyPressedEvent(KeyPressedEvent& event);
        bool OnKeyReleasedEvent(KeyReleasedEvent& event);
        bool OnKeyTypedEvent(KeyTypedEvent& event);
        bool OnWindowResizeEvent(WindowResizeEvent& event);

    private:
        float m_Time = 0.0f;
    };

}
