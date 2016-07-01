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
	static_assert(index_ <= 16, "Pin index out of range");

	static constexpr std::uint8_t index = index_;
	static constexpr std::uint32_t base = base_ + 0x20 + ((index & 0x08) >> 1);
	static constexpr std::uint32_t value = std::uint32_t(alternate_) << ((index & 0x7) << 2);
	static constexpr std::uint32_t mask = 0xF << ((index & 0x7) << 2);
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

namespace PA4 {

typedef pin_tag<4, gpioA::base, alternate_t::AF5> spi1_nss;
typedef pin_tag<4, gpioA::base, alternate_t::AF5> i2s1_ws;
typedef pin_tag<4, gpioA::base, alternate_t::AF6> spi3_nss;
typedef pin_tag<4, gpioA::base, alternate_t::AF6> i2s3_ws;
typedef pin_tag<4, gpioA::base, alternate_t::AF7> usart2_ck;

}

namespace PA5 {

typedef pin_tag<5, gpioA::base, alternate_t::AF1> tim2_ch1;
typedef pin_tag<5, gpioA::base, alternate_t::AF1> tim2_etr;
typedef pin_tag<5, gpioA::base, alternate_t::AF5> spi1_sck;
typedef pin_tag<5, gpioA::base, alternate_t::AF5> i2s1_ck;

}

namespace PA6 {

typedef pin_tag<6, gpioA::base, alternate_t::AF1> tim1_bkin;
typedef pin_tag<6, gpioA::base, alternate_t::AF2> tim3_ch1;
typedef pin_tag<6, gpioA::base, alternate_t::AF5> spi1_miso;
typedef pin_tag<6, gpioA::base, alternate_t::AF6> i2s2_mck;
typedef pin_tag<6, gpioA::base, alternate_t::AF12> sdio_cmd;

}

namespace PA7 {

typedef pin_tag<7, gpioA::base, alternate_t::AF1> tim1_ch1n;
typedef pin_tag<7, gpioA::base, alternate_t::AF2> tim3_ch2;
typedef pin_tag<7, gpioA::base, alternate_t::AF5> spi1_mosi;
typedef pin_tag<7, gpioA::base, alternate_t::AF5> i2s1_sd;

}

namespace PA8 {

typedef pin_tag<8, gpioA::base, alternate_t::AF0> mco_1;
typedef pin_tag<8, gpioA::base, alternate_t::AF1> tim1_ch1;
typedef pin_tag<8, gpioA::base, alternate_t::AF4> i2c3_scl;
typedef pin_tag<8, gpioA::base, alternate_t::AF7> usart1_ck;
typedef pin_tag<8, gpioA::base, alternate_t::AF10> usb_fs_sof;
typedef pin_tag<8, gpioA::base, alternate_t::AF12> sdio_d1;

}

namespace PA9 {

typedef pin_tag<9, gpioA::base, alternate_t::AF1> tim1_ch2;
typedef pin_tag<9, gpioA::base, alternate_t::AF4> i2c3_smba;
typedef pin_tag<9, gpioA::base, alternate_t::AF7> usart1_tx;
typedef pin_tag<9, gpioA::base, alternate_t::AF10> usb_fs_vbus;
typedef pin_tag<9, gpioA::base, alternate_t::AF12> sdio_d2;

}

namespace PA10 {

typedef pin_tag<10, gpioA::base, alternate_t::AF1> tim1_ch3;
typedef pin_tag<10, gpioA::base, alternate_t::AF6> spi5_mosi;
typedef pin_tag<10, gpioA::base, alternate_t::AF6> i2s5_sd;
typedef pin_tag<10, gpioA::base, alternate_t::AF7> usart1_rx;
typedef pin_tag<10, gpioA::base, alternate_t::AF10> usb_fs_id;

}

namespace PA11 {

typedef pin_tag<11, gpioA::base, alternate_t::AF1> tim1_ch4;
typedef pin_tag<11, gpioA::base, alternate_t::AF6> spi4_miso;
typedef pin_tag<11, gpioA::base, alternate_t::AF7> usart1_cts;
typedef pin_tag<11, gpioA::base, alternate_t::AF8> usart6_tx;
typedef pin_tag<11, gpioA::base, alternate_t::AF10> usb_fs_dm;

}

namespace PA12 {

typedef pin_tag<12, gpioA::base, alternate_t::AF1> tim1_etr;
typedef pin_tag<12, gpioA::base, alternate_t::AF6> spi5_miso;
typedef pin_tag<12, gpioA::base, alternate_t::AF7> usart1_rts;
typedef pin_tag<12, gpioA::base, alternate_t::AF8> usart6_rx;
typedef pin_tag<12, gpioA::base, alternate_t::AF10> usb_fs_dp;

}

namespace PA13 {

typedef pin_tag<13, gpioA::base, alternate_t::AF0> jtms_swdio;

}

namespace PA14 {

typedef pin_tag<14, gpioA::base, alternate_t::AF0> jtck_swclk;

}

namespace PA15 {

typedef pin_tag<15, gpioA::base, alternate_t::AF0> jtdi;
typedef pin_tag<15, gpioA::base, alternate_t::AF1> tim2_ch1;
typedef pin_tag<15, gpioA::base, alternate_t::AF1> tim2_etr;
typedef pin_tag<15, gpioA::base, alternate_t::AF5> spi1_nss;
typedef pin_tag<15, gpioA::base, alternate_t::AF5> i2s1_ws;
typedef pin_tag<15, gpioA::base, alternate_t::AF6> spi3_nss;
typedef pin_tag<15, gpioA::base, alternate_t::AF6> i2s3_ws;
typedef pin_tag<15, gpioA::base, alternate_t::AF7> usart1_tx;

}

namespace PB0 {

typedef pin_tag<0, gpioB::base, alternate_t::AF1> tim1_ch2n;
typedef pin_tag<0, gpioB::base, alternate_t::AF2> tim3_ch3;
typedef pin_tag<0, gpioB::base, alternate_t::AF6> spi5_sck;
typedef pin_tag<0, gpioB::base, alternate_t::AF6> i2s5_ck;

}

namespace PB1 {

typedef pin_tag<1, gpioB::base, alternate_t::AF1> tim1_ch3n;
typedef pin_tag<1, gpioB::base, alternate_t::AF2> tim3_ch4;
typedef pin_tag<1, gpioB::base, alternate_t::AF6> spi5_nss;
typedef pin_tag<1, gpioB::base, alternate_t::AF6> i2s5_ws;

}

namespace PB3 {

typedef pin_tag<3, gpioB::base, alternate_t::AF0> jtdo_swo;
typedef pin_tag<3, gpioB::base, alternate_t::AF1> tim2_ch2;
typedef pin_tag<3, gpioB::base, alternate_t::AF5> spi1_sck;
typedef pin_tag<3, gpioB::base, alternate_t::AF5> i2s1_ck;
typedef pin_tag<3, gpioB::base, alternate_t::AF6> spi3_sck;
typedef pin_tag<3, gpioB::base, alternate_t::AF6> i2s3_ck;
typedef pin_tag<3, gpioB::base, alternate_t::AF7> usart1_rx;
typedef pin_tag<3, gpioB::base, alternate_t::AF9> i2c2_sda;

}

namespace PB4 {

typedef pin_tag<4, gpioB::base, alternate_t::AF0> jtrst;
typedef pin_tag<4, gpioB::base, alternate_t::AF2> tim3_ch1;
typedef pin_tag<4, gpioB::base, alternate_t::AF5> spi1_miso;
typedef pin_tag<4, gpioB::base, alternate_t::AF6> spi3_miso;
typedef pin_tag<4, gpioB::base, alternate_t::AF7> i2s3ext_sd;
typedef pin_tag<4, gpioB::base, alternate_t::AF9> i2c3_sda;
typedef pin_tag<4, gpioB::base, alternate_t::AF12> sdio_d0;

}

namespace PB5 {

typedef pin_tag<5, gpioB::base, alternate_t::AF2> tim3_ch2;
typedef pin_tag<5, gpioB::base, alternate_t::AF4> i2c1_smba;
typedef pin_tag<5, gpioB::base, alternate_t::AF5> spi1_mosi;
typedef pin_tag<5, gpioB::base, alternate_t::AF5> i2s1_sd;
typedef pin_tag<5, gpioB::base, alternate_t::AF6> spi3_mosi;
typedef pin_tag<5, gpioB::base, alternate_t::AF6> i2s3_sd;
typedef pin_tag<5, gpioB::base, alternate_t::AF12> sdio_d3;

}

namespace PB6 {

typedef pin_tag<6, gpioB::base, alternate_t::AF2> tim4_ch1;
typedef pin_tag<6, gpioB::base, alternate_t::AF4> i2c1_scl;
typedef pin_tag<6, gpioB::base, alternate_t::AF7> usart1_tx;

}

namespace PB7 {

typedef pin_tag<7, gpioB::base, alternate_t::AF2> tim4_ch2;
typedef pin_tag<7, gpioB::base, alternate_t::AF4> i2c1_sda;
typedef pin_tag<7, gpioB::base, alternate_t::AF7> usart1_rx;
typedef pin_tag<7, gpioB::base, alternate_t::AF12> sdio_d0;

}

namespace PB8 {

typedef pin_tag<8, gpioB::base, alternate_t::AF2> tim4_ch3;
typedef pin_tag<8, gpioB::base, alternate_t::AF3> tim10_ch1;
typedef pin_tag<8, gpioB::base, alternate_t::AF4> i2c1_scl;
typedef pin_tag<8, gpioB::base, alternate_t::AF6> spi5_mosi;
typedef pin_tag<8, gpioB::base, alternate_t::AF6> i2s5_sd;
typedef pin_tag<8, gpioB::base, alternate_t::AF9> i2c3_sda;
typedef pin_tag<8, gpioB::base, alternate_t::AF12> sdio_d4;

}

namespace PB9 {

typedef pin_tag<9, gpioB::base, alternate_t::AF2> tim4_ch4;
typedef pin_tag<9, gpioB::base, alternate_t::AF3> tim11_ch1;
typedef pin_tag<9, gpioB::base, alternate_t::AF4> i2c1_sda;
typedef pin_tag<9, gpioB::base, alternate_t::AF5> spi2_nss;
typedef pin_tag<9, gpioB::base, alternate_t::AF5> i2s2_ws;
typedef pin_tag<9, gpioB::base, alternate_t::AF9> i2c2_sda;
typedef pin_tag<9, gpioB::base, alternate_t::AF12> sdio_d5;

}

namespace PB10 {

typedef pin_tag<10, gpioB::base, alternate_t::AF1> tim2_ch3;
typedef pin_tag<10, gpioB::base, alternate_t::AF4> i2c2_scl;
typedef pin_tag<10, gpioB::base, alternate_t::AF5> spi2_sck;
typedef pin_tag<10, gpioB::base, alternate_t::AF5> i2s2_ck;
typedef pin_tag<10, gpioB::base, alternate_t::AF6> i2s3_mck;
typedef pin_tag<10, gpioB::base, alternate_t::AF12> sdio_d7;

}

namespace PB11 {

typedef pin_tag<11, gpioB::base, alternate_t::AF1> tim2_ch4;
typedef pin_tag<11, gpioB::base, alternate_t::AF4> i2c2_sda;
typedef pin_tag<11, gpioB::base, alternate_t::AF5> i2s2_ckin;

}

namespace PB12 {

typedef pin_tag<12, gpioB::base, alternate_t::AF1> tim1_bkin;
typedef pin_tag<12, gpioB::base, alternate_t::AF4> i2c2_smba;
typedef pin_tag<12, gpioB::base, alternate_t::AF5> spi2_nss;
typedef pin_tag<12, gpioB::base, alternate_t::AF5> i2s2_ws;
typedef pin_tag<12, gpioB::base, alternate_t::AF6> spi4_nss;
typedef pin_tag<12, gpioB::base, alternate_t::AF6> i2s4_ws;
typedef pin_tag<12, gpioB::base, alternate_t::AF7> spi3_sck;
typedef pin_tag<12, gpioB::base, alternate_t::AF7> i2s3_ck;

}

namespace PB13 {

typedef pin_tag<13, gpioB::base, alternate_t::AF1> tim1_ch1n;
typedef pin_tag<13, gpioB::base, alternate_t::AF5> spi2_sck;
typedef pin_tag<13, gpioB::base, alternate_t::AF5> i2s2_ck;
typedef pin_tag<13, gpioB::base, alternate_t::AF6> spi4_sck;
typedef pin_tag<13, gpioB::base, alternate_t::AF6> i2s4_ck;

}

namespace PB14 {

typedef pin_tag<14, gpioB::base, alternate_t::AF1> tim1_ch2n;
typedef pin_tag<14, gpioB::base, alternate_t::AF5> spi2_miso;
typedef pin_tag<14, gpioB::base, alternate_t::AF6> i2s2ext_sd;
typedef pin_tag<14, gpioB::base, alternate_t::AF12> sdio_d6;

}

namespace PB15 {

typedef pin_tag<15, gpioB::base, alternate_t::AF0> rtc_50hz;
typedef pin_tag<15, gpioB::base, alternate_t::AF1> tim1_ch3n;
typedef pin_tag<15, gpioB::base, alternate_t::AF5> spi2_mosi;
typedef pin_tag<15, gpioB::base, alternate_t::AF5> i2s2_sd;
typedef pin_tag<15, gpioB::base, alternate_t::AF12> sdio_ck;

}

namespace PC2 {

typedef pin_tag<2, gpioC::base, alternate_t::AF5> spi2_miso;
typedef pin_tag<2, gpioC::base, alternate_t::AF6> i2s2ext_sd;

}

namespace PC3 {

typedef pin_tag<3, gpioC::base, alternate_t::AF5> spi2_mosi;
typedef pin_tag<3, gpioC::base, alternate_t::AF5> i2s2_sd;

}

namespace PC6 {

typedef pin_tag<6, gpioC::base, alternate_t::AF2> tim3_ch1;
typedef pin_tag<6, gpioC::base, alternate_t::AF5> i2s2_mck;
typedef pin_tag<6, gpioC::base, alternate_t::AF8> usart6_tx;
typedef pin_tag<6, gpioC::base, alternate_t::AF12> sdio_d6;

}

namespace PC7 {

typedef pin_tag<7, gpioC::base, alternate_t::AF2> tim3_ch2;
typedef pin_tag<7, gpioC::base, alternate_t::AF5> spi2_sck;
typedef pin_tag<7, gpioC::base, alternate_t::AF5> i2s2_ck;
typedef pin_tag<7, gpioC::base, alternate_t::AF6> i2s3_mck;
typedef pin_tag<7, gpioC::base, alternate_t::AF8> usart6_rx;
typedef pin_tag<7, gpioC::base, alternate_t::AF12> sdio_d7;

}

namespace PC8 {

typedef pin_tag<8, gpioC::base, alternate_t::AF2> tim3_ch3;
typedef pin_tag<8, gpioC::base, alternate_t::AF8> usart6_ck;
typedef pin_tag<8, gpioC::base, alternate_t::AF12> sdio_d0;

}

namespace PC9 {

typedef pin_tag<9, gpioC::base, alternate_t::AF0> mco_2;
typedef pin_tag<9, gpioC::base, alternate_t::AF2> tim3_ch4;
typedef pin_tag<9, gpioC::base, alternate_t::AF4> i2c3_sda;
typedef pin_tag<9, gpioC::base, alternate_t::AF5> i2s2_ckin;
typedef pin_tag<9, gpioC::base, alternate_t::AF12> sdio_d1;

}

namespace PC10 {

typedef pin_tag<10, gpioC::base, alternate_t::AF6> spi3_sck;
typedef pin_tag<10, gpioC::base, alternate_t::AF6> i2s3_ck;
typedef pin_tag<10, gpioC::base, alternate_t::AF12> sdio_d2;

}

namespace PC11 {

typedef pin_tag<11, gpioC::base, alternate_t::AF5> i2s3ext_sd;
typedef pin_tag<11, gpioC::base, alternate_t::AF6> spi3_miso;
typedef pin_tag<11, gpioC::base, alternate_t::AF12> sdio_d3;

}

namespace PC12 {

typedef pin_tag<12, gpioC::base, alternate_t::AF6> spi3_mosi;
typedef pin_tag<12, gpioC::base, alternate_t::AF6> i2s3_sd;
typedef pin_tag<12, gpioC::base, alternate_t::AF12> sdio_ck;

}

namespace PD2 {

typedef pin_tag<2, gpioD::base, alternate_t::AF2> tim3_etr;
typedef pin_tag<2, gpioD::base, alternate_t::AF12> sdio_cmd;

}

namespace PD3 {

typedef pin_tag<3, gpioD::base, alternate_t::AF5> spi2_sck;
typedef pin_tag<3, gpioD::base, alternate_t::AF5> i2s2_ck;
typedef pin_tag<3, gpioD::base, alternate_t::AF7> usart2_cts;

}

namespace PD4 {

typedef pin_tag<4, gpioD::base, alternate_t::AF7> usart2_rts;

}

namespace PD5 {

typedef pin_tag<5, gpioD::base, alternate_t::AF7> usart2_tx;

}

namespace PD6 {

typedef pin_tag<6, gpioD::base, alternate_t::AF5> spi3_mosi;
typedef pin_tag<6, gpioD::base, alternate_t::AF5> i2s3_sd;
typedef pin_tag<6, gpioD::base, alternate_t::AF7> usart2_rx;

}

namespace PD7 {

typedef pin_tag<7, gpioD::base, alternate_t::AF7> usart2_ck;

}

namespace PD12 {

typedef pin_tag<12, gpioD::base, alternate_t::AF2> tim4_ch1;

}

namespace PD13 {

typedef pin_tag<13, gpioD::base, alternate_t::AF2> tim4_ch2;

}

namespace PD14 {

typedef pin_tag<14, gpioD::base, alternate_t::AF2> tim4_ch3;

}

namespace PD15 {

typedef pin_tag<15, gpioD::base, alternate_t::AF2> tim4_ch4;

}

namespace PE0 {

typedef pin_tag<0, gpioE::base, alternate_t::AF2> tim4_etr;

}

namespace PE2 {

typedef pin_tag<2, gpioE::base, alternate_t::AF0> traceclk;
typedef pin_tag<2, gpioE::base, alternate_t::AF5> spi4_sck;
typedef pin_tag<2, gpioE::base, alternate_t::AF5> i2s4_ck;
typedef pin_tag<2, gpioE::base, alternate_t::AF6> spi5_sck;
typedef pin_tag<2, gpioE::base, alternate_t::AF6> i2s5_ck;

}

namespace PE3 {

typedef pin_tag<3, gpioE::base, alternate_t::AF0> traced0;

}

namespace PE4 {

typedef pin_tag<4, gpioE::base, alternate_t::AF0> traced1;
typedef pin_tag<4, gpioE::base, alternate_t::AF5> spi4_nss;
typedef pin_tag<4, gpioE::base, alternate_t::AF5> i2s4_ws;
typedef pin_tag<4, gpioE::base, alternate_t::AF6> spi5_nss;
typedef pin_tag<4, gpioE::base, alternate_t::AF6> i2s5_ws;

}

namespace PE5 {

typedef pin_tag<5, gpioE::base, alternate_t::AF0> traced2;
typedef pin_tag<5, gpioE::base, alternate_t::AF3> tim9_ch1;
typedef pin_tag<5, gpioE::base, alternate_t::AF5> spi4_miso;
typedef pin_tag<5, gpioE::base, alternate_t::AF6> spi5_miso;

}

namespace PE6 {

typedef pin_tag<6, gpioE::base, alternate_t::AF0> traced3;
typedef pin_tag<6, gpioE::base, alternate_t::AF3> tim9_ch2;
typedef pin_tag<6, gpioE::base, alternate_t::AF5> spi4_mosi;
typedef pin_tag<6, gpioE::base, alternate_t::AF5> i2s4_sd;
typedef pin_tag<6, gpioE::base, alternate_t::AF6> spi5_mosi;
typedef pin_tag<6, gpioE::base, alternate_t::AF6> i2s5_sd;

}

namespace PE7 {

typedef pin_tag<7, gpioE::base, alternate_t::AF1> tim1_etr;

}

namespace PE8 {

typedef pin_tag<8, gpioE::base, alternate_t::AF1> tim1_ch1n;

}

namespace PE9 {

typedef pin_tag<9, gpioE::base, alternate_t::AF1> tim1_ch1;

}

namespace PE10 {

typedef pin_tag<10, gpioE::base, alternate_t::AF1> tim1_ch2n;

}

namespace PE11 {

typedef pin_tag<11, gpioE::base, alternate_t::AF1> tim1_ch2;
typedef pin_tag<11, gpioE::base, alternate_t::AF5> spi4_nss;
typedef pin_tag<11, gpioE::base, alternate_t::AF5> i2s4_ws;
typedef pin_tag<11, gpioE::base, alternate_t::AF6> spi5_nss;
typedef pin_tag<11, gpioE::base, alternate_t::AF6> i2s5_ws;

}

namespace PE12 {

typedef pin_tag<12, gpioE::base, alternate_t::AF1> tim1_ch3n;
typedef pin_tag<12, gpioE::base, alternate_t::AF5> spi4_sck;
typedef pin_tag<12, gpioE::base, alternate_t::AF5> i2s4_ck;
typedef pin_tag<12, gpioE::base, alternate_t::AF6> spi5_sck;
typedef pin_tag<12, gpioE::base, alternate_t::AF6> i2s5_ck;

}

namespace PE13 {

typedef pin_tag<13, gpioE::base, alternate_t::AF1> tim1_ch3;
typedef pin_tag<13, gpioE::base, alternate_t::AF5> spi4_miso;
typedef pin_tag<13, gpioE::base, alternate_t::AF6> spi5_miso;

}

namespace PE14 {

typedef pin_tag<14, gpioE::base, alternate_t::AF1> tim1_ch4;
typedef pin_tag<14, gpioE::base, alternate_t::AF5> spi4_mosi;
typedef pin_tag<14, gpioE::base, alternate_t::AF5> i2s4_sd;
typedef pin_tag<14, gpioE::base, alternate_t::AF6> spi5_mosi;
typedef pin_tag<14, gpioE::base, alternate_t::AF6> i2s5_sd;

}

namespace PE15 {

typedef pin_tag<15, gpioE::base, alternate_t::AF1> tim1_bkin;

}

/**
 * @brief Set alternate in function
 */
template<typename T>
void function(const std::uint32_t value = 0, const std::uint32_t mask = 0)
{
	typedef T config;

	*((uint32_t*)config::base) = (*((uint32_t*)config::base) & ~(config::mask | mask)) | config::value | value;
}

template<typename T, typename Tn, typename... Args>
void function(const std::uint32_t value = 0, const std::uint32_t mask = 0)
{
	typedef T config;
	typedef Tn config_next;

	static_assert(config::base == config_next::base, "Elements must have the same register address");

	function<Tn, Args...>(config::value | value, config::mask | mask);
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
