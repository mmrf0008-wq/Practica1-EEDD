cmake_minimum_required(VERSION 3.29)
project(Practica1_EEDD)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Practica1_EEDD
        main.cpp
        Especie.cpp
        Especie.h
        VDinamico.h
        LectorCSV.cpp
)
