/*
 * Shim header used by the arm-neon-tests suite when building on non-ARM
 * platforms.  Redirect to neon2rvv so the test harness exercises our RVV
 * implementation rather than native ARM NEON.
 */
#include "../neon2rvv.h"

#if defined(__riscv) || defined(__riscv__)
/*
 * The arm-neon-tests reference header (stm-arm-neon-ref.h) contains an
 * ARM-specific inline assembly block guarded by #ifndef STM_ARM_NEON_MODELS
 * that reads FPSCR via `vmrs` to detect the QC (saturation) flag.  On
 * RISC-V we can't emit that instruction, so we define STM_ARM_NEON_MODELS
 * to suppress that block and provide our own implementation using the
 * RISC-V vxsat CSR (which is set by saturating vector instructions).
 */
#define STM_ARM_NEON_MODELS 1

#include <stdint.h>

/* Union matching the layout expected by the test harness. */
typedef union {
  struct {
    int _xxx : 27;
    unsigned int QC : 1;
    int V : 1;
    int C : 1;
    int Z : 1;
    int N : 1;
  } b;
  unsigned int word;
} _ARM_FPSCR;

/*
 * Read the RISC-V vxsat CSR (bit 0 = saturation flag).
 * Returns non-zero when any saturating operation has set the flag.
 */
static inline int __riscv_read_neon_sat(void) {
  unsigned long r;
  __asm__ volatile("csrr %0, vxsat" : "=r"(r));
  return (int)(r & 1u);
}

/*
 * Write the RISC-V vxsat CSR.
 */
static inline void __riscv_write_neon_sat(int val) {
  unsigned long v = (unsigned long)(unsigned int)val;
  __asm__ volatile("csrw vxsat, %0" : : "r"(v));
}

#define Neon_Cumulative_Sat __riscv_read_neon_sat()
#define Set_Neon_Cumulative_Sat(x, depend) \
  do {                                     \
    (void)(depend);                        \
    __riscv_write_neon_sat(x);             \
  } while (0)

#endif /* __riscv */
