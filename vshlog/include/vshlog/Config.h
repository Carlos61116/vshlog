#pragma once

#include "LogLevel.h"

namespace vsh
{
    struct FileSinkConfig {
        bool append{ 0 };
        size_t max_size_bytes{ 0 };
        vsh::LogLevel min_log_level{vsh::LogLevel::TRACE};
    };

    struct ConsoleSinkConfig {
        vsh::LogLevel min_log_level{ vsh::LogLevel::TRACE };
    };
}