#ifndef PERIPH_USART_H
#define PERIPH_USART_H

#include <periph/periph.h>


namespace periph {

namespace usart {

enum class data_t
{
	data_8,
	data_9,
};

enum class lin_t
{
	disable		= 0,	/*!< LIN mode disabled */
	enable		= 1,	/*!< LIN mode enabled */
};

enum class stop_t
{
	half		= 1,	/*!< 0.5 stop bit */
	one			= 0,	/*!< 1 stop bit */
	one_half	= 3,	/*!< 1.5 stop bit */
	two			= 2,	/*!< 2 stop bits */
};

enum class clock_t
{
	disable		= 0,	/*!< SCLK pin disabled */
	enable		= 1,	/*!< SCLK pin enabled */
};

enum class clock_polarity_t
{
	low			= 0,	/*!< Steady low value on SCLK pin outside transmission window */
	high		= 1,	/*!< Steady high value on SCLK pin outside transmission window */
};

enum class clock_phase_t
{
	first		= 0,	/*!< The first clock transition is the first data capture edge */
	second		= 1,	/*!< The second clock transition is the first data capture edge */
};

}

template<typename T>
class uart
{
	private:
		typedef T config;

		static const std::uint32_t SR	= 0x00;	/*!< Status register */
		static const std::uint32_t DR	= 0x04;	/*!< Data register */
		static const std::uint32_t BRR	= 0x08;	/*!< Baud rate register */
		static const std::uint32_t CR1	= 0x0C;	/*!< Control register 1 */
		static const std::uint32_t CR2	= 0x10;	/*!< Control register 2 */
		static const std::uint32_t CR3	= 0x14;	/*!< Control register 3 */
		static const std::uint32_t GTPR	= 0x18;	/*!< Guard time and prescaler register */

	public:
		uart()
		{
			static_assert(config::periph_class == class_t::usart, "Tag must be of class USART");

		}

		void baudrate(const std::uint32_t value)
		{
			const float divider = float(config::CLOCK) / value / 16;
			const unsigned int mantissa = divider;
			const unsigned int fraction = (divider - mantissa) * 16 + 0.5;

			*(volatile std::uint32_t *)(config::base + BRR) = mantissa << 4 | fraction;
		}
};

}

#endif
