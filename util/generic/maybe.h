#pragma once

#include <optional>

template <class T>
using TMaybe = std::optional<T>;

inline constexpr std::nullopt_t Nothing() {
    return std::nullopt;
}
