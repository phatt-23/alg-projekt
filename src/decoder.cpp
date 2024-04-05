#include "inc/decoder.h"
#include "inc/measurement.h"
#include "inc/precomp.h"

Decoder::Decoder() 
{
    if(__decoder_dbg__) {
        __info_all__ __endl__ 
    }
    for(size_t i = 0; i < 4; ++i)
        m_extremes.emplace_back(nullptr);
}

Decoder::Decoder(const char* t_path) {
    if(__decoder_dbg__) {
        __info_all__ __endl__;
    }
    this->read_in(t_path);
}

Decoder::~Decoder() {
    if(__decoder_dbg__) {
        __info_all__ __endl__
    }
    for(size_t i = 0; i < 4; ++i)
        m_extremes.emplace_back(nullptr);
}


bool Decoder::read_in(const char* t_path) {
    std::ifstream l_file(t_path);
    if(l_file.is_open()) {
        __info_all__ printf("reading in the file %s\n", t_path);
        std::string l_time_str, l_payload_str;
        while(l_file.good()) {
            l_file >> l_time_str >> l_payload_str;
            m_measurements.emplace_back(new Measurement(l_time_str, l_payload_str));
            if(__decoder_dbg__) {
                __info_all__ 
                printf("added [%s :: %s]\n", l_time_str.c_str(), l_payload_str.c_str());
            }
        }
        return true;
    }
    __error_all__ printf("failed to read the file %s\n", t_path);
    return false;
}

bool Decoder::write_to(const char* t_path, PrintType t_type) {
    if(__decoder_dbg__) {
        __info_all__ printf("began writing to file %s\n", t_path);
    }

    std::ofstream l_file(t_path);
    if(l_file.is_open()) {
        switch (t_type) {
            case PrintType::Bits:
                // doesn't write individual bits 
                // but does it in form of a decimal number 
                l_file.close();
                l_file.open(t_path, std::ios::binary);
                for(Measurement* m : m_measurements) {
                    l_file 
                        << m->get_time_cmp() 
                        << " " 
                        << m->get_payload_cmp() 
                        << std::endl;
                }
                break;
            case PrintType::Original:
                for(Measurement* m : m_measurements) {
                    l_file << m->get_og_fmt() << std::endl;
                }
                break;
            case PrintType::Human:
                char l_str[__buffer_len__] = { 0 };
                for(size_t i = 0; i < m_measurements.size(); ++i) {
                    sprintf(l_str,
                        "[%ld]\ttime %s, payload %s", 
                        i, m_measurements.at(i)->get_fmtd_tm().c_str(), 
                        m_measurements.at(i)->get_fmtd_pl().c_str()
                    );
                    l_file << l_str << std::endl;
                }
                break;
        }
        l_file.close();
        return true;
    }

    __error_all__ printf("failed to write into file %s\n", t_path);
    return false;
}

void Decoder::sort_ms() {
    uint32_t l_fn_calls = 0;
    static std::function<size_t(std::vector<Measurement*>*, size_t, size_t)> l_partition 
        = [&](std::vector<Measurement*>* t_ms, size_t t_start, size_t t_end) -> size_t 
        {
            Measurement* l_pivot = t_ms->at(t_start);
            size_t l_count = 0;
            for(size_t i = t_start + 1; i <= t_end; ++i) {
                if(t_ms->at(i)->get_time_cmp() <= l_pivot->get_time_cmp()) {
                    l_count++;
                }    
            }
            size_t l_pivot_idx = t_start + l_count;
            std::swap(t_ms->at(l_pivot_idx), t_ms->at(t_start));
            size_t l_i = t_start;
            size_t l_j = t_end;
            while(l_i < l_pivot_idx && l_j > l_pivot_idx) {
                while(t_ms->at(l_i)->get_time_cmp() <= l_pivot->get_time_cmp())
                    l_i++;
                while(t_ms->at(l_j)->get_time_cmp() > l_pivot->get_time_cmp())
                    l_j--;
                if(l_i < l_pivot_idx && l_j > l_pivot_idx) {
                    std::swap(t_ms->at(l_i++), t_ms->at(l_j--));
                }
            }
            return l_pivot_idx;
        };

    static std::function<void(std::vector<Measurement*>*, int32_t, int32_t)> l_qsort 
        = [&](std::vector<Measurement*>* t_ms, int32_t t_start, int32_t t_end) -> void
        {
            l_fn_calls++;
            if(t_start >= t_end) return;
            size_t l_p = l_partition(t_ms, t_start, t_end);
            l_qsort(t_ms, t_start, l_p - 1);
            l_qsort(t_ms, l_p + 1, t_end);
        };

    if(__decoder_dbg__) { __info_all__ printf("began sorting measurements by time\n"); }

    l_qsort(&m_measurements, 0, m_measurements.size() - 1);

    if(__decoder_dbg__) { __info_all__ printf("done sorting measurements by times (fn-calls: %d)\n", l_fn_calls); }
}

void Decoder::rm_dups() {
    if(__decoder_dbg__) { __info_all__ printf("began removing duplicates\n"); }
    for(size_t i = 1; i < m_measurements.size(); ++i) {
        if(m_measurements[i - 1]->get_time_cmp() == m_measurements[i]->get_time_cmp()) {
            m_measurements.erase(m_measurements.begin() + i-- - 1);
        }
    }
    if(__decoder_dbg__) { __info_all__ printf("done removing duplicates\n"); }
}

const std::vector<Measurement*>* Decoder::find_exts() {
    if(__decoder_dbg__) { __info_all__ printf("finding the extremes\n"); }
    for(Measurement*& m : m_extremes) {
        if(m == nullptr) {
            m = m_measurements.at(0);
        }
    }

    // print extremes -> might factor out to another function
    printf("min temperature: %.2f\n", get_ext(Temperature, Min)->get_pl_temp());
    printf("max temperature: %.2f\n", get_ext(Temperature, Max)->get_pl_temp());
    printf("min moisture: %.2f\n", get_ext(Moisture, Min)->get_pl_mstr());
    printf("max moisture: %.2f\n", get_ext(Moisture, Max)->get_pl_mstr());

    for(Measurement* m : m_measurements) {
        if(m->get_pl_temp() < get_ext(Temperature, Min)->get_pl_temp()) {
            printf("setting min T\n");
            set_ext(Temperature, Min, m);
        }
        if(m->get_pl_temp() > get_ext(Temperature, Max)->get_pl_temp()) {
            printf("setting max T\n");
            set_ext(Temperature, Max, m);
        }
        if(m->get_pl_mstr() < get_ext(Moisture, Min)->get_pl_mstr()) {
            set_ext(Moisture, Min, m);
        }
        if(m->get_pl_mstr() > get_ext(Moisture, Max)->get_pl_mstr()) {
            set_ext(Moisture, Max, m);
        }
    #if 0
    #endif
    }

    
    return &m_extremes;
}

Measurement* Decoder::get_ext(PayloadType t_type, Extreme t_ext) const {
    switch(t_type) {
        case PayloadType::Temperature:
            switch(t_ext) {
                case Extreme::Min:
                    if(m_extremes.at(0) != nullptr)
                        return m_extremes.at(0);
                    break;
                case Extreme::Max:
                    if(m_extremes.at(1) != nullptr)
                        return m_extremes.at(1);
                    break;
                default: break;
            }
            break;
        case PayloadType::Moisture:
            switch(t_ext) {
                case Extreme::Min:
                    if(m_extremes.at(2) != nullptr)
                        return m_extremes.at(2);
                    break;
                case Extreme::Max:
                    if(m_extremes.at(3) != nullptr)
                        return m_extremes.at(3);
                    break;
                default: break;
            }
            break;
        default: break;
    }
    __error_all__ printf("requested extreme not defined / found\n");
    return nullptr;
}

void Decoder::set_ext(PayloadType t_type, Extreme t_ext, Measurement* t_new) {
    if(t_new != nullptr) {
        switch(t_type) {
            case PayloadType::Temperature:
                switch(t_ext) {
                    case Extreme::Min:
                        if(m_extremes.at(0) != nullptr)
                            m_extremes.at(0) = t_new;
                        break;
                    case Extreme::Max:
                        if(m_extremes.at(1) != nullptr)
                            m_extremes.at(1) = t_new;
                        break;
                    default: break;
                }
                break;
            case PayloadType::Moisture:
                switch(t_ext) {
                    case Extreme::Min:
                        if(m_extremes.at(2) != nullptr)
                            m_extremes.at(2) = t_new;
                        break;
                    case Extreme::Max:
                        if(m_extremes.at(3) != nullptr)
                            m_extremes.at(3) = t_new;
                        break;
                    default: break;
                }
                break;
            default: break;
        }
    }
    __error_all__ printf("requested extreme for setting not defined / found\n");
}


Measurement* Decoder::get_ms(const char* t_time) const {
    (void) t_time;
    return nullptr;
    
}

std::vector<Interval*>* Decoder::print_hist(PayloadType t_type, uint32_t t_intervals) {
    (void) t_type;
    (void) t_intervals;
    return nullptr;
}

void Decoder::print_ms(PrintType t_type) {
    if(__decoder_dbg__) { __info_all__ printf("printing out the measurements\n"); }
    switch (t_type) {
        case PrintType::Bits:
            for(size_t i = 0; i < m_measurements.size(); ++i) {
                const uint8_t* l_tm = m_measurements[i]->get_time_arr();
                const uint8_t* l_pl = m_measurements[i]->get_payload_arr();
                printf(
                    "[%ld]\ttime [%.8b %.8b %.8b %.8b %.8b], payload [%.8b %.8b %.8b %.8b %.8b]\n", 
                    i, l_tm[0], l_tm[1], l_tm[2], l_tm[3], l_tm[4],
                    l_pl[0], l_pl[1], l_pl[2], l_pl[3], l_pl[4] 
                );
            }
            break;
        case PrintType::Human:
            for(size_t i = 0; i < m_measurements.size(); ++i) {
                printf(
                    "[%ld]\ttime %s, payload %s\n", 
                    i, m_measurements.at(i)->get_fmtd_tm().c_str(), 
                    m_measurements.at(i)->get_fmtd_pl().c_str()
                );
            }
            break;
        case PrintType::Original:
            for(Measurement* m : m_measurements) {
                std::cout << m->get_og_fmt() << std::endl;
            }
            break;
        default: break;
    }
    if(__decoder_dbg__) { __info_all__ printf("done printing the measurements\n"); }
}


