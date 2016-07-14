add_library(cortexm_common STATIC 
    atomic_arch.c
    cortexm_init.c  
    irq_arch.c
    panic.c
    reboot_arch.c
    thread_arch.c
    vectors_cortexm.c)
target_include_directories(cortexm_common PUBLIC include)
# We  add newlib_syscalls_default here to skip repeating this for all the cortex mcus
target_link_libraries(cortexm_common PUBLIC board cpu newlib_syscalls_default -L${CMAKE_CURRENT_SOURCE_DIR}/ldscripts)
target_compile_definitions(cortexm_common PUBLIC COREIF_NG MODULE_CORTEXM_COMMON)

