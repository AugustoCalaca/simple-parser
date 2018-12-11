cmake_minimum_required(VERSION 3.4)
project(compiler)
add_executable(main main.cpp parser.h parser.cpp lexicon.h lexicon.cpp token.h token.cpp)