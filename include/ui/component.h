#pragma once

#include "core/Core.h"

namespace crystal
{
    class Component
    {
    public:
        virtual void render();
        virtual void update();
        virtual const crystal::Size& getSize();
        virtual const crystal::Vector2f& getPosition();
        virtual ~Component() = default;
    };
}