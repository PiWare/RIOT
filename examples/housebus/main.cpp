/*
 * Copyright (C) 2016 Benjamin Füldner
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @file
 * @brief
 * @author Benjamin Füldner <benjamin@fueldner.net>
 */

extern "C"
{
#include "thread.h"
#include "c_functions.h"
}

#include <cstdint>
#include <cstdio>
#include <vector>

extern "C"
{
#include "periph/i2c.h"
#include "xtimer.h"
}

#include <periph/pwm.h>
#include <periph/gpio.h>
#include <periph/periph.h>

#include <driver/rgb.h>

#include "cpp_class.hpp"

/*
template <std::uint8_t index_, std::uint32_t base_, std::uint8_t interrupt_, bool ahb_ = false>
struct gpio_tag
{
	static constexpr std::uint8_t index = index_;
	static constexpr std::uint32_t base = base_;
	static constexpr std::uint8_t interrupt = interrupt_;
	static constexpr bool ahb = ahb_;
};

typedef gpio_tag<0, 0x10000000, 1> gpio0_tag;
typedef gpio_tag<1, 0x20000000, 2> gpio1_tag;

constexpr gpio0_tag gpio0;
constexpr gpio1_tag gpio1;
*/

template<typename T>
void enable()
{
	typedef T config;

	*((volatile uint32_t *)config::base) |= config::index;
}


/* thread's stack */
char threadA_stack [THREAD_STACKSIZE_MAIN];

/* thread's function */
void *threadA_func(void *arg);

struct i2c
{
	unsigned int m_dev;

	i2c(const unsigned int dev, const i2c_speed_t speed):
		m_dev(dev)
	{
	//	int res = 
		i2c_init_master(m_dev, speed);
	}
	
	size_t write(const std::uint8_t address, char *data, size_t length)
	{
		return i2c_write_bytes(m_dev, address, data, length);
	}
	
	size_t read(const std::uint8_t address, char *data, size_t length)
	{
		return i2c_read_bytes(m_dev, address, data, length);
	}

	size_t read_reg(const std::uint8_t address, const std::uint8_t reg, char *data, size_t length)
	{
		return i2c_read_regs(m_dev, address, reg, data, length);
	}
};

struct hts221
{
	enum class temperature_average_t:
		std::uint8_t
	{
		
	};
	
	enum class rate_t:
		std::uint8_t
	{
		off				= 0x04,
		oneshot			= 0x84,
		rate_1_hz		= 0x85,
		rate_7_hz		= 0x86,
		rate_12_5_hz	= 0x87,
	};

	struct __attribute__((__packed__)) calib_t
	{
		std::uint8_t H0_rH;
		std::uint8_t H1_rH;
		std::uint8_t T0_degC_x8;
		std::uint8_t T1_degC_x8;
		std::uint16_t reserved_1;
		std::uint8_t T1_T2_msb;
		std::int16_t H0_T0_OUT;
		std::int16_t reserved_2;
		std::int16_t H1_T0_OUT;
		std::int16_t T0_OUT;
		std::int16_t T1_OUT;
	};

	static const std::uint8_t I2C_ADDRESS		= 0x5F;
	static const std::uint8_t WHO_AM_I_DEFAULT	= 0xBC;
	static const std::uint8_t REG_MULTIPLE		= 0x80;
	
	/* Registers */
	static const std::uint8_t WHO_AM_I			= 0x0F;
	static const std::uint8_t AV_CONF			= 0x10;
	
	static const std::uint8_t CTRL_REG1			= 0x20;
	static const std::uint8_t CTRL_REG2			= 0x21;
	static const std::uint8_t CTRL_REG3			= 0x22;
	
	static const std::uint8_t STATUS_REG		= 0x27;
	static const std::uint8_t HUMIDITY_OUT_L	= 0x28;
	static const std::uint8_t HUMIDITY_OUT_H	= 0x29;
	static const std::uint8_t TEMP_OUT_L		= 0x2A;
	static const std::uint8_t TEMP_OUT_H		= 0x2B;
	
	static const std::uint8_t CALIB_0			= 0x30;	// | REG_MULTIPLE;
	static const std::uint8_t CALIB_1			= 0x31;
	static const std::uint8_t CALIB_2			= 0x32;
	static const std::uint8_t CALIB_3			= 0x33;
	static const std::uint8_t CALIB_4			= 0x34;
	static const std::uint8_t CALIB_5			= 0x35;
	static const std::uint8_t CALIB_6			= 0x36;
	static const std::uint8_t CALIB_7			= 0x37;
	static const std::uint8_t CALIB_8			= 0x38;
	static const std::uint8_t CALIB_9			= 0x39;
	static const std::uint8_t CALIB_A			= 0x3A;
	static const std::uint8_t CALIB_B			= 0x3B;
	static const std::uint8_t CALIB_C			= 0x3C;
	static const std::uint8_t CALIB_D			= 0x3D;
	static const std::uint8_t CALIB_E			= 0x3E;
	static const std::uint8_t CALIB_F			= 0x3F;

	i2c &m_i2c;
	const std::uint8_t m_address;
	
	calib_t m_calib;
	std::uint16_t m_t0, m_t1;
	
	hts221(i2c &i2c_, const std::uint8_t address = I2C_ADDRESS):
		m_i2c(i2c_),
		m_address(address)
	{
	}
	
	bool detect()
	{
		std::uint8_t who_am_i;
	//	char *ptr = (char *)&m_calib;

		m_i2c.read_reg(m_address, WHO_AM_I, (char *)&who_am_i, 1);
		
		if (who_am_i != WHO_AM_I_DEFAULT)
			return false;
		
		printf("sizeof = %d\n", sizeof(calib_t));

		m_i2c.read_reg(m_address, CALIB_0 | REG_MULTIPLE, (char *)&m_calib, sizeof(calib_t));

		m_calib.H0_rH >>= 1;
		m_calib.H1_rH >>= 1;

		m_t0 = ((((uint16_t)(m_calib.T1_T2_msb & 0x03)) << 8) | ((uint16_t)m_calib.T0_degC_x8)) >> 3;
		m_t1 = ((((uint16_t)(m_calib.T1_T2_msb & 0x0C)) << 6) | ((uint16_t)m_calib.T1_degC_x8)) >> 3;

		return true;
	}

	void setAverage()
	{
		char buffer[2] = { AV_CONF, (char)0 };

		m_i2c.write(m_address, buffer, sizeof(buffer));
	}
	
	void power(rate_t rate)
	{
		char buffer[2] = { CTRL_REG1, (char)rate };

		m_i2c.write(m_address, buffer, sizeof(buffer));
	}
	
	std::uint16_t humidity(void)
	{
		std::uint16_t result;
		
		m_i2c.read_reg(m_address, HUMIDITY_OUT_L | REG_MULTIPLE, (char *)&result, 2);
		
		std::uint32_t tmp = ((std::uint32_t)(result - m_calib.H0_T0_OUT)) * ((uint32_t)(m_calib.H1_rH - m_calib.H0_rH) * 10);
		result = tmp / (m_calib.H1_T0_OUT - m_calib.H0_T0_OUT) + m_calib.H0_rH * 10;

	/*
		if (result > 1000)
			result = 1000;
	*/
		return result;
	}
	
	std::int16_t temperature(void)
	{
		std::uint16_t result;
		
		m_i2c.read_reg(m_address, TEMP_OUT_L | REG_MULTIPLE, (char *)&result, 2);

		std::uint32_t tmp = ((uint32_t)(result - m_calib.T0_OUT)) * ((uint32_t)(m_t1 - m_t0) * 10);
		result = tmp / (m_calib.T1_OUT - m_calib.T0_OUT)  + m_t0 * 10;


	/*
		double T_DegC;
		double T0_degC = (T0_degC_x8 + (1 << 8) * (T1_T0msb & 0x03)) / 8.0;
		double T1_degC = (T1_degC_x8 + (1 << 6) * (T1_T0msb & 0x0C)) / 8.0;	// Value is in 3rd and fourth bit, so we only need to shift this value 6 more bits.
		T_DegC = (T0_degC + (T_OUT - T0_OUT) * (T1_degC - T0_degC) / (T1_OUT - T0_OUT));
	*/
		return result;
	}
};

const std::uint8_t hts221::I2C_ADDRESS;
const std::uint8_t hts221::WHO_AM_I_DEFAULT;
const std::uint8_t hts221::REG_MULTIPLE;

/* Registers */
const std::uint8_t hts221::WHO_AM_I;
const std::uint8_t hts221::AV_CONF;

const std::uint8_t hts221::CTRL_REG1;
const std::uint8_t hts221::CTRL_REG2;
const std::uint8_t hts221::CTRL_REG3;

const std::uint8_t hts221::STATUS_REG;
const std::uint8_t hts221::HUMIDITY_OUT_L;
const std::uint8_t hts221::HUMIDITY_OUT_H;
const std::uint8_t hts221::TEMP_OUT_L;
const std::uint8_t hts221::TEMP_OUT_H;

const std::uint8_t hts221::CALIB_0;
const std::uint8_t hts221::CALIB_1;
const std::uint8_t hts221::CALIB_2;
const std::uint8_t hts221::CALIB_3;
const std::uint8_t hts221::CALIB_4;
const std::uint8_t hts221::CALIB_5;
const std::uint8_t hts221::CALIB_6;
const std::uint8_t hts221::CALIB_7;
const std::uint8_t hts221::CALIB_8;
const std::uint8_t hts221::CALIB_9;
const std::uint8_t hts221::CALIB_A;
const std::uint8_t hts221::CALIB_B;
const std::uint8_t hts221::CALIB_C;
const std::uint8_t hts221::CALIB_D;
const std::uint8_t hts221::CALIB_E;
const std::uint8_t hts221::CALIB_F;

struct lps25hb
{
	enum class temperature_average_t:
		std::uint8_t
	{

	};

	enum class rate_t:
		std::uint8_t
	{
		off				= 0x04,
		oneshot			= 0x84,
		rate_1_hz		= 0x94,
		rate_7_hz		= 0xA4,
		rate_12_5_hz	= 0xB7,
		rate_25_hz		= 0xC7,
	};

	struct __attribute__((__packed__)) calib_t
	{
	};

	static const std::uint8_t I2C_ADDRESS		= 0x5D;	// 0x5C SA0 = 0
	static const std::uint8_t WHO_AM_I_DEFAULT	= 0xBD;
	static const std::uint8_t REG_MULTIPLE		= 0x80;

	/* Registers */
	static const std::uint8_t REF_P_XL			= 0x08;
	static const std::uint8_t REF_P_L			= 0x09;
	static const std::uint8_t REF_P_H			= 0x0A;

	static const std::uint8_t WHO_AM_I			= 0x0F;
	static const std::uint8_t RES_CONF			= 0x10;

	static const std::uint8_t CTRL_REG1			= 0x20;
	static const std::uint8_t CTRL_REG2			= 0x21;
	static const std::uint8_t CTRL_REG3			= 0x22;
	static const std::uint8_t CTRL_REG4			= 0x23;
	static const std::uint8_t INTERRUPT_CFG		= 0x24;
	static const std::uint8_t INT_SOURCE		= 0x25;

	static const std::uint8_t STATUS_REG		= 0x27;
	static const std::uint8_t PRESS_OUT_XL		= 0x28;
	static const std::uint8_t PRESS_OUT_L		= 0x29;
	static const std::uint8_t PRESS_OUT_H		= 0x2A;
	static const std::uint8_t TEMP_OUT_L		= 0x2B;
	static const std::uint8_t TEMP_OUT_H		= 0x2C;

	i2c &m_i2c;
	const std::uint8_t m_address;

	calib_t m_calib;
	std::uint16_t m_t0, m_t1;

	lps25hb(i2c &i2c_, const std::uint8_t address = I2C_ADDRESS):
		m_i2c(i2c_),
		m_address(address)
	{
	}

	bool detect()
	{
		std::uint8_t who_am_i;

		m_i2c.write(m_address, (char *)&WHO_AM_I, 1);
		m_i2c.read(m_address, (char *)&who_am_i, 1);

		if (who_am_i != WHO_AM_I_DEFAULT)
			return false;

		return true;
	}

	void power(rate_t rate)
	{
		char buffer[2] = { CTRL_REG1, (char)rate };

		m_i2c.write(m_address, buffer, sizeof(buffer));
	}

	std::uint32_t reference(void)
	{
		std::uint32_t result = 0;

		m_i2c.read_reg(m_address, REF_P_XL | REG_MULTIPLE, (char *)&result, 3);

		return result;
	}

	std::int16_t pressure(void)
	{
		std::int32_t result = 0;

		m_i2c.read_reg(m_address, PRESS_OUT_XL | REG_MULTIPLE, (char *)&result, 3);
		if (result & 0x800000)
			result |= 0xFF000000;
		return result >> 12;
	}

	std::int16_t temperature(void)
	{
		std::int16_t result;

		m_i2c.read_reg(m_address, TEMP_OUT_L | REG_MULTIPLE, (char *)&result, 2);

		return 42.5 + result / 480;
	}
};

const std::uint8_t lps25hb::I2C_ADDRESS;
const std::uint8_t lps25hb::WHO_AM_I_DEFAULT;
const std::uint8_t lps25hb::REG_MULTIPLE;

const std::uint8_t lps25hb::REF_P_XL;
const std::uint8_t lps25hb::REF_P_L;
const std::uint8_t lps25hb::REF_P_H;

const std::uint8_t lps25hb::WHO_AM_I;
const std::uint8_t lps25hb::RES_CONF;

const std::uint8_t lps25hb::CTRL_REG1;
const std::uint8_t lps25hb::CTRL_REG2;
const std::uint8_t lps25hb::CTRL_REG3;
const std::uint8_t lps25hb::CTRL_REG4;
const std::uint8_t lps25hb::INTERRUPT_CFG;
const std::uint8_t lps25hb::INT_SOURCE;

const std::uint8_t lps25hb::STATUS_REG;
const std::uint8_t lps25hb::PRESS_OUT_XL;
const std::uint8_t lps25hb::PRESS_OUT_L;
const std::uint8_t lps25hb::PRESS_OUT_H;
const std::uint8_t lps25hb::TEMP_OUT_L;
const std::uint8_t lps25hb::TEMP_OUT_H;

struct lis3mdl
{
/*
	enum class mode_t:
		std::uint8_t
	{
		low_power				= 0x0,
		medium_performance		= 0x1,
		high_performance		= 0x2,
		ultra_high_performance	= 0x3,
	};
*/
	enum class mode_t:
		std::uint8_t
	{
		continuous			= 0x0,
		single				= 0x1,
		power_down			= 0x3,
	};

	enum class rate_t:
		std::uint8_t
	{
		rate_0_hz_625		= 0x00,
		rate_1_hz_25		= 0x04,
		rate_2_hz_5			= 0x08,
		rate_5_hz			= 0x0C,
		rate_10_hz			= 0x10,
		rate_20_hz			= 0x14,
		rate_40_hz			= 0x18,
		rate_80_hz			= 0x1C,
		rate_155_hz			= 0x02,
		rate_300_hz			= 0x22,
		rate_560_hz			= 0x42,
		rate_1000_hz		= 0x62,
	};

	enum class gauss_t:
		std::uint8_t
	{
		gauss_4			= 0x0,
		gauss_8			= 0x1,
		gauss_12		= 0x2,
		gauss_16		= 0x3,
	};

	static const std::uint8_t I2C_ADDRESS		= 0x1E;	// 0x1C SA0 = 0
	static const std::uint8_t WHO_AM_I_DEFAULT	= 0x3D;
	static const std::uint8_t REG_MULTIPLE		= 0x80;

	/* Registers */
	static const std::uint8_t WHO_AM_I			= 0x0F;

	static const std::uint8_t CTRL_REG1			= 0x20;
	static const std::uint8_t CTRL_REG2			= 0x21;
	static const std::uint8_t CTRL_REG3			= 0x22;
	static const std::uint8_t CTRL_REG4			= 0x23;
	static const std::uint8_t CTRL_REG5			= 0x24;

	static const std::uint8_t STATUS_REG		= 0x27;
	static const std::uint8_t OUT_X_L			= 0x28;
	static const std::uint8_t OUT_X_H			= 0x29;
	static const std::uint8_t OUT_Y_L			= 0x2A;
	static const std::uint8_t OUT_Y_H			= 0x2B;
	static const std::uint8_t OUT_Z_L			= 0x2C;
	static const std::uint8_t OUT_Z_H			= 0x2D;
	static const std::uint8_t TEMP_OUT_L		= 0x2E;
	static const std::uint8_t TEMP_OUT_H		= 0x2F;

	static const std::uint8_t INT_CFG			= 0x30;
	static const std::uint8_t INT_SRC			= 0x31;
	static const std::uint8_t INT_THS_L			= 0x32;
	static const std::uint8_t INT_THS_H			= 0x33;

	i2c &m_i2c;
	const std::uint8_t m_address;

	lis3mdl(i2c &i2c_, const std::uint8_t address = I2C_ADDRESS):
		m_i2c(i2c_),
		m_address(address)
	{
	}

	bool detect()
	{
		std::uint8_t who_am_i;

		m_i2c.read_reg(m_address, WHO_AM_I, (char *)&who_am_i, 1);
		if (who_am_i != WHO_AM_I_DEFAULT)
			return false;

		return true;
	}

	void power(mode_t mode, rate_t rate, gauss_t gauss)
	{
		char buffer[6] = { CTRL_REG1 | REG_MULTIPLE, char((char)rate | (char)0x80), char((char)gauss << 5), (char)mode, char((char)rate & 0x60 >> 3), 0x40 };

		m_i2c.write(m_address, buffer, sizeof(buffer));
	}

	std::int16_t axisX(void)
	{
		std::int16_t result;

		m_i2c.read_reg(m_address, OUT_X_L | REG_MULTIPLE, (char *)&result, 2);

		return result;	// / 6842
	}

	std::int16_t axisY(void)
	{
		std::int16_t result;

		m_i2c.read_reg(m_address, OUT_Y_L | REG_MULTIPLE, (char *)&result, 2);

		return result;	// / 6842
	}

	std::int16_t axisZ(void)
	{
		std::int16_t result;

		m_i2c.read_reg(m_address, OUT_Z_L | REG_MULTIPLE, (char *)&result, 2);

		return result;	// / 6842
	}

	std::int16_t temperature(void)
	{
		std::int16_t result;

		m_i2c.read_reg(m_address, TEMP_OUT_L | REG_MULTIPLE, (char *)&result, 2);

		return (result >> 3) + 25;
	}
};

const std::uint8_t lis3mdl::I2C_ADDRESS;
const std::uint8_t lis3mdl::WHO_AM_I_DEFAULT;
const std::uint8_t lis3mdl::REG_MULTIPLE;

const std::uint8_t lis3mdl::WHO_AM_I;

const std::uint8_t lis3mdl::CTRL_REG1;
const std::uint8_t lis3mdl::CTRL_REG2;
const std::uint8_t lis3mdl::CTRL_REG3;
const std::uint8_t lis3mdl::CTRL_REG4;
const std::uint8_t lis3mdl::CTRL_REG5;

const std::uint8_t lis3mdl::STATUS_REG;
const std::uint8_t lis3mdl::OUT_X_L;
const std::uint8_t lis3mdl::OUT_X_H;
const std::uint8_t lis3mdl::OUT_Y_L;
const std::uint8_t lis3mdl::OUT_Y_H;
const std::uint8_t lis3mdl::OUT_Z_L;
const std::uint8_t lis3mdl::OUT_Z_H;
const std::uint8_t lis3mdl::TEMP_OUT_L;
const std::uint8_t lis3mdl::TEMP_OUT_H;

const std::uint8_t lis3mdl::INT_CFG;
const std::uint8_t lis3mdl::INT_SRC;
const std::uint8_t lis3mdl::INT_THS_L;
const std::uint8_t lis3mdl::INT_THS_H;

struct dma
{
//	static const std::uint32_t DMA_OFFSET	= 0x40026000;	/*!< DMA 1 */
	static const std::uint32_t DMA_OFFSET	= 0x40026400;	/*!< DMA 2 */

	static const std::uint16_t DMA_LISR		= 0x0000;
	static const std::uint16_t DMA_HISR		= 0x0004;
	static const std::uint16_t DMA_LIFCR	= 0x0008;
	static const std::uint16_t DMA_HIFCR	= 0x000C;

	static const std::uint16_t DMA_SxCR		= 0x0010;
	static const std::uint16_t DMA_SxNDTR	= 0x0014;
	static const std::uint16_t DMA_SxPAR	= 0x0018;
	static const std::uint16_t DMA_SxM0AR	= 0x001C;
	static const std::uint16_t DMA_SxM1AR	= 0x0020;
	static const std::uint16_t DMA_SxFCR	= 0x0024;

	static const std::uint16_t DMA_CHANNEL_SIZE	= 0x0018;

	enum class channel_t
	{
		channel_0	= 0x00,
		channel_1	= 0x01,
		channel_2	= 0x02,
		channel_3	= 0x03,
		channel_4	= 0x04,
		channel_5	= 0x05,
		channel_6	= 0x06,
		channel_7	= 0x07,
	};

	enum class priority_t
	{
		low			= 0x0,
		medium		= 0x1,
		high		= 0x2,
		very_high	= 0x3,
	};

	enum class mode_t
	{
		peripheral_to_memory	= 0x00,
		memory_to_peripheral	= 0x01,
		memory_to_memory		= 0x02,
	};

	enum class size_t
	{
		byte		= 0x00,
		half_word	= 0x01,
		word		= 0x02,
	};

	const std::uint8_t m_stream;

	dma(const std::uint8_t stream, const std::uint32_t *peripheral, const std::uint32_t *memory, const std::uint16_t size):
		m_stream(stream)
	{
		/* Disable channel */
		*((volatile std::uint32_t *)(DMA_OFFSET + DMA_SxCR + DMA_CHANNEL_SIZE * m_stream)) &= ~1;
		while (*((volatile std::uint32_t *)(DMA_OFFSET + DMA_SxCR + DMA_CHANNEL_SIZE * m_stream)) & 0x00000001);

		/* Set peripheral address */
		*((volatile std::uint32_t *)(DMA_OFFSET + DMA_CHANNEL_SIZE * m_stream + DMA_SxPAR)) = (unsigned long int)peripheral;

		/* Set memory address */
		*((volatile std::uint32_t *)(DMA_OFFSET + DMA_CHANNEL_SIZE * m_stream + DMA_SxM0AR)) = (unsigned long int)memory;

		/* Set size */
		*((volatile std::uint32_t *)(DMA_OFFSET + DMA_CHANNEL_SIZE * m_stream + DMA_SxNDTR)) = size;

		/* Configure channel */
		*((volatile std::uint32_t *)(DMA_OFFSET + DMA_CHANNEL_SIZE * m_stream + DMA_SxCR)) =
			(std::uint32_t)channel_t::channel_7 << 25 |
			(std::uint32_t)priority_t::very_high << 16 |
			(std::uint32_t)size_t::word << 13 |
			(std::uint32_t)size_t::word << 11 |
			(std::uint32_t)1 << 10 |
			(std::uint32_t)1 << 9 |
			(std::uint32_t)mode_t::memory_to_memory << 6;

		/* Configure FIFO */
		*((volatile std::uint32_t *)(DMA_OFFSET + DMA_CHANNEL_SIZE * m_stream + DMA_SxFCR)) = 0x04;
	}

	void start()
	{
		*((volatile std::uint32_t *)(DMA_OFFSET + DMA_LISR)) = 0x3F;
		info();

		*((volatile std::uint32_t *)(DMA_OFFSET + DMA_SxCR + DMA_CHANNEL_SIZE * m_stream)) |= 1;
	}

	void stop()
	{
		*((volatile std::uint32_t *)(DMA_OFFSET + DMA_SxCR + DMA_CHANNEL_SIZE * m_stream)) &= ~1;
	}

	void info()
	{
		printf("LISR: %.8lX\n", *((volatile std::uint32_t *)(DMA_OFFSET + DMA_LISR)));
		printf("SxCR: %.8lX\n", *((volatile std::uint32_t *)(DMA_OFFSET + DMA_SxCR + DMA_CHANNEL_SIZE * m_stream)));
		printf("SxFCR: %.8lX\n", *((volatile std::uint32_t *)(DMA_OFFSET + DMA_CHANNEL_SIZE * m_stream + DMA_SxFCR)));
	}

	bool busy()
	{
		return *((volatile std::uint32_t *)(DMA_OFFSET + DMA_SxCR + DMA_CHANNEL_SIZE * m_stream)) & 1;
	}
};



/* set interval to 1 second */
#define INTERVAL (1000000U)

/* main */
int main()
{
	dma_poweron(0);
	dma_poweron(8);

	periph::enable<periph::dma1>();
	periph::enable<periph::dma2>();

	periph::gpio::set<periph::gpio::PA2::usart2_tx>();

//	periph::clock::get().enable(periph::clock::AHB1ENR, periph::clock::DMA1_);
//	periph::clock::get().enable(periph::clock::AHB1ENR, periph::clock::DMA2_);

	std::uint32_t array1[4] = { 0xBADEAFFE, 0xDEADBEEF, 0xFEEDBEEF, 0xDEADC0DE };
	std::uint32_t array2[4] = { 0xAAAAAAAA, 0xBBBBBBBB, 0xCCCCCCCC, 0xDDDDDDDD };

	printf("\n************ RIOT and C++ demo program ***********\n");
	printf("\n");

	float test = 1.5f;
	printf("Float: %f\n", test);

	printf("%.8lX\n", (unsigned long int)array1);
	printf("%.8lX\n", (unsigned long int)array2);

	printf("%.8lX %.8lX %.8lX %.8lX\n", array2[0], array2[1], array2[2], array2[3]);

	dma dm0(0, array1, array2, sizeof(array1));
	dm0.start();
	while (dm0.busy());
	dm0.info();

	printf("%.8lX %.8lX %.8lX %.8lX\n", array2[0], array2[1], array2[2], array2[3]);

	i2c i2c0(0, I2C_SPEED_FAST);
	hts221 hts(i2c0);
	if (hts.detect())
	{
		printf("HTS221 found\n");
	}
	else
	{
		printf("HTS221 not found!\n");
	}

	lps25hb lps(i2c0);
	if (lps.detect())
	{
		printf("LPS25HB found\n");
	}
	else
	{
		printf("LPS25HB not found!\n");
	}

	lis3mdl lis(i2c0);
	if (lis.detect())
	{
		printf("LIS3MDL found\n");
	}
	else
	{
		printf("LIS3MDL not found!\n");
	}

	hts.power(hts221::rate_t::rate_1_hz);
	lps.power(lps25hb::rate_t::rate_1_hz);
	lis.power(lis3mdl::mode_t::continuous, lis3mdl::rate_t::rate_5_hz, lis3mdl::gauss_t::gauss_4);

	uint32_t last_wakeup = xtimer_now();
	while (true)
	{
		printf("Humidity: %d\n", hts.humidity());
		printf("Temperature: %d\n\n", hts.temperature());

		printf("Reference: %ld\n", lps.reference());
		printf("Pressure: %d mBar\n", lps.pressure());
		printf("Temperature: %d C\n\n", lps.temperature());

		printf("Axis X: %d\n", lis.axisX());
		printf("Axis Y: %d\n", lis.axisY());
		printf("Axis Z: %d\n", lis.axisZ());
		printf("Temperature: %d C\n", lis.temperature());

		printf("Sleep...\n");
		xtimer_usleep_until(&last_wakeup, INTERVAL);
		printf("Wakeup...\n");
	}

	hts.power(hts221::rate_t::off);
	lps.power(lps25hb::rate_t::off);

#if 0
	/* create thread A */
	thread_create(threadA_stack, sizeof(threadA_stack), 0, THREAD_CREATE_WOUT_YIELD, threadA_func, NULL, "thread A");

    printf("******** Hello, you're in thread #%" PRIkernel_pid " ********\n", sched_active_pid);
    printf("We'll test C++ class and methods here!\n");

    cpp_class cpp_obj;
    printf("\n-= Test overloading functions =-\n");
    cpp_obj.say_hello();
    cpp_obj.say_hello(42);
    cpp_obj.say_hello(3.141592f);

    printf("\n-= Test namespace =-\n");
    printf("typing std::vector is obsolete when 'using namespace std;'\n");
    vector<int> vInts;
    vInts.push_back(1);
    vInts.push_back(3);
    vInts.push_back(2);
    printf("The vector vInts has been filled with %d numbers.\n", (int)vInts.size());

    printf("\n-= Test iterator =-\n");
    printf("The content of vInts = { ");

    for (vector<int>::iterator it = vInts.begin(); it != vInts.end(); ++it) {
        printf("%d ", *(it));
    }

    printf("}\n");
#endif

    return 0;
}

/* thread A function implemetation */
void *threadA_func(void *)
{
    int day = 13, month = 6, year = 2014;
    int ret_day;

    printf("******** Hello, you're in thread #%" PRIkernel_pid " ********\n", sched_active_pid);
    printf("We'll test some C functions here!\n");

    printf("\n-= hello function =-\n");
    hello();

    printf("\n-= day_of_week function =-\n");

    printf("day %d, month %d, year %d is ", day, month, year);

    ret_day = day_of_week(day, month, year);
    if (ret_day >= 0){
        char day_of_week_table[][32] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        printf("%s\n", day_of_week_table[ret_day]);
    }

    printf("\nThis demo ends here, press Ctrl-C to exit (if you're on native)!\n");

    return NULL;
}
