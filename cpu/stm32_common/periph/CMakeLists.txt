add_library(stm32_common_periph STATIC cpuid.c dac.c)
target_link_libraries(stm32_common_periph PRIVATE cpu stm32_common)
