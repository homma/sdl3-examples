#!/bin/sh -x

SDL3_INC="-I$(brew --prefix sdl3)/include"
SDL3_LIB="-L$(brew --prefix sdl3)/lib -lSDL3"
SDL3_OPT="${SDL3_INC} ${SDL3_LIB}"

CXX_OPT="-std=c++2c"

c++ main.cpp -o sdl_renderer_draw_test ${CXX_OPT} ${SDL3_OPT}
