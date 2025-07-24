#pragma once
#include <memory>

namespace crystal
{

    template<typename T>
    using Ref = std::shared_ptr<T>;


    template<typename T>
    using Owned = std::unique_ptr<T>;
}