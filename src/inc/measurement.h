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

namespace Ms {
    enum Extreme {
        Min,
        Max,
    };

    enum PayloadType {
        Temperature,
        Moisture,
    };
}

/**
 * @brief Represents a measurement consisting of time and payload data.
 *
 * The time and payload data are stored in a compact binary format.
 * The time format consists of 5 bytes representing year, month, day, hour, minute, and second.
 * The payload format also consists of 5 bytes.
 */
class Measurement {
    uint8_t m_time[5]; /**< Binary representation of time data (year, month, day, hour, minute, second). */
    uint8_t m_payload[5]; /**< Binary representation of payload data. */

public:
    /**
     * @brief Default constructor.
     */
    Measurement();

    /**
     * @brief Constructor that initializes the measurement with time and payload data.
     *
     * @param t_time The time data in string format.
     * @param t_payload The payload data in string format.
     */
    Measurement(const std::string& t_time, const std::string& t_payload);

    /**
     * @brief Destructor to clean up resources.
     */
    ~Measurement();

    /**
     * @brief Get the time data as a compact binary representation for comparison.
     *
     * @return uint64_t The time data as a 64-bit unsigned integer.
     */
    uint64_t get_time_cmp() const;

    /**
     * @brief Get the payload data as a compact binary representation for comparison.
     *
     * @return uint64_t The payload data as a 64-bit unsigned integer.
     */
    uint64_t get_payload_cmp() const;

    /**
     * @brief Get the time data as an array of 5 bytes.
     *
     * @return const uint8_t* Pointer to the time data array.
     */
    const uint8_t* get_time_arr() const;

    /**
     * @brief Get the payload data as an array of 5 bytes.
     *
     * @return const uint8_t* Pointer to the payload data array.
     */
    const uint8_t* get_payload_arr() const;

    /**
     * @brief Get the original formatted string representation of the measurement.
     *
     * @return std::string The original formatted string.
     */
    std::string get_og_fmt();

    /**
     * @brief Get the formatted payload data as a string.
     *
     * @return std::string The formatted payload data.
     */
    std::string get_fmtd_pl();

    /**
     * @brief Get the formatted time data as a string.
     *
     * @return std::string The formatted time data.
     */
    std::string get_fmtd_tm();

    /**
     * @brief Get the voltage value from the payload data.
     *
     * @return uint16_t The voltage value.
     */
    uint16_t get_pl_vltg();

    /**
     * @brief Get the temperature value from the payload data.
     *
     * @return float The temperature value.
     */
    float get_pl_temp();

    /**
     * @brief Get the moisture value from the payload data.
     *
     * @return float The moisture value.
     */
    float get_pl_mstr();

    /**
     * @brief Print the original formatted string representation of the measurement.
     */
    void print_og();
};

#endif//__measuerement_h__
