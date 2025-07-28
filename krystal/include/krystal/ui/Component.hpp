#pragma once

#include "krystal/geometry/Vector2.hpp"
#include "krystal/layout/Size.hpp"

namespace ktl
{
    class Component
    {
        public:
            virtual void                              render ();
            virtual void                              update ();
            virtual const ktl::geometry::Size&      getSize ();
            virtual const ktl::geometry::Vector2& getPosition ();
            virtual ~Component () = default;
    };
} // namespace ktl