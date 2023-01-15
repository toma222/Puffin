
#pragma once

#include <memory>

#define MAX_SPRITES_IN_SCENE 20

namespace puffin
{
    // Thanks to the Cherno for this bit of code!
    template <typename T>
    using Ref = std::shared_ptr<T>;
    template <typename T, typename... Args>
    constexpr Ref<T> CreateRef(Args &&...args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
} // namespace puffin
