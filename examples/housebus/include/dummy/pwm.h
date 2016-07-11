#ifndef PERIPH_PWM_H
#define PERIPH_PWM_H

#include <cstdint>

#include <interface/pwm.h>


namespace periph { namespace pwm {

template<typename T>
class control
{
	private:
		typedef T config;

		class channel:
			public interface::pwm::channel
		{
			protected:
			public:
				channel() {}
		};

	protected:
		static const std::uint8_t CR1	= 0x00;
		static const std::uint8_t CR2	= 0x04;
		static const std::uint8_t SMCR	= 0x08;
		static const std::uint8_t DIER	= 0x0C;
		static const std::uint8_t SR	= 0x10;
		static const std::uint8_t EGR	= 0x14;
		static const std::uint8_t 	= 0x;	/*!<  */
		static const std::uint8_t 	= 0x;	/*!<  */
		static const std::uint8_t CCER	= 0x20;	/*!< Capture/compare enable register */
		static const std::uint8_t 	= 0x;	/*!<  */
		static const std::uint8_t 	= 0x;	/*!<  */

		static const std::uint8_t CNT	= 0x24;	/*!< Counter */
		static const std::uint8_t PSC	= 0x28;	/*!< Prescaler */
		static const std::uint8_t ARR	= 0x2C;	/*!< Auto-reload register */
		static const std::uint8_t RCR	= 0x30;	/*!< Repetition counter register */
		static const std::uint8_t CCR1	= 0x34;	/*!< Capture/compare register 1 */
		static const std::uint8_t CCR2	= 0x38;	/*!< Capture/compare register 2 */
		static const std::uint8_t CCR3	= 0x3C;	/*!< Capture/compare register 3 */
		static const std::uint8_t CCR4	= 0x40;	/*!< Capture/compare register 4 */
		static const std::uint8_t BDTR	= 0x44;	/*!< Break and dead-time register */
		static const std::uint8_t DCR	= 0x48;	/*!< DMA control register */
		static const std::uint8_t DMAR	= 0x4C;	/*!< DMA address for full transfer */


		channel m_channel[4];

	public:
		control()
		{

		}

		interface::pwm::channel channel(const size_t index)
		{
			return m_channel[index];
		}
};

} }

#endif
