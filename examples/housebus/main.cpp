/*
 * Copyright (C) 2014 Hamburg University of Applied Sciences (HAW)
 * Copyright (C) 2014 Ho Chi Minh University of Technology (HCMUT)
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @file
 * @brief       Demonstration of mixed c++ and c user application with pure c RIOT
 *              - mixing of c and c++ source to test name mangling
 *              - introducing a namespace to declarative block, avoiding to qualify calls, e.g. std::vector
 *              - using private and public member functions, e.g. 'cpp_obj.greet()' cannot be accessed from main.cpp
 *              - overloading of function 'cpp_obj.say_hello(...)' for 'none', 'int' or 'float'
 *              - demonstration of templated c++ container 'std::vector'
 *              - usage of iterator to access elements of the container type
 *
 * @author      Martin Landsmann <martin.landsmann@haw-hamburg.de>
 * @author      DangNhat Pham-Huu <51002279@hcmut.edu.vn>
 */

/*
 * all included headers defining c functions, i.e. all RIOT functions, must be marked as extern "C"
 */
extern "C" {
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

using namespace std;

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
		rate_1_hz		= 0x05,
		rate_7_hz		= 0x06,
		rate_12_5_hz	= 0x07,
	};

	struct __attribute__((__packed__)) calib_t
	{
		std::uint8_t H0_rH_x2;
		std::uint8_t H1_rH_x2;
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

	const std::uint8_t WHO_AM_I_DEFAULT	= 0xBC;
	const std::uint8_t REG_MULTIPLE		= 0x80;
	
	/* Registers */
	const std::uint8_t WHO_AM_I			= 0x0F;
	const std::uint8_t AV_CONF			= 0x10;
	
	const std::uint8_t CTRL_REG1		= 0x20;
	const std::uint8_t CTRL_REG2		= 0x21;
	const std::uint8_t CTRL_REG3		= 0x22;
	
	const std::uint8_t STATUS_REG		= 0x27;
	const std::uint8_t HUMIDITY_OUT_L	= 0x28;
	const std::uint8_t HUMIDITY_OUT_H	= 0x29;
	const std::uint8_t TEMP_OUT_L		= 0x2A;
	const std::uint8_t TEMP_OUT_H		= 0x2B;
	
	const std::uint8_t CALIB_0			= 0x30;

	spi &m_spi;
	const std::uint8_t m_address;
	
	calib_t m_calib;
	
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

		return true;
	}
	
	void power(rate_t rate)
	{
		m_spi.write(m_address, (char *)&AV_CONF, 1);
		m_spi.read(m_address, (char *)&rate, 1);
	}
	
	void setAverage()
	{
	}

	std::uint16_t humidity(void)
	{
		const std::uint8_t reg = HUMIDITY_OUT_L | REG_MULTIPLE;
		std::uint16_t result;
		
		m_spi.write(m_address, (char *)&reg, 1);
		m_spi.read(m_address, (char *)&result, 2);
		
		return result;
	}
	
	
	std::int16_t temperature(void)
	{
		const std::uint8_t reg = TEMP_OUT_L | REG_MULTIPLE;
		std::int16_t result;
		
		m_spi.write(m_address, (char *)&reg, 1);
		m_spi.read(m_address, (char *)&result, 2);
		
		return result;
	}
};

/* set interval to 1 second */
//#define INTERVAL (1000000U)
#define INTERVAL (10U)

/* main */
int main()
{
	printf("\n************ RIOT and C++ demo program ***********\n");
	printf("\n");

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
	
	while(1)
	{
		xtimer_usleep_until(&last_wakeup, INTERVAL);
		printf("slept until %" PRIu32 "\n", xtimer_now());
	}
	
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
