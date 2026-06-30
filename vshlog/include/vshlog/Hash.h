#pragma once

#include <cstdint>

namespace vsh
{
    constexpr std::uint32_t hash_str(const char* str) {
        std::uint32_t hash = 0;
        while (*str) {
            hash = hash * 31 + *str++;
        }
        return hash;
    }
}