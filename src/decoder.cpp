#include "inc/decoder.h"
#include "inc/measurement.h"
#include "inc/precomp.h"

Decoder::Decoder() 
{
    if(__decoder_dbg__) {
        __info_all__ __endl__ 
    }
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

    std::ofstream l_file(t_path, std::ios_base::binary);
    if(l_file.is_open()) {
        switch (t_type) {
            case PrintType::Bits:
                // doesn't write individual bits 
                // but does it in form of a decimal number 
                for(Measurement* m : m_measurements) {
                    l_file 
                        << m->get_time_cmp() 
                        << " " 
                        << m->get_payload_cmp() 
                        << std::endl;
                }
                break;
            case PrintType::Human:
                // TODO: composes a human readable file 
                for(Measurement* m : m_measurements) {
                    std::cout << m->get_formated();
                }
                break;
            default: break;
        }
        return true;
    }

    __error_all__ printf("failed to write into file %s\n", t_path);
    return false;
}
/*
template<typename T>
void quicksort(T* arr_t, int start, int end) {
    if (start >= end) return;
    int p = partition(arr_t, start, end);
    quicksort(arr_t, start, p - 1);
    quicksort(arr_t, p + 1, end);
}

template<typename T>
int partition(T* arr, size_t start, size_t end) {
    T pivot = arr[start];
    size_t count = 0;
    for(size_t i = start + 1; i <= end; ++i) {
        if(arr[i] <= pivot) count++;
    }

    size_t pivot_index = start + count;
    swap(&arr[pivot_index], &arr[start]);
    
    size_t i = start; 
    size_t j = end;
    while(i < pivot_index && j > pivot_index) {
        while(arr[i] <= pivot) i++;
        while(arr[j] > pivot) j--;
        if(i < pivot_index && j > pivot_index) {
            swap(&arr[i++], &arr[j--]);
        }
    }
    return pivot_index;
}
*/

void Decoder::sort_ms() {
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
            if(t_start >= t_end) return;
            size_t l_p = l_partition(t_ms, t_start, t_end);
            l_qsort(t_ms, t_start, l_p - 1);
            l_qsort(t_ms, l_p + 1, t_end);
        };

    if(__decoder_dbg__) { __info_all__ printf("began sorting measurements by time\n"); }

    l_qsort(&m_measurements, 0, m_measurements.size() - 1);

    if(__decoder_dbg__) { __info_all__ printf("done sorting measurements by time\n"); }
    
}

void Decoder::rm_dups() {
    if(__decoder_dbg__) { __info_all__ printf("began removing duplicates\n"); }
    for(int i = 1; i < m_measurements.size(); ++i) {
        if(m_measurements[i - 1]->get_time_cmp() == m_measurements[i]->get_time_cmp()) {
            m_measurements.erase(m_measurements.begin() + i-- - 1);
        }
    }
    if(__decoder_dbg__) { __info_all__ printf("done removing duplicates\n"); }
}

const std::vector<Measurement*>* Decoder::find_exts() {
    return nullptr;
}

Measurement* Decoder::get_ext(Extreme t_ext) const {
    return nullptr;
}

Measurement* Decoder::get_ms(const char* t_time) const {
    return nullptr;
    
}

std::vector<Interval*>* Decoder::print_hist(PayloadType t_type, uint32_t t_intervals) {
    return nullptr;
    
}

void Decoder::print_ms(PrintType t_type) {
    __info_all__ printf("printing out the measurements\n");
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
            
            break;
        default: break;
    }
    __info_all__ printf("done printing the measurements\n");
}

void Decoder::dump() {
    
}

