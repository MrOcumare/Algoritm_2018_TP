cmake_minimum_required(VERSION 3.12)
project(graphs)

set(CMAKE_CXX_STANDARD 17)

add_executable(graphs main.cpp IGraph.h IGraph.cpp CListGraph.h CListGraph.cpp CMatrixGraph.cpp CMatrixGraph.h CSetGraph.cpp CSetGraph.h CArcGraph.cpp CArcGraph.h Generator.cpp Generator.h)