cmake_minimum_required(VERSION 3.22)
project(tai_assignment2_group8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -O3")

add_executable(was_chatted src/was_chatted.cpp
        src/util/program_arguments.cpp
        src/util/program_arguments.h
        src/markov/markov_model.h
        src/util/file_reader.h
        src/util/file_reader.cpp
        src/markov/markov_model.cpp
        src/markov/markov_analyser.cpp
        src/markov/markov_analyser.h)
