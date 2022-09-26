#!/usr/bin/env bash

ARG=$1
CC=nvc
CXX=nvc++

if [[ $ARG == "clean" ]]
then
  rm -v cusolver_determinant_mwe
else
  $CC \
  -I$NVHPC_ROOT/math_libs/include \
  -L$NVHPC_ROOT/math_libs/lib64 \
  -lpthread \
  -lm \
  -ldl \
  -lcublas \
  -lcusolver \
  -mp \
  -target=gpu \
  cusolver_determinant_mwe.c \
  -o cusolver_determinant_mwe
fi
