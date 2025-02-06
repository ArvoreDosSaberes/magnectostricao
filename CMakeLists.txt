# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)


set(PROJECT_NAME magnectostriccao)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(FREERTOS_KERNEL_PATH "${CMAKE_SOURCE_DIR}/FreeRTOS-Kernel" CACHE STRING "Path to the FreeRTOS Kernel")
set(FREERTOS_CONFIG_FILE_DIRECTORY "${CMAKE_SOURCE_DIR}/tasks/" CACHE STRING "") 

# Select the heap port.  values between 1-4 will pick a heap.
set(FREERTOS_HEAP "4" CACHE STRING "" FORCE)

#Select the native compile PORT
#set(FREERTOS_PORT "GCC_ARM_CM0" CACHE STRING "" FORCE)
#set(FREERTOS_PORT "GCC_RP2040" CACHE STRING "" FORCE)
#set(FREERTOS_PORT "ThirdParty_GCC_RP2040" CACHE STRING "" FORCE)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(${PROJECT_NAME} C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(${PROJECT_NAME} main.c  
        inc/neopixel.c
        inc/ssd1306_i2c.c
        tasks/freeRTOS_helpers.c
        tasks/task_drone_control.c
        tasks/task_adc_with_dma.c
        tasks/task_tinyML.c 
)

pico_set_program_name(${PROJECT_NAME} "magnectostriccao")
pico_set_program_version(${PROJECT_NAME} "0.1")

# Generate PIO header
pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/inc/ws2818b.pio)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(${PROJECT_NAME} 1)
pico_enable_stdio_usb(${PROJECT_NAME} 1)

# Add the standard include files to the build
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

include_directories(${INCLUDES})

# Add the freertos_config for FreeRTOS-Kernel
add_library(freertos_config INTERFACE)

target_include_directories(freertos_config
    INTERFACE
    "./tasks"
)
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

target_link_libraries(${PROJECT_NAME} 
    FreeRTOS-Kernel
    FreeRTOS-Kernel-Heap4
    hardware_i2c
    hardware_adc
    hardware_dma
    hardware_pio
    hardware_timer
    hardware_watchdog
    hardware_clocks
    pico_cyw43_arch_lwip_threadsafe_background
    pico_stdlib 
)
target_compile_definitions(${PROJECT_NAME}  PRIVATE
        mainRUN_FREE_RTOS_ON_CORE=1
        PICO_STACK_SIZE=0x1000
)

pico_add_extra_outputs(${PROJECT_NAME})