set(STM_MCU stm32f0 stm32f1 stm32f3 stm32l0 stm32l1)
set(CORTEX_CPU nrf52 ${STM_MCU})
if( CPU IN_LIST CORTEX_CPU)
    add_subdirectory(cortexm_common)
endif()

add_subdirectory(${CPU})

if( "${CPU}" STREQUAL "nrf52")
    add_subdirectory(nrf5x_common)
endif()
if( CPU IN_LIST STM_MCU)
    add_subdirectory(stm32_common)
endif()
