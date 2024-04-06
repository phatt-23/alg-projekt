#ifndef __interval_h__
#define __interval_h__

#include "precomp.h"
#include "measurement.h"

class Interval { // can be used for both temperature and moisture
    uint32_t m_freq;

    // these floats hold the possible range
    float m_lwr_range_fl;
    float m_upr_range_fl;

    // these measurements specify its range
    Measurement* m_lwr_bound;
    Measurement* m_upr_bound;

    Ms::PayloadType m_type;

public:
    Interval(Ms::PayloadType t_type, float t_lwr, float t_upr);
    ~Interval();
    bool set_ms(Ms::Extreme t_ext, Measurement* t_ms);
    void set_freq(uint32_t t_n);
    void inc_freq();

    Measurement* get_ms(Ms::Extreme t_ext) const;
    float get_range_fl(Ms::Extreme t_ext) const;
    uint32_t get_freq() const;
};

#endif//__interval_h__
