#pragma once

#include "Capybara/Core/Base.h"

#include "Framebuffer.h"

namespace Capybara {

    struct RenderPassSpecification
    {
        Ref<Framebuffer> TargetFramebuffer;
    };

    class RenderPass
    {
    public:
        virtual ~RenderPass() {}

        virtual const RenderPassSpecification& GetSpecification() const = 0;

        static Ref<RenderPass> Create(const RenderPassSpecification& spec);
    };

}