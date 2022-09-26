#!/usr/bin/env bash

ARG=$1
CC=nvc
CXX=nvc++

if [[ $ARG == "clean" ]]
then
  rm -v cublas_dgemm_mwe
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
  cublas_dgemm_mwe.c \
  -o cublas_dgemm_mwe
fi
