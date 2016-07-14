add_library(nrf5x_common_periph STATIC
    periph/cpuid.c
    periph/gpio.c
    periph/hwrng.c
    periph/timer.c
    periph/uart.c)
target_link_libraries(nrf5x_common_periph PRIVATE cpu)
target_include_directories(nrf5x_common_periph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
