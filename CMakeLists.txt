cmake_minimum_required(VERSION 3.27)
project(Mineswooper C)

set(CMAKE_C_STANDARD 11)

add_executable(Mineswooper src/main.c
        include/Game_State.h
        include/Cell.h
        src/Game_Logic.c
        include/Game_Logic.h
        include/Input_Processing.h
        src/Input_Processing.c
        include/Constants.h
        src/Utilities.c
        include/Utilities.h)
