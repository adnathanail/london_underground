cmake_minimum_required(VERSION 3.17)
project(london_underground C)

set(CMAKE_C_STANDARD 99)

add_executable(london_underground
    main.c
    data/data.c
    data/data.h
    libs/data_types.h
    libs/data_proc.c
    libs/data_proc.h
    libs/data_structures.c
    libs/data_structures.h
    libs/user_interaction.c
    libs/user_interaction.h
)