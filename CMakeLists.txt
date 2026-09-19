cmake_minimum_required(VERSION 3.29)
project(Practica1_EEDD)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Practica1_EEDD
    LectorCSV.cpp
    LectorCSV.h
    main.cpp
        Especie.cpp
        VDinamico.h
)
