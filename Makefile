ifndef CC
override CC = gcc
endif

ifndef CXX
override CXX = g++
endif

ifndef ENABLE_TEST_ALL
	DEFINED_FLAGS =
else
	DEFINED_FLAGS = -DENABLE_TEST_ALL
endif

ifndef CROSS_COMPILE
    processor := $(shell uname -m)
	ARCH_CFLAGS = -march=armv8.4-a+simd+i8mm+dotprod+sha3
else # CROSS_COMPILE was set
    CC = $(CROSS_COMPILE)gcc
    CXX = $(CROSS_COMPILE)g++
    CXXFLAGS += -static
    LDFLAGS += -static

    check_riscv := $(shell echo | $(CROSS_COMPILE)cpp -dM - | grep " __riscv_xlen " | cut -c22-)
    uname_result := $(shell uname -m)
	ifeq ($(check_riscv),64)
		processor = rv64
    else ifeq ($(uname_result),rv64imafdc)
		processor = rv64
    else ifeq ($(check_riscv),32)
		processor = rv32
    else ifeq ($(uname_result),rv32i)
		processor = rv32
	else
		$(error Unsupported cross-compiler)
	endif

	ARCH_CFLAGS = -march=$(processor)gcv_zba

	ifeq ($(SIMULATOR_TYPE), qemu)
		SIMULATOR += qemu-riscv64
		SIMULATOR_FLAGS = -cpu $(processor),v=true,zba=true,vlen=128
	else
		SIMULATOR = spike
		SIMULATOR_FLAGS = --isa=$(processor)gcv_zba
		PROXY_KERNEL = pk
	endif
endif

CXXFLAGS += -Wall -Wcast-qual -I. $(ARCH_CFLAGS)
LDFLAGS	+= -lm
OBJS = \
	tests/binding.o \
	tests/common.o \
	tests/debug_tools.o \
	tests/impl.o \
	tests/main.o
deps := $(OBJS:%.o=%.o.d)

.SUFFIXES: .o .cpp
.cpp.o:
	$(CXX) -o $@ $(CXXFLAGS) $(DEFINED_FLAGS) -c -MMD -MF $@.d $<

EXEC = tests/main

$(EXEC): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

test: tests/main
ifeq ($(processor),$(filter $(processor),rv32 rv64))
	$(CC) $(ARCH_CFLAGS) -c neon2rvv.h
endif
	$(SIMULATOR) $(SIMULATOR_FLAGS) $(PROXY_KERNEL) $^

build-test: tests/main
ifeq ($(processor),$(filter $(processor),rv32 rv64))
	$(CC) $(ARCH_CFLAGS) -c neon2rvv.h
endif

format:
	@echo "Formatting files with clang-format.."
	@if ! hash clang-format; then echo "clang-format is required to indent"; fi
	clang-format -i neon2rvv.h tests/*.cpp tests/*.h

# ── arm-neon-tests integration ──────────────────────────────────────────────
# Tests from https://github.com/christophe-lyon/arm-neon-tests compiled
# against neon2rvv and compared with the upstream reference output.
ANT_DIR = tests/arm-neon-tests

# All ref_*.c files except the non-NEON (integer/DSP) ones not covered by
# neon2rvv. Those are replaced by empty stubs in tests/neon_stubs.c.
ANT_SRCS := $(filter-out \
	$(ANT_DIR)/ref_integer.c \
	$(ANT_DIR)/ref_dsp.c \
	$(ANT_DIR)/ref_dspfns.c, \
	$(wildcard $(ANT_DIR)/ref_*.c))

ANT_CFLAGS  = -Wall -Wno-unused-variable -Wno-unused-function \
              -ffast-math $(ARCH_CFLAGS) \
              -I. -Itests -I$(ANT_DIR)
ANT_REFFILE     = neon2rvv-neon-ref.txt
ANT_GCCTESTFILE = neon2rvv-gcc-tests.txt
ANT_EXEC        = tests/arm-neon-tests-main

$(ANT_EXEC): $(ANT_SRCS) tests/neon_stubs.c
	$(CC) $(ANT_CFLAGS) -static \
	    -DREFFILE=\"$(ANT_REFFILE)\" \
	    -DGCCTESTS_FILE=\"$(ANT_GCCTESTFILE)\" \
	    -o $@ \
	    $(ANT_DIR)/compute_ref.c $(ANT_SRCS) tests/neon_stubs.c -lm

# Build only (no run) – useful to verify the code compiles on RISC-V.
build-arm-neon-tests: $(ANT_EXEC)

# Build, run, and diff against the upstream reference.
check-arm-neon-tests: $(ANT_EXEC)
	$(SIMULATOR) $(SIMULATOR_FLAGS) $(PROXY_KERNEL) $<
	diff $(ANT_REFFILE) $(ANT_DIR)/ref-rvct-neon-nofp16.txt

.PHONY: clean check format build-arm-neon-tests check-arm-neon-tests

clean:
	$(RM) $(OBJS) $(EXEC) $(deps) neon2rvv.h.gch
	$(RM) $(ANT_EXEC) $(ANT_REFFILE) $(ANT_GCCTESTFILE)

clean-all: clean
	$(RM) *.log

-include $(deps)
