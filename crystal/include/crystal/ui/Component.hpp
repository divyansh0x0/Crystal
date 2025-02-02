#pragma once

#include "crystal/geometry/Vector2.hpp"
#include "crystal/layout/Size.hpp"

namespace crystal
{
    class Component
    {
        public:
            virtual void                              render ();
            virtual void                              update ();
            virtual const crystal::layout::Size&      getSize ();
            virtual const crystal::geometry::Vector2& getPosition ();
            virtual ~Component () = default;
    };
} // namespace crystal