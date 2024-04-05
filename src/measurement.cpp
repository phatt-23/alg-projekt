#include "inc/measurement.h"
#include "inc/bit_conversion.h"
#include "inc/precomp.h"

Measurement::Measurement() {
    memset(m_time, 0, sizeof(uint8_t) * (sizeof(m_time)/sizeof(*m_time)));
    memset(m_payload, 0, sizeof(uint8_t) * (sizeof(m_time)/sizeof(*m_time)));
}

Measurement::Measurement(const std::string& t_time, const std::string& t_payload) 
{
    memset(m_time, 0, sizeof(uint8_t) * (sizeof(m_time)/sizeof(*m_time)));
    memset(m_payload, 0, sizeof(uint8_t) * (sizeof(m_time)/sizeof(*m_time)));

    char l_yy_str[5] = { 0 };
    char l_mm_str[3] = { 0 };
    char l_dd_str[3] = { 0 };
    char l_hh_str[3] = { 0 };
    char l_mn_str[3] = { 0 };
    char l_ss_str[3] = { 0 };

    for(int i = 0; i < 4; ++i) 
        l_yy_str[i] = t_time.at(i);

    l_mm_str[0] = t_time.at(5);
    l_mm_str[1] = t_time.at(6);

    l_dd_str[0] = t_time.at(8);
    l_dd_str[1] = t_time.at(9);

    l_hh_str[0] = t_time.at(11);
    l_hh_str[1] = t_time.at(12);

    l_mn_str[0] = t_time.at(14);
    l_mn_str[1] = t_time.at(15);
    
    l_ss_str[0] = t_time.at(17);
    l_ss_str[1] = t_time.at(18);

    uint32_t l_yy_num = std::atoi(l_yy_str);
    uint32_t l_mm_num = std::atoi(l_mm_str);
    uint32_t l_dd_num = std::atoi(l_dd_str);
    uint32_t l_hh_num = std::atoi(l_hh_str);
    uint32_t l_mn_num = std::atoi(l_mn_str);
    uint32_t l_ss_num = std::atoi(l_ss_str);

    m_time[0] |= l_yy_num >> 6;
    m_time[1] |= l_yy_num << 2;
    m_time[1] |= l_mm_num >> 2;
    m_time[2] |= l_mm_num << 6;
    m_time[2] |= l_dd_num << 1;
    m_time[2] |= l_hh_num >> 4;
    m_time[3] |= l_hh_num << 4;
    m_time[3] |= l_mn_num >> 2;
    m_time[4] |= l_mn_num << 6;
    m_time[4] |= l_ss_num;

    uint64_t l_payload = bit_conv::u128_from(t_payload.c_str());
    for(size_t i = 0; i < 5; ++i) {
        m_payload[i] = l_payload >> ((4 - i) * 8);
    }

    if(__measurement_dbg__) {
        __info_all__ __endl__
        printf(
            "[time : 0b -> (%.8b) (%.8b) (%.8b) (%.8b) (%.8b)]\n", 
            m_time[0], m_time[1], m_time[2], m_time[3], m_time[4]
        );
        printf(
            "[result : 0b -> Y: %.14b, M: %.4b, D: %.5b, h: %.5b m: %.6b s: %.6b]\n",
            l_yy_num, l_mm_num, l_dd_num, l_hh_num, l_mn_num, l_ss_num
        );
        printf(
            "[payload : 0x -> %.2x %.2x %.2x %.2x %.2x from %s]\n",
            m_payload[0], m_payload[1], m_payload[2], m_payload[3], m_payload[4], 
            t_payload.c_str()
        );
    }


}

Measurement::~Measurement() {
    
}

uint64_t Measurement::get_time_cmp() const {
    uint64_t l_time = 0;
    l_time |= uint64_t(m_time[0]) << 32; 
    l_time |= uint32_t(m_time[1]) << 24;
    l_time |= uint32_t(m_time[2]) << 16;
    l_time |= uint16_t(m_time[3]) << 8;
    l_time |= m_time[4];
    return l_time;
}

uint64_t Measurement::get_payload_cmp() const {
    uint64_t l_payload = 0;
    l_payload |= uint64_t(m_time[0]) << 32; 
    l_payload |= uint32_t(m_time[1]) << 24;
    l_payload |= uint32_t(m_time[2]) << 16;
    l_payload |= uint16_t(m_time[3]) << 8;
    l_payload |= m_time[4];
    return l_payload;
}

const uint8_t* Measurement::get_time_arr() const {
    return m_time;
}

const uint8_t* Measurement::get_payload_arr() const {
    return m_payload;
}

#include <cstring>
#include <cstdlib>

std::string Measurement::get_og_fmt() {
    uint16_t l_time[5] = { 0 };
    for(size_t i = 0; i < 5; ++i) 
        l_time[i] = m_time[i];

    uint16_t l_yy_num = l_time[0] << 6 | m_time[1] >> 2;
    uint16_t l_mm_num = (l_time[1] & 0x03) << 2 | l_time[2] >> 6;
    uint16_t l_dd_num = (l_time[2] >> 1) & 0x1f;
    uint16_t l_hh_num = (l_time[2] & 0x01) << 4 | l_time[3] >> 4;
    uint16_t l_mn_num = (l_time[3] & 0x0f) << 2 | l_time[4] >> 6;
    uint16_t l_ss_num = (l_time[4] & 0x3f);


    char l_str[__buffer_len__] = { 0 };
    sprintf(
        l_str, "%.2d-%.2d-%.2dT%.2d:%.2d:%.2d %.2X%.2X%.2X%.2X%.2X", 
        l_yy_num, l_mm_num, l_dd_num,l_hh_num, l_mn_num, l_ss_num,
        m_payload[0], m_payload[1], m_payload[2], m_payload[3], m_payload[4]
    );
    
    return std::string(l_str);
}

std::string Measurement::get_fmtd_pl() {
    uint32_t l_vltg = 30 * m_payload[0];
    float l_C = 0.1 * float(256 * m_payload[1] + m_payload[2]);
    float l_M = 0.1 * float(256 * m_payload[3] + m_payload[4]);

    char l_str[__buffer_len__] = { 0 };
    sprintf(
        l_str, 
        "{ V(mV): %d, t(C): %.2f, M(%%): %.2f }",
        l_vltg, l_C, l_M
    );

    return std::string(l_str);
}

std::string Measurement::get_fmtd_tm() {
    uint16_t l_time[5] = { 0 };
    for(size_t i = 0; i < 5; ++i) 
        l_time[i] = m_time[i];

    uint16_t l_yy_num = l_time[0] << 6 | m_time[1] >> 2;
    uint16_t l_mm_num = (l_time[1] & 0x03) << 2 | l_time[2] >> 6;
    uint16_t l_dd_num = (l_time[2] >> 1) & 0x1f;
    uint16_t l_hh_num = (l_time[2] & 0x01) << 4 | l_time[3] >> 4;
    uint16_t l_mn_num = (l_time[3] & 0x0f) << 2 | l_time[4] >> 6;
    uint16_t l_ss_num = (l_time[4] & 0x3f);

    char l_str[__buffer_len__] = { 0 };
    sprintf(
        l_str,
        "{ (%.4d.%.2d.%.2d) %.2d:%.2d:%.2d }",
        l_yy_num, l_mm_num, l_dd_num,l_hh_num, l_mn_num, l_ss_num
    );
    
    return std::string(l_str);
}

uint16_t Measurement::get_pl_vltg() {
    return 30 * m_payload[0];
}

float Measurement::get_pl_temp() {
    return 0.1 * float(256 * m_payload[1] + m_payload[2]);
}

float Measurement::get_pl_mstr() {
    return 0.1 * float(256 * m_payload[3] + m_payload[4]);
}

