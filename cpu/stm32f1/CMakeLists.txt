set(CPU_ARCH cortex-m3)
set(CPU_FAM stm32f1)
set(CMAKE_SYSTEM_PROCESSOR "cortex-m3")
set(CPU_FLAGS -mcpu=cortex-m3 -mlittle-endian -mthumb)

add_library(cpu STATIC cpu.c lpm_arch.c vectors.c)
target_link_libraries(cpu PUBLIC core cortexm_common stm32_common stm32_common_periph -uinterrupt_vector -L${CMAKE_CURRENT_SOURCE_DIR}/ldscripts -T${CMAKE_CURRENT_SOURCE_DIR}/ldscripts/${CPU_MODEL}.ld ${CPU_FLAGS})
target_include_directories(cpu PUBLIC include)
target_compile_definitions(cpu PUBLIC "-DCPU_ARCH_CORTEX_M3")
target_compile_options(cpu PUBLIC ${CPU_FLAGS}  )

add_library(board_drivers periph/adc.c  periph/gpio.c  periph/i2c.c periph/rtt.c  periph/spi.c  periph/timer.c  periph/uart.c)
target_include_directories(board_drivers PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
target_link_libraries(board_drivers PUBLIC cortexm_common)
