cmake_minimum_required(VERSION 3.27)
project(HW4 C)

set(CMAKE_C_STANDARD 99)

include_directories(src)

set(signal_processing_sources
        src/filter.c
        src/filter.h
        src/resample.c
        src/resample.h)

add_library(signal_processing ${signal_processing_sources})

add_library(wav_file
        src/wav_file.c)

add_executable(HW4
        main.c
        src/test.c)

target_link_libraries(HW4 wav_file signal_processing m)
