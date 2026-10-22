cmake_minimum_required(VERSION 4.3)
project(C_projects C)

set(CMAKE_C_STANDARD 17)

add_executable(C_projects main.c
        header/Question.h
        source/Question.c
        header/Question_types.h
        header/get_key.h
        source/get_key.c)


target_compile_options(C_projects PRIVATE
        -fsanitize=address
        -fno-omit-frame-pointer
        -g
)

target_link_options(C_projects PRIVATE
        -fsanitize=address
)
