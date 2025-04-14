cmake_minimum_required(VERSION 3.30)

project(snow_globe C)

# specify source files
set(SOURCE
        src/main.c 
        src/snow_globe.c
)

# specify header files
set(HEADER 
        src/snow_globe.h
)

# adding preprocessor definitions
add_definitions(-DNCURSES_STATIC)

# adding executable
add_executable(snow_globe ${SOURCE} ${HEADER})

# linking executable with ncurses library
target_link_libraries(snow_globe ncurses)
