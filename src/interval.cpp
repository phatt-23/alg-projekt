#include "inc/interval.h"
#include "inc/measurement.h"
#include "inc/precomp.h"

Interval::Interval(Ms::PayloadType t_type, float t_lwr, float t_upr)
    : m_freq(0)
    , m_lwr_range_fl(t_lwr)
    , m_upr_range_fl(t_upr)
    , m_lwr_bound(nullptr)
    , m_upr_bound(nullptr)
    , m_type(t_type)
{
    if(__interval_dbg__) { __info_all__ printf("(%.2f, %.2f)\n", t_lwr, t_upr); }
}

Interval::~Interval() {
    if(__interval_dbg__) { 
        __info_all__ 
        printf(
            "decons called for (%.2f, %.2f)\n", 
            m_lwr_range_fl, m_upr_range_fl
        );
    }
}

bool Interval::set_ms(Ms::Extreme t_ext, Measurement* t_ms) {
    switch(m_type) {
        case Ms::Temperature:
            switch(t_ext) {
                case Ms::Min:
                    if(t_ms->get_pl_temp() < m_lwr_bound->get_pl_mstr()) {
                        m_lwr_bound = t_ms;
                        return true;
                    }
                    break;
                case Ms::Max:
                    if(t_ms->get_pl_temp() > m_upr_bound->get_pl_mstr()) {
                        m_upr_bound = t_ms;
                        return true;
                    }
                    break;
                default: break;
            }
            break;
        case Ms::Moisture:
            switch(t_ext) {
                case Ms::Min:
                    if(t_ms->get_pl_mstr() < m_lwr_bound->get_pl_mstr()) {
                        m_lwr_bound = t_ms;
                        return true;
                    }
                    break;
                case Ms::Max:
                    if(t_ms->get_pl_temp() < m_upr_bound->get_pl_mstr()) {
                        m_upr_bound = t_ms;
                        return true;
                    }
                    break;
                default: break;
            }
            break;
        default: break;
    }
    return false;
}

void Interval::set_freq(uint32_t t_n) {
    m_freq = t_n;
}

void Interval::inc_freq() {
    m_freq++;
}


Measurement* Interval::get_ms(Ms::Extreme t_ext) const {
    switch(t_ext) {
        case Ms::Min: return m_lwr_bound;
        case Ms::Max: return m_upr_bound;
        default: break;
    }
    __error_all__ printf("requested ms wasn't found\n");
    return nullptr;
}

float Interval::get_range_fl(Ms::Extreme t_ext) const {
    switch(t_ext) {
        case Ms::Min: return m_lwr_range_fl;
        case Ms::Max: return m_upr_range_fl;
        default: break;
    }
    __error_all__ printf("requested ms wasn't found\n");
    return 0;
}


uint32_t Interval::get_freq() const {
    return m_freq;
}

