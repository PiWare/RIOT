#ifndef DRIVER_SPI_PCD8544_H
#define DRIVER_SPI_PCD8544_H

#include <interface/spi.h>
#include <interface/gpio.h>
#include <interface/display.h>


namespace driver { namespace spi {

class pcd8544:
	public interface::display	// <monochrome>
{
	protected:
		static const std::uint8_t FUNCTION				= 0x20;

		/* H = 0 */
		static const std::uint8_t DISPLAY_CONTROL		= 0x08;	/*!< Set display configuration */
		static const std::uint8_t SET_Y_ADDRESS			= 0x40;	/*!< Set Y address of RAM */
		static const std::uint8_t SET_X_ADDRESS			= 0x80;	/*!< Set X address of RAM */

		/* H = 1 */
		static const std::uint8_t TEMPERATURE_CONTROL	= 0x04;	/*!< Set Temperature Coefficient (TCx) */
		static const std::uint8_t BIAS_SYSTEM			= 0x10;	/*!< Set Bias System (BSx) */
		static const std::uint8_t SET_VOP				= 0x80;	/*!< Write Vop to register */

		interface::spi &m_spi;
		interface::gpio &m_reset;
		interface::gpio &m_data_command;

		bool m_power;

	public:
		pcd8544(interface::spi &spi, interface::gpio &reset, interface::gpio &data_command):
			m_spi(spi),
			m_reset(reset),
			m_data_command(data_command),

			m_power(false)
		{

		}

		virtual void set(const bool value)
		{

		}

		virtual bool get(void) const
		{
			return m_power;
		}

		virtual void draw(const bool value)
		{

		}
};

} }

#endif
