cmake_minimum_required(VERSION 3.6)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

project(RIOT C)

#Get the current git branch and hash

# Get the current working branch
execute_process(
  COMMAND git rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the latest abbreviated commit hash of the working branch
execute_process(
  COMMAND git log -1 --format=%h
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

add_definitions(-DRIOT_VERSION="${GIT_COMMIT_HASH}-${GIT_BRANCH}")

include_directories(
    drivers/include
    sys/include)
#for now just set the board here

set(BOARD stm32f0discovery)

add_subdirectory(boards/${BOARD})
add_subdirectory(cpu/${CPU})

foreach(additional_dir IN LISTS additional_cpu_dir)
add_subdirectory(${additional_dir})
endforeach()

add_subdirectory(core)
add_subdirectory(sys)
add_subdirectory(examples)
