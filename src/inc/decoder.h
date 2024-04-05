#ifndef __decoder_h__
#define __decoder_h__

#include "precomp.h"
#include "measurement.h"
#include "interval.h"


class Decoder {
    std::vector<Measurement*> m_measurements;
    std::vector<Measurement*> m_extremes;

public:
    enum Extreme {
        Min,
        Max,
    };

    enum PayloadType {
        Temperature,
        Moisture,
    };
    
    enum PrintType {
        Human,
        Bits,
    };

    Decoder();
    Decoder(const char* t_path);
    ~Decoder();

    bool read_in(const char* t_path);
    bool write_to(const char* t_path, PrintType t_type);
    void sort_ms();
    void rm_dups();
    const std::vector<Measurement*>* find_exts();
    Measurement* get_ext(Extreme t_ext) const;
    Measurement* get_ms(const char* t_time) const;
    std::vector<Interval*>* print_hist(PayloadType t_type, uint32_t t_intervals);

    void print_ms(PrintType t_type);
    void dump();
};

#endif//__decoder_h__
