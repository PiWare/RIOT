#ifndef DRIVER_LED_RGB_H
#define DRIVER_LED_RGB_H

#include <interface/gpio.h>
#include <interface/pwm.h>


namespace driver { namespace led {

template<typename T>
class rgb
{
	public:
		enum class color:
			std::uint32_t
		{
			none		= 0x000000,
			red			= 0x0000FF,
			green		= 0x00FF00,
			blue		= 0xFF0000,
			yellow		= 0x00FFFF,
			cyan		= 0xFFFF00,
			mangenta	= 0xFF00FF,
			white		= 0xFFFFFF,
		};

	private:
		T &m_red, &m_green, &m_blue;

	public:
		rgb(T &red, T &green, T &blue):
			m_red(red),
			m_green(green),
			m_blue(blue)
		{
			set(0);
		}

		void set(const std::uint32_t value)
		{
			m_red.set(value & 0xFF);
			m_green.set(value & 0xFF00 >> 8);
			m_blue.set(value & 0xFF0000 >> 16);
		}

		void set(const color col)
		{
			set(std::uint32_t(col));
		}
};

typedef rgb<interface::gpio> rgp_gpio;
typedef rgb<interface::pwm> rgp_pwm;

} }

#endif
