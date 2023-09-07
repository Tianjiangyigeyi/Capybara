#pragma once

#include "Capybara/Core/Input.h"

namespace Capybara
{
    class WindowsInput : public Input
    {
    public:
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override;
        virtual bool IsMouseButtonPressedImpl(int button) override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
    };

}
