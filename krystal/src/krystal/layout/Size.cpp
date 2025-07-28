#include "krystal/geometry/Size.hpp"
#include <climits>

namespace ktl::geometry
{

    int Size::getHeightAsInt() const
    {
        return height <= INT_MAX ? static_cast<int>(height) : INT_MAX;
    }
    int Size::getWidthAsInt() const
    {
        return width <= INT_MAX ? static_cast<int>(width) : INT_MAX;
    }
} // namespace ktl::layout