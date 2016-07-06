set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS FALSE)

set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_SUFFIX ".a")
set(CMAKE_EXECUTABLE_SUFFIX "")
set(CMAKE_C_OUTPUT_EXTENSION ".o")
set(CMAKE_ASM_OUTPUT_EXTENSION ".o")
set(CMAKE_CXX_OUTPUT_EXTENSION ".o")

function(module name )
    set(options )
    set(oneValueArgs )
    set(multiValueArgs SOURCES REQUIRES)
    cmake_parse_arguments(module "${options}" "${oneValueArgs}"
                          "${multiValueArgs}" ${ARGN} )

                      add_library( ${name} STATIC ${module_SOURCES})
    target_include_directories( ${name} PUBLIC include)
    target_compile_definitions( ${name} PUBLIC "MODULE_$<UPPER_CASE:${name}>")
    if(NOT "${name}" STREQUAL "cpu")
        target_link_libraries( ${name} PRIVATE cpu)
    endif()
    if(NOT "${name}" STREQUAL "board")
        target_link_libraries( ${name} PRIVATE board)
    endif()
endfunction()

function(application name)
    set(options )
    set(oneValueArgs )
    set(multiValueArgs SOURCES REQUIRES)

    cmake_parse_arguments(app "${options}" "${oneValueArgs}"
                          "${multiValueArgs}" ${ARGN} )

    add_executable( ${name} ${app_SOURCES})
    target_link_libraries(${name} PUBLIC ${app_REQUIRES})
    get_property(libraries TARGET ${name} PROPERTY INTERFACE_LINK_LIBRARIES)
    message(STATUS "Lib: ${libraries}")
    foreach( lib IN LISTS libraries)
        message(STATUS "Lib: ${lib}")
    endforeach()
endfunction()
