#pragma once

#include <algorithm>
#include <functional>
#include <optional>

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
 * Wrapper for `std::find_if` that iterates over the whole container.
 *
 * Note: This method returns a iterator reference with which the contents of the list
 *       can be modified.
 */
template<typename Container, typename Func>
inline std::optional<typename Container::value_type>
findValueIf(const Container& container, Func func)
{
    auto found = findIf(container, func);
    if (std::end(container) == found) {
        return std::nullopt;
    }
    return std::make_optional(*found);
}

}
