cmake_minimum_required(VERSION 3.22)
project(untitled3 C)

set(CMAKE_C_STANDARD 23)

add_executable(untitled3 Card/card.h Terminal/terminal.h Server/server.h Application/app.h Application/app.c Card/card.c Terminal/terminal.c Server/server.c top.h)
