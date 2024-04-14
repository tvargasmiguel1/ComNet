cmake_minimum_required(VERSION 3.28)
project(ComNet C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(ComNet
        include/HTTP_Server.h
        include/Response.h
        include/Routes.h
        src/HTTP_Server.c
        src/main.c
        src/Response.c
        src/Routes.c)
