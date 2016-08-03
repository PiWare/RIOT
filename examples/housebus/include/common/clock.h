#ifndef COMMON_CLOCK_H
#define COMMON_CLOCK_H

#include <type/class.h>


namespace common { namespace clock {

enum class bus_t
{
	cpu,
	sysclk,
	rtc,
	watchdog,
	i2s,
	usb,
	apb,
	ahb,
	output,
};

template<typename T, bus_t bus_, unsigned int index_, unsigned int divider_ = 1, unsigned long int frequency = -1>
struct tag
{
	static_assert(T::tag_class == type::class_t::oscillator, "No oscillator::tag");
	static_assert((frequency == -1) || ((T::frequency / divider_) == frequency), "Frequency mismatch");

	static constexpr type::class_t tag_class = type::class_t::clock;
	static constexpr unsigned long int frequency = T::frequency;
	static constexpr bus_t bus = bus_;
	static constexpr unsigned int index = index_;
	static constexpr unsigned int divider = divider_;
};

/**
 * @brief Spezialisation for IWDGCLK
 */
template<typename T, bus_t bus_, unsigned int index_, unsigned int divider_ = 1, unsigned long int frequency = -1>
struct tag<bus_t::watchdog>
{
	static_assert(T::tag_class == type::class_t::oscillator, "No oscillator::tag");
	static_assert((frequency == -1) || ((T::frequency / divider_) == frequency), "Frequency mismatch");

	static constexpr type::class_t tag_class = type::class_t::clock;
	static constexpr unsigned long int frequency = T::frequency;
	static constexpr bus_t bus = bus_;
	static constexpr unsigned int index = index_;
	static constexpr unsigned int divider = divider_;
};

/**
 * @brief Spezialisation for RTCCLK
 */
template<typename T, bus_t bus_, unsigned int index_, unsigned int divider_ = 1, unsigned long int frequency = -1>
struct tag<bus_t::rtc>
{
	static_assert(T::tag_class == type::class_t::oscillator, "No oscillator::tag");
	static_assert((frequency == -1) || ((T::frequency / divider_) == frequency), "Frequency mismatch");

	static constexpr type::class_t tag_class = type::class_t::clock;
	static constexpr unsigned long int frequency = T::frequency;
	static constexpr bus_t bus = bus_;
	static constexpr unsigned int index = index_;
	static constexpr unsigned int divider = divider_;
};

} }

#endif
