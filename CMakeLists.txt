cmake_minimum_required(VERSION 3.24)
project(Labor C)

set(CMAKE_C_STANDARD 11)

add_executable(rand_seq
        01/rand_seq.c)

add_executable(double_num
        01/double_num.c)

add_executable(reverse_str
        01/reverse_str.c)

add_executable(linked_list
        02_linked_list/main.c)
