#pragma once

#include <chrono>

namespace timehelper
{
    long currentTimeMillis()
    {
        auto millisDuration = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch());
        return static_cast<long>(millisDuration.count());
    }
}