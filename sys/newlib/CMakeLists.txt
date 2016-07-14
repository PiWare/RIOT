add_library(newlib_syscalls_default STATIC syscalls.c)
target_compile_definitions(newlib_syscalls_default PUBLIC MODULE_NEWLIB)
target_link_libraries(newlib_syscalls_default PRIVATE uart_stdio)
target_link_libraries(newlib_syscalls_default PUBLIC cpu  -u_init -specs=nano.specs -lc -lnosys)
