add_library(uart_stdio STATIC uart_stdio.c)
target_link_libraries(uart_stdio PRIVATE tsrb)
