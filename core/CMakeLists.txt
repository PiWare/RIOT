add_library(core STATIC
    atomic.c
    bitarithm.c
    c11_atomic.c
    kernel_init.c
    lifo.c
    msg.c
    mutex.c
    panic.c
    priority_queue.c
    ringbuffer.c
    sched.c
    thread.c
    thread_flags.c)

target_include_directories(core PUBLIC include)
target_link_libraries(core PRIVATE board)
target_compile_options(core PUBLIC "-std=c11")
