#ifndef __bit_conversion_h__
#define __bit_conversion_h__

#include "precomp.h"

/**
 * @brief Namespace containing functions for bitwise conversions.
 */
namespace bit_conv {

    /**
     * @brief Convert a string to a 128-bit unsigned integer.
     *
     * @param t_str The input string to convert.
     * @return __uint128_t The resulting 128-bit unsigned integer.
     */
    __uint128_t u128_from(const char* t_str);

    /**
     * @brief Convert a string to a 64-bit unsigned integer.
     *
     * @param t_str The input string to convert.
     * @return __uint64_t The resulting 64-bit unsigned integer.
     */
    __uint64_t u64_from(const char* t_str);

    /**
     * @brief Convert a 64-bit unsigned integer to a hexadecimal string.
     *
     * @param t_num The 64-bit unsigned integer to convert.
     * @param t_n The desired length of the hexadecimal string.
     * @return std::string The resulting hexadecimal string.
     */
    std::string hex_from_str(uint64_t t_num, size_t t_n);
};

#endif//__bit_conversion_h__
