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
#Set the current RIOT version from the GIT version
add_definitions(-DRIOT_VERSION="${GIT_COMMIT_HASH}-${GIT_BRANCH}")

# add the main interface include directories needed throughout the project
include_directories(
    drivers/include
    sys/include
    core/include)

#for now just set the board here
#set(BOARD stm32f0discovery)
set(BOARD nucleo-f103)
#set(BOARD nrf52dk)

# include the board specified
add_subdirectory(boards/${BOARD})
# next comes the cpu support
add_subdirectory(cpu)
# the core and system libraries
add_subdirectory(core)
add_subdirectory(sys)
# last the applications
add_subdirectory(examples)
