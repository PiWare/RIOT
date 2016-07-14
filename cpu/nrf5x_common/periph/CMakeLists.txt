module(nrf5x_common_periph SOURCES cpuid.c gpio.c hwrng.c timer.c uart.c)
target_link_libraries(nrf5x_common_periph PRIVATE cpu)
