#pragma once
#include "exported.hpp"
#include <cstdint>
#include <string>s

namespace memory
{
    // This namespace contains functions related to memory manipulation

    static std::pair<std::uintptr_t, std::uint32_t> _memory_module{};

    bool initialize( const wchar_t* const module_name );
    std::uintptr_t from_pattern( const char* const sig, const char* const mask );
}
