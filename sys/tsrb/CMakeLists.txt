add_library(tsrb STATIC tsrb.c)
target_link_libraries(tsrb PUBLIC board cpu)
