cmake_minimum_required(VERSION 3.26)
project(P5)

set(CMAKE_CXX_STANDARD 17)

add_executable(P5 main.cpp
        PaMedicamento.cpp
        PaMedicamento.h
        MediExpress.cpp
        MediExpress.h
        Laboratorio.cpp
        Laboratorio.h
        Farmacia.cpp
        Farmacia.h
        Stock.cpp
        Stock.h
        ThashMedicam.cpp
        ThashMedicam.h)
