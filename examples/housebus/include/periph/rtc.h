#ifndef PERIPH_RTC_H
#define PERIPH_RTC_H

#include <cstdint>


namespace periph {

class rtc
{
	private:
		static const std::uint32_t TR			= 0x00;	/*!< Time register */
		static const std::uint32_t DR			= 0x04;	/*!< Date register */
		static const std::uint32_t CR			= 0x;	/*!< Control register */
		static const std::uint32_t ISR			= 0x;	/*!< Initialization and status register */
		static const std::uint32_t PRER			= 0x;	/*!< Prescaler register */
		static const std::uint32_t WUTR			= 0x;	/*!< Wakeup timer register */
		static const std::uint32_t CALIBR		= 0x;	/*!< Calibration register */
		static const std::uint32_t ALARMAR		= 0x;	/*!< Alarm A register */
		static const std::uint32_t ALARMBR		= 0x;	/*!< Alarm B register */
		static const std::uint32_t WPR			= 0x;	/*!< Write protection register */
		static const std::uint32_t SSR			= 0x;	/*!< Sub second register */
		static const std::uint32_t SHFITR		= 0x;	/*!< Shift control register */
		static const std::uint32_t TSTR			= 0x;	/*!< Timestamp time register */
		static const std::uint32_t TSDR			= 0x;	/*!< Timestamp date register */
		static const std::uint32_t TSSSR		= 0x;	/*!< Timestamp sub second register */
		static const std::uint32_t CALR			= 0x;	/*!< Calibration register */
		static const std::uint32_t TAFCR		= 0x;	/*!< Tamper and alternate function configuration register */
		static const std::uint32_t ALARMASSR	= 0x;	/*!< Alarm A sub second register */
		static const std::uint32_t ALARMBSSR	= 0x;	/*!< Alarm B sub second register */
		static const std::uint32_t BKPR			= 0x50;	/*!< Backup registers 0x50..0x9C */

		enum class reg
		{
			SR		= 0x00,
			CR1		= 0x04,
			CR2		= 0x08,
			SMPR1	= 0x0C,
			SMPR2	= 0x10,
			JOFR1	= 0x14,
			JOFR2	= 0x18,
			JOFR3	= 0x1C,
			JOFR4	= 0x20,
			HTR		= 0x24,
			LTR		= 0x28,
			SQR1	= 0x2C,
			SQR2	= 0x30,
			SQR3	= 0x34,
			JSQR	= 0x38,
			JDR1	= 0x3C,
			JDR2	= 0x40,
			JDR3	= 0x44,
			JDR4	= 0x48,
			DR		= 0x4C,
			CCR		= 0x04,	/*!< ??? */
		};

	public:
		rtc() {}

};

}

#endif
