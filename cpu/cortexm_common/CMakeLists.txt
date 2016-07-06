module(cortexm_common SOURCES 
    atomic_arch.c
    cortexm_init.c  
    irq_arch.c
    panic.c
    reboot_arch.c
    thread_arch.c  
    vectors_cortexm.c)
target_link_libraries(cortexm_common PUBLIC board cpu core newlib_syscalls)
target_compile_definitions(cortexm_common PUBLIC COREIF_NG)
get_property(APPLICATION_LINK_FLAGS TARGET cpu PROPERTY APPLICATION_LINK_FLAGS)
set_property(TARGET cpu PROPERTY APPLICATION_LINK_FLAGS "-L${CMAKE_CURRENT_SOURCE_DIR}/ldscripts ${APPLICATION_LINK_FLAGS}")
#add_library(cortexm_common atomic_arch.c  cortexm_init.c  irq_arch.c  panic.c  reboot_arch.c  thread_arch.c  vectors_cortexm.c)
#target_include_directories(cortexm_common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
