#pragma once
#include "precomp.h"
#include "Capybara/Core/Layer.h"


namespace Capybara
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ImGuiLayer(const std::string& name);
        virtual ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;
        
        void Begin();
        void End();
        
    private:
        float m_Time = 0.0f;
    };

}
