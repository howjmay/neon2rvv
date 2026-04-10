/*
 * Empty stubs for the non-NEON (integer/DSP) test functions declared in
 * arm-neon-tests/compute_ref.c.  Those functions are only meaningful when
 * running on an ARM RVCT toolchain; neon2rvv does not implement them so we
 * provide no-op definitions to satisfy the linker when targeting RISC-V.
 */
void exec_integer(void) {}
void exec_dsp(void) {}
void exec_dspfns(void) {}
