add_executable(hello-world main.c )
target_link_libraries(hello-world cpu board_drivers)
board_flash_command(hello-world)
add_custom_command(TARGET hello-world POST_BUILD COMMAND arm-none-eabi-objcopy -O ihex $<TARGET_FILE:hello-world> ${CMAKE_CURRENT_BINARY_DIR}/hello-world.hex)
