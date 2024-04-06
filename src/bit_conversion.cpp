#include "inc/bit_conversion.h"
#include "inc/precomp.h"

static char s_values[] = "0123456789ABCDEF";

__uint128_t bit_conv::u128_from(const char* t_str) {
    size_t l_len = strlen(t_str);
    assert(l_len != 16);

    l_len -= 1;
    uint64_t l_ret = 0;
    for(size_t i = 0; t_str[i] != '\0'; ++i) {
        for(size_t j = 0; j < 16; ++j) {
            if(t_str[i] == s_values[j] || t_str[i] == (s_values[j] | 0x20)) {
                l_ret += j << ((l_len - i) * 4);
            }
        }
    }
    return l_ret;
}

__uint64_t bit_conv::u64_from(const char* t_str) {
    (void) t_str;
    return 0;
}

std::string bit_conv::hex_from_str(uint64_t t_num, size_t t_n) {
    char l_str[__buffer_len__] = { 0 };

    for(size_t i = 1; i < t_n + 1; ++i) {
        l_str[t_n - i] = s_values[(t_num & (0xf << (4*(i - 1)))) >> 4*(i - 1)]; 
        printf("%c\n", s_values[(t_num & (0xf << (4*(i - 1)))) >> 4*(i - 1)]);
    }
    printf("converted %.40lb -> %.10lx -> %s\n", t_num, t_num, l_str);
    
    return std::string(l_str);
}
