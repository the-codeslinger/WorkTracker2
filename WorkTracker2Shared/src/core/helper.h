#pragma once

#include <algorithm>
#include <functional>

namespace Core {

/**
 * Wrapper for `std::for_each` that iterates over the whole container.
 */
template<typename Container, typename Func>
inline Func forEach(const Container& container, Func func)
{
    return std::for_each(std::begin(container), std::end(container), func);
}

/**
 * Wrapper for `std::find_if` that iterates over the whole container.
 */
template<typename Container, typename Func>
inline typename Container::const_iterator findIf(const Container& container, Func func)
{
    return std::find_if(std::begin(container), std::end(container), func);
}

/**
 * Iterates the container until `func` returns `true`. Returns the found element or a
 * default constructed one.
 */
template<typename Container>
inline typename Container::value_type
firstOrDefault(
        const Container& container,
        std::function<bool(typename Container::value_type)> func)
{
    for (const auto& item : container) {
        if (func(item)) {
            return item;
        }
    }
    return typename Container::value_type();
}

}
