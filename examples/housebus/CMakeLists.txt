cmake_minimum_required(VERSION 2.8)
project(lib_test CXX)

set(CMAKE_CXX_FLAGS "-std=c++11") # -Wall")

set(HEADER
	include/type/color.h
	include/type/direction.h

	include/interface/display.h
	include/interface/gpio.h
	include/interface/input.h
	include/interface/i2c.h
	include/interface/output.h
	include/interface/pwm.h
	include/interface/spi.h

	include/driver/rgb.h
	include/driver/i2c/pcal6408.h
	include/driver/spi/pcd8544.h

	include/periph/adc.h
	include/periph/clock.h
	include/periph/gpio.h
	include/periph/i2c.h
	include/periph/periph.h
	include/periph/pwm.h
	include/periph/spi.h

	include/dummy/adc.h
	include/dummy/clock.h
	include/dummy/gpio.h
	include/dummy/i2c.h
	include/dummy/periph.h
	include/dummy/pwm.h
	include/dummy/spi.h
)

set(SOURCE
	test/test.cpp

	src/driver/i2c/pcal6408.cpp
)

include_directories("include")

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADER})
#target_link_libraries(template ${Boost_LIBRARIES} Qt5::Widgets)
