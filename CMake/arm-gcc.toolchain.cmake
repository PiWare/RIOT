set(CMAKE_SYSTEM_NAME RIOT)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE NEVER)

set(CMAKE_CXX_COMPILER_WORKS TRUE)
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wstrict-prototypes -Werror=strict-prototypes -Wold-style-definition -Werror=old-style-definition -Wall")
set(CMAKE_C_LINK_EXECUTABLE "${CMAKE_CXX_COMPILER} <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> -static -lgcc -nostartfiles -Wl,-Map,<TARGET>.map -Wl,--start-group <OBJECTS> <LINK_LIBRARIES> -Wl,--end-group -o <TARGET>")
