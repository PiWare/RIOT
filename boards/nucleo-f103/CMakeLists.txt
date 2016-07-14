set(CPU stm32f1 CACHE STRING "cpu type")
set(CPU_MODEL stm32f103rb CACHE STRING "cpu model")

if(LINUX)
    set(SERIAL_PORT /dev/ttyUSB0 PARENT_SCOPE)
elseif(DARWIN)

endif()

include(openocd)
include_directories(include)

add_library(board STATIC board.c)
target_include_directories(board PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/boards/nucleo-common/include> $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
target_link_libraries(board PUBLIC cpu)
target_compile_definitions(board PUBLIC "-DCPU_MODEL_STM32F103RB" -DRIOT_BOARD="nucleo-f103" -DRIOT_MCU="stm32f1")
set_property(TARGET board PROPERTY BOARD_DEBUGGER_SCRIPT board/st_nucleo_f103rb.cfg)
