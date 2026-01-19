#!/bin/sh -x

SDL3_OPT="$(pkg-config sdl3 --cflags-only-I --libs-only-L --libs-only-l)"
GLM_OPT="$(pkg-config glm --cflags-only-I)"
OPENGL_OPT="-framework OpenGL"
CXX_OPT="-std=c++2c"

c++ main.cpp -o sdl_opengl_2d_test ${CXX_OPT} ${SDL3_OPT} ${GLM_OPT} ${OPENGL_OPT}
