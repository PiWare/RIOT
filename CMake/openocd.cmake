macro(board_flash_command targetname)
    add_custom_target(flash COMMAND openocd -f $<TARGET_PROPERTY:board,BOARD_DEBUGGER_SCRIPT> -c \"program $<TARGET_FILE:${targetname}> verify reset exit\" DEPENDS ${targetname})
endmacro()

