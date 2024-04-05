#ifndef __measuerement_h__
#define __measuerement_h__

#include "precomp.h"

// 5-bytes arch
// 0b00000000  0b00000000  0b00000000  0b00000000  0b00000000 
//   yyyyyyyy    yyyyyymm    mmdddddh    hhhhmmmm    mmssssss
// - Year   => will last until 2^14
// - Month  => 1..12 (2^4)
// - Day    => 1..31 (2^5)
// - Hour   => 0..23 (2^5)
// - Minute => 0..59 (2^6)
// - Second => 0..59 (2^6)

class Measurement {
    uint8_t m_time[5];
    uint8_t m_payload[5];

public:
    Measurement(const std::string& t_time, const std::string& t_payload);
    ~Measurement();
    uint64_t get_time_cmp() const;
    uint64_t get_payload_cmp() const;
    const uint8_t* get_time_arr() const;
    const uint8_t* get_payload_arr() const;
    std::string get_formated();
};

#endif//__measuerement_h__
