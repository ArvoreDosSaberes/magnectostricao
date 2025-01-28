# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(MODEL_FOLDER .)
set(EI_SDK_FOLDER edge-impulse-sdk)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(magnectostriccao C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(magnectostriccao main.c 
        inc/ssd1306_i2c.c
#        inc/ei_classifier_porting.cpp
)


pico_set_program_name(magnectostriccao "magnectostriccao")
pico_set_program_version(magnectostriccao "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(magnectostriccao 0)
pico_enable_stdio_usb(magnectostriccao 1)

pico_add_extra_outputs(magnectostriccao)

# Generate PIO header
pico_generate_pio_header(magnectostriccao ${CMAKE_CURRENT_LIST_DIR}/inc/ws2818b.pio)

# Add the standard library to the build
target_link_libraries(magnectostriccao
        pico_stdlib
        )

# Add the standard include files to the build
target_include_directories(magnectostriccao PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)

include_directories(${INCLUDES})
#include_directories(include)

target_link_libraries(magnectostriccao
        hardware_i2c
        hardware_dma
        hardware_timer
        hardware_adc
        hardware_pio
        hardware_clocks
        )

target_link_libraries(magnectostriccao
        pico_cyw43_arch_lwip_threadsafe_background
#        pico_cyw43_arch_none
#        pico_cyw43_arch_lwip_threadsafe_background
        )

pico_add_extra_outputs(magnectostriccao)

