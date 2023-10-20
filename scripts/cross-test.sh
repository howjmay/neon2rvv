#!/usr/bin/env bash

# Clang/LLVM is natively a cross-compiler.
# TODO: Do cross-compilation using Clang
# https://clang.llvm.org/docs/CrossCompilation.html
if [ $(printenv CXX | grep clang) ]; then
    exit
fi

set -x

make clean
make CROSS_COMPILE=riscv64-unknown-elf- SIMULATOR_TYPE=$1 test || exit 1 # riscv64

# make clean
# make CROSS_COMPILE=riscv32-unknown-elf- test || exit 1 # riscv32
