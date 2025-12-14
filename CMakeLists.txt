#
# CMakeLists.txt
#
#  Created on: 13 dec. 2025
#      Author: Ludo
#

# Minimum CMake version.
cmake_minimum_required(VERSION 3.23)

# Project creation.
project(stm32l0xx-device)

# Build mode.
if(NOT DEFINED BUILD_MODE)
    set(BUILD_MODE "STATIC")
endif()

# Create library.
add_library(${PROJECT_NAME} ${BUILD_MODE})

# Static library.
if(${BUILD_MODE} STREQUAL STATIC)

    # Hardware specific settings.
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=cortex-m0plus -O0")

    # Macro to convert options to variables.
    macro(add_compilation_flag FLAG_NAME FLAG_DESCRIPTION FLAG_DEFAULT_VALUE)
        option(FLAG_NAME FLAG_DESCRIPTION FLAG_DEFAULT_VALUE)
        set(${FLAG_NAME} ${FLAG_DEFAULT_VALUE} CACHE STRING ${FLAG_DESCRIPTION})
        list(APPEND COMPILATION_FLAGS_LIST ${FLAG_NAME})
    endmacro()
    
    # Compilation flags.
    add_compilation_flag(STM32L0XX_DEVICE_DISABLE "Disable the STM32L0xx device code." OFF)
    add_compilation_flag(STM32L0XX_DEVICE_STACK_SIZE "Size of the stack to reserve in RAM memory." 0x00000400)
    add_compilation_flag(STM32L0XX_DEVICE_HEAP_SIZE "Size of the heap to reserve in RAM memory." 0x00000C00)
    
    # Remove OFF flags from list and keep flags set to value 0.
    foreach(FLAG ${COMPILATION_FLAGS_LIST})
        if((NOT ${FLAG} STREQUAL OFF) AND (NOT ${FLAG} STREQUAL ON))
            set(${FLAG} "(${${FLAG}})")
        endif()
    endforeach()   
    
    # Create flags file.
    configure_file(stm32l0xx_device_flags.h.in stm32l0xx_device_flags.h @ONLY)
    
    # Dependencies folders.
    target_include_directories(${PROJECT_NAME}
        PUBLIC
            ${CMAKE_CURRENT_BINARY_DIR}
            ${TYPES_PATH}
    )
    
    # Print archive size.
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
        COMMAND ${CMAKE_SIZE_UTIL} -t lib${PROJECT_NAME}.a
    )
    
endif()

# Source files list.
target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/startup/stm32l0xx_startup.c
)