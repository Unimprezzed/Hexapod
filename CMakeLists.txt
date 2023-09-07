cmake_minimum_required(VERSION 3.12)

# Change your executable name to something creative!
set(NAME pico-hexapod) 

include(pimoroni_pico_import.cmake)
include(pico_sdk_import.cmake)

# Gooey boilerplate
project(${NAME} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

#Include libraries
add_subdirectory(lib) #Implemented in full


# Add your source files
add_executable(${NAME}
    main.cpp # <-- Add source files here!
)

# Include required libraries
# This assumes `pimoroni-pico` is stored alongside your project
#Includes a work-around for weirdness in the original CMake project
include(drivers/analog/analog)
include(drivers/analogmux/analogmux)
include(drivers/button/button)
include(drivers/plasma/plasma)
include(drivers/servo/servo)
include(drivers/servo/servo_cluster)
include(drivers/pwm/pwm)
include(drivers/pwm/pwm_cluster)
include(libraries/servo2040/servo2040)


# Don't forget to link the libraries you need!
target_link_libraries(${NAME}
    vecmath
    pico_stdlib
    servo2040
    analogmux
    analog
    button
)

# enable usb output, disable uart output (so it doesn't confuse any connected servos)
pico_enable_stdio_usb(${NAME} 1)
pico_enable_stdio_uart(${NAME} 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(${NAME})

# Set up files for the release packages
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${NAME}.uf2
    ${CMAKE_CURRENT_LIST_DIR}/README.md
    DESTINATION .
)

set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_GENERATOR "ZIP" "TGZ")
include(CPack)

