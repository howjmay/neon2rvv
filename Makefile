ifndef CC
override CC = gcc
endif

ifndef CXX
override CXX = g++
endif

ifndef CROSS_COMPILE
    processor := $(shell uname -m)
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
    tests/impl.o \
    tests/main.o
deps := $(OBJS:%.o=%.o.d)

.SUFFIXES: .o .cpp
.cpp.o:
	$(CXX) -o $@ $(CXXFLAGS) -c -MMD -MF $@.d $<

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

.PHONY: clean check format

clean:
	$(RM) $(OBJS) $(EXEC) $(deps) neon2rvv.h.gch

clean-all: clean
	$(RM) *.log

-include $(deps)
