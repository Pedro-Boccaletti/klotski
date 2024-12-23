cmake_minimum_required(VERSION 3.22)
project(labProg C)

set(CMAKE_C_STANDARD 99)

add_executable(labProg main.c
        matrix.c
        matrix.h
        test.c)
