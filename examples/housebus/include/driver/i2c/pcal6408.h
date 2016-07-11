#ifndef DRIVER_I2C_PCAL6408_H
#define DRIVER_I2C_PCAL6408_H

#include <interface/i2c.h>
#include <interface/gpio.h>


namespace driver { namespace i2c {

class pcal6408
{
	protected:
		class gpio:
			public interface::gpio
		{
			protected:
				pcal6408 &m_owner;
				const std::uint8_t m_index;

			public:
				gpio(pcal6408 &owner, const std::uint8_t index):
					m_owner(owner),
					m_index(index)
				{

				}

				virtual void direction(const type::direction value)
				{

				}

				virtual type::direction direction() const
				{
					return type::direction::output;
				}

				virtual void set(const bool value)
				{
					m_owner.set(1 << m_index);
				}

				virtual bool get(void) const
				{
					return m_owner.get() & (1 << m_index);
				}
		};

		static const std::uint8_t INPUT_PORT				= 0x00;
		static const std::uint8_t OUTPUT_PORT				= 0x01;
		static const std::uint8_t POLARITY_INVERSION		= 0x02;
		static const std::uint8_t CONFIGURATION				= 0x03;
		static const std::uint8_t OUTPUT_DRIVER_STRENGH_0	= 0x40;
		static const std::uint8_t OUTPUT_DRIVER_STRENGH_1	= 0x41;
		static const std::uint8_t INPUT_LATCH				= 0x42;
		static const std::uint8_t PULL_UPDOWN_ENABLE		= 0x43;
		static const std::uint8_t PULL_UPDOWN_SELECTION		= 0x44;
		static const std::uint8_t INTERRUPT_MASK			= 0x45;
		static const std::uint8_t INTERRUPT_STATUS			= 0x46;
		static const std::uint8_t OUTPUT_PORT_CONFIGURATION	= 0x4F;

		interface::i2c &m_i2c;
		const std::uint8_t m_address;
		gpio m_gpio[8];

		std::uint8_t m_output;

	public:
		pcal6408(interface::i2c &i2c, const std::uint8_t address = 0x20):
			m_i2c(i2c),
			m_address(address),
			m_gpio
			{
				{ *this, 0 },
				{ *this, 1 },
				{ *this, 2 },
				{ *this, 3 },
				{ *this, 4 },
				{ *this, 5 },
				{ *this, 6 },
				{ *this, 7 },
			},
			m_output(0)
		{

		}

		interface::gpio &get(const size_t index)
		{
			return m_gpio[index];
		}

		void set(const std::uint8_t bit)
		{
			m_output |= (1 << bit);
			std::uint8_t buffer[2] = { OUTPUT_PORT, m_output };

			m_i2c.write(m_address, buffer, sizeof(buffer));
		}

		std::uint8_t get() const
		{
			std::uint8_t buffer;

			m_i2c.write(m_address, &INPUT_PORT, 1);
			m_i2c.read(m_address, &buffer, 1);
			return buffer;
		}
};

} }

#endif
