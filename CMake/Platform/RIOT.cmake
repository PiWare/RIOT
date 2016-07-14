set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS FALSE)

set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_SUFFIX ".a")
set(CMAKE_EXECUTABLE_SUFFIX ".elf")
set(CMAKE_C_OUTPUT_EXTENSION ".o")
set(CMAKE_ASM_OUTPUT_EXTENSION ".o")
set(CMAKE_CXX_OUTPUT_EXTENSION ".o")

set(CMAKE_EXE_LINKER_FLAGS_INIT "-static -lgcc -nostartfiles -Wl,--cref")
include_directories(SYSTEM /usr/include/newlib/nano)
set(CMAKE_C_FLAGS_INIT "-std=c11 -Wstrict-prototypes -Werror=strict-prototypes -Wold-style-definition -Werror=old-style-definition -Wall")
