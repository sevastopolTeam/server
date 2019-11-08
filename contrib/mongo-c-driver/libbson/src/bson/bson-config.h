#pragma once

#if defined(__linux__)
#include "bson-config-linux.h"
#endif

#if defined(__APPLE__)
#include "bson-config-osx.h"
#endif

#if defined(_MSC_VER)
#include "bson-config-win.h"
#endif
