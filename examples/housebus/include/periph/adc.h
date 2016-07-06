#ifndef PERIPH_ADC_H
#define PERIPH_ADC_H

#include <cstdint>


namespace periph {

namespace adc {

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

enum class resolution_t
{
	bit_12	= 0,
	bit_10	= 1,
	bit_8	= 2,
	bit_6	= 3,
};

enum class channel_t
{
	channel
};

enum class trigger_t
{
	disable			= 0,
	rising_edge		= 1,
	falling_edge	= 2,
	both_edges		= 3,
};

enum class event_t
{
	timer1_cc1	= 0,
	timer1_cc2	= 1,
	timer1_cc3	= 2,
	timer2_cc2	= 3,
	timer2_cc3	= 4,
	timer2_cc4	= 5,
	timer2_trgo	= 6,
	timer3_cc1	= 7,
	timer3_trgo	= 8,
	timer4_cc4	= 9,
	timer5_cc1	= 10,
	timer5_cc2	= 11,
	timer5_cc3	= 12,
	exti11		= 15,
};

template<const std::uint8_t index_>
struct channel_tag
{
	static_assert(index_ <= 18, "Channel index out of range");

	static constexpr std::uint8_t index = index_;
};

typedef channel_tag<0> adc_in0;
typedef channel_tag<1> adc_in1;
typedef channel_tag<2> adc_in2;
typedef channel_tag<3> adc_in3;
typedef channel_tag<4> adc_in4;
typedef channel_tag<5> adc_in5;
typedef channel_tag<6> adc_in6;
typedef channel_tag<7> adc_in7;
typedef channel_tag<8> adc_in8;
typedef channel_tag<9> adc_in9;
typedef channel_tag<10> adc_in10;
typedef channel_tag<11> adc_in11;
typedef channel_tag<12> adc_in12;
typedef channel_tag<13> adc_in13;
typedef channel_tag<14> adc_in14;
typedef channel_tag<15> adc_in15;
typedef channel_tag<16> adc_temp;
typedef channel_tag<17> adc_reference;
typedef channel_tag<18> adc_battery;

/**
 * @brief Set alternate in function
 */
template<typename T>
void sequence(const std::uint8_t index = 0, const std::uint32_t value = 0, const std::uint32_t mask = 0)
{
	typedef T config;

	*((volatile uint32_t*)config::base) = config::value | value;
}

template<typename T, typename Tn, typename... Args>
void sequence(const std::uint8_t index = 0, const std::uint32_t value = 0, const std::uint32_t mask = 0)
{
	typedef T config;
	typedef Tn config_next;

	static_assert(config::base == config_next::base, "Elements must have the same register address");
	static_assert(config::index != config_next::index, "Can not set the same pin two times");

	function<Tn, Args...>(index, config::value | value, config::mask | mask);
}

}

}

#endif
