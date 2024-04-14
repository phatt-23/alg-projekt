#ifndef __decoder_h__
#define __decoder_h__

#include "precomp.h"
#include "measurement.h"
#include "interval.h"


/**
 * @brief Class representing a decoder.
 * 
 * This class provides functionality for decoding
 * and sorting measurements and printing histograms.
 */
class Decoder {
private:
    /// Vector containing measurements.
    std::vector<Measurement*> m_measurements; 
    /// Vector containing extreme measurements.
    std::vector<Measurement*> m_extremes;     
    /// Vector containing intervals.
    std::vector<Interval*> m_intervals;       

    /**
     * @brief Prints a histogram of temperature.
     * 
     * @param t_intervals Number of intervals for the histogram.
     */
    void print_hist_temp(uint32_t t_intervals);

    /**
     * @brief Prints a histogram of moisture.
     * 
     * @param t_intervals Number of intervals for the histogram.
     */
    void print_hist_mstr(uint32_t t_intervals);

public:
    /**
     * @brief Enumeration for specifying print types.
     */
    enum PrintType {
        /// Human-readable format.
        Human,    
        /// Original format.
        Original, 
        /// Bits format.
        Bits      
    };
    
    /**
     * @brief Default constructor.
     */
    Decoder();

    /**
     * @brief Constructor with file path parameter.
     * 
     * @param t_path File path for reading measurements.
     */
    Decoder(const char* t_path);

    /**
     * @brief Destructor.
     */
    ~Decoder();

    /**
     * @brief Reads measurements from a file.
     * 
     * @param t_path File path for reading measurements.
     * @return True if reading is successful, false otherwise.
     */
    bool read_in(const char* t_path);

    /**
     * @brief Writes measurements to a file.
     * 
     * @param t_path File path for writing measurements.
     * @param t_type Type of printing.
     * @return True if writing is successful, false otherwise.
     */
    bool write_to(const char* t_path, PrintType t_type);

    /**
     * @brief Sorts measurements.
     */
    void sort_ms();

    /**
     * @brief Removes duplicate measurements.
     */
    void rm_dups();

    /**
     * @brief Finds extreme measurements.
     * 
     * @return Pointer to a vector containing extreme measurements.
     */
    std::vector<Measurement*>* find_exts();

    /**
     * @brief Gets an extreme measurement of a specific type.
     * 
     * @param t_type Type of payload.
     * @param t_ext Type of extreme.
     * @return Pointer to the extreme measurement.
     */
    Measurement* get_ext(Ms::PayloadType t_type, Ms::Extreme t_ext) const;

    /**
     * @brief Sets an extreme measurement of a specific type.
     * 
     * @param t_type Type of payload.
     * @param t_ext Type of extreme.
     * @param t_new Pointer to the new extreme measurement.
     */
    void set_ext(Ms::PayloadType t_type, Ms::Extreme t_ext, Measurement* t_new);

    /**
     * @brief Gets a measurement by timestamp.
     * 
     * @param t_time Timestamp of the measurement.
     * @return Pointer to the measurement.
     */
    Measurement* get_ms(const char* t_time) const;

    /**
     * @brief Prints a histogram of measurements.
     * 
     * @param t_type Type of payload to be printed.
     * @param t_intervals Number of intervals for the histogram.
     * @return Pointer to a vector containing intervals.
     */
    std::vector<Interval*>* print_hist(Ms::PayloadType t_type, uint32_t t_intervals);

    /**
     * @brief Prints measurements.
     * 
     * @param t_type Type of printing.
     */
    void print_ms(PrintType t_type);
};

#endif//__decoder_h__
