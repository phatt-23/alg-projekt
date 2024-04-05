#include "inc/bit_conversion.h"

__uint128_t bit_conv::u128_from(const char* t_str) {
    size_t l_len = strlen(t_str);
    assert(l_len != 16);

    l_len -= 1;
    static char s_values[] = "0123456789ABCDEF";
    uint64_t l_ret = 0;
    for(size_t i = 0; t_str[i] != '\0'; ++i) {
        for(size_t j = 0; j < 16; ++j) {
            if(t_str[i] == s_values[j]) {
                l_ret += j << ((l_len - i) * 4);
            }
        }
    }
    return l_ret;
}

__uint64_t bit_conv::u64_from(const char* t_str) {
    return 0;
}
