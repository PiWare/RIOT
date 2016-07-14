set(CPU nrf52 CACHE STRING "cpu type")
set(CPU_MODEL nrf52xxaa CACHE STRING "cpu model")

if(LINUX)
    set(SERIAL_PORT /dev/ttyACM0 PARENT_SCOPE)
elseif(DARWIN)

endif()
include(jlink)
include_directories(include)

add_library(board STATIC board.c)
target_include_directories(board PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/boards/nucleo-common/include> $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
target_link_libraries(board PUBLIC cpu)
target_compile_definitions(board PUBLIC "-DCPU_MODEL_NRF52XXAA" -DRIOT_BOARD="nrf52dk" -DRIOT_MCU="nrf52" -DCPU_FAM_$<UPPER_CASE:${CPU}>)
set_property(TARGET board PROPERTY JLINK_FLASH_ADDR 0)
set_property(TARGET board PROPERTY JLINK_DEVICE nrf52)
set_property(TARGET board PROPERTY BOARD_DEBUGGER_SCRIPT nrf52)
