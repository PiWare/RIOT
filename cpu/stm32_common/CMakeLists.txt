module(stm32_common SOURCES 
    cpu_common.c)
target_link_libraries( stm32_common PUBLIC cpu stm32_common_periph )
add_subdirectory(periph)
