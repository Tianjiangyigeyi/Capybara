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

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;
        
        void Begin();
        void End();
    private:
        float m_Time = 0.0f;
    };

}
