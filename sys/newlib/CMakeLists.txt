set_property(TARGET cpu APPEND PROPERTY APPLICATION_OBJECTS "${CMAKE_CURRENT_SOURCE_DIR}/syscalls.c")
# Append link properties to the cpu target which is always present and transports additional linker flags
get_property(APPLICATION_LINK_FLAGS TARGET cpu PROPERTY APPLICATION_LINK_FLAGS)
set_property(TARGET cpu PROPERTY APPLICATION_LINK_FLAGS "${APPLICATION_LINK_FLAGS} -specs=nano.specs -lc -lnosys")

module(newlib_syscalls SOURCES syscalls.c)
target_link_libraries(newlib_syscalls PRIVATE uart_stdio)
#set_property(TARGET cpu APPEND PROPERTY APPLICATION_OBJECTS "${CMAKE_CURRENT_SOURCE_DIR}/syscalls.c")
# Append link properties to the cpu target which is always present and transports additional linker flags
