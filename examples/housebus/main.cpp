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

#include "cpp_class.hpp"

/* thread's stack */
char threadA_stack [THREAD_STACKSIZE_MAIN];

/* thread's function */
void *threadA_func(void *arg);

struct spi
{
	unsigned int m_dev;

	spi(const unsigned int dev, const i2c_speed_t speed):
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
	
	static const std::uint8_t CALIB_0			= 0x30 | REG_MULTIPLE;

	spi &m_spi;
	const std::uint8_t m_address;
	
	calib_t m_calib;
	std::uint16_t m_t0, m_t1;
	
	hts221(spi &spi_, const std::uint8_t address):
		m_spi(spi_),
		m_address(address)
	{
	}
	
	bool detect()
	{
		std::uint8_t who_am_i;

		m_spi.write(m_address, (char *)&WHO_AM_I, 1);
		m_spi.read(m_address, (char *)&who_am_i, 1);
		
		if (who_am_i != WHO_AM_I_DEFAULT)
			return false;
		
		m_spi.write(m_address, (char *)&CALIB_0, 1);
		m_spi.read(m_address, (char *)&m_calib, sizeof(calib_t));

		m_calib.H0_rH >>= 1;
		m_calib.H1_rH >>= 1;

		m_t0 = ((((uint16_t)(m_calib.T1_T2_msb & 0x03)) << 8) | ((uint16_t)m_calib.T0_degC_x8)) >> 3;
		m_t1 = ((((uint16_t)(m_calib.T1_T2_msb & 0x0C)) << 6) | ((uint16_t)m_calib.T1_degC_x8)) >> 3;

		return true;
	}

	void setAverage()
	{
		char buffer[2] = { AV_CONF, (char)0 };

		m_spi.write(m_address, buffer, sizeof(buffer));
	}
	
	void power(rate_t rate)
	{
		char buffer[2] = { CTRL_REG1, (char)rate };

		m_spi.write(m_address, buffer, sizeof(buffer));
	}
	
	std::uint16_t humidity(void)
	{
		const std::uint8_t reg = HUMIDITY_OUT_L | REG_MULTIPLE;
		std::uint16_t result;
		
		m_spi.write(m_address, (char *)&reg, 1);
		m_spi.read(m_address, (char *)&result, 2);
		

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
		const std::uint8_t reg = TEMP_OUT_L | REG_MULTIPLE;
		std::uint16_t result;
		
		m_spi.write(m_address, (char *)&reg, 1);
		m_spi.read(m_address, (char *)&result, 2);

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

	std::uint32_t array1[4] = { 0x12345678, 0xDEADBEEF, 0x11111111, 0xACACACAC };
	std::uint32_t array2[4] = { 0xAAAAAAAA, 0xBBBBBBBB, 0xCCCCCCCC, 0xDDDDDDDD };

	printf("\n************ RIOT and C++ demo program ***********\n");
	printf("\n");

	printf("%.8lX\n", (unsigned long int)array1);
	printf("%.8lX\n", (unsigned long int)array2);

	printf("%.8lX %.8lX %.8lX %.8lX\n", array2[0], array2[1], array2[2], array2[3]);

	dma dm0(0, array1, array2, sizeof(array1));
	dm0.start();
	while (dm0.busy());
	dm0.info();

	printf("%.8lX %.8lX %.8lX %.8lX\n", array2[0], array2[1], array2[2], array2[3]);

	spi spi0(0, I2C_SPEED_FAST);
	hts221 hts(spi0, 0x5F);
	if (hts.detect())
	{
		printf("HTS221 found\n");
	}
	else
	{
		printf("HTS221 not found!\n");
	}

	hts.power(hts221::rate_t::rate_1_hz);

	uint32_t last_wakeup = xtimer_now();
	
/*
	while(1)
	{
		xtimer_usleep_until(&last_wakeup, INTERVAL);
		printf("slept until %" PRIu32 "\n", xtimer_now());
	}
*/
	
	while (true)
	{
		printf("Humidity: %d\n", hts.humidity());
		printf("Temperature: %d\n", hts.temperature());
		
		printf("Sleep...\n");
		xtimer_usleep_until(&last_wakeup, INTERVAL);
		printf("Wakeup...\n");
	}
	
	hts.power(hts221::rate_t::off);

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
