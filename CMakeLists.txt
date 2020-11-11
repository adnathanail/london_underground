cmake_minimum_required(VERSION 3.17)
project(london_underground C)

set(CMAKE_C_STANDARD 99)

add_executable(london_underground
    data/data.c
    data/data.h
    src/main.c
    src/data_types.h
    src/data_proc.c
    src/data_proc.h
    src/data_structures.c
    src/data_structures.h
    src/user_interaction.c
    src/user_interaction.h
    src/xterm_codes.h
    src/utils.c
    src/utils.h
)