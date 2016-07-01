#ifndef PERIPH_PERIPH_H
#define PERIPH_PERIPH_H

#include <cstdint>


namespace periph {

enum class bus_t
{
	ahb1	= 0x00,
	ahb2	= 0x04,
	apb1	= 0x10,
	apb2	= 0x14,
};

template<const std::uint8_t index_, const std::uint32_t base_, const std::uint8_t bit_, const bus_t bus_>
struct base_tag
{
	static constexpr std::uint8_t index = index_;
	static constexpr std::uint32_t base = base_;
	static constexpr std::uint32_t bitmask = 1 << bit_;
	static constexpr bus_t bus = bus_;
	static constexpr std::uint32_t reset = 0x40023800 + (std::uint32_t)bus_ + 0x10;
	static constexpr std::uint32_t clock = 0x40023800 + (std::uint32_t)bus_ + 0x30;
	static constexpr std::uint32_t lowclock = 0x40023800 + (std::uint32_t)bus_ + 0x50;
};

/* AHB 1 */
typedef base_tag< 1, 0x40026400, 22, bus_t::ahb1> dma2;		/*!< DMA2 */
typedef base_tag< 0, 0x40026000, 21, bus_t::ahb1> dma1;		/*!< DMA1 */
//typedef base< 0, 0x40023C00> flash;	/*!< Flash Interface */
//typedef base< 0, 0x40023800> rcc;	/*!< RCC */
typedef base_tag< 0, 0x40023000, 12, bus_t::ahb1> crc;		/*!< CRC */
typedef base_tag< 7, 0x40021C00,  7, bus_t::ahb1> gpioH;	/*!< GPIO H */
typedef base_tag< 4, 0x40021000,  4, bus_t::ahb1> gpioE;	/*!< GPIO E */
typedef base_tag< 3, 0x40020C00,  3, bus_t::ahb1> gpioD;	/*!< GPIO D */
typedef base_tag< 2, 0x40020800,  2, bus_t::ahb1> gpioC;	/*!< GPIO C */
typedef base_tag< 1, 0x40020400,  1, bus_t::ahb1> gpioB;	/*!< GPIO B */
typedef base_tag< 0, 0x40020000,  0, bus_t::ahb1> gpioA;	/*!< GPIO A */

/* AHB 2 */
typedef base_tag< 0, 0x50000000,  7, bus_t::ahb2> usb;		/*!< USB OTG FS */

/* APB 1 */
typedef base_tag< 0, 0x40007000, 28, bus_t::apb1> pwr;
typedef base_tag< 2, 0x40005C00, 23, bus_t::apb1> i2c3;
typedef base_tag< 1, 0x40005800, 22, bus_t::apb1> i2c2;
typedef base_tag< 0, 0x40005400, 21, bus_t::apb1> i2c1;
typedef base_tag< 1, 0x40004400, 17, bus_t::apb1> usart2;
//typedef base< 2, 0x40004000> i2s3ext;
typedef base_tag< 2, 0x40003C00, 15, bus_t::apb1> spi3;
typedef base_tag< 1, 0x40003800, 14, bus_t::apb1> spi2;
//typedef base< 1, 0x40003400> i2S2ext;
//typedef base< 0, 0x40003000> iwdg;
typedef base_tag< 0, 0x40002C00, 11, bus_t::apb1> wwdg;
//typedef base< 0, 0x40002800> rtc;
typedef base_tag< 4, 0x40000C00,  3, bus_t::apb1> tim5;
typedef base_tag< 3, 0x40000800,  2, bus_t::apb1> tim4;
typedef base_tag< 2, 0x40000400,  1, bus_t::apb1> tim3;
typedef base_tag< 1, 0x40000000,  0, bus_t::apb1> tim2;

/* APB 2 */
typedef base_tag< 4, 0x40015000, 20, bus_t::apb2> spi5;
typedef base_tag<10, 0x40014800, 18, bus_t::apb2> tim11;
typedef base_tag< 9, 0x40014400, 17, bus_t::apb2> tim10;
typedef base_tag< 8, 0x40014000, 16, bus_t::apb2> tim9;
//typedef base< 0, 0x40013C00> exti;
typedef base_tag< 0, 0x40013800, 14, bus_t::apb2> syscfg;
typedef base_tag< 3, 0x40013400, 13, bus_t::apb2> spi4;
typedef base_tag< 0, 0x40013000, 12, bus_t::apb2> spi1;
typedef base_tag< 0, 0x40012C00, 11, bus_t::apb2> sdio;
typedef base_tag< 0, 0x40012000,  8, bus_t::apb2> adc1;
typedef base_tag< 5, 0x40011400,  5, bus_t::apb2> usart6;
typedef base_tag< 0, 0x40011000,  4, bus_t::apb2> usart1;
typedef base_tag< 0, 0x40010000,  0, bus_t::apb2> tim1;

typedef spi5 i2s5;
typedef spi4 i2s4;
typedef spi3 i2s3;
typedef spi2 i2s2;
typedef spi1 i2s1;
//typedef rtc bkp;


/**
 * @brief Reset one or multiple peripheral units
 */
template<typename T>
void reset(const std::uint32_t bitmask = 0)
{
	typedef T config;

	*((uint32_t*)config::reset) = config::bitmask | bitmask;
}

template<typename T, typename Tn, typename... Args>
void reset(const std::uint32_t bitmask = 0)
{
	typedef T config;
	typedef Tn config_next;

	static_assert(config::bus == config_next::bus, "Elements must have the same bus");

	reset<Tn, Args...>(config::bitmask | bitmask);
}

/**
 * @brief Enable one or multiple peripheral units
 */
template<typename T>
void enable(const std::uint32_t bitmask = 0)
{
	typedef T config;

	*((uint32_t*)config::clock) |= (config::bitmask | bitmask);
}

template<typename T, typename Tn, typename... Args>
void enable(const std::uint32_t bitmask = 0)
{
	typedef T config;
	typedef Tn config_next;

	static_assert(config::bus == config_next::bus, "Elements must have the same bus");

	enable<Tn, Args...>(config::bitmask | bitmask);
}

/**
 * @brief Disable one or multiple peripheral units
 */
template<typename T>
void disable(const std::uint32_t bitmask = 0)
{
	typedef T config;

	*((uint32_t*)config::clock) &= ~(config::bitmask | bitmask);
}

template<typename T, typename Tn, typename... Args>
void disable(const std::uint32_t bitmask = 0)
{
	typedef T config;
	typedef Tn config_next;

	static_assert(config::bus == config_next::bus, "Elements must have the same bus");

	enable<Tn, Args...>(config::bitmask | bitmask);
}

}

#endif
