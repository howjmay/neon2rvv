# neon2rvv

A C/C++ header file that converts Arm/Aarch64 NEON intrinsics to RISC-V Vector (RVV) Extension.

## Introduction

neon2rvv is a translator of Arm/Aarch64 NEON intrinsics to RISC-V Vector (RVV) Extension, shortening the time needed to get an RISCV working program that then can be used to extract profiles and to identify hot paths in the code. The header file `neon2rvv.h` contains several of the functions provided by NEON intrinsic header, `<arm_neon.h>`, only implemented with RISCV-based counterparts to produce the exact semantics of the intrinsics.

## Usage

* Put the file `neon2rvv.h` in to your source code directory.
* Replace the header file `arm_neon.h` with `neon2rvv.h`.

    ```c
    #include "neon2rvv.h"
    ```

* Explicitly specify platform-specific options to gcc/clang compilers

    ```shell
    -march=rv64gcv_zba
    ```

### Targets and Limitations

The preliminary stage development goal of neon2rvv is targeting RV64 architecture with 128 bits vector register size, which means the implementation is compiled with `-march=rv64gcv_zba` flag.

We are using [RISC-V GNU Compiler Toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain) for development.

## Development

### Run Tests

`neon2rvv` provides a unified interface for developing test cases. These test cases are located in `tests` directory, and the input data is specified at runtime. Use the following commands to perform test cases:

You can run the tests under the architecture of your current machine. This can help you verify the implementation of tests case if you run the tests on ARM machines.

```shell
$ make test
```

You can specify GNU toolchain for cross compilation as well. For simulator, RISC-V ISA Simulator, [Spike](https://github.com/riscv-software-src/riscv-isa-sim) is used in default.

```shell
$ make CROSS_COMPILE=riscv64-unknown-elf- check # rv64
```

For developers who wants to run the cross-compiled tests with [qemu-riscv64](https://www.qemu.org/), you can specify QEMU with following command.

```shell
$ make CROSS_COMPILE=riscv64-unknown-elf- SIMULATOR_TYPE=qemu test
```

## Official Documents

* [riscv-v-spec](https://github.com/riscv/riscv-v-spec)
* [rvv-intrinsic-doc](https://github.com/riscv-non-isa/rvv-intrinsic-doc)
* [riscv-c-api](https://github.com/riscv-non-isa/riscv-c-api-doc/blob/master/riscv-c-api.md)
* [NEON Intrinsics](https://developer.arm.com/architectures/instruction-sets/intrinsics)
* Coding for Neon:
  * [Part 1: Load and Stores](https://community.arm.com/arm-community-blogs/b/architectures-and-processors-blog/posts/coding-for-neon---part-1-load-and-stores)
  * [Part 2: Dealing With Leftovers](https://community.arm.com/arm-community-blogs/b/architectures-and-processors-blog/posts/coding-for-neon---part-2-dealing-with-leftovers)
  * [Part 3: Matrix Multiplication](https://community.arm.com/arm-community-blogs/b/architectures-and-processors-blog/posts/coding-for-neon---part-3-matrix-multiplication)
  * [Part 4: Shifting Left and Right](https://community.arm.com/arm-community-blogs/b/architectures-and-processors-blog/posts/coding-for-neon---part-4-shifting-left-and-right)
  * [Part 5: Rearranging Vectors](https://community.arm.com/arm-community-blogs/b/architectures-and-processors-blog/posts/coding-for-neon---part-5-rearranging-vectors)

## References

* [sse2neon](https://github.com/DLTcollab/sse2neon)
* [rvv_example](https://github.com/brucehoult/rvv_example)
