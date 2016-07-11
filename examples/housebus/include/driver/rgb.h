#ifndef DRIVER_LED_RGB_H
#define DRIVER_LED_RGB_H

#include <type/color.h>

#include <interface/gpio.h>
#include <interface/pwm.h>


namespace driver { namespace led {

struct linear
{
	int operator()(const int value) const
	{
		return value;
	}

//	std::uint8_t operator()(const std::uint8_t value) const { return value; }
};

struct logarithmic
{
	int operator()(const int value) const
	{
		return (value * value) >> 8;
	}

//	std::uint8_t operator()(const std::uint8_t value) const { return (value * value) >> 8; }
};

template<typename T, typename func = linear>
class rgb
{
	private:
		T &m_red, &m_green, &m_blue;
		func m_function;

	public:
		rgb(T &red, T &green, T &blue):
			m_red(red),
			m_green(green),
			m_blue(blue)
		{
		}

		void set(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue)
		{
			m_red.set(m_function(red));
			m_green.set(m_function(green));
			m_blue.set(m_function(blue));
		}

		void set(const std::uint32_t value)
		{
			set(value & 0xFF, (value & 0xFF00) >> 8, (value & 0xFF0000) >> 16);
		}

		void set(const type::color color)
		{
			set(std::uint32_t(color));
		}
};

typedef rgb<interface::gpio> rgp_gpio;
typedef rgb<interface::pwm> rgp_pwm;

} }

#endif
