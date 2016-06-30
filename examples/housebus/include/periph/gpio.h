#ifndef PERIPH_GPIO_H
#define PERIPH_GPIO_H

#include <interface/gpio.h>

#include <periph/periph.h>


namespace periph { namespace gpio {

enum class mode_t
{
	input	= 0x0,
	output	= 0x1,
	alternate	= 0x2,
	analog	= 0x3,
};

enum class speed_t
{
	low		= 0x0,
	medium	= 0x1,
	fast	= 0x2,
	high	= 0x3,
};

enum class pull_t
{
	none	= 0x0,
	up		= 0x1,
	down	= 0x2,
};

enum class alternate_t
{
	AF0		= 0x0,
	AF1		= 0x1,
	AF2		= 0x2,
	AF3		= 0x3,
	AF4		= 0x4,
	AF5		= 0x5,
	AF6		= 0x6,
	AF7		= 0x7,
	AF8		= 0x8,
	AF9		= 0x9,
	AF10	= 0xa,
	AF11	= 0xb,
	AF12	= 0xc,
	AF13	= 0xd,
	AF14	= 0xe,
	AF15	= 0xf,
};

template<const std::uint8_t index_, const std::uint32_t base_, const alternate_t alternate_>
struct pin_tag
{
	static constexpr std::uint8_t index = index_;
	static constexpr std::uint32_t base = base_ + 0x20 + ((index & 0x08) >> 1);
	static constexpr std::uint32_t value = std::uint32_t(alternate_);
};

namespace PA0 {

typedef pin_tag<0, gpioA::base, alternate_t::AF1> tim2_ch1;
typedef pin_tag<0, gpioA::base, alternate_t::AF1> tim2_etr;
typedef pin_tag<0, gpioA::base, alternate_t::AF2> tim5_ch1;
typedef pin_tag<0, gpioA::base, alternate_t::AF7> usart2_cts;

}

namespace PA1 {

typedef pin_tag<1, gpioA::base, alternate_t::AF1> tim2_ch2;
typedef pin_tag<1, gpioA::base, alternate_t::AF2> tim5_ch2;
typedef pin_tag<1, gpioA::base, alternate_t::AF5> spi4_mosi;
typedef pin_tag<1, gpioA::base, alternate_t::AF5> i2s4_sd;
typedef pin_tag<1, gpioA::base, alternate_t::AF7> usart2_rts;

}

namespace PA2 {

typedef pin_tag<2, gpioA::base, alternate_t::AF1> tim2_ch3;
typedef pin_tag<2, gpioA::base, alternate_t::AF2> tim5_ch3;
typedef pin_tag<2, gpioA::base, alternate_t::AF3> tim9_ch1;
typedef pin_tag<2, gpioA::base, alternate_t::AF5> i2s2_ckin;
typedef pin_tag<2, gpioA::base, alternate_t::AF7> usart2_tx;

}

namespace PA3 {

typedef pin_tag<3, gpioA::base, alternate_t::AF1> tim2_ch4;
typedef pin_tag<3, gpioA::base, alternate_t::AF2> tim5_ch4;
typedef pin_tag<3, gpioA::base, alternate_t::AF3> tim9_ch2;
typedef pin_tag<3, gpioA::base, alternate_t::AF5> i2s2_mck;
typedef pin_tag<3, gpioA::base, alternate_t::AF7> usart2_rx;

}

template<typename T>
void set()
{
	typedef T config;

	/* TODO: Mask */
	*((uint32_t*)config::base) = config::value;
}

/*
class gpio:
	public interface::gpio
{
	public:
		gpio();

		virtual void set(void)
		{

		}

		virtual void clear(void)
		{

		}
};
*/
} }

#endif
