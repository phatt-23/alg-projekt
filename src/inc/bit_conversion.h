#ifndef __bit_conversion_h__
#define __bit_conversion_h__

#include "precomp.h"

namespace bit_conv {
    __uint128_t u128_from(const char* t_str);
    __uint64_t u64_from(const char* t_str);
    std::string hex_from_str(uint64_t t_num, size_t t_n);
};

#endif//__bit_conversion_h__
