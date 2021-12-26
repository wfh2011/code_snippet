cmake_minimum_required(VERSION 3.20)
project(LinuxList C)

set(CMAKE_C_STANDARD 99)

add_executable(LinuxList main.c sds.c)
