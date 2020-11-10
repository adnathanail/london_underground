cmake_minimum_required(VERSION 3.17)
project(london_underground C)

set(CMAKE_C_STANDARD 99)

add_executable(london_underground
    main.c
    data/types.h
    data/data.c
    data/data.h
    data/data_proc.c
    data/data_proc.h
)