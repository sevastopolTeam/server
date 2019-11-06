#pragma once

#include <memory>

template<class T, class D = std::default_delete<T>>
using THolder = std::unique_ptr<T, D>;
