cmake_minimum_required(VERSION 3.23)
project(BPlusTree)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(BPlusTree
        BPlusTree.h
        BPlusTree.tpp
        FuncionesDeGestion.cpp
        FuncionesDeGestion.h
        main.cpp
        Utilerias.cpp
        Utilerias.h)
