set(CPU stm32f0 CACHE STRING "cpu type")
set(CPU_MODEL stm32f0051r8 CACHE STRING "cpu model")

if(LINUX)
    set(SERIAL_PORT /dev/ttyUSB0 PARENT_SCOPE)
elseif(DARWIN)

endif()

set(DEBUGGER_TYPE openocd CACHE STRING "Debugger")
set(DEBUGGER_CONFIG ${CMAKE_CURRENT_SOURCE_DIR}/dist/openocd.cfg PARENT_SCOPE)

include_directories(include)

add_library(board STATIC board.c)
target_include_directories(board PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
target_link_libraries(board PUBLIC cpu newlib)
target_compile_definitions(board PUBLIC "-DCPU_MODEL_STM32F051R8" -DRIOT_BOARD="stm32f0discovery" -DRIOT_MCU="stm32f0")
