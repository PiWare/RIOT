add_library(stm32_common STATIC cpu_common.c)
target_link_libraries( stm32_common PUBLIC cpu stm32_common_periph )
target_include_directories(stm32_common PUBLIC include)
add_subdirectory(periph)
