#ifndef __interval_h__
#define __interval_h__

#include "precomp.h"
#include "measurement.h"

class Interval { // can be used for both temperature and moisture
    struct Pair {
        uint32_t m_value;
        uint32_t m_freq; 
    };

    uint32_t t_size;
    Measurement* m_lower_bound;
    Measurement* m_upper_bound;
    std::vector<Pair> m_pairs;
public:
    Interval();
    ~Interval();
};

#endif//__interval_h__
