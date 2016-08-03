#ifndef COMMON_OSCILLATOR_H
#define COMMON_OSCILLATOR_H

#include <type/class.h>


namespace common { namespace oscillator {

/**
 * @brief Oscillator type
 */
enum class source_t
{
	internal,	/*!< Internal oscillator */
	external,	/*!< External clock */
	rc,			/*!< External RC oscillator */
	oszillator,	/*!< External quarz oscillator */
};

/**
 * @brief Tag for oscillator configuration
 */
template<source_t source_, unsigned long int frequency_>
struct tag
{
	static constexpr type::class_t tag_class = type::class_t::oscillator;

	static constexpr source_t source = source_;
	static constexpr unsigned long int frequency = frequency_;
};

} }

#endif
