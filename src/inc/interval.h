#ifndef __interval_h__
#define __interval_h__

#include "precomp.h"
#include "measurement.h"

/**
 * @brief Represents an interval for temperature or moisture measurements.
 */
class Interval {
    uint32_t m_freq; /** The frequency of measurements within the interval. */

    float m_lwr_range_fl; /** The lower bound of the possible range (float). */
    float m_upr_range_fl; /** The upper bound of the possible range (float). */

    Measurement* m_lwr_bound; /** Pointer to the lower bound measurement. */
    Measurement* m_upr_bound; /** Pointer to the upper bound measurement. */

    Ms::PayloadType m_type; /** The type of payload associated with the interval. */

public:
    /**
     * @brief Constructs an Interval object with the specified type and range.
     *
     * @param t_type The type of payload associated with the interval.
     * @param t_lwr The lower bound of the range.
     * @param t_upr The upper bound of the range.
     */
    Interval(Ms::PayloadType t_type, float t_lwr, float t_upr);

    /**
     * @brief Destructor to clean up resources.
     */
    ~Interval();

    /**
     * @brief Sets the measurement for the specified extreme of the interval.
     *
     * @param t_ext The extreme (lower or upper) for which to set the measurement.
     * @param t_ms Pointer to the measurement to set.
     * @return bool True if the measurement was successfully set, false otherwise.
     */
    bool set_ms(Ms::Extreme t_ext, Measurement* t_ms);

    /**
     * @brief Sets the frequency of measurements within the interval.
     *
     * @param t_n The frequency value to set.
     */
    void set_freq(uint32_t t_n);

    /**
     * @brief Increments the frequency of measurements within the interval.
     */
    void inc_freq();

    /**
     * @brief Gets the measurement for the specified extreme of the interval.
     *
     * @param t_ext The extreme (lower or upper) for which to get the measurement.
     * @return Measurement* Pointer to the measurement.
     */
    Measurement* get_ms(Ms::Extreme t_ext) const;

    /**
     * @brief Gets the range of the interval for the specified extreme.
     *
     * @param t_ext The extreme (lower or upper) for which to get the range.
     * @return float The range value.
     */
    float get_range_fl(Ms::Extreme t_ext) const;

    /**
     * @brief Gets the frequency of measurements within the interval.
     *
     * @return uint32_t The frequency value.
     */
    uint32_t get_freq() const;
};

#endif//__interval_h__
