// Finished
#pragma once

#include "Event.h"

namespace Capybara
{
    class CAPYBARA_API MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}

        inline float GetX() const { return m_MouseX; }
        inline float GetY() const { return m_MouseY; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
    private:
        float m_MouseX, m_MouseY;
    };

    class CAPYBARA_API MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float x, float y) : m_Xoffset(x), m_Yoffset(y) {}
        inline float GetXOffset() const { return m_Xoffset; }
        inline float GetYOffset() const { return m_Yoffset; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << m_Xoffset << ", " << m_Yoffset;
            return ss.str();
        }
        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
    private:
        float m_Xoffset, m_Yoffset;  
    };

    class CAPYBARA_API MouseButtonEvent : public Event
    {
    public:
        inline int GetMouseButton() const { return m_Button; }

        EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouseButton)
    protected:
        MouseButtonEvent(int button) : m_Button(button) {}
        int m_Button;
    };

    class CAPYBARA_API MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_Button;
            return ss.str();
        }
        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class CAPYBARA_API MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_Button;
            return ss.str();
        }
        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
    
}