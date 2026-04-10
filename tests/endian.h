/*
 * Minimal endian.h shim for bare-metal RISC-V builds (riscv64-unknown-elf).
 * Newlib does not ship endian.h; stm-arm-neon-ref.h needs __BYTE_ORDER and
 * the __LITTLE_ENDIAN / __BIG_ENDIAN constants.  RISC-V is always LE.
 */
#ifndef _ENDIAN_H
#define _ENDIAN_H

#define __LITTLE_ENDIAN 1234
#define __BIG_ENDIAN    4321
#define __PDP_ENDIAN    3412
#define __BYTE_ORDER    __LITTLE_ENDIAN

#endif /* _ENDIAN_H */
