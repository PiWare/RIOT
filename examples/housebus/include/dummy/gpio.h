#ifndef DUMMY_GPIO_H
#define DUMMY_GPIO_H

#include <interface/gpio.h>

#include <periph/periph.h>


namespace dummy { namespace gpio {

class gpio:
	public interface::gpio
{
	private:
		const std::uint8_t m_index;
		bool m_value;

	public:
		gpio(const std::uint8_t index):
			m_index(index),
			m_value(false)
		{

		}

		virtual void set(const bool value)
		{
			m_value = value;
		}

		virtual bool get() const
		{
			return m_value;
		}
};

} }

#endif
