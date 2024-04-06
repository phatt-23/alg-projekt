#ifndef __decoder_h__
#define __decoder_h__

#include "precomp.h"
#include "measurement.h"
#include "interval.h"


class Decoder {
    std::vector<Measurement*> m_measurements;
    std::vector<Measurement*> m_extremes;
    std::vector<Interval*> m_intervals;

    void print_hist_temp(uint32_t t_intervals);
    void print_hist_mstr(uint32_t t_intervals);

public:
    enum PrintType {
        Human,
        Original,
        Bits,
    };

    Decoder();
    Decoder(const char* t_path);
    ~Decoder();

    bool read_in(const char* t_path);
    bool write_to(const char* t_path, PrintType t_type);

    /// sorts the ms by time
    /// would be nice to add the option
    /// to sort by different paramenter
    void sort_ms();
    void rm_dups();
    const std::vector<Measurement*>* find_exts();
    Measurement* get_ext(Ms::PayloadType t_type, Ms::Extreme t_ext) const;
    void set_ext(Ms::PayloadType t_type, Ms::Extreme t_ext, Measurement* t_new);
    Measurement* get_ms(const char* t_time) const;
    std::vector<Interval*>* print_hist(Ms::PayloadType t_type, uint32_t t_intervals);

    void print_ms(PrintType t_type);
};

#endif//__decoder_h__
