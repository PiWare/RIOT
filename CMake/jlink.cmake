macro(board_flash_command targetname)
    get_property(JLINK_PRE_FLASH TARGET board PROPERTY JLINK_PRE_FLASH)
    get_property(JLINK_FLASH_ADDR TARGET board PROPERTY JLINK_FLASH_ADDR)
    get_property(JLINK_POST_FLASH TARGET board PROPERTY JLINK_POST_FLASH)
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${targetname}.flash "${JLINK_PRE_FLASH}\n"
    "loadfile ${CMAKE_CURRENT_BINARY_DIR}/${targetname}.hex\n"
    "${JLINK_POST_FLASH}\n"
    "r\n"
    "g\n"
    "exit\n")
    
add_custom_target(${targetname}-flash COMMAND JLinkExe  -device $<TARGET_PROPERTY:board,JLINK_DEVICE> -speed 2000 -if SWD -CommandFile \"${CMAKE_CURRENT_BINARY_DIR}/${targetname}.flash\" DEPENDS ${targetname})
endmacro()

macro(board_debug_command targetname)
    get_property(JLINK_PRE_FLASH TARGET board PROPERTY JLINK_PRE_FLASH)
    get_property(JLINK_FLASH_ADDR TARGET board PROPERTY JLINK_FLASH_ADDR)
    get_property(JLINK_POST_FLASH TARGET board PROPERTY JLINK_POST_FLASH)

    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${targetname}.flash "${JLINK_PRE_FLASH}\n")
    file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${targetname}.flash "loadfile ${CMAKE_CURRENT_BINARY_DIR}/${targetname}.hex\n")
    file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${targetname}.flash "${JLINK_POST_FLASH}\n")
    file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${targetname}.flash "r\n")
    file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${targetname}.flash "g\n")
    file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/${targetname}.flash "exit\n")
    
    add_custom_target(debug COMMAND JLinkExe  -device $<TARGET_PROPERTY:board,JLINK_DEVICE> -speed 2000 -if SWD -CommandFile \"$<TARGET_FILE:${targetname}>.flash\" DEPENDS ${targetname})
endmacro()
