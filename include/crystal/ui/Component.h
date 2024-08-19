#pragma once

#include "crystal/layout/Size.h"
#include "crystal/geometry/Vector2.h"


namespace crystal
{
    class Component
    {
    public:
        virtual void render();
        virtual void update();
        virtual const crystal::layout::Size& getSize();
        virtual const crystal::geometry::Vector2& getPosition();
        virtual ~Component() = default;
    };
}