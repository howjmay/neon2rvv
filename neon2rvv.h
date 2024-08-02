/*
 * This header file provides a simple API translation layer
 * between Arm/Aarch64 NEON to their corresponding RVV intrinsics versions.
 *
 * neon2rvv is freely redistributable under the MIT License.
 *
 * MIT License
 *
 * Copyright (c) 2015-2024 NEON2RVV Contributors.
 *
 * Contributors to this work are:
 *    Yang Hau <yuanyanghau@gmail.com>
 *    Octavian Maghiar <octavian.maghiar@imgtec.com>
 *    Camel Coder <camel-cdr@protonmail.com>
 *    Yang Liu <numbksco@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef NEON2RVV_H
#define NEON2RVV_H

#ifdef __cplusplus
extern "C" {
#endif

// TODO uncomment this and put all the implementation into `#elif defined(__riscv) || defined(__riscv__)`
// In this way the developers only need to include `neon2rvv.h`
// #if (defined(__aarch64__) || defined(_M_ARM64)) || defined(__arm__)
// #include <arm_neon.h>
// #elif (defined(__riscv) || defined(__riscv__))
#include <riscv_vector.h>

#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma push_macro("FORCE_INLINE")
#pragma push_macro("ALIGN_STRUCT")
#define FORCE_INLINE static inline __attribute__((always_inline))
#define ALIGN_STRUCT(x) __attribute__((aligned(x)))
#define _neon2rvv_likely(x) __builtin_expect(!!(x), 1)
#define _neon2rvv_unlikely(x) __builtin_expect(!!(x), 0)
#endif

typedef float float32_t;
typedef double float64_t;

#if __riscv_v_min_vlen == 128 || __riscv_v_min_vlen == 256 || __riscv_v_min_vlen == 512
// 64bit width vector register
typedef vint8m1_t int8x8_t;
typedef vint16m1_t int16x4_t;
typedef vint32m1_t int32x2_t;
typedef vint64m1_t int64x1_t;
typedef vuint8m1_t uint8x8_t;
typedef vuint16m1_t uint16x4_t;
typedef vuint32m1_t uint32x2_t;
typedef vuint64m1_t uint64x1_t;
typedef vfloat32m1_t float32x2_t;
typedef vfloat64m1_t float64x1_t;
// 128bit width vector register
typedef vint8m1_t int8x16_t;
typedef vint16m1_t int16x8_t;
typedef vint32m1_t int32x4_t;
typedef vint64m1_t int64x2_t;
typedef vuint8m1_t uint8x16_t;
typedef vuint16m1_t uint16x8_t;
typedef vuint32m1_t uint32x4_t;
typedef vuint64m1_t uint64x2_t;
typedef vfloat32m1_t float32x4_t;
typedef vfloat64m1_t float64x2_t;

typedef vint8m1x2_t int8x8x2_t;
typedef vuint8m1x2_t uint8x8x2_t;
typedef vint8m1x3_t int8x8x3_t;
typedef vuint8m1x3_t uint8x8x3_t;
typedef vint8m1x4_t int8x8x4_t;
typedef vuint8m1x4_t uint8x8x4_t;
typedef vint8m1x2_t int8x16x2_t;
typedef vuint8m1x2_t uint8x16x2_t;
typedef vint8m1x3_t int8x16x3_t;
typedef vuint8m1x3_t uint8x16x3_t;
typedef vint8m1x4_t int8x16x4_t;
typedef vuint8m1x4_t uint8x16x4_t;
typedef vint16m1x2_t int16x4x2_t;
typedef vuint16m1x2_t uint16x4x2_t;
typedef vint16m1x3_t int16x4x3_t;
typedef vuint16m1x3_t uint16x4x3_t;
typedef vint16m1x4_t int16x4x4_t;
typedef vuint16m1x4_t uint16x4x4_t;
typedef vint16m1x2_t int16x8x2_t;
typedef vuint16m1x2_t uint16x8x2_t;
typedef vint16m1x3_t int16x8x3_t;
typedef vuint16m1x3_t uint16x8x3_t;
typedef vint16m1x4_t int16x8x4_t;
typedef vuint16m1x4_t uint16x8x4_t;
typedef vint32m1x2_t int32x2x2_t;
typedef vuint32m1x2_t uint32x2x2_t;
typedef vint32m1x3_t int32x2x3_t;
typedef vuint32m1x3_t uint32x2x3_t;
typedef vint32m1x4_t int32x2x4_t;
typedef vuint32m1x4_t uint32x2x4_t;
typedef vint32m1x2_t int32x4x2_t;
typedef vuint32m1x2_t uint32x4x2_t;
typedef vint32m1x3_t int32x4x3_t;
typedef vuint32m1x3_t uint32x4x3_t;
typedef vint32m1x4_t int32x4x4_t;
typedef vuint32m1x4_t uint32x4x4_t;
typedef vint64m1x2_t int64x1x2_t;
typedef vuint64m1x2_t uint64x1x2_t;
typedef vint64m1x3_t int64x1x3_t;
typedef vuint64m1x3_t uint64x1x3_t;
typedef vint64m1x4_t int64x1x4_t;
typedef vuint64m1x4_t uint64x1x4_t;
typedef vint64m1x2_t int64x2x2_t;
typedef vuint64m1x2_t uint64x2x2_t;
typedef vint64m1x3_t int64x2x3_t;
typedef vuint64m1x3_t uint64x2x3_t;
typedef vint64m1x4_t int64x2x4_t;
typedef vuint64m1x4_t uint64x2x4_t;
typedef vfloat32m1x2_t float32x2x2_t;
typedef vfloat32m1x3_t float32x2x3_t;
typedef vfloat32m1x4_t float32x2x4_t;
typedef vfloat32m1x2_t float32x4x2_t;
typedef vfloat32m1x3_t float32x4x3_t;
typedef vfloat32m1x4_t float32x4x4_t;
typedef vfloat64m1x2_t float64x1x2_t;
typedef vfloat64m1x3_t float64x1x3_t;
typedef vfloat64m1x4_t float64x1x4_t;
typedef vfloat64m1x2_t float64x2x2_t;
typedef vfloat64m1x3_t float64x2x3_t;
typedef vfloat64m1x4_t float64x2x4_t;
#else
#error unsupported vlen
#endif

// XRM
// #define __RISCV_VXRM_RNU 0  // round-to-nearest-up (add +0.5 LSB)
// #define __RISCV_VXRM_RNE 1  // round-to-nearest-even
// #define __RISCV_VXRM_RDN 2  // round-down (truncate)
// #define __RISCV_VXRM_ROD 3  // round-to-odd (OR bits into LSB, aka "jam")
// FRM
// #define __RISCV_FRM_RNE 0  // round to nearest, ties to even
// #define __RISCV_FRM_RTZ 1  // round towards zero
// #define __RISCV_FRM_RDN 2  // round down (towards -infinity)
// #define __RISCV_FRM_RUP 3  // round up (towards +infinity)
// #define __RISCV_FRM_RMM 4  // round to nearest, ties to max magnitude

static inline int8_t neon2rvv_saturate_int8(int a) {
  if (a > INT8_MAX)
    return (int8_t)INT8_MAX;
  if (a < INT8_MIN)
    return (int8_t)INT8_MIN;
  return (int8_t)a;
}
static inline uint8_t neon2rvv_saturate_uint8(int a) {
  if (a > UINT8_MAX) {
    return (uint8_t)UINT8_MAX;
  } else if (a < 0) {
    return 0;
  }
  return (uint8_t)a;
}
static inline int16_t neon2rvv_saturate_int16(int a) {
  if (a > INT16_MAX)
    return (int16_t)INT16_MAX;
  if (a < INT16_MIN)
    return (int16_t)INT16_MIN;
  return (int16_t)a;
}
static inline uint16_t neon2rvv_saturate_uint16(int a) {
  if (a > UINT16_MAX) {
    return (uint16_t)UINT16_MAX;
  } else if (a < 0) {
    return 0;
  }
  return a;
}
static inline int32_t neon2rvv_saturate_int32(int64_t a) {
  if (a > INT32_MAX)
    return (int32_t)INT32_MAX;
  if (a < INT32_MIN)
    return (int32_t)INT32_MIN;
  return (int32_t)a;
}
static inline uint32_t neon2rvv_saturate_uint32(uint64_t a) {
  if (a > UINT32_MAX) {
    return (uint32_t)UINT32_MAX;
  } else if (a < 0) {
    return 0;
  }
  return a;
}

// forward declaration
// FIXME vdup_n_* will be removed if the __riscv_vmv_* errors are fixed
FORCE_INLINE int8x8_t vdup_n_s8(int8_t a);
FORCE_INLINE int16x4_t vdup_n_s16(int16_t a);
FORCE_INLINE int32x2_t vdup_n_s32(int32_t a);
FORCE_INLINE float32x2_t vdup_n_f32(float32_t a);
FORCE_INLINE float64x1_t vdup_n_f64(float64_t a);
FORCE_INLINE float64x2_t vdupq_n_f64(float64_t a);
FORCE_INLINE uint8x8_t vdup_n_u8(uint8_t a);
FORCE_INLINE uint16x4_t vdup_n_u16(uint16_t a);
FORCE_INLINE uint32x2_t vdup_n_u32(uint32_t a);
FORCE_INLINE int64x1_t vdup_n_s64(int64_t a);
FORCE_INLINE uint64x1_t vdup_n_u64(uint64_t a);
FORCE_INLINE int8x16_t vdupq_n_s8(int8_t a);
FORCE_INLINE int16x8_t vdupq_n_s16(int16_t a);
FORCE_INLINE int32x4_t vdupq_n_s32(int32_t a);
FORCE_INLINE float32x4_t vdupq_n_f32(float32_t a);
FORCE_INLINE uint8x16_t vdupq_n_u8(uint8_t a);
FORCE_INLINE uint16x8_t vdupq_n_u16(uint16_t a);
FORCE_INLINE uint32x4_t vdupq_n_u32(uint32_t a);
FORCE_INLINE int64x2_t vdupq_n_s64(int64_t a);
FORCE_INLINE uint64x2_t vdupq_n_u64(uint64_t a);

FORCE_INLINE int8x8_t vcnt_s8(int8x8_t a);
FORCE_INLINE uint8x8_t vcnt_u8(uint8x8_t a);

/* vadd */
FORCE_INLINE int8x8_t vadd_s8(int8x8_t a, int8x8_t b) { return __riscv_vadd_vv_i8m1(a, b, 8); }

FORCE_INLINE int16x4_t vadd_s16(int16x4_t a, int16x4_t b) { return __riscv_vadd_vv_i16m1(a, b, 4); }

FORCE_INLINE int32x2_t vadd_s32(int32x2_t a, int32x2_t b) { return __riscv_vadd_vv_i32m1(a, b, 2); }

FORCE_INLINE float32x2_t vadd_f32(float32x2_t a, float32x2_t b) { return __riscv_vfadd_vv_f32m1(a, b, 2); }

FORCE_INLINE uint8x8_t vadd_u8(uint8x8_t a, uint8x8_t b) { return __riscv_vadd_vv_u8m1(a, b, 8); }

FORCE_INLINE uint16x4_t vadd_u16(uint16x4_t a, uint16x4_t b) { return __riscv_vadd_vv_u16m1(a, b, 4); }

FORCE_INLINE uint32x2_t vadd_u32(uint32x2_t a, uint32x2_t b) { return __riscv_vadd_vv_u32m1(a, b, 2); }

FORCE_INLINE int64x1_t vadd_s64(int64x1_t a, int64x1_t b) { return __riscv_vadd_vv_i64m1(a, b, 2); }

FORCE_INLINE uint64x1_t vadd_u64(uint64x1_t a, uint64x1_t b) { return __riscv_vadd_vv_u64m1(a, b, 2); }

FORCE_INLINE int8x16_t vaddq_s8(int8x16_t a, int8x16_t b) { return __riscv_vadd_vv_i8m1(a, b, 16); }

FORCE_INLINE int16x8_t vaddq_s16(int16x8_t a, int16x8_t b) { return __riscv_vadd_vv_i16m1(a, b, 8); }

FORCE_INLINE int32x4_t vaddq_s32(int32x4_t a, int32x4_t b) { return __riscv_vadd_vv_i32m1(a, b, 4); }

FORCE_INLINE int64x2_t vaddq_s64(int64x2_t a, int64x2_t b) { return __riscv_vadd_vv_i64m1(a, b, 2); }

FORCE_INLINE float32x4_t vaddq_f32(float32x4_t a, float32x4_t b) { return __riscv_vfadd_vv_f32m1(a, b, 4); }

FORCE_INLINE float64x1_t vadd_f64(float64x1_t a, float64x1_t b) { return __riscv_vfadd_vv_f64m1(a, b, 1); }

FORCE_INLINE float64x2_t vaddq_f64(float64x2_t a, float64x2_t b) { return __riscv_vfadd_vv_f64m1(a, b, 2); }

FORCE_INLINE int64_t vaddd_s64(int64_t a, int64_t b) { return a + b; }

FORCE_INLINE uint64_t vaddd_u64(uint64_t a, uint64_t b) { return a + b; }

FORCE_INLINE uint8x16_t vaddq_u8(uint8x16_t a, uint8x16_t b) { return __riscv_vadd_vv_u8m1(a, b, 16); }

FORCE_INLINE uint16x8_t vaddq_u16(uint16x8_t a, uint16x8_t b) { return __riscv_vadd_vv_u16m1(a, b, 8); }

FORCE_INLINE uint32x4_t vaddq_u32(uint32x4_t a, uint32x4_t b) { return __riscv_vadd_vv_u32m1(a, b, 4); }

FORCE_INLINE uint64x2_t vaddq_u64(uint64x2_t a, uint64x2_t b) { return __riscv_vadd_vv_u64m1(a, b, 2); }

FORCE_INLINE int16x8_t vaddl_s8(int8x8_t a, int8x8_t b) {
  return __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vwadd_vv_i16m2(a, b, 8));
}

FORCE_INLINE int32x4_t vaddl_s16(int16x4_t a, int16x4_t b) {
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwadd_vv_i32m2(a, b, 4));
}

FORCE_INLINE int64x2_t vaddl_s32(int32x2_t a, int32x2_t b) {
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwadd_vv_i64m2(a, b, 2));
}

FORCE_INLINE uint16x8_t vaddl_u8(uint8x8_t a, uint8x8_t b) {
  return __riscv_vlmul_trunc_v_u16m2_u16m1(__riscv_vwaddu_vv_u16m2(a, b, 8));
}

FORCE_INLINE uint32x4_t vaddl_u16(uint16x4_t a, uint16x4_t b) {
  return __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwaddu_vv_u32m2(a, b, 4));
}

FORCE_INLINE uint64x2_t vaddl_u32(uint32x2_t a, uint32x2_t b) {
  return __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwaddu_vv_u64m2(a, b, 2));
}

FORCE_INLINE int16x8_t vaddl_high_s8(int8x16_t a, int8x16_t b) {
  vint8m1_t a_high = __riscv_vslidedown_vx_i8m1(a, 8, 16);
  vint8m1_t b_high = __riscv_vslidedown_vx_i8m1(b, 8, 16);
  return __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vwadd_vv_i16m2(a_high, b_high, 8));
}

FORCE_INLINE int32x4_t vaddl_high_s16(int16x8_t a, int16x8_t b) {
  vint16m1_t a_high = __riscv_vslidedown_vx_i16m1(a, 4, 8);
  vint16m1_t b_high = __riscv_vslidedown_vx_i16m1(b, 4, 8);
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwadd_vv_i32m2(a_high, b_high, 4));
}

FORCE_INLINE int64x2_t vaddl_high_s32(int32x4_t a, int32x4_t b) {
  vint32m1_t a_high = __riscv_vslidedown_vx_i32m1(a, 2, 4);
  vint32m1_t b_high = __riscv_vslidedown_vx_i32m1(b, 2, 4);
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwadd_vv_i64m2(a_high, b_high, 2));
}

FORCE_INLINE uint16x8_t vaddl_high_u8(uint8x16_t a, uint8x16_t b) {
  vuint8m1_t a_high = __riscv_vslidedown_vx_u8m1(a, 8, 16);
  vuint8m1_t b_high = __riscv_vslidedown_vx_u8m1(b, 8, 16);
  return __riscv_vlmul_trunc_v_u16m2_u16m1(__riscv_vwaddu_vv_u16m2(a_high, b_high, 8));
}

FORCE_INLINE uint32x4_t vaddl_high_u16(uint16x8_t a, uint16x8_t b) {
  vuint16m1_t a_high = __riscv_vslidedown_vx_u16m1(a, 4, 8);
  vuint16m1_t b_high = __riscv_vslidedown_vx_u16m1(b, 4, 8);
  return __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwaddu_vv_u32m2(a_high, b_high, 4));
}

FORCE_INLINE uint64x2_t vaddl_high_u32(uint32x4_t a, uint32x4_t b) {
  vuint32m1_t a_high = __riscv_vslidedown_vx_u32m1(a, 2, 4);
  vuint32m1_t b_high = __riscv_vslidedown_vx_u32m1(b, 2, 4);
  return __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwaddu_vv_u64m2(a_high, b_high, 2));
}

FORCE_INLINE int16x8_t vaddw_s8(int16x8_t a, int8x8_t b) {
  return __riscv_vwmacc_vx_i16m1(a, 1, __riscv_vlmul_trunc_v_i8m1_i8mf2(b), 8);
}

FORCE_INLINE int32x4_t vaddw_s16(int32x4_t a, int16x4_t b) {
  return __riscv_vwmacc_vx_i32m1(a, 1, __riscv_vlmul_trunc_v_i16m1_i16mf2(b), 4);
}

FORCE_INLINE int64x2_t vaddw_s32(int64x2_t a, int32x2_t b) {
  return __riscv_vwmacc_vx_i64m1(a, 1, __riscv_vlmul_trunc_v_i32m1_i32mf2(b), 2);
}

FORCE_INLINE uint16x8_t vaddw_u8(uint16x8_t a, uint8x8_t b) {
  return __riscv_vwmaccu_vx_u16m1(a, 1, __riscv_vlmul_trunc_v_u8m1_u8mf2(b), 8);
}

FORCE_INLINE uint32x4_t vaddw_u16(uint32x4_t a, uint16x4_t b) {
  return __riscv_vwmaccu_vx_u32m1(a, 1, __riscv_vlmul_trunc_v_u16m1_u16mf2(b), 4);
}

FORCE_INLINE uint64x2_t vaddw_u32(uint64x2_t a, uint32x2_t b) {
  return __riscv_vwmaccu_vx_u64m1(a, 1, __riscv_vlmul_trunc_v_u32m1_u32mf2(b), 2);
}

FORCE_INLINE int16x8_t vaddw_high_s8(int16x8_t a, int8x16_t b) {
  vint16m1_t b_ext = __riscv_vsext_vf2_i16m1(__riscv_vlmul_trunc_v_i8m1_i8mf2(__riscv_vslidedown_vx_i8m1(b, 8, 16)), 8);
  return __riscv_vadd_vv_i16m1(a, b_ext, 8);
}

FORCE_INLINE int32x4_t vaddw_high_s16(int32x4_t a, int16x8_t b) {
  vint32m1_t b_ext =
      __riscv_vsext_vf2_i32m1(__riscv_vlmul_trunc_v_i16m1_i16mf2(__riscv_vslidedown_vx_i16m1(b, 4, 8)), 4);
  return __riscv_vadd_vv_i32m1(a, b_ext, 4);
}

FORCE_INLINE int64x2_t vaddw_high_s32(int64x2_t a, int32x4_t b) {
  vint64m1_t b_ext =
      __riscv_vsext_vf2_i64m1(__riscv_vlmul_trunc_v_i32m1_i32mf2(__riscv_vslidedown_vx_i32m1(b, 2, 4)), 2);
  return __riscv_vadd_vv_i64m1(a, b_ext, 2);
}

FORCE_INLINE uint16x8_t vaddw_high_u8(uint16x8_t a, uint8x16_t b) {
  vuint16m1_t b_ext =
      __riscv_vzext_vf2_u16m1(__riscv_vlmul_trunc_v_u8m1_u8mf2(__riscv_vslidedown_vx_u8m1(b, 8, 16)), 8);
  return __riscv_vadd_vv_u16m1(a, b_ext, 8);
}

FORCE_INLINE uint32x4_t vaddw_high_u16(uint32x4_t a, uint16x8_t b) {
  vuint32m1_t b_ext =
      __riscv_vzext_vf2_u32m1(__riscv_vlmul_trunc_v_u16m1_u16mf2(__riscv_vslidedown_vx_u16m1(b, 4, 8)), 4);
  return __riscv_vadd_vv_u32m1(a, b_ext, 4);
}

FORCE_INLINE uint64x2_t vaddw_high_u32(uint64x2_t a, uint32x4_t b) {
  vuint64m1_t b_ext =
      __riscv_vzext_vf2_u64m1(__riscv_vlmul_trunc_v_u32m1_u32mf2(__riscv_vslidedown_vx_u32m1(b, 2, 4)), 2);
  return __riscv_vadd_vv_u64m1(a, b_ext, 2);
}

FORCE_INLINE int8x8_t vhadd_s8(int8x8_t a, int8x8_t b) { return __riscv_vaadd_vv_i8m1(a, b, __RISCV_VXRM_RDN, 8); }

FORCE_INLINE int16x4_t vhadd_s16(int16x4_t a, int16x4_t b) { return __riscv_vaadd_vv_i16m1(a, b, __RISCV_VXRM_RDN, 4); }

FORCE_INLINE int32x2_t vhadd_s32(int32x2_t a, int32x2_t b) { return __riscv_vaadd_vv_i32m1(a, b, __RISCV_VXRM_RDN, 2); }

FORCE_INLINE uint8x8_t vhadd_u8(uint8x8_t a, uint8x8_t b) { return __riscv_vaaddu_vv_u8m1(a, b, __RISCV_VXRM_RDN, 8); }

FORCE_INLINE uint16x4_t vhadd_u16(uint16x4_t a, uint16x4_t b) {
  return __riscv_vaaddu_vv_u16m1(a, b, __RISCV_VXRM_RDN, 4);
}

FORCE_INLINE uint32x2_t vhadd_u32(uint32x2_t a, uint32x2_t b) {
  return __riscv_vaaddu_vv_u32m1(a, b, __RISCV_VXRM_RDN, 2);
}

FORCE_INLINE int8x16_t vhaddq_s8(int8x16_t a, int8x16_t b) { return __riscv_vaadd_vv_i8m1(a, b, __RISCV_VXRM_RDN, 16); }

FORCE_INLINE int16x8_t vhaddq_s16(int16x8_t a, int16x8_t b) {
  return __riscv_vaadd_vv_i16m1(a, b, __RISCV_VXRM_RDN, 8);
}

FORCE_INLINE int32x4_t vhaddq_s32(int32x4_t a, int32x4_t b) {
  return __riscv_vaadd_vv_i32m1(a, b, __RISCV_VXRM_RDN, 4);
}

FORCE_INLINE uint8x16_t vhaddq_u8(uint8x16_t a, uint8x16_t b) {
  return __riscv_vaaddu_vv_u8m1(a, b, __RISCV_VXRM_RDN, 16);
}

FORCE_INLINE uint16x8_t vhaddq_u16(uint16x8_t a, uint16x8_t b) {
  return __riscv_vaaddu_vv_u16m1(a, b, __RISCV_VXRM_RDN, 8);
}

FORCE_INLINE uint32x4_t vhaddq_u32(uint32x4_t a, uint32x4_t b) {
  return __riscv_vaaddu_vv_u32m1(a, b, __RISCV_VXRM_RDN, 4);
}

FORCE_INLINE int8x8_t vrhadd_s8(int8x8_t a, int8x8_t b) { return __riscv_vaadd_vv_i8m1(a, b, __RISCV_VXRM_RNU, 8); }

FORCE_INLINE int16x4_t vrhadd_s16(int16x4_t a, int16x4_t b) {
  return __riscv_vaadd_vv_i16m1(a, b, __RISCV_VXRM_RNU, 4);
}

FORCE_INLINE int32x2_t vrhadd_s32(int32x2_t a, int32x2_t b) {
  return __riscv_vaadd_vv_i32m1(a, b, __RISCV_VXRM_RNU, 2);
}

FORCE_INLINE uint8x8_t vrhadd_u8(uint8x8_t a, uint8x8_t b) { return __riscv_vaaddu_vv_u8m1(a, b, __RISCV_VXRM_RNU, 8); }

FORCE_INLINE uint16x4_t vrhadd_u16(uint16x4_t a, uint16x4_t b) {
  return __riscv_vaaddu_vv_u16m1(a, b, __RISCV_VXRM_RNU, 4);
}

FORCE_INLINE uint32x2_t vrhadd_u32(uint32x2_t a, uint32x2_t b) {
  return __riscv_vaaddu_vv_u32m1(a, b, __RISCV_VXRM_RNU, 2);
}

FORCE_INLINE int8x16_t vrhaddq_s8(int8x16_t a, int8x16_t b) {
  return __riscv_vaadd_vv_i8m1(a, b, __RISCV_VXRM_RNU, 16);
}

FORCE_INLINE int16x8_t vrhaddq_s16(int16x8_t a, int16x8_t b) {
  return __riscv_vaadd_vv_i16m1(a, b, __RISCV_VXRM_RNU, 8);
}

FORCE_INLINE int32x4_t vrhaddq_s32(int32x4_t a, int32x4_t b) {
  return __riscv_vaadd_vv_i32m1(a, b, __RISCV_VXRM_RNU, 4);
}

FORCE_INLINE uint8x16_t vrhaddq_u8(uint8x16_t a, uint8x16_t b) {
  return __riscv_vaaddu_vv_u8m1(a, b, __RISCV_VXRM_RNU, 16);
}

FORCE_INLINE uint16x8_t vrhaddq_u16(uint16x8_t a, uint16x8_t b) {
  return __riscv_vaaddu_vv_u16m1(a, b, __RISCV_VXRM_RNU, 8);
}

FORCE_INLINE uint32x4_t vrhaddq_u32(uint32x4_t a, uint32x4_t b) {
  return __riscv_vaaddu_vv_u32m1(a, b, __RISCV_VXRM_RNU, 4);
}

FORCE_INLINE int8x8_t vqadd_s8(int8x8_t a, int8x8_t b) { return __riscv_vsadd_vv_i8m1(a, b, 8); }

FORCE_INLINE int16x4_t vqadd_s16(int16x4_t a, int16x4_t b) { return __riscv_vsadd_vv_i16m1(a, b, 4); }

FORCE_INLINE int32x2_t vqadd_s32(int32x2_t a, int32x2_t b) { return __riscv_vsadd_vv_i32m1(a, b, 2); }

FORCE_INLINE int64x1_t vqadd_s64(int64x1_t a, int64x1_t b) { return __riscv_vsadd_vv_i64m1(a, b, 1); }

FORCE_INLINE uint8x8_t vqadd_u8(uint8x8_t a, uint8x8_t b) { return __riscv_vsaddu_vv_u8m1(a, b, 8); }

FORCE_INLINE uint16x4_t vqadd_u16(uint16x4_t a, uint16x4_t b) { return __riscv_vsaddu_vv_u16m1(a, b, 4); }

FORCE_INLINE uint32x2_t vqadd_u32(uint32x2_t a, uint32x2_t b) { return __riscv_vsaddu_vv_u32m1(a, b, 2); }

FORCE_INLINE uint64x1_t vqadd_u64(uint64x1_t a, uint64x1_t b) { return __riscv_vsaddu_vv_u64m1(a, b, 1); }

FORCE_INLINE int8x16_t vqaddq_s8(int8x16_t a, int8x16_t b) { return __riscv_vsadd_vv_i8m1(a, b, 16); }

FORCE_INLINE int16x8_t vqaddq_s16(int16x8_t a, int16x8_t b) { return __riscv_vsadd_vv_i16m1(a, b, 8); }

FORCE_INLINE int32x4_t vqaddq_s32(int32x4_t a, int32x4_t b) { return __riscv_vsadd_vv_i32m1(a, b, 4); }

FORCE_INLINE int64x2_t vqaddq_s64(int64x2_t a, int64x2_t b) { return __riscv_vsadd_vv_i64m1(a, b, 2); }

FORCE_INLINE uint8x16_t vqaddq_u8(uint8x16_t a, uint8x16_t b) { return __riscv_vsaddu_vv_u8m1(a, b, 16); }

FORCE_INLINE uint16x8_t vqaddq_u16(uint16x8_t a, uint16x8_t b) { return __riscv_vsaddu_vv_u16m1(a, b, 8); }

FORCE_INLINE uint32x4_t vqaddq_u32(uint32x4_t a, uint32x4_t b) { return __riscv_vsaddu_vv_u32m1(a, b, 4); }

FORCE_INLINE uint64x2_t vqaddq_u64(uint64x2_t a, uint64x2_t b) { return __riscv_vsaddu_vv_u64m1(a, b, 2); }

#define SATURATE_ADD_SUB(BIT)                                                       \
  static inline int##BIT##_t sat_add_int##BIT(int##BIT##_t a, int##BIT##_t b) {     \
    if (a > 0 && b > INT##BIT##_MAX - a) {                                          \
      return INT##BIT##_MAX;                                                        \
    } else if (a < 0 && b < INT##BIT##_MIN - a) {                                   \
      return INT##BIT##_MIN;                                                        \
    } else                                                                          \
      return a + b;                                                                 \
  }                                                                                 \
  static inline uint##BIT##_t sat_add_uint##BIT(uint##BIT##_t a, uint##BIT##_t b) { \
    uint##BIT##_t r = a + b;                                                        \
    r |= -(r < a);                                                                  \
    return r;                                                                       \
  }                                                                                 \
  static inline int##BIT##_t sat_sub_int##BIT(int##BIT##_t a, int##BIT##_t b) {     \
    if (b > 0 && a < INT##BIT##_MIN + b) {                                          \
      return INT##BIT##_MIN;                                                        \
    } else if (b < 0 && a > INT##BIT##_MAX + b) {                                   \
      return INT##BIT##_MAX;                                                        \
    } else                                                                          \
      return a - b;                                                                 \
  }                                                                                 \
  static inline uint##BIT##_t sat_sub_uint##BIT(uint##BIT##_t a, uint##BIT##_t b) { \
    uint##BIT##_t r = a - b;                                                        \
    r &= -(r <= a);                                                                 \
    return r;                                                                       \
  }
SATURATE_ADD_SUB(8)
SATURATE_ADD_SUB(16)
SATURATE_ADD_SUB(32)
SATURATE_ADD_SUB(64)

FORCE_INLINE int8_t vqaddb_s8(int8_t a, int8_t b) { return sat_add_int8(a, b); }

FORCE_INLINE int16_t vqaddh_s16(int16_t a, int16_t b) { return sat_add_int16(a, b); }

FORCE_INLINE int32_t vqadds_s32(int32_t a, int32_t b) { return sat_add_int32(a, b); }

FORCE_INLINE int64_t vqaddd_s64(int64_t a, int64_t b) { return sat_add_int64(a, b); }

FORCE_INLINE uint8_t vqaddb_u8(uint8_t a, uint8_t b) { return sat_add_uint8(a, b); }

FORCE_INLINE uint16_t vqaddh_u16(uint16_t a, uint16_t b) { return sat_add_uint16(a, b); }

FORCE_INLINE uint32_t vqadds_u32(uint32_t a, uint32_t b) { return sat_add_uint32(a, b); }

FORCE_INLINE uint64_t vqaddd_u64(uint64_t a, uint64_t b) { return sat_add_uint64(a, b); }

// FORCE_INLINE int8x8_t vuqadd_s8(int8x8_t a, uint8x8_t b);

// FORCE_INLINE int8x16_t vuqaddq_s8(int8x16_t a, uint8x16_t b);

// FORCE_INLINE int16x4_t vuqadd_s16(int16x4_t a, uint16x4_t b);

// FORCE_INLINE int16x8_t vuqaddq_s16(int16x8_t a, uint16x8_t b);

// FORCE_INLINE int32x2_t vuqadd_s32(int32x2_t a, uint32x2_t b);

// FORCE_INLINE int32x4_t vuqaddq_s32(int32x4_t a, uint32x4_t b);

// FORCE_INLINE int64x1_t vuqadd_s64(int64x1_t a, uint64x1_t b);

// FORCE_INLINE int64x2_t vuqaddq_s64(int64x2_t a, uint64x2_t b);

// FORCE_INLINE int8_t vuqaddb_s8(int8_t a, uint8_t b);

// FORCE_INLINE int16_t vuqaddh_s16(int16_t a, uint16_t b);

// FORCE_INLINE int32_t vuqadds_s32(int32_t a, uint32_t b);

// FORCE_INLINE int64_t vuqaddd_s64(int64_t a, uint64_t b);

// FORCE_INLINE uint8x8_t vsqadd_u8(uint8x8_t a, int8x8_t b);

// FORCE_INLINE uint8x16_t vsqaddq_u8(uint8x16_t a, int8x16_t b);

// FORCE_INLINE uint16x4_t vsqadd_u16(uint16x4_t a, int16x4_t b);

// FORCE_INLINE uint16x8_t vsqaddq_u16(uint16x8_t a, int16x8_t b);

// FORCE_INLINE uint32x2_t vsqadd_u32(uint32x2_t a, int32x2_t b);

// FORCE_INLINE uint32x4_t vsqaddq_u32(uint32x4_t a, int32x4_t b);

// FORCE_INLINE uint64x1_t vsqadd_u64(uint64x1_t a, int64x1_t b);

// FORCE_INLINE uint64x2_t vsqaddq_u64(uint64x2_t a, int64x2_t b);

// FORCE_INLINE uint8_t vsqaddb_u8(uint8_t a, int8_t b);

// FORCE_INLINE uint16_t vsqaddh_u16(uint16_t a, int16_t b);

// FORCE_INLINE uint32_t vsqadds_u32(uint32_t a, int32_t b);

// FORCE_INLINE uint64_t vsqaddd_u64(uint64_t a, int64_t b);

FORCE_INLINE int8x8_t vaddhn_s16(int16x8_t a, int16x8_t b) {
  vint16m1_t ab_add = __riscv_vadd_vv_i16m1(a, b, 8);
  return __riscv_vlmul_ext_v_i8mf2_i8m1(__riscv_vnsra_wx_i8mf2(ab_add, 8, 8));
}

FORCE_INLINE int16x4_t vaddhn_s32(int32x4_t a, int32x4_t b) {
  vint32m1_t ab_add = __riscv_vadd_vv_i32m1(a, b, 4);
  return __riscv_vlmul_ext_v_i16mf2_i16m1(__riscv_vnsra_wx_i16mf2(ab_add, 16, 4));
}

FORCE_INLINE int32x2_t vaddhn_s64(int64x2_t a, int64x2_t b) {
  vint64m1_t ab_add = __riscv_vadd_vv_i64m1(a, b, 2);
  return __riscv_vlmul_ext_v_i32mf2_i32m1(__riscv_vnsra_wx_i32mf2(ab_add, 32, 2));
}

FORCE_INLINE uint8x8_t vaddhn_u16(uint16x8_t a, uint16x8_t b) {
  vuint16m1_t ab_add = __riscv_vadd_vv_u16m1(a, b, 8);
  return __riscv_vlmul_ext_v_u8mf2_u8m1(__riscv_vnsrl_wx_u8mf2(ab_add, 8, 8));
}

FORCE_INLINE uint16x4_t vaddhn_u32(uint32x4_t a, uint32x4_t b) {
  vuint32m1_t ab_add = __riscv_vadd_vv_u32m1(a, b, 4);
  return __riscv_vlmul_ext_v_u16mf2_u16m1(__riscv_vnsrl_wx_u16mf2(ab_add, 16, 4));
}

FORCE_INLINE uint32x2_t vaddhn_u64(uint64x2_t a, uint64x2_t b) {
  vuint64m1_t ab_add = __riscv_vadd_vv_u64m1(a, b, 2);
  return __riscv_vlmul_ext_v_u32mf2_u32m1(__riscv_vnsrl_wx_u32mf2(ab_add, 32, 2));
}

FORCE_INLINE int8x16_t vaddhn_high_s16(int8x8_t r, int16x8_t a, int16x8_t b) {
  vint16m1_t ab_add = __riscv_vadd_vv_i16m1(a, b, 8);
  vint8m1_t addhn = __riscv_vlmul_ext_v_i8mf2_i8m1(__riscv_vnsra_wx_i8mf2(ab_add, 8, 8));
  return __riscv_vslideup_vx_i8m1(r, addhn, 8, 16);
}

FORCE_INLINE int16x8_t vaddhn_high_s32(int16x4_t r, int32x4_t a, int32x4_t b) {
  vint32m1_t ab_add = __riscv_vadd_vv_i32m1(a, b, 4);
  vint16m1_t addhn = __riscv_vlmul_ext_v_i16mf2_i16m1(__riscv_vnsra_wx_i16mf2(ab_add, 16, 4));
  return __riscv_vslideup_vx_i16m1(r, addhn, 4, 8);
}

FORCE_INLINE int32x4_t vaddhn_high_s64(int32x2_t r, int64x2_t a, int64x2_t b) {
  vint64m1_t ab_add = __riscv_vadd_vv_i64m1(a, b, 2);
  vint32m1_t addhn = __riscv_vlmul_ext_v_i32mf2_i32m1(__riscv_vnsra_wx_i32mf2(ab_add, 32, 2));
  return __riscv_vslideup_vx_i32m1(r, addhn, 2, 4);
}

FORCE_INLINE uint8x16_t vaddhn_high_u16(uint8x8_t r, uint16x8_t a, uint16x8_t b) {
  vuint16m1_t ab_add = __riscv_vadd_vv_u16m1(a, b, 8);
  vuint8m1_t addhn = __riscv_vlmul_ext_v_u8mf2_u8m1(__riscv_vnsrl_wx_u8mf2(ab_add, 8, 8));
  return __riscv_vslideup_vx_u8m1(r, addhn, 8, 16);
}

FORCE_INLINE uint16x8_t vaddhn_high_u32(uint16x4_t r, uint32x4_t a, uint32x4_t b) {
  vuint32m1_t ab_add = __riscv_vadd_vv_u32m1(a, b, 4);
  vuint16m1_t addhn = __riscv_vlmul_ext_v_u16mf2_u16m1(__riscv_vnsrl_wx_u16mf2(ab_add, 16, 4));
  return __riscv_vslideup_vx_u16m1(r, addhn, 4, 8);
}

FORCE_INLINE uint32x4_t vaddhn_high_u64(uint32x2_t r, uint64x2_t a, uint64x2_t b) {
  vuint64m1_t ab_add = __riscv_vadd_vv_u64m1(a, b, 2);
  vuint32m1_t addhn = __riscv_vlmul_ext_v_u32mf2_u32m1(__riscv_vnsrl_wx_u32mf2(ab_add, 32, 2));
  return __riscv_vslideup_vx_u32m1(r, addhn, 2, 4);
}

FORCE_INLINE int8x8_t vraddhn_s16(int16x8_t a, int16x8_t b) {
  vint16m1_t add_ab = __riscv_vadd_vv_i16m1(a, b, 8);
  vint16m1_t add_round = __riscv_vadd_vx_i16m1(add_ab, 1 << 7, 8);
  return __riscv_vnsra_wx_i8m1(__riscv_vlmul_ext_v_i16m1_i16m2(add_round), 8, 8);
}

FORCE_INLINE int16x4_t vraddhn_s32(int32x4_t a, int32x4_t b) {
  vint32m1_t add_ab = __riscv_vadd_vv_i32m1(a, b, 4);
  vint32m1_t add_round = __riscv_vadd_vx_i32m1(add_ab, 1 << 15, 4);
  return __riscv_vnsra_wx_i16m1(__riscv_vlmul_ext_v_i32m1_i32m2(add_round), 16, 4);
}

FORCE_INLINE int32x2_t vraddhn_s64(int64x2_t a, int64x2_t b) {
  vint64m1_t add_ab = __riscv_vadd_vv_i64m1(a, b, 2);
  vint64m1_t add_round = __riscv_vadd_vx_i64m1(add_ab, (int64_t)1 << 31, 2);
  return __riscv_vnsra_wx_i32m1(__riscv_vlmul_ext_v_i64m1_i64m2(add_round), 32, 2);
}

FORCE_INLINE uint8x8_t vraddhn_u16(uint16x8_t a, uint16x8_t b) {
  vuint16m1_t add_ab = __riscv_vadd_vv_u16m1(a, b, 8);
  vuint16m1_t add_round = __riscv_vadd_vx_u16m1(add_ab, 1 << 7, 8);
  return __riscv_vnsrl_wx_u8m1(__riscv_vlmul_ext_v_u16m1_u16m2(add_round), 8, 8);
}

FORCE_INLINE uint16x4_t vraddhn_u32(uint32x4_t a, uint32x4_t b) {
  vuint32m1_t add_ab = __riscv_vadd_vv_u32m1(a, b, 4);
  vuint32m1_t add_round = __riscv_vadd_vx_u32m1(add_ab, 1 << 15, 4);
  return __riscv_vnsrl_wx_u16m1(__riscv_vlmul_ext_v_u32m1_u32m2(add_round), 16, 4);
}

FORCE_INLINE uint32x2_t vraddhn_u64(uint64x2_t a, uint64x2_t b) {
  vuint64m1_t add_ab = __riscv_vadd_vv_u64m1(a, b, 2);
  vuint64m1_t add_round = __riscv_vadd_vx_u64m1(add_ab, (int64_t)1 << 31, 2);
  return __riscv_vnsrl_wx_u32m1(__riscv_vlmul_ext_v_u64m1_u64m2(add_round), 32, 2);
}

FORCE_INLINE int8x16_t vraddhn_high_s16(int8x8_t r, int16x8_t a, int16x8_t b) {
  vint16m1_t add_ab = __riscv_vadd_vv_i16m1(a, b, 8);
  vint16m1_t add_round = __riscv_vadd_vx_i16m1(add_ab, 1 << 7, 8);
  vint8m1_t raddhn = __riscv_vnsra_wx_i8m1(__riscv_vlmul_ext_v_i16m1_i16m2(add_round), 8, 8);
  return __riscv_vslideup_vx_i8m1(r, raddhn, 8, 16);
}

FORCE_INLINE int16x8_t vraddhn_high_s32(int16x4_t r, int32x4_t a, int32x4_t b) {
  vint32m1_t add_ab = __riscv_vadd_vv_i32m1(a, b, 4);
  vint32m1_t add_round = __riscv_vadd_vx_i32m1(add_ab, 1 << 15, 4);
  vint16m1_t raddhn = __riscv_vnsra_wx_i16m1(__riscv_vlmul_ext_v_i32m1_i32m2(add_round), 16, 4);
  return __riscv_vslideup_vx_i16m1(r, raddhn, 4, 8);
}

FORCE_INLINE int32x4_t vraddhn_high_s64(int32x2_t r, int64x2_t a, int64x2_t b) {
  vint64m1_t add_ab = __riscv_vadd_vv_i64m1(a, b, 2);
  vint64m1_t add_round = __riscv_vadd_vx_i64m1(add_ab, (int64_t)1 << 31, 2);
  vint32m1_t raddhn = __riscv_vnsra_wx_i32m1(__riscv_vlmul_ext_v_i64m1_i64m2(add_round), 32, 2);
  return __riscv_vslideup_vx_i32m1(r, raddhn, 2, 4);
}

FORCE_INLINE uint8x16_t vraddhn_high_u16(uint8x8_t r, uint16x8_t a, uint16x8_t b) {
  vuint16m1_t add_ab = __riscv_vadd_vv_u16m1(a, b, 8);
  vuint16m1_t add_round = __riscv_vadd_vx_u16m1(add_ab, 1 << 7, 8);
  vuint8m1_t raddhn = __riscv_vnsrl_wx_u8m1(__riscv_vlmul_ext_v_u16m1_u16m2(add_round), 8, 8);
  return __riscv_vslideup_vx_u8m1(r, raddhn, 8, 16);
}

FORCE_INLINE uint16x8_t vraddhn_high_u32(uint16x4_t r, uint32x4_t a, uint32x4_t b) {
  vuint32m1_t add_ab = __riscv_vadd_vv_u32m1(a, b, 4);
  vuint32m1_t add_round = __riscv_vadd_vx_u32m1(add_ab, 1 << 15, 4);
  vuint16m1_t raddhn = __riscv_vnsrl_wx_u16m1(__riscv_vlmul_ext_v_u32m1_u32m2(add_round), 16, 4);
  return __riscv_vslideup_vx_u16m1(r, raddhn, 4, 8);
}

FORCE_INLINE uint32x4_t vraddhn_high_u64(uint32x2_t r, uint64x2_t a, uint64x2_t b) {
  vuint64m1_t add_ab = __riscv_vadd_vv_u64m1(a, b, 2);
  vuint64m1_t add_round = __riscv_vadd_vx_u64m1(add_ab, (int64_t)1 << 31, 2);
  vuint32m1_t raddhn = __riscv_vnsrl_wx_u32m1(__riscv_vlmul_ext_v_u64m1_u64m2(add_round), 32, 2);
  return __riscv_vslideup_vx_u32m1(r, raddhn, 2, 4);
}

FORCE_INLINE int8x8_t vmul_s8(int8x8_t a, int8x8_t b) { return __riscv_vmul_vv_i8m1(a, b, 8); }

FORCE_INLINE int16x4_t vmul_s16(int16x4_t a, int16x4_t b) { return __riscv_vmul_vv_i16m1(a, b, 4); }

FORCE_INLINE int32x2_t vmul_s32(int32x2_t a, int32x2_t b) { return __riscv_vmul_vv_i32m1(a, b, 2); }

FORCE_INLINE float32x2_t vmul_f32(float32x2_t a, float32x2_t b) { return __riscv_vfmul_vv_f32m1(a, b, 2); }

FORCE_INLINE uint8x8_t vmul_u8(uint8x8_t a, uint8x8_t b) { return __riscv_vmul_vv_u8m1(a, b, 8); }

FORCE_INLINE uint16x4_t vmul_u16(uint16x4_t a, uint16x4_t b) { return __riscv_vmul_vv_u16m1(a, b, 4); }

FORCE_INLINE uint32x2_t vmul_u32(uint32x2_t a, uint32x2_t b) { return __riscv_vmul_vv_u32m1(a, b, 2); }

FORCE_INLINE int8x16_t vmulq_s8(int8x16_t a, int8x16_t b) { return __riscv_vmul_vv_i8m1(a, b, 16); }

FORCE_INLINE int16x8_t vmulq_s16(int16x8_t a, int16x8_t b) { return __riscv_vmul_vv_i16m1(a, b, 8); }

FORCE_INLINE int32x4_t vmulq_s32(int32x4_t a, int32x4_t b) { return __riscv_vmul_vv_i32m1(a, b, 4); }

FORCE_INLINE float32x4_t vmulq_f32(float32x4_t a, float32x4_t b) { return __riscv_vfmul_vv_f32m1(a, b, 4); }

// FORCE_INLINE poly8x8_t vmul_p8(poly8x8_t a, poly8x8_t b);

// FORCE_INLINE poly8x16_t vmulq_p8(poly8x16_t a, poly8x16_t b);

FORCE_INLINE float64x1_t vmul_f64(float64x1_t a, float64x1_t b) { return __riscv_vfmul_vv_f64m1(a, b, 1); }

FORCE_INLINE float64x2_t vmulq_f64(float64x2_t a, float64x2_t b) { return __riscv_vfmul_vv_f64m1(a, b, 2); }

FORCE_INLINE float32x2_t vmulx_f32(float32x2_t a, float32x2_t b) {
  vbool32_t a_non_nan_mask = __riscv_vmfeq_vv_f32m1_b32(a, a, 2);
  vbool32_t b_non_nan_mask = __riscv_vmfeq_vv_f32m1_b32(b, b, 2);
  vbool32_t ab_nan_mask = __riscv_vmnot_m_b32(__riscv_vmor_mm_b32(a_non_nan_mask, b_non_nan_mask, 2), 2);
  vfloat32m1_t mul = __riscv_vfmul_vv_f32m1(a, b, 2);
  vbool32_t non_nan_mask = __riscv_vmfeq_vv_f32m1_b32(mul, mul, 2);
  vbool32_t non_two_mask = __riscv_vmor_mm_b32(non_nan_mask, ab_nan_mask, 2);
  vfloat32m1_t all_twos = __riscv_vfmv_v_f_f32m1(2, 2);
  return __riscv_vmerge_vvm_f32m1(all_twos, mul, non_two_mask, 2);
}

FORCE_INLINE float32x4_t vmulxq_f32(float32x4_t a, float32x4_t b) {
  vbool32_t a_non_nan_mask = __riscv_vmfeq_vv_f32m1_b32(a, a, 4);
  vbool32_t b_non_nan_mask = __riscv_vmfeq_vv_f32m1_b32(b, b, 4);
  vbool32_t ab_nan_mask = __riscv_vmnot_m_b32(__riscv_vmor_mm_b32(a_non_nan_mask, b_non_nan_mask, 4), 4);
  vfloat32m1_t mul = __riscv_vfmul_vv_f32m1(a, b, 4);
  vbool32_t non_nan_mask = __riscv_vmfeq_vv_f32m1_b32(mul, mul, 4);
  vbool32_t non_two_mask = __riscv_vmor_mm_b32(non_nan_mask, ab_nan_mask, 4);
  vfloat32m1_t all_twos = __riscv_vfmv_v_f_f32m1(2, 4);
  return __riscv_vmerge_vvm_f32m1(all_twos, mul, non_two_mask, 4);
}

FORCE_INLINE float64x1_t vmulx_f64(float64x1_t a, float64x1_t b) {
  vbool64_t a_non_nan_mask = __riscv_vmfeq_vv_f64m1_b64(a, a, 1);
  vbool64_t b_non_nan_mask = __riscv_vmfeq_vv_f64m1_b64(b, b, 1);
  vbool64_t ab_nan_mask = __riscv_vmnot_m_b64(__riscv_vmor_mm_b64(a_non_nan_mask, b_non_nan_mask, 1), 1);
  vfloat64m1_t mul = __riscv_vfmul_vv_f64m1(a, b, 1);
  vbool64_t non_nan_mask = __riscv_vmfeq_vv_f64m1_b64(mul, mul, 1);
  vbool64_t non_two_mask = __riscv_vmor_mm_b64(non_nan_mask, ab_nan_mask, 1);
  vfloat64m1_t all_twos = __riscv_vfmv_v_f_f64m1(2, 1);
  return __riscv_vmerge_vvm_f64m1(all_twos, mul, non_two_mask, 1);
}

FORCE_INLINE float64x2_t vmulxq_f64(float64x2_t a, float64x2_t b) {
  vbool64_t a_non_nan_mask = __riscv_vmfeq_vv_f64m1_b64(a, a, 2);
  vbool64_t b_non_nan_mask = __riscv_vmfeq_vv_f64m1_b64(b, b, 2);
  vbool64_t ab_nan_mask = __riscv_vmnot_m_b64(__riscv_vmor_mm_b64(a_non_nan_mask, b_non_nan_mask, 2), 2);
  vfloat64m1_t mul = __riscv_vfmul_vv_f64m1(a, b, 2);
  vbool64_t non_nan_mask = __riscv_vmfeq_vv_f64m1_b64(mul, mul, 2);
  vbool64_t non_two_mask = __riscv_vmor_mm_b64(non_nan_mask, ab_nan_mask, 2);
  vfloat64m1_t all_twos = __riscv_vfmv_v_f_f64m1(2, 2);
  return __riscv_vmerge_vvm_f64m1(all_twos, mul, non_two_mask, 2);
}

FORCE_INLINE float32_t vmulxs_f32(float32_t a, float32_t b) {
  float32_t mul = a * b;
  if (mul != mul) {
    return 2;
  }
  return mul;
}

FORCE_INLINE float64_t vmulxd_f64(float64_t a, float64_t b) {
  float64_t mul = a * b;
  if (mul != mul) {
    return 2;
  }
  return mul;
}

FORCE_INLINE float32x2_t vmulx_lane_f32(float32x2_t a, float32x2_t b, const int lane) {
  vfloat32m1_t b_dup_lane = __riscv_vrgather_vx_f32m1(b, lane, 2);
  return vmulx_f32(a, b_dup_lane);
}

FORCE_INLINE float32x4_t vmulxq_lane_f32(float32x4_t a, float32x2_t b, const int lane) {
  vfloat32m1_t b_dup_lane = __riscv_vrgather_vx_f32m1(b, lane, 4);
  return vmulxq_f32(a, b_dup_lane);
}

FORCE_INLINE float64x1_t vmulx_lane_f64(float64x1_t a, float64x1_t b, const int lane) {
  vfloat64m1_t b_dup_lane = __riscv_vrgather_vx_f64m1(b, lane, 1);
  return vmulx_f64(a, b_dup_lane);
}

FORCE_INLINE float64x2_t vmulxq_lane_f64(float64x2_t a, float64x1_t b, const int lane) {
  vfloat64m1_t b_dup_lane = __riscv_vrgather_vx_f64m1(b, lane, 2);
  return vmulxq_f64(a, b_dup_lane);
}

FORCE_INLINE float32_t vmulxs_lane_f32(float32_t a, float32x2_t b, const int lane) {
  float32_t b_lane = __riscv_vfmv_f_s_f32m1_f32(__riscv_vslidedown_vx_f32m1(b, lane, 2));
  return a * b_lane;
}

FORCE_INLINE float64_t vmulxd_lane_f64(float64_t a, float64x1_t b, const int lane) {
  float64_t b_lane = __riscv_vfmv_f_s_f64m1_f64(b);
  return a * b_lane;
}

FORCE_INLINE float32x2_t vmulx_laneq_f32(float32x2_t a, float32x4_t b, const int lane) {
  vfloat32m1_t b_dup_lane = __riscv_vrgather_vx_f32m1(b, lane, 4);
  return vmulx_f32(a, b_dup_lane);
}

FORCE_INLINE float32x4_t vmulxq_laneq_f32(float32x4_t a, float32x4_t b, const int lane) {
  vfloat32m1_t b_dup_lane = __riscv_vrgather_vx_f32m1(b, lane, 4);
  return vmulxq_f32(a, b_dup_lane);
}

FORCE_INLINE float64x1_t vmulx_laneq_f64(float64x1_t a, float64x2_t b, const int lane) {
  vfloat64m1_t b_dup_lane = __riscv_vrgather_vx_f64m1(b, lane, 2);
  return vmulx_f64(a, b_dup_lane);
}

FORCE_INLINE float64x2_t vmulxq_laneq_f64(float64x2_t a, float64x2_t b, const int lane) {
  vfloat64m1_t b_dup_lane = __riscv_vrgather_vx_f64m1(b, lane, 2);
  return vmulxq_f64(a, b_dup_lane);
}

FORCE_INLINE float32_t vmulxs_laneq_f32(float32_t a, float32x4_t b, const int lane) {
  // FIXME solve the NAN input
  float32_t b_lane = __riscv_vfmv_f_s_f32m1_f32(__riscv_vslidedown_vx_f32m1(b, lane, 4));
  return a * b_lane;
}

FORCE_INLINE float64_t vmulxd_laneq_f64(float64_t a, float64x2_t b, const int lane) {
  // FIXME solve the NAN input
  float64_t b_lane = __riscv_vfmv_f_s_f64m1_f64(__riscv_vslidedown_vx_f64m1(b, lane, 2));
  return a * b_lane;
}

FORCE_INLINE float32x2_t vdiv_f32(float32x2_t a, float32x2_t b) { return __riscv_vfdiv_vv_f32m1(a, b, 2); }

FORCE_INLINE float32x4_t vdivq_f32(float32x4_t a, float32x4_t b) { return __riscv_vfdiv_vv_f32m1(a, b, 4); }

FORCE_INLINE float64x1_t vdiv_f64(float64x1_t a, float64x1_t b) { return __riscv_vfdiv_vv_f64m1(a, b, 1); }

FORCE_INLINE float64x2_t vdivq_f64(float64x2_t a, float64x2_t b) { return __riscv_vfdiv_vv_f64m1(a, b, 2); }

FORCE_INLINE uint8x16_t vmulq_u8(uint8x16_t a, uint8x16_t b) { return __riscv_vmul_vv_u8m1(a, b, 16); }

FORCE_INLINE uint16x8_t vmulq_u16(uint16x8_t a, uint16x8_t b) { return __riscv_vmul_vv_u16m1(a, b, 8); }

FORCE_INLINE uint32x4_t vmulq_u32(uint32x4_t a, uint32x4_t b) { return __riscv_vmul_vv_u32m1(a, b, 4); }

FORCE_INLINE int16x4_t vqdmulh_s16(int16x4_t a, int16x4_t b) {
  vint32m2_t ab_mul = __riscv_vwmul_vv_i32m2(a, b, 4);
  vint32m2_t ab_mulx2 = __riscv_vmul_vx_i32m2(ab_mul, 2, 4);
  return __riscv_vnsra_wx_i16m1(ab_mulx2, 16, 4);
}

FORCE_INLINE int32x2_t vqdmulh_s32(int32x2_t a, int32x2_t b) {
  vint64m2_t ab_mul = __riscv_vwmul_vv_i64m2(a, b, 2);
  vint64m2_t ab_mulx2 = __riscv_vmul_vx_i64m2(ab_mul, 2, 2);
  return __riscv_vnsra_wx_i32m1(ab_mulx2, 32, 2);
}

FORCE_INLINE int16x8_t vqdmulhq_s16(int16x8_t a, int16x8_t b) {
  vint32m2_t ab_mul = __riscv_vwmul_vv_i32m2(a, b, 8);
  vint32m2_t ab_mulx2 = __riscv_vmul_vx_i32m2(ab_mul, 2, 8);
  return __riscv_vnsra_wx_i16m1(ab_mulx2, 16, 8);
}

FORCE_INLINE int32x4_t vqdmulhq_s32(int32x4_t a, int32x4_t b) {
  vint64m2_t ab_mul = __riscv_vwmul_vv_i64m2(a, b, 4);
  vint64m2_t ab_mulx2 = __riscv_vmul_vx_i64m2(ab_mul, 2, 4);
  return __riscv_vnsra_wx_i32m1(ab_mulx2, 32, 4);
}

FORCE_INLINE int16_t vqdmulhh_s16(int16_t a, int16_t b) {
  int32_t unsat = 2 * (int32_t)a * (int32_t)b;
  return unsat >> 16;
}

FORCE_INLINE int32_t vqdmulhs_s32(int32_t a, int32_t b) {
  int64_t unsat = 2 * (int64_t)a * (int64_t)b;
  return unsat >> 32;
}

FORCE_INLINE int16x4_t vqrdmulh_s16(int16x4_t a, int16x4_t b) {
  vint32m2_t ab_mul = __riscv_vwmul_vv_i32m2(a, b, 4);
  vint32m2_t ab_mulx2 = __riscv_vmul_vx_i32m2(ab_mul, 2, 4);
  return __riscv_vnclip_wx_i16m1(ab_mulx2, 16, __RISCV_VXRM_RNU, 4);
}

FORCE_INLINE int32x2_t vqrdmulh_s32(int32x2_t a, int32x2_t b) {
  vint64m2_t ab_mul = __riscv_vwmul_vv_i64m2(a, b, 2);
  vint64m2_t ab_mulx2 = __riscv_vmul_vx_i64m2(ab_mul, 2, 2);
  return __riscv_vnclip_wx_i32m1(ab_mulx2, 32, __RISCV_VXRM_RNU, 2);
}

FORCE_INLINE int16x8_t vqrdmulhq_s16(int16x8_t a, int16x8_t b) {
  vint32m2_t ab_mul = __riscv_vwmul_vv_i32m2(a, b, 8);
  vint32m2_t ab_mulx2 = __riscv_vmul_vx_i32m2(ab_mul, 2, 8);
  return __riscv_vnclip_wx_i16m1(ab_mulx2, 16, __RISCV_VXRM_RNU, 8);
}

FORCE_INLINE int32x4_t vqrdmulhq_s32(int32x4_t a, int32x4_t b) {
  vint64m2_t ab_mul = __riscv_vwmul_vv_i64m2(a, b, 4);
  vint64m2_t ab_mulx2 = __riscv_vmul_vx_i64m2(ab_mul, 2, 4);
  return __riscv_vnclip_wx_i32m1(ab_mulx2, 32, __RISCV_VXRM_RNU, 4);
}

FORCE_INLINE int16_t vqrdmulhh_s16(int16_t a, int16_t b) {
  int32_t dmul = 2 * (int32_t)a * (int32_t)b;
  return ((dmul >> 15) + 1) >> 1;
}

FORCE_INLINE int32_t vqrdmulhs_s32(int32_t a, int32_t b) {
  int64_t dmul = 2 * (int64_t)a * (int64_t)b;
  return ((dmul >> 31) + 1) >> 1;
}

FORCE_INLINE int16x4_t vqrdmlah_s16(int16x4_t a, int16x4_t b, int16x4_t c) {
  vint32m2_t bc_mul = __riscv_vwmul_vv_i32m2(b, c, 4);
  vint32m2_t bc_mulx2 = __riscv_vsll_vx_i32m2(bc_mul, 1, 4);
  vint16m1_t bc_s = __riscv_vnclip_wx_i16m1(bc_mulx2, 16, __RISCV_VXRM_RNU, 4);
  return __riscv_vsadd_vv_i16m1(a, bc_s, 4);
}

FORCE_INLINE int32x2_t vqrdmlah_s32(int32x2_t a, int32x2_t b, int32x2_t c) {
  vint64m2_t bc_mul = __riscv_vwmul_vv_i64m2(b, c, 2);
  vint64m2_t bc_mulx2 = __riscv_vsll_vx_i64m2(bc_mul, 1, 2);
  vint32m1_t bc_s = __riscv_vnclip_wx_i32m1(bc_mulx2, 32, __RISCV_VXRM_RNU, 2);
  return __riscv_vsadd_vv_i32m1(a, bc_s, 2);
}

FORCE_INLINE int16x8_t vqrdmlahq_s16(int16x8_t a, int16x8_t b, int16x8_t c) {
  vint32m2_t bc_mul = __riscv_vwmul_vv_i32m2(b, c, 8);
  vint32m2_t bc_mulx2 = __riscv_vsll_vx_i32m2(bc_mul, 1, 8);
  vint16m1_t bc_s = __riscv_vnclip_wx_i16m1(bc_mulx2, 16, __RISCV_VXRM_RNU, 8);
  return __riscv_vsadd_vv_i16m1(a, bc_s, 8);
}

FORCE_INLINE int32x4_t vqrdmlahq_s32(int32x4_t a, int32x4_t b, int32x4_t c) {
  vint64m2_t bc_mul = __riscv_vwmul_vv_i64m2(b, c, 4);
  vint64m2_t bc_mulx2 = __riscv_vsll_vx_i64m2(bc_mul, 1, 4);
  vint32m1_t bc_s = __riscv_vnclip_wx_i32m1(bc_mulx2, 32, __RISCV_VXRM_RNU, 4);
  return __riscv_vsadd_vv_i32m1(a, bc_s, 4);
}

FORCE_INLINE int16x4_t vqrdmlsh_s16(int16x4_t a, int16x4_t b, int16x4_t c) {
  vint32m2_t bc_mul = __riscv_vwmul_vv_i32m2(b, c, 4);
  vint32m2_t bc_mulx2 = __riscv_vsll_vx_i32m2(bc_mul, 1, 4);
  vint16m1_t bc_s = __riscv_vnclip_wx_i16m1(bc_mulx2, 16, __RISCV_VXRM_RNU, 4);
  return __riscv_vssub_vv_i16m1(a, bc_s, 4);
}

FORCE_INLINE int32x2_t vqrdmlsh_s32(int32x2_t a, int32x2_t b, int32x2_t c) {
  vint64m2_t bc_mul = __riscv_vwmul_vv_i64m2(b, c, 2);
  vint64m2_t bc_mulx2 = __riscv_vsll_vx_i64m2(bc_mul, 1, 2);
  vint32m1_t bc_s = __riscv_vnclip_wx_i32m1(bc_mulx2, 32, __RISCV_VXRM_RNU, 2);
  return __riscv_vssub_vv_i32m1(a, bc_s, 2);
}

FORCE_INLINE int16x8_t vqrdmlshq_s16(int16x8_t a, int16x8_t b, int16x8_t c) {
  vint32m2_t bc_mul = __riscv_vwmul_vv_i32m2(b, c, 8);
  vint32m2_t bc_mulx2 = __riscv_vsll_vx_i32m2(bc_mul, 1, 8);
  vint16m1_t bc_s = __riscv_vnclip_wx_i16m1(bc_mulx2, 16, __RISCV_VXRM_RNU, 8);
  return __riscv_vssub_vv_i16m1(a, bc_s, 8);
}

FORCE_INLINE int32x4_t vqrdmlshq_s32(int32x4_t a, int32x4_t b, int32x4_t c) {
  vint64m2_t bc_mul = __riscv_vwmul_vv_i64m2(b, c, 4);
  vint64m2_t bc_mulx2 = __riscv_vsll_vx_i64m2(bc_mul, 1, 4);
  vint32m1_t bc_s = __riscv_vnclip_wx_i32m1(bc_mulx2, 32, __RISCV_VXRM_RNU, 4);
  return __riscv_vssub_vv_i32m1(a, bc_s, 4);
}

FORCE_INLINE int16x8_t vmull_s8(int8x8_t a, int8x8_t b) {
  return __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vwmul_vv_i16m2(a, b, 8));
}

FORCE_INLINE int32x4_t vmull_s16(int16x4_t a, int16x4_t b) {
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vv_i32m2(a, b, 4));
}

FORCE_INLINE int64x2_t vmull_s32(int32x2_t a, int32x2_t b) {
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vv_i64m2(a, b, 2));
}

FORCE_INLINE uint16x8_t vmull_u8(uint8x8_t a, uint8x8_t b) {
  return __riscv_vlmul_trunc_v_u16m2_u16m1(__riscv_vwmulu_vv_u16m2(a, b, 8));
}

FORCE_INLINE uint32x4_t vmull_u16(uint16x4_t a, uint16x4_t b) {
  return __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwmulu_vv_u32m2(a, b, 4));
}

FORCE_INLINE uint64x2_t vmull_u32(uint32x2_t a, uint32x2_t b) {
  return __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwmulu_vv_u64m2(a, b, 2));
}

// FORCE_INLINE poly16x8_t vmull_p8(poly8x8_t a, poly8x8_t b);

FORCE_INLINE int16x8_t vmull_high_s8(int8x16_t a, int8x16_t b) {
  vint8mf2_t a_high = __riscv_vlmul_trunc_v_i8m1_i8mf2(__riscv_vslidedown_vx_i8m1(a, 8, 16));
  vint8mf2_t b_high = __riscv_vlmul_trunc_v_i8m1_i8mf2(__riscv_vslidedown_vx_i8m1(b, 8, 16));
  return __riscv_vwmul_vv_i16m1(a_high, b_high, 8);
}

FORCE_INLINE int32x4_t vmull_high_s16(int16x8_t a, int16x8_t b) {
  vint16mf2_t a_high = __riscv_vlmul_trunc_v_i16m1_i16mf2(__riscv_vslidedown_vx_i16m1(a, 4, 8));
  vint16mf2_t b_high = __riscv_vlmul_trunc_v_i16m1_i16mf2(__riscv_vslidedown_vx_i16m1(b, 4, 8));
  return __riscv_vwmul_vv_i32m1(a_high, b_high, 4);
}

FORCE_INLINE int64x2_t vmull_high_s32(int32x4_t a, int32x4_t b) {
  vint32mf2_t a_high = __riscv_vlmul_trunc_v_i32m1_i32mf2(__riscv_vslidedown_vx_i32m1(a, 2, 4));
  vint32mf2_t b_high = __riscv_vlmul_trunc_v_i32m1_i32mf2(__riscv_vslidedown_vx_i32m1(b, 2, 4));
  return __riscv_vwmul_vv_i64m1(a_high, b_high, 2);
}

FORCE_INLINE uint16x8_t vmull_high_u8(uint8x16_t a, uint8x16_t b) {
  vuint8mf2_t a_high = __riscv_vlmul_trunc_v_u8m1_u8mf2(__riscv_vslidedown_vx_u8m1(a, 8, 16));
  vuint8mf2_t b_high = __riscv_vlmul_trunc_v_u8m1_u8mf2(__riscv_vslidedown_vx_u8m1(b, 8, 16));
  return __riscv_vwmulu_vv_u16m1(a_high, b_high, 8);
}

FORCE_INLINE uint32x4_t vmull_high_u16(uint16x8_t a, uint16x8_t b) {
  vuint16mf2_t a_high = __riscv_vlmul_trunc_v_u16m1_u16mf2(__riscv_vslidedown_vx_u16m1(a, 4, 8));
  vuint16mf2_t b_high = __riscv_vlmul_trunc_v_u16m1_u16mf2(__riscv_vslidedown_vx_u16m1(b, 4, 8));
  return __riscv_vwmulu_vv_u32m1(a_high, b_high, 4);
}

FORCE_INLINE uint64x2_t vmull_high_u32(uint32x4_t a, uint32x4_t b) {
  vuint32mf2_t a_high = __riscv_vlmul_trunc_v_u32m1_u32mf2(__riscv_vslidedown_vx_u32m1(a, 2, 4));
  vuint32mf2_t b_high = __riscv_vlmul_trunc_v_u32m1_u32mf2(__riscv_vslidedown_vx_u32m1(b, 2, 4));
  return __riscv_vwmulu_vv_u64m1(a_high, b_high, 2);
}

// FORCE_INLINE poly16x8_t vmull_high_p8(poly8x16_t a, poly8x16_t b);

FORCE_INLINE int32x4_t vqdmull_s16(int16x4_t a, int16x4_t b) {
  vint32m2_t ab_mul = __riscv_vwmul_vv_i32m2(a, b, 4);
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vsll_vx_i32m2(ab_mul, 1, 4));
}

FORCE_INLINE int64x2_t vqdmull_s32(int32x2_t a, int32x2_t b) {
  vint64m2_t ab_mul = __riscv_vwmul_vv_i64m2(a, b, 4);
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vsll_vx_i64m2(ab_mul, 1, 2));
}

FORCE_INLINE int32_t vqdmullh_s16(int16_t a, int16_t b) {
  int32_t tmp = (int32_t)a * (int32_t)b;
  return tmp > INT32_MAX / 2 ? INT32_MAX : tmp < INT32_MIN / 2 ? INT32_MIN : tmp * 2;
}

FORCE_INLINE int64_t vqdmulls_s32(int32_t a, int32_t b) {
  int64_t tmp = (int64_t)a * (int64_t)b;
  return tmp > INT64_MAX / 2 ? INT64_MAX : tmp < INT64_MIN / 2 ? INT64_MIN : tmp * 2;
}

FORCE_INLINE int32x4_t vqdmull_high_s16(int16x8_t a, int16x8_t b) {
  vint16mf2_t a_high = __riscv_vlmul_trunc_v_i16m1_i16mf2(__riscv_vslidedown_vx_i16m1(a, 4, 8));
  vint16mf2_t b_high = __riscv_vlmul_trunc_v_i16m1_i16mf2(__riscv_vslidedown_vx_i16m1(b, 4, 8));
  vint32m1_t ab_mul = __riscv_vwmul_vv_i32m1(a_high, b_high, 4);
  return __riscv_vsll_vx_i32m1(ab_mul, 1, 4);
}

FORCE_INLINE int64x2_t vqdmull_high_s32(int32x4_t a, int32x4_t b) {
  vint32mf2_t a_high = __riscv_vlmul_trunc_v_i32m1_i32mf2(__riscv_vslidedown_vx_i32m1(a, 2, 4));
  vint32mf2_t b_high = __riscv_vlmul_trunc_v_i32m1_i32mf2(__riscv_vslidedown_vx_i32m1(b, 2, 4));
  vint64m1_t ab_mul = __riscv_vwmul_vv_i64m1(a_high, b_high, 4);
  return __riscv_vsll_vx_i64m1(ab_mul, 1, 2);
}

FORCE_INLINE int8x8_t vmla_s8(int8x8_t a, int8x8_t b, int8x8_t c) { return __riscv_vmacc_vv_i8m1(a, b, c, 8); }

FORCE_INLINE int16x4_t vmla_s16(int16x4_t a, int16x4_t b, int16x4_t c) { return __riscv_vmacc_vv_i16m1(a, b, c, 4); }

FORCE_INLINE int32x2_t vmla_s32(int32x2_t a, int32x2_t b, int32x2_t c) { return __riscv_vmacc_vv_i32m1(a, b, c, 2); }

FORCE_INLINE float32x2_t vmla_f32(float32x2_t a, float32x2_t b, float32x2_t c) {
  return __riscv_vfmacc_vv_f32m1(a, b, c, 2);
}

FORCE_INLINE uint8x8_t vmla_u8(uint8x8_t a, uint8x8_t b, uint8x8_t c) { return __riscv_vmacc_vv_u8m1(a, b, c, 8); }

FORCE_INLINE uint16x4_t vmla_u16(uint16x4_t a, uint16x4_t b, uint16x4_t c) {
  return __riscv_vmacc_vv_u16m1(a, b, c, 4);
}

FORCE_INLINE uint32x2_t vmla_u32(uint32x2_t a, uint32x2_t b, uint32x2_t c) {
  return __riscv_vmacc_vv_u32m1(a, b, c, 2);
}

FORCE_INLINE int8x16_t vmlaq_s8(int8x16_t a, int8x16_t b, int8x16_t c) { return __riscv_vmacc_vv_i8m1(a, b, c, 16); }

FORCE_INLINE int16x8_t vmlaq_s16(int16x8_t a, int16x8_t b, int16x8_t c) { return __riscv_vmacc_vv_i16m1(a, b, c, 8); }

FORCE_INLINE int32x4_t vmlaq_s32(int32x4_t a, int32x4_t b, int32x4_t c) { return __riscv_vmacc_vv_i32m1(a, b, c, 4); }

FORCE_INLINE float32x4_t vmlaq_f32(float32x4_t a, float32x4_t b, float32x4_t c) {
  return __riscv_vfmacc_vv_f32m1(a, b, c, 4);
}

FORCE_INLINE float64x1_t vmla_f64(float64x1_t a, float64x1_t b, float64x1_t c) {
  return __riscv_vfmacc_vv_f64m1(a, b, c, 1);
}

FORCE_INLINE float64x2_t vmlaq_f64(float64x2_t a, float64x2_t b, float64x2_t c) {
  return __riscv_vfmacc_vv_f64m1(a, b, c, 2);
}

FORCE_INLINE uint8x16_t vmlaq_u8(uint8x16_t a, uint8x16_t b, uint8x16_t c) {
  return __riscv_vmacc_vv_u8m1(a, b, c, 16);
}

FORCE_INLINE uint16x8_t vmlaq_u16(uint16x8_t a, uint16x8_t b, uint16x8_t c) {
  return __riscv_vmacc_vv_u16m1(a, b, c, 8);
}

FORCE_INLINE uint32x4_t vmlaq_u32(uint32x4_t a, uint32x4_t b, uint32x4_t c) {
  return __riscv_vmacc_vv_u32m1(a, b, c, 4);
}

FORCE_INLINE int16x8_t vmlal_s8(int16x8_t a, int8x8_t b, int8x8_t c) {
  return __riscv_vwmacc_vv_i16m1(a, __riscv_vlmul_trunc_v_i8m1_i8mf2(b), __riscv_vlmul_trunc_v_i8m1_i8mf2(c), 8);
}

FORCE_INLINE int32x4_t vmlal_s16(int32x4_t a, int16x4_t b, int16x4_t c) {
  return __riscv_vwmacc_vv_i32m1(a, __riscv_vlmul_trunc_v_i16m1_i16mf2(b), __riscv_vlmul_trunc_v_i16m1_i16mf2(c), 4);
}

FORCE_INLINE int64x2_t vmlal_s32(int64x2_t a, int32x2_t b, int32x2_t c) {
  return __riscv_vwmacc_vv_i64m1(a, __riscv_vlmul_trunc_v_i32m1_i32mf2(b), __riscv_vlmul_trunc_v_i32m1_i32mf2(c), 2);
}

FORCE_INLINE uint16x8_t vmlal_u8(uint16x8_t a, uint8x8_t b, uint8x8_t c) {
  return __riscv_vwmaccu_vv_u16m1(a, __riscv_vlmul_trunc_v_u8m1_u8mf2(b), __riscv_vlmul_trunc_v_u8m1_u8mf2(c), 8);
}

FORCE_INLINE uint32x4_t vmlal_u16(uint32x4_t a, uint16x4_t b, uint16x4_t c) {
  return __riscv_vwmaccu_vv_u32m1(a, __riscv_vlmul_trunc_v_u16m1_u16mf2(b), __riscv_vlmul_trunc_v_u16m1_u16mf2(c), 4);
}

FORCE_INLINE uint64x2_t vmlal_u32(uint64x2_t a, uint32x2_t b, uint32x2_t c) {
  return __riscv_vwmaccu_vv_u64m1(a, __riscv_vlmul_trunc_v_u32m1_u32mf2(b), __riscv_vlmul_trunc_v_u32m1_u32mf2(c), 2);
}

FORCE_INLINE int16x8_t vmlal_high_s8(int16x8_t a, int8x16_t b, int8x16_t c) {
  vint8mf2_t b_high = __riscv_vlmul_trunc_v_i8m1_i8mf2(__riscv_vslidedown_vx_i8m1(b, 8, 16));
  vint8mf2_t c_high = __riscv_vlmul_trunc_v_i8m1_i8mf2(__riscv_vslidedown_vx_i8m1(c, 8, 16));
  return __riscv_vwmacc_vv_i16m1(a, b_high, c_high, 8);
}

FORCE_INLINE int32x4_t vmlal_high_s16(int32x4_t a, int16x8_t b, int16x8_t c) {
  vint16mf2_t b_high = __riscv_vlmul_trunc_v_i16m1_i16mf2(__riscv_vslidedown_vx_i16m1(b, 4, 8));
  vint16mf2_t c_high = __riscv_vlmul_trunc_v_i16m1_i16mf2(__riscv_vslidedown_vx_i16m1(c, 4, 8));
  return __riscv_vwmacc_vv_i32m1(a, b_high, c_high, 4);
}

FORCE_INLINE int64x2_t vmlal_high_s32(int64x2_t a, int32x4_t b, int32x4_t c) {
  vint32mf2_t b_high = __riscv_vlmul_trunc_v_i32m1_i32mf2(__riscv_vslidedown_vx_i32m1(b, 2, 4));
  vint32mf2_t c_high = __riscv_vlmul_trunc_v_i32m1_i32mf2(__riscv_vslidedown_vx_i32m1(c, 2, 4));
  return __riscv_vwmacc_vv_i64m1(a, b_high, c_high, 2);
}

FORCE_INLINE uint16x8_t vmlal_high_u8(uint16x8_t a, uint8x16_t b, uint8x16_t c) {
  vuint8mf2_t b_high = __riscv_vlmul_trunc_v_u8m1_u8mf2(__riscv_vslidedown_vx_u8m1(b, 8, 16));
  vuint8mf2_t c_high = __riscv_vlmul_trunc_v_u8m1_u8mf2(__riscv_vslidedown_vx_u8m1(c, 8, 16));
  return __riscv_vwmaccu_vv_u16m1(a, b_high, c_high, 8);
}

FORCE_INLINE uint32x4_t vmlal_high_u16(uint32x4_t a, uint16x8_t b, uint16x8_t c) {
  vuint16mf2_t b_high = __riscv_vlmul_trunc_v_u16m1_u16mf2(__riscv_vslidedown_vx_u16m1(b, 4, 8));
  vuint16mf2_t c_high = __riscv_vlmul_trunc_v_u16m1_u16mf2(__riscv_vslidedown_vx_u16m1(c, 4, 8));
  return __riscv_vwmaccu_vv_u32m1(a, b_high, c_high, 4);
}

FORCE_INLINE uint64x2_t vmlal_high_u32(uint64x2_t a, uint32x4_t b, uint32x4_t c) {
  vuint32mf2_t b_high = __riscv_vlmul_trunc_v_u32m1_u32mf2(__riscv_vslidedown_vx_u32m1(b, 2, 4));
  vuint32mf2_t c_high = __riscv_vlmul_trunc_v_u32m1_u32mf2(__riscv_vslidedown_vx_u32m1(c, 2, 4));
  return __riscv_vwmaccu_vv_u64m1(a, b_high, c_high, 2);
}

FORCE_INLINE int32x4_t vqdmlal_s16(int32x4_t a, int16x4_t b, int16x4_t c) {
  vint32m1_t bc_mul = __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vv_i32m2(b, c, 4));
  vint32m1_t bc_mulx2 = __riscv_vmul_vx_i32m1(bc_mul, 2, 4);
  return __riscv_vadd_vv_i32m1(a, bc_mulx2, 4);
}

FORCE_INLINE int64x2_t vqdmlal_s32(int64x2_t a, int32x2_t b, int32x2_t c) {
  vint64m1_t bc_mul = __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vv_i64m2(b, c, 2));
  vint64m1_t bc_mulx2 = __riscv_vmul_vx_i64m1(bc_mul, 2, 2);
  return __riscv_vadd_vv_i64m1(a, bc_mulx2, 2);
}

FORCE_INLINE int32_t vqdmlalh_s16(int32_t a, int16_t b, int16_t c) {
  int32_t tmp = (int32_t)b * (int32_t)c;
  tmp = tmp > INT32_MAX / 2 ? INT32_MAX : tmp < INT32_MIN / 2 ? INT32_MIN : tmp * 2;
  if (a > 0 && tmp > INT32_MAX - a) {
    return INT32_MAX;
  } else if (a < 0 && tmp < INT32_MIN - a) {
    return INT32_MIN;
  }
  return a + tmp;
}

FORCE_INLINE int64_t vqdmlals_s32(int64_t a, int32_t b, int32_t c) {
  int64_t tmp = (int64_t)b * (int64_t)c;
  tmp = tmp > INT64_MAX / 2 ? INT64_MAX : tmp < INT64_MIN / 2 ? INT64_MIN : tmp * 2;
  if (a > 0 && tmp > INT64_MAX - a) {
    return INT64_MAX;
  } else if (a < 0 && tmp < INT64_MIN - a) {
    return INT64_MIN;
  }
  return a + tmp;
}

FORCE_INLINE int32x4_t vqdmlal_high_s16(int32x4_t a, int16x8_t b, int16x8_t c) {
  vint16mf2_t b_high = __riscv_vlmul_trunc_v_i16m1_i16mf2(__riscv_vslidedown_vx_i16m1(b, 4, 8));
  vint16mf2_t c_high = __riscv_vlmul_trunc_v_i16m1_i16mf2(__riscv_vslidedown_vx_i16m1(c, 4, 8));
  vint32m1_t bc_mul = __riscv_vwmul_vv_i32m1(b_high, c_high, 4);
  vint32m1_t bc_mulx2 = __riscv_vmul_vx_i32m1(bc_mul, 2, 4);
  return __riscv_vadd_vv_i32m1(a, bc_mulx2, 4);
}

FORCE_INLINE int64x2_t vqdmlal_high_s32(int64x2_t a, int32x4_t b, int32x4_t c) {
  vint32mf2_t b_high = __riscv_vlmul_trunc_v_i32m1_i32mf2(__riscv_vslidedown_vx_i32m1(b, 2, 4));
  vint32mf2_t c_high = __riscv_vlmul_trunc_v_i32m1_i32mf2(__riscv_vslidedown_vx_i32m1(c, 2, 4));
  vint64m1_t bc_mul = __riscv_vwmul_vv_i64m1(b_high, c_high, 2);
  vint64m1_t bc_mulx2 = __riscv_vmul_vx_i64m1(bc_mul, 2, 2);
  return __riscv_vadd_vv_i64m1(a, bc_mulx2, 2);
}

FORCE_INLINE int8x8_t vmls_s8(int8x8_t a, int8x8_t b, int8x8_t c) { return __riscv_vnmsac_vv_i8m1(a, b, c, 8); }

FORCE_INLINE int16x4_t vmls_s16(int16x4_t a, int16x4_t b, int16x4_t c) { return __riscv_vnmsac_vv_i16m1(a, b, c, 4); }

FORCE_INLINE int32x2_t vmls_s32(int32x2_t a, int32x2_t b, int32x2_t c) { return __riscv_vnmsac_vv_i32m1(a, b, c, 2); }

FORCE_INLINE float32x2_t vmls_f32(float32x2_t a, float32x2_t b, float32x2_t c) {
  return __riscv_vfnmsac_vv_f32m1(a, b, c, 2);
}

FORCE_INLINE uint8x8_t vmls_u8(uint8x8_t a, uint8x8_t b, uint8x8_t c) { return __riscv_vnmsac_vv_u8m1(a, b, c, 8); }

FORCE_INLINE uint16x4_t vmls_u16(uint16x4_t a, uint16x4_t b, uint16x4_t c) {
  return __riscv_vnmsac_vv_u16m1(a, b, c, 4);
}

FORCE_INLINE uint32x2_t vmls_u32(uint32x2_t a, uint32x2_t b, uint32x2_t c) {
  return __riscv_vnmsac_vv_u32m1(a, b, c, 2);
}

FORCE_INLINE int8x16_t vmlsq_s8(int8x16_t a, int8x16_t b, int8x16_t c) { return __riscv_vnmsac_vv_i8m1(a, b, c, 16); }

FORCE_INLINE int16x8_t vmlsq_s16(int16x8_t a, int16x8_t b, int16x8_t c) { return __riscv_vnmsac_vv_i16m1(a, b, c, 8); }

FORCE_INLINE int32x4_t vmlsq_s32(int32x4_t a, int32x4_t b, int32x4_t c) { return __riscv_vnmsac_vv_i32m1(a, b, c, 4); }

FORCE_INLINE float32x4_t vmlsq_f32(float32x4_t a, float32x4_t b, float32x4_t c) {
  return __riscv_vfnmsac_vv_f32m1(a, b, c, 4);
}

FORCE_INLINE float64x1_t vmls_f64(float64x1_t a, float64x1_t b, float64x1_t c) {
  return __riscv_vfnmsac_vv_f64m1(a, b, c, 1);
}

FORCE_INLINE float64x2_t vmlsq_f64(float64x2_t a, float64x2_t b, float64x2_t c) {
  return __riscv_vfnmsac_vv_f64m1(a, b, c, 2);
}

FORCE_INLINE uint8x16_t vmlsq_u8(uint8x16_t a, uint8x16_t b, uint8x16_t c) {
  return __riscv_vnmsac_vv_u8m1(a, b, c, 16);
}

FORCE_INLINE uint16x8_t vmlsq_u16(uint16x8_t a, uint16x8_t b, uint16x8_t c) {
  return __riscv_vnmsac_vv_u16m1(a, b, c, 8);
}

FORCE_INLINE uint32x4_t vmlsq_u32(uint32x4_t a, uint32x4_t b, uint32x4_t c) {
  return __riscv_vnmsac_vv_u32m1(a, b, c, 4);
}

FORCE_INLINE int16x8_t vmlsl_s8(int16x8_t a, int8x8_t b, int8x8_t c) {
  return __riscv_vsub_vv_i16m1(
      a, __riscv_vwmul_vv_i16m1(__riscv_vlmul_trunc_v_i8m1_i8mf2(b), __riscv_vlmul_trunc_v_i8m1_i8mf2(c), 8), 8);
}

FORCE_INLINE int32x4_t vmlsl_s16(int32x4_t a, int16x4_t b, int16x4_t c) {
  return __riscv_vsub_vv_i32m1(
      a, __riscv_vwmul_vv_i32m1(__riscv_vlmul_trunc_v_i16m1_i16mf2(b), __riscv_vlmul_trunc_v_i16m1_i16mf2(c), 4), 4);
}

FORCE_INLINE int64x2_t vmlsl_s32(int64x2_t a, int32x2_t b, int32x2_t c) {
  return __riscv_vsub_vv_i64m1(
      a, __riscv_vwmul_vv_i64m1(__riscv_vlmul_trunc_v_i32m1_i32mf2(b), __riscv_vlmul_trunc_v_i32m1_i32mf2(c), 2), 2);
}

FORCE_INLINE uint16x8_t vmlsl_u8(uint16x8_t a, uint8x8_t b, uint8x8_t c) {
  return __riscv_vsub_vv_u16m1(
      a, __riscv_vwmulu_vv_u16m1(__riscv_vlmul_trunc_v_u8m1_u8mf2(b), __riscv_vlmul_trunc_v_u8m1_u8mf2(c), 8), 8);
}

FORCE_INLINE uint32x4_t vmlsl_u16(uint32x4_t a, uint16x4_t b, uint16x4_t c) {
  return __riscv_vsub_vv_u32m1(
      a, __riscv_vwmulu_vv_u32m1(__riscv_vlmul_trunc_v_u16m1_u16mf2(b), __riscv_vlmul_trunc_v_u16m1_u16mf2(c), 4), 4);
}

FORCE_INLINE uint64x2_t vmlsl_u32(uint64x2_t a, uint32x2_t b, uint32x2_t c) {
  return __riscv_vsub_vv_u64m1(
      a, __riscv_vwmulu_vv_u64m1(__riscv_vlmul_trunc_v_u32m1_u32mf2(b), __riscv_vlmul_trunc_v_u32m1_u32mf2(c), 2), 2);
}

FORCE_INLINE int16x8_t vmlsl_high_s8(int16x8_t a, int8x16_t b, int8x16_t c) {
  vint8mf2_t b_high = __riscv_vlmul_trunc_v_i8m1_i8mf2(__riscv_vslidedown_vx_i8m1(b, 8, 16));
  vint8mf2_t c_high = __riscv_vlmul_trunc_v_i8m1_i8mf2(__riscv_vslidedown_vx_i8m1(c, 8, 16));
  return __riscv_vsub_vv_i16m1(a, __riscv_vwmul_vv_i16m1(b_high, c_high, 8), 8);
}

FORCE_INLINE int32x4_t vmlsl_high_s16(int32x4_t a, int16x8_t b, int16x8_t c) {
  vint16mf2_t b_high = __riscv_vlmul_trunc_v_i16m1_i16mf2(__riscv_vslidedown_vx_i16m1(b, 4, 8));
  vint16mf2_t c_high = __riscv_vlmul_trunc_v_i16m1_i16mf2(__riscv_vslidedown_vx_i16m1(c, 4, 8));
  return __riscv_vsub_vv_i32m1(a, __riscv_vwmul_vv_i32m1(b_high, c_high, 4), 4);
}

FORCE_INLINE int64x2_t vmlsl_high_s32(int64x2_t a, int32x4_t b, int32x4_t c) {
  vint32mf2_t b_high = __riscv_vlmul_trunc_v_i32m1_i32mf2(__riscv_vslidedown_vx_i32m1(b, 2, 4));
  vint32mf2_t c_high = __riscv_vlmul_trunc_v_i32m1_i32mf2(__riscv_vslidedown_vx_i32m1(c, 2, 4));
  return __riscv_vsub_vv_i64m1(a, __riscv_vwmul_vv_i64m1(b_high, c_high, 2), 2);
}

FORCE_INLINE uint16x8_t vmlsl_high_u8(uint16x8_t a, uint8x16_t b, uint8x16_t c) {
  vuint8mf2_t b_high = __riscv_vlmul_trunc_v_u8m1_u8mf2(__riscv_vslidedown_vx_u8m1(b, 8, 16));
  vuint8mf2_t c_high = __riscv_vlmul_trunc_v_u8m1_u8mf2(__riscv_vslidedown_vx_u8m1(c, 8, 16));
  return __riscv_vsub_vv_u16m1(a, __riscv_vwmulu_vv_u16m1(b_high, c_high, 8), 8);
}

FORCE_INLINE uint32x4_t vmlsl_high_u16(uint32x4_t a, uint16x8_t b, uint16x8_t c) {
  vuint16mf2_t b_high = __riscv_vlmul_trunc_v_u16m1_u16mf2(__riscv_vslidedown_vx_u16m1(b, 4, 8));
  vuint16mf2_t c_high = __riscv_vlmul_trunc_v_u16m1_u16mf2(__riscv_vslidedown_vx_u16m1(c, 4, 8));
  return __riscv_vsub_vv_u32m1(a, __riscv_vwmulu_vv_u32m1(b_high, c_high, 4), 4);
}

FORCE_INLINE uint64x2_t vmlsl_high_u32(uint64x2_t a, uint32x4_t b, uint32x4_t c) {
  vuint32mf2_t b_high = __riscv_vlmul_trunc_v_u32m1_u32mf2(__riscv_vslidedown_vx_u32m1(b, 2, 4));
  vuint32mf2_t c_high = __riscv_vlmul_trunc_v_u32m1_u32mf2(__riscv_vslidedown_vx_u32m1(c, 2, 4));
  return __riscv_vsub_vv_u64m1(a, __riscv_vwmulu_vv_u64m1(b_high, c_high, 2), 2);
}

FORCE_INLINE int32x4_t vqdmlsl_s16(int32x4_t a, int16x4_t b, int16x4_t c) {
  vint32m1_t bc_mul = __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vv_i32m2(b, c, 4));
  vint32m1_t bc_mulx2 = __riscv_vsll_vx_i32m1(bc_mul, 1, 4);
  return __riscv_vsub_vv_i32m1(a, bc_mulx2, 4);
}

FORCE_INLINE int64x2_t vqdmlsl_s32(int64x2_t a, int32x2_t b, int32x2_t c) {
  vint64m1_t bc_mul = __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vv_i64m2(b, c, 2));
  vint64m1_t bc_mulx2 = __riscv_vsll_vx_i64m1(bc_mul, 1, 2);
  return __riscv_vsub_vv_i64m1(a, bc_mulx2, 2);
}

FORCE_INLINE int32_t vqdmlslh_s16(int32_t a, int16_t b, int16_t c) {
  int32_t tmp = (int32_t)b * (int32_t)c;
  tmp = tmp > INT32_MAX / 2 ? INT32_MAX : tmp < INT32_MIN / 2 ? INT32_MIN : tmp * 2;
  if (tmp > 0 && a < INT32_MIN + tmp) {
    return INT32_MIN;
  } else if (tmp < 0 && a > INT32_MAX + tmp) {
    return INT32_MAX;
  }
  return a - tmp;
}

FORCE_INLINE int64_t vqdmlsls_s32(int64_t a, int32_t b, int32_t c) {
  int64_t tmp = (int64_t)b * (int64_t)c;
  tmp = tmp > INT64_MAX / 2 ? INT64_MAX : tmp < INT64_MIN / 2 ? INT64_MIN : tmp * 2;
  if (tmp > 0 && a < INT64_MIN + tmp) {
    return INT64_MIN;
  } else if (tmp < 0 && a > INT64_MAX + tmp) {
    return INT64_MAX;
  }
  return a - tmp;
}

FORCE_INLINE int32x4_t vqdmlsl_high_s16(int32x4_t a, int16x8_t b, int16x8_t c) {
  vint16mf2_t b_high = __riscv_vlmul_trunc_v_i16m1_i16mf2(__riscv_vslidedown_vx_i16m1(b, 4, 8));
  vint16mf2_t c_high = __riscv_vlmul_trunc_v_i16m1_i16mf2(__riscv_vslidedown_vx_i16m1(c, 4, 8));
  vint32m1_t bc_mul = __riscv_vwmul_vv_i32m1(b_high, c_high, 4);
  vint32m1_t bc_mulx2 = __riscv_vmul_vx_i32m1(bc_mul, 2, 4);
  return __riscv_vsub_vv_i32m1(a, bc_mulx2, 4);
}

FORCE_INLINE int64x2_t vqdmlsl_high_s32(int64x2_t a, int32x4_t b, int32x4_t c) {
  vint32mf2_t b_high = __riscv_vlmul_trunc_v_i32m1_i32mf2(__riscv_vslidedown_vx_i32m1(b, 2, 4));
  vint32mf2_t c_high = __riscv_vlmul_trunc_v_i32m1_i32mf2(__riscv_vslidedown_vx_i32m1(c, 2, 4));
  vint64m1_t bc_mul = __riscv_vwmul_vv_i64m1(b_high, c_high, 2);
  vint64m1_t bc_mulx2 = __riscv_vmul_vx_i64m1(bc_mul, 2, 2);
  return __riscv_vsub_vv_i64m1(a, bc_mulx2, 2);
}

FORCE_INLINE float32x2_t vfma_f32(float32x2_t a, float32x2_t b, float32x2_t c) {
  return __riscv_vfmacc_vv_f32m1(a, b, c, 2);
}

FORCE_INLINE float32x4_t vfmaq_f32(float32x4_t a, float32x4_t b, float32x4_t c) {
  return __riscv_vfmacc_vv_f32m1(a, b, c, 4);
}

FORCE_INLINE float64x1_t vfma_f64(float64x1_t a, float64x1_t b, float64x1_t c) {
  return __riscv_vfmacc_vv_f64m1(a, b, c, 1);
}

FORCE_INLINE float64x2_t vfmaq_f64(float64x2_t a, float64x2_t b, float64x2_t c) {
  return __riscv_vfmacc_vv_f64m1(a, b, c, 2);
}

FORCE_INLINE float32x2_t vfma_lane_f32(float32x2_t a, float32x2_t b, float32x2_t v, const int lane) {
  float32x2_t v_dup = __riscv_vrgather_vx_f32m1(v, lane, 2);
  return __riscv_vfmacc_vv_f32m1(a, b, v_dup, 2);
}

FORCE_INLINE float32x4_t vfmaq_lane_f32(float32x4_t a, float32x4_t b, float32x2_t v, const int lane) {
  float32x4_t v_dup = __riscv_vrgather_vx_f32m1(v, lane, 4);
  return __riscv_vfmacc_vv_f32m1(a, b, v_dup, 4);
}

FORCE_INLINE float64x1_t vfma_lane_f64(float64x1_t a, float64x1_t b, float64x1_t v, const int lane) {
  float64x1_t v_dup = __riscv_vrgather_vx_f64m1(v, lane, 1);
  return __riscv_vfmacc_vv_f64m1(a, b, v_dup, 1);
}

FORCE_INLINE float64x2_t vfmaq_lane_f64(float64x2_t a, float64x2_t b, float64x1_t v, const int lane) {
  float64x2_t v_dup = __riscv_vrgather_vx_f64m1(v, lane, 2);
  return __riscv_vfmacc_vv_f64m1(a, b, v_dup, 2);
}

FORCE_INLINE float32_t vfmas_lane_f32(float32_t a, float32_t b, float32x2_t v, const int lane) {
  float32_t v_lane = __riscv_vfmv_f_s_f32m1_f32(__riscv_vslidedown_vx_f32m1(v, lane, 2));
  return a + b * v_lane;
}

FORCE_INLINE float64_t vfmad_lane_f64(float64_t a, float64_t b, float64x1_t v, const int lane) {
  float64_t v_lane = __riscv_vfmv_f_s_f64m1_f64(v);
  return a + b * v_lane;
}

FORCE_INLINE float32x2_t vfma_laneq_f32(float32x2_t a, float32x2_t b, float32x4_t v, const int lane) {
  vfloat32m1_t v_dup = __riscv_vrgather_vx_f32m1(v, lane, 4);
  return __riscv_vfmacc_vv_f32m1(a, b, v_dup, 2);
}

FORCE_INLINE float32x4_t vfmaq_laneq_f32(float32x4_t a, float32x4_t b, float32x4_t v, const int lane) {
  vfloat32m1_t v_dup = __riscv_vrgather_vx_f32m1(v, lane, 4);
  return __riscv_vfmacc_vv_f32m1(a, b, v_dup, 4);
}

FORCE_INLINE float64x1_t vfma_laneq_f64(float64x1_t a, float64x1_t b, float64x2_t v, const int lane) {
  vfloat64m1_t v_dup = __riscv_vrgather_vx_f64m1(v, lane, 2);
  return __riscv_vfmacc_vv_f64m1(a, b, v_dup, 1);
}

FORCE_INLINE float64x2_t vfmaq_laneq_f64(float64x2_t a, float64x2_t b, float64x2_t v, const int lane) {
  vfloat64m1_t v_dup = __riscv_vrgather_vx_f64m1(v, lane, 2);
  return __riscv_vfmacc_vv_f64m1(a, b, v_dup, 2);
}

FORCE_INLINE float32_t vfmas_laneq_f32(float32_t a, float32_t b, float32x4_t v, const int lane) {
  float32_t v_lane = __riscv_vfmv_f_s_f32m1_f32(__riscv_vslidedown_vx_f32m1(v, lane, 4));
  return a + b * v_lane;
}

FORCE_INLINE float64_t vfmad_laneq_f64(float64_t a, float64_t b, float64x2_t v, const int lane) {
  float64_t v_lane = __riscv_vfmv_f_s_f64m1_f64(__riscv_vslidedown_vx_f64m1(v, lane, 2));
  return a + b * v_lane;
}

FORCE_INLINE float32x2_t vfms_f32(float32x2_t a, float32x2_t b, float32x2_t c) {
  return __riscv_vfnmsac_vv_f32m1(a, b, c, 2);
}

FORCE_INLINE float32x4_t vfmsq_f32(float32x4_t a, float32x4_t b, float32x4_t c) {
  return __riscv_vfnmsac_vv_f32m1(a, b, c, 4);
}

FORCE_INLINE float64x1_t vfms_f64(float64x1_t a, float64x1_t b, float64x1_t c) {
  return __riscv_vfnmsac_vv_f64m1(a, b, c, 1);
}

FORCE_INLINE float64x2_t vfmsq_f64(float64x2_t a, float64x2_t b, float64x2_t c) {
  return __riscv_vfnmsac_vv_f64m1(a, b, c, 2);
}

FORCE_INLINE float32x2_t vfms_lane_f32(float32x2_t a, float32x2_t b, float32x2_t v, const int lane) {
  float32x2_t v_dup = __riscv_vrgather_vx_f32m1(v, lane, 2);
  return __riscv_vfnmsac_vv_f32m1(a, b, v_dup, 2);
}

FORCE_INLINE float32x4_t vfmsq_lane_f32(float32x4_t a, float32x4_t b, float32x2_t v, const int lane) {
  float32x4_t v_dup = __riscv_vrgather_vx_f32m1(v, lane, 4);
  return __riscv_vfnmsac_vv_f32m1(a, b, v_dup, 4);
}

FORCE_INLINE float64x1_t vfms_lane_f64(float64x1_t a, float64x1_t b, float64x1_t v, const int lane) {
  float64x1_t v_dup = __riscv_vrgather_vx_f64m1(v, lane, 1);
  return __riscv_vfnmsac_vv_f64m1(a, b, v_dup, 1);
}

FORCE_INLINE float64x2_t vfmsq_lane_f64(float64x2_t a, float64x2_t b, float64x1_t v, const int lane) {
  float64x2_t v_dup = __riscv_vrgather_vx_f64m1(v, lane, 2);
  return __riscv_vfnmsac_vv_f64m1(a, b, v_dup, 2);
}

FORCE_INLINE float32_t vfmss_lane_f32(float32_t a, float32_t b, float32x2_t v, const int lane) {
  float32_t v_lane = __riscv_vfmv_f_s_f32m1_f32(__riscv_vslidedown_vx_f32m1(v, lane, 2));
  return a - b * v_lane;
}

FORCE_INLINE float64_t vfmsd_lane_f64(float64_t a, float64_t b, float64x1_t v, const int lane) {
  float64_t v_lane = __riscv_vfmv_f_s_f64m1_f64(v);
  return a - b * v_lane;
}

FORCE_INLINE float32x2_t vfms_laneq_f32(float32x2_t a, float32x2_t b, float32x4_t v, const int lane) {
  vfloat32m1_t v_dup = __riscv_vrgather_vx_f32m1(v, lane, 4);
  return __riscv_vfnmsac_vv_f32m1(a, b, v_dup, 2);
}

FORCE_INLINE float32x4_t vfmsq_laneq_f32(float32x4_t a, float32x4_t b, float32x4_t v, const int lane) {
  vfloat32m1_t v_dup = __riscv_vrgather_vx_f32m1(v, lane, 4);
  return __riscv_vfnmsac_vv_f32m1(a, b, v_dup, 4);
}

FORCE_INLINE float64x1_t vfms_laneq_f64(float64x1_t a, float64x1_t b, float64x2_t v, const int lane) {
  vfloat64m1_t v_dup = __riscv_vrgather_vx_f64m1(v, lane, 2);
  return __riscv_vfnmsac_vv_f64m1(a, b, v_dup, 1);
}

FORCE_INLINE float64x2_t vfmsq_laneq_f64(float64x2_t a, float64x2_t b, float64x2_t v, const int lane) {
  vfloat64m1_t v_dup = __riscv_vrgather_vx_f64m1(v, lane, 2);
  return __riscv_vfnmsac_vv_f64m1(a, b, v_dup, 2);
}

FORCE_INLINE float32_t vfmss_laneq_f32(float32_t a, float32_t b, float32x4_t v, const int lane) {
  float32_t v_lane = __riscv_vfmv_f_s_f32m1_f32(__riscv_vslidedown_vx_f32m1(v, lane, 4));
  return a - b * v_lane;
}

FORCE_INLINE float64_t vfmsd_laneq_f64(float64_t a, float64_t b, float64x2_t v, const int lane) {
  float64_t v_lane = __riscv_vfmv_f_s_f64m1_f64(__riscv_vslidedown_vx_f64m1(v, lane, 2));
  return a - b * v_lane;
}

FORCE_INLINE float32x2_t vrndn_f32(float32x2_t a) {
  return __riscv_vfcvt_f_x_v_f32m1(__riscv_vfcvt_x_f_v_i32m1_rm(a, __RISCV_FRM_RNE, 2), 2);
}

FORCE_INLINE float32x4_t vrndnq_f32(float32x4_t a) {
  return __riscv_vfcvt_f_x_v_f32m1(__riscv_vfcvt_x_f_v_i32m1_rm(a, __RISCV_FRM_RNE, 4), 4);
}

// FORCE_INLINE float64x1_t vrndn_f64(float64x1_t a);

// FORCE_INLINE float64x2_t vrndnq_f64(float64x2_t a);

// FORCE_INLINE float32_t vrndns_f32(float32_t a);

FORCE_INLINE float32x2_t vrnda_f32(float32x2_t a) {
  return __riscv_vfcvt_f_x_v_f32m1(__riscv_vfcvt_x_f_v_i32m1_rm(a, __RISCV_FRM_RMM, 2), 2);
}

FORCE_INLINE float32x4_t vrndaq_f32(float32x4_t a) {
  return __riscv_vfcvt_f_x_v_f32m1(__riscv_vfcvt_x_f_v_i32m1_rm(a, __RISCV_FRM_RMM, 4), 4);
}

// FORCE_INLINE float64x1_t vrnda_f64(float64x1_t a);

// FORCE_INLINE float64x2_t vrndaq_f64(float64x2_t a);

// FORCE_INLINE float32x2_t vrndi_f32(float32x2_t a);

// FORCE_INLINE float32x4_t vrndiq_f32(float32x4_t a);

// FORCE_INLINE float64x1_t vrndi_f64(float64x1_t a);

// FORCE_INLINE float64x2_t vrndiq_f64(float64x2_t a);

FORCE_INLINE float32x2_t vrndp_f32(float32x2_t a) {
  return __riscv_vfcvt_f_x_v_f32m1(__riscv_vfcvt_x_f_v_i32m1_rm(a, __RISCV_FRM_RUP, 2), 2);
}

FORCE_INLINE float32x4_t vrndpq_f32(float32x4_t a) {
  return __riscv_vfcvt_f_x_v_f32m1(__riscv_vfcvt_x_f_v_i32m1_rm(a, __RISCV_FRM_RUP, 4), 4);
}

// FORCE_INLINE float64x1_t vrndp_f64(float64x1_t a);

// FORCE_INLINE float64x2_t vrndpq_f64(float64x2_t a);

FORCE_INLINE float32x2_t vrndm_f32(float32x2_t a) {
  return __riscv_vfcvt_f_x_v_f32m1(__riscv_vfcvt_x_f_v_i32m1_rm(a, __RISCV_FRM_RDN, 2), 2);
}

FORCE_INLINE float32x4_t vrndmq_f32(float32x4_t a) {
  return __riscv_vfcvt_f_x_v_f32m1(__riscv_vfcvt_x_f_v_i32m1_rm(a, __RISCV_FRM_RDN, 4), 4);
}

// FORCE_INLINE float64x1_t vrndm_f64(float64x1_t a);

// FORCE_INLINE float64x2_t vrndmq_f64(float64x2_t a);

// FORCE_INLINE float32x2_t vrndx_f32(float32x2_t a);

// FORCE_INLINE float32x4_t vrndxq_f32(float32x4_t a);

// FORCE_INLINE float64x1_t vrndx_f64(float64x1_t a);

// FORCE_INLINE float64x2_t vrndxq_f64(float64x2_t a);

FORCE_INLINE float32x2_t vrnd_f32(float32x2_t a) {
  return __riscv_vfcvt_f_x_v_f32m1(__riscv_vfcvt_x_f_v_i32m1_rm(a, __RISCV_FRM_RTZ, 2), 2);
}

FORCE_INLINE float32x4_t vrndq_f32(float32x4_t a) {
  return __riscv_vfcvt_f_x_v_f32m1(__riscv_vfcvt_x_f_v_i32m1_rm(a, __RISCV_FRM_RTZ, 4), 4);
}

// FORCE_INLINE float64x1_t vrnd_f64(float64x1_t a);

// FORCE_INLINE float64x2_t vrndq_f64(float64x2_t a);

FORCE_INLINE int8x8_t vsub_s8(int8x8_t a, int8x8_t b) { return __riscv_vsub_vv_i8m1(a, b, 8); }

FORCE_INLINE int16x4_t vsub_s16(int16x4_t a, int16x4_t b) { return __riscv_vsub_vv_i16m1(a, b, 4); }

FORCE_INLINE int32x2_t vsub_s32(int32x2_t a, int32x2_t b) { return __riscv_vsub_vv_i32m1(a, b, 2); }

FORCE_INLINE float32x2_t vsub_f32(float32x2_t a, float32x2_t b) { return __riscv_vfsub_vv_f32m1(a, b, 2); }

FORCE_INLINE uint8x8_t vsub_u8(uint8x8_t a, uint8x8_t b) { return __riscv_vsub_vv_u8m1(a, b, 8); }

FORCE_INLINE uint16x4_t vsub_u16(uint16x4_t a, uint16x4_t b) { return __riscv_vsub_vv_u16m1(a, b, 4); }

FORCE_INLINE uint32x2_t vsub_u32(uint32x2_t a, uint32x2_t b) { return __riscv_vsub_vv_u32m1(a, b, 2); }

FORCE_INLINE int64x1_t vsub_s64(int64x1_t a, int64x1_t b) { return __riscv_vsub_vv_i64m1(a, b, 2); }

FORCE_INLINE uint64x1_t vsub_u64(uint64x1_t a, uint64x1_t b) { return __riscv_vsub_vv_u64m1(a, b, 2); }

FORCE_INLINE int8x16_t vsubq_s8(int8x16_t a, int8x16_t b) { return __riscv_vsub_vv_i8m1(a, b, 16); }

FORCE_INLINE int16x8_t vsubq_s16(int16x8_t a, int16x8_t b) { return __riscv_vsub_vv_i16m1(a, b, 8); }

FORCE_INLINE int32x4_t vsubq_s32(int32x4_t a, int32x4_t b) { return __riscv_vsub_vv_i32m1(a, b, 4); }

FORCE_INLINE int64x2_t vsubq_s64(int64x2_t a, int64x2_t b) { return __riscv_vsub_vv_i64m1(a, b, 2); }

FORCE_INLINE float32x4_t vsubq_f32(float32x4_t a, float32x4_t b) { return __riscv_vfsub_vv_f32m1(a, b, 4); }

FORCE_INLINE float64x1_t vsub_f64(float64x1_t a, float64x1_t b) { return __riscv_vfsub_vv_f64m1(a, b, 1); }

FORCE_INLINE float64x2_t vsubq_f64(float64x2_t a, float64x2_t b) { return __riscv_vfsub_vv_f64m1(a, b, 2); }

FORCE_INLINE int64_t vsubd_s64(int64_t a, int64_t b) { return a - b; }

FORCE_INLINE uint64_t vsubd_u64(uint64_t a, uint64_t b) { return a - b; }

FORCE_INLINE uint8x16_t vsubq_u8(uint8x16_t a, uint8x16_t b) { return __riscv_vsub_vv_u8m1(a, b, 16); }

FORCE_INLINE uint16x8_t vsubq_u16(uint16x8_t a, uint16x8_t b) { return __riscv_vsub_vv_u16m1(a, b, 8); }

FORCE_INLINE uint32x4_t vsubq_u32(uint32x4_t a, uint32x4_t b) { return __riscv_vsub_vv_u32m1(a, b, 4); }

FORCE_INLINE uint64x2_t vsubq_u64(uint64x2_t a, uint64x2_t b) { return __riscv_vsub_vv_u64m1(a, b, 2); }

FORCE_INLINE int16x8_t vsubl_s8(int8x8_t a, int8x8_t b) {
  return __riscv_vwsub_vv_i16m1(__riscv_vlmul_trunc_v_i8m1_i8mf2(a), __riscv_vlmul_trunc_v_i8m1_i8mf2(b), 8);
}

FORCE_INLINE int32x4_t vsubl_s16(int16x4_t a, int16x4_t b) {
  return __riscv_vwsub_vv_i32m1(__riscv_vlmul_trunc_v_i16m1_i16mf2(a), __riscv_vlmul_trunc_v_i16m1_i16mf2(b), 4);
}

FORCE_INLINE int64x2_t vsubl_s32(int32x2_t a, int32x2_t b) {
  return __riscv_vwsub_vv_i64m1(__riscv_vlmul_trunc_v_i32m1_i32mf2(a), __riscv_vlmul_trunc_v_i32m1_i32mf2(b), 2);
}

FORCE_INLINE uint16x8_t vsubl_u8(uint8x8_t a, uint8x8_t b) {
  return __riscv_vwsubu_vv_u16m1(__riscv_vlmul_trunc_v_u8m1_u8mf2(a), __riscv_vlmul_trunc_v_u8m1_u8mf2(b), 8);
}

FORCE_INLINE uint32x4_t vsubl_u16(uint16x4_t a, uint16x4_t b) {
  return __riscv_vwsubu_vv_u32m1(__riscv_vlmul_trunc_v_u16m1_u16mf2(a), __riscv_vlmul_trunc_v_u16m1_u16mf2(b), 4);
}

FORCE_INLINE uint64x2_t vsubl_u32(uint32x2_t a, uint32x2_t b) {
  return __riscv_vwsubu_vv_u64m1(__riscv_vlmul_trunc_v_u32m1_u32mf2(a), __riscv_vlmul_trunc_v_u32m1_u32mf2(b), 2);
}

FORCE_INLINE int16x8_t vsubl_high_s8(int8x16_t a, int8x16_t b) {
  vint8m1_t a_high = __riscv_vslidedown_vx_i8m1(a, 8, 16);
  vint8m1_t b_high = __riscv_vslidedown_vx_i8m1(b, 8, 16);
  return __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vwsub_vv_i16m2(a_high, b_high, 8));
}

FORCE_INLINE int32x4_t vsubl_high_s16(int16x8_t a, int16x8_t b) {
  vint16m1_t a_high = __riscv_vslidedown_vx_i16m1(a, 4, 8);
  vint16m1_t b_high = __riscv_vslidedown_vx_i16m1(b, 4, 8);
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwsub_vv_i32m2(a_high, b_high, 4));
}

FORCE_INLINE int64x2_t vsubl_high_s32(int32x4_t a, int32x4_t b) {
  vint32m1_t a_high = __riscv_vslidedown_vx_i32m1(a, 2, 4);
  vint32m1_t b_high = __riscv_vslidedown_vx_i32m1(b, 2, 4);
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwsub_vv_i64m2(a_high, b_high, 2));
}

FORCE_INLINE uint16x8_t vsubl_high_u8(uint8x16_t a, uint8x16_t b) {
  vuint8m1_t a_high = __riscv_vslidedown_vx_u8m1(a, 8, 16);
  vuint8m1_t b_high = __riscv_vslidedown_vx_u8m1(b, 8, 16);
  return __riscv_vlmul_trunc_v_u16m2_u16m1(__riscv_vwsubu_vv_u16m2(a_high, b_high, 8));
}

FORCE_INLINE uint32x4_t vsubl_high_u16(uint16x8_t a, uint16x8_t b) {
  vuint16m1_t a_high = __riscv_vslidedown_vx_u16m1(a, 4, 8);
  vuint16m1_t b_high = __riscv_vslidedown_vx_u16m1(b, 4, 8);
  return __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwsubu_vv_u32m2(a_high, b_high, 4));
}

FORCE_INLINE uint64x2_t vsubl_high_u32(uint32x4_t a, uint32x4_t b) {
  vuint32m1_t a_high = __riscv_vslidedown_vx_u32m1(a, 2, 4);
  vuint32m1_t b_high = __riscv_vslidedown_vx_u32m1(b, 2, 4);
  return __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwsubu_vv_u64m2(a_high, b_high, 2));
}

FORCE_INLINE int16x8_t vsubw_s8(int16x8_t a, int8x8_t b) {
  return __riscv_vwmacc_vx_i16m1(a, -1, __riscv_vlmul_trunc_v_i8m1_i8mf2(b), 8);
}

FORCE_INLINE int32x4_t vsubw_s16(int32x4_t a, int16x4_t b) {
  return __riscv_vwmacc_vx_i32m1(a, -1, __riscv_vlmul_trunc_v_i16m1_i16mf2(b), 4);
}

FORCE_INLINE int64x2_t vsubw_s32(int64x2_t a, int32x2_t b) {
  return __riscv_vwmacc_vx_i64m1(a, -1, __riscv_vlmul_trunc_v_i32m1_i32mf2(b), 2);
}

FORCE_INLINE uint16x8_t vsubw_u8(uint16x8_t a, uint8x8_t b) {
  vuint16m1_t b_ext = __riscv_vzext_vf2_u16m1(__riscv_vlmul_trunc_v_u8m1_u8mf2(b), 8);
  return __riscv_vsub_vv_u16m1(a, b_ext, 8);
}

FORCE_INLINE uint32x4_t vsubw_u16(uint32x4_t a, uint16x4_t b) {
  vuint32m1_t b_ext = __riscv_vzext_vf2_u32m1(__riscv_vlmul_trunc_v_u16m1_u16mf2(b), 4);
  return __riscv_vsub_vv_u32m1(a, b_ext, 4);
}

FORCE_INLINE uint64x2_t vsubw_u32(uint64x2_t a, uint32x2_t b) {
  vuint64m1_t b_ext = __riscv_vzext_vf2_u64m1(__riscv_vlmul_trunc_v_u32m1_u32mf2(b), 2);
  return __riscv_vsub_vv_u64m1(a, b_ext, 2);
}

FORCE_INLINE int16x8_t vsubw_high_s8(int16x8_t a, int8x16_t b) {
  vint8m1_t b_high = __riscv_vslidedown_vx_i8m1(b, 8, 16);
  return __riscv_vwmacc_vx_i16m1(a, -1, __riscv_vlmul_trunc_v_i8m1_i8mf2(b_high), 8);
}

FORCE_INLINE int32x4_t vsubw_high_s16(int32x4_t a, int16x8_t b) {
  vint16m1_t b_high = __riscv_vslidedown_vx_i16m1(b, 4, 8);
  return __riscv_vwmacc_vx_i32m1(a, -1, __riscv_vlmul_trunc_v_i16m1_i16mf2(b_high), 4);
}

FORCE_INLINE int64x2_t vsubw_high_s32(int64x2_t a, int32x4_t b) {
  vint32m1_t b_high = __riscv_vslidedown_vx_i32m1(b, 2, 4);
  return __riscv_vwmacc_vx_i64m1(a, -1, __riscv_vlmul_trunc_v_i32m1_i32mf2(b_high), 2);
}

FORCE_INLINE uint16x8_t vsubw_high_u8(uint16x8_t a, uint8x16_t b) {
  vuint8m1_t b_high = __riscv_vslidedown_vx_u8m1(b, 8, 16);
  vuint16m1_t b_ext = __riscv_vzext_vf2_u16m1(__riscv_vlmul_trunc_v_u8m1_u8mf2(b_high), 8);
  return __riscv_vsub_vv_u16m1(a, b_ext, 8);
}

FORCE_INLINE uint32x4_t vsubw_high_u16(uint32x4_t a, uint16x8_t b) {
  vuint16m1_t b_high = __riscv_vslidedown_vx_u16m1(b, 4, 8);
  vuint32m1_t b_ext = __riscv_vzext_vf2_u32m1(__riscv_vlmul_trunc_v_u16m1_u16mf2(b_high), 4);
  return __riscv_vsub_vv_u32m1(a, b_ext, 4);
}

FORCE_INLINE uint64x2_t vsubw_high_u32(uint64x2_t a, uint32x4_t b) {
  vuint32m1_t b_high = __riscv_vslidedown_vx_u32m1(b, 2, 4);
  vuint64m1_t b_ext = __riscv_vzext_vf2_u64m1(__riscv_vlmul_trunc_v_u32m1_u32mf2(b_high), 2);
  return __riscv_vsub_vv_u64m1(a, b_ext, 2);
}

FORCE_INLINE int8x8_t vhsub_s8(int8x8_t a, int8x8_t b) { return __riscv_vasub_vv_i8m1(a, b, __RISCV_VXRM_RDN, 8); }

FORCE_INLINE int16x4_t vhsub_s16(int16x4_t a, int16x4_t b) { return __riscv_vasub_vv_i16m1(a, b, __RISCV_VXRM_RDN, 4); }

FORCE_INLINE int32x2_t vhsub_s32(int32x2_t a, int32x2_t b) { return __riscv_vasub_vv_i32m1(a, b, __RISCV_VXRM_RDN, 2); }

FORCE_INLINE uint8x8_t vhsub_u8(uint8x8_t a, uint8x8_t b) { return __riscv_vasubu_vv_u8m1(a, b, __RISCV_VXRM_RDN, 8); }

FORCE_INLINE uint16x4_t vhsub_u16(uint16x4_t a, uint16x4_t b) {
  return __riscv_vasubu_vv_u16m1(a, b, __RISCV_VXRM_RDN, 4);
}

FORCE_INLINE uint32x2_t vhsub_u32(uint32x2_t a, uint32x2_t b) {
  return __riscv_vasubu_vv_u32m1(a, b, __RISCV_VXRM_RDN, 2);
}

FORCE_INLINE int8x16_t vhsubq_s8(int8x16_t a, int8x16_t b) { return __riscv_vasub_vv_i8m1(a, b, __RISCV_VXRM_RDN, 16); }

FORCE_INLINE int16x8_t vhsubq_s16(int16x8_t a, int16x8_t b) {
  return __riscv_vasub_vv_i16m1(a, b, __RISCV_VXRM_RDN, 8);
}

FORCE_INLINE int32x4_t vhsubq_s32(int32x4_t a, int32x4_t b) {
  return __riscv_vasub_vv_i32m1(a, b, __RISCV_VXRM_RDN, 4);
}

FORCE_INLINE uint8x16_t vhsubq_u8(uint8x16_t a, uint8x16_t b) {
  return __riscv_vasubu_vv_u8m1(a, b, __RISCV_VXRM_RDN, 16);
}

FORCE_INLINE uint16x8_t vhsubq_u16(uint16x8_t a, uint16x8_t b) {
  return __riscv_vasubu_vv_u16m1(a, b, __RISCV_VXRM_RDN, 8);
}

FORCE_INLINE uint32x4_t vhsubq_u32(uint32x4_t a, uint32x4_t b) {
  return __riscv_vasubu_vv_u32m1(a, b, __RISCV_VXRM_RDN, 4);
}

FORCE_INLINE int8x8_t vqsub_s8(int8x8_t a, int8x8_t b) { return __riscv_vssub_vv_i8m1(a, b, 8); }

FORCE_INLINE int16x4_t vqsub_s16(int16x4_t a, int16x4_t b) { return __riscv_vssub_vv_i16m1(a, b, 4); }

FORCE_INLINE int32x2_t vqsub_s32(int32x2_t a, int32x2_t b) { return __riscv_vssub_vv_i32m1(a, b, 2); }

FORCE_INLINE int64x1_t vqsub_s64(int64x1_t a, int64x1_t b) { return __riscv_vssub_vv_i64m1(a, b, 1); }

FORCE_INLINE uint8x8_t vqsub_u8(uint8x8_t a, uint8x8_t b) { return __riscv_vssubu_vv_u8m1(a, b, 8); }

FORCE_INLINE uint16x4_t vqsub_u16(uint16x4_t a, uint16x4_t b) { return __riscv_vssubu_vv_u16m1(a, b, 4); }

FORCE_INLINE uint32x2_t vqsub_u32(uint32x2_t a, uint32x2_t b) { return __riscv_vssubu_vv_u32m1(a, b, 2); }

FORCE_INLINE uint64x1_t vqsub_u64(uint64x1_t a, uint64x1_t b) { return __riscv_vssubu_vv_u64m1(a, b, 1); }

FORCE_INLINE int8x16_t vqsubq_s8(int8x16_t a, int8x16_t b) { return __riscv_vssub_vv_i8m1(a, b, 16); }

FORCE_INLINE int16x8_t vqsubq_s16(int16x8_t a, int16x8_t b) { return __riscv_vssub_vv_i16m1(a, b, 8); }

FORCE_INLINE int32x4_t vqsubq_s32(int32x4_t a, int32x4_t b) { return __riscv_vssub_vv_i32m1(a, b, 4); }

FORCE_INLINE int64x2_t vqsubq_s64(int64x2_t a, int64x2_t b) { return __riscv_vssub_vv_i64m1(a, b, 2); }

FORCE_INLINE uint8x16_t vqsubq_u8(uint8x16_t a, uint8x16_t b) { return __riscv_vssubu_vv_u8m1(a, b, 16); }

FORCE_INLINE uint16x8_t vqsubq_u16(uint16x8_t a, uint16x8_t b) { return __riscv_vssubu_vv_u16m1(a, b, 8); }

FORCE_INLINE uint32x4_t vqsubq_u32(uint32x4_t a, uint32x4_t b) { return __riscv_vssubu_vv_u32m1(a, b, 4); }

FORCE_INLINE uint64x2_t vqsubq_u64(uint64x2_t a, uint64x2_t b) { return __riscv_vssubu_vv_u64m1(a, b, 2); }

FORCE_INLINE int8_t vqsubb_s8(int8_t a, int8_t b) { return sat_sub_int8(a, b); }

FORCE_INLINE int16_t vqsubh_s16(int16_t a, int16_t b) { return sat_sub_int16(a, b); }

FORCE_INLINE int32_t vqsubs_s32(int32_t a, int32_t b) { return sat_sub_int32(a, b); }

FORCE_INLINE int64_t vqsubd_s64(int64_t a, int64_t b) { return sat_sub_int64(a, b); }

FORCE_INLINE uint8_t vqsubb_u8(uint8_t a, uint8_t b) { return sat_sub_uint8(a, b); }

FORCE_INLINE uint16_t vqsubh_u16(uint16_t a, uint16_t b) { return sat_sub_uint16(a, b); }

FORCE_INLINE uint32_t vqsubs_u32(uint32_t a, uint32_t b) { return sat_sub_uint32(a, b); }

FORCE_INLINE uint64_t vqsubd_u64(uint64_t a, uint64_t b) { return sat_sub_uint64(a, b); }

FORCE_INLINE int8x8_t vsubhn_s16(int16x8_t a, int16x8_t b) {
  vint16m2_t ab_sub = __riscv_vlmul_ext_v_i16m1_i16m2(__riscv_vsub_vv_i16m1(a, b, 8));
  return __riscv_vnsra_wx_i8m1(ab_sub, 8, 8);
}

FORCE_INLINE int16x4_t vsubhn_s32(int32x4_t a, int32x4_t b) {
  vint32m2_t ab_sub = __riscv_vlmul_ext_v_i32m1_i32m2(__riscv_vsub_vv_i32m1(a, b, 4));
  return __riscv_vnsra_wx_i16m1(ab_sub, 16, 4);
}

FORCE_INLINE int32x2_t vsubhn_s64(int64x2_t a, int64x2_t b) {
  vint64m2_t ab_sub = __riscv_vlmul_ext_v_i64m1_i64m2(__riscv_vsub_vv_i64m1(a, b, 2));
  return __riscv_vnsra_wx_i32m1(ab_sub, 32, 2);
}

FORCE_INLINE uint8x8_t vsubhn_u16(uint16x8_t a, uint16x8_t b) {
  vuint16m2_t ab_sub = __riscv_vlmul_ext_v_u16m1_u16m2(__riscv_vsub_vv_u16m1(a, b, 8));
  return __riscv_vnsrl_wx_u8m1(ab_sub, 8, 8);
}

FORCE_INLINE uint16x4_t vsubhn_u32(uint32x4_t a, uint32x4_t b) {
  vuint32m2_t ab_sub = __riscv_vlmul_ext_v_u32m1_u32m2(__riscv_vsub_vv_u32m1(a, b, 4));
  return __riscv_vnsrl_wx_u16m1(ab_sub, 16, 4);
}

FORCE_INLINE uint32x2_t vsubhn_u64(uint64x2_t a, uint64x2_t b) {
  vuint64m2_t ab_sub = __riscv_vlmul_ext_v_u64m1_u64m2(__riscv_vsub_vv_u64m1(a, b, 2));
  return __riscv_vnsrl_wx_u32m1(ab_sub, 32, 2);
}

FORCE_INLINE int8x16_t vsubhn_high_s16(int8x8_t r, int16x8_t a, int16x8_t b) {
  vint16m1_t ab_add = __riscv_vsub_vv_i16m1(a, b, 8);
  vint8m1_t addhn = __riscv_vlmul_ext_v_i8mf2_i8m1(__riscv_vnsra_wx_i8mf2(ab_add, 8, 8));
  return __riscv_vslideup_vx_i8m1(r, addhn, 8, 16);
}

FORCE_INLINE int16x8_t vsubhn_high_s32(int16x4_t r, int32x4_t a, int32x4_t b) {
  vint32m1_t ab_add = __riscv_vsub_vv_i32m1(a, b, 4);
  vint16m1_t addhn = __riscv_vlmul_ext_v_i16mf2_i16m1(__riscv_vnsra_wx_i16mf2(ab_add, 16, 4));
  return __riscv_vslideup_vx_i16m1(r, addhn, 4, 8);
}

FORCE_INLINE int32x4_t vsubhn_high_s64(int32x2_t r, int64x2_t a, int64x2_t b) {
  vint64m1_t ab_add = __riscv_vsub_vv_i64m1(a, b, 2);
  vint32m1_t addhn = __riscv_vlmul_ext_v_i32mf2_i32m1(__riscv_vnsra_wx_i32mf2(ab_add, 32, 2));
  return __riscv_vslideup_vx_i32m1(r, addhn, 2, 4);
}

FORCE_INLINE uint8x16_t vsubhn_high_u16(uint8x8_t r, uint16x8_t a, uint16x8_t b) {
  vuint16m1_t ab_add = __riscv_vsub_vv_u16m1(a, b, 8);
  vuint8m1_t addhn = __riscv_vlmul_ext_v_u8mf2_u8m1(__riscv_vnsrl_wx_u8mf2(ab_add, 8, 8));
  return __riscv_vslideup_vx_u8m1(r, addhn, 8, 16);
}

FORCE_INLINE uint16x8_t vsubhn_high_u32(uint16x4_t r, uint32x4_t a, uint32x4_t b) {
  vuint32m1_t ab_add = __riscv_vsub_vv_u32m1(a, b, 4);
  vuint16m1_t addhn = __riscv_vlmul_ext_v_u16mf2_u16m1(__riscv_vnsrl_wx_u16mf2(ab_add, 16, 4));
  return __riscv_vslideup_vx_u16m1(r, addhn, 4, 8);
}

FORCE_INLINE uint32x4_t vsubhn_high_u64(uint32x2_t r, uint64x2_t a, uint64x2_t b) {
  vuint64m1_t ab_add = __riscv_vsub_vv_u64m1(a, b, 2);
  vuint32m1_t addhn = __riscv_vlmul_ext_v_u32mf2_u32m1(__riscv_vnsrl_wx_u32mf2(ab_add, 32, 2));
  return __riscv_vslideup_vx_u32m1(r, addhn, 2, 4);
}

FORCE_INLINE int8x8_t vrsubhn_s16(int16x8_t a, int16x8_t b) {
  vint16m1_t add_ab = __riscv_vsub_vv_i16m1(a, b, 8);
  vint16m1_t add_round = __riscv_vadd_vx_i16m1(add_ab, 1 << 7, 8);
  return __riscv_vnsra_wx_i8m1(__riscv_vlmul_ext_v_i16m1_i16m2(add_round), 8, 8);
}

FORCE_INLINE int16x4_t vrsubhn_s32(int32x4_t a, int32x4_t b) {
  vint32m1_t ab_sub = __riscv_vsub_vv_i32m1(a, b, 4);
  vint32m1_t sub_round = __riscv_vadd_vx_i32m1(ab_sub, 1 << 15, 4);
  return __riscv_vnsra_wx_i16m1(__riscv_vlmul_ext_v_i32m1_i32m2(sub_round), 16, 4);
}

FORCE_INLINE int32x2_t vrsubhn_s64(int64x2_t a, int64x2_t b) {
  vint64m1_t ab_sub = __riscv_vsub_vv_i64m1(a, b, 2);
  vint64m1_t sub_round = __riscv_vadd_vx_i64m1(ab_sub, (int64_t)1 << 31, 2);
  return __riscv_vnsra_wx_i32m1(__riscv_vlmul_ext_v_i64m1_i64m2(sub_round), 32, 2);
}

FORCE_INLINE uint8x8_t vrsubhn_u16(uint16x8_t a, uint16x8_t b) {
  // FIXME use vnclipu
  vuint16m1_t add_ab = __riscv_vsub_vv_u16m1(a, b, 8);
  vuint16m1_t add_round = __riscv_vadd_vx_u16m1(add_ab, 1 << 7, 8);
  return __riscv_vnsrl_wx_u8m1(__riscv_vlmul_ext_v_u16m1_u16m2(add_round), 8, 8);
}

FORCE_INLINE uint16x4_t vrsubhn_u32(uint32x4_t a, uint32x4_t b) {
  vuint32m1_t add_ab = __riscv_vsub_vv_u32m1(a, b, 4);
  vuint32m1_t add_round = __riscv_vadd_vx_u32m1(add_ab, 1 << 15, 4);
  return __riscv_vnsrl_wx_u16m1(__riscv_vlmul_ext_v_u32m1_u32m2(add_round), 16, 4);
}

FORCE_INLINE uint32x2_t vrsubhn_u64(uint64x2_t a, uint64x2_t b) {
  vuint64m1_t add_ab = __riscv_vsub_vv_u64m1(a, b, 2);
  vuint64m1_t add_round = __riscv_vadd_vx_u64m1(add_ab, (int64_t)1 << 31, 2);
  return __riscv_vnsrl_wx_u32m1(__riscv_vlmul_ext_v_u64m1_u64m2(add_round), 32, 2);
}

FORCE_INLINE int8x16_t vrsubhn_high_s16(int8x8_t r, int16x8_t a, int16x8_t b) {
  vint16m1_t add_ab = __riscv_vsub_vv_i16m1(a, b, 8);
  vint16m1_t add_round = __riscv_vadd_vx_i16m1(add_ab, 1 << 7, 8);
  vint8m1_t subhn = __riscv_vnsra_wx_i8m1(__riscv_vlmul_ext_v_i16m1_i16m2(add_round), 8, 8);
  return __riscv_vslideup_vx_i8m1(r, subhn, 8, 16);
}

FORCE_INLINE int16x8_t vrsubhn_high_s32(int16x4_t r, int32x4_t a, int32x4_t b) {
  vint32m1_t ab_sub = __riscv_vsub_vv_i32m1(a, b, 4);
  vint32m1_t sub_round = __riscv_vadd_vx_i32m1(ab_sub, 1 << 15, 4);
  vint16m1_t subhn = __riscv_vnsra_wx_i16m1(__riscv_vlmul_ext_v_i32m1_i32m2(sub_round), 16, 4);
  return __riscv_vslideup_vx_i16m1(r, subhn, 4, 8);
}

FORCE_INLINE int32x4_t vrsubhn_high_s64(int32x2_t r, int64x2_t a, int64x2_t b) {
  vint64m1_t ab_sub = __riscv_vsub_vv_i64m1(a, b, 2);
  vint64m1_t sub_round = __riscv_vadd_vx_i64m1(ab_sub, (int64_t)1 << 31, 2);
  vint32m1_t subhn = __riscv_vnsra_wx_i32m1(__riscv_vlmul_ext_v_i64m1_i64m2(sub_round), 32, 2);
  return __riscv_vslideup_vx_i32m1(r, subhn, 2, 4);
}

FORCE_INLINE uint8x16_t vrsubhn_high_u16(uint8x8_t r, uint16x8_t a, uint16x8_t b) {
  vuint16m1_t add_ab = __riscv_vsub_vv_u16m1(a, b, 8);
  vuint16m1_t add_round = __riscv_vadd_vx_u16m1(add_ab, 1 << 7, 8);
  vuint8m1_t subhn = __riscv_vnsrl_wx_u8m1(__riscv_vlmul_ext_v_u16m1_u16m2(add_round), 8, 8);
  return __riscv_vslideup_vx_u8m1(r, subhn, 8, 16);
}

FORCE_INLINE uint16x8_t vrsubhn_high_u32(uint16x4_t r, uint32x4_t a, uint32x4_t b) {
  vuint32m1_t add_ab = __riscv_vsub_vv_u32m1(a, b, 4);
  vuint32m1_t add_round = __riscv_vadd_vx_u32m1(add_ab, 1 << 15, 4);
  vuint16m1_t subhn = __riscv_vnsrl_wx_u16m1(__riscv_vlmul_ext_v_u32m1_u32m2(add_round), 16, 4);
  return __riscv_vslideup_vx_u16m1(r, subhn, 4, 8);
}

FORCE_INLINE uint32x4_t vrsubhn_high_u64(uint32x2_t r, uint64x2_t a, uint64x2_t b) {
  vuint64m1_t add_ab = __riscv_vsub_vv_u64m1(a, b, 2);
  vuint64m1_t add_round = __riscv_vadd_vx_u64m1(add_ab, (int64_t)1 << 31, 2);
  vuint32m1_t subhn = __riscv_vnsrl_wx_u32m1(__riscv_vlmul_ext_v_u64m1_u64m2(add_round), 32, 2);
  return __riscv_vslideup_vx_u32m1(r, subhn, 2, 4);
}

FORCE_INLINE uint8x8_t vceq_s8(int8x8_t a, int8x8_t b) {
  vbool8_t cmp_res = __riscv_vmseq_vv_i8m1_b8(a, b, 8);
  return __riscv_vmerge_vvm_u8m1(vdup_n_u8(0x0), vdup_n_u8(UINT8_MAX), cmp_res, 8);
}

FORCE_INLINE uint16x4_t vceq_s16(int16x4_t a, int16x4_t b) {
  vbool16_t cmp_res = __riscv_vmseq_vv_i16m1_b16(a, b, 4);
  return __riscv_vmerge_vvm_u16m1(vdup_n_u16(0x0), vdup_n_u16(UINT16_MAX), cmp_res, 4);
}

FORCE_INLINE uint32x2_t vceq_s32(int32x2_t a, int32x2_t b) {
  vbool32_t cmp_res = __riscv_vmseq_vv_i32m1_b32(a, b, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint32x2_t vceq_f32(float32x2_t a, float32x2_t b) {
  vbool32_t cmp_res = __riscv_vmfeq_vv_f32m1_b32(a, b, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint8x8_t vceq_u8(uint8x8_t a, uint8x8_t b) {
  vbool8_t cmp_res = __riscv_vmseq_vv_u8m1_b8(a, b, 8);
  return __riscv_vmerge_vvm_u8m1(vdup_n_u8(0x0), vdup_n_u8(UINT8_MAX), cmp_res, 8);
}

FORCE_INLINE uint16x4_t vceq_u16(uint16x4_t a, uint16x4_t b) {
  vbool16_t cmp_res = __riscv_vmseq_vv_u16m1_b16(a, b, 4);
  return __riscv_vmerge_vvm_u16m1(vdup_n_u16(0x0), vdup_n_u16(UINT16_MAX), cmp_res, 4);
}

FORCE_INLINE uint32x2_t vceq_u32(uint32x2_t a, uint32x2_t b) {
  vbool32_t cmp_res = __riscv_vmseq_vv_u32m1_b32(a, b, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint8x16_t vceqq_s8(int8x16_t a, int8x16_t b) {
  vbool8_t cmp_res = __riscv_vmseq_vv_i8m1_b8(a, b, 16);
  return __riscv_vmerge_vvm_u8m1(vdupq_n_u8(0x0), vdupq_n_u8(UINT8_MAX), cmp_res, 16);
}

FORCE_INLINE uint16x8_t vceqq_s16(int16x8_t a, int16x8_t b) {
  vbool16_t cmp_res = __riscv_vmseq_vv_i16m1_b16(a, b, 8);
  return __riscv_vmerge_vvm_u16m1(vdupq_n_u16(0x0), vdupq_n_u16(UINT16_MAX), cmp_res, 8);
}

FORCE_INLINE uint32x4_t vceqq_s32(int32x4_t a, int32x4_t b) {
  vbool32_t cmp_res = __riscv_vmseq_vv_i32m1_b32(a, b, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint32x4_t vceqq_f32(float32x4_t a, float32x4_t b) {
  vbool32_t cmp_res = __riscv_vmfeq_vv_f32m1_b32(a, b, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

// FORCE_INLINE uint8x8_t vceq_p8(poly8x8_t a, poly8x8_t b);

// FORCE_INLINE uint8x16_t vceqq_p8(poly8x16_t a, poly8x16_t b);

FORCE_INLINE uint64x1_t vceq_s64(int64x1_t a, int64x1_t b) {
  vbool64_t cmp_res = __riscv_vmseq_vv_i64m1_b64(a, b, 1);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vceqq_s64(int64x2_t a, int64x2_t b) {
  vbool64_t cmp_res = __riscv_vmseq_vv_i64m1_b64(a, b, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint64x1_t vceq_u64(uint64x1_t a, uint64x1_t b) {
  vbool64_t cmp_res = __riscv_vmseq_vv_u64m1_b64(a, b, 1);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vceqq_u64(uint64x2_t a, uint64x2_t b) {
  vbool64_t cmp_res = __riscv_vmseq_vv_u64m1_b64(a, b, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

// FORCE_INLINE uint64x1_t vceq_p64(poly64x1_t a, poly64x1_t b);

// FORCE_INLINE uint64x2_t vceqq_p64(poly64x2_t a, poly64x2_t b);

FORCE_INLINE uint64x1_t vceq_f64(float64x1_t a, float64x1_t b) {
  vbool64_t cmp_res = __riscv_vmfeq_vv_f64m1_b64(a, b, 1);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vceqq_f64(float64x2_t a, float64x2_t b) {
  vbool64_t cmp_res = __riscv_vmfeq_vv_f64m1_b64(a, b, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint64_t vceqd_s64(int64_t a, int64_t b) { return a == b ? UINT64_MAX : 0x0; }

FORCE_INLINE uint64_t vceqd_u64(uint64_t a, uint64_t b) { return a == b ? UINT64_MAX : 0x0; }

FORCE_INLINE uint32_t vceqs_f32(float32_t a, float32_t b) { return a == b ? UINT32_MAX : 0x0; }

FORCE_INLINE uint64_t vceqd_f64(float64_t a, float64_t b) { return a == b ? UINT64_MAX : 0x0; }

FORCE_INLINE uint8x8_t vceqz_s8(int8x8_t a) {
  vbool8_t cmp_res = __riscv_vmseq_vx_i8m1_b8(a, 0, 8);
  return __riscv_vmerge_vvm_u8m1(vdup_n_u8(0x0), vdup_n_u8(UINT8_MAX), cmp_res, 8);
}

FORCE_INLINE uint8x16_t vceqzq_s8(int8x16_t a) {
  vbool8_t cmp_res = __riscv_vmseq_vx_i8m1_b8(a, 0, 16);
  return __riscv_vmerge_vvm_u8m1(vdupq_n_u8(0x0), vdupq_n_u8(UINT8_MAX), cmp_res, 16);
}

FORCE_INLINE uint16x4_t vceqz_s16(int16x4_t a) {
  vbool16_t cmp_res = __riscv_vmseq_vx_i16m1_b16(a, 0, 4);
  return __riscv_vmerge_vvm_u16m1(vdup_n_u16(0x0), vdup_n_u16(UINT16_MAX), cmp_res, 4);
}

FORCE_INLINE uint16x8_t vceqzq_s16(int16x8_t a) {
  vbool16_t cmp_res = __riscv_vmseq_vx_i16m1_b16(a, 0, 8);
  return __riscv_vmerge_vvm_u16m1(vdupq_n_u16(0x0), vdupq_n_u16(UINT16_MAX), cmp_res, 8);
}

FORCE_INLINE uint32x2_t vceqz_s32(int32x2_t a) {
  vbool32_t cmp_res = __riscv_vmseq_vx_i32m1_b32(a, 0, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint32x4_t vceqzq_s32(int32x4_t a) {
  vbool32_t cmp_res = __riscv_vmseq_vx_i32m1_b32(a, 0, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint8x8_t vceqz_u8(uint8x8_t a) {
  vbool8_t cmp_res = __riscv_vmseq_vx_u8m1_b8(a, 0, 8);
  return __riscv_vmerge_vvm_u8m1(vdup_n_u8(0x0), vdup_n_u8(UINT8_MAX), cmp_res, 8);
}

FORCE_INLINE uint8x16_t vceqzq_u8(uint8x16_t a) {
  vbool8_t cmp_res = __riscv_vmseq_vx_u8m1_b8(a, 0, 16);
  return __riscv_vmerge_vvm_u8m1(vdupq_n_u8(0x0), vdupq_n_u8(UINT8_MAX), cmp_res, 16);
}

FORCE_INLINE uint16x4_t vceqz_u16(uint16x4_t a) {
  vbool16_t cmp_res = __riscv_vmseq_vx_u16m1_b16(a, 0, 4);
  return __riscv_vmerge_vvm_u16m1(vdup_n_u16(0x0), vdup_n_u16(UINT16_MAX), cmp_res, 4);
}

FORCE_INLINE uint16x8_t vceqzq_u16(uint16x8_t a) {
  vbool16_t cmp_res = __riscv_vmseq_vx_u16m1_b16(a, 0, 8);
  return __riscv_vmerge_vvm_u16m1(vdupq_n_u16(0x0), vdupq_n_u16(UINT16_MAX), cmp_res, 8);
}

FORCE_INLINE uint32x2_t vceqz_u32(uint32x2_t a) {
  vbool32_t cmp_res = __riscv_vmseq_vx_u32m1_b32(a, 0, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint32x4_t vceqzq_u32(uint32x4_t a) {
  vbool32_t cmp_res = __riscv_vmseq_vx_u32m1_b32(a, 0, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint32x2_t vceqz_f32(float32x2_t a) {
  vbool32_t cmp_res = __riscv_vmfeq_vf_f32m1_b32(a, 0, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint32x4_t vceqzq_f32(float32x4_t a) {
  vbool32_t cmp_res = __riscv_vmfeq_vf_f32m1_b32(a, 0, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

// FORCE_INLINE uint8x8_t vceqz_p8(poly8x8_t a);

// FORCE_INLINE uint8x16_t vceqzq_p8(poly8x16_t a);

FORCE_INLINE uint64x1_t vceqz_s64(int64x1_t a) {
  vbool64_t cmp_res = __riscv_vmseq_vx_i64m1_b64(a, 0, 1);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vceqzq_s64(int64x2_t a) {
  vbool64_t cmp_res = __riscv_vmseq_vx_i64m1_b64(a, 0, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint64x1_t vceqz_u64(uint64x1_t a) {
  vbool64_t cmp_res = __riscv_vmseq_vx_u64m1_b64(a, 0, 1);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vceqzq_u64(uint64x2_t a) {
  vbool64_t cmp_res = __riscv_vmseq_vx_u64m1_b64(a, 0, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

// FORCE_INLINE uint64x1_t vceqz_p64(poly64x1_t a);

// FORCE_INLINE uint64x2_t vceqzq_p64(poly64x2_t a);

FORCE_INLINE uint64x1_t vceqz_f64(float64x1_t a) {
  vbool64_t cmp_res = __riscv_vmfeq_vf_f64m1_b64(a, 0, 1);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vceqzq_f64(float64x2_t a) {
  vbool64_t cmp_res = __riscv_vmfeq_vf_f64m1_b64(a, 0, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint64_t vceqzd_s64(int64_t a) { return a == 0 ? UINT64_MAX : 0x0; }

FORCE_INLINE uint64_t vceqzd_u64(uint64_t a) { return a == 0 ? UINT64_MAX : 0x0; }

FORCE_INLINE uint32_t vceqzs_f32(float32_t a) { return a == 0 ? UINT32_MAX : 0x0; }

FORCE_INLINE uint64_t vceqzd_f64(float64_t a) { return a == 0 ? UINT64_MAX : 0x0; }

FORCE_INLINE uint8x16_t vceqq_u8(uint8x16_t a, uint8x16_t b) {
  vbool8_t cmp_res = __riscv_vmseq_vv_u8m1_b8(a, b, 16);
  return __riscv_vmerge_vvm_u8m1(vdupq_n_u8(0x0), vdupq_n_u8(UINT8_MAX), cmp_res, 16);
}

FORCE_INLINE uint16x8_t vceqq_u16(uint16x8_t a, uint16x8_t b) {
  vbool16_t cmp_res = __riscv_vmseq_vv_u16m1_b16(a, b, 8);
  return __riscv_vmerge_vvm_u16m1(vdupq_n_u16(0x0), vdupq_n_u16(UINT16_MAX), cmp_res, 8);
}

FORCE_INLINE uint32x4_t vceqq_u32(uint32x4_t a, uint32x4_t b) {
  vbool32_t cmp_res = __riscv_vmseq_vv_u32m1_b32(a, b, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint8x8_t vcge_s8(int8x8_t a, int8x8_t b) {
  vbool8_t cmp_res = __riscv_vmsge_vv_i8m1_b8(a, b, 8);
  return __riscv_vmerge_vvm_u8m1(vdup_n_u8(0x0), vdup_n_u8(UINT8_MAX), cmp_res, 8);
}

FORCE_INLINE uint16x4_t vcge_s16(int16x4_t a, int16x4_t b) {
  vbool16_t cmp_res = __riscv_vmsge_vv_i16m1_b16(a, b, 4);
  return __riscv_vmerge_vvm_u16m1(vdup_n_u16(0x0), vdup_n_u16(UINT16_MAX), cmp_res, 4);
}

FORCE_INLINE uint32x2_t vcge_s32(int32x2_t a, int32x2_t b) {
  vbool32_t cmp_res = __riscv_vmsge_vv_i32m1_b32(a, b, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint32x2_t vcge_f32(float32x2_t a, float32x2_t b) {
  vbool32_t cmp_res = __riscv_vmfge_vv_f32m1_b32(a, b, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint8x8_t vcge_u8(uint8x8_t a, uint8x8_t b) {
  vbool8_t cmp_res = __riscv_vmsgeu_vv_u8m1_b8(a, b, 8);
  return __riscv_vmerge_vvm_u8m1(vdup_n_u8(0x0), vdup_n_u8(UINT8_MAX), cmp_res, 8);
}

FORCE_INLINE uint16x4_t vcge_u16(uint16x4_t a, uint16x4_t b) {
  vbool16_t cmp_res = __riscv_vmsgeu_vv_u16m1_b16(a, b, 4);
  return __riscv_vmerge_vvm_u16m1(vdup_n_u16(0x0), vdup_n_u16(UINT16_MAX), cmp_res, 4);
}

FORCE_INLINE uint32x2_t vcge_u32(uint32x2_t a, uint32x2_t b) {
  vbool32_t cmp_res = __riscv_vmsgeu_vv_u32m1_b32(a, b, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint8x16_t vcgeq_s8(int8x16_t a, int8x16_t b) {
  vbool8_t cmp_res = __riscv_vmsge_vv_i8m1_b8(a, b, 16);
  return __riscv_vmerge_vvm_u8m1(vdupq_n_u8(0x0), vdupq_n_u8(UINT8_MAX), cmp_res, 16);
}

FORCE_INLINE uint16x8_t vcgeq_s16(int16x8_t a, int16x8_t b) {
  vbool16_t cmp_res = __riscv_vmsge_vv_i16m1_b16(a, b, 8);
  return __riscv_vmerge_vvm_u16m1(vdupq_n_u16(0x0), vdupq_n_u16(UINT16_MAX), cmp_res, 8);
}

FORCE_INLINE uint32x4_t vcgeq_s32(int32x4_t a, int32x4_t b) {
  vbool32_t cmp_res = __riscv_vmsge_vv_i32m1_b32(a, b, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint32x4_t vcgeq_f32(float32x4_t a, float32x4_t b) {
  vbool32_t cmp_res = __riscv_vmfge_vv_f32m1_b32(a, b, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint64x1_t vcge_s64(int64x1_t a, int64x1_t b) {
  vbool64_t cmp_res = __riscv_vmsge_vv_i64m1_b64(a, b, 1);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vcgeq_s64(int64x2_t a, int64x2_t b) {
  vbool64_t cmp_res = __riscv_vmsge_vv_i64m1_b64(a, b, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint64x1_t vcge_u64(uint64x1_t a, uint64x1_t b) {
  vbool64_t cmp_res = __riscv_vmsgeu_vv_u64m1_b64(a, b, 1);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vcgeq_u64(uint64x2_t a, uint64x2_t b) {
  vbool64_t cmp_res = __riscv_vmsgeu_vv_u64m1_b64(a, b, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint64x1_t vcge_f64(float64x1_t a, float64x1_t b) {
  vbool64_t cmp_res = __riscv_vmfge_vv_f64m1_b64(a, b, 1);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vcgeq_f64(float64x2_t a, float64x2_t b) {
  vbool64_t cmp_res = __riscv_vmfge_vv_f64m1_b64(a, b, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint64_t vcged_s64(int64_t a, int64_t b) { return a >= b ? UINT64_MAX : 0x0; }

FORCE_INLINE uint64_t vcged_u64(uint64_t a, uint64_t b) { return a >= b ? UINT64_MAX : 0x0; }

FORCE_INLINE uint32_t vcges_f32(float32_t a, float32_t b) { return a >= b ? UINT32_MAX : 0x0; }

FORCE_INLINE uint64_t vcged_f64(float64_t a, float64_t b) { return a >= b ? UINT64_MAX : 0x0; }

FORCE_INLINE uint8x8_t vcgez_s8(int8x8_t a) {
  vbool8_t cmp_res = __riscv_vmsge_vx_i8m1_b8(a, 0, 8);
  return __riscv_vmerge_vvm_u8m1(vdup_n_u8(0x0), vdup_n_u8(UINT8_MAX), cmp_res, 8);
}

FORCE_INLINE uint8x16_t vcgezq_s8(int8x16_t a) {
  vbool8_t cmp_res = __riscv_vmsge_vx_i8m1_b8(a, 0, 16);
  return __riscv_vmerge_vvm_u8m1(vdupq_n_u8(0x0), vdupq_n_u8(UINT8_MAX), cmp_res, 16);
}

FORCE_INLINE uint16x4_t vcgez_s16(int16x4_t a) {
  vbool16_t cmp_res = __riscv_vmsge_vx_i16m1_b16(a, 0, 4);
  return __riscv_vmerge_vvm_u16m1(vdup_n_u16(0x0), vdup_n_u16(UINT16_MAX), cmp_res, 4);
}

FORCE_INLINE uint16x8_t vcgezq_s16(int16x8_t a) {
  vbool16_t cmp_res = __riscv_vmsge_vx_i16m1_b16(a, 0, 8);
  return __riscv_vmerge_vvm_u16m1(vdupq_n_u16(0x0), vdupq_n_u16(UINT16_MAX), cmp_res, 8);
}

FORCE_INLINE uint32x2_t vcgez_s32(int32x2_t a) {
  vbool32_t cmp_res = __riscv_vmsge_vx_i32m1_b32(a, 0, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint32x4_t vcgezq_s32(int32x4_t a) {
  vbool32_t cmp_res = __riscv_vmsge_vx_i32m1_b32(a, 0, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint64x1_t vcgez_s64(int64x1_t a) {
  vbool64_t cmp_res = __riscv_vmsge_vx_i64m1_b64(a, 0, 1);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vcgezq_s64(int64x2_t a) {
  vbool64_t cmp_res = __riscv_vmsge_vx_i64m1_b64(a, 0, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint32x2_t vcgez_f32(float32x2_t a) {
  vbool32_t cmp_res = __riscv_vmfge_vf_f32m1_b32(a, 0, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint32x4_t vcgezq_f32(float32x4_t a) {
  vbool32_t cmp_res = __riscv_vmfge_vf_f32m1_b32(a, 0, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint64x1_t vcgez_f64(float64x1_t a) {
  vbool64_t cmp_res = __riscv_vmfge_vf_f64m1_b64(a, 0, 1);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vcgezq_f64(float64x2_t a) {
  vbool64_t cmp_res = __riscv_vmfge_vf_f64m1_b64(a, 0, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint64_t vcgezd_s64(int64_t a) { return (a >= 0) ? UINT64_MAX : 0x00; }

FORCE_INLINE uint32_t vcgezs_f32(float32_t a) { return (a >= 0) ? UINT32_MAX : 0x00; }

FORCE_INLINE uint64_t vcgezd_f64(float64_t a) { return (a >= 0) ? UINT64_MAX : 0x00; }

FORCE_INLINE uint8x16_t vcgeq_u8(uint8x16_t a, uint8x16_t b) {
  vbool8_t cmp_res = __riscv_vmsgeu_vv_u8m1_b8(a, b, 16);
  return __riscv_vmerge_vvm_u8m1(vdupq_n_u8(0x0), vdupq_n_u8(UINT8_MAX), cmp_res, 16);
}

FORCE_INLINE uint16x8_t vcgeq_u16(uint16x8_t a, uint16x8_t b) {
  vbool16_t cmp_res = __riscv_vmsgeu_vv_u16m1_b16(a, b, 8);
  return __riscv_vmerge_vvm_u16m1(vdupq_n_u16(0x0), vdupq_n_u16(UINT16_MAX), cmp_res, 8);
}

FORCE_INLINE uint32x4_t vcgeq_u32(uint32x4_t a, uint32x4_t b) {
  vbool32_t cmp_res = __riscv_vmsgeu_vv_u32m1_b32(a, b, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint8x8_t vcle_s8(int8x8_t a, int8x8_t b) {
  vbool8_t cmp_res = __riscv_vmsle_vv_i8m1_b8(a, b, 8);
  return __riscv_vmerge_vvm_u8m1(vdup_n_u8(0x0), vdup_n_u8(UINT8_MAX), cmp_res, 8);
}

FORCE_INLINE uint16x4_t vcle_s16(int16x4_t a, int16x4_t b) {
  vbool16_t cmp_res = __riscv_vmsle_vv_i16m1_b16(a, b, 4);
  return __riscv_vmerge_vvm_u16m1(vdup_n_u16(0x0), vdup_n_u16(UINT16_MAX), cmp_res, 4);
}

FORCE_INLINE uint32x2_t vcle_s32(int32x2_t a, int32x2_t b) {
  vbool32_t cmp_res = __riscv_vmsle_vv_i32m1_b32(a, b, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint32x2_t vcle_f32(float32x2_t a, float32x2_t b) {
  vbool32_t cmp_res = __riscv_vmfle_vv_f32m1_b32(a, b, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint8x8_t vcle_u8(uint8x8_t a, uint8x8_t b) {
  vbool8_t cmp_res = __riscv_vmsleu_vv_u8m1_b8(a, b, 8);
  return __riscv_vmerge_vvm_u8m1(vdup_n_u8(0x0), vdup_n_u8(UINT8_MAX), cmp_res, 8);
}

FORCE_INLINE uint16x4_t vcle_u16(uint16x4_t a, uint16x4_t b) {
  vbool16_t cmp_res = __riscv_vmsleu_vv_u16m1_b16(a, b, 4);
  return __riscv_vmerge_vvm_u16m1(vdup_n_u16(0x0), vdup_n_u16(UINT16_MAX), cmp_res, 4);
}

FORCE_INLINE uint32x2_t vcle_u32(uint32x2_t a, uint32x2_t b) {
  vbool32_t cmp_res = __riscv_vmsleu_vv_u32m1_b32(a, b, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint8x16_t vcleq_s8(int8x16_t a, int8x16_t b) {
  vbool8_t cmp_res = __riscv_vmsle_vv_i8m1_b8(a, b, 16);
  return __riscv_vmerge_vvm_u8m1(vdupq_n_u8(0x0), vdupq_n_u8(UINT8_MAX), cmp_res, 16);
}

FORCE_INLINE uint16x8_t vcleq_s16(int16x8_t a, int16x8_t b) {
  vbool16_t cmp_res = __riscv_vmsle_vv_i16m1_b16(a, b, 8);
  return __riscv_vmerge_vvm_u16m1(vdupq_n_u16(0x0), vdupq_n_u16(UINT16_MAX), cmp_res, 8);
}

FORCE_INLINE uint32x4_t vcleq_s32(int32x4_t a, int32x4_t b) {
  vbool32_t cmp_res = __riscv_vmsle_vv_i32m1_b32(a, b, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint32x4_t vcleq_f32(float32x4_t a, float32x4_t b) {
  vbool32_t cmp_res = __riscv_vmfle_vv_f32m1_b32(a, b, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint64x1_t vcle_s64(int64x1_t a, int64x1_t b) {
  vbool64_t cmp_res = __riscv_vmsle_vv_i64m1_b64(a, b, 1);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vcleq_s64(int64x2_t a, int64x2_t b) {
  vbool64_t cmp_res = __riscv_vmsle_vv_i64m1_b64(a, b, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint64x1_t vcle_u64(uint64x1_t a, uint64x1_t b) {
  vbool64_t cmp_res = __riscv_vmsleu_vv_u64m1_b64(a, b, 1);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vcleq_u64(uint64x2_t a, uint64x2_t b) {
  vbool64_t cmp_res = __riscv_vmsleu_vv_u64m1_b64(a, b, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint64x1_t vcle_f64(float64x1_t a, float64x1_t b) {
  vbool64_t cmp_res = __riscv_vmfle_vv_f64m1_b64(a, b, 1);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vcleq_f64(float64x2_t a, float64x2_t b) {
  vbool64_t cmp_res = __riscv_vmfle_vv_f64m1_b64(a, b, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint64_t vcled_s64(int64_t a, int64_t b) { return a <= b ? UINT64_MAX : 0x0; }

FORCE_INLINE uint64_t vcled_u64(uint64_t a, uint64_t b) { return a <= b ? UINT64_MAX : 0x0; }

FORCE_INLINE uint32_t vcles_f32(float32_t a, float32_t b) { return a <= b ? UINT32_MAX : 0x0; }

FORCE_INLINE uint64_t vcled_f64(float64_t a, float64_t b) { return a <= b ? UINT64_MAX : 0x0; }

FORCE_INLINE uint8x8_t vclez_s8(int8x8_t a) {
  vbool8_t cmp_res = __riscv_vmsle_vx_i8m1_b8(a, 0, 8);
  return __riscv_vmerge_vvm_u8m1(vdup_n_u8(0x0), vdup_n_u8(UINT8_MAX), cmp_res, 8);
}

FORCE_INLINE uint8x16_t vclezq_s8(int8x16_t a) {
  vbool8_t cmp_res = __riscv_vmsle_vx_i8m1_b8(a, 0, 16);
  return __riscv_vmerge_vvm_u8m1(vdupq_n_u8(0x0), vdupq_n_u8(UINT8_MAX), cmp_res, 16);
}

FORCE_INLINE uint16x4_t vclez_s16(int16x4_t a) {
  vbool16_t cmp_res = __riscv_vmsle_vx_i16m1_b16(a, 0, 4);
  return __riscv_vmerge_vvm_u16m1(vdup_n_u16(0x0), vdup_n_u16(UINT16_MAX), cmp_res, 4);
}

FORCE_INLINE uint16x8_t vclezq_s16(int16x8_t a) {
  vbool16_t cmp_res = __riscv_vmsle_vx_i16m1_b16(a, 0, 8);
  return __riscv_vmerge_vvm_u16m1(vdupq_n_u16(0x0), vdupq_n_u16(UINT16_MAX), cmp_res, 8);
}

FORCE_INLINE uint32x2_t vclez_s32(int32x2_t a) {
  vbool32_t cmp_res = __riscv_vmsle_vx_i32m1_b32(a, 0, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint32x4_t vclezq_s32(int32x4_t a) {
  vbool32_t cmp_res = __riscv_vmsle_vx_i32m1_b32(a, 0, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint64x1_t vclez_s64(int64x1_t a) {
  vbool64_t cmp_res = __riscv_vmsle_vx_i64m1_b64(a, 0, 1);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vclezq_s64(int64x2_t a) {
  vbool64_t cmp_res = __riscv_vmsle_vx_i64m1_b64(a, 0, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint32x2_t vclez_f32(float32x2_t a) {
  vbool32_t cmp_res = __riscv_vmfle_vf_f32m1_b32(a, 0, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint32x4_t vclezq_f32(float32x4_t a) {
  vbool32_t cmp_res = __riscv_vmfle_vf_f32m1_b32(a, 0, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint64x1_t vclez_f64(float64x1_t a) {
  vbool64_t cmp_res = __riscv_vmfle_vf_f64m1_b64(a, 0, 1);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vclezq_f64(float64x2_t a) {
  vbool64_t cmp_res = __riscv_vmfle_vf_f64m1_b64(a, 0, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint64_t vclezd_s64(int64_t a) { return (a <= 0) ? UINT64_MAX : 0x00; }

FORCE_INLINE uint32_t vclezs_f32(float32_t a) { return (a <= 0) ? UINT32_MAX : 0x00; }

FORCE_INLINE uint64_t vclezd_f64(float64_t a) { return (a <= 0) ? UINT64_MAX : 0x00; }

FORCE_INLINE uint8x16_t vcleq_u8(uint8x16_t a, uint8x16_t b) {
  vbool8_t cmp_res = __riscv_vmsleu_vv_u8m1_b8(a, b, 16);
  return __riscv_vmerge_vvm_u8m1(vdupq_n_u8(0x0), vdupq_n_u8(UINT8_MAX), cmp_res, 16);
}

FORCE_INLINE uint16x8_t vcleq_u16(uint16x8_t a, uint16x8_t b) {
  vbool16_t cmp_res = __riscv_vmsleu_vv_u16m1_b16(a, b, 8);
  return __riscv_vmerge_vvm_u16m1(vdupq_n_u16(0x0), vdupq_n_u16(UINT16_MAX), cmp_res, 8);
}

FORCE_INLINE uint32x4_t vcleq_u32(uint32x4_t a, uint32x4_t b) {
  vbool32_t cmp_res = __riscv_vmsleu_vv_u32m1_b32(a, b, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint8x8_t vcgt_s8(int8x8_t a, int8x8_t b) {
  // vbool8_t uses every bit to represent the boolean values of each elements of the comparison result
  vbool8_t cmp_res = __riscv_vmsgt_vv_i8m1_b8(a, b, 8);
  return __riscv_vmerge_vvm_u8m1(vdup_n_u8(0x0), vdup_n_u8(UINT8_MAX), cmp_res, 8);
}

FORCE_INLINE uint16x4_t vcgt_s16(int16x4_t a, int16x4_t b) {
  vbool16_t cmp_res = __riscv_vmsgt_vv_i16m1_b16(a, b, 4);
  return __riscv_vmerge_vvm_u16m1(vdup_n_u16(0x0), vdup_n_u16(UINT16_MAX), cmp_res, 4);
}

FORCE_INLINE uint32x2_t vcgt_s32(int32x2_t a, int32x2_t b) {
  vbool32_t cmp_res = __riscv_vmsgt_vv_i32m1_b32(a, b, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint32x2_t vcgt_f32(float32x2_t a, float32x2_t b) {
  vbool32_t cmp_res = __riscv_vmfgt_vv_f32m1_b32(a, b, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint8x8_t vcgt_u8(uint8x8_t a, uint8x8_t b) {
  vbool8_t cmp_res = __riscv_vmsgtu_vv_u8m1_b8(a, b, 8);
  return __riscv_vmerge_vvm_u8m1(vdup_n_u8(0x0), vdup_n_u8(UINT8_MAX), cmp_res, 8);
}

FORCE_INLINE uint16x4_t vcgt_u16(uint16x4_t a, uint16x4_t b) {
  vbool16_t cmp_res = __riscv_vmsgtu_vv_u16m1_b16(a, b, 4);
  return __riscv_vmerge_vvm_u16m1(vdup_n_u16(0x0), vdup_n_u16(UINT16_MAX), cmp_res, 4);
}

FORCE_INLINE uint32x2_t vcgt_u32(uint32x2_t a, uint32x2_t b) {
  vbool32_t cmp_res = __riscv_vmsgtu_vv_u32m1_b32(a, b, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint8x16_t vcgtq_s8(int8x16_t a, int8x16_t b) {
  vbool8_t cmp_res = __riscv_vmsgt_vv_i8m1_b8(a, b, 16);
  return __riscv_vmerge_vvm_u8m1(vdupq_n_u8(0x0), vdupq_n_u8(UINT8_MAX), cmp_res, 16);
}

FORCE_INLINE uint16x8_t vcgtq_s16(int16x8_t a, int16x8_t b) {
  vbool16_t cmp_res = __riscv_vmsgt_vv_i16m1_b16(a, b, 8);
  return __riscv_vmerge_vvm_u16m1(vdupq_n_u16(0x0), vdupq_n_u16(UINT16_MAX), cmp_res, 8);
}

FORCE_INLINE uint32x4_t vcgtq_s32(int32x4_t a, int32x4_t b) {
  vbool32_t cmp_res = __riscv_vmsgt_vv_i32m1_b32(a, b, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint32x4_t vcgtq_f32(float32x4_t a, float32x4_t b) {
  vbool32_t cmp_res = __riscv_vmfgt_vv_f32m1_b32(a, b, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint64x1_t vcgt_s64(int64x1_t a, int64x1_t b) {
  vbool64_t cmp_res = __riscv_vmsgt_vv_i64m1_b64(a, b, 1);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vcgtq_s64(int64x2_t a, int64x2_t b) {
  vbool64_t cmp_res = __riscv_vmsgt_vv_i64m1_b64(a, b, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint64x1_t vcgt_u64(uint64x1_t a, uint64x1_t b) {
  vbool64_t cmp_res = __riscv_vmsgtu_vv_u64m1_b64(a, b, 1);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vcgtq_u64(uint64x2_t a, uint64x2_t b) {
  vbool64_t cmp_res = __riscv_vmsgtu_vv_u64m1_b64(a, b, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint64x1_t vcgt_f64(float64x1_t a, float64x1_t b) {
  vbool64_t cmp_res = __riscv_vmfgt_vv_f64m1_b64(a, b, 1);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vcgtq_f64(float64x2_t a, float64x2_t b) {
  vbool64_t cmp_res = __riscv_vmfgt_vv_f64m1_b64(a, b, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint64_t vcgtd_s64(int64_t a, int64_t b) { return a > b ? UINT64_MAX : 0x0; }

FORCE_INLINE uint64_t vcgtd_u64(uint64_t a, uint64_t b) { return a > b ? UINT64_MAX : 0x0; }

FORCE_INLINE uint32_t vcgts_f32(float32_t a, float32_t b) { return a > b ? UINT32_MAX : 0x0; }

FORCE_INLINE uint64_t vcgtd_f64(float64_t a, float64_t b) { return a > b ? UINT64_MAX : 0x0; }

FORCE_INLINE uint8x8_t vcgtz_s8(int8x8_t a) {
  vbool8_t cmp_res = __riscv_vmsgt_vx_i8m1_b8(a, 0, 8);
  return __riscv_vmerge_vvm_u8m1(vdup_n_u8(0x0), vdup_n_u8(UINT8_MAX), cmp_res, 8);
}

FORCE_INLINE uint8x16_t vcgtzq_s8(int8x16_t a) {
  vbool8_t cmp_res = __riscv_vmsgt_vx_i8m1_b8(a, 0, 16);
  return __riscv_vmerge_vvm_u8m1(vdupq_n_u8(0x0), vdupq_n_u8(UINT8_MAX), cmp_res, 16);
}

FORCE_INLINE uint16x4_t vcgtz_s16(int16x4_t a) {
  vbool16_t cmp_res = __riscv_vmsgt_vx_i16m1_b16(a, 0, 4);
  return __riscv_vmerge_vvm_u16m1(vdup_n_u16(0x0), vdup_n_u16(UINT16_MAX), cmp_res, 4);
}

FORCE_INLINE uint16x8_t vcgtzq_s16(int16x8_t a) {
  vbool16_t cmp_res = __riscv_vmsgt_vx_i16m1_b16(a, 0, 8);
  return __riscv_vmerge_vvm_u16m1(vdupq_n_u16(0x0), vdupq_n_u16(UINT16_MAX), cmp_res, 8);
}

FORCE_INLINE uint32x2_t vcgtz_s32(int32x2_t a) {
  vbool32_t cmp_res = __riscv_vmsgt_vx_i32m1_b32(a, 0, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint32x4_t vcgtzq_s32(int32x4_t a) {
  vbool32_t cmp_res = __riscv_vmsgt_vx_i32m1_b32(a, 0, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint64x1_t vcgtz_s64(int64x1_t a) {
  vbool64_t cmp_res = __riscv_vmsgt_vx_i64m1_b64(a, 0, 1);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vcgtzq_s64(int64x2_t a) {
  vbool64_t cmp_res = __riscv_vmsgt_vx_i64m1_b64(a, 0, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint32x2_t vcgtz_f32(float32x2_t a) {
  vbool32_t cmp_res = __riscv_vmfgt_vf_f32m1_b32(a, 0, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint32x4_t vcgtzq_f32(float32x4_t a) {
  vbool32_t cmp_res = __riscv_vmfgt_vf_f32m1_b32(a, 0, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint64x1_t vcgtz_f64(float64x1_t a) {
  vbool64_t cmp_res = __riscv_vmfgt_vf_f64m1_b64(a, 0, 1);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vcgtzq_f64(float64x2_t a) {
  vbool64_t cmp_res = __riscv_vmfgt_vf_f64m1_b64(a, 0, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint64_t vcgtzd_s64(int64_t a) { return (a > 0) ? UINT64_MAX : 0x00; }

FORCE_INLINE uint32_t vcgtzs_f32(float32_t a) { return (a > 0) ? UINT32_MAX : 0x00; }

FORCE_INLINE uint64_t vcgtzd_f64(float64_t a) { return (a > 0) ? UINT64_MAX : 0x00; }

FORCE_INLINE uint8x16_t vcgtq_u8(uint8x16_t a, uint8x16_t b) {
  vbool8_t cmp_res = __riscv_vmsgtu_vv_u8m1_b8(a, b, 16);
  return __riscv_vmerge_vvm_u8m1(vdupq_n_u8(0x0), vdupq_n_u8(UINT8_MAX), cmp_res, 16);
}

FORCE_INLINE uint16x8_t vcgtq_u16(uint16x8_t a, uint16x8_t b) {
  vbool16_t cmp_res = __riscv_vmsgtu_vv_u16m1_b16(a, b, 8);
  return __riscv_vmerge_vvm_u16m1(vdupq_n_u16(0x0), vdupq_n_u16(UINT16_MAX), cmp_res, 8);
}

FORCE_INLINE uint32x4_t vcgtq_u32(uint32x4_t a, uint32x4_t b) {
  vbool32_t cmp_res = __riscv_vmsgtu_vv_u32m1_b32(a, b, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint8x8_t vclt_s8(int8x8_t a, int8x8_t b) {
  vbool8_t cmp_res = __riscv_vmslt_vv_i8m1_b8(a, b, 8);
  return __riscv_vmerge_vvm_u8m1(vdup_n_u8(0x0), vdup_n_u8(UINT8_MAX), cmp_res, 8);
}

FORCE_INLINE uint16x4_t vclt_s16(int16x4_t a, int16x4_t b) {
  vbool16_t cmp_res = __riscv_vmslt_vv_i16m1_b16(a, b, 4);
  return __riscv_vmerge_vvm_u16m1(vdup_n_u16(0x0), vdup_n_u16(UINT16_MAX), cmp_res, 4);
}

FORCE_INLINE uint32x2_t vclt_s32(int32x2_t a, int32x2_t b) {
  vbool32_t cmp_res = __riscv_vmslt_vv_i32m1_b32(a, b, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint32x2_t vclt_f32(float32x2_t a, float32x2_t b) {
  vbool32_t cmp_res = __riscv_vmflt_vv_f32m1_b32(a, b, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint8x8_t vclt_u8(uint8x8_t a, uint8x8_t b) {
  vbool8_t cmp_res = __riscv_vmsltu_vv_u8m1_b8(a, b, 8);
  return __riscv_vmerge_vvm_u8m1(vdup_n_u8(0x0), vdup_n_u8(UINT8_MAX), cmp_res, 8);
}

FORCE_INLINE uint16x4_t vclt_u16(uint16x4_t a, uint16x4_t b) {
  vbool16_t cmp_res = __riscv_vmsltu_vv_u16m1_b16(a, b, 4);
  return __riscv_vmerge_vvm_u16m1(vdup_n_u16(0x0), vdup_n_u16(UINT16_MAX), cmp_res, 4);
}

FORCE_INLINE uint32x2_t vclt_u32(uint32x2_t a, uint32x2_t b) {
  vbool32_t cmp_res = __riscv_vmsltu_vv_u32m1_b32(a, b, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint8x16_t vcltq_s8(int8x16_t a, int8x16_t b) {
  vbool8_t cmp_res = __riscv_vmslt_vv_i8m1_b8(a, b, 16);
  return __riscv_vmerge_vvm_u8m1(vdupq_n_u8(0x0), vdupq_n_u8(UINT8_MAX), cmp_res, 16);
}

FORCE_INLINE uint16x8_t vcltq_s16(int16x8_t a, int16x8_t b) {
  vbool16_t cmp_res = __riscv_vmslt_vv_i16m1_b16(a, b, 8);
  return __riscv_vmerge_vvm_u16m1(vdupq_n_u16(0x0), vdupq_n_u16(UINT16_MAX), cmp_res, 8);
}

FORCE_INLINE uint32x4_t vcltq_s32(int32x4_t a, int32x4_t b) {
  vbool32_t cmp_res = __riscv_vmslt_vv_i32m1_b32(a, b, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint32x4_t vcltq_f32(float32x4_t a, float32x4_t b) {
  vbool32_t cmp_res = __riscv_vmflt_vv_f32m1_b32(a, b, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint64x1_t vclt_s64(int64x1_t a, int64x1_t b) {
  vbool64_t cmp_res = __riscv_vmslt_vv_i64m1_b64(a, b, 1);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vcltq_s64(int64x2_t a, int64x2_t b) {
  vbool64_t cmp_res = __riscv_vmslt_vv_i64m1_b64(a, b, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint64x1_t vclt_u64(uint64x1_t a, uint64x1_t b) {
  vbool64_t cmp_res = __riscv_vmsltu_vv_u64m1_b64(a, b, 1);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vcltq_u64(uint64x2_t a, uint64x2_t b) {
  vbool64_t cmp_res = __riscv_vmsltu_vv_u64m1_b64(a, b, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint64x1_t vclt_f64(float64x1_t a, float64x1_t b) {
  vbool64_t cmp_res = __riscv_vmflt_vv_f64m1_b64(a, b, 1);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vcltq_f64(float64x2_t a, float64x2_t b) {
  vbool64_t cmp_res = __riscv_vmflt_vv_f64m1_b64(a, b, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint64_t vcltd_s64(int64_t a, int64_t b) { return a < b ? UINT64_MAX : 0x0; }

FORCE_INLINE uint64_t vcltd_u64(uint64_t a, uint64_t b) { return a < b ? UINT64_MAX : 0x0; }

FORCE_INLINE uint32_t vclts_f32(float32_t a, float32_t b) { return a < b ? UINT32_MAX : 0x0; }

FORCE_INLINE uint64_t vcltd_f64(float64_t a, float64_t b) { return a < b ? UINT64_MAX : 0x0; }

FORCE_INLINE uint8x8_t vcltz_s8(int8x8_t a) {
  vbool8_t cmp_res = __riscv_vmslt_vx_i8m1_b8(a, 0, 8);
  return __riscv_vmerge_vvm_u8m1(vdup_n_u8(0x0), vdup_n_u8(UINT8_MAX), cmp_res, 8);
}

FORCE_INLINE uint8x16_t vcltzq_s8(int8x16_t a) {
  vbool8_t cmp_res = __riscv_vmslt_vx_i8m1_b8(a, 0, 16);
  return __riscv_vmerge_vvm_u8m1(vdupq_n_u8(0x0), vdupq_n_u8(UINT8_MAX), cmp_res, 16);
}

FORCE_INLINE uint16x4_t vcltz_s16(int16x4_t a) {
  vbool16_t cmp_res = __riscv_vmslt_vx_i16m1_b16(a, 0, 4);
  return __riscv_vmerge_vvm_u16m1(vdup_n_u16(0x0), vdup_n_u16(UINT16_MAX), cmp_res, 4);
}

FORCE_INLINE uint16x8_t vcltzq_s16(int16x8_t a) {
  vbool16_t cmp_res = __riscv_vmslt_vx_i16m1_b16(a, 0, 8);
  return __riscv_vmerge_vvm_u16m1(vdupq_n_u16(0x0), vdupq_n_u16(UINT16_MAX), cmp_res, 8);
}

FORCE_INLINE uint32x2_t vcltz_s32(int32x2_t a) {
  vbool32_t cmp_res = __riscv_vmslt_vx_i32m1_b32(a, 0, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint32x4_t vcltzq_s32(int32x4_t a) {
  vbool32_t cmp_res = __riscv_vmslt_vx_i32m1_b32(a, 0, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint64x1_t vcltz_s64(int64x1_t a) {
  vbool64_t cmp_res = __riscv_vmslt_vx_i64m1_b64(a, 0, 1);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vcltzq_s64(int64x2_t a) {
  vbool64_t cmp_res = __riscv_vmslt_vx_i64m1_b64(a, 0, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint32x2_t vcltz_f32(float32x2_t a) {
  vbool32_t cmp_res = __riscv_vmflt_vf_f32m1_b32(a, 0, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint32x4_t vcltzq_f32(float32x4_t a) {
  vbool32_t cmp_res = __riscv_vmflt_vf_f32m1_b32(a, 0, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint64x1_t vcltz_f64(float64x1_t a) {
  vbool64_t cmp_res = __riscv_vmflt_vf_f64m1_b64(a, 0, 1);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vcltzq_f64(float64x2_t a) {
  vbool64_t cmp_res = __riscv_vmflt_vf_f64m1_b64(a, 0, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint64_t vcltzd_s64(int64_t a) { return (a < 0) ? UINT64_MAX : 0x00; }

FORCE_INLINE uint32_t vcltzs_f32(float32_t a) { return (a < 0) ? UINT32_MAX : 0x00; }

FORCE_INLINE uint64_t vcltzd_f64(float64_t a) { return (a < 0) ? UINT64_MAX : 0x00; }

FORCE_INLINE uint8x16_t vcltq_u8(uint8x16_t a, uint8x16_t b) {
  vbool8_t cmp_res = __riscv_vmsltu_vv_u8m1_b8(a, b, 16);
  return __riscv_vmerge_vvm_u8m1(vdupq_n_u8(0x0), vdupq_n_u8(UINT8_MAX), cmp_res, 16);
}

FORCE_INLINE uint16x8_t vcltq_u16(uint16x8_t a, uint16x8_t b) {
  vbool16_t cmp_res = __riscv_vmsltu_vv_u16m1_b16(a, b, 8);
  return __riscv_vmerge_vvm_u16m1(vdupq_n_u16(0x0), vdupq_n_u16(UINT16_MAX), cmp_res, 8);
}

FORCE_INLINE uint32x4_t vcltq_u32(uint32x4_t a, uint32x4_t b) {
  vbool32_t cmp_res = __riscv_vmsltu_vv_u32m1_b32(a, b, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

// TODO RVV doesn't have abs?
FORCE_INLINE int8x8_t vabs_s8(int8x8_t a) {
  // refer https://stackoverflow.com/questions/12041632/how-to-compute-the-integer-absolute-value
  vint8m1_t mask = __riscv_vsra_vx_i8m1(a, 7, 8);
  vint8m1_t a_xor = __riscv_vxor_vv_i8m1(a, mask, 8);
  return __riscv_vsub_vv_i8m1(a_xor, mask, 8);
}

FORCE_INLINE int16x4_t vabs_s16(int16x4_t a) {
  vint16m1_t mask = __riscv_vsra_vx_i16m1(a, 15, 4);
  vint16m1_t a_xor = __riscv_vxor_vv_i16m1(a, mask, 4);
  return __riscv_vsub_vv_i16m1(a_xor, mask, 4);
}

FORCE_INLINE int32x2_t vabs_s32(int32x2_t a) {
  vint32m1_t mask = __riscv_vsra_vx_i32m1(a, 31, 2);
  vint32m1_t a_xor = __riscv_vxor_vv_i32m1(a, mask, 2);
  return __riscv_vsub_vv_i32m1(a_xor, mask, 2);
}

FORCE_INLINE float32x2_t vabs_f32(float32x2_t a) { return __riscv_vfabs_v_f32m1(a, 2); }

FORCE_INLINE int8x16_t vabsq_s8(int8x16_t a) {
  vint8m1_t mask = __riscv_vsra_vx_i8m1(a, 7, 16);
  vint8m1_t a_xor = __riscv_vxor_vv_i8m1(a, mask, 16);
  return __riscv_vsub_vv_i8m1(a_xor, mask, 16);
}

FORCE_INLINE int16x8_t vabsq_s16(int16x8_t a) {
  vint16m1_t mask = __riscv_vsra_vx_i16m1(a, 15, 8);
  vint16m1_t a_xor = __riscv_vxor_vv_i16m1(a, mask, 8);
  return __riscv_vsub_vv_i16m1(a_xor, mask, 8);
}

FORCE_INLINE int32x4_t vabsq_s32(int32x4_t a) {
  vint32m1_t mask = __riscv_vsra_vx_i32m1(a, 31, 4);
  vint32m1_t a_xor = __riscv_vxor_vv_i32m1(a, mask, 4);
  return __riscv_vsub_vv_i32m1(a_xor, mask, 4);
}

FORCE_INLINE float32x4_t vabsq_f32(float32x4_t a) { return __riscv_vfabs_v_f32m1(a, 4); }

FORCE_INLINE int64x1_t vabs_s64(int64x1_t a) {
  vint64m1_t mask = __riscv_vsra_vx_i64m1(a, 63, 1);
  vint64m1_t a_xor = __riscv_vxor_vv_i64m1(a, mask, 1);
  return __riscv_vsub_vv_i64m1(a_xor, mask, 1);
}

FORCE_INLINE int64_t vabsd_s64(int64_t a) { return a > 0 ? a : -a; }

FORCE_INLINE int64x2_t vabsq_s64(int64x2_t a) {
  vint64m1_t mask = __riscv_vsra_vx_i64m1(a, 63, 2);
  vint64m1_t a_xor = __riscv_vxor_vv_i64m1(a, mask, 2);
  return __riscv_vsub_vv_i64m1(a_xor, mask, 2);
}

FORCE_INLINE float64x1_t vabs_f64(float64x1_t a) { return __riscv_vfabs_v_f64m1(a, 1); }

FORCE_INLINE float64x2_t vabsq_f64(float64x2_t a) { return __riscv_vfabs_v_f64m1(a, 2); }

FORCE_INLINE int8x8_t vqabs_s8(int8x8_t a) {
  vint8m1_t mask = __riscv_vsra_vx_i8m1(a, 7, 8);
  vint8m1_t a_xor = __riscv_vxor_vv_i8m1(a, mask, 8);
  return __riscv_vssub_vv_i8m1(a_xor, mask, 8);
}

FORCE_INLINE int16x4_t vqabs_s16(int16x4_t a) {
  vint16m1_t mask = __riscv_vsra_vx_i16m1(a, 15, 4);
  vint16m1_t a_xor = __riscv_vxor_vv_i16m1(a, mask, 4);
  return __riscv_vssub_vv_i16m1(a_xor, mask, 4);
}

FORCE_INLINE int32x2_t vqabs_s32(int32x2_t a) {
  vint32m1_t mask = __riscv_vsra_vx_i32m1(a, 31, 2);
  vint32m1_t a_xor = __riscv_vxor_vv_i32m1(a, mask, 2);
  return __riscv_vssub_vv_i32m1(a_xor, mask, 2);
}

FORCE_INLINE int8x16_t vqabsq_s8(int8x16_t a) {
  vint8m1_t mask = __riscv_vsra_vx_i8m1(a, 7, 16);
  vint8m1_t a_xor = __riscv_vxor_vv_i8m1(a, mask, 16);
  return __riscv_vssub_vv_i8m1(a_xor, mask, 16);
}

FORCE_INLINE int16x8_t vqabsq_s16(int16x8_t a) {
  vint16m1_t mask = __riscv_vsra_vx_i16m1(a, 15, 8);
  vint16m1_t a_xor = __riscv_vxor_vv_i16m1(a, mask, 8);
  return __riscv_vssub_vv_i16m1(a_xor, mask, 8);
}

FORCE_INLINE int32x4_t vqabsq_s32(int32x4_t a) {
  vint32m1_t mask = __riscv_vsra_vx_i32m1(a, 31, 4);
  vint32m1_t a_xor = __riscv_vxor_vv_i32m1(a, mask, 4);
  return __riscv_vssub_vv_i32m1(a_xor, mask, 4);
}

FORCE_INLINE int64x1_t vqabs_s64(int64x1_t a) {
  vint64m1_t mask = __riscv_vsra_vx_i64m1(a, 63, 1);
  vint64m1_t a_xor = __riscv_vxor_vv_i64m1(a, mask, 1);
  return __riscv_vssub_vv_i64m1(a_xor, mask, 1);
}

FORCE_INLINE int64x2_t vqabsq_s64(int64x2_t a) {
  vint64m1_t mask = __riscv_vsra_vx_i64m1(a, 63, 2);
  vint64m1_t a_xor = __riscv_vxor_vv_i64m1(a, mask, 2);
  return __riscv_vssub_vv_i64m1(a_xor, mask, 2);
}

FORCE_INLINE int8_t vqabsb_s8(int8_t a) {
  int8_t mask = a >> 7;
  int8_t a_xor = a ^ mask;
  int8_t un_sat = a_xor - mask;
  return (un_sat & 0x80) ? INT8_MAX : un_sat;
}

FORCE_INLINE int16_t vqabsh_s16(int16_t a) {
  int16_t mask = a >> 15;
  int16_t a_xor = a ^ mask;
  int16_t un_sat = a_xor - mask;
  return (un_sat & 0x8000) ? INT16_MAX : un_sat;
}

FORCE_INLINE int32_t vqabss_s32(int32_t a) {
  int32_t mask = a >> 31;
  int32_t a_xor = a ^ mask;
  int32_t un_sat = a_xor - mask;
  return (un_sat & 0x80000000) ? INT32_MAX : un_sat;
}

FORCE_INLINE int64_t vqabsd_s64(int64_t a) {
  int64_t mask = a >> 63;
  int64_t a_xor = a ^ mask;
  int64_t un_sat = a_xor - mask;
  return (un_sat & 0x8000000000000000) ? INT64_MAX : un_sat;
}

FORCE_INLINE uint32x2_t vcage_f32(float32x2_t a, float32x2_t b) {
  vfloat32m1_t a_abs = __riscv_vfabs_v_f32m1(a, 2);
  vfloat32m1_t b_abs = __riscv_vfabs_v_f32m1(b, 2);
  vbool32_t cmp_res = __riscv_vmfge_vv_f32m1_b32(a_abs, b_abs, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint32x4_t vcageq_f32(float32x4_t a, float32x4_t b) {
  vfloat32m1_t a_abs = __riscv_vfabs_v_f32m1(a, 4);
  vfloat32m1_t b_abs = __riscv_vfabs_v_f32m1(b, 4);
  vbool32_t cmp_res = __riscv_vmfge_vv_f32m1_b32(a_abs, b_abs, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint64x1_t vcage_f64(float64x1_t a, float64x1_t b) {
  vfloat64m1_t a_abs = __riscv_vfabs_v_f64m1(a, 1);
  vfloat64m1_t b_abs = __riscv_vfabs_v_f64m1(b, 1);
  vbool64_t cmp_res = __riscv_vmfge_vv_f64m1_b64(a_abs, b_abs, 1);
  return __riscv_vmerge_vvm_u64m1(vdup_n_u64(0x0), vdup_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vcageq_f64(float64x2_t a, float64x2_t b) {
  vfloat64m1_t a_abs = __riscv_vfabs_v_f64m1(a, 2);
  vfloat64m1_t b_abs = __riscv_vfabs_v_f64m1(b, 2);
  vbool64_t cmp_res = __riscv_vmfge_vv_f64m1_b64(a_abs, b_abs, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint32_t vcages_f32(float32_t a, float32_t b) { return fabs(a) >= fabs(b) ? UINT32_MAX : 0x0; }

FORCE_INLINE uint64_t vcaged_f64(float64_t a, float64_t b) { return fabs(a) >= fabs(b) ? UINT64_MAX : 0x0; }

FORCE_INLINE uint32x2_t vcale_f32(float32x2_t a, float32x2_t b) {
  vfloat32m1_t a_abs = __riscv_vfabs_v_f32m1(a, 2);
  vfloat32m1_t b_abs = __riscv_vfabs_v_f32m1(b, 2);
  vbool32_t cmp_res = __riscv_vmfle_vv_f32m1_b32(a_abs, b_abs, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint32x4_t vcaleq_f32(float32x4_t a, float32x4_t b) {
  vfloat32m1_t a_abs = __riscv_vfabs_v_f32m1(a, 4);
  vfloat32m1_t b_abs = __riscv_vfabs_v_f32m1(b, 4);
  vbool32_t cmp_res = __riscv_vmfle_vv_f32m1_b32(a_abs, b_abs, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint64x1_t vcale_f64(float64x1_t a, float64x1_t b) {
  vfloat64m1_t a_abs = __riscv_vfabs_v_f64m1(a, 1);
  vfloat64m1_t b_abs = __riscv_vfabs_v_f64m1(b, 1);
  vbool64_t cmp_res = __riscv_vmfle_vv_f64m1_b64(a_abs, b_abs, 1);
  return __riscv_vmerge_vvm_u64m1(vdup_n_u64(0x0), vdup_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vcaleq_f64(float64x2_t a, float64x2_t b) {
  vfloat64m1_t a_abs = __riscv_vfabs_v_f64m1(a, 2);
  vfloat64m1_t b_abs = __riscv_vfabs_v_f64m1(b, 2);
  vbool64_t cmp_res = __riscv_vmfle_vv_f64m1_b64(a_abs, b_abs, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint32_t vcales_f32(float32_t a, float32_t b) { return fabs(a) <= fabs(b) ? UINT32_MAX : 0x0; }

FORCE_INLINE uint64_t vcaled_f64(float64_t a, float64_t b) { return fabs(a) <= fabs(b) ? UINT64_MAX : 0x0; }

FORCE_INLINE uint32x2_t vcagt_f32(float32x2_t a, float32x2_t b) {
  vfloat32m1_t a_abs = __riscv_vfabs_v_f32m1(a, 2);
  vfloat32m1_t b_abs = __riscv_vfabs_v_f32m1(b, 2);
  vbool32_t cmp_res = __riscv_vmfgt_vv_f32m1_b32(a_abs, b_abs, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint32x4_t vcagtq_f32(float32x4_t a, float32x4_t b) {
  vfloat32m1_t a_abs = __riscv_vfabs_v_f32m1(a, 4);
  vfloat32m1_t b_abs = __riscv_vfabs_v_f32m1(b, 4);
  vbool32_t cmp_res = __riscv_vmfgt_vv_f32m1_b32(a_abs, b_abs, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint64x1_t vcagt_f64(float64x1_t a, float64x1_t b) {
  vfloat64m1_t a_abs = __riscv_vfabs_v_f64m1(a, 1);
  vfloat64m1_t b_abs = __riscv_vfabs_v_f64m1(b, 1);
  vbool64_t cmp_res = __riscv_vmfgt_vv_f64m1_b64(a_abs, b_abs, 1);
  return __riscv_vmerge_vvm_u64m1(vdup_n_u64(0x0), vdup_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vcagtq_f64(float64x2_t a, float64x2_t b) {
  vfloat64m1_t a_abs = __riscv_vfabs_v_f64m1(a, 2);
  vfloat64m1_t b_abs = __riscv_vfabs_v_f64m1(b, 2);
  vbool64_t cmp_res = __riscv_vmfgt_vv_f64m1_b64(a_abs, b_abs, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint32_t vcagts_f32(float32_t a, float32_t b) { return fabs(a) > fabs(b) ? UINT32_MAX : 0x0; }

FORCE_INLINE uint64_t vcagtd_f64(float64_t a, float64_t b) { return fabs(a) > fabs(b) ? UINT64_MAX : 0x0; }

FORCE_INLINE uint32x2_t vcalt_f32(float32x2_t a, float32x2_t b) {
  vfloat32m1_t a_abs = __riscv_vfabs_v_f32m1(a, 2);
  vfloat32m1_t b_abs = __riscv_vfabs_v_f32m1(b, 2);
  vbool32_t cmp_res = __riscv_vmflt_vv_f32m1_b32(a_abs, b_abs, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(UINT32_MAX), cmp_res, 2);
}

FORCE_INLINE uint32x4_t vcaltq_f32(float32x4_t a, float32x4_t b) {
  vfloat32m1_t a_abs = __riscv_vfabs_v_f32m1(a, 4);
  vfloat32m1_t b_abs = __riscv_vfabs_v_f32m1(b, 4);
  vbool32_t cmp_res = __riscv_vmflt_vv_f32m1_b32(a_abs, b_abs, 4);
  return __riscv_vmerge_vvm_u32m1(vdupq_n_u32(0x0), vdupq_n_u32(UINT32_MAX), cmp_res, 4);
}

FORCE_INLINE uint64x1_t vcalt_f64(float64x1_t a, float64x1_t b) {
  vfloat64m1_t a_abs = __riscv_vfabs_v_f64m1(a, 1);
  vfloat64m1_t b_abs = __riscv_vfabs_v_f64m1(b, 1);
  vbool64_t cmp_res = __riscv_vmflt_vv_f64m1_b64(a_abs, b_abs, 1);
  return __riscv_vmerge_vvm_u64m1(vdup_n_u64(0x0), vdup_n_u64(UINT64_MAX), cmp_res, 1);
}

FORCE_INLINE uint64x2_t vcaltq_f64(float64x2_t a, float64x2_t b) {
  vfloat64m1_t a_abs = __riscv_vfabs_v_f64m1(a, 2);
  vfloat64m1_t b_abs = __riscv_vfabs_v_f64m1(b, 2);
  vbool64_t cmp_res = __riscv_vmflt_vv_f64m1_b64(a_abs, b_abs, 2);
  return __riscv_vmerge_vvm_u64m1(vdupq_n_u64(0x0), vdupq_n_u64(UINT64_MAX), cmp_res, 2);
}

FORCE_INLINE uint32_t vcalts_f32(float32_t a, float32_t b) { return fabs(a) <= fabs(b) ? UINT32_MAX : 0x0; }

FORCE_INLINE uint64_t vcaltd_f64(float64_t a, float64_t b) { return fabs(a) <= fabs(b) ? UINT64_MAX : 0x0; }

FORCE_INLINE uint8x8_t vtst_s8(int8x8_t a, int8x8_t b) {
  vint8m1_t ab_and = __riscv_vand_vv_i8m1(a, b, 8);
  vbool8_t nonzero_mask = __riscv_vmsgtu_vx_u8m1_b8(__riscv_vreinterpret_v_i8m1_u8m1(ab_and), 0, 8);
  return __riscv_vreinterpret_v_i8m1_u8m1(__riscv_vmerge_vxm_i8m1(vdup_n_s8(0), UINT8_MAX, nonzero_mask, 8));
}

FORCE_INLINE uint16x4_t vtst_s16(int16x4_t a, int16x4_t b) {
  vint16m1_t ab_and = __riscv_vand_vv_i16m1(a, b, 4);
  vbool16_t nonzero_mask = __riscv_vmsgtu_vx_u16m1_b16(__riscv_vreinterpret_v_i16m1_u16m1(ab_and), 0, 4);
  return __riscv_vreinterpret_v_i16m1_u16m1(__riscv_vmerge_vxm_i16m1(vdup_n_s16(0), UINT16_MAX, nonzero_mask, 4));
}

FORCE_INLINE uint32x2_t vtst_s32(int32x2_t a, int32x2_t b) {
  vint32m1_t ab_and = __riscv_vand_vv_i32m1(a, b, 2);
  vbool32_t nonzero_mask = __riscv_vmsgtu_vx_u32m1_b32(__riscv_vreinterpret_v_i32m1_u32m1(ab_and), 0, 2);
  return __riscv_vreinterpret_v_i32m1_u32m1(__riscv_vmerge_vxm_i32m1(vdup_n_s32(0), UINT32_MAX, nonzero_mask, 2));
}

FORCE_INLINE uint8x8_t vtst_u8(uint8x8_t a, uint8x8_t b) {
  vuint8m1_t ab_and = __riscv_vand_vv_u8m1(a, b, 8);
  vbool8_t nonzero_mask = __riscv_vmsgtu_vx_u8m1_b8(ab_and, 0, 8);
  return __riscv_vmerge_vxm_u8m1(vdup_n_u8(0), UINT8_MAX, nonzero_mask, 8);
}

FORCE_INLINE uint16x4_t vtst_u16(uint16x4_t a, uint16x4_t b) {
  vuint16m1_t ab_and = __riscv_vand_vv_u16m1(a, b, 4);
  vbool16_t nonzero_mask = __riscv_vmsgtu_vx_u16m1_b16(ab_and, 0, 4);
  return __riscv_vmerge_vxm_u16m1(vdup_n_u16(0), UINT16_MAX, nonzero_mask, 4);
}

FORCE_INLINE uint32x2_t vtst_u32(uint32x2_t a, uint32x2_t b) {
  vuint32m1_t ab_and = __riscv_vand_vv_u32m1(a, b, 2);
  vbool32_t nonzero_mask = __riscv_vmsgtu_vx_u32m1_b32(ab_and, 0, 2);
  return __riscv_vmerge_vxm_u32m1(vdup_n_u32(0), UINT32_MAX, nonzero_mask, 2);
}

FORCE_INLINE uint8x16_t vtstq_s8(int8x16_t a, int8x16_t b) {
  vint8m1_t ab_and = __riscv_vand_vv_i8m1(a, b, 16);
  vbool8_t nonzero_mask = __riscv_vmsgtu_vx_u8m1_b8(__riscv_vreinterpret_v_i8m1_u8m1(ab_and), 0, 16);
  return __riscv_vreinterpret_v_i8m1_u8m1(__riscv_vmerge_vxm_i8m1(vdupq_n_s8(0), UINT8_MAX, nonzero_mask, 16));
}

FORCE_INLINE uint16x8_t vtstq_s16(int16x8_t a, int16x8_t b) {
  vint16m1_t ab_and = __riscv_vand_vv_i16m1(a, b, 8);
  vbool16_t nonzero_mask = __riscv_vmsgtu_vx_u16m1_b16(__riscv_vreinterpret_v_i16m1_u16m1(ab_and), 0, 8);
  return __riscv_vreinterpret_v_i16m1_u16m1(__riscv_vmerge_vxm_i16m1(vdupq_n_s16(0), UINT16_MAX, nonzero_mask, 8));
}

FORCE_INLINE uint32x4_t vtstq_s32(int32x4_t a, int32x4_t b) {
  vint32m1_t ab_and = __riscv_vand_vv_i32m1(a, b, 4);
  vbool32_t nonzero_mask = __riscv_vmsgtu_vx_u32m1_b32(__riscv_vreinterpret_v_i32m1_u32m1(ab_and), 0, 4);
  return __riscv_vreinterpret_v_i32m1_u32m1(__riscv_vmerge_vxm_i32m1(vdupq_n_s32(0), UINT32_MAX, nonzero_mask, 4));
}

FORCE_INLINE uint8x16_t vtstq_u8(uint8x16_t a, uint8x16_t b) {
  vuint8m1_t ab_and = __riscv_vand_vv_u8m1(a, b, 16);
  vbool8_t nonzero_mask = __riscv_vmsgtu_vx_u8m1_b8(ab_and, 0, 16);
  return __riscv_vmerge_vxm_u8m1(vdupq_n_u8(0), UINT8_MAX, nonzero_mask, 16);
}

FORCE_INLINE uint16x8_t vtstq_u16(uint16x8_t a, uint16x8_t b) {
  vuint16m1_t ab_and = __riscv_vand_vv_u16m1(a, b, 8);
  vbool16_t nonzero_mask = __riscv_vmsgtu_vx_u16m1_b16(ab_and, 0, 8);
  return __riscv_vmerge_vxm_u16m1(vdupq_n_u16(0), UINT16_MAX, nonzero_mask, 8);
}

FORCE_INLINE uint32x4_t vtstq_u32(uint32x4_t a, uint32x4_t b) {
  vuint32m1_t ab_and = __riscv_vand_vv_u32m1(a, b, 4);
  vbool32_t nonzero_mask = __riscv_vmsgtu_vx_u32m1_b32(ab_and, 0, 4);
  return __riscv_vmerge_vxm_u32m1(vdupq_n_u32(0), UINT32_MAX, nonzero_mask, 4);
}

// FORCE_INLINE uint8x8_t vtst_p8(poly8x8_t a, poly8x8_t b);

// FORCE_INLINE uint8x16_t vtstq_p8(poly8x16_t a, poly8x16_t b);

FORCE_INLINE uint64x1_t vtst_s64(int64x1_t a, int64x1_t b) {
  vuint64m1_t ab_and =
      __riscv_vand_vv_u64m1(__riscv_vreinterpret_v_i64m1_u64m1(a), __riscv_vreinterpret_v_i64m1_u64m1(b), 1);
  vbool64_t nonzero_mask = __riscv_vmsgtu_vx_u64m1_b64(ab_and, 0, 1);
  return __riscv_vmerge_vxm_u64m1(vdup_n_u64(0), UINT64_MAX, nonzero_mask, 1);
}

FORCE_INLINE uint64x2_t vtstq_s64(int64x2_t a, int64x2_t b) {
  vuint64m1_t ab_and =
      __riscv_vand_vv_u64m1(__riscv_vreinterpret_v_i64m1_u64m1(a), __riscv_vreinterpret_v_i64m1_u64m1(b), 2);
  vbool64_t nonzero_mask = __riscv_vmsgtu_vx_u64m1_b64(ab_and, 0, 2);
  return __riscv_vmerge_vxm_u64m1(vdupq_n_u64(0), UINT64_MAX, nonzero_mask, 2);
}

FORCE_INLINE uint64x1_t vtst_u64(uint64x1_t a, uint64x1_t b) {
  vuint64m1_t ab_and = __riscv_vand_vv_u64m1(a, b, 1);
  vbool64_t nonzero_mask = __riscv_vmsgtu_vx_u64m1_b64(ab_and, 0, 1);
  return __riscv_vmerge_vxm_u64m1(vdup_n_u64(0), UINT64_MAX, nonzero_mask, 1);
}

FORCE_INLINE uint64x2_t vtstq_u64(uint64x2_t a, uint64x2_t b) {
  vuint64m1_t ab_and = __riscv_vand_vv_u64m1(a, b, 2);
  vbool64_t nonzero_mask = __riscv_vmsgtu_vx_u64m1_b64(ab_and, 0, 2);
  return __riscv_vmerge_vxm_u64m1(vdupq_n_u64(0), UINT64_MAX, nonzero_mask, 2);
}

// FORCE_INLINE uint64x1_t vtst_p64(poly64x1_t a, poly64x1_t b);

// FORCE_INLINE uint64x2_t vtstq_p64(poly64x2_t a, poly64x2_t b);

FORCE_INLINE uint64_t vtstd_s64(int64_t a, int64_t b) { return (a & b) ? UINT64_MAX : 0x0; }

FORCE_INLINE uint64_t vtstd_u64(uint64_t a, uint64_t b) { return (a & b) ? UINT64_MAX : 0x0; }

FORCE_INLINE int8x8_t vabd_s8(int8x8_t a, int8x8_t b) {
  // TODO need to benchmark the two implementation
  // extend to 16 bits then do abs()
  vint16m1_t ab_sub = __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vwsub_vv_i16m2(a, b, 8));
  vint16m1_t sign_bit_mask = __riscv_vsra_vx_i16m1(ab_sub, 15, 8);
  vint16m1_t ab_xor = __riscv_vxor_vv_i16m1(ab_sub, sign_bit_mask, 8);
  vint16m1_t ab_sub_16 = __riscv_vsub_vv_i16m1(ab_xor, sign_bit_mask, 8);

  // select the lower 8 bits
  return __riscv_vnsra_wx_i8m1(__riscv_vlmul_ext_v_i16m1_i16m2(ab_sub_16), 0, 8);
}

FORCE_INLINE int16x4_t vabd_s16(int16x4_t a, int16x4_t b) {
  vint16m1_t ab_max = __riscv_vmax_vv_i16m1(a, b, 4);
  vint16m1_t ab_min = __riscv_vmin_vv_i16m1(a, b, 4);
  return __riscv_vsub_vv_i16m1(ab_max, ab_min, 4);
}

FORCE_INLINE int32x2_t vabd_s32(int32x2_t a, int32x2_t b) {
  vint32m1_t ab_max = __riscv_vmax_vv_i32m1(a, b, 2);
  vint32m1_t ab_min = __riscv_vmin_vv_i32m1(a, b, 2);
  return __riscv_vsub_vv_i32m1(ab_max, ab_min, 2);
}

FORCE_INLINE float32x2_t vabd_f32(float32x2_t a, float32x2_t b) {
  return __riscv_vfabs_v_f32m1(__riscv_vfsub_vv_f32m1(a, b, 2), 2);
}

FORCE_INLINE uint8x8_t vabd_u8(uint8x8_t a, uint8x8_t b) {
  vuint8m1_t ab_max = __riscv_vmaxu_vv_u8m1(a, b, 8);
  vuint8m1_t ab_min = __riscv_vminu_vv_u8m1(a, b, 8);
  return __riscv_vsub_vv_u8m1(ab_max, ab_min, 8);
}

FORCE_INLINE uint16x4_t vabd_u16(uint16x4_t a, uint16x4_t b) {
  vuint16m1_t ab_max = __riscv_vmaxu_vv_u16m1(a, b, 4);
  vuint16m1_t ab_min = __riscv_vminu_vv_u16m1(a, b, 4);
  return __riscv_vsub_vv_u16m1(ab_max, ab_min, 4);
}

FORCE_INLINE uint32x2_t vabd_u32(uint32x2_t a, uint32x2_t b) {
  vuint32m1_t ab_max = __riscv_vmaxu_vv_u32m1(a, b, 2);
  vuint32m1_t ab_min = __riscv_vminu_vv_u32m1(a, b, 2);
  return __riscv_vsub_vv_u32m1(ab_max, ab_min, 2);
}

FORCE_INLINE int8x16_t vabdq_s8(int8x16_t a, int8x16_t b) {
  vint8m1_t ab_max = __riscv_vmax_vv_i8m1(a, b, 16);
  vint8m1_t ab_min = __riscv_vmin_vv_i8m1(a, b, 16);
  return __riscv_vsub_vv_i8m1(ab_max, ab_min, 16);
}

FORCE_INLINE int16x8_t vabdq_s16(int16x8_t a, int16x8_t b) {
  vint16m1_t ab_max = __riscv_vmax_vv_i16m1(a, b, 8);
  vint16m1_t ab_min = __riscv_vmin_vv_i16m1(a, b, 8);
  return __riscv_vsub_vv_i16m1(ab_max, ab_min, 8);
}

FORCE_INLINE int32x4_t vabdq_s32(int32x4_t a, int32x4_t b) {
  vint32m1_t ab_max = __riscv_vmax_vv_i32m1(a, b, 4);
  vint32m1_t ab_min = __riscv_vmin_vv_i32m1(a, b, 4);
  return __riscv_vsub_vv_i32m1(ab_max, ab_min, 4);
}

FORCE_INLINE float32x4_t vabdq_f32(float32x4_t a, float32x4_t b) {
  return __riscv_vfabs_v_f32m1(__riscv_vfsub_vv_f32m1(a, b, 4), 4);
}

FORCE_INLINE float64x1_t vabd_f64(float64x1_t a, float64x1_t b) {
  return __riscv_vfabs_v_f64m1(__riscv_vfsub_vv_f64m1(a, b, 1), 1);
}

FORCE_INLINE float64x2_t vabdq_f64(float64x2_t a, float64x2_t b) {
  return __riscv_vfabs_v_f64m1(__riscv_vfsub_vv_f64m1(a, b, 2), 2);
}

FORCE_INLINE float32_t vabds_f32(float32_t a, float32_t b) { return abs(a - b); }

FORCE_INLINE float64_t vabdd_f64(float64_t a, float64_t b) { return abs(a - b); }

FORCE_INLINE uint8x16_t vabdq_u8(uint8x16_t a, uint8x16_t b) {
  vuint8m1_t ab_max = __riscv_vmaxu_vv_u8m1(a, b, 16);
  vuint8m1_t ab_min = __riscv_vminu_vv_u8m1(a, b, 16);
  return __riscv_vsub_vv_u8m1(ab_max, ab_min, 16);
}

FORCE_INLINE uint16x8_t vabdq_u16(uint16x8_t a, uint16x8_t b) {
  vuint16m1_t ab_max = __riscv_vmaxu_vv_u16m1(a, b, 8);
  vuint16m1_t ab_min = __riscv_vminu_vv_u16m1(a, b, 8);
  return __riscv_vsub_vv_u16m1(ab_max, ab_min, 8);
}

FORCE_INLINE uint32x4_t vabdq_u32(uint32x4_t a, uint32x4_t b) {
  vuint32m1_t ab_max = __riscv_vmaxu_vv_u32m1(a, b, 4);
  vuint32m1_t ab_min = __riscv_vminu_vv_u32m1(a, b, 4);
  return __riscv_vsub_vv_u32m1(ab_max, ab_min, 4);
}

FORCE_INLINE int16x8_t vabdl_s8(int8x8_t a, int8x8_t b) {
  vint16m1_t ab_sub =
      __riscv_vwsub_vv_i16m1(__riscv_vlmul_trunc_v_i8m1_i8mf2(a), __riscv_vlmul_trunc_v_i8m1_i8mf2(b), 8);
  vint16m1_t sign_bit_mask = __riscv_vsra_vx_i16m1(ab_sub, 15, 8);
  vint16m1_t ab_xor = __riscv_vxor_vv_i16m1(ab_sub, sign_bit_mask, 8);
  return __riscv_vsub_vv_i16m1(ab_xor, sign_bit_mask, 8);
}

FORCE_INLINE int32x4_t vabdl_s16(int16x4_t a, int16x4_t b) {
  vint32m1_t ab_sub =
      __riscv_vwsub_vv_i32m1(__riscv_vlmul_trunc_v_i16m1_i16mf2(a), __riscv_vlmul_trunc_v_i16m1_i16mf2(b), 4);
  vint32m1_t sign_bit_mask = __riscv_vsra_vx_i32m1(ab_sub, 31, 4);
  vint32m1_t ab_xor = __riscv_vxor_vv_i32m1(ab_sub, sign_bit_mask, 4);
  return __riscv_vsub_vv_i32m1(ab_xor, sign_bit_mask, 4);
}

FORCE_INLINE int64x2_t vabdl_s32(int32x2_t a, int32x2_t b) {
  vint64m1_t ab_sub =
      __riscv_vwsub_vv_i64m1(__riscv_vlmul_trunc_v_i32m1_i32mf2(a), __riscv_vlmul_trunc_v_i32m1_i32mf2(b), 4);
  vint64m1_t sign_bit_mask = __riscv_vsra_vx_i64m1(ab_sub, 63, 4);
  vint64m1_t ab_xor = __riscv_vxor_vv_i64m1(ab_sub, sign_bit_mask, 4);
  return __riscv_vsub_vv_i64m1(ab_xor, sign_bit_mask, 4);
}

FORCE_INLINE uint16x8_t vabdl_u8(uint8x8_t a, uint8x8_t b) {
  vuint16m1_t a_ext = __riscv_vzext_vf2_u16m1(__riscv_vlmul_trunc_v_u8m1_u8mf2(a), 8);
  vuint16m1_t b_ext = __riscv_vzext_vf2_u16m1(__riscv_vlmul_trunc_v_u8m1_u8mf2(b), 8);
  vbool16_t a_gt_mask = __riscv_vmsgtu_vv_u16m1_b16(a_ext, b_ext, 8);
  vuint16m1_t ab_sub = __riscv_vsub_vv_u16m1(a_ext, b_ext, 8);
  vuint16m1_t ba_sub = __riscv_vsub_vv_u16m1(b_ext, a_ext, 8);
  return __riscv_vmerge_vvm_u16m1(ba_sub, ab_sub, a_gt_mask, 8);
}

FORCE_INLINE uint32x4_t vabdl_u16(uint16x4_t a, uint16x4_t b) {
  vuint32m1_t a_ext = __riscv_vzext_vf2_u32m1(__riscv_vlmul_trunc_v_u16m1_u16mf2(a), 4);
  vuint32m1_t b_ext = __riscv_vzext_vf2_u32m1(__riscv_vlmul_trunc_v_u16m1_u16mf2(b), 4);
  vbool32_t a_gt_mask = __riscv_vmsgtu_vv_u32m1_b32(a_ext, b_ext, 4);
  vuint32m1_t ab_sub = __riscv_vsub_vv_u32m1(a_ext, b_ext, 4);
  vuint32m1_t ba_sub = __riscv_vsub_vv_u32m1(b_ext, a_ext, 4);
  return __riscv_vmerge_vvm_u32m1(ba_sub, ab_sub, a_gt_mask, 4);
}

FORCE_INLINE uint64x2_t vabdl_u32(uint32x2_t a, uint32x2_t b) {
  vuint64m1_t a_ext = __riscv_vzext_vf2_u64m1(__riscv_vlmul_trunc_v_u32m1_u32mf2(a), 2);
  vuint64m1_t b_ext = __riscv_vzext_vf2_u64m1(__riscv_vlmul_trunc_v_u32m1_u32mf2(b), 2);
  vbool64_t a_gt_mask = __riscv_vmsgtu_vv_u64m1_b64(a_ext, b_ext, 2);
  vuint64m1_t ab_sub = __riscv_vsub_vv_u64m1(a_ext, b_ext, 2);
  vuint64m1_t ba_sub = __riscv_vsub_vv_u64m1(b_ext, a_ext, 2);
  return __riscv_vmerge_vvm_u64m1(ba_sub, ab_sub, a_gt_mask, 2);
}

FORCE_INLINE int16x8_t vabdl_high_s8(int8x16_t a, int8x16_t b) {
  vint8m1_t a_high = __riscv_vslidedown_vx_i8m1(a, 8, 16);
  vint8m1_t b_high = __riscv_vslidedown_vx_i8m1(b, 8, 16);
  vint16m1_t ab_sub =
      __riscv_vwsub_vv_i16m1(__riscv_vlmul_trunc_v_i8m1_i8mf2(a_high), __riscv_vlmul_trunc_v_i8m1_i8mf2(b_high), 8);
  vint16m1_t sign_bit_mask = __riscv_vsra_vx_i16m1(ab_sub, 15, 8);
  vint16m1_t ab_xor = __riscv_vxor_vv_i16m1(ab_sub, sign_bit_mask, 8);
  return __riscv_vsub_vv_i16m1(ab_xor, sign_bit_mask, 8);
}

FORCE_INLINE int32x4_t vabdl_high_s16(int16x8_t a, int16x8_t b) {
  vint16m1_t a_high = __riscv_vslidedown_vx_i16m1(a, 4, 8);
  vint16m1_t b_high = __riscv_vslidedown_vx_i16m1(b, 4, 8);
  vint32m1_t ab_sub =
      __riscv_vwsub_vv_i32m1(__riscv_vlmul_trunc_v_i16m1_i16mf2(a_high), __riscv_vlmul_trunc_v_i16m1_i16mf2(b_high), 4);
  vint32m1_t sign_bit_mask = __riscv_vsra_vx_i32m1(ab_sub, 31, 4);
  vint32m1_t ab_xor = __riscv_vxor_vv_i32m1(ab_sub, sign_bit_mask, 4);
  return __riscv_vsub_vv_i32m1(ab_xor, sign_bit_mask, 4);
}

FORCE_INLINE int64x2_t vabdl_high_s32(int32x4_t a, int32x4_t b) {
  vint32m1_t a_high = __riscv_vslidedown_vx_i32m1(a, 2, 4);
  vint32m1_t b_high = __riscv_vslidedown_vx_i32m1(b, 2, 4);
  vint64m1_t ab_sub =
      __riscv_vwsub_vv_i64m1(__riscv_vlmul_trunc_v_i32m1_i32mf2(a_high), __riscv_vlmul_trunc_v_i32m1_i32mf2(b_high), 4);
  vint64m1_t sign_bit_mask = __riscv_vsra_vx_i64m1(ab_sub, 63, 4);
  vint64m1_t ab_xor = __riscv_vxor_vv_i64m1(ab_sub, sign_bit_mask, 4);
  return __riscv_vsub_vv_i64m1(ab_xor, sign_bit_mask, 4);
}

FORCE_INLINE uint16x8_t vabdl_high_u8(uint8x16_t a, uint8x16_t b) {
  vuint8m1_t a_high = __riscv_vslidedown_vx_u8m1(a, 8, 16);
  vuint8m1_t b_high = __riscv_vslidedown_vx_u8m1(b, 8, 16);
  vuint16m1_t a_ext = __riscv_vzext_vf2_u16m1(__riscv_vlmul_trunc_v_u8m1_u8mf2(a_high), 8);
  vuint16m1_t b_ext = __riscv_vzext_vf2_u16m1(__riscv_vlmul_trunc_v_u8m1_u8mf2(b_high), 8);
  vbool16_t a_gt_mask = __riscv_vmsgtu_vv_u16m1_b16(a_ext, b_ext, 8);
  vuint16m1_t ab_sub = __riscv_vsub_vv_u16m1(a_ext, b_ext, 8);
  vuint16m1_t ba_sub = __riscv_vsub_vv_u16m1(b_ext, a_ext, 8);
  return __riscv_vmerge_vvm_u16m1(ba_sub, ab_sub, a_gt_mask, 8);
}

FORCE_INLINE uint32x4_t vabdl_high_u16(uint16x8_t a, uint16x8_t b) {
  vuint16m1_t a_high = __riscv_vslidedown_vx_u16m1(a, 4, 8);
  vuint16m1_t b_high = __riscv_vslidedown_vx_u16m1(b, 4, 8);
  vuint32m1_t a_ext = __riscv_vzext_vf2_u32m1(__riscv_vlmul_trunc_v_u16m1_u16mf2(a_high), 4);
  vuint32m1_t b_ext = __riscv_vzext_vf2_u32m1(__riscv_vlmul_trunc_v_u16m1_u16mf2(b_high), 4);
  vbool32_t a_gt_mask = __riscv_vmsgtu_vv_u32m1_b32(a_ext, b_ext, 4);
  vuint32m1_t ab_sub = __riscv_vsub_vv_u32m1(a_ext, b_ext, 4);
  vuint32m1_t ba_sub = __riscv_vsub_vv_u32m1(b_ext, a_ext, 4);
  return __riscv_vmerge_vvm_u32m1(ba_sub, ab_sub, a_gt_mask, 4);
}

FORCE_INLINE uint64x2_t vabdl_high_u32(uint32x4_t a, uint32x4_t b) {
  vuint32m1_t a_high = __riscv_vslidedown_vx_u32m1(a, 2, 4);
  vuint32m1_t b_high = __riscv_vslidedown_vx_u32m1(b, 2, 4);
  vuint64m1_t a_ext = __riscv_vzext_vf2_u64m1(__riscv_vlmul_trunc_v_u32m1_u32mf2(a_high), 2);
  vuint64m1_t b_ext = __riscv_vzext_vf2_u64m1(__riscv_vlmul_trunc_v_u32m1_u32mf2(b_high), 2);
  vbool64_t a_gt_mask = __riscv_vmsgtu_vv_u64m1_b64(a_ext, b_ext, 2);
  vuint64m1_t ab_sub = __riscv_vsub_vv_u64m1(a_ext, b_ext, 2);
  vuint64m1_t ba_sub = __riscv_vsub_vv_u64m1(b_ext, a_ext, 2);
  return __riscv_vmerge_vvm_u64m1(ba_sub, ab_sub, a_gt_mask, 2);
}

FORCE_INLINE int8x8_t vaba_s8(int8x8_t a, int8x8_t b, int8x8_t c) {
  vint8m1_t bc_max = __riscv_vmax_vv_i8m1(b, c, 8);
  vint8m1_t bc_min = __riscv_vmin_vv_i8m1(b, c, 8);
  vint8m1_t max_min_sub = __riscv_vsub_vv_i8m1(bc_max, bc_min, 8);
  return __riscv_vadd_vv_i8m1(a, max_min_sub, 8);
}

FORCE_INLINE int16x4_t vaba_s16(int16x4_t a, int16x4_t b, int16x4_t c) {
  vint16m1_t bc_max = __riscv_vmax_vv_i16m1(b, c, 4);
  vint16m1_t bc_min = __riscv_vmin_vv_i16m1(b, c, 4);
  vint16m1_t max_min_sub = __riscv_vsub_vv_i16m1(bc_max, bc_min, 4);
  return __riscv_vadd_vv_i16m1(a, max_min_sub, 4);
}

FORCE_INLINE int32x2_t vaba_s32(int32x2_t a, int32x2_t b, int32x2_t c) {
  vint32m1_t bc_max = __riscv_vmax_vv_i32m1(b, c, 2);
  vint32m1_t bc_min = __riscv_vmin_vv_i32m1(b, c, 2);
  vint32m1_t max_min_sub = __riscv_vsub_vv_i32m1(bc_max, bc_min, 2);
  return __riscv_vadd_vv_i32m1(a, max_min_sub, 2);
}

FORCE_INLINE uint8x8_t vaba_u8(uint8x8_t a, uint8x8_t b, uint8x8_t c) {
  vuint8m1_t bc_max = __riscv_vmaxu_vv_u8m1(b, c, 8);
  vuint8m1_t bc_min = __riscv_vminu_vv_u8m1(b, c, 8);
  vuint8m1_t max_min_sub = __riscv_vsub_vv_u8m1(bc_max, bc_min, 8);
  return __riscv_vadd_vv_u8m1(a, max_min_sub, 8);
}

FORCE_INLINE uint16x4_t vaba_u16(uint16x4_t a, uint16x4_t b, uint16x4_t c) {
  vuint16m1_t bc_max = __riscv_vmaxu_vv_u16m1(b, c, 4);
  vuint16m1_t bc_min = __riscv_vminu_vv_u16m1(b, c, 4);
  vuint16m1_t max_min_sub = __riscv_vsub_vv_u16m1(bc_max, bc_min, 4);
  return __riscv_vadd_vv_u16m1(a, max_min_sub, 4);
}

FORCE_INLINE uint32x2_t vaba_u32(uint32x2_t a, uint32x2_t b, uint32x2_t c) {
  vuint32m1_t bc_max = __riscv_vmaxu_vv_u32m1(b, c, 2);
  vuint32m1_t bc_min = __riscv_vminu_vv_u32m1(b, c, 2);
  vuint32m1_t max_min_sub = __riscv_vsub_vv_u32m1(bc_max, bc_min, 2);
  return __riscv_vadd_vv_u32m1(a, max_min_sub, 2);
}

FORCE_INLINE int8x16_t vabaq_s8(int8x16_t a, int8x16_t b, int8x16_t c) {
  vint8m1_t bc_max = __riscv_vmax_vv_i8m1(b, c, 16);
  vint8m1_t bc_min = __riscv_vmin_vv_i8m1(b, c, 16);
  vint8m1_t max_min_sub = __riscv_vsub_vv_i8m1(bc_max, bc_min, 16);
  return __riscv_vadd_vv_i8m1(a, max_min_sub, 16);
}

FORCE_INLINE int16x8_t vabaq_s16(int16x8_t a, int16x8_t b, int16x8_t c) {
  vint16m1_t bc_max = __riscv_vmax_vv_i16m1(b, c, 8);
  vint16m1_t bc_min = __riscv_vmin_vv_i16m1(b, c, 8);
  vint16m1_t max_min_sub = __riscv_vsub_vv_i16m1(bc_max, bc_min, 8);
  return __riscv_vadd_vv_i16m1(a, max_min_sub, 8);
}

FORCE_INLINE int32x4_t vabaq_s32(int32x4_t a, int32x4_t b, int32x4_t c) {
  vint32m1_t bc_max = __riscv_vmax_vv_i32m1(b, c, 4);
  vint32m1_t bc_min = __riscv_vmin_vv_i32m1(b, c, 4);
  vint32m1_t max_min_sub = __riscv_vsub_vv_i32m1(bc_max, bc_min, 4);
  return __riscv_vadd_vv_i32m1(a, max_min_sub, 4);
}

FORCE_INLINE uint8x16_t vabaq_u8(uint8x16_t a, uint8x16_t b, uint8x16_t c) {
  vuint8m1_t bc_max = __riscv_vmaxu_vv_u8m1(b, c, 16);
  vuint8m1_t bc_min = __riscv_vminu_vv_u8m1(b, c, 16);
  vuint8m1_t max_min_sub = __riscv_vsub_vv_u8m1(bc_max, bc_min, 16);
  return __riscv_vadd_vv_u8m1(a, max_min_sub, 16);
}

FORCE_INLINE uint16x8_t vabaq_u16(uint16x8_t a, uint16x8_t b, uint16x8_t c) {
  vuint16m1_t bc_max = __riscv_vmaxu_vv_u16m1(b, c, 8);
  vuint16m1_t bc_min = __riscv_vminu_vv_u16m1(b, c, 8);
  vuint16m1_t max_min_sub = __riscv_vsub_vv_u16m1(bc_max, bc_min, 8);
  return __riscv_vadd_vv_u16m1(a, max_min_sub, 8);
}

FORCE_INLINE uint32x4_t vabaq_u32(uint32x4_t a, uint32x4_t b, uint32x4_t c) {
  vuint32m1_t bc_max = __riscv_vmaxu_vv_u32m1(b, c, 4);
  vuint32m1_t bc_min = __riscv_vminu_vv_u32m1(b, c, 4);
  vuint32m1_t max_min_sub = __riscv_vsub_vv_u32m1(bc_max, bc_min, 4);
  return __riscv_vadd_vv_u32m1(a, max_min_sub, 4);
}

FORCE_INLINE int16x8_t vabal_s8(int16x8_t a, int8x8_t b, int8x8_t c) {
  vint16m1_t bc_sub = __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vwsub_vv_i16m2(b, c, 8));
  vint16m1_t sign_bit_mask = __riscv_vsra_vx_i16m1(bc_sub, 15, 8);
  vint16m1_t bc_xor = __riscv_vxor_vv_i16m1(bc_sub, sign_bit_mask, 8);
  vint16m1_t abs_diff = __riscv_vsub_vv_i16m1(bc_xor, sign_bit_mask, 8);
  return __riscv_vadd_vv_i16m1(a, abs_diff, 8);
}

FORCE_INLINE int32x4_t vabal_s16(int32x4_t a, int16x4_t b, int16x4_t c) {
  vint32m1_t bc_sub = __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwsub_vv_i32m2(b, c, 4));
  vint32m1_t sign_bit_mask = __riscv_vsra_vx_i32m1(bc_sub, 31, 4);
  vint32m1_t bc_xor = __riscv_vxor_vv_i32m1(bc_sub, sign_bit_mask, 4);
  vint32m1_t abs_diff = __riscv_vsub_vv_i32m1(bc_xor, sign_bit_mask, 4);
  return __riscv_vadd_vv_i32m1(a, abs_diff, 4);
}

FORCE_INLINE int64x2_t vabal_s32(int64x2_t a, int32x2_t b, int32x2_t c) {
  vint64m1_t bc_sub = __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwsub_vv_i64m2(b, c, 2));
  vint64m1_t sign_bit_mask = __riscv_vsra_vx_i64m1(bc_sub, 63, 2);
  vint64m1_t bc_xor = __riscv_vxor_vv_i64m1(bc_sub, sign_bit_mask, 2);
  vint64m1_t abs_diff = __riscv_vsub_vv_i64m1(bc_xor, sign_bit_mask, 2);
  return __riscv_vadd_vv_i64m1(a, abs_diff, 2);
}

FORCE_INLINE uint16x8_t vabal_u8(uint16x8_t a, uint8x8_t b, uint8x8_t c) {
  vuint8m1_t bc_max = __riscv_vmaxu_vv_u8m1(b, c, 8);
  vuint8m1_t bc_min = __riscv_vminu_vv_u8m1(b, c, 8);
  vuint16m1_t bc_sub = __riscv_vlmul_trunc_v_u16m2_u16m1(__riscv_vwsubu_vv_u16m2(bc_max, bc_min, 8));
  return __riscv_vadd_vv_u16m1(a, bc_sub, 8);
}

FORCE_INLINE uint32x4_t vabal_u16(uint32x4_t a, uint16x4_t b, uint16x4_t c) {
  vuint16m1_t bc_max = __riscv_vmaxu_vv_u16m1(b, c, 4);
  vuint16m1_t bc_min = __riscv_vminu_vv_u16m1(b, c, 4);
  vuint32m1_t bc_sub = __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwsubu_vv_u32m2(bc_max, bc_min, 4));
  return __riscv_vadd_vv_u32m1(a, bc_sub, 4);
}

FORCE_INLINE uint64x2_t vabal_u32(uint64x2_t a, uint32x2_t b, uint32x2_t c) {
  vuint32m1_t bc_max = __riscv_vmaxu_vv_u32m1(b, c, 2);
  vuint32m1_t bc_min = __riscv_vminu_vv_u32m1(b, c, 2);
  vuint64m1_t bc_sub = __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwsubu_vv_u64m2(bc_max, bc_min, 2));
  return __riscv_vadd_vv_u64m1(a, bc_sub, 2);
}

FORCE_INLINE int16x8_t vabal_high_s8(int16x8_t a, int8x16_t b, int8x16_t c) {
  vint8m1_t b_high = __riscv_vslidedown_vx_i8m1(b, 8, 16);
  vint8m1_t c_high = __riscv_vslidedown_vx_i8m1(c, 8, 16);
  vint16m1_t bc_sub = __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vwsub_vv_i16m2(b_high, c_high, 8));
  vint16m1_t sign_bit_mask = __riscv_vsra_vx_i16m1(bc_sub, 15, 8);
  vint16m1_t bc_xor = __riscv_vxor_vv_i16m1(bc_sub, sign_bit_mask, 8);
  vint16m1_t abs_diff = __riscv_vsub_vv_i16m1(bc_xor, sign_bit_mask, 8);
  return __riscv_vadd_vv_i16m1(a, abs_diff, 8);
}

FORCE_INLINE int32x4_t vabal_high_s16(int32x4_t a, int16x8_t b, int16x8_t c) {
  vint16m1_t b_high = __riscv_vslidedown_vx_i16m1(b, 4, 8);
  vint16m1_t c_high = __riscv_vslidedown_vx_i16m1(c, 4, 8);
  vint32m1_t bc_sub = __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwsub_vv_i32m2(b_high, c_high, 4));
  vint32m1_t sign_bit_mask = __riscv_vsra_vx_i32m1(bc_sub, 31, 4);
  vint32m1_t bc_xor = __riscv_vxor_vv_i32m1(bc_sub, sign_bit_mask, 4);
  vint32m1_t abs_diff = __riscv_vsub_vv_i32m1(bc_xor, sign_bit_mask, 4);
  return __riscv_vadd_vv_i32m1(a, abs_diff, 4);
}

FORCE_INLINE int64x2_t vabal_high_s32(int64x2_t a, int32x4_t b, int32x4_t c) {
  vint32m1_t b_high = __riscv_vslidedown_vx_i32m1(b, 2, 4);
  vint32m1_t c_high = __riscv_vslidedown_vx_i32m1(c, 2, 4);
  vint64m1_t bc_sub = __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwsub_vv_i64m2(b_high, c_high, 2));
  vint64m1_t sign_bit_mask = __riscv_vsra_vx_i64m1(bc_sub, 63, 2);
  vint64m1_t bc_xor = __riscv_vxor_vv_i64m1(bc_sub, sign_bit_mask, 2);
  vint64m1_t abs_diff = __riscv_vsub_vv_i64m1(bc_xor, sign_bit_mask, 2);
  return __riscv_vadd_vv_i64m1(a, abs_diff, 2);
}

FORCE_INLINE uint16x8_t vabal_high_u8(uint16x8_t a, uint8x16_t b, uint8x16_t c) {
  vuint8m1_t b_high = __riscv_vslidedown_vx_u8m1(b, 8, 16);
  vuint8m1_t c_high = __riscv_vslidedown_vx_u8m1(c, 8, 16);
  vuint8m1_t bc_max = __riscv_vmaxu_vv_u8m1(b_high, c_high, 8);
  vuint8m1_t bc_min = __riscv_vminu_vv_u8m1(b_high, c_high, 8);
  vuint16m1_t bc_sub = __riscv_vlmul_trunc_v_u16m2_u16m1(__riscv_vwsubu_vv_u16m2(bc_max, bc_min, 8));
  return __riscv_vadd_vv_u16m1(a, bc_sub, 8);
}

FORCE_INLINE uint32x4_t vabal_high_u16(uint32x4_t a, uint16x8_t b, uint16x8_t c) {
  vuint16m1_t b_high = __riscv_vslidedown_vx_u16m1(b, 4, 8);
  vuint16m1_t c_high = __riscv_vslidedown_vx_u16m1(c, 4, 8);
  vuint16m1_t bc_max = __riscv_vmaxu_vv_u16m1(b_high, c_high, 4);
  vuint16m1_t bc_min = __riscv_vminu_vv_u16m1(b_high, c_high, 4);
  vuint32m1_t bc_sub = __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwsubu_vv_u32m2(bc_max, bc_min, 4));
  return __riscv_vadd_vv_u32m1(a, bc_sub, 4);
}

FORCE_INLINE uint64x2_t vabal_high_u32(uint64x2_t a, uint32x4_t b, uint32x4_t c) {
  vuint32m1_t b_high = __riscv_vslidedown_vx_u32m1(b, 2, 4);
  vuint32m1_t c_high = __riscv_vslidedown_vx_u32m1(c, 2, 4);
  vuint32m1_t bc_max = __riscv_vmaxu_vv_u32m1(b_high, c_high, 2);
  vuint32m1_t bc_min = __riscv_vminu_vv_u32m1(b_high, c_high, 2);
  vuint64m1_t bc_sub = __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwsubu_vv_u64m2(bc_max, bc_min, 2));
  return __riscv_vadd_vv_u64m1(a, bc_sub, 2);
}

FORCE_INLINE int8x8_t vmax_s8(int8x8_t a, int8x8_t b) { return __riscv_vmax_vv_i8m1(a, b, 8); }

FORCE_INLINE int16x4_t vmax_s16(int16x4_t a, int16x4_t b) { return __riscv_vmax_vv_i16m1(a, b, 4); }

FORCE_INLINE int32x2_t vmax_s32(int32x2_t a, int32x2_t b) { return __riscv_vmax_vv_i32m1(a, b, 2); }

FORCE_INLINE float32x2_t vmax_f32(float32x2_t a, float32x2_t b) { return __riscv_vfmax_vv_f32m1(a, b, 2); }

FORCE_INLINE uint8x8_t vmax_u8(uint8x8_t a, uint8x8_t b) { return __riscv_vmaxu_vv_u8m1(a, b, 8); }

FORCE_INLINE uint16x4_t vmax_u16(uint16x4_t a, uint16x4_t b) { return __riscv_vmaxu_vv_u16m1(a, b, 4); }

FORCE_INLINE uint32x2_t vmax_u32(uint32x2_t a, uint32x2_t b) { return __riscv_vmaxu_vv_u32m1(a, b, 2); }

FORCE_INLINE int8x16_t vmaxq_s8(int8x16_t a, int8x16_t b) { return __riscv_vmax_vv_i8m1(a, b, 16); }

FORCE_INLINE int16x8_t vmaxq_s16(int16x8_t a, int16x8_t b) { return __riscv_vmax_vv_i16m1(a, b, 8); }

FORCE_INLINE int32x4_t vmaxq_s32(int32x4_t a, int32x4_t b) { return __riscv_vmax_vv_i32m1(a, b, 4); }

FORCE_INLINE float32x4_t vmaxq_f32(float32x4_t a, float32x4_t b) {
  vbool32_t mask = __riscv_vmand_mm_b32(__riscv_vmfeq_vv_f32m1_b32(a, a, 4), __riscv_vmfeq_vv_f32m1_b32(b, b, 4), 4);
  float32x4_t max_res = __riscv_vfmax_vv_f32m1(a, b, 4);
  return __riscv_vmerge_vvm_f32m1(vdupq_n_f32(NAN), max_res, mask, 4);
}

FORCE_INLINE float64x1_t vmax_f64(float64x1_t a, float64x1_t b) { return __riscv_vfmax_vv_f64m1(a, b, 1); }

FORCE_INLINE float64x2_t vmaxq_f64(float64x2_t a, float64x2_t b) {
  vbool64_t mask = __riscv_vmand_mm_b64(__riscv_vmfeq_vv_f64m1_b64(a, a, 2), __riscv_vmfeq_vv_f64m1_b64(b, b, 2), 2);
  float64x2_t max_res = __riscv_vfmax_vv_f64m1(a, b, 2);
  return __riscv_vmerge_vvm_f64m1(vdupq_n_f64(NAN), max_res, mask, 2);
}

FORCE_INLINE float32x2_t vmaxnm_f32(float32x2_t a, float32x2_t b) {
  vbool32_t a_non_nan_mask = __riscv_vmfeq_vv_f32m1_b32(a, a, 2);
  vbool32_t b_non_nan_mask = __riscv_vmfeq_vv_f32m1_b32(b, b, 2);
  float32x2_t a_replace = __riscv_vmerge_vvm_f32m1(b, a, a_non_nan_mask, 2);
  float32x2_t b_replace = __riscv_vmerge_vvm_f32m1(a, b, b_non_nan_mask, 2);
  return __riscv_vfmax_vv_f32m1(a_replace, b_replace, 2);
}

FORCE_INLINE float32x4_t vmaxnmq_f32(float32x4_t a, float32x4_t b) {
  vbool32_t a_non_nan_mask = __riscv_vmfeq_vv_f32m1_b32(a, a, 4);
  vbool32_t b_non_nan_mask = __riscv_vmfeq_vv_f32m1_b32(b, b, 4);
  float32x2_t a_replace = __riscv_vmerge_vvm_f32m1(b, a, a_non_nan_mask, 4);
  float32x2_t b_replace = __riscv_vmerge_vvm_f32m1(a, b, b_non_nan_mask, 4);
  return __riscv_vfmax_vv_f32m1(a_replace, b_replace, 4);
}

FORCE_INLINE float64x1_t vmaxnm_f64(float64x1_t a, float64x1_t b) {
  vbool64_t a_non_nan_mask = __riscv_vmfeq_vv_f64m1_b64(a, a, 1);
  vbool64_t b_non_nan_mask = __riscv_vmfeq_vv_f64m1_b64(b, b, 1);
  float64x2_t a_replace = __riscv_vmerge_vvm_f64m1(b, a, a_non_nan_mask, 1);
  float64x2_t b_replace = __riscv_vmerge_vvm_f64m1(a, b, b_non_nan_mask, 1);
  return __riscv_vfmax_vv_f64m1(a_replace, b_replace, 1);
}

FORCE_INLINE float64x2_t vmaxnmq_f64(float64x2_t a, float64x2_t b) {
  vbool64_t a_non_nan_mask = __riscv_vmfeq_vv_f64m1_b64(a, a, 2);
  vbool64_t b_non_nan_mask = __riscv_vmfeq_vv_f64m1_b64(b, b, 2);
  float64x2_t a_replace = __riscv_vmerge_vvm_f64m1(b, a, a_non_nan_mask, 2);
  float64x2_t b_replace = __riscv_vmerge_vvm_f64m1(a, b, b_non_nan_mask, 2);
  return __riscv_vfmax_vv_f64m1(a_replace, b_replace, 2);
}

FORCE_INLINE float32x2_t vminnm_f32(float32x2_t a, float32x2_t b) {
  vbool32_t a_non_nan_mask = __riscv_vmfeq_vv_f32m1_b32(a, a, 2);
  vbool32_t b_non_nan_mask = __riscv_vmfeq_vv_f32m1_b32(b, b, 2);
  float32x2_t a_replace = __riscv_vmerge_vvm_f32m1(b, a, a_non_nan_mask, 2);
  float32x2_t b_replace = __riscv_vmerge_vvm_f32m1(a, b, b_non_nan_mask, 2);
  return __riscv_vfmin_vv_f32m1(a_replace, b_replace, 2);
}

FORCE_INLINE float32x4_t vminnmq_f32(float32x4_t a, float32x4_t b) {
  vbool32_t a_non_nan_mask = __riscv_vmfeq_vv_f32m1_b32(a, a, 4);
  vbool32_t b_non_nan_mask = __riscv_vmfeq_vv_f32m1_b32(b, b, 4);
  float32x2_t a_replace = __riscv_vmerge_vvm_f32m1(b, a, a_non_nan_mask, 4);
  float32x2_t b_replace = __riscv_vmerge_vvm_f32m1(a, b, b_non_nan_mask, 4);
  return __riscv_vfmin_vv_f32m1(a_replace, b_replace, 4);
}

FORCE_INLINE float64x1_t vminnm_f64(float64x1_t a, float64x1_t b) {
  vbool64_t a_non_nan_mask = __riscv_vmfeq_vv_f64m1_b64(a, a, 1);
  vbool64_t b_non_nan_mask = __riscv_vmfeq_vv_f64m1_b64(b, b, 1);
  float64x2_t a_replace = __riscv_vmerge_vvm_f64m1(b, a, a_non_nan_mask, 1);
  float64x2_t b_replace = __riscv_vmerge_vvm_f64m1(a, b, b_non_nan_mask, 1);
  return __riscv_vfmin_vv_f64m1(a_replace, b_replace, 1);
}

FORCE_INLINE float64x2_t vminnmq_f64(float64x2_t a, float64x2_t b) {
  vbool64_t a_non_nan_mask = __riscv_vmfeq_vv_f64m1_b64(a, a, 2);
  vbool64_t b_non_nan_mask = __riscv_vmfeq_vv_f64m1_b64(b, b, 2);
  float64x2_t a_replace = __riscv_vmerge_vvm_f64m1(b, a, a_non_nan_mask, 2);
  float64x2_t b_replace = __riscv_vmerge_vvm_f64m1(a, b, b_non_nan_mask, 2);
  return __riscv_vfmin_vv_f64m1(a_replace, b_replace, 2);
}

FORCE_INLINE uint8x16_t vmaxq_u8(uint8x16_t a, uint8x16_t b) { return __riscv_vmaxu_vv_u8m1(a, b, 16); }

FORCE_INLINE uint16x8_t vmaxq_u16(uint16x8_t a, uint16x8_t b) { return __riscv_vmaxu_vv_u16m1(a, b, 8); }

FORCE_INLINE uint32x4_t vmaxq_u32(uint32x4_t a, uint32x4_t b) { return __riscv_vmaxu_vv_u32m1(a, b, 4); }

FORCE_INLINE int8x8_t vmin_s8(int8x8_t a, int8x8_t b) { return __riscv_vmin_vv_i8m1(a, b, 8); }

FORCE_INLINE int16x4_t vmin_s16(int16x4_t a, int16x4_t b) { return __riscv_vmin_vv_i16m1(a, b, 4); }

FORCE_INLINE int32x2_t vmin_s32(int32x2_t a, int32x2_t b) { return __riscv_vmin_vv_i32m1(a, b, 2); }

FORCE_INLINE float32x2_t vmin_f32(float32x2_t a, float32x2_t b) { return __riscv_vfmin_vv_f32m1(a, b, 2); }

FORCE_INLINE uint8x8_t vmin_u8(uint8x8_t a, uint8x8_t b) { return __riscv_vminu_vv_u8m1(a, b, 8); }

FORCE_INLINE uint16x4_t vmin_u16(uint16x4_t a, uint16x4_t b) { return __riscv_vminu_vv_u16m1(a, b, 4); }

FORCE_INLINE uint32x2_t vmin_u32(uint32x2_t a, uint32x2_t b) { return __riscv_vminu_vv_u32m1(a, b, 2); }

FORCE_INLINE int8x16_t vminq_s8(int8x16_t a, int8x16_t b) { return __riscv_vmin_vv_i8m1(a, b, 16); }

FORCE_INLINE int16x8_t vminq_s16(int16x8_t a, int16x8_t b) { return __riscv_vmin_vv_i16m1(a, b, 8); }

FORCE_INLINE int32x4_t vminq_s32(int32x4_t a, int32x4_t b) { return __riscv_vmin_vv_i32m1(a, b, 4); }

FORCE_INLINE float32x4_t vminq_f32(float32x4_t a, float32x4_t b) {
  vbool32_t mask = __riscv_vmand_mm_b32(__riscv_vmfeq_vv_f32m1_b32(a, a, 4), __riscv_vmfeq_vv_f32m1_b32(b, b, 4), 4);
  float32x4_t min_res = __riscv_vfmin_vv_f32m1(a, b, 4);
  return __riscv_vmerge_vvm_f32m1(vdupq_n_f32(NAN), min_res, mask, 4);
}

FORCE_INLINE float64x1_t vmin_f64(float64x1_t a, float64x1_t b) { return __riscv_vfmin_vv_f64m1(a, b, 1); }

FORCE_INLINE float64x2_t vminq_f64(float64x2_t a, float64x2_t b) {
  vbool64_t mask = __riscv_vmand_mm_b64(__riscv_vmfeq_vv_f64m1_b64(a, a, 2), __riscv_vmfeq_vv_f64m1_b64(b, b, 2), 2);
  float64x2_t min_res = __riscv_vfmin_vv_f64m1(a, b, 2);
  return __riscv_vmerge_vvm_f64m1(vdupq_n_f64(NAN), min_res, mask, 2);
}

FORCE_INLINE uint8x16_t vminq_u8(uint8x16_t a, uint8x16_t b) { return __riscv_vminu_vv_u8m1(a, b, 16); }

FORCE_INLINE uint16x8_t vminq_u16(uint16x8_t a, uint16x8_t b) { return __riscv_vminu_vv_u16m1(a, b, 8); }

FORCE_INLINE uint32x4_t vminq_u32(uint32x4_t a, uint32x4_t b) { return __riscv_vminu_vv_u32m1(a, b, 4); }

FORCE_INLINE int8x8_t vpadd_s8(int8x8_t a, int8x8_t b) {
  vint8m1_t ab = __riscv_vslideup_vx_i8m1(a, b, 8, 16);
  vint8m1_t ab_s = __riscv_vslidedown_vx_i8m1(ab, 1, 16);
  vint8m1_t ab_add = __riscv_vadd_vv_i8m1(ab, ab_s, 16);
  return __riscv_vlmul_ext_v_i8mf2_i8m1(__riscv_vncvt_x_x_w_i8mf2(__riscv_vreinterpret_v_i8m1_i16m1(ab_add), 8));
}

FORCE_INLINE int16x4_t vpadd_s16(int16x4_t a, int16x4_t b) {
  vint16m1_t ab = __riscv_vslideup_vx_i16m1(a, b, 4, 8);
  vint16m1_t ab_s = __riscv_vslidedown_vx_i16m1(ab, 1, 8);
  vint16m1_t ab_add = __riscv_vadd_vv_i16m1(ab, ab_s, 8);
  return __riscv_vlmul_ext_v_i16mf2_i16m1(__riscv_vncvt_x_x_w_i16mf2(__riscv_vreinterpret_v_i16m1_i32m1(ab_add), 4));
}

FORCE_INLINE int32x2_t vpadd_s32(int32x2_t a, int32x2_t b) {
  vint32m1_t ab = __riscv_vslideup_vx_i32m1(a, b, 2, 4);
  vint32m1_t ab_s = __riscv_vslidedown_vx_i32m1(ab, 1, 4);
  vint32m1_t ab_add = __riscv_vadd_vv_i32m1(ab, ab_s, 4);
  return __riscv_vlmul_ext_v_i32mf2_i32m1(__riscv_vncvt_x_x_w_i32mf2(__riscv_vreinterpret_v_i32m1_i64m1(ab_add), 2));
}

FORCE_INLINE float32x2_t vpadd_f32(float32x2_t a, float32x2_t b) {
  vfloat32m1_t ab = __riscv_vslideup_vx_f32m1(a, b, 2, 4);
  vfloat32m1_t ab_s = __riscv_vslidedown_vx_f32m1(ab, 1, 4);
  vfloat32m1_t ab_add = __riscv_vfadd_vv_f32m1(ab, ab_s, 4);
  vuint32m1_t w = __riscv_vreinterpret_v_f32m1_u32m1(ab_add);
  return __riscv_vreinterpret_v_u32m1_f32m1(
      __riscv_vlmul_ext_v_u32mf2_u32m1(__riscv_vncvt_x_x_w_u32mf2(__riscv_vreinterpret_v_u32m1_u64m1(w), 2)));
}

FORCE_INLINE int8x16_t vpaddq_s8(int8x16_t a, int8x16_t b) {
  vint8m2_t a_m2 = __riscv_vlmul_ext_v_i8m1_i8m2(a);
  vint8m2_t b_m2 = __riscv_vlmul_ext_v_i8m1_i8m2(b);
  vint8m2_t ab = __riscv_vslideup_vx_i8m2(a_m2, b_m2, 16, 32);
  vint8m2_t ab_s = __riscv_vslidedown_vx_i8m2(ab, 1, 32);
  vint8m2_t ab_add = __riscv_vadd_vv_i8m2(ab, ab_s, 32);
  return __riscv_vncvt_x_x_w_i8m1(__riscv_vreinterpret_v_i8m2_i16m2(ab_add), 16);
}

FORCE_INLINE int16x8_t vpaddq_s16(int16x8_t a, int16x8_t b) {
  vint16m2_t a_m2 = __riscv_vlmul_ext_v_i16m1_i16m2(a);
  vint16m2_t b_m2 = __riscv_vlmul_ext_v_i16m1_i16m2(b);
  vint16m2_t ab = __riscv_vslideup_vx_i16m2(a_m2, b_m2, 8, 16);
  vint16m2_t ab_s = __riscv_vslidedown_vx_i16m2(ab, 1, 16);
  vint16m2_t ab_add = __riscv_vadd_vv_i16m2(ab, ab_s, 16);
  return __riscv_vncvt_x_x_w_i16m1(__riscv_vreinterpret_v_i16m2_i32m2(ab_add), 8);
}

FORCE_INLINE int32x4_t vpaddq_s32(int32x4_t a, int32x4_t b) {
  vint32m2_t a_m2 = __riscv_vlmul_ext_v_i32m1_i32m2(a);
  vint32m2_t b_m2 = __riscv_vlmul_ext_v_i32m1_i32m2(b);
  vint32m2_t ab = __riscv_vslideup_vx_i32m2(a_m2, b_m2, 4, 8);
  vint32m2_t ab_s = __riscv_vslidedown_vx_i32m2(ab, 1, 8);
  vint32m2_t ab_add = __riscv_vadd_vv_i32m2(ab, ab_s, 8);
  return __riscv_vncvt_x_x_w_i32m1(__riscv_vreinterpret_v_i32m2_i64m2(ab_add), 4);
}

FORCE_INLINE int64x2_t vpaddq_s64(int64x2_t a, int64x2_t b) {
  vbool32_t mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8(85));
  vint64m2_t a_m2 = __riscv_vlmul_ext_v_i64m1_i64m2(a);
  vint64m2_t b_m2 = __riscv_vlmul_ext_v_i64m1_i64m2(b);
  vint64m2_t ab = __riscv_vslideup_vx_i64m2(a_m2, b_m2, 2, 4);
  vint64m2_t ab_s = __riscv_vslidedown_vx_i64m2(ab, 1, 4);
  vint64m2_t ab_add = __riscv_vadd_vv_i64m2(ab, ab_s, 4);
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vcompress_vm_i64m2(ab_add, mask, 4));
}

FORCE_INLINE uint8x16_t vpaddq_u8(uint8x16_t a, uint8x16_t b) {
  vuint8m2_t a_m2 = __riscv_vlmul_ext_v_u8m1_u8m2(a);
  vuint8m2_t b_m2 = __riscv_vlmul_ext_v_u8m1_u8m2(b);
  vuint8m2_t ab = __riscv_vslideup_vx_u8m2(a_m2, b_m2, 16, 32);
  vuint8m2_t ab_s = __riscv_vslidedown_vx_u8m2(ab, 1, 32);
  vuint8m2_t ab_add = __riscv_vadd_vv_u8m2(ab, ab_s, 32);
  return __riscv_vncvt_x_x_w_u8m1(__riscv_vreinterpret_v_u8m2_u16m2(ab_add), 16);
}

FORCE_INLINE uint16x8_t vpaddq_u16(uint16x8_t a, uint16x8_t b) {
  vuint16m2_t a_m2 = __riscv_vlmul_ext_v_u16m1_u16m2(a);
  vuint16m2_t b_m2 = __riscv_vlmul_ext_v_u16m1_u16m2(b);
  vuint16m2_t ab = __riscv_vslideup_vx_u16m2(a_m2, b_m2, 8, 16);
  vuint16m2_t ab_s = __riscv_vslidedown_vx_u16m2(ab, 1, 16);
  vuint16m2_t ab_add = __riscv_vadd_vv_u16m2(ab, ab_s, 16);
  return __riscv_vncvt_x_x_w_u16m1(__riscv_vreinterpret_v_u16m2_u32m2(ab_add), 8);
}

FORCE_INLINE uint32x4_t vpaddq_u32(uint32x4_t a, uint32x4_t b) {
  vuint32m2_t a_m2 = __riscv_vlmul_ext_v_u32m1_u32m2(a);
  vuint32m2_t b_m2 = __riscv_vlmul_ext_v_u32m1_u32m2(b);
  vuint32m2_t ab = __riscv_vslideup_vx_u32m2(a_m2, b_m2, 4, 8);
  vuint32m2_t ab_s = __riscv_vslidedown_vx_u32m2(ab, 1, 8);
  vuint32m2_t ab_add = __riscv_vadd_vv_u32m2(ab, ab_s, 8);
  return __riscv_vncvt_x_x_w_u32m1(__riscv_vreinterpret_v_u32m2_u64m2(ab_add), 4);
}

FORCE_INLINE uint64x2_t vpaddq_u64(uint64x2_t a, uint64x2_t b) {
  vbool32_t mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8(85));
  vuint64m2_t a_m2 = __riscv_vlmul_ext_v_u64m1_u64m2(a);
  vuint64m2_t b_m2 = __riscv_vlmul_ext_v_u64m1_u64m2(b);
  vuint64m2_t ab = __riscv_vslideup_vx_u64m2(a_m2, b_m2, 2, 4);
  vuint64m2_t ab_s = __riscv_vslidedown_vx_u64m2(ab, 1, 4);
  vuint64m2_t ab_add = __riscv_vadd_vv_u64m2(ab, ab_s, 4);
  return __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vcompress_vm_u64m2(ab_add, mask, 4));
}

FORCE_INLINE float32x4_t vpaddq_f32(float32x4_t a, float32x4_t b) {
  vfloat32m2_t a_m2 = __riscv_vlmul_ext_v_f32m1_f32m2(a);
  vfloat32m2_t b_m2 = __riscv_vlmul_ext_v_f32m1_f32m2(b);
  vfloat32m2_t ab = __riscv_vslideup_vx_f32m2(a_m2, b_m2, 4, 8);
  vfloat32m2_t ab_s = __riscv_vslidedown_vx_f32m2(ab, 1, 8);
  vfloat32m2_t ab_add = __riscv_vfadd_vv_f32m2(ab, ab_s, 8);
  return __riscv_vreinterpret_v_u32m1_f32m1(
      __riscv_vncvt_x_x_w_u32m1(__riscv_vreinterpret_v_u32m2_u64m2(__riscv_vreinterpret_v_f32m2_u32m2(ab_add)), 4));
}

FORCE_INLINE float64x2_t vpaddq_f64(float64x2_t a, float64x2_t b) {
  vbool32_t mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8(85));
  vfloat64m2_t a_m2 = __riscv_vlmul_ext_v_f64m1_f64m2(a);
  vfloat64m2_t b_m2 = __riscv_vlmul_ext_v_f64m1_f64m2(b);
  vfloat64m2_t ab = __riscv_vslideup_vx_f64m2(a_m2, b_m2, 2, 4);
  vfloat64m2_t ab_s = __riscv_vslidedown_vx_f64m2(ab, 1, 4);
  vfloat64m2_t ab_add = __riscv_vfadd_vv_f64m2(ab, ab_s, 4);
  return __riscv_vlmul_trunc_v_f64m2_f64m1(__riscv_vcompress_vm_f64m2(ab_add, mask, 4));
}

FORCE_INLINE uint8x8_t vpadd_u8(uint8x8_t a, uint8x8_t b) {
  vuint8m1_t ab = __riscv_vslideup_vx_u8m1(a, b, 8, 16);
  vuint8m1_t ab_s = __riscv_vslidedown_vx_u8m1(ab, 1, 16);
  vuint8m1_t ab_add = __riscv_vadd_vv_u8m1(ab, ab_s, 16);
  return __riscv_vlmul_ext_v_u8mf2_u8m1(__riscv_vncvt_x_x_w_u8mf2(__riscv_vreinterpret_v_u8m1_u16m1(ab_add), 8));
}

FORCE_INLINE uint16x4_t vpadd_u16(uint16x4_t a, uint16x4_t b) {
  vuint16m1_t ab = __riscv_vslideup_vx_u16m1(a, b, 4, 8);
  vuint16m1_t ab_s = __riscv_vslidedown_vx_u16m1(ab, 1, 8);
  vuint16m1_t ab_add = __riscv_vadd_vv_u16m1(ab, ab_s, 8);
  return __riscv_vlmul_ext_v_u16mf2_u16m1(__riscv_vncvt_x_x_w_u16mf2(__riscv_vreinterpret_v_u16m1_u32m1(ab_add), 4));
}

FORCE_INLINE uint32x2_t vpadd_u32(uint32x2_t a, uint32x2_t b) {
  vuint32m1_t ab = __riscv_vslideup_vx_u32m1(a, b, 2, 4);
  vuint32m1_t ab_s = __riscv_vslidedown_vx_u32m1(ab, 1, 4);
  vuint32m1_t ab_add = __riscv_vadd_vv_u32m1(ab, ab_s, 4);
  return __riscv_vlmul_ext_v_u32mf2_u32m1(__riscv_vncvt_x_x_w_u32mf2(__riscv_vreinterpret_v_u32m1_u64m1(ab_add), 2));
}

FORCE_INLINE int16x4_t vpaddl_s8(int8x8_t a) {
  vint8m1_t a_s = __riscv_vslidedown_vx_i8m1(a, 1, 8);
  vint16m2_t a_add = __riscv_vwadd_vv_i16m2(a, a_s, 8);
  return __riscv_vnsra_wx_i16m1(__riscv_vreinterpret_v_i16m2_i32m2(a_add), 0, 4);
}

FORCE_INLINE int32x2_t vpaddl_s16(int16x4_t a) {
  vint16m1_t a_s = __riscv_vslidedown_vx_i16m1(a, 1, 4);
  vint32m2_t a_add = __riscv_vwadd_vv_i32m2(a, a_s, 4);
  return __riscv_vnsra_wx_i32m1(__riscv_vreinterpret_v_i32m2_i64m2(a_add), 0, 2);
}

FORCE_INLINE int64x1_t vpaddl_s32(int32x2_t a) {
  vint32m1_t a_s = __riscv_vslidedown_vx_i32m1(a, 1, 2);
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwadd_vv_i64m2(a, a_s, 2));
}

FORCE_INLINE uint16x4_t vpaddl_u8(uint8x8_t a) {
  vuint8m1_t a_s = __riscv_vslidedown_vx_u8m1(a, 1, 8);
  vuint16m2_t a_add = __riscv_vwaddu_vv_u16m2(a, a_s, 8);
  return __riscv_vnsrl_wx_u16m1(__riscv_vreinterpret_v_u16m2_u32m2(a_add), 0, 4);
}

FORCE_INLINE uint32x2_t vpaddl_u16(uint16x4_t a) {
  vuint16m1_t a_s = __riscv_vslidedown_vx_u16m1(a, 1, 4);
  vuint32m2_t a_add = __riscv_vwaddu_vv_u32m2(a, a_s, 4);
  return __riscv_vnsrl_wx_u32m1(__riscv_vreinterpret_v_u32m2_u64m2(a_add), 0, 2);
}

FORCE_INLINE uint64x1_t vpaddl_u32(uint32x2_t a) {
  vuint32m1_t a_s = __riscv_vslidedown_vx_u32m1(a, 1, 2);
  return __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwaddu_vv_u64m2(a, a_s, 2));
}

FORCE_INLINE int16x8_t vpaddlq_s8(int8x16_t a) {
  vint8m1_t a_s = __riscv_vslidedown_vx_i8m1(a, 1, 16);
  vint16m2_t a_add = __riscv_vwadd_vv_i16m2(a, a_s, 16);
  return __riscv_vnsra_wx_i16m1(__riscv_vreinterpret_v_i16m2_i32m2(a_add), 0, 8);
}

FORCE_INLINE int32x4_t vpaddlq_s16(int16x8_t a) {
  vint16m1_t a_s = __riscv_vslidedown_vx_i16m1(a, 1, 8);
  vint32m2_t a_add = __riscv_vwadd_vv_i32m2(a, a_s, 8);
  return __riscv_vnsra_wx_i32m1(__riscv_vreinterpret_v_i32m2_i64m2(a_add), 0, 4);
}

FORCE_INLINE int64x2_t vpaddlq_s32(int32x4_t a) {
  vint32m1_t a_s = __riscv_vslidedown_vx_i32m1(a, 1, 4);
  vint64m2_t a_padd = __riscv_vwadd_vv_i64m2(a, a_s, 4);
  return __riscv_vlmul_trunc_v_i64m2_i64m1(
      __riscv_vcompress_vm_i64m2(a_padd, __riscv_vreinterpret_v_i8m1_b32(vdup_n_s8(85)), 4));
}

FORCE_INLINE uint16x8_t vpaddlq_u8(uint8x16_t a) {
  vuint8m1_t a_s = __riscv_vslidedown_vx_u8m1(a, 1, 16);
  vuint16m2_t a_add = __riscv_vwaddu_vv_u16m2(a, a_s, 16);
  return __riscv_vnsrl_wx_u16m1(__riscv_vreinterpret_v_u16m2_u32m2(a_add), 0, 8);
}

FORCE_INLINE uint32x4_t vpaddlq_u16(uint16x8_t a) {
  vuint16m1_t a_s = __riscv_vslidedown_vx_u16m1(a, 1, 8);
  vuint32m2_t a_add = __riscv_vwaddu_vv_u32m2(a, a_s, 8);
  return __riscv_vnsrl_wx_u32m1(__riscv_vreinterpret_v_u32m2_u64m2(a_add), 0, 4);
}

FORCE_INLINE uint64x2_t vpaddlq_u32(uint32x4_t a) {
  vuint32m1_t a_s = __riscv_vslidedown_vx_u32m1(a, 1, 4);
  vuint64m2_t a_padd = __riscv_vwaddu_vv_u64m2(a, a_s, 4);
  return __riscv_vlmul_trunc_v_u64m2_u64m1(
      __riscv_vcompress_vm_u64m2(a_padd, __riscv_vreinterpret_v_i8m1_b32(vdup_n_s8(85)), 4));
}

FORCE_INLINE int16x4_t vpadal_s8(int16x4_t a, int8x8_t b) {
  vint8m1_t b_s = __riscv_vslidedown_vx_i8m1(b, 1, 8);
  vint16m2_t b_add = __riscv_vwadd_vv_i16m2(b, b_s, 8);
  vint16m1_t padd = __riscv_vnsra_wx_i16m1(__riscv_vreinterpret_v_i16m2_i32m2(b_add), 0, 8);
  return __riscv_vadd_vv_i16m1(padd, a, 8);
}

FORCE_INLINE int32x2_t vpadal_s16(int32x2_t a, int16x4_t b) {
  vint16m1_t b_s = __riscv_vslidedown_vx_i16m1(b, 1, 4);
  vint32m2_t b_add = __riscv_vwadd_vv_i32m2(b, b_s, 4);
  vint32m1_t padd = __riscv_vnsra_wx_i32m1(__riscv_vreinterpret_v_i32m2_i64m2(b_add), 0, 4);
  return __riscv_vadd_vv_i32m1(padd, a, 4);
}

FORCE_INLINE int64x1_t vpadal_s32(int64x1_t a, int32x2_t b) {
  vint32m1_t b_s = __riscv_vslidedown_vx_i32m1(b, 1, 2);
  vint64m1_t padd = __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwadd_vv_i64m2(b, b_s, 2));
  return __riscv_vadd_vv_i64m1(padd, a, 2);
}

FORCE_INLINE uint16x4_t vpadal_u8(uint16x4_t a, uint8x8_t b) {
  vuint8m1_t b_s = __riscv_vslidedown_vx_u8m1(b, 1, 8);
  vuint16m2_t b_add = __riscv_vwaddu_vv_u16m2(b, b_s, 8);
  vuint16m1_t padd = __riscv_vnsrl_wx_u16m1(__riscv_vreinterpret_v_u16m2_u32m2(b_add), 0, 8);
  return __riscv_vadd_vv_u16m1(padd, a, 8);
}

FORCE_INLINE uint32x2_t vpadal_u16(uint32x2_t a, uint16x4_t b) {
  vuint16m1_t b_s = __riscv_vslidedown_vx_u16m1(b, 1, 4);
  vuint32m2_t b_add = __riscv_vwaddu_vv_u32m2(b, b_s, 4);
  vuint32m1_t padd = __riscv_vnsrl_wx_u32m1(__riscv_vreinterpret_v_u32m2_u64m2(b_add), 0, 4);
  return __riscv_vadd_vv_u32m1(padd, a, 4);
}

FORCE_INLINE uint64x1_t vpadal_u32(uint64x1_t a, uint32x2_t b) {
  vuint32m1_t b_s = __riscv_vslidedown_vx_u32m1(b, 1, 2);
  vuint64m1_t padd = __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwaddu_vv_u64m2(b, b_s, 2));
  return __riscv_vadd_vv_u64m1(padd, a, 2);
}

FORCE_INLINE int16x8_t vpadalq_s8(int16x8_t a, int8x16_t b) {
  vint8m1_t b_s = __riscv_vslidedown_vx_i8m1(b, 1, 16);
  vint16m2_t b_add = __riscv_vwadd_vv_i16m2(b, b_s, 16);
  vint16m1_t padd = __riscv_vnsra_wx_i16m1(__riscv_vreinterpret_v_i16m2_i32m2(b_add), 0, 16);
  return __riscv_vadd_vv_i16m1(padd, a, 16);
}

FORCE_INLINE int32x4_t vpadalq_s16(int32x4_t a, int16x8_t b) {
  vint16m1_t b_s = __riscv_vslidedown_vx_i16m1(b, 1, 8);
  vint32m2_t b_add = __riscv_vwadd_vv_i32m2(b, b_s, 8);
  vint32m1_t padd = __riscv_vnsra_wx_i32m1(__riscv_vreinterpret_v_i32m2_i64m2(b_add), 0, 8);
  return __riscv_vadd_vv_i32m1(padd, a, 8);
}

FORCE_INLINE int64x2_t vpadalq_s32(int64x2_t a, int32x4_t b) {
  vint32m1_t b_s = __riscv_vslidedown_vx_i32m1(b, 1, 4);
  vint64m2_t padd = __riscv_vwadd_vv_i64m2(b, b_s, 4);
  vint64m1_t padd_res = __riscv_vlmul_trunc_v_i64m2_i64m1(
      __riscv_vcompress_vm_i64m2(padd, __riscv_vreinterpret_v_i8m1_b32(vdup_n_s8(85)), 4));
  return __riscv_vadd_vv_i64m1(padd_res, a, 4);
}

FORCE_INLINE uint16x8_t vpadalq_u8(uint16x8_t a, uint8x16_t b) {
  vuint8m1_t b_s = __riscv_vslidedown_vx_u8m1(b, 1, 16);
  vuint16m2_t b_add = __riscv_vwaddu_vv_u16m2(b, b_s, 16);
  vuint16m1_t padd = __riscv_vnsrl_wx_u16m1(__riscv_vreinterpret_v_u16m2_u32m2(b_add), 0, 16);
  return __riscv_vadd_vv_u16m1(padd, a, 16);
}

FORCE_INLINE uint32x4_t vpadalq_u16(uint32x4_t a, uint16x8_t b) {
  vuint16m1_t b_s = __riscv_vslidedown_vx_u16m1(b, 1, 8);
  vuint32m2_t b_add = __riscv_vwaddu_vv_u32m2(b, b_s, 8);
  vuint32m1_t padd = __riscv_vnsrl_wx_u32m1(__riscv_vreinterpret_v_u32m2_u64m2(b_add), 0, 8);
  return __riscv_vadd_vv_u32m1(padd, a, 8);
}

FORCE_INLINE uint64x2_t vpadalq_u32(uint64x2_t a, uint32x4_t b) {
  vuint32m1_t b_s = __riscv_vslidedown_vx_u32m1(b, 1, 4);
  vuint64m2_t padd = __riscv_vwaddu_vv_u64m2(b, b_s, 4);
  vuint64m1_t padd_res = __riscv_vlmul_trunc_v_u64m2_u64m1(
      __riscv_vcompress_vm_u64m2(padd, __riscv_vreinterpret_v_i8m1_b32(vdup_n_s8(85)), 4));
  return __riscv_vadd_vv_u64m1(padd_res, a, 4);
}

FORCE_INLINE int8x8_t vpmax_s8(int8x8_t a, int8x8_t b) {
  vbool8_t mask = __riscv_vreinterpret_v_u8m1_b8(vdup_n_u8(85));
  vint8m1_t ab = __riscv_vslideup_vx_i8m1(a, b, 8, 16);
  vint8m1_t ab_s = __riscv_vslidedown_vx_i8m1(ab, 1, 16);
  vint8m1_t ab_max = __riscv_vmax_vv_i8m1(ab, ab_s, 16);
  return __riscv_vcompress_vm_i8m1(ab_max, mask, 16);
}

FORCE_INLINE int16x4_t vpmax_s16(int16x4_t a, int16x4_t b) {
  vbool16_t mask = __riscv_vreinterpret_v_u16m1_b16(vdup_n_u16(85));
  vint16m1_t ab = __riscv_vslideup_vx_i16m1(a, b, 4, 8);
  vint16m1_t ab_s = __riscv_vslidedown_vx_i16m1(ab, 1, 8);
  vint16m1_t ab_max = __riscv_vmax_vv_i16m1(ab, ab_s, 8);
  return __riscv_vcompress_vm_i16m1(ab_max, mask, 8);
}

FORCE_INLINE int32x2_t vpmax_s32(int32x2_t a, int32x2_t b) {
  vbool32_t mask = __riscv_vreinterpret_v_u32m1_b32(vdup_n_u32(85));
  vint32m1_t ab = __riscv_vslideup_vx_i32m1(a, b, 2, 4);
  vint32m1_t ab_s = __riscv_vslidedown_vx_i32m1(ab, 1, 4);
  vint32m1_t ab_max = __riscv_vmax_vv_i32m1(ab, ab_s, 4);
  return __riscv_vcompress_vm_i32m1(ab_max, mask, 4);
}

FORCE_INLINE float32x2_t vpmax_f32(float32x2_t a, float32x2_t b) {
  vbool32_t mask = __riscv_vreinterpret_v_u32m1_b32(vdup_n_u32(85));
  vfloat32m1_t ab = __riscv_vslideup_vx_f32m1(a, b, 2, 4);
  vfloat32m1_t ab_s = __riscv_vslidedown_vx_f32m1(ab, 1, 4);
  vfloat32m1_t ab_max = __riscv_vfmax_vv_f32m1(ab, ab_s, 4);
  return __riscv_vcompress_vm_f32m1(ab_max, mask, 4);
}

FORCE_INLINE int8x16_t vpmaxq_s8(int8x16_t a, int8x16_t b) {
  vbool4_t mask = __riscv_vreinterpret_v_i8m1_b4(vdupq_n_s8(85));
  vint8m2_t a_m2 = __riscv_vlmul_ext_v_i8m1_i8m2(a);
  vint8m2_t b_m2 = __riscv_vlmul_ext_v_i8m1_i8m2(b);
  vint8m2_t ab = __riscv_vslideup_vx_i8m2(a_m2, b_m2, 16, 32);
  vint8m2_t ab_s = __riscv_vslidedown_vx_i8m2(ab, 1, 32);
  vint8m2_t ab_max = __riscv_vmax_vv_i8m2(ab, ab_s, 32);
  return __riscv_vlmul_trunc_v_i8m2_i8m1(__riscv_vcompress_vm_i8m2(ab_max, mask, 32));
}

FORCE_INLINE int16x8_t vpmaxq_s16(int16x8_t a, int16x8_t b) {
  vbool8_t mask = __riscv_vreinterpret_v_i8m1_b8(vdupq_n_s8(85));
  vint16m2_t a_m2 = __riscv_vlmul_ext_v_i16m1_i16m2(a);
  vint16m2_t b_m2 = __riscv_vlmul_ext_v_i16m1_i16m2(b);
  vint16m2_t ab = __riscv_vslideup_vx_i16m2(a_m2, b_m2, 8, 16);
  vint16m2_t ab_s = __riscv_vslidedown_vx_i16m2(ab, 1, 16);
  vint16m2_t ab_max = __riscv_vmax_vv_i16m2(ab, ab_s, 16);
  return __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vcompress_vm_i16m2(ab_max, mask, 16));
}

FORCE_INLINE int32x4_t vpmaxq_s32(int32x4_t a, int32x4_t b) {
  vbool16_t mask = __riscv_vreinterpret_v_i8m1_b16(vdupq_n_s8(85));
  vint32m2_t a_m2 = __riscv_vlmul_ext_v_i32m1_i32m2(a);
  vint32m2_t b_m2 = __riscv_vlmul_ext_v_i32m1_i32m2(b);
  vint32m2_t ab = __riscv_vslideup_vx_i32m2(a_m2, b_m2, 4, 8);
  vint32m2_t ab_s = __riscv_vslidedown_vx_i32m2(ab, 1, 8);
  vint32m2_t ab_max = __riscv_vmax_vv_i32m2(ab, ab_s, 8);
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vcompress_vm_i32m2(ab_max, mask, 8));
}

FORCE_INLINE uint8x16_t vpmaxq_u8(uint8x16_t a, uint8x16_t b) {
  vbool4_t mask = __riscv_vreinterpret_v_u8m1_b4(vdupq_n_u8(85));
  vuint8m2_t a_m2 = __riscv_vlmul_ext_v_u8m1_u8m2(a);
  vuint8m2_t b_m2 = __riscv_vlmul_ext_v_u8m1_u8m2(b);
  vuint8m2_t ab = __riscv_vslideup_vx_u8m2(a_m2, b_m2, 16, 32);
  vuint8m2_t ab_s = __riscv_vslidedown_vx_u8m2(ab, 1, 32);
  vuint8m2_t ab_max = __riscv_vmaxu_vv_u8m2(ab, ab_s, 32);
  return __riscv_vlmul_trunc_v_u8m2_u8m1(__riscv_vcompress_vm_u8m2(ab_max, mask, 32));
}

FORCE_INLINE uint16x8_t vpmaxq_u16(uint16x8_t a, uint16x8_t b) {
  vbool8_t mask = __riscv_vreinterpret_v_u8m1_b8(vdupq_n_u8(85));
  vuint16m2_t a_m2 = __riscv_vlmul_ext_v_u16m1_u16m2(a);
  vuint16m2_t b_m2 = __riscv_vlmul_ext_v_u16m1_u16m2(b);
  vuint16m2_t ab = __riscv_vslideup_vx_u16m2(a_m2, b_m2, 8, 16);
  vuint16m2_t ab_s = __riscv_vslidedown_vx_u16m2(ab, 1, 16);
  vuint16m2_t ab_max = __riscv_vmaxu_vv_u16m2(ab, ab_s, 16);
  return __riscv_vlmul_trunc_v_u16m2_u16m1(__riscv_vcompress_vm_u16m2(ab_max, mask, 16));
}

FORCE_INLINE uint32x4_t vpmaxq_u32(uint32x4_t a, uint32x4_t b) {
  vbool16_t mask = __riscv_vreinterpret_v_u8m1_b16(vdupq_n_u8(85));
  vuint32m2_t a_m2 = __riscv_vlmul_ext_v_u32m1_u32m2(a);
  vuint32m2_t b_m2 = __riscv_vlmul_ext_v_u32m1_u32m2(b);
  vuint32m2_t ab = __riscv_vslideup_vx_u32m2(a_m2, b_m2, 4, 8);
  vuint32m2_t ab_s = __riscv_vslidedown_vx_u32m2(ab, 1, 8);
  vuint32m2_t ab_max = __riscv_vmaxu_vv_u32m2(ab, ab_s, 8);
  return __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vcompress_vm_u32m2(ab_max, mask, 8));
}

FORCE_INLINE float32x4_t vpmaxq_f32(float32x4_t a, float32x4_t b) {
  vbool16_t mask = __riscv_vreinterpret_v_i8m1_b16(vdupq_n_s8(85));
  vfloat32m2_t a_m2 = __riscv_vlmul_ext_v_f32m1_f32m2(a);
  vfloat32m2_t b_m2 = __riscv_vlmul_ext_v_f32m1_f32m2(b);
  vfloat32m2_t ab = __riscv_vslideup_vx_f32m2(a_m2, b_m2, 4, 8);
  vfloat32m2_t ab_s = __riscv_vslidedown_vx_f32m2(ab, 1, 8);
  vfloat32m2_t ab_max = __riscv_vfmax_vv_f32m2(ab, ab_s, 8);
  return __riscv_vlmul_trunc_v_f32m2_f32m1(__riscv_vcompress_vm_f32m2(ab_max, mask, 8));
}

FORCE_INLINE float64x2_t vpmaxq_f64(float64x2_t a, float64x2_t b) {
  vbool32_t mask = __riscv_vreinterpret_v_i8m1_b32(vdupq_n_s8(85));
  vfloat64m2_t a_m2 = __riscv_vlmul_ext_v_f64m1_f64m2(a);
  vfloat64m2_t b_m2 = __riscv_vlmul_ext_v_f64m1_f64m2(b);
  vfloat64m2_t ab = __riscv_vslideup_vx_f64m2(a_m2, b_m2, 2, 4);
  vfloat64m2_t ab_s = __riscv_vslidedown_vx_f64m2(ab, 1, 4);
  vfloat64m2_t ab_max = __riscv_vfmax_vv_f64m2(ab, ab_s, 4);
  return __riscv_vlmul_trunc_v_f64m2_f64m1(__riscv_vcompress_vm_f64m2(ab_max, mask, 4));
}

FORCE_INLINE uint8x8_t vpmax_u8(uint8x8_t a, uint8x8_t b) {
  vbool8_t mask = __riscv_vreinterpret_v_u8m1_b8(vdup_n_u8(85));
  vuint8m1_t ab = __riscv_vslideup_vx_u8m1(a, b, 8, 16);
  vuint8m1_t ab_s = __riscv_vslidedown_vx_u8m1(ab, 1, 16);
  vuint8m1_t ab_max = __riscv_vmaxu_vv_u8m1(ab, ab_s, 16);
  return __riscv_vcompress_vm_u8m1(ab_max, mask, 16);
}

FORCE_INLINE uint16x4_t vpmax_u16(uint16x4_t a, uint16x4_t b) {
  vbool16_t mask = __riscv_vreinterpret_v_u16m1_b16(vdup_n_u16(85));
  vuint16m1_t ab = __riscv_vslideup_vx_u16m1(a, b, 4, 8);
  vuint16m1_t ab_s = __riscv_vslidedown_vx_u16m1(ab, 1, 8);
  vuint16m1_t ab_max = __riscv_vmaxu_vv_u16m1(ab, ab_s, 8);
  return __riscv_vcompress_vm_u16m1(ab_max, mask, 8);
}

FORCE_INLINE uint32x2_t vpmax_u32(uint32x2_t a, uint32x2_t b) {
  vbool32_t mask = __riscv_vreinterpret_v_u32m1_b32(vdup_n_u32(85));
  vuint32m1_t ab = __riscv_vslideup_vx_u32m1(a, b, 2, 4);
  vuint32m1_t ab_s = __riscv_vslidedown_vx_u32m1(ab, 1, 4);
  vuint32m1_t ab_max = __riscv_vmaxu_vv_u32m1(ab, ab_s, 4);
  return __riscv_vcompress_vm_u32m1(ab_max, mask, 4);
}

FORCE_INLINE int8x8_t vpmin_s8(int8x8_t a, int8x8_t b) {
  vbool8_t mask = __riscv_vreinterpret_v_u8m1_b8(vdup_n_u8(85));
  vint8m1_t ab = __riscv_vslideup_vx_i8m1(a, b, 8, 16);
  vint8m1_t ab_s = __riscv_vslidedown_vx_i8m1(ab, 1, 16);
  vint8m1_t ab_min = __riscv_vmin_vv_i8m1(ab, ab_s, 16);
  return __riscv_vcompress_vm_i8m1(ab_min, mask, 16);
}

FORCE_INLINE int16x4_t vpmin_s16(int16x4_t a, int16x4_t b) {
  vbool16_t mask = __riscv_vreinterpret_v_u16m1_b16(vdup_n_u16(85));
  vint16m1_t ab = __riscv_vslideup_vx_i16m1(a, b, 4, 8);
  vint16m1_t ab_s = __riscv_vslidedown_vx_i16m1(ab, 1, 8);
  vint16m1_t ab_min = __riscv_vmin_vv_i16m1(ab, ab_s, 8);
  return __riscv_vcompress_vm_i16m1(ab_min, mask, 8);
}

FORCE_INLINE int32x2_t vpmin_s32(int32x2_t a, int32x2_t b) {
  vbool32_t mask = __riscv_vreinterpret_v_u32m1_b32(vdup_n_u32(85));
  vint32m1_t ab = __riscv_vslideup_vx_i32m1(a, b, 2, 4);
  vint32m1_t ab_s = __riscv_vslidedown_vx_i32m1(ab, 1, 4);
  vint32m1_t ab_min = __riscv_vmin_vv_i32m1(ab, ab_s, 4);
  return __riscv_vcompress_vm_i32m1(ab_min, mask, 4);
}

FORCE_INLINE float32x2_t vpmin_f32(float32x2_t a, float32x2_t b) {
  vbool32_t mask = __riscv_vreinterpret_v_u32m1_b32(vdup_n_u32(85));
  vfloat32m1_t ab = __riscv_vslideup_vx_f32m1(a, b, 2, 4);
  vfloat32m1_t ab_s = __riscv_vslidedown_vx_f32m1(ab, 1, 4);
  vfloat32m1_t ab_min = __riscv_vfmin_vv_f32m1(ab, ab_s, 4);
  return __riscv_vcompress_vm_f32m1(ab_min, mask, 4);
}

FORCE_INLINE int8x16_t vpminq_s8(int8x16_t a, int8x16_t b) {
  vbool4_t mask = __riscv_vreinterpret_v_i8m1_b4(vdupq_n_s8(85));
  vint8m2_t a_m2 = __riscv_vlmul_ext_v_i8m1_i8m2(a);
  vint8m2_t b_m2 = __riscv_vlmul_ext_v_i8m1_i8m2(b);
  vint8m2_t ab = __riscv_vslideup_vx_i8m2(a_m2, b_m2, 16, 32);
  vint8m2_t ab_s = __riscv_vslidedown_vx_i8m2(ab, 1, 32);
  vint8m2_t ab_min = __riscv_vmin_vv_i8m2(ab, ab_s, 32);
  return __riscv_vlmul_trunc_v_i8m2_i8m1(__riscv_vcompress_vm_i8m2(ab_min, mask, 32));
}

FORCE_INLINE int16x8_t vpminq_s16(int16x8_t a, int16x8_t b) {
  vbool8_t mask = __riscv_vreinterpret_v_i8m1_b8(vdupq_n_s8(85));
  vint16m2_t a_m2 = __riscv_vlmul_ext_v_i16m1_i16m2(a);
  vint16m2_t b_m2 = __riscv_vlmul_ext_v_i16m1_i16m2(b);
  vint16m2_t ab = __riscv_vslideup_vx_i16m2(a_m2, b_m2, 8, 16);
  vint16m2_t ab_s = __riscv_vslidedown_vx_i16m2(ab, 1, 16);
  vint16m2_t ab_min = __riscv_vmin_vv_i16m2(ab, ab_s, 16);
  return __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vcompress_vm_i16m2(ab_min, mask, 16));
}

FORCE_INLINE int32x4_t vpminq_s32(int32x4_t a, int32x4_t b) {
  vbool16_t mask = __riscv_vreinterpret_v_i8m1_b16(vdupq_n_s8(85));
  vint32m2_t a_m2 = __riscv_vlmul_ext_v_i32m1_i32m2(a);
  vint32m2_t b_m2 = __riscv_vlmul_ext_v_i32m1_i32m2(b);
  vint32m2_t ab = __riscv_vslideup_vx_i32m2(a_m2, b_m2, 4, 8);
  vint32m2_t ab_s = __riscv_vslidedown_vx_i32m2(ab, 1, 8);
  vint32m2_t ab_min = __riscv_vmin_vv_i32m2(ab, ab_s, 8);
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vcompress_vm_i32m2(ab_min, mask, 8));
}

FORCE_INLINE uint8x16_t vpminq_u8(uint8x16_t a, uint8x16_t b) {
  vbool4_t mask = __riscv_vreinterpret_v_u8m1_b4(vdupq_n_u8(85));
  vuint8m2_t a_m2 = __riscv_vlmul_ext_v_u8m1_u8m2(a);
  vuint8m2_t b_m2 = __riscv_vlmul_ext_v_u8m1_u8m2(b);
  vuint8m2_t ab = __riscv_vslideup_vx_u8m2(a_m2, b_m2, 16, 32);
  vuint8m2_t ab_s = __riscv_vslidedown_vx_u8m2(ab, 1, 32);
  vuint8m2_t ab_min = __riscv_vminu_vv_u8m2(ab, ab_s, 32);
  return __riscv_vlmul_trunc_v_u8m2_u8m1(__riscv_vcompress_vm_u8m2(ab_min, mask, 32));
}

FORCE_INLINE uint16x8_t vpminq_u16(uint16x8_t a, uint16x8_t b) {
  vbool8_t mask = __riscv_vreinterpret_v_u8m1_b8(vdupq_n_u8(85));
  vuint16m2_t a_m2 = __riscv_vlmul_ext_v_u16m1_u16m2(a);
  vuint16m2_t b_m2 = __riscv_vlmul_ext_v_u16m1_u16m2(b);
  vuint16m2_t ab = __riscv_vslideup_vx_u16m2(a_m2, b_m2, 8, 16);
  vuint16m2_t ab_s = __riscv_vslidedown_vx_u16m2(ab, 1, 16);
  vuint16m2_t ab_min = __riscv_vminu_vv_u16m2(ab, ab_s, 16);
  return __riscv_vlmul_trunc_v_u16m2_u16m1(__riscv_vcompress_vm_u16m2(ab_min, mask, 16));
}

FORCE_INLINE uint32x4_t vpminq_u32(uint32x4_t a, uint32x4_t b) {
  vbool16_t mask = __riscv_vreinterpret_v_u8m1_b16(vdupq_n_u8(85));
  vuint32m2_t a_m2 = __riscv_vlmul_ext_v_u32m1_u32m2(a);
  vuint32m2_t b_m2 = __riscv_vlmul_ext_v_u32m1_u32m2(b);
  vuint32m2_t ab = __riscv_vslideup_vx_u32m2(a_m2, b_m2, 4, 8);
  vuint32m2_t ab_s = __riscv_vslidedown_vx_u32m2(ab, 1, 8);
  vuint32m2_t ab_min = __riscv_vminu_vv_u32m2(ab, ab_s, 8);
  return __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vcompress_vm_u32m2(ab_min, mask, 8));
}

FORCE_INLINE float32x4_t vpminq_f32(float32x4_t a, float32x4_t b) {
  vbool16_t mask = __riscv_vreinterpret_v_i8m1_b16(vdupq_n_s8(85));
  vfloat32m2_t a_m2 = __riscv_vlmul_ext_v_f32m1_f32m2(a);
  vfloat32m2_t b_m2 = __riscv_vlmul_ext_v_f32m1_f32m2(b);
  vfloat32m2_t ab = __riscv_vslideup_vx_f32m2(a_m2, b_m2, 4, 8);
  vfloat32m2_t ab_s = __riscv_vslidedown_vx_f32m2(ab, 1, 8);
  vfloat32m2_t ab_min = __riscv_vfmin_vv_f32m2(ab, ab_s, 8);
  return __riscv_vlmul_trunc_v_f32m2_f32m1(__riscv_vcompress_vm_f32m2(ab_min, mask, 8));
}

FORCE_INLINE float64x2_t vpminq_f64(float64x2_t a, float64x2_t b) {
  vbool32_t mask = __riscv_vreinterpret_v_i8m1_b32(vdupq_n_s8(85));
  vfloat64m2_t a_m2 = __riscv_vlmul_ext_v_f64m1_f64m2(a);
  vfloat64m2_t b_m2 = __riscv_vlmul_ext_v_f64m1_f64m2(b);
  vfloat64m2_t ab = __riscv_vslideup_vx_f64m2(a_m2, b_m2, 2, 4);
  vfloat64m2_t ab_s = __riscv_vslidedown_vx_f64m2(ab, 1, 4);
  vfloat64m2_t ab_min = __riscv_vfmin_vv_f64m2(ab, ab_s, 4);
  return __riscv_vlmul_trunc_v_f64m2_f64m1(__riscv_vcompress_vm_f64m2(ab_min, mask, 4));
}

FORCE_INLINE float32x2_t vpmaxnm_f32(float32x2_t a, float32x2_t b) {
  vbool32_t mask = __riscv_vreinterpret_v_u32m1_b32(vdup_n_u32(85));
  vfloat32m1_t ab = __riscv_vslideup_vx_f32m1(a, b, 2, 4);
  vfloat32m1_t ab_s = __riscv_vslidedown_vx_f32m1(ab, 1, 4);
  vbool32_t ab_non_nan_mask = __riscv_vmfeq_vv_f32m1_b32(ab, ab, 4);
  vbool32_t ab_s_non_nan_mask = __riscv_vmfeq_vv_f32m1_b32(ab_s, ab_s, 4);
  vfloat32m1_t ab_replace = __riscv_vmerge_vvm_f32m1(ab_s, ab, ab_non_nan_mask, 4);
  vfloat32m1_t ab_s_replace = __riscv_vmerge_vvm_f32m1(ab, ab_s, ab_s_non_nan_mask, 4);
  vfloat32m1_t ab_max = __riscv_vfmax_vv_f32m1(ab_replace, ab_s_replace, 4);
  return __riscv_vcompress_vm_f32m1(ab_max, mask, 4);
}

FORCE_INLINE float32x4_t vpmaxnmq_f32(float32x4_t a, float32x4_t b) {
  vbool16_t mask = __riscv_vreinterpret_v_i8m1_b16(vdupq_n_s8(85));
  vfloat32m2_t a_m2 = __riscv_vlmul_ext_v_f32m1_f32m2(a);
  vfloat32m2_t b_m2 = __riscv_vlmul_ext_v_f32m1_f32m2(b);
  vfloat32m2_t ab = __riscv_vslideup_vx_f32m2(a_m2, b_m2, 4, 8);
  vfloat32m2_t ab_s = __riscv_vslidedown_vx_f32m2(ab, 1, 8);
  vbool16_t ab_non_nan_mask = __riscv_vmfeq_vv_f32m2_b16(ab, ab, 8);
  vbool16_t ab_s_non_nan_mask = __riscv_vmfeq_vv_f32m2_b16(ab_s, ab_s, 8);
  vfloat32m2_t ab_replace = __riscv_vmerge_vvm_f32m2(ab_s, ab, ab_non_nan_mask, 8);
  vfloat32m2_t ab_s_replace = __riscv_vmerge_vvm_f32m2(ab, ab_s, ab_s_non_nan_mask, 8);
  vfloat32m2_t ab_max = __riscv_vfmax_vv_f32m2(ab_replace, ab_s_replace, 8);
  return __riscv_vlmul_trunc_v_f32m2_f32m1(__riscv_vcompress_vm_f32m2(ab_max, mask, 8));
}

FORCE_INLINE float64x2_t vpmaxnmq_f64(float64x2_t a, float64x2_t b) {
  vbool32_t mask = __riscv_vreinterpret_v_i8m1_b32(vdupq_n_s8(85));
  vfloat64m2_t a_m2 = __riscv_vlmul_ext_v_f64m1_f64m2(a);
  vfloat64m2_t b_m2 = __riscv_vlmul_ext_v_f64m1_f64m2(b);
  vfloat64m2_t ab = __riscv_vslideup_vx_f64m2(a_m2, b_m2, 2, 4);
  vfloat64m2_t ab_s = __riscv_vslidedown_vx_f64m2(ab, 1, 4);
  vbool32_t ab_non_nan_mask = __riscv_vmfeq_vv_f64m2_b32(ab, ab, 4);
  vbool32_t ab_s_non_nan_mask = __riscv_vmfeq_vv_f64m2_b32(ab_s, ab_s, 4);
  vfloat64m2_t ab_replace = __riscv_vmerge_vvm_f64m2(ab_s, ab, ab_non_nan_mask, 4);
  vfloat64m2_t ab_s_replace = __riscv_vmerge_vvm_f64m2(ab, ab_s, ab_s_non_nan_mask, 4);
  vfloat64m2_t ab_max = __riscv_vfmax_vv_f64m2(ab_replace, ab_s_replace, 4);
  return __riscv_vlmul_trunc_v_f64m2_f64m1(__riscv_vcompress_vm_f64m2(ab_max, mask, 4));
}

FORCE_INLINE float32x2_t vpminnm_f32(float32x2_t a, float32x2_t b) {
  vbool32_t mask = __riscv_vreinterpret_v_u32m1_b32(vdup_n_u32(85));
  vfloat32m1_t ab = __riscv_vslideup_vx_f32m1(a, b, 2, 4);
  vfloat32m1_t ab_s = __riscv_vslidedown_vx_f32m1(ab, 1, 4);
  vbool32_t ab_non_nan_mask = __riscv_vmfeq_vv_f32m1_b32(ab, ab, 4);
  vbool32_t ab_s_non_nan_mask = __riscv_vmfeq_vv_f32m1_b32(ab_s, ab_s, 4);
  vfloat32m1_t ab_replace = __riscv_vmerge_vvm_f32m1(ab_s, ab, ab_non_nan_mask, 4);
  vfloat32m1_t ab_s_replace = __riscv_vmerge_vvm_f32m1(ab, ab_s, ab_s_non_nan_mask, 4);
  vfloat32m1_t ab_max = __riscv_vfmin_vv_f32m1(ab_replace, ab_s_replace, 4);
  return __riscv_vcompress_vm_f32m1(ab_max, mask, 4);
}

FORCE_INLINE float32x4_t vpminnmq_f32(float32x4_t a, float32x4_t b) {
  vbool16_t mask = __riscv_vreinterpret_v_i8m1_b16(vdupq_n_s8(85));
  vfloat32m2_t a_m2 = __riscv_vlmul_ext_v_f32m1_f32m2(a);
  vfloat32m2_t b_m2 = __riscv_vlmul_ext_v_f32m1_f32m2(b);
  vfloat32m2_t ab = __riscv_vslideup_vx_f32m2(a_m2, b_m2, 4, 8);
  vfloat32m2_t ab_s = __riscv_vslidedown_vx_f32m2(ab, 1, 8);
  vbool16_t ab_non_nan_mask = __riscv_vmfeq_vv_f32m2_b16(ab, ab, 8);
  vbool16_t ab_s_non_nan_mask = __riscv_vmfeq_vv_f32m2_b16(ab_s, ab_s, 8);
  vfloat32m2_t ab_replace = __riscv_vmerge_vvm_f32m2(ab_s, ab, ab_non_nan_mask, 8);
  vfloat32m2_t ab_s_replace = __riscv_vmerge_vvm_f32m2(ab, ab_s, ab_s_non_nan_mask, 8);
  vfloat32m2_t ab_max = __riscv_vfmin_vv_f32m2(ab_replace, ab_s_replace, 8);
  return __riscv_vlmul_trunc_v_f32m2_f32m1(__riscv_vcompress_vm_f32m2(ab_max, mask, 8));
}

FORCE_INLINE float64x2_t vpminnmq_f64(float64x2_t a, float64x2_t b) {
  vbool32_t mask = __riscv_vreinterpret_v_i8m1_b32(vdupq_n_s8(85));
  vfloat64m2_t a_m2 = __riscv_vlmul_ext_v_f64m1_f64m2(a);
  vfloat64m2_t b_m2 = __riscv_vlmul_ext_v_f64m1_f64m2(b);
  vfloat64m2_t ab = __riscv_vslideup_vx_f64m2(a_m2, b_m2, 2, 4);
  vfloat64m2_t ab_s = __riscv_vslidedown_vx_f64m2(ab, 1, 4);
  vbool32_t ab_non_nan_mask = __riscv_vmfeq_vv_f64m2_b32(ab, ab, 4);
  vbool32_t ab_s_non_nan_mask = __riscv_vmfeq_vv_f64m2_b32(ab_s, ab_s, 4);
  vfloat64m2_t ab_replace = __riscv_vmerge_vvm_f64m2(ab_s, ab, ab_non_nan_mask, 4);
  vfloat64m2_t ab_s_replace = __riscv_vmerge_vvm_f64m2(ab, ab_s, ab_s_non_nan_mask, 4);
  vfloat64m2_t ab_max = __riscv_vfmin_vv_f64m2(ab_replace, ab_s_replace, 4);
  return __riscv_vlmul_trunc_v_f64m2_f64m1(__riscv_vcompress_vm_f64m2(ab_max, mask, 4));
}

FORCE_INLINE int64_t vpaddd_s64(int64x2_t a) {
  return __riscv_vmv_x_s_i64m1_i64(__riscv_vredsum_vs_i64m1_i64m1(a, __riscv_vmv_v_x_i64m1(0, 2), 2));
}

FORCE_INLINE uint64_t vpaddd_u64(uint64x2_t a) {
  return __riscv_vmv_x_s_u64m1_u64(__riscv_vredsum_vs_u64m1_u64m1(a, __riscv_vmv_v_x_u64m1(0, 2), 2));
}

FORCE_INLINE float32_t vpadds_f32(float32x2_t a) {
  return __riscv_vfmv_f_s_f32m1_f32(__riscv_vfredosum_vs_f32m1_f32m1(a, __riscv_vfmv_v_f_f32m1(0, 2), 2));
}

FORCE_INLINE float64_t vpaddd_f64(float64x2_t a) {
  return __riscv_vfmv_f_s_f64m1_f64(__riscv_vfredosum_vs_f64m1_f64m1(a, __riscv_vfmv_v_f_f64m1(0, 2), 2));
}

FORCE_INLINE float32_t vpmaxs_f32(float32x2_t a) {
  return __riscv_vfmv_f_s_f32m1_f32(__riscv_vfredmax_vs_f32m1_f32m1(a, a, 2));
}

FORCE_INLINE float64_t vpmaxqd_f64(float64x2_t a) {
  return __riscv_vfmv_f_s_f64m1_f64(__riscv_vfredmax_vs_f64m1_f64m1(a, a, 2));
}

FORCE_INLINE float32_t vpmins_f32(float32x2_t a) {
  return __riscv_vfmv_f_s_f32m1_f32(__riscv_vfredmin_vs_f32m1_f32m1(a, a, 2));
}

FORCE_INLINE float64_t vpminqd_f64(float64x2_t a) {
  return __riscv_vfmv_f_s_f64m1_f64(__riscv_vfredmin_vs_f64m1_f64m1(a, a, 2));
}

// FORCE_INLINE float32_t vpmaxnms_f32(float32x2_t a);

// FORCE_INLINE float64_t vpmaxnmqd_f64(float64x2_t a);

// FORCE_INLINE float32_t vpminnms_f32(float32x2_t a);

// FORCE_INLINE float64_t vpminnmqd_f64(float64x2_t a);

FORCE_INLINE int8_t vaddv_s8(int8x8_t a) {
  return __riscv_vmv_x_s_i8m1_i8(__riscv_vredsum_vs_i8m1_i8m1(a, vdup_n_s8(0), 8));
}

FORCE_INLINE int8_t vaddvq_s8(int8x16_t a) {
  return __riscv_vmv_x_s_i8m1_i8(__riscv_vredsum_vs_i8m1_i8m1(a, vdupq_n_s8(0), 16));
}

FORCE_INLINE int16_t vaddv_s16(int16x4_t a) {
  return __riscv_vmv_x_s_i16m1_i16(__riscv_vredsum_vs_i16m1_i16m1(a, vdup_n_s16(0), 4));
}

FORCE_INLINE int16_t vaddvq_s16(int16x8_t a) {
  return __riscv_vmv_x_s_i16m1_i16(__riscv_vredsum_vs_i16m1_i16m1(a, vdupq_n_s16(0), 8));
}

FORCE_INLINE int32_t vaddv_s32(int32x2_t a) {
  return __riscv_vmv_x_s_i32m1_i32(__riscv_vredsum_vs_i32m1_i32m1(a, vdup_n_s32(0), 2));
}

FORCE_INLINE int32_t vaddvq_s32(int32x4_t a) {
  return __riscv_vmv_x_s_i32m1_i32(__riscv_vredsum_vs_i32m1_i32m1(a, vdupq_n_s32(0), 4));
}

FORCE_INLINE int64_t vaddvq_s64(int64x2_t a) {
  return __riscv_vmv_x_s_i64m1_i64(__riscv_vredsum_vs_i64m1_i64m1(a, vdupq_n_s64(0), 2));
}

FORCE_INLINE uint8_t vaddv_u8(uint8x8_t a) {
  return __riscv_vmv_x_s_u8m1_u8(__riscv_vredsum_vs_u8m1_u8m1(a, vdup_n_u8(0), 8));
}

FORCE_INLINE uint8_t vaddvq_u8(uint8x16_t a) {
  return __riscv_vmv_x_s_u8m1_u8(__riscv_vredsum_vs_u8m1_u8m1(a, vdupq_n_u8(0), 16));
}

FORCE_INLINE uint16_t vaddv_u16(uint16x4_t a) {
  return __riscv_vmv_x_s_u16m1_u16(__riscv_vredsum_vs_u16m1_u16m1(a, vdup_n_u16(0), 4));
}

FORCE_INLINE uint16_t vaddvq_u16(uint16x8_t a) {
  return __riscv_vmv_x_s_u16m1_u16(__riscv_vredsum_vs_u16m1_u16m1(a, vdupq_n_u16(0), 8));
}

FORCE_INLINE uint32_t vaddv_u32(uint32x2_t a) {
  return __riscv_vmv_x_s_u32m1_u32(__riscv_vredsum_vs_u32m1_u32m1(a, vdup_n_u32(0), 2));
}

FORCE_INLINE uint32_t vaddvq_u32(uint32x4_t a) {
  return __riscv_vmv_x_s_u32m1_u32(__riscv_vredsum_vs_u32m1_u32m1(a, vdupq_n_u32(0), 4));
}

FORCE_INLINE uint64_t vaddvq_u64(uint64x2_t a) {
  return __riscv_vmv_x_s_u64m1_u64(__riscv_vredsum_vs_u64m1_u64m1(a, vdupq_n_u64(0), 2));
}

FORCE_INLINE float32_t vaddv_f32(float32x2_t a) {
  return __riscv_vfmv_f_s_f32m1_f32(__riscv_vfredosum_vs_f32m1_f32m1(a, __riscv_vfmv_v_f_f32m1(0, 2), 2));
}

FORCE_INLINE float32_t vaddvq_f32(float32x4_t a) {
  return __riscv_vfmv_f_s_f32m1_f32(__riscv_vfredosum_vs_f32m1_f32m1(a, __riscv_vfmv_v_f_f32m1(0, 4), 4));
}

FORCE_INLINE float64_t vaddvq_f64(float64x2_t a) {
  return __riscv_vfmv_f_s_f64m1_f64(__riscv_vfredosum_vs_f64m1_f64m1(a, __riscv_vfmv_v_f_f64m1(0, 2), 2));
}

FORCE_INLINE int16_t vaddlv_s8(int8x8_t a) {
  return __riscv_vmv_x_s_i16m1_i16(__riscv_vwredsum_vs_i8m1_i16m1(a, vdup_n_s16(0), 8));
}

FORCE_INLINE int16_t vaddlvq_s8(int8x16_t a) {
  return __riscv_vmv_x_s_i16m1_i16(__riscv_vwredsum_vs_i8m1_i16m1(a, vdupq_n_s16(0), 16));
}

FORCE_INLINE int32_t vaddlv_s16(int16x4_t a) {
  return __riscv_vmv_x_s_i32m1_i32(__riscv_vwredsum_vs_i16m1_i32m1(a, vdup_n_s32(0), 4));
}

FORCE_INLINE int32_t vaddlvq_s16(int16x8_t a) {
  return __riscv_vmv_x_s_i32m1_i32(__riscv_vwredsum_vs_i16m1_i32m1(a, vdupq_n_s32(0), 8));
}

FORCE_INLINE int64_t vaddlv_s32(int32x2_t a) {
  return __riscv_vmv_x_s_i64m1_i64(__riscv_vwredsum_vs_i32m1_i64m1(a, vdup_n_s64(0), 2));
};

FORCE_INLINE int64_t vaddlvq_s32(int32x4_t a) {
  return __riscv_vmv_x_s_i64m1_i64(__riscv_vwredsum_vs_i32m1_i64m1(a, vdupq_n_s64(0), 4));
};

FORCE_INLINE uint16_t vaddlv_u8(uint8x8_t a) {
  return __riscv_vmv_x_s_u16m1_u16(__riscv_vwredsumu_vs_u8m1_u16m1(a, vdup_n_u16(0), 8));
}

FORCE_INLINE uint16_t vaddlvq_u8(uint8x16_t a) {
  return __riscv_vmv_x_s_u16m1_u16(__riscv_vwredsumu_vs_u8m1_u16m1(a, vdupq_n_u16(0), 16));
}

FORCE_INLINE uint32_t vaddlv_u16(uint16x4_t a) {
  return __riscv_vmv_x_s_u32m1_u32(__riscv_vwredsumu_vs_u16m1_u32m1(a, vdup_n_u32(0), 4));
}

FORCE_INLINE uint32_t vaddlvq_u16(uint16x8_t a) {
  return __riscv_vmv_x_s_u32m1_u32(__riscv_vwredsumu_vs_u16m1_u32m1(a, vdupq_n_u32(0), 8));
}

FORCE_INLINE uint64_t vaddlv_u32(uint32x2_t a) {
  return __riscv_vmv_x_s_u64m1_u64(__riscv_vwredsumu_vs_u32m1_u64m1(a, vdup_n_u64(0), 2));
}

FORCE_INLINE uint64_t vaddlvq_u32(uint32x4_t a) {
  return __riscv_vmv_x_s_u64m1_u64(__riscv_vwredsumu_vs_u32m1_u64m1(a, vdupq_n_u64(0), 4));
}

FORCE_INLINE int8_t vmaxv_s8(int8x8_t a) {
  return __riscv_vmv_x_s_i8m1_i8(__riscv_vredmax_vs_i8m1_i8m1(a, vdup_n_s8(INT8_MIN), 8));
}

FORCE_INLINE int8_t vmaxvq_s8(int8x16_t a) {
  return __riscv_vmv_x_s_i8m1_i8(__riscv_vredmax_vs_i8m1_i8m1(a, vdupq_n_s8(INT8_MIN), 16));
}

FORCE_INLINE int16_t vmaxv_s16(int16x4_t a) {
  return __riscv_vmv_x_s_i16m1_i16(__riscv_vredmax_vs_i16m1_i16m1(a, vdup_n_s16(INT16_MIN), 4));
}

FORCE_INLINE int16_t vmaxvq_s16(int16x8_t a) {
  return __riscv_vmv_x_s_i16m1_i16(__riscv_vredmax_vs_i16m1_i16m1(a, vdupq_n_s16(INT16_MIN), 8));
}

FORCE_INLINE int32_t vmaxv_s32(int32x2_t a) {
  return __riscv_vmv_x_s_i32m1_i32(__riscv_vredmax_vs_i32m1_i32m1(a, vdup_n_s32(INT32_MIN), 2));
}

FORCE_INLINE int32_t vmaxvq_s32(int32x4_t a) {
  return __riscv_vmv_x_s_i32m1_i32(__riscv_vredmax_vs_i32m1_i32m1(a, vdupq_n_s32(INT32_MIN), 4));
}

FORCE_INLINE uint8_t vmaxv_u8(uint8x8_t a) {
  return __riscv_vmv_x_s_u8m1_u8(__riscv_vredmaxu_vs_u8m1_u8m1(a, vdup_n_u8(0), 8));
}

FORCE_INLINE uint8_t vmaxvq_u8(uint8x16_t a) {
  return __riscv_vmv_x_s_u8m1_u8(__riscv_vredmaxu_vs_u8m1_u8m1(a, vdupq_n_u8(0), 16));
}

FORCE_INLINE uint16_t vmaxv_u16(uint16x4_t a) {
  return __riscv_vmv_x_s_u16m1_u16(__riscv_vredmaxu_vs_u16m1_u16m1(a, vdup_n_u16(0), 4));
}

FORCE_INLINE uint16_t vmaxvq_u16(uint16x8_t a) {
  return __riscv_vmv_x_s_u16m1_u16(__riscv_vredmaxu_vs_u16m1_u16m1(a, vdupq_n_u16(0), 8));
}

FORCE_INLINE uint32_t vmaxv_u32(uint32x2_t a) {
  return __riscv_vmv_x_s_u32m1_u32(__riscv_vredmaxu_vs_u32m1_u32m1(a, vdup_n_u32(0), 2));
}

FORCE_INLINE uint32_t vmaxvq_u32(uint32x4_t a) {
  return __riscv_vmv_x_s_u32m1_u32(__riscv_vredmaxu_vs_u32m1_u32m1(a, vdupq_n_u32(0), 4));
}

FORCE_INLINE float32_t vmaxv_f32(float32x2_t a) {
  return __riscv_vfmv_f_s_f32m1_f32(__riscv_vfredmax_vs_f32m1_f32m1(a, __riscv_vfmv_v_f_f32m1(-FLT_MAX, 2), 2));
}

FORCE_INLINE float32_t vmaxvq_f32(float32x4_t a) {
  uint8_t mask = __riscv_vmv_x_s_u8m1_u8(__riscv_vreinterpret_v_b32_u8m1(__riscv_vmfeq_vv_f32m1_b32(a, a, 4)));
  if ((mask & 0b1111) != 0b1111) {
    return NAN;
  }
  return __riscv_vfmv_f_s_f32m1_f32(__riscv_vfredmax_vs_f32m1_f32m1(a, __riscv_vfmv_v_f_f32m1(-FLT_MAX, 4), 4));
}

FORCE_INLINE float64_t vmaxvq_f64(float64x2_t a) {
  uint8_t mask = __riscv_vmv_x_s_u8m1_u8(__riscv_vreinterpret_v_b64_u8m1(__riscv_vmfeq_vv_f64m1_b64(a, a, 2)));
  if ((mask & 0b11) != 0b11) {
    return NAN;
  }
  return __riscv_vfmv_f_s_f64m1_f64(__riscv_vfredmax_vs_f64m1_f64m1(a, __riscv_vfmv_v_f_f64m1(-DBL_MAX, 2), 2));
}

FORCE_INLINE int8_t vminv_s8(int8x8_t a) {
  return __riscv_vmv_x_s_i8m1_i8(__riscv_vredmin_vs_i8m1_i8m1(a, vdup_n_s8(INT8_MAX), 8));
}

FORCE_INLINE int8_t vminvq_s8(int8x16_t a) {
  return __riscv_vmv_x_s_i8m1_i8(__riscv_vredmin_vs_i8m1_i8m1(a, vdupq_n_s8(INT8_MAX), 16));
}

FORCE_INLINE int16_t vminv_s16(int16x4_t a) {
  return __riscv_vmv_x_s_i16m1_i16(__riscv_vredmin_vs_i16m1_i16m1(a, vdup_n_s16(INT16_MAX), 4));
}

FORCE_INLINE int16_t vminvq_s16(int16x8_t a) {
  return __riscv_vmv_x_s_i16m1_i16(__riscv_vredmin_vs_i16m1_i16m1(a, vdupq_n_s16(INT16_MAX), 8));
}

FORCE_INLINE int32_t vminv_s32(int32x2_t a) {
  return __riscv_vmv_x_s_i32m1_i32(__riscv_vredmin_vs_i32m1_i32m1(a, vdup_n_s32(INT32_MAX), 2));
}

FORCE_INLINE int32_t vminvq_s32(int32x4_t a) {
  return __riscv_vmv_x_s_i32m1_i32(__riscv_vredmin_vs_i32m1_i32m1(a, vdupq_n_s32(INT32_MAX), 4));
}

FORCE_INLINE uint8_t vminv_u8(uint8x8_t a) {
  return __riscv_vmv_x_s_u8m1_u8(__riscv_vredminu_vs_u8m1_u8m1(a, vdup_n_u8(UINT8_MAX), 8));
}

FORCE_INLINE uint8_t vminvq_u8(uint8x16_t a) {
  return __riscv_vmv_x_s_u8m1_u8(__riscv_vredminu_vs_u8m1_u8m1(a, vdupq_n_u8(UINT8_MAX), 16));
}

FORCE_INLINE uint16_t vminv_u16(uint16x4_t a) {
  return __riscv_vmv_x_s_u16m1_u16(__riscv_vredminu_vs_u16m1_u16m1(a, vdup_n_u16(UINT16_MAX), 4));
}

FORCE_INLINE uint16_t vminvq_u16(uint16x8_t a) {
  return __riscv_vmv_x_s_u16m1_u16(__riscv_vredminu_vs_u16m1_u16m1(a, vdupq_n_u16(UINT16_MAX), 8));
}

FORCE_INLINE uint32_t vminv_u32(uint32x2_t a) {
  return __riscv_vmv_x_s_u32m1_u32(__riscv_vredminu_vs_u32m1_u32m1(a, vdup_n_u32(UINT32_MAX), 2));
}

FORCE_INLINE uint32_t vminvq_u32(uint32x4_t a) {
  return __riscv_vmv_x_s_u32m1_u32(__riscv_vredminu_vs_u32m1_u32m1(a, vdupq_n_u32(UINT32_MAX), 4));
}

FORCE_INLINE float32_t vminv_f32(float32x2_t a) {
  return __riscv_vfmv_f_s_f32m1_f32(__riscv_vfredmin_vs_f32m1_f32m1(a, __riscv_vfmv_v_f_f32m1(FLT_MAX, 2), 2));
}

FORCE_INLINE float32_t vminvq_f32(float32x4_t a) {
  uint8_t mask = __riscv_vmv_x_s_u8m1_u8(__riscv_vreinterpret_v_b32_u8m1(__riscv_vmfeq_vv_f32m1_b32(a, a, 4)));
  if ((mask & 0b1111) != 0b1111) {
    return NAN;
  }
  return __riscv_vfmv_f_s_f32m1_f32(__riscv_vfredmin_vs_f32m1_f32m1(a, __riscv_vfmv_v_f_f32m1(FLT_MAX, 4), 4));
}

FORCE_INLINE float64_t vminvq_f64(float64x2_t a) {
  uint8_t mask = __riscv_vmv_x_s_u8m1_u8(__riscv_vreinterpret_v_b64_u8m1(__riscv_vmfeq_vv_f64m1_b64(a, a, 2)));
  if ((mask & 0b11) != 0b11) {
    return NAN;
  }
  return __riscv_vfmv_f_s_f64m1_f64(__riscv_vfredmin_vs_f64m1_f64m1(a, __riscv_vfmv_v_f_f64m1(DBL_MAX, 2), 2));
}

// FORCE_INLINE float32_t vmaxnmv_f32(float32x2_t a);

// FORCE_INLINE float32_t vmaxnmvq_f32(float32x4_t a);

// FORCE_INLINE float64_t vmaxnmvq_f64(float64x2_t a);

// FORCE_INLINE float32_t vminnmv_f32(float32x2_t a);

// FORCE_INLINE float32_t vminnmvq_f32(float32x4_t a);

// FORCE_INLINE float64_t vminnmvq_f64(float64x2_t a);

FORCE_INLINE uint8x8_t vpmin_u8(uint8x8_t a, uint8x8_t b) {
  vbool8_t mask = __riscv_vreinterpret_v_u8m1_b8(vdup_n_u8(85));
  vuint8m1_t ab = __riscv_vslideup_vx_u8m1(a, b, 8, 16);
  vuint8m1_t ab_s = __riscv_vslidedown_vx_u8m1(ab, 1, 16);
  vuint8m1_t ab_min = __riscv_vminu_vv_u8m1(ab, ab_s, 16);
  return __riscv_vcompress_vm_u8m1(ab_min, mask, 16);
}

FORCE_INLINE uint16x4_t vpmin_u16(uint16x4_t a, uint16x4_t b) {
  vbool16_t mask = __riscv_vreinterpret_v_u16m1_b16(vdup_n_u16(85));
  vuint16m1_t ab = __riscv_vslideup_vx_u16m1(a, b, 4, 8);
  vuint16m1_t ab_s = __riscv_vslidedown_vx_u16m1(ab, 1, 8);
  vuint16m1_t ab_min = __riscv_vminu_vv_u16m1(ab, ab_s, 8);
  return __riscv_vcompress_vm_u16m1(ab_min, mask, 8);
}

FORCE_INLINE uint32x2_t vpmin_u32(uint32x2_t a, uint32x2_t b) {
  vbool32_t mask = __riscv_vreinterpret_v_u32m1_b32(vdup_n_u32(85));
  vuint32m1_t ab = __riscv_vslideup_vx_u32m1(a, b, 2, 4);
  vuint32m1_t ab_s = __riscv_vslidedown_vx_u32m1(ab, 1, 4);
  vuint32m1_t ab_min = __riscv_vminu_vv_u32m1(ab, ab_s, 4);
  return __riscv_vcompress_vm_u32m1(ab_min, mask, 4);
}

FORCE_INLINE float32x2_t vrecps_f32(float32x2_t a, float32x2_t b) {
  return __riscv_vfnmsac_vv_f32m1(vdup_n_f32(2.0), a, b, 2);
}

FORCE_INLINE float32x4_t vrecpsq_f32(float32x4_t a, float32x4_t b) {
  return __riscv_vfnmsac_vv_f32m1(vdupq_n_f32(2.0), a, b, 4);
}

FORCE_INLINE float64x1_t vrecps_f64(float64x1_t a, float64x1_t b) {
  return __riscv_vfnmsac_vv_f64m1(vdup_n_f64(2.0), a, b, 1);
}

FORCE_INLINE float64x2_t vrecpsq_f64(float64x2_t a, float64x2_t b) {
  return __riscv_vfnmsac_vv_f64m1(vdupq_n_f64(2.0), a, b, 2);
}

FORCE_INLINE float32_t vrecpss_f32(float32_t a, float32_t b) { return 2.0 - a * b; }

FORCE_INLINE float64_t vrecpsd_f64(float64_t a, float64_t b) { return 2.0 - a * b; }

FORCE_INLINE float32x2_t vsqrt_f32(float32x2_t a) { return __riscv_vfsqrt_v_f32m1(a, 2); }

FORCE_INLINE float32x4_t vsqrtq_f32(float32x4_t a) { return __riscv_vfsqrt_v_f32m1(a, 4); }

FORCE_INLINE float64x1_t vsqrt_f64(float64x1_t a) { return __riscv_vfsqrt_v_f64m1(a, 1); }

FORCE_INLINE float64x2_t vsqrtq_f64(float64x2_t a) { return __riscv_vfsqrt_v_f64m1(a, 2); }

FORCE_INLINE float32x2_t vrsqrts_f32(float32x2_t a, float32x2_t b) {
  return __riscv_vfdiv_vf_f32m1(__riscv_vfnmsac_vv_f32m1(vdup_n_f32(3.0), a, b, 2), 2.0, 2);
}

FORCE_INLINE float32x4_t vrsqrtsq_f32(float32x4_t a, float32x4_t b) {
  return __riscv_vfdiv_vf_f32m1(__riscv_vfnmsac_vv_f32m1(vdupq_n_f32(3.0), a, b, 4), 2.0, 4);
}

FORCE_INLINE float64x1_t vrsqrts_f64(float64x1_t a, float64x1_t b) {
  return __riscv_vfdiv_vf_f64m1(__riscv_vfnmsac_vv_f64m1(vdup_n_f64(3.0), a, b, 1), 2.0, 1);
}

FORCE_INLINE float64x2_t vrsqrtsq_f64(float64x2_t a, float64x2_t b) {
  return __riscv_vfdiv_vf_f64m1(__riscv_vfnmsac_vv_f64m1(vdupq_n_f64(3.0), a, b, 2), 2.0, 2);
}

FORCE_INLINE float32_t vrsqrtss_f32(float32_t a, float32_t b) { return (3.0 - a * b) / 2.0; }

FORCE_INLINE float64_t vrsqrtsd_f64(float64_t a, float64_t b) { return (3.0 - a * b) / 2.0; }

FORCE_INLINE int8x8_t vshl_s8(int8x8_t a, int8x8_t b) {
  // implementation only works within defined range 'b' in [0, 7]
  vbool8_t positive_mask = __riscv_vmsgt_vx_i8m1_b8(b, 0, 8);
  vint8m1_t shl = __riscv_vsll_vv_i8m1(a, __riscv_vreinterpret_v_i8m1_u8m1(b), 8);
  vint16m2_t a_ext = __riscv_vsext_vf2_i16m2(a, 8);
  vint8m1_t b_neg = __riscv_vneg_v_i8m1(b, 8);
  vint8m1_t shr = __riscv_vnclip_wv_i8m1(a_ext, __riscv_vreinterpret_v_i8m1_u8m1(b_neg), __RISCV_VXRM_RDN, 8);
  return __riscv_vmerge_vvm_i8m1(shr, shl, positive_mask, 8);
}

FORCE_INLINE int16x4_t vshl_s16(int16x4_t a, int16x4_t b) {
  // implementation only works within defined range 'b' in [0, 15]
  vbool16_t positive_mask = __riscv_vmsgt_vx_i16m1_b16(b, 0, 4);
  vint16m1_t shl = __riscv_vsll_vv_i16m1(a, __riscv_vreinterpret_v_i16m1_u16m1(b), 4);
  vint32m2_t a_ext = __riscv_vsext_vf2_i32m2(a, 4);
  vint16m1_t b_neg = __riscv_vneg_v_i16m1(b, 4);
  vint16m1_t shr = __riscv_vnclip_wv_i16m1(a_ext, __riscv_vreinterpret_v_i16m1_u16m1(b_neg), __RISCV_VXRM_RDN, 4);
  return __riscv_vmerge_vvm_i16m1(shr, shl, positive_mask, 4);
}

FORCE_INLINE int32x2_t vshl_s32(int32x2_t a, int32x2_t b) {
  // implementation only works within defined range 'b' in [0, 31]
  vbool32_t positive_mask = __riscv_vmsgt_vx_i32m1_b32(b, 0, 2);
  vint32m1_t shl = __riscv_vsll_vv_i32m1(a, __riscv_vreinterpret_v_i32m1_u32m1(b), 2);
  vint64m2_t a_ext = __riscv_vsext_vf2_i64m2(a, 2);
  vint32m1_t b_neg = __riscv_vneg_v_i32m1(b, 2);
  vint32m1_t shr = __riscv_vnclip_wv_i32m1(a_ext, __riscv_vreinterpret_v_i32m1_u32m1(b_neg), __RISCV_VXRM_RDN, 2);
  return __riscv_vmerge_vvm_i32m1(shr, shl, positive_mask, 2);
}

FORCE_INLINE int64x1_t vshl_s64(int64x1_t a, int64x1_t b) {
  // implementation only works within defined range 'b' in [0, 63]
  vbool64_t positive_mask = __riscv_vmsgt_vx_i64m1_b64(b, 0, 1);
  vint64m1_t shl = __riscv_vsll_vv_i64m1(a, __riscv_vreinterpret_v_i64m1_u64m1(b), 1);
  vint64m1_t b_neg = __riscv_vneg_v_i64m1(b, 1);
  vint64m1_t shr = __riscv_vsra_vv_i64m1(a, __riscv_vreinterpret_v_i64m1_u64m1(b_neg), 1);
  return __riscv_vmerge_vvm_i64m1(shr, shl, positive_mask, 1);
}

FORCE_INLINE uint8x8_t vshl_u8(uint8x8_t a, int8x8_t b) {
  // implementation only works within defined range 'b' in [0, 7]
  vbool8_t positive_mask = __riscv_vmsgt_vx_i8m1_b8(b, 0, 8);
  vuint8m1_t shl = __riscv_vsll_vv_u8m1(a, __riscv_vreinterpret_v_i8m1_u8m1(b), 8);
  vuint16m2_t a_ext = __riscv_vzext_vf2_u16m2(a, 8);
  vint8m1_t b_neg = __riscv_vneg_v_i8m1(b, 8);
  vuint8m1_t shr = __riscv_vnclipu_wv_u8m1(a_ext, __riscv_vreinterpret_v_i8m1_u8m1(b_neg), __RISCV_VXRM_RDN, 8);
  return __riscv_vmerge_vvm_u8m1(shr, shl, positive_mask, 8);
}

FORCE_INLINE uint16x4_t vshl_u16(uint16x4_t a, int16x4_t b) {
  // implementation only works within defined range 'b' in [0, 15]
  vbool16_t positive_mask = __riscv_vmsgt_vx_i16m1_b16(b, 0, 4);
  vuint16m1_t shl = __riscv_vsll_vv_u16m1(a, __riscv_vreinterpret_v_i16m1_u16m1(b), 4);
  vuint32m2_t a_ext = __riscv_vzext_vf2_u32m2(a, 4);
  vint16m1_t b_neg = __riscv_vneg_v_i16m1(b, 4);
  vuint16m1_t shr = __riscv_vnclipu_wv_u16m1(a_ext, __riscv_vreinterpret_v_i16m1_u16m1(b_neg), __RISCV_VXRM_RDN, 4);
  return __riscv_vmerge_vvm_u16m1(shr, shl, positive_mask, 4);
}

FORCE_INLINE uint32x2_t vshl_u32(uint32x2_t a, int32x2_t b) {
  // implementation only works within defined range 'b' in [0, 31]
  vbool32_t positive_mask = __riscv_vmsgt_vx_i32m1_b32(b, 0, 2);
  vuint32m1_t shl = __riscv_vsll_vv_u32m1(a, __riscv_vreinterpret_v_i32m1_u32m1(b), 2);
  vuint64m2_t a_ext = __riscv_vzext_vf2_u64m2(a, 2);
  vint32m1_t b_neg = __riscv_vneg_v_i32m1(b, 2);
  vuint32m1_t shr = __riscv_vnclipu_wv_u32m1(a_ext, __riscv_vreinterpret_v_i32m1_u32m1(b_neg), __RISCV_VXRM_RDN, 2);
  return __riscv_vmerge_vvm_u32m1(shr, shl, positive_mask, 2);
}

FORCE_INLINE uint64x1_t vshl_u64(uint64x1_t a, int64x1_t b) {
  // implementation only works within defined range 'b' in [0, 63]
  vbool64_t positive_mask = __riscv_vmsgt_vx_i64m1_b64(b, 0, 1);
  vuint64m1_t shl = __riscv_vsll_vv_u64m1(a, __riscv_vreinterpret_v_i64m1_u64m1(b), 1);
  vint64m1_t b_neg = __riscv_vneg_v_i64m1(b, 1);
  vuint64m1_t shr = __riscv_vsrl_vv_u64m1(a, __riscv_vreinterpret_v_i64m1_u64m1(b_neg), 1);
  return __riscv_vmerge_vvm_u64m1(shr, shl, positive_mask, 1);
}

FORCE_INLINE int8x16_t vshlq_s8(int8x16_t a, int8x16_t b) {
  // implementation only works within defined range 'b' in [0, 7]
  vbool8_t positive_mask = __riscv_vmsgt_vx_i8m1_b8(b, 0, 16);
  vint8m1_t shl = __riscv_vsll_vv_i8m1(a, __riscv_vreinterpret_v_i8m1_u8m1(b), 16);
  vint16m2_t a_ext = __riscv_vsext_vf2_i16m2(a, 16);
  vint8m1_t b_neg = __riscv_vneg_v_i8m1(b, 16);
  vint8m1_t shr = __riscv_vnclip_wv_i8m1(a_ext, __riscv_vreinterpret_v_i8m1_u8m1(b_neg), __RISCV_VXRM_RDN, 16);
  return __riscv_vmerge_vvm_i8m1(shr, shl, positive_mask, 16);
}

FORCE_INLINE int16x8_t vshlq_s16(int16x8_t a, int16x8_t b) {
  // implementation only works within defined range 'b' in [0, 15]
  vbool16_t positive_mask = __riscv_vmsgt_vx_i16m1_b16(b, 0, 8);
  vint16m1_t shl = __riscv_vsll_vv_i16m1(a, __riscv_vreinterpret_v_i16m1_u16m1(b), 8);
  vint32m2_t a_ext = __riscv_vsext_vf2_i32m2(a, 8);
  vint16m1_t b_neg = __riscv_vneg_v_i16m1(b, 8);
  vint16m1_t shr = __riscv_vnclip_wv_i16m1(a_ext, __riscv_vreinterpret_v_i16m1_u16m1(b_neg), __RISCV_VXRM_RDN, 8);
  return __riscv_vmerge_vvm_i16m1(shr, shl, positive_mask, 8);
}

FORCE_INLINE int32x4_t vshlq_s32(int32x4_t a, int32x4_t b) {
  // implementation only works within defined range 'b' in [0, 31]
  vbool32_t positive_mask = __riscv_vmsgt_vx_i32m1_b32(b, 0, 4);
  vint32m1_t shl = __riscv_vsll_vv_i32m1(a, __riscv_vreinterpret_v_i32m1_u32m1(b), 4);
  vint64m2_t a_ext = __riscv_vsext_vf2_i64m2(a, 4);
  vint32m1_t b_neg = __riscv_vneg_v_i32m1(b, 4);
  vint32m1_t shr = __riscv_vnclip_wv_i32m1(a_ext, __riscv_vreinterpret_v_i32m1_u32m1(b_neg), __RISCV_VXRM_RDN, 4);
  return __riscv_vmerge_vvm_i32m1(shr, shl, positive_mask, 4);
}

FORCE_INLINE int64x2_t vshlq_s64(int64x2_t a, int64x2_t b) {
  // implementation only works within defined range 'b' in [0, 63]
  vbool64_t positive_mask = __riscv_vmsgt_vx_i64m1_b64(b, 0, 2);
  vint64m1_t shl = __riscv_vsll_vv_i64m1(a, __riscv_vreinterpret_v_i64m1_u64m1(b), 2);
  vint64m1_t b_neg = __riscv_vneg_v_i64m1(b, 2);
  vint64m1_t shr = __riscv_vsra_vv_i64m1(a, __riscv_vreinterpret_v_i64m1_u64m1(b_neg), 2);
  return __riscv_vmerge_vvm_i64m1(shr, shl, positive_mask, 2);
}

FORCE_INLINE uint8x16_t vshlq_u8(uint8x16_t a, int8x16_t b) {
  // implementation only works within defined range 'b' in [0, 7]
  vbool8_t positive_mask = __riscv_vmsgt_vx_i8m1_b8(b, 0, 16);
  vuint8m1_t shl = __riscv_vsll_vv_u8m1(a, __riscv_vreinterpret_v_i8m1_u8m1(b), 16);
  vuint16m2_t a_ext = __riscv_vzext_vf2_u16m2(a, 16);
  vint8m1_t b_neg = __riscv_vneg_v_i8m1(b, 16);
  vuint8m1_t shr = __riscv_vnclipu_wv_u8m1(a_ext, __riscv_vreinterpret_v_i8m1_u8m1(b_neg), __RISCV_VXRM_RDN, 16);
  return __riscv_vmerge_vvm_u8m1(shr, shl, positive_mask, 16);
}

FORCE_INLINE uint16x8_t vshlq_u16(uint16x8_t a, int16x8_t b) {
  // implementation only works within defined range 'b' in [0, 15]
  vbool16_t positive_mask = __riscv_vmsgt_vx_i16m1_b16(b, 0, 8);
  vuint16m1_t shl = __riscv_vsll_vv_u16m1(a, __riscv_vreinterpret_v_i16m1_u16m1(b), 8);
  vuint32m2_t a_ext = __riscv_vzext_vf2_u32m2(a, 8);
  vint16m1_t b_neg = __riscv_vneg_v_i16m1(b, 8);
  vuint16m1_t shr = __riscv_vnclipu_wv_u16m1(a_ext, __riscv_vreinterpret_v_i16m1_u16m1(b_neg), __RISCV_VXRM_RDN, 8);
  return __riscv_vmerge_vvm_u16m1(shr, shl, positive_mask, 8);
}

FORCE_INLINE uint32x4_t vshlq_u32(uint32x4_t a, int32x4_t b) {
  // implementation only works within defined range 'b' in [0, 31]
  vbool32_t positive_mask = __riscv_vmsgt_vx_i32m1_b32(b, 0, 4);
  vuint32m1_t shl = __riscv_vsll_vv_u32m1(a, __riscv_vreinterpret_v_i32m1_u32m1(b), 4);
  vuint64m2_t a_ext = __riscv_vzext_vf2_u64m2(a, 4);
  vint32m1_t b_neg = __riscv_vneg_v_i32m1(b, 4);
  vuint32m1_t shr = __riscv_vnclipu_wv_u32m1(a_ext, __riscv_vreinterpret_v_i32m1_u32m1(b_neg), __RISCV_VXRM_RDN, 4);
  return __riscv_vmerge_vvm_u32m1(shr, shl, positive_mask, 4);
}

FORCE_INLINE uint64x2_t vshlq_u64(uint64x2_t a, int64x2_t b) {
  // implementation only works within defined range 'b' in [0, 63]
  vbool64_t positive_mask = __riscv_vmsgt_vx_i64m1_b64(b, 0, 2);
  vuint64m1_t shl = __riscv_vsll_vv_u64m1(a, __riscv_vreinterpret_v_i64m1_u64m1(b), 2);
  vint64m1_t b_neg = __riscv_vneg_v_i64m1(b, 2);
  vuint64m1_t shr = __riscv_vsrl_vv_u64m1(a, __riscv_vreinterpret_v_i64m1_u64m1(b_neg), 2);
  return __riscv_vmerge_vvm_u64m1(shr, shl, positive_mask, 2);
}

FORCE_INLINE int64_t vshld_s64(int64_t a, int64_t b) {
  if (b < 0) {
    return a >> -b;
  } else {
    return a << b;
  }
}

FORCE_INLINE uint64_t vshld_u64(uint64_t a, int64_t b) {
  if (b < 0) {
    return a >> -b;
  } else {
    return a << b;
  }
}

FORCE_INLINE int8x8_t vrshl_s8(int8x8_t a, int8x8_t b) {
  vbool8_t positive_mask = __riscv_vmsgt_vx_i8m1_b8(b, 0, 8);
  vint8m1_t shl = __riscv_vsll_vv_i8m1(a, __riscv_vreinterpret_v_i8m1_u8m1(b), 8);
  vint16m2_t a_ext = __riscv_vsext_vf2_i16m2(a, 8);
  vint8m1_t b_neg = __riscv_vneg_v_i8m1(b, 8);
  vint8m1_t shr = __riscv_vnclip_wv_i8m1(a_ext, __riscv_vreinterpret_v_i8m1_u8m1(b_neg), __RISCV_VXRM_RNU, 8);
  return __riscv_vmerge_vvm_i8m1(shr, shl, positive_mask, 8);
}

FORCE_INLINE int16x4_t vrshl_s16(int16x4_t a, int16x4_t b) {
  vbool16_t positive_mask = __riscv_vmsgt_vx_i16m1_b16(b, 0, 4);
  vint16m1_t shl = __riscv_vsll_vv_i16m1(a, __riscv_vreinterpret_v_i16m1_u16m1(b), 4);
  vint32m2_t a_ext = __riscv_vsext_vf2_i32m2(a, 4);
  vint16m1_t b_neg = __riscv_vneg_v_i16m1(b, 4);
  vint16m1_t shr = __riscv_vnclip_wv_i16m1(a_ext, __riscv_vreinterpret_v_i16m1_u16m1(b_neg), __RISCV_VXRM_RNU, 4);
  return __riscv_vmerge_vvm_i16m1(shr, shl, positive_mask, 4);
}

FORCE_INLINE int32x2_t vrshl_s32(int32x2_t a, int32x2_t b) {
  vbool32_t positive_mask = __riscv_vmsgt_vx_i32m1_b32(b, 0, 2);
  vint32m1_t shl = __riscv_vsll_vv_i32m1(a, __riscv_vreinterpret_v_i32m1_u32m1(b), 2);
  vint64m2_t a_ext = __riscv_vsext_vf2_i64m2(a, 2);
  vint32m1_t b_neg = __riscv_vneg_v_i32m1(b, 2);
  vint32m1_t shr = __riscv_vnclip_wv_i32m1(a_ext, __riscv_vreinterpret_v_i32m1_u32m1(b_neg), __RISCV_VXRM_RNU, 2);
  return __riscv_vmerge_vvm_i32m1(shr, shl, positive_mask, 2);
}

FORCE_INLINE int64x1_t vrshl_s64(int64x1_t a, int64x1_t b) {
  // implementation only works within defined range 'b' in [0, 63]
  vbool64_t non_neg_mask = __riscv_vmsge_vx_i64m1_b64(b, 0, 1);
  vint64m1_t shl = __riscv_vsll_vv_i64m1(a, __riscv_vreinterpret_v_i64m1_u64m1(b), 1);
  vint64m1_t b_neg = __riscv_vneg_v_i64m1(b, 1);
  vint64m1_t round_const = __riscv_vsll_vv_i64m1(
      vdup_n_s64(1), __riscv_vreinterpret_v_i64m1_u64m1(__riscv_vsub_vx_i64m1(__riscv_vneg_v_i64m1(b, 1), 1, 1)), 1);
  vint64m1_t a_round = __riscv_vadd_vv_i64m1(a, round_const, 1);
  vint64m1_t shr = __riscv_vsra_vv_i64m1((a_round), __riscv_vreinterpret_v_i64m1_u64m1(b_neg), 1);
  return __riscv_vmerge_vvm_i64m1(shr, shl, non_neg_mask, 1);
}

FORCE_INLINE uint8x8_t vrshl_u8(uint8x8_t a, int8x8_t b) {
  // implementation only works within defined range 'b' in [0, 7]
  vbool8_t positive_mask = __riscv_vmsgt_vx_i8m1_b8(b, 0, 8);
  vuint8m1_t shl = __riscv_vsll_vv_u8m1(a, __riscv_vreinterpret_v_i8m1_u8m1(b), 8);
  vuint16m2_t a_ext = __riscv_vzext_vf2_u16m2(a, 8);
  vint8m1_t b_neg = __riscv_vneg_v_i8m1(b, 8);
  vuint8m1_t shr = __riscv_vnclipu_wv_u8m1(a_ext, __riscv_vreinterpret_v_i8m1_u8m1(b_neg), __RISCV_VXRM_RNU, 8);
  return __riscv_vmerge_vvm_u8m1(shr, shl, positive_mask, 8);
}

FORCE_INLINE uint16x4_t vrshl_u16(uint16x4_t a, int16x4_t b) {
  // implementation only works within defined range 'b' in [0, 15]
  vbool16_t positive_mask = __riscv_vmsgt_vx_i16m1_b16(b, 0, 4);
  vuint16m1_t shl = __riscv_vsll_vv_u16m1(a, __riscv_vreinterpret_v_i16m1_u16m1(b), 4);
  vuint32m2_t a_ext = __riscv_vzext_vf2_u32m2(a, 4);
  vint16m1_t b_neg = __riscv_vneg_v_i16m1(b, 4);
  vuint16m1_t shr = __riscv_vnclipu_wv_u16m1(a_ext, __riscv_vreinterpret_v_i16m1_u16m1(b_neg), __RISCV_VXRM_RNU, 4);
  return __riscv_vmerge_vvm_u16m1(shr, shl, positive_mask, 4);
}

FORCE_INLINE uint32x2_t vrshl_u32(uint32x2_t a, int32x2_t b) {
  // implementation only works within defined range 'b' in [0, 31]
  vbool32_t positive_mask = __riscv_vmsgt_vx_i32m1_b32(b, 0, 2);
  vuint32m1_t shl = __riscv_vsll_vv_u32m1(a, __riscv_vreinterpret_v_i32m1_u32m1(b), 2);
  vuint64m2_t a_ext = __riscv_vzext_vf2_u64m2(a, 2);
  vint32m1_t b_neg = __riscv_vneg_v_i32m1(b, 2);
  vuint32m1_t shr = __riscv_vnclipu_wv_u32m1(a_ext, __riscv_vreinterpret_v_i32m1_u32m1(b_neg), __RISCV_VXRM_RNU, 2);
  return __riscv_vmerge_vvm_u32m1(shr, shl, positive_mask, 2);
}

FORCE_INLINE uint64x1_t vrshl_u64(uint64x1_t a, int64x1_t b) {
  // implementation only works within defined range 'b' in [0, 63]
  vbool64_t non_neg_mask = __riscv_vmsge_vx_i64m1_b64(b, 0, 1);
  vuint64m1_t shl = __riscv_vsll_vv_u64m1(a, __riscv_vreinterpret_v_i64m1_u64m1(b), 1);
  vint64m1_t b_neg = __riscv_vneg_v_i64m1(b, 1);
  vuint64m1_t round_const = __riscv_vsll_vv_u64m1(
      vdup_n_u64(1), __riscv_vreinterpret_v_i64m1_u64m1(__riscv_vsub_vx_i64m1(__riscv_vneg_v_i64m1(b, 1), 1, 1)), 1);
  vuint64m1_t a_round = __riscv_vadd_vv_u64m1(a, round_const, 1);
  vuint64m1_t shr = __riscv_vsrl_vv_u64m1((a_round), __riscv_vreinterpret_v_i64m1_u64m1(b_neg), 1);
  return __riscv_vmerge_vvm_u64m1(shr, shl, non_neg_mask, 1);
}

FORCE_INLINE int8x16_t vrshlq_s8(int8x16_t a, int8x16_t b) {
  // implementation only works within defined range 'b' in [0, 7]
  vbool8_t positive_mask = __riscv_vmsgt_vx_i8m1_b8(b, 0, 16);
  vint8m1_t shl = __riscv_vsll_vv_i8m1(a, __riscv_vreinterpret_v_i8m1_u8m1(b), 16);
  vint16m2_t a_ext = __riscv_vsext_vf2_i16m2(a, 16);
  vint8m1_t b_neg = __riscv_vneg_v_i8m1(b, 16);
  vint8m1_t shr = __riscv_vnclip_wv_i8m1(a_ext, __riscv_vreinterpret_v_i8m1_u8m1(b_neg), __RISCV_VXRM_RNU, 16);
  return __riscv_vmerge_vvm_i8m1(shr, shl, positive_mask, 16);
}

FORCE_INLINE int16x8_t vrshlq_s16(int16x8_t a, int16x8_t b) {
  // implementation only works within defined range 'b' in [0, 15]
  vbool16_t positive_mask = __riscv_vmsgt_vx_i16m1_b16(b, 0, 8);
  vint16m1_t shl = __riscv_vsll_vv_i16m1(a, __riscv_vreinterpret_v_i16m1_u16m1(b), 8);
  vint32m2_t a_ext = __riscv_vsext_vf2_i32m2(a, 8);
  vint16m1_t b_neg = __riscv_vneg_v_i16m1(b, 8);
  vint16m1_t shr = __riscv_vnclip_wv_i16m1(a_ext, __riscv_vreinterpret_v_i16m1_u16m1(b_neg), __RISCV_VXRM_RNU, 8);
  return __riscv_vmerge_vvm_i16m1(shr, shl, positive_mask, 8);
}

FORCE_INLINE int32x4_t vrshlq_s32(int32x4_t a, int32x4_t b) {
  // implementation only works within defined range 'b' in [0, 31]
  vbool32_t positive_mask = __riscv_vmsgt_vx_i32m1_b32(b, 0, 4);
  vint32m1_t shl = __riscv_vsll_vv_i32m1(a, __riscv_vreinterpret_v_i32m1_u32m1(b), 4);
  vint64m2_t a_ext = __riscv_vsext_vf2_i64m2(a, 4);
  vint32m1_t b_neg = __riscv_vneg_v_i32m1(b, 4);
  vint32m1_t shr = __riscv_vnclip_wv_i32m1(a_ext, __riscv_vreinterpret_v_i32m1_u32m1(b_neg), __RISCV_VXRM_RNU, 4);
  return __riscv_vmerge_vvm_i32m1(shr, shl, positive_mask, 4);
}

FORCE_INLINE int64x2_t vrshlq_s64(int64x2_t a, int64x2_t b) {
  // implementation only works within defined range 'b' in [0, 63]
  vbool64_t non_neg_mask = __riscv_vmsge_vx_i64m1_b64(b, 0, 2);
  vint64m1_t shl = __riscv_vsll_vv_i64m1(a, __riscv_vreinterpret_v_i64m1_u64m1(b), 2);
  vint64m1_t b_neg = __riscv_vneg_v_i64m1(b, 2);
  vint64m1_t round_const = __riscv_vsll_vv_i64m1(
      vdupq_n_s64(1), __riscv_vreinterpret_v_i64m1_u64m1(__riscv_vsub_vx_i64m1(__riscv_vneg_v_i64m1(b, 2), 1, 2)), 2);
  vint64m1_t a_round = __riscv_vadd_vv_i64m1(a, round_const, 2);
  vint64m1_t shr = __riscv_vsra_vv_i64m1((a_round), __riscv_vreinterpret_v_i64m1_u64m1(b_neg), 2);
  return __riscv_vmerge_vvm_i64m1(shr, shl, non_neg_mask, 2);
}

FORCE_INLINE uint8x16_t vrshlq_u8(uint8x16_t a, int8x16_t b) {
  // implementation only works within defined range 'b' in [0, 7]
  vbool8_t positive_mask = __riscv_vmsgt_vx_i8m1_b8(b, 0, 16);
  vuint8m1_t shl = __riscv_vsll_vv_u8m1(a, __riscv_vreinterpret_v_i8m1_u8m1(b), 16);
  vuint16m2_t a_ext = __riscv_vzext_vf2_u16m2(a, 16);
  vint8m1_t b_neg = __riscv_vneg_v_i8m1(b, 16);
  vuint8m1_t shr = __riscv_vnclipu_wv_u8m1(a_ext, __riscv_vreinterpret_v_i8m1_u8m1(b_neg), __RISCV_VXRM_RNU, 16);
  return __riscv_vmerge_vvm_u8m1(shr, shl, positive_mask, 16);
}

FORCE_INLINE uint16x8_t vrshlq_u16(uint16x8_t a, int16x8_t b) {
  // implementation only works within defined range 'b' in [0, 15]
  vbool16_t positive_mask = __riscv_vmsgt_vx_i16m1_b16(b, 0, 8);
  vuint16m1_t shl = __riscv_vsll_vv_u16m1(a, __riscv_vreinterpret_v_i16m1_u16m1(b), 8);
  vuint32m2_t a_ext = __riscv_vzext_vf2_u32m2(a, 8);
  vint16m1_t b_neg = __riscv_vneg_v_i16m1(b, 8);
  vuint16m1_t shr = __riscv_vnclipu_wv_u16m1(a_ext, __riscv_vreinterpret_v_i16m1_u16m1(b_neg), __RISCV_VXRM_RNU, 8);
  return __riscv_vmerge_vvm_u16m1(shr, shl, positive_mask, 8);
}

FORCE_INLINE uint32x4_t vrshlq_u32(uint32x4_t a, int32x4_t b) {
  // implementation only works within defined range 'b' in [0, 31]
  vbool32_t positive_mask = __riscv_vmsgt_vx_i32m1_b32(b, 0, 4);
  vuint32m1_t shl = __riscv_vsll_vv_u32m1(a, __riscv_vreinterpret_v_i32m1_u32m1(b), 4);
  vuint64m2_t a_ext = __riscv_vzext_vf2_u64m2(a, 4);
  vint32m1_t b_neg = __riscv_vneg_v_i32m1(b, 4);
  vuint32m1_t shr = __riscv_vnclipu_wv_u32m1(a_ext, __riscv_vreinterpret_v_i32m1_u32m1(b_neg), __RISCV_VXRM_RNU, 4);
  return __riscv_vmerge_vvm_u32m1(shr, shl, positive_mask, 4);
}

FORCE_INLINE uint64x2_t vrshlq_u64(uint64x2_t a, int64x2_t b) {
  // implementation only works within defined range 'b' in [0, 63]
  vbool64_t non_neg_mask = __riscv_vmsge_vx_i64m1_b64(b, 0, 2);
  vuint64m1_t shl = __riscv_vsll_vv_u64m1(a, __riscv_vreinterpret_v_i64m1_u64m1(b), 2);
  vint64m1_t b_neg = __riscv_vneg_v_i64m1(b, 2);
  vuint64m1_t round_const = __riscv_vsll_vv_u64m1(
      vdupq_n_u64(1), __riscv_vreinterpret_v_i64m1_u64m1(__riscv_vsub_vx_i64m1(__riscv_vneg_v_i64m1(b, 2), 1, 2)), 2);
  vuint64m1_t a_round = __riscv_vadd_vv_u64m1(a, round_const, 2);
  vuint64m1_t shr = __riscv_vsrl_vv_u64m1((a_round), __riscv_vreinterpret_v_i64m1_u64m1(b_neg), 2);
  return __riscv_vmerge_vvm_u64m1(shr, shl, non_neg_mask, 2);
}

FORCE_INLINE int64_t vrshld_s64(int64_t a, int64_t b) {
  if (b < 0) {
    int64_t b_neg = -b;
    return (a + (1 << (b_neg - 1))) >> b_neg;
  } else {
    return a << b;
  }
}

FORCE_INLINE uint64_t vrshld_u64(uint64_t a, int64_t b) {
  if (b < 0) {
    int64_t b_neg = -b;
    return (a + (1 << (b_neg - 1))) >> b_neg;
  } else {
    return a << b;
  }
}

FORCE_INLINE int8x8_t vqshl_s8(int8x8_t a, int8x8_t b) {
  vbool8_t positive_mask = __riscv_vmsgt_vx_i8m1_b8(b, 0, 8);
  vint16m2_t a_ext = __riscv_vsext_vf2_i16m2(a, 8);
  vint16m2_t b_ext = __riscv_vsext_vf2_i16m2(b, 8);
  // shift left
  vint16m2_t shl_w = __riscv_vsll_vv_i16m2(a_ext, __riscv_vreinterpret_v_i16m2_u16m2(b_ext), 8);
  vint8m1_t shl = __riscv_vnclip_wx_i8m1(shl_w, 0, __RISCV_VXRM_RDN, 8);
  // shift right
  vint8m1_t b_neg = __riscv_vneg_v_i8m1(b, 8);
  vint8m1_t shr = __riscv_vnclip_wv_i8m1(a_ext, __riscv_vreinterpret_v_i8m1_u8m1(b_neg), __RISCV_VXRM_RDN, 8);
  return __riscv_vmerge_vvm_i8m1(shr, shl, positive_mask, 8);
}

FORCE_INLINE int16x4_t vqshl_s16(int16x4_t a, int16x4_t b) {
  vbool16_t positive_mask = __riscv_vmsgt_vx_i16m1_b16(b, 0, 4);
  vint32m2_t a_ext = __riscv_vsext_vf2_i32m2(a, 4);
  vint32m2_t b_ext = __riscv_vsext_vf2_i32m2(b, 4);
  // shift left
  vint32m2_t shl_w = __riscv_vsll_vv_i32m2(a_ext, __riscv_vreinterpret_v_i32m2_u32m2(b_ext), 4);
  vint16m1_t shl = __riscv_vnclip_wx_i16m1(shl_w, 0, __RISCV_VXRM_RDN, 4);
  // shift right
  vint16m1_t b_neg = __riscv_vneg_v_i16m1(b, 4);
  vint16m1_t shr = __riscv_vnclip_wv_i16m1(a_ext, __riscv_vreinterpret_v_i16m1_u16m1(b_neg), __RISCV_VXRM_RDN, 4);
  return __riscv_vmerge_vvm_i16m1(shr, shl, positive_mask, 4);
}

FORCE_INLINE int32x2_t vqshl_s32(int32x2_t a, int32x2_t b) {
  vbool32_t positive_mask = __riscv_vmsgt_vx_i32m1_b32(b, 0, 2);
  vint64m2_t a_ext = __riscv_vsext_vf2_i64m2(a, 2);
  vint64m2_t b_ext = __riscv_vsext_vf2_i64m2(b, 2);
  // shift left
  vint64m2_t shl_w = __riscv_vsll_vv_i64m2(a_ext, __riscv_vreinterpret_v_i64m2_u64m2(b_ext), 2);
  vint32m1_t shl = __riscv_vnclip_wx_i32m1(shl_w, 0, __RISCV_VXRM_RDN, 2);
  // shift right
  vint32m1_t b_neg = __riscv_vneg_v_i32m1(b, 2);
  vint32m1_t shr = __riscv_vnclip_wv_i32m1(a_ext, __riscv_vreinterpret_v_i32m1_u32m1(b_neg), __RISCV_VXRM_RDN, 2);
  return __riscv_vmerge_vvm_i32m1(shr, shl, positive_mask, 2);
}

FORCE_INLINE int64x1_t vqshl_s64(int64x1_t a, int64x1_t b) {
  vbool64_t positive_mask = __riscv_vmsgt_vx_i64m1_b64(b, 0, 1);
  vint64m1_t shl = __riscv_vsll_vv_i64m1(a, __riscv_vreinterpret_v_i64m1_u64m1(b), 1);
  vint64m1_t b_neg = __riscv_vneg_v_i64m1(b, 1);
  vint64m1_t shr = __riscv_vsra_vv_i64m1(a, __riscv_vreinterpret_v_i64m1_u64m1(b_neg), 1);
  return __riscv_vmerge_vvm_i64m1(shr, shl, positive_mask, 1);
}

FORCE_INLINE uint8x8_t vqshl_u8(uint8x8_t a, int8x8_t b) {
  vbool8_t positive_mask = __riscv_vmsgt_vx_i8m1_b8(b, 0, 8);
  vuint16m2_t a_ext = __riscv_vzext_vf2_u16m2(a, 8);
  vint16m2_t b_ext = __riscv_vsext_vf2_i16m2(b, 8);
  // shift left
  vuint16m2_t shl_w = __riscv_vsll_vv_u16m2(a_ext, __riscv_vreinterpret_v_i16m2_u16m2(b_ext), 8);
  vuint8m1_t shl = __riscv_vnclipu_wx_u8m1(shl_w, 0, __RISCV_VXRM_RDN, 8);
  // shift right
  vint8m1_t b_neg = __riscv_vneg_v_i8m1(b, 8);
  vuint8m1_t shr = __riscv_vnclipu_wv_u8m1(a_ext, __riscv_vreinterpret_v_i8m1_u8m1(b_neg), __RISCV_VXRM_RDN, 8);
  return __riscv_vmerge_vvm_u8m1(shr, shl, positive_mask, 8);
}

FORCE_INLINE uint16x4_t vqshl_u16(uint16x4_t a, int16x4_t b) {
  vbool16_t positive_mask = __riscv_vmsgt_vx_i16m1_b16(b, 0, 4);
  vuint32m2_t a_ext = __riscv_vzext_vf2_u32m2(a, 4);
  vint32m2_t b_ext = __riscv_vsext_vf2_i32m2(b, 4);
  // shift left
  vuint32m2_t shl_w = __riscv_vsll_vv_u32m2(a_ext, __riscv_vreinterpret_v_i32m2_u32m2(b_ext), 4);
  vuint16m1_t shl = __riscv_vnclipu_wx_u16m1(shl_w, 0, __RISCV_VXRM_RDN, 4);
  // shift right
  vint16m1_t b_neg = __riscv_vneg_v_i16m1(b, 4);
  vuint16m1_t shr = __riscv_vnclipu_wv_u16m1(a_ext, __riscv_vreinterpret_v_i16m1_u16m1(b_neg), __RISCV_VXRM_RDN, 4);
  return __riscv_vmerge_vvm_u16m1(shr, shl, positive_mask, 4);
}

FORCE_INLINE uint32x2_t vqshl_u32(uint32x2_t a, int32x2_t b) {
  vbool32_t positive_mask = __riscv_vmsgt_vx_i32m1_b32(b, 0, 2);
  vuint64m2_t a_ext = __riscv_vzext_vf2_u64m2(a, 2);
  vint64m2_t b_ext = __riscv_vsext_vf2_i64m2(b, 2);
  // shift left
  vuint64m2_t shl_w = __riscv_vsll_vv_u64m2(a_ext, __riscv_vreinterpret_v_i64m2_u64m2(b_ext), 2);
  vuint32m1_t shl = __riscv_vnclipu_wx_u32m1(shl_w, 0, __RISCV_VXRM_RDN, 2);
  // shift right
  vint32m1_t b_neg = __riscv_vneg_v_i32m1(b, 2);
  vuint32m1_t shr = __riscv_vnclipu_wv_u32m1(a_ext, __riscv_vreinterpret_v_i32m1_u32m1(b_neg), __RISCV_VXRM_RDN, 2);
  return __riscv_vmerge_vvm_u32m1(shr, shl, positive_mask, 2);
}

FORCE_INLINE uint64x1_t vqshl_u64(uint64x1_t a, int64x1_t b) {
  uint64_t _a = ((uint64_t *)&a)[0];
  int64_t _b = ((int64_t *)&b)[0];
  _b = _b % 8;
  uint64_t _c;
  if (_b < 0) {
    _c = _a >> -_b;
  } else {
    if ((UINT64_MAX >> _b) < _a) {
      _c = UINT64_MAX;
    } else {
      _c = (uint64_t)_a << _b;
    }
  }
  return __riscv_vmv_v_x_u64m1(_c, 1);
}

FORCE_INLINE int8x16_t vqshlq_s8(int8x16_t a, int8x16_t b) {
  vbool8_t positive_mask = __riscv_vmsgt_vx_i8m1_b8(b, 0, 16);
  vint16m2_t a_ext = __riscv_vsext_vf2_i16m2(a, 16);
  vint16m2_t b_ext = __riscv_vsext_vf2_i16m2(b, 16);
  // shift left
  vint16m2_t shl_w = __riscv_vsll_vv_i16m2(a_ext, __riscv_vreinterpret_v_i16m2_u16m2(b_ext), 16);
  vint8m1_t shl = __riscv_vnclip_wx_i8m1(shl_w, 0, __RISCV_VXRM_RDN, 16);
  // shift right
  vint8m1_t b_neg = __riscv_vneg_v_i8m1(b, 16);
  vint8m1_t shr = __riscv_vnclip_wv_i8m1(a_ext, __riscv_vreinterpret_v_i8m1_u8m1(b_neg), __RISCV_VXRM_RDN, 16);
  return __riscv_vmerge_vvm_i8m1(shr, shl, positive_mask, 16);
}

FORCE_INLINE int16x8_t vqshlq_s16(int16x8_t a, int16x8_t b) {
  vbool16_t positive_mask = __riscv_vmsgt_vx_i16m1_b16(b, 0, 8);
  vint32m2_t a_ext = __riscv_vsext_vf2_i32m2(a, 8);
  vint32m2_t b_ext = __riscv_vsext_vf2_i32m2(b, 8);
  // shift left
  vint32m2_t shl_w = __riscv_vsll_vv_i32m2(a_ext, __riscv_vreinterpret_v_i32m2_u32m2(b_ext), 8);
  vint16m1_t shl = __riscv_vnclip_wx_i16m1(shl_w, 0, __RISCV_VXRM_RDN, 8);
  // shift right
  vint16m1_t b_neg = __riscv_vneg_v_i16m1(b, 8);
  vint16m1_t shr = __riscv_vnclip_wv_i16m1(a_ext, __riscv_vreinterpret_v_i16m1_u16m1(b_neg), __RISCV_VXRM_RDN, 8);
  return __riscv_vmerge_vvm_i16m1(shr, shl, positive_mask, 8);
}

FORCE_INLINE int32x4_t vqshlq_s32(int32x4_t a, int32x4_t b) {
  vbool32_t positive_mask = __riscv_vmsgt_vx_i32m1_b32(b, 0, 4);
  vint64m2_t a_ext = __riscv_vsext_vf2_i64m2(a, 4);
  vint64m2_t b_ext = __riscv_vsext_vf2_i64m2(b, 4);
  // shift left
  vint64m2_t shl_w = __riscv_vsll_vv_i64m2(a_ext, __riscv_vreinterpret_v_i64m2_u64m2(b_ext), 4);
  vint32m1_t shl = __riscv_vnclip_wx_i32m1(shl_w, 0, __RISCV_VXRM_RDN, 4);
  // shift right
  vint32m1_t b_neg = __riscv_vneg_v_i32m1(b, 4);
  vint32m1_t shr = __riscv_vnclip_wv_i32m1(a_ext, __riscv_vreinterpret_v_i32m1_u32m1(b_neg), __RISCV_VXRM_RDN, 4);
  return __riscv_vmerge_vvm_i32m1(shr, shl, positive_mask, 4);
}

FORCE_INLINE int64x2_t vqshlq_s64(int64x2_t a, int64x2_t b) {
  vbool64_t positive_mask = __riscv_vmsgt_vx_i64m1_b64(b, 0, 2);
  vint64m1_t shl = __riscv_vsll_vv_i64m1(a, __riscv_vreinterpret_v_i64m1_u64m1(b), 2);
  vint64m1_t b_neg = __riscv_vneg_v_i64m1(b, 2);
  vint64m1_t shr = __riscv_vsra_vv_i64m1(a, __riscv_vreinterpret_v_i64m1_u64m1(b_neg), 2);
  return __riscv_vmerge_vvm_i64m1(shr, shl, positive_mask, 2);
}

FORCE_INLINE uint8x16_t vqshlq_u8(uint8x16_t a, int8x16_t b) {
  vbool8_t positive_mask = __riscv_vmsgt_vx_i8m1_b8(b, 0, 16);
  vuint16m2_t a_ext = __riscv_vzext_vf2_u16m2(a, 16);
  vint16m2_t b_ext = __riscv_vsext_vf2_i16m2(b, 16);
  // shift left
  vuint16m2_t shl_w = __riscv_vsll_vv_u16m2(a_ext, __riscv_vreinterpret_v_i16m2_u16m2(b_ext), 16);
  vuint8m1_t shl = __riscv_vnclipu_wx_u8m1(shl_w, 0, __RISCV_VXRM_RDN, 16);
  // shift right
  vint8m1_t b_neg = __riscv_vneg_v_i8m1(b, 16);
  vuint8m1_t shr = __riscv_vnclipu_wv_u8m1(a_ext, __riscv_vreinterpret_v_i8m1_u8m1(b_neg), __RISCV_VXRM_RDN, 16);
  return __riscv_vmerge_vvm_u8m1(shr, shl, positive_mask, 16);
}

FORCE_INLINE uint16x8_t vqshlq_u16(uint16x8_t a, int16x8_t b) {
  vbool16_t positive_mask = __riscv_vmsgt_vx_i16m1_b16(b, 0, 8);
  vuint32m2_t a_ext = __riscv_vzext_vf2_u32m2(a, 8);
  vint32m2_t b_ext = __riscv_vsext_vf2_i32m2(b, 8);
  // shift left
  vuint32m2_t shl_w = __riscv_vsll_vv_u32m2(a_ext, __riscv_vreinterpret_v_i32m2_u32m2(b_ext), 8);
  vuint16m1_t shl = __riscv_vnclipu_wx_u16m1(shl_w, 0, __RISCV_VXRM_RDN, 8);
  // shift right
  vint16m1_t b_neg = __riscv_vneg_v_i16m1(b, 8);
  vuint16m1_t shr = __riscv_vnclipu_wv_u16m1(a_ext, __riscv_vreinterpret_v_i16m1_u16m1(b_neg), __RISCV_VXRM_RDN, 8);
  return __riscv_vmerge_vvm_u16m1(shr, shl, positive_mask, 8);
}

FORCE_INLINE uint32x4_t vqshlq_u32(uint32x4_t a, int32x4_t b) {
  vbool32_t positive_mask = __riscv_vmsgt_vx_i32m1_b32(b, 0, 4);
  vuint64m2_t a_ext = __riscv_vzext_vf2_u64m2(a, 4);
  vint64m2_t b_ext = __riscv_vsext_vf2_i64m2(b, 4);
  // shift left
  vuint64m2_t shl_w = __riscv_vsll_vv_u64m2(a_ext, __riscv_vreinterpret_v_i64m2_u64m2(b_ext), 4);
  vuint32m1_t shl = __riscv_vnclipu_wx_u32m1(shl_w, 0, __RISCV_VXRM_RDN, 4);
  // shift right
  vint32m1_t b_neg = __riscv_vneg_v_i32m1(b, 4);
  vuint32m1_t shr = __riscv_vnclipu_wv_u32m1(a_ext, __riscv_vreinterpret_v_i32m1_u32m1(b_neg), __RISCV_VXRM_RDN, 4);
  return __riscv_vmerge_vvm_u32m1(shr, shl, positive_mask, 4);
}

FORCE_INLINE uint64x2_t vqshlq_u64(uint64x2_t a, int64x2_t b) {
  uint64_t *_a = ((uint64_t *)&a);
  int64_t *_b = ((int64_t *)&b);
  uint64_t _c[2];
  for (int i = 0; i < 2; i++) {
    _b[i] = _b[i] % 8;
    if (_b[i] < 0) {
      _c[i] = _a[i] >> -_b[i];
    } else {
      if ((UINT64_MAX >> _b[i]) < _a[i]) {
        _c[i] = UINT64_MAX;
      } else {
        _c[i] = (uint64_t)_a[i] << _b[i];
      }
    }
  }
  return __riscv_vle64_v_u64m1(_c, 2);
}

FORCE_INLINE int8_t vqshlb_s8(int8_t a, int8_t b) {
  if (b < 0) {
    return a >> -b;
  }

  int16_t tmp = a << b;
  if (tmp > INT8_MAX) {
    return (int8_t)INT8_MAX;
  }
  if (tmp < INT8_MIN) {
    return (int8_t)INT8_MIN;
  }
  return (int8_t)tmp;
}

FORCE_INLINE int16_t vqshlh_s16(int16_t a, int16_t b) {
  if (b < 0) {
    return a >> -b;
  }
  int32_t tmp = a << b;
  if (tmp > INT16_MAX) {
    return (int16_t)INT16_MAX;
  }
  if (tmp < INT16_MIN) {
    return (int16_t)INT16_MIN;
  }
  return (int16_t)tmp;
}

FORCE_INLINE int32_t vqshls_s32(int32_t a, int32_t b) {
  if (b < 0) {
    return a >> -b;
  }
  if ((INT32_MAX >> b) < a) {
    return INT32_MAX;
  } else {
    return a << b;
  }
}

FORCE_INLINE int64_t vqshld_s64(int64_t a, int64_t b) {
  if (b < 0) {
    return a >> -b;
  }
  if ((INT64_MAX >> b) < a) {
    return INT64_MAX;
  } else {
    return (int64_t)a << b;
  }
}

FORCE_INLINE uint8_t vqshlb_u8(uint8_t a, int8_t b) {
  if (b < 0) {
    return a >> -b;
  }
  if ((UINT8_MAX >> b) < a) {
    return UINT8_MAX;
  } else {
    return a << b;
  }
}

FORCE_INLINE uint16_t vqshlh_u16(uint16_t a, int16_t b) {
  if (b < 0) {
    return a >> -b;
  }
  if ((UINT16_MAX >> b) < a) {
    return UINT16_MAX;
  } else {
    return a << b;
  }
}

FORCE_INLINE uint32_t vqshls_u32(uint32_t a, int32_t b) {
  if (b < 0) {
    return a >> -b;
  }
  if ((UINT32_MAX >> b) < a) {
    return UINT32_MAX;
  } else {
    return a << b;
  }
}

FORCE_INLINE uint64_t vqshld_u64(uint64_t a, int64_t b) {
  if (b < 0) {
    return a >> -b;
  }
  if ((UINT64_MAX >> b) < a) {
    return UINT64_MAX;
  } else {
    return (uint64_t)a << b;
  }
}

FORCE_INLINE int8x8_t vqrshl_s8(int8x8_t a, int8x8_t b) {
  vbool8_t positive_mask = __riscv_vmsgt_vx_i8m1_b8(b, 0, 8);
  vint16m2_t a_ext = __riscv_vsext_vf2_i16m2(a, 8);
  vint16m2_t b_ext = __riscv_vsext_vf2_i16m2(b, 8);
  // shift left
  vint16m2_t shl_w = __riscv_vsll_vv_i16m2(a_ext, __riscv_vreinterpret_v_i16m2_u16m2(b_ext), 8);
  vint8m1_t shl = __riscv_vnclip_wx_i8m1(shl_w, 0, __RISCV_VXRM_RDN, 8);
  // shift right
  vint8m1_t b_neg = __riscv_vneg_v_i8m1(b, 8);
  vint8m1_t shr = __riscv_vnclip_wv_i8m1(a_ext, __riscv_vreinterpret_v_i8m1_u8m1(b_neg), __RISCV_VXRM_RNU, 8);
  return __riscv_vmerge_vvm_i8m1(shr, shl, positive_mask, 8);
}

FORCE_INLINE int16x4_t vqrshl_s16(int16x4_t a, int16x4_t b) {
  vbool16_t positive_mask = __riscv_vmsgt_vx_i16m1_b16(b, 0, 4);
  vint32m2_t a_ext = __riscv_vsext_vf2_i32m2(a, 4);
  vint32m2_t b_ext = __riscv_vsext_vf2_i32m2(b, 4);
  // shift left
  vint32m2_t shl_w = __riscv_vsll_vv_i32m2(a_ext, __riscv_vreinterpret_v_i32m2_u32m2(b_ext), 4);
  vint16m1_t shl = __riscv_vnclip_wx_i16m1(shl_w, 0, __RISCV_VXRM_RDN, 4);
  // shift right
  vint16m1_t b_neg = __riscv_vneg_v_i16m1(b, 4);
  vint16m1_t shr = __riscv_vnclip_wv_i16m1(a_ext, __riscv_vreinterpret_v_i16m1_u16m1(b_neg), __RISCV_VXRM_RNU, 4);
  return __riscv_vmerge_vvm_i16m1(shr, shl, positive_mask, 4);
}

FORCE_INLINE int32x2_t vqrshl_s32(int32x2_t a, int32x2_t b) {
  vbool32_t positive_mask = __riscv_vmsgt_vx_i32m1_b32(b, 0, 2);
  vint64m2_t a_ext = __riscv_vsext_vf2_i64m2(a, 2);
  vint64m2_t b_ext = __riscv_vsext_vf2_i64m2(b, 2);
  // shift left
  vint64m2_t shl_w = __riscv_vsll_vv_i64m2(a_ext, __riscv_vreinterpret_v_i64m2_u64m2(b_ext), 2);
  vint32m1_t shl = __riscv_vnclip_wx_i32m1(shl_w, 0, __RISCV_VXRM_RDN, 2);
  // shift right
  vint32m1_t b_neg = __riscv_vneg_v_i32m1(b, 2);
  vint32m1_t shr = __riscv_vnclip_wv_i32m1(a_ext, __riscv_vreinterpret_v_i32m1_u32m1(b_neg), __RISCV_VXRM_RNU, 2);
  return __riscv_vmerge_vvm_i32m1(shr, shl, positive_mask, 2);
}

// FORCE_INLINE int64x1_t vqrshl_s64(int64x1_t a, int64x1_t b);

FORCE_INLINE uint8x8_t vqrshl_u8(uint8x8_t a, int8x8_t b) {
  vbool8_t positive_mask = __riscv_vmsgt_vx_i8m1_b8(b, 0, 8);
  vuint16m2_t a_ext = __riscv_vzext_vf2_u16m2(a, 8);
  vint16m2_t b_ext = __riscv_vsext_vf2_i16m2(b, 8);
  // shift left
  vuint16m2_t shl_w = __riscv_vsll_vv_u16m2(a_ext, __riscv_vreinterpret_v_i16m2_u16m2(b_ext), 8);
  vuint8m1_t shl = __riscv_vnclipu_wx_u8m1(shl_w, 0, __RISCV_VXRM_RDN, 8);
  // shift right
  vint8m1_t b_neg = __riscv_vneg_v_i8m1(b, 8);
  vuint8m1_t shr = __riscv_vnclipu_wv_u8m1(a_ext, __riscv_vreinterpret_v_i8m1_u8m1(b_neg), __RISCV_VXRM_RNU, 8);
  return __riscv_vmerge_vvm_u8m1(shr, shl, positive_mask, 8);
}

FORCE_INLINE uint16x4_t vqrshl_u16(uint16x4_t a, int16x4_t b) {
  vbool16_t positive_mask = __riscv_vmsgt_vx_i16m1_b16(b, 0, 4);
  vuint32m2_t a_ext = __riscv_vzext_vf2_u32m2(a, 4);
  vint32m2_t b_ext = __riscv_vsext_vf2_i32m2(b, 4);
  // shift left
  vuint32m2_t shl_w = __riscv_vsll_vv_u32m2(a_ext, __riscv_vreinterpret_v_i32m2_u32m2(b_ext), 4);
  vuint16m1_t shl = __riscv_vnclipu_wx_u16m1(shl_w, 0, __RISCV_VXRM_RDN, 4);
  // shift right
  vint16m1_t b_neg = __riscv_vneg_v_i16m1(b, 4);
  vuint16m1_t shr = __riscv_vnclipu_wv_u16m1(a_ext, __riscv_vreinterpret_v_i16m1_u16m1(b_neg), __RISCV_VXRM_RNU, 4);
  return __riscv_vmerge_vvm_u16m1(shr, shl, positive_mask, 4);
}

FORCE_INLINE uint32x2_t vqrshl_u32(uint32x2_t a, int32x2_t b) {
  vbool32_t positive_mask = __riscv_vmsgt_vx_i32m1_b32(b, 0, 2);
  vuint64m2_t a_ext = __riscv_vzext_vf2_u64m2(a, 2);
  vint64m2_t b_ext = __riscv_vsext_vf2_i64m2(b, 2);
  // shift left
  vuint64m2_t shl_w = __riscv_vsll_vv_u64m2(a_ext, __riscv_vreinterpret_v_i64m2_u64m2(b_ext), 2);
  vuint32m1_t shl = __riscv_vnclipu_wx_u32m1(shl_w, 0, __RISCV_VXRM_RDN, 2);
  // shift right
  vint32m1_t b_neg = __riscv_vneg_v_i32m1(b, 2);
  vuint32m1_t shr = __riscv_vnclipu_wv_u32m1(a_ext, __riscv_vreinterpret_v_i32m1_u32m1(b_neg), __RISCV_VXRM_RNU, 2);
  return __riscv_vmerge_vvm_u32m1(shr, shl, positive_mask, 2);
}

// FORCE_INLINE uint64x1_t vqrshl_u64(uint64x1_t a, int64x1_t b);

FORCE_INLINE int8x16_t vqrshlq_s8(int8x16_t a, int8x16_t b) {
  vbool8_t positive_mask = __riscv_vmsgt_vx_i8m1_b8(b, 0, 16);
  vint16m2_t a_ext = __riscv_vsext_vf2_i16m2(a, 16);
  vint16m2_t b_ext = __riscv_vsext_vf2_i16m2(b, 16);
  // shift left
  vint16m2_t shl_w = __riscv_vsll_vv_i16m2(a_ext, __riscv_vreinterpret_v_i16m2_u16m2(b_ext), 16);
  vint8m1_t shl = __riscv_vnclip_wx_i8m1(shl_w, 0, __RISCV_VXRM_RDN, 16);
  // shift right
  vint8m1_t b_neg = __riscv_vneg_v_i8m1(b, 16);
  vint8m1_t shr = __riscv_vnclip_wv_i8m1(a_ext, __riscv_vreinterpret_v_i8m1_u8m1(b_neg), __RISCV_VXRM_RNU, 16);
  return __riscv_vmerge_vvm_i8m1(shr, shl, positive_mask, 16);
}

FORCE_INLINE int16x8_t vqrshlq_s16(int16x8_t a, int16x8_t b) {
  vbool16_t positive_mask = __riscv_vmsgt_vx_i16m1_b16(b, 0, 8);
  vint32m2_t a_ext = __riscv_vsext_vf2_i32m2(a, 8);
  vint32m2_t b_ext = __riscv_vsext_vf2_i32m2(b, 8);
  // shift left
  vint32m2_t shl_w = __riscv_vsll_vv_i32m2(a_ext, __riscv_vreinterpret_v_i32m2_u32m2(b_ext), 8);
  vint16m1_t shl = __riscv_vnclip_wx_i16m1(shl_w, 0, __RISCV_VXRM_RDN, 8);
  // shift right
  vint16m1_t b_neg = __riscv_vneg_v_i16m1(b, 8);
  vint16m1_t shr = __riscv_vnclip_wv_i16m1(a_ext, __riscv_vreinterpret_v_i16m1_u16m1(b_neg), __RISCV_VXRM_RNU, 8);
  return __riscv_vmerge_vvm_i16m1(shr, shl, positive_mask, 8);
}

FORCE_INLINE int32x4_t vqrshlq_s32(int32x4_t a, int32x4_t b) {
  vbool32_t positive_mask = __riscv_vmsgt_vx_i32m1_b32(b, 0, 4);
  vint64m2_t a_ext = __riscv_vsext_vf2_i64m2(a, 4);
  vint64m2_t b_ext = __riscv_vsext_vf2_i64m2(b, 4);
  // shift left
  vint64m2_t shl_w = __riscv_vsll_vv_i64m2(a_ext, __riscv_vreinterpret_v_i64m2_u64m2(b_ext), 4);
  vint32m1_t shl = __riscv_vnclip_wx_i32m1(shl_w, 0, __RISCV_VXRM_RDN, 4);
  // shift right
  vint32m1_t b_neg = __riscv_vneg_v_i32m1(b, 4);
  vint32m1_t shr = __riscv_vnclip_wv_i32m1(a_ext, __riscv_vreinterpret_v_i32m1_u32m1(b_neg), __RISCV_VXRM_RNU, 4);
  return __riscv_vmerge_vvm_i32m1(shr, shl, positive_mask, 4);
}

// FORCE_INLINE int64x2_t vqrshlq_s64(int64x2_t a, int64x2_t b);

FORCE_INLINE uint8x16_t vqrshlq_u8(uint8x16_t a, int8x16_t b) {
  vbool8_t positive_mask = __riscv_vmsgt_vx_i8m1_b8(b, 0, 16);
  vuint16m2_t a_ext = __riscv_vzext_vf2_u16m2(a, 16);
  vint16m2_t b_ext = __riscv_vsext_vf2_i16m2(b, 16);
  // shift left
  vuint16m2_t shl_w = __riscv_vsll_vv_u16m2(a_ext, __riscv_vreinterpret_v_i16m2_u16m2(b_ext), 16);
  vuint8m1_t shl = __riscv_vnclipu_wx_u8m1(shl_w, 0, __RISCV_VXRM_RDN, 16);
  // shift right
  vint8m1_t b_neg = __riscv_vneg_v_i8m1(b, 16);
  vuint8m1_t shr = __riscv_vnclipu_wv_u8m1(a_ext, __riscv_vreinterpret_v_i8m1_u8m1(b_neg), __RISCV_VXRM_RNU, 16);
  return __riscv_vmerge_vvm_u8m1(shr, shl, positive_mask, 16);
}

FORCE_INLINE uint16x8_t vqrshlq_u16(uint16x8_t a, int16x8_t b) {
  vbool16_t positive_mask = __riscv_vmsgt_vx_i16m1_b16(b, 0, 8);
  vuint32m2_t a_ext = __riscv_vzext_vf2_u32m2(a, 8);
  vint32m2_t b_ext = __riscv_vsext_vf2_i32m2(b, 8);
  // shift left
  vuint32m2_t shl_w = __riscv_vsll_vv_u32m2(a_ext, __riscv_vreinterpret_v_i32m2_u32m2(b_ext), 8);
  vuint16m1_t shl = __riscv_vnclipu_wx_u16m1(shl_w, 0, __RISCV_VXRM_RDN, 8);
  // shift right
  vint16m1_t b_neg = __riscv_vneg_v_i16m1(b, 8);
  vuint16m1_t shr = __riscv_vnclipu_wv_u16m1(a_ext, __riscv_vreinterpret_v_i16m1_u16m1(b_neg), __RISCV_VXRM_RNU, 8);
  return __riscv_vmerge_vvm_u16m1(shr, shl, positive_mask, 8);
}

FORCE_INLINE uint32x4_t vqrshlq_u32(uint32x4_t a, int32x4_t b) {
  vbool32_t positive_mask = __riscv_vmsgt_vx_i32m1_b32(b, 0, 4);
  vuint64m2_t a_ext = __riscv_vzext_vf2_u64m2(a, 4);
  vint64m2_t b_ext = __riscv_vsext_vf2_i64m2(b, 4);
  // shift left
  vuint64m2_t shl_w = __riscv_vsll_vv_u64m2(a_ext, __riscv_vreinterpret_v_i64m2_u64m2(b_ext), 4);
  vuint32m1_t shl = __riscv_vnclipu_wx_u32m1(shl_w, 0, __RISCV_VXRM_RDN, 4);
  // shift right
  vint32m1_t b_neg = __riscv_vneg_v_i32m1(b, 4);
  vuint32m1_t shr = __riscv_vnclipu_wv_u32m1(a_ext, __riscv_vreinterpret_v_i32m1_u32m1(b_neg), __RISCV_VXRM_RNU, 4);
  return __riscv_vmerge_vvm_u32m1(shr, shl, positive_mask, 4);
}

// FORCE_INLINE uint64x2_t vqrshlq_u64(uint64x2_t a, int64x2_t b);

// FORCE_INLINE int8_t vqrshlb_s8(int8_t a, int8_t b);

// FORCE_INLINE int16_t vqrshlh_s16(int16_t a, int16_t b);

// FORCE_INLINE int32_t vqrshls_s32(int32_t a, int32_t b);

// FORCE_INLINE int64_t vqrshld_s64(int64_t a, int64_t b);

// FORCE_INLINE uint8_t vqrshlb_u8(uint8_t a, int8_t b);

// FORCE_INLINE uint16_t vqrshlh_u16(uint16_t a, int16_t b);

// FORCE_INLINE uint32_t vqrshls_u32(uint32_t a, int32_t b);

// FORCE_INLINE uint64_t vqrshld_u64(uint64_t a, int64_t b);

FORCE_INLINE int8x8_t vshr_n_s8(int8x8_t a, const int b) {
  const int imm = b - (b >> 3);
  return __riscv_vsra_vx_i8m1(a, imm, 8);
}

FORCE_INLINE int16x4_t vshr_n_s16(int16x4_t a, const int b) {
  const int imm = b - (b >> 4);
  return __riscv_vsra_vx_i16m1(a, imm, 4);
}

FORCE_INLINE int32x2_t vshr_n_s32(int32x2_t a, const int b) {
  const int imm = b - (b >> 5);
  return __riscv_vsra_vx_i32m1(a, imm, 2);
}

FORCE_INLINE int64x1_t vshr_n_s64(int64x1_t a, const int b) {
  const int imm = b - (b >> 6);
  return __riscv_vsra_vx_i64m1(a, imm, 1);
}

FORCE_INLINE uint8x8_t vshr_n_u8(uint8x8_t a, const int b) {
  const int b_half = b >> 1;
  vuint8m1_t srl1 = __riscv_vsrl_vx_u8m1(a, b_half, 8);
  return __riscv_vsrl_vx_u8m1(srl1, b_half + (b & 0x1), 8);
}

FORCE_INLINE uint16x4_t vshr_n_u16(uint16x4_t a, const int b) {
  const int b_half = b >> 1;
  vuint16m1_t srl1 = __riscv_vsrl_vx_u16m1(a, b_half, 4);
  return __riscv_vsrl_vx_u16m1(srl1, b_half + (b & 0x1), 4);
}

FORCE_INLINE uint32x2_t vshr_n_u32(uint32x2_t a, const int b) {
  const int b_half = b >> 1;
  vuint32m1_t srl1 = __riscv_vsrl_vx_u32m1(a, b_half, 2);
  return __riscv_vsrl_vx_u32m1(srl1, b_half + (b & 0x1), 2);
}

FORCE_INLINE uint64x1_t vshr_n_u64(uint64x1_t a, const int b) {
  const int b_half = b >> 1;
  vuint64m1_t srl1 = __riscv_vsrl_vx_u64m1(a, b_half, 1);
  return __riscv_vsrl_vx_u64m1(srl1, b_half + (b & 0x1), 1);
}

FORCE_INLINE int8x16_t vshrq_n_s8(int8x16_t a, const int b) {
  const int imm = b - (b >> 3);
  return __riscv_vsra_vx_i8m1(a, imm, 16);
}

FORCE_INLINE int16x8_t vshrq_n_s16(int16x8_t a, const int b) {
  const int imm = b - (b >> 4);
  return __riscv_vsra_vx_i16m1(a, imm, 8);
}

FORCE_INLINE int32x4_t vshrq_n_s32(int32x4_t a, const int b) {
  const int imm = b - (b >> 5);
  return __riscv_vsra_vx_i32m1(a, imm, 4);
}

FORCE_INLINE int64x2_t vshrq_n_s64(int64x2_t a, const int b) {
  const int imm = b - (b >> 6);
  return __riscv_vsra_vx_i64m1(a, imm, 2);
}

FORCE_INLINE uint8x16_t vshrq_n_u8(uint8x16_t a, const int b) {
  const int b_half = b >> 1;
  vuint8m1_t srl1 = __riscv_vsrl_vx_u8m1(a, b_half, 16);
  return __riscv_vsrl_vx_u8m1(srl1, b_half + (b & 0x1), 16);
}

FORCE_INLINE uint16x8_t vshrq_n_u16(uint16x8_t a, const int b) {
  const int b_half = b >> 1;
  vuint16m1_t srl1 = __riscv_vsrl_vx_u16m1(a, b_half, 8);
  return __riscv_vsrl_vx_u16m1(srl1, b_half + (b & 0x1), 8);
}

FORCE_INLINE uint32x4_t vshrq_n_u32(uint32x4_t a, const int b) {
  const int b_half = b >> 1;
  vuint32m1_t srl1 = __riscv_vsrl_vx_u32m1(a, b_half, 4);
  return __riscv_vsrl_vx_u32m1(srl1, b_half + (b & 0x1), 4);
}

FORCE_INLINE uint64x2_t vshrq_n_u64(uint64x2_t a, const int b) {
  const int b_half = b >> 1;
  vuint64m1_t srl1 = __riscv_vsrl_vx_u64m1(a, b_half, 2);
  return __riscv_vsrl_vx_u64m1(srl1, b_half + (b & 0x1), 2);
}

FORCE_INLINE int64_t vshrd_n_s64(int64_t a, const int n) { return a >> n; }

FORCE_INLINE uint64_t vshrd_n_u64(uint64_t a, const int n) { return a >> n; }

FORCE_INLINE int8x8_t vrshr_n_s8(int8x8_t a, const int b) {
  vint16m2_t a_ext = __riscv_vsext_vf2_i16m2(a, 8);
  return __riscv_vnclip_wx_i8m1(a_ext, b, __RISCV_VXRM_RNU, 8);
}

FORCE_INLINE int16x4_t vrshr_n_s16(int16x4_t a, const int b) {
  vint32m2_t a_ext = __riscv_vsext_vf2_i32m2(a, 4);
  return __riscv_vnclip_wx_i16m1(a_ext, b, __RISCV_VXRM_RNU, 4);
}

FORCE_INLINE int32x2_t vrshr_n_s32(int32x2_t a, const int b) {
  vint64m2_t a_ext = __riscv_vsext_vf2_i64m2(a, 2);
  return __riscv_vnclip_wx_i32m1(a_ext, b, __RISCV_VXRM_RNU, 2);
}

FORCE_INLINE int64x1_t vrshr_n_s64(int64x1_t a, const int b) {
  vint64m1_t sra = __riscv_vsra_vx_i64m1(a, b - 1, 2);
  vint64m1_t sra_round = __riscv_vadd_vv_i64m1(sra, __riscv_vand_vx_i64m1(sra, 1, 2), 2);
  return __riscv_vsra_vx_i64m1(sra_round, 1, 2);
}

FORCE_INLINE uint8x8_t vrshr_n_u8(uint8x8_t a, const int b) {
  vuint16m2_t a_ext = __riscv_vzext_vf2_u16m2(a, 8);
  return __riscv_vnclipu_wx_u8m1(a_ext, b, __RISCV_VXRM_RNU, 8);
}

FORCE_INLINE uint16x4_t vrshr_n_u16(uint16x4_t a, const int b) {
  vuint32m2_t a_ext = __riscv_vzext_vf2_u32m2(a, 4);
  return __riscv_vnclipu_wx_u16m1(a_ext, b, __RISCV_VXRM_RNU, 4);
}

FORCE_INLINE uint32x2_t vrshr_n_u32(uint32x2_t a, const int b) {
  vuint64m2_t a_ext = __riscv_vzext_vf2_u64m2(a, 2);
  return __riscv_vnclipu_wx_u32m1(a_ext, b, __RISCV_VXRM_RNU, 2);
}

FORCE_INLINE uint64x1_t vrshr_n_u64(uint64x1_t a, const int b) {
  vuint64m1_t srl = __riscv_vsrl_vx_u64m1(a, b - 1, 2);
  vuint64m1_t srl_round = __riscv_vadd_vv_u64m1(srl, __riscv_vand_vx_u64m1(srl, 1, 2), 2);
  return __riscv_vsrl_vx_u64m1(srl_round, 1, 2);
}

FORCE_INLINE int8x16_t vrshrq_n_s8(int8x16_t a, const int b) {
  vint16m2_t a_ext = __riscv_vsext_vf2_i16m2(a, 16);
  return __riscv_vnclip_wx_i8m1(a_ext, b, __RISCV_VXRM_RNU, 16);
}

FORCE_INLINE int16x8_t vrshrq_n_s16(int16x8_t a, const int b) {
  vint32m2_t a_ext = __riscv_vsext_vf2_i32m2(a, 8);
  return __riscv_vnclip_wx_i16m1(a_ext, b, __RISCV_VXRM_RNU, 8);
}

FORCE_INLINE int32x4_t vrshrq_n_s32(int32x4_t a, const int b) {
  vint64m2_t a_ext = __riscv_vsext_vf2_i64m2(a, 4);
  return __riscv_vnclip_wx_i32m1(a_ext, b, __RISCV_VXRM_RNU, 4);
}

FORCE_INLINE int64x2_t vrshrq_n_s64(int64x2_t a, const int b) {
  vint64m1_t sra = __riscv_vsra_vx_i64m1(a, b - 1, 2);
  vint64m1_t sra_round = __riscv_vadd_vv_i64m1(sra, __riscv_vand_vx_i64m1(sra, 1, 2), 2);
  return __riscv_vsra_vx_i64m1(sra_round, 1, 2);
}

FORCE_INLINE uint8x16_t vrshrq_n_u8(uint8x16_t a, const int b) {
  vuint16m2_t a_ext = __riscv_vzext_vf2_u16m2(a, 16);
  return __riscv_vnclipu_wx_u8m1(a_ext, b, __RISCV_VXRM_RNU, 16);
}

FORCE_INLINE uint16x8_t vrshrq_n_u16(uint16x8_t a, const int b) {
  vuint32m2_t a_ext = __riscv_vzext_vf2_u32m2(a, 8);
  return __riscv_vnclipu_wx_u16m1(a_ext, b, __RISCV_VXRM_RNU, 8);
}

FORCE_INLINE uint32x4_t vrshrq_n_u32(uint32x4_t a, const int b) {
  vuint64m2_t a_ext = __riscv_vzext_vf2_u64m2(a, 4);
  return __riscv_vnclipu_wx_u32m1(a_ext, b, __RISCV_VXRM_RNU, 4);
}

FORCE_INLINE uint64x2_t vrshrq_n_u64(uint64x2_t a, const int b) {
  vuint64m1_t srl = __riscv_vsrl_vx_u64m1(a, b - 1, 2);
  vuint64m1_t srl_round = __riscv_vadd_vv_u64m1(srl, __riscv_vand_vx_u64m1(srl, 1, 2), 2);
  return __riscv_vsrl_vx_u64m1(srl_round, 1, 2);
}

FORCE_INLINE int64_t vrshrd_n_s64(int64_t a, const int n) {
  int64_t round_const = 0;
  if (a & ((int64_t)1 << (n - 1))) {
    round_const = 1;
  }
  return ((a >> (n - 1)) + round_const) >> 1;
}

FORCE_INLINE uint64_t vrshrd_n_u64(uint64_t a, const int n) {
  uint64_t round_const = 0;
  if (a & ((uint64_t)1 << (n - 1))) {
    round_const = 1;
  }
  return ((a >> (n - 1)) + round_const) >> 1;
}

FORCE_INLINE int8x8_t vshrn_n_s16(int16x8_t a, const int b) {
  return __riscv_vreinterpret_v_u8m1_i8m1(
      __riscv_vnsrl_wx_u8m1(__riscv_vlmul_ext_v_u16m1_u16m2(__riscv_vreinterpret_v_i16m1_u16m1(a)), b, 8));
}

FORCE_INLINE int16x4_t vshrn_n_s32(int32x4_t a, const int b) {
  return __riscv_vreinterpret_v_u16m1_i16m1(
      __riscv_vnsrl_wx_u16m1(__riscv_vlmul_ext_v_u32m1_u32m2(__riscv_vreinterpret_v_i32m1_u32m1(a)), b, 4));
}

FORCE_INLINE int32x2_t vshrn_n_s64(int64x2_t a, const int b) {
  return __riscv_vreinterpret_v_u32m1_i32m1(
      __riscv_vnsrl_wx_u32m1(__riscv_vlmul_ext_v_u64m1_u64m2(__riscv_vreinterpret_v_i64m1_u64m1(a)), b, 2));
}

FORCE_INLINE uint8x8_t vshrn_n_u16(uint16x8_t a, const int b) {
  return __riscv_vnsrl_wx_u8m1(__riscv_vlmul_ext_v_u16m1_u16m2(a), b, 8);
}

FORCE_INLINE uint16x4_t vshrn_n_u32(uint32x4_t a, const int b) {
  return __riscv_vnsrl_wx_u16m1(__riscv_vlmul_ext_v_u32m1_u32m2(a), b, 4);
}

FORCE_INLINE uint32x2_t vshrn_n_u64(uint64x2_t a, const int b) {
  return __riscv_vnsrl_wx_u32m1(__riscv_vlmul_ext_v_u64m1_u64m2(a), b, 2);
}

FORCE_INLINE int8x16_t vshrn_high_n_s16(int8x8_t r, int16x8_t a, const int n) {
  vint8m1_t shrn_n = __riscv_vreinterpret_v_u8m1_i8m1(
      __riscv_vnsrl_wx_u8m1(__riscv_vlmul_ext_v_u16m1_u16m2(__riscv_vreinterpret_v_i16m1_u16m1(a)), n, 8));
  return __riscv_vslideup_vx_i8m1(r, shrn_n, 8, 16);
}

FORCE_INLINE int16x8_t vshrn_high_n_s32(int16x4_t r, int32x4_t a, const int n) {
  vint16m1_t shrn_n = __riscv_vreinterpret_v_u16m1_i16m1(
      __riscv_vnsrl_wx_u16m1(__riscv_vlmul_ext_v_u32m1_u32m2(__riscv_vreinterpret_v_i32m1_u32m1(a)), n, 4));
  return __riscv_vslideup_vx_i16m1(r, shrn_n, 4, 8);
}

FORCE_INLINE int32x4_t vshrn_high_n_s64(int32x2_t r, int64x2_t a, const int n) {
  vint32m1_t shrn_n = __riscv_vreinterpret_v_u32m1_i32m1(
      __riscv_vnsrl_wx_u32m1(__riscv_vlmul_ext_v_u64m1_u64m2(__riscv_vreinterpret_v_i64m1_u64m1(a)), n, 2));
  return __riscv_vslideup_vx_i32m1(r, shrn_n, 2, 4);
}

FORCE_INLINE uint8x16_t vshrn_high_n_u16(uint8x8_t r, uint16x8_t a, const int n) {
  vuint8m1_t shrn_n = __riscv_vnsrl_wx_u8m1(__riscv_vlmul_ext_v_u16m1_u16m2(a), n, 8);
  return __riscv_vslideup_vx_u8m1(r, shrn_n, 8, 16);
}

FORCE_INLINE uint16x8_t vshrn_high_n_u32(uint16x4_t r, uint32x4_t a, const int n) {
  vuint16m1_t shrn_n = __riscv_vnsrl_wx_u16m1(__riscv_vlmul_ext_v_u32m1_u32m2(a), n, 4);
  return __riscv_vslideup_vx_u16m1(r, shrn_n, 4, 8);
}

FORCE_INLINE uint32x4_t vshrn_high_n_u64(uint32x2_t r, uint64x2_t a, const int n) {
  vuint32m1_t shrn_n = __riscv_vnsrl_wx_u32m1(__riscv_vlmul_ext_v_u64m1_u64m2(a), n, 2);
  return __riscv_vslideup_vx_u32m1(r, shrn_n, 2, 4);
}

FORCE_INLINE int8x8_t vrshrn_n_s16(int16x8_t a, const int b) {
  vuint16m1_t a_round = __riscv_vadd_vx_u16m1(__riscv_vreinterpret_v_i16m1_u16m1(a), 1 << (b - 1), 8);
  return __riscv_vreinterpret_v_u8m1_i8m1(__riscv_vnsrl_wx_u8m1(__riscv_vlmul_ext_v_u16m1_u16m2(a_round), b, 8));
}

FORCE_INLINE int16x4_t vrshrn_n_s32(int32x4_t a, const int b) {
  vuint32m1_t a_round = __riscv_vadd_vx_u32m1(__riscv_vreinterpret_v_i32m1_u32m1(a), 1 << (b - 1), 4);
  return __riscv_vreinterpret_v_u16m1_i16m1(__riscv_vnsrl_wx_u16m1(__riscv_vlmul_ext_v_u32m1_u32m2(a_round), b, 4));
}

FORCE_INLINE int32x2_t vrshrn_n_s64(int64x2_t a, const int b) {
  vint64m1_t sra = __riscv_vsra_vx_i64m1(a, b - 1, 2);
  vint64m1_t sra_round = __riscv_vadd_vv_i64m1(sra, __riscv_vand_vx_i64m1(sra, 1, 2), 2);
  return __riscv_vnsra_wx_i32m1(__riscv_vlmul_ext_v_i64m1_i64m2(sra_round), 1, 2);
}

FORCE_INLINE uint8x8_t vrshrn_n_u16(uint16x8_t a, const int b) {
  vuint16m1_t a_round = __riscv_vadd_vx_u16m1(a, 1 << (b - 1), 8);
  return __riscv_vnsrl_wx_u8m1(__riscv_vlmul_ext_v_u16m1_u16m2(a_round), b, 8);
}

FORCE_INLINE uint16x4_t vrshrn_n_u32(uint32x4_t a, const int b) {
  vuint32m1_t a_round = __riscv_vadd_vx_u32m1(a, 1 << (b - 1), 4);
  return __riscv_vnsrl_wx_u16m1(__riscv_vlmul_ext_v_u32m1_u32m2(a_round), b, 4);
}

FORCE_INLINE uint32x2_t vrshrn_n_u64(uint64x2_t a, const int b) {
  vuint64m1_t srl = __riscv_vsrl_vx_u64m1(a, b - 1, 2);
  vuint64m1_t srl_round = __riscv_vadd_vv_u64m1(srl, __riscv_vand_vx_u64m1(srl, 1, 2), 2);
  return __riscv_vnsrl_wx_u32m1(__riscv_vlmul_ext_v_u64m1_u64m2(srl_round), 1, 2);
}

FORCE_INLINE int8x16_t vrshrn_high_n_s16(int8x8_t r, int16x8_t a, const int n) {
  vuint16m1_t a_round = __riscv_vadd_vx_u16m1(__riscv_vreinterpret_v_i16m1_u16m1(a), 1 << (n - 1), 8);
  vint8m1_t vrshrn =
      __riscv_vreinterpret_v_u8m1_i8m1(__riscv_vnsrl_wx_u8m1(__riscv_vlmul_ext_v_u16m1_u16m2(a_round), n, 8));
  return __riscv_vslideup_vx_i8m1(r, vrshrn, 8, 16);
}

FORCE_INLINE int16x8_t vrshrn_high_n_s32(int16x4_t r, int32x4_t a, const int n) {
  vuint32m1_t a_round = __riscv_vadd_vx_u32m1(__riscv_vreinterpret_v_i32m1_u32m1(a), 1 << (n - 1), 4);
  vint16m1_t vrshrn =
      __riscv_vreinterpret_v_u16m1_i16m1(__riscv_vnsrl_wx_u16m1(__riscv_vlmul_ext_v_u32m1_u32m2(a_round), n, 4));
  return __riscv_vslideup_vx_i16m1(r, vrshrn, 4, 8);
}

FORCE_INLINE int32x4_t vrshrn_high_n_s64(int32x2_t r, int64x2_t a, const int n) {
  vint64m1_t sra = __riscv_vsra_vx_i64m1(a, n - 1, 2);
  vint64m1_t sra_round = __riscv_vadd_vv_i64m1(sra, __riscv_vand_vx_i64m1(sra, 1, 2), 2);
  vint32m1_t vrshrn = __riscv_vnsra_wx_i32m1(__riscv_vlmul_ext_v_i64m1_i64m2(sra_round), 1, 2);
  return __riscv_vslideup_vx_i32m1(r, vrshrn, 2, 4);
}

FORCE_INLINE uint8x16_t vrshrn_high_n_u16(uint8x8_t r, uint16x8_t a, const int n) {
  vuint16m1_t a_round = __riscv_vadd_vx_u16m1(a, 1 << (n - 1), 8);
  vuint8m1_t vrshrn = __riscv_vnsrl_wx_u8m1(__riscv_vlmul_ext_v_u16m1_u16m2(a_round), n, 8);
  return __riscv_vslideup_vx_u8m1(r, vrshrn, 8, 16);
}

FORCE_INLINE uint16x8_t vrshrn_high_n_u32(uint16x4_t r, uint32x4_t a, const int n) {
  vuint32m1_t a_round = __riscv_vadd_vx_u32m1(a, 1 << (n - 1), 4);
  vuint16m1_t vrshrn = __riscv_vnsrl_wx_u16m1(__riscv_vlmul_ext_v_u32m1_u32m2(a_round), n, 4);
  return __riscv_vslideup_vx_u16m1(r, vrshrn, 4, 8);
}

FORCE_INLINE uint32x4_t vrshrn_high_n_u64(uint32x2_t r, uint64x2_t a, const int n) {
  vuint64m1_t srl = __riscv_vsrl_vx_u64m1(a, n - 1, 2);
  vuint64m1_t srl_round = __riscv_vadd_vv_u64m1(srl, __riscv_vand_vx_u64m1(srl, 1, 2), 2);
  vuint32m1_t vrshrn = __riscv_vnsrl_wx_u32m1(__riscv_vlmul_ext_v_u64m1_u64m2(srl_round), 1, 2);
  return __riscv_vslideup_vx_u32m1(r, vrshrn, 2, 4);
}

FORCE_INLINE int8x8_t vqshrn_n_s16(int16x8_t a, const int b) {
  return __riscv_vnclip_wx_i8m1(__riscv_vlmul_ext_v_i16m1_i16m2(a), b, __RISCV_VXRM_RDN, 8);
}

FORCE_INLINE int16x4_t vqshrn_n_s32(int32x4_t a, const int b) {
  return __riscv_vnclip_wx_i16m1(__riscv_vlmul_ext_v_i32m1_i32m2(a), b, __RISCV_VXRM_RDN, 4);
}

FORCE_INLINE int32x2_t vqshrn_n_s64(int64x2_t a, const int b) {
  return __riscv_vnclip_wx_i32m1(__riscv_vlmul_ext_v_i64m1_i64m2(a), b, __RISCV_VXRM_RDN, 2);
}

FORCE_INLINE uint8x8_t vqshrn_n_u16(uint16x8_t a, const int b) {
  return __riscv_vnclipu_wx_u8m1(__riscv_vlmul_ext_v_u16m1_u16m2(a), b, __RISCV_VXRM_RDN, 8);
}

FORCE_INLINE uint16x4_t vqshrn_n_u32(uint32x4_t a, const int b) {
  return __riscv_vnclipu_wx_u16m1(__riscv_vlmul_ext_v_u32m1_u32m2(a), b, __RISCV_VXRM_RDN, 4);
}

FORCE_INLINE uint32x2_t vqshrn_n_u64(uint64x2_t a, const int b) {
  return __riscv_vnclipu_wx_u32m1(__riscv_vlmul_ext_v_u64m1_u64m2(a), b, __RISCV_VXRM_RDN, 2);
}

FORCE_INLINE int8_t vqshrnh_n_s16(int16_t a, const int n) { return neon2rvv_saturate_int8(a >> n); }

FORCE_INLINE int16_t vqshrns_n_s32(int32_t a, const int n) { return neon2rvv_saturate_int16(a >> n); }

FORCE_INLINE int32_t vqshrnd_n_s64(int64_t a, const int n) { return neon2rvv_saturate_int32(a >> n); }

FORCE_INLINE uint8_t vqshrnh_n_u16(uint16_t a, const int n) { return neon2rvv_saturate_uint8(a >> n); }

FORCE_INLINE uint16_t vqshrns_n_u32(uint32_t a, const int n) { return neon2rvv_saturate_uint16(a >> n); }

FORCE_INLINE uint32_t vqshrnd_n_u64(uint64_t a, const int n) { return neon2rvv_saturate_uint32(a >> n); }

FORCE_INLINE int8x16_t vqshrn_high_n_s16(int8x8_t r, int16x8_t a, const int n) {
  vint8m1_t qshrn_n = __riscv_vnclip_wx_i8m1(__riscv_vlmul_ext_v_i16m1_i16m2(a), n, __RISCV_VXRM_RDN, 8);
  return __riscv_vslideup_vx_i8m1(r, qshrn_n, 8, 16);
}

FORCE_INLINE int16x8_t vqshrn_high_n_s32(int16x4_t r, int32x4_t a, const int n) {
  vint16m1_t qshrn_n = __riscv_vnclip_wx_i16m1(__riscv_vlmul_ext_v_i32m1_i32m2(a), n, __RISCV_VXRM_RDN, 4);
  return __riscv_vslideup_vx_i16m1(r, qshrn_n, 4, 8);
}

FORCE_INLINE int32x4_t vqshrn_high_n_s64(int32x2_t r, int64x2_t a, const int n) {
  vint32m1_t qshrn_n = __riscv_vnclip_wx_i32m1(__riscv_vlmul_ext_v_i64m1_i64m2(a), n, __RISCV_VXRM_RDN, 2);
  return __riscv_vslideup_vx_i32m1(r, qshrn_n, 2, 4);
}

FORCE_INLINE uint8x16_t vqshrn_high_n_u16(uint8x8_t r, uint16x8_t a, const int n) {
  vuint8m1_t qshrn_n = __riscv_vnclipu_wx_u8m1(__riscv_vlmul_ext_v_u16m1_u16m2(a), n, __RISCV_VXRM_RDN, 8);
  return __riscv_vslideup_vx_u8m1(r, qshrn_n, 8, 16);
}

FORCE_INLINE uint16x8_t vqshrn_high_n_u32(uint16x4_t r, uint32x4_t a, const int n) {
  vuint16m1_t qshrn_n = __riscv_vnclipu_wx_u16m1(__riscv_vlmul_ext_v_u32m1_u32m2(a), n, __RISCV_VXRM_RDN, 4);
  return __riscv_vslideup_vx_u16m1(r, qshrn_n, 4, 8);
}

FORCE_INLINE uint32x4_t vqshrn_high_n_u64(uint32x2_t r, uint64x2_t a, const int n) {
  vuint32m1_t qshrn_n = __riscv_vnclipu_wx_u32m1(__riscv_vlmul_ext_v_u64m1_u64m2(a), n, __RISCV_VXRM_RDN, 2);
  return __riscv_vslideup_vx_u32m1(r, qshrn_n, 2, 4);
}

FORCE_INLINE int8x8_t vqrshrn_n_s16(int16x8_t a, const int b) {
  return __riscv_vnclip_wx_i8m1(__riscv_vlmul_ext_v_i16m1_i16m2(a), b, __RISCV_VXRM_RNU, 8);
}

FORCE_INLINE int16x4_t vqrshrn_n_s32(int32x4_t a, const int b) {
  return __riscv_vnclip_wx_i16m1(__riscv_vlmul_ext_v_i32m1_i32m2(a), b, __RISCV_VXRM_RNU, 4);
}

FORCE_INLINE int32x2_t vqrshrn_n_s64(int64x2_t a, const int b) {
  return __riscv_vnclip_wx_i32m1(__riscv_vlmul_ext_v_i64m1_i64m2(a), b, __RISCV_VXRM_RNU, 2);
}

FORCE_INLINE uint8x8_t vqrshrn_n_u16(uint16x8_t a, const int b) {
  return __riscv_vnclipu_wx_u8m1(__riscv_vlmul_ext_v_u16m1_u16m2(a), b, __RISCV_VXRM_RNU, 8);
}

FORCE_INLINE uint16x4_t vqrshrn_n_u32(uint32x4_t a, const int b) {
  return __riscv_vnclipu_wx_u16m1(__riscv_vlmul_ext_v_u32m1_u32m2(a), b, __RISCV_VXRM_RNU, 4);
}

FORCE_INLINE uint32x2_t vqrshrn_n_u64(uint64x2_t a, const int b) {
  return __riscv_vnclipu_wx_u32m1(__riscv_vlmul_ext_v_u64m1_u64m2(a), b, __RISCV_VXRM_RNU, 2);
}

FORCE_INLINE int8_t vqrshrnh_n_s16(int16_t a, const int n) {
  int16_t round_const = 1 << (n - 1);
  return neon2rvv_saturate_int8((a + round_const) >> n);
}

FORCE_INLINE int16_t vqrshrns_n_s32(int32_t a, const int n) {
  int32_t round_const = 1 << (n - 1);
  return neon2rvv_saturate_int16((a + round_const) >> n);
}

FORCE_INLINE int32_t vqrshrnd_n_s64(int64_t a, const int n) {
  int64_t round_const = 0;
  if (a & ((int64_t)1 << (n - 1))) {
    round_const = 1;
  }
  return neon2rvv_saturate_int32(((a >> (n - 1)) + round_const) >> 1);
}

FORCE_INLINE uint8_t vqrshrnh_n_u16(uint16_t a, const int n) {
  uint16_t round_const = 1 << (n - 1);
  return neon2rvv_saturate_uint8((a + round_const) >> n);
}

FORCE_INLINE uint16_t vqrshrns_n_u32(uint32_t a, const int n) {
  uint32_t round_const = 1 << (n - 1);
  return neon2rvv_saturate_uint16(((uint64_t)a + round_const) >> n);
}

FORCE_INLINE uint32_t vqrshrnd_n_u64(uint64_t a, const int n) {
  uint64_t round_const = 0;
  if (a & ((uint64_t)1 << (n - 1))) {
    round_const = 1;
  }
  return neon2rvv_saturate_uint32(((a >> (n - 1)) + round_const) >> 1);
}

FORCE_INLINE int8x16_t vqrshrn_high_n_s16(int8x8_t r, int16x8_t a, const int n) {
  vint8m1_t vqrshrn = __riscv_vnclip_wx_i8m1(__riscv_vlmul_ext_v_i16m1_i16m2(a), n, __RISCV_VXRM_RNU, 8);
  return __riscv_vslideup_vx_i8m1(r, vqrshrn, 8, 16);
}

FORCE_INLINE int16x8_t vqrshrn_high_n_s32(int16x4_t r, int32x4_t a, const int n) {
  vint16m1_t vqrshrn = __riscv_vnclip_wx_i16m1(__riscv_vlmul_ext_v_i32m1_i32m2(a), n, __RISCV_VXRM_RNU, 4);
  return __riscv_vslideup_vx_i16m1(r, vqrshrn, 4, 8);
}

FORCE_INLINE int32x4_t vqrshrn_high_n_s64(int32x2_t r, int64x2_t a, const int n) {
  vint32m1_t vqrshrn = __riscv_vnclip_wx_i32m1(__riscv_vlmul_ext_v_i64m1_i64m2(a), n, __RISCV_VXRM_RNU, 2);
  return __riscv_vslideup_vx_i32m1(r, vqrshrn, 2, 4);
}

FORCE_INLINE uint8x16_t vqrshrn_high_n_u16(uint8x8_t r, uint16x8_t a, const int n) {
  vuint8m1_t vqrshrn = __riscv_vnclipu_wx_u8m1(__riscv_vlmul_ext_v_u16m1_u16m2(a), n, __RISCV_VXRM_RNU, 8);
  return __riscv_vslideup_vx_u8m1(r, vqrshrn, 8, 16);
}

FORCE_INLINE uint16x8_t vqrshrn_high_n_u32(uint16x4_t r, uint32x4_t a, const int n) {
  vuint16m1_t vqrshrn = __riscv_vnclipu_wx_u16m1(__riscv_vlmul_ext_v_u32m1_u32m2(a), n, __RISCV_VXRM_RNU, 4);
  return __riscv_vslideup_vx_u16m1(r, vqrshrn, 4, 8);
}

FORCE_INLINE uint32x4_t vqrshrn_high_n_u64(uint32x2_t r, uint64x2_t a, const int n) {
  vuint32m1_t vqrshrn = __riscv_vnclipu_wx_u32m1(__riscv_vlmul_ext_v_u64m1_u64m2(a), n, __RISCV_VXRM_RNU, 2);
  return __riscv_vslideup_vx_u32m1(r, vqrshrn, 2, 4);
}

FORCE_INLINE uint8x8_t vqshrun_n_s16(int16x8_t a, const int b) {
  vint16m2_t a_eliminate_neg = __riscv_vlmul_ext_v_i16m1_i16m2(__riscv_vmax_vx_i16m1(a, 0, 8));
  return __riscv_vnclipu_wx_u8m1(__riscv_vreinterpret_v_i16m2_u16m2(a_eliminate_neg), b, __RISCV_VXRM_RDN, 8);
}

FORCE_INLINE uint16x4_t vqshrun_n_s32(int32x4_t a, const int b) {
  vint32m2_t a_eliminate_neg = __riscv_vlmul_ext_v_i32m1_i32m2(__riscv_vmax_vx_i32m1(a, 0, 4));
  return __riscv_vnclipu_wx_u16m1(__riscv_vreinterpret_v_i32m2_u32m2(a_eliminate_neg), b, __RISCV_VXRM_RDN, 4);
}

FORCE_INLINE uint32x2_t vqshrun_n_s64(int64x2_t a, const int b) {
  vint64m2_t a_eliminate_neg = __riscv_vlmul_ext_v_i64m1_i64m2(__riscv_vmax_vx_i64m1(a, 0, 2));
  return __riscv_vnclipu_wx_u32m1(__riscv_vreinterpret_v_i64m2_u64m2(a_eliminate_neg), b, __RISCV_VXRM_RDN, 2);
}

FORCE_INLINE uint8_t vqshrunh_n_s16(int16_t a, const int n) {
  int16_t tmp = a >> n;
  tmp = ~(tmp >> 15) & tmp;
  return neon2rvv_saturate_uint8(tmp);
}

FORCE_INLINE uint16_t vqshruns_n_s32(int32_t a, const int n) {
  int32_t tmp = a >> n;
  tmp = ~(tmp >> 31) & tmp;
  return neon2rvv_saturate_uint16(tmp);
}

FORCE_INLINE uint32_t vqshrund_n_s64(int64_t a, const int n) {
  int64_t tmp = a >> n;
  tmp = ~(tmp >> 63) & tmp;
  return neon2rvv_saturate_uint32(tmp);
}

FORCE_INLINE uint8x16_t vqshrun_high_n_s16(uint8x8_t r, int16x8_t a, const int n) {
  vint16m2_t a_eliminate_neg = __riscv_vlmul_ext_v_i16m1_i16m2(__riscv_vmax_vx_i16m1(a, 0, 8));
  vuint8m1_t vqshrun =
      __riscv_vnclipu_wx_u8m1(__riscv_vreinterpret_v_i16m2_u16m2(a_eliminate_neg), n, __RISCV_VXRM_RDN, 8);
  return __riscv_vslideup_vx_u8m1(r, vqshrun, 8, 16);
}

FORCE_INLINE uint16x8_t vqshrun_high_n_s32(uint16x4_t r, int32x4_t a, const int n) {
  vint32m2_t a_eliminate_neg = __riscv_vlmul_ext_v_i32m1_i32m2(__riscv_vmax_vx_i32m1(a, 0, 4));
  vuint16m1_t vqshrun =
      __riscv_vnclipu_wx_u16m1(__riscv_vreinterpret_v_i32m2_u32m2(a_eliminate_neg), n, __RISCV_VXRM_RDN, 4);
  return __riscv_vslideup_vx_u16m1(r, vqshrun, 4, 8);
}

FORCE_INLINE uint32x4_t vqshrun_high_n_s64(uint32x2_t r, int64x2_t a, const int n) {
  vint64m2_t a_eliminate_neg = __riscv_vlmul_ext_v_i64m1_i64m2(__riscv_vmax_vx_i64m1(a, 0, 2));
  vuint32m1_t vqshrun =
      __riscv_vnclipu_wx_u32m1(__riscv_vreinterpret_v_i64m2_u64m2(a_eliminate_neg), n, __RISCV_VXRM_RDN, 2);
  return __riscv_vslideup_vx_u32m1(r, vqshrun, 2, 4);
}

FORCE_INLINE uint8x8_t vqrshrun_n_s16(int16x8_t a, const int b) {
  vint16m2_t a_eliminate_neg = __riscv_vlmul_ext_v_i16m1_i16m2(__riscv_vmax_vx_i16m1(a, 0, 8));
  return __riscv_vnclipu_wx_u8m1(__riscv_vreinterpret_v_i16m2_u16m2(a_eliminate_neg), b, __RISCV_VXRM_RNU, 8);
}

FORCE_INLINE uint16x4_t vqrshrun_n_s32(int32x4_t a, const int b) {
  vint32m2_t a_eliminate_neg = __riscv_vlmul_ext_v_i32m1_i32m2(__riscv_vmax_vx_i32m1(a, 0, 4));
  return __riscv_vnclipu_wx_u16m1(__riscv_vreinterpret_v_i32m2_u32m2(a_eliminate_neg), b, __RISCV_VXRM_RNU, 4);
}

FORCE_INLINE uint32x2_t vqrshrun_n_s64(int64x2_t a, const int b) {
  vint64m2_t a_eliminate_neg = __riscv_vlmul_ext_v_i64m1_i64m2(__riscv_vmax_vx_i64m1(a, 0, 2));
  return __riscv_vnclipu_wx_u32m1(__riscv_vreinterpret_v_i64m2_u64m2(a_eliminate_neg), b, __RISCV_VXRM_RNU, 2);
}

FORCE_INLINE uint8_t vqrshrunh_n_s16(int16_t a, const int n) {
  int16_t round_const = 1 << (n - 1);
  int16_t tmp = (a + round_const) >> n;
  tmp = ~(tmp >> 15) & tmp;
  return neon2rvv_saturate_uint8(tmp);
}

FORCE_INLINE uint16_t vqrshruns_n_s32(int32_t a, const int n) {
  int32_t round_const = 1 << (n - 1);
  int32_t tmp = (a + round_const) >> n;
  tmp = ~(tmp >> 31) & tmp;
  return neon2rvv_saturate_uint16(tmp);
}

FORCE_INLINE uint32_t vqrshrund_n_s64(int64_t a, const int n) {
  int64_t tmp = a >> (n - 1);
  tmp = ~(tmp >> 63) & tmp;
  return neon2rvv_saturate_uint32((tmp + 1) >> 1);
}

FORCE_INLINE uint8x16_t vqrshrun_high_n_s16(uint8x8_t r, int16x8_t a, const int n) {
  vint16m2_t a_eliminate_neg = __riscv_vlmul_ext_v_i16m1_i16m2(__riscv_vmax_vx_i16m1(a, 0, 8));
  vuint8m1_t vqrshrun =
      __riscv_vnclipu_wx_u8m1(__riscv_vreinterpret_v_i16m2_u16m2(a_eliminate_neg), n, __RISCV_VXRM_RNU, 8);
  return __riscv_vslideup_vx_u8m1(r, vqrshrun, 8, 16);
}

FORCE_INLINE uint16x8_t vqrshrun_high_n_s32(uint16x4_t r, int32x4_t a, const int n) {
  vint32m2_t a_eliminate_neg = __riscv_vlmul_ext_v_i32m1_i32m2(__riscv_vmax_vx_i32m1(a, 0, 4));
  vuint16m1_t vqrshrun =
      __riscv_vnclipu_wx_u16m1(__riscv_vreinterpret_v_i32m2_u32m2(a_eliminate_neg), n, __RISCV_VXRM_RNU, 4);
  return __riscv_vslideup_vx_u16m1(r, vqrshrun, 4, 8);
}

FORCE_INLINE uint32x4_t vqrshrun_high_n_s64(uint32x2_t r, int64x2_t a, const int n) {
  vint64m2_t a_eliminate_neg = __riscv_vlmul_ext_v_i64m1_i64m2(__riscv_vmax_vx_i64m1(a, 0, 2));
  vuint32m1_t vqrshrun =
      __riscv_vnclipu_wx_u32m1(__riscv_vreinterpret_v_i64m2_u64m2(a_eliminate_neg), n, __RISCV_VXRM_RNU, 2);
  return __riscv_vslideup_vx_u32m1(r, vqrshrun, 2, 4);
}

FORCE_INLINE int8x8_t vshl_n_s8(int8x8_t a, const int b) { return __riscv_vsll_vx_i8m1(a, b, 8); }

FORCE_INLINE int16x4_t vshl_n_s16(int16x4_t a, const int b) { return __riscv_vsll_vx_i16m1(a, b, 4); }

FORCE_INLINE int32x2_t vshl_n_s32(int32x2_t a, const int b) { return __riscv_vsll_vx_i32m1(a, b, 2); }

FORCE_INLINE int64x1_t vshl_n_s64(int64x1_t a, const int b) { return __riscv_vsll_vx_i64m1(a, b, 1); }

FORCE_INLINE uint8x8_t vshl_n_u8(uint8x8_t a, const int b) { return __riscv_vsll_vx_u8m1(a, b, 8); }

FORCE_INLINE uint16x4_t vshl_n_u16(uint16x4_t a, const int b) { return __riscv_vsll_vx_u16m1(a, b, 4); }

FORCE_INLINE uint32x2_t vshl_n_u32(uint32x2_t a, const int b) { return __riscv_vsll_vx_u32m1(a, b, 2); }

FORCE_INLINE uint64x1_t vshl_n_u64(uint64x1_t a, const int b) { return __riscv_vsll_vx_u64m1(a, b, 1); }

FORCE_INLINE int8x16_t vshlq_n_s8(int8x16_t a, const int b) { return __riscv_vsll_vx_i8m1(a, b, 16); }

FORCE_INLINE int16x8_t vshlq_n_s16(int16x8_t a, const int b) { return __riscv_vsll_vx_i16m1(a, b, 8); }

FORCE_INLINE int32x4_t vshlq_n_s32(int32x4_t a, const int b) { return __riscv_vsll_vx_i32m1(a, b, 4); }

FORCE_INLINE int64x2_t vshlq_n_s64(int64x2_t a, const int b) { return __riscv_vsll_vx_i64m1(a, b, 2); }

FORCE_INLINE uint8x16_t vshlq_n_u8(uint8x16_t a, const int b) { return __riscv_vsll_vx_u8m1(a, b, 16); }

FORCE_INLINE uint16x8_t vshlq_n_u16(uint16x8_t a, const int b) { return __riscv_vsll_vx_u16m1(a, b, 8); }

FORCE_INLINE uint32x4_t vshlq_n_u32(uint32x4_t a, const int b) { return __riscv_vsll_vx_u32m1(a, b, 4); }

FORCE_INLINE uint64x2_t vshlq_n_u64(uint64x2_t a, const int b) { return __riscv_vsll_vx_u64m1(a, b, 2); }

FORCE_INLINE int64_t vshld_n_s64(int64_t a, const int n) { return a << n; }

FORCE_INLINE uint64_t vshld_n_u64(uint64_t a, const int n) { return a << n; }

FORCE_INLINE int8x8_t vqshl_n_s8(int8x8_t a, const int b) {
  vint16m2_t a_ext = __riscv_vsext_vf2_i16m2(a, 8);
  vint16m2_t a_s = __riscv_vsll_vx_i16m2(a_ext, b, 8);
  return __riscv_vnclip_wx_i8m1(a_s, 0, __RISCV_VXRM_RDN, 8);
}

FORCE_INLINE int16x4_t vqshl_n_s16(int16x4_t a, const int b) {
  vint32m2_t a_ext = __riscv_vsext_vf2_i32m2(a, 4);
  vint32m2_t a_s = __riscv_vsll_vx_i32m2(a_ext, b, 4);
  return __riscv_vnclip_wx_i16m1(a_s, 0, __RISCV_VXRM_RDN, 4);
}

FORCE_INLINE int32x2_t vqshl_n_s32(int32x2_t a, const int b) {
  vint64m2_t a_ext = __riscv_vsext_vf2_i64m2(a, 2);
  vint64m2_t a_s = __riscv_vsll_vx_i64m2(a_ext, b, 2);
  return __riscv_vnclip_wx_i32m1(a_s, 0, __RISCV_VXRM_RDN, 2);
}

FORCE_INLINE int64x1_t vqshl_n_s64(int64x1_t a, const int b) {
  vbool64_t mask_positive = __riscv_vmsgt_vx_i64m1_b64(a, 0, 1);
  vbool64_t mask_non_positive = __riscv_vmnot_m_b64(mask_positive, 1);
  vbool64_t gt_max = __riscv_vmsgt_vx_i64m1_b64(a, INT64_MAX >> b, 1);
  vbool64_t lt_min = __riscv_vmslt_vx_i64m1_b64(a, INT64_MIN >> b, 1);
  vbool64_t mask_sat_positive = __riscv_vmand_mm_b64(gt_max, mask_positive, 1);
  vbool64_t mask_sat_non_positive = __riscv_vmand_mm_b64(lt_min, mask_non_positive, 1);
  vint64m1_t shl = __riscv_vsll_vx_i64m1(a, b, 1);
  vint64m1_t shl_max = __riscv_vmerge_vxm_i64m1(shl, INT64_MAX, mask_sat_positive, 1);
  return __riscv_vmerge_vxm_i64m1(shl_max, INT64_MIN, mask_sat_non_positive, 1);
}

FORCE_INLINE uint8x8_t vqshl_n_u8(uint8x8_t a, const int b) {
  vuint16m2_t a_ext = __riscv_vzext_vf2_u16m2(a, 8);
  vuint16m2_t a_s = __riscv_vsll_vx_u16m2(a_ext, b, 8);
  return __riscv_vnclipu_wx_u8m1(a_s, 0, __RISCV_VXRM_RDN, 8);
}

FORCE_INLINE uint16x4_t vqshl_n_u16(uint16x4_t a, const int b) {
  vuint32m2_t a_ext = __riscv_vzext_vf2_u32m2(a, 4);
  vuint32m2_t a_s = __riscv_vsll_vx_u32m2(a_ext, b, 4);
  return __riscv_vnclipu_wx_u16m1(a_s, 0, __RISCV_VXRM_RDN, 4);
}

FORCE_INLINE uint32x2_t vqshl_n_u32(uint32x2_t a, const int b) {
  vuint64m2_t a_ext = __riscv_vzext_vf2_u64m2(a, 2);
  vuint64m2_t a_s = __riscv_vsll_vx_u64m2(a_ext, b, 2);
  return __riscv_vnclipu_wx_u32m1(a_s, 0, __RISCV_VXRM_RDN, 2);
}

FORCE_INLINE uint64x1_t vqshl_n_u64(uint64x1_t a, const int b) {
  vbool64_t mask_positive = __riscv_vmsgtu_vx_u64m1_b64(a, 0, 1);
  vbool64_t gt_max = __riscv_vmsgtu_vx_u64m1_b64(a, UINT64_MAX >> b, 1);
  vbool64_t mask_sat_positive = __riscv_vmand_mm_b64(gt_max, mask_positive, 1);
  vuint64m1_t shl = __riscv_vsll_vx_u64m1(a, b, 1);
  return __riscv_vmerge_vxm_u64m1(shl, UINT64_MAX, mask_sat_positive, 1);
}

FORCE_INLINE int8x16_t vqshlq_n_s8(int8x16_t a, const int b) {
  vint16m2_t a_ext = __riscv_vsext_vf2_i16m2(a, 16);
  vint16m2_t a_s = __riscv_vsll_vx_i16m2(a_ext, b, 16);
  return __riscv_vnclip_wx_i8m1(a_s, 0, __RISCV_VXRM_RDN, 16);
}

FORCE_INLINE int16x8_t vqshlq_n_s16(int16x8_t a, const int b) {
  vint32m2_t a_ext = __riscv_vsext_vf2_i32m2(a, 8);
  vint32m2_t a_s = __riscv_vsll_vx_i32m2(a_ext, b, 8);
  return __riscv_vnclip_wx_i16m1(a_s, 0, __RISCV_VXRM_RDN, 8);
}

FORCE_INLINE int32x4_t vqshlq_n_s32(int32x4_t a, const int b) {
  vint64m2_t a_ext = __riscv_vsext_vf2_i64m2(a, 4);
  vint64m2_t a_s = __riscv_vsll_vx_i64m2(a_ext, b, 4);
  return __riscv_vnclip_wx_i32m1(a_s, 0, __RISCV_VXRM_RDN, 4);
}

FORCE_INLINE int64x2_t vqshlq_n_s64(int64x2_t a, const int b) {
  vbool64_t mask_positive = __riscv_vmsgt_vx_i64m1_b64(a, 0, 2);
  vbool64_t mask_non_positive = __riscv_vmnot_m_b64(mask_positive, 2);
  vbool64_t gt_max = __riscv_vmsgt_vx_i64m1_b64(a, INT64_MAX >> b, 2);
  vbool64_t lt_min = __riscv_vmslt_vx_i64m1_b64(a, INT64_MIN >> b, 2);
  vbool64_t mask_sat_positive = __riscv_vmand_mm_b64(gt_max, mask_positive, 2);
  vbool64_t mask_sat_non_positive = __riscv_vmand_mm_b64(lt_min, mask_non_positive, 2);
  vint64m1_t shl = __riscv_vsll_vx_i64m1(a, b, 2);
  vint64m1_t shl_max = __riscv_vmerge_vxm_i64m1(shl, INT64_MAX, mask_sat_positive, 2);
  return __riscv_vmerge_vxm_i64m1(shl_max, INT64_MIN, mask_sat_non_positive, 2);
}

FORCE_INLINE uint8x16_t vqshlq_n_u8(uint8x16_t a, const int b) {
  vuint16m2_t a_ext = __riscv_vzext_vf2_u16m2(a, 16);
  vuint16m2_t a_s = __riscv_vsll_vx_u16m2(a_ext, b, 16);
  return __riscv_vnclipu_wx_u8m1(a_s, 0, __RISCV_VXRM_RDN, 16);
}

FORCE_INLINE uint16x8_t vqshlq_n_u16(uint16x8_t a, const int b) {
  vuint32m2_t a_ext = __riscv_vzext_vf2_u32m2(a, 8);
  vuint32m2_t a_s = __riscv_vsll_vx_u32m2(a_ext, b, 8);
  return __riscv_vnclipu_wx_u16m1(a_s, 0, __RISCV_VXRM_RDN, 8);
}

FORCE_INLINE uint32x4_t vqshlq_n_u32(uint32x4_t a, const int b) {
  vuint64m2_t a_ext = __riscv_vzext_vf2_u64m2(a, 4);
  vuint64m2_t a_s = __riscv_vsll_vx_u64m2(a_ext, b, 4);
  return __riscv_vnclipu_wx_u32m1(a_s, 0, __RISCV_VXRM_RDN, 4);
}

FORCE_INLINE uint64x2_t vqshlq_n_u64(uint64x2_t a, const int b) {
  vbool64_t mask_positive = __riscv_vmsgtu_vx_u64m1_b64(a, 0, 2);
  vbool64_t gt_max = __riscv_vmsgtu_vx_u64m1_b64(a, UINT64_MAX >> b, 2);
  vbool64_t mask_sat_positive = __riscv_vmand_mm_b64(gt_max, mask_positive, 2);
  vuint64m1_t shl = __riscv_vsll_vx_u64m1(a, b, 2);
  return __riscv_vmerge_vxm_u64m1(shl, UINT64_MAX, mask_sat_positive, 2);
}

FORCE_INLINE int8_t vqshlb_n_s8(int8_t a, const int n) { return neon2rvv_saturate_int8(a << n); }

FORCE_INLINE int16_t vqshlh_n_s16(int16_t a, const int n) { return neon2rvv_saturate_int16(a << n); }

FORCE_INLINE int32_t vqshls_n_s32(int32_t a, const int n) { return neon2rvv_saturate_int32((int64_t)a << n); }

FORCE_INLINE int64_t vqshld_n_s64(int64_t a, const int n) {
  if (a > 0) {
    if (a > (INT64_MAX >> n)) {
      return INT64_MAX;
    } else {
      return a << n;
    }
  }
  if (a < (INT64_MIN >> n)) {
    return INT64_MIN;
  }
  return a << n;
}

FORCE_INLINE uint8_t vqshlb_n_u8(uint8_t a, const int n) { return neon2rvv_saturate_uint8(a << n); }

FORCE_INLINE uint16_t vqshlh_n_u16(uint16_t a, const int n) { return neon2rvv_saturate_uint16(a << n); }

FORCE_INLINE uint32_t vqshls_n_u32(uint32_t a, const int n) { return neon2rvv_saturate_uint32((uint64_t)a << n); }

FORCE_INLINE uint64_t vqshld_n_u64(uint64_t a, const int n) {
  if (a > (UINT64_MAX >> n)) {
    return UINT64_MAX;
  }
  return a << n;
}

FORCE_INLINE uint8x8_t vqshlu_n_s8(int8x8_t a, const int b) {
  vint8m1_t a_non_neg = __riscv_vmax_vx_i8m1(a, 0, 8);
  vint16m2_t a_ext = __riscv_vsext_vf2_i16m2(a_non_neg, 16);
  vuint16m2_t a_s = __riscv_vreinterpret_v_i16m2_u16m2(__riscv_vsll_vx_i16m2(a_ext, b, 16));
  return __riscv_vnclipu_wx_u8m1(a_s, 0, __RISCV_VXRM_RDN, 16);
}

FORCE_INLINE uint16x4_t vqshlu_n_s16(int16x4_t a, const int b) {
  vint16m1_t a_non_neg = __riscv_vmax_vx_i16m1(a, 0, 4);
  vint32m2_t a_ext = __riscv_vsext_vf2_i32m2(a_non_neg, 8);
  vuint32m2_t a_s = __riscv_vreinterpret_v_i32m2_u32m2(__riscv_vsll_vx_i32m2(a_ext, b, 8));
  return __riscv_vnclipu_wx_u16m1(a_s, 0, __RISCV_VXRM_RDN, 8);
}

FORCE_INLINE uint32x2_t vqshlu_n_s32(int32x2_t a, const int b) {
  vint32m1_t a_non_neg = __riscv_vmax_vx_i32m1(a, 0, 2);
  vint64m2_t a_ext = __riscv_vsext_vf2_i64m2(a_non_neg, 4);
  vuint64m2_t a_s = __riscv_vreinterpret_v_i64m2_u64m2(__riscv_vsll_vx_i64m2(a_ext, b, 4));
  return __riscv_vnclipu_wx_u32m1(a_s, 0, __RISCV_VXRM_RDN, 4);
}

FORCE_INLINE uint64x1_t vqshlu_n_s64(int64x1_t a, const int b) {
  vuint64m1_t a_non_neg = __riscv_vreinterpret_v_i64m1_u64m1(__riscv_vmax_vx_i64m1(a, 0, 1));
  vbool64_t gt_mask = __riscv_vmsgtu_vx_u64m1_b64(a_non_neg, UINT64_MAX >> b, 1);
  vuint64m1_t shl = __riscv_vsll_vx_u64m1(a_non_neg, b, 1);
  return __riscv_vmerge_vxm_u64m1(shl, UINT64_MAX, gt_mask, 1);
}

FORCE_INLINE uint8x16_t vqshluq_n_s8(int8x16_t a, const int b) {
  vint8m1_t a_non_neg = __riscv_vmax_vx_i8m1(a, 0, 16);
  vint16m2_t a_ext = __riscv_vsext_vf2_i16m2(a_non_neg, 32);
  vuint16m2_t a_s = __riscv_vreinterpret_v_i16m2_u16m2(__riscv_vsll_vx_i16m2(a_ext, b, 32));
  return __riscv_vnclipu_wx_u8m1(a_s, 0, __RISCV_VXRM_RDN, 32);
}

FORCE_INLINE uint16x8_t vqshluq_n_s16(int16x8_t a, const int b) {
  vint16m1_t a_non_neg = __riscv_vmax_vx_i16m1(a, 0, 8);
  vint32m2_t a_ext = __riscv_vsext_vf2_i32m2(a_non_neg, 16);
  vuint32m2_t a_s = __riscv_vreinterpret_v_i32m2_u32m2(__riscv_vsll_vx_i32m2(a_ext, b, 16));
  return __riscv_vnclipu_wx_u16m1(a_s, 0, __RISCV_VXRM_RDN, 16);
}

FORCE_INLINE uint32x4_t vqshluq_n_s32(int32x4_t a, const int b) {
  vint32m1_t a_non_neg = __riscv_vmax_vx_i32m1(a, 0, 4);
  vint64m2_t a_ext = __riscv_vsext_vf2_i64m2(a_non_neg, 8);
  vuint64m2_t a_s = __riscv_vreinterpret_v_i64m2_u64m2(__riscv_vsll_vx_i64m2(a_ext, b, 8));
  return __riscv_vnclipu_wx_u32m1(a_s, 0, __RISCV_VXRM_RDN, 8);
}

FORCE_INLINE uint64x2_t vqshluq_n_s64(int64x2_t a, const int b) {
  vuint64m1_t a_non_neg = __riscv_vreinterpret_v_i64m1_u64m1(__riscv_vmax_vx_i64m1(a, 0, 2));
  vbool64_t gt_mask = __riscv_vmsgtu_vx_u64m1_b64(a_non_neg, UINT64_MAX >> b, 2);
  vuint64m1_t shl = __riscv_vsll_vx_u64m1(a_non_neg, b, 2);
  return __riscv_vmerge_vxm_u64m1(shl, UINT64_MAX, gt_mask, 2);
}

FORCE_INLINE uint8_t vqshlub_n_s8(int8_t a, const int n) {
  int16_t tmp = (int16_t)a << n;
  tmp = ~(tmp >> 15) & tmp;
  return neon2rvv_saturate_uint8(tmp);
}

FORCE_INLINE uint16_t vqshluh_n_s16(int16_t a, const int n) {
  int32_t tmp = (int32_t)a << n;
  tmp = ~(tmp >> 31) & tmp;
  return neon2rvv_saturate_uint16(tmp);
}

FORCE_INLINE uint32_t vqshlus_n_s32(int32_t a, const int n) {
  int64_t tmp = (int64_t)a << n;
  tmp = ~(tmp >> 63) & tmp;
  return neon2rvv_saturate_uint32(tmp);
}

FORCE_INLINE uint64_t vqshlud_n_s64(int64_t a, const int n) {
  if (a < 0) {
    return 0;
  }
  if ((uint64_t)a > (UINT64_MAX >> n)) {
    return UINT64_MAX;
  }
  return a << n;
}

FORCE_INLINE int16x8_t vshll_n_s8(int8x8_t a, const int b) {
  vint16m1_t a_ext = __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vsext_vf2_i16m2(a, 8));
  return __riscv_vsll_vx_i16m1(a_ext, b, 8);
}

FORCE_INLINE int32x4_t vshll_n_s16(int16x4_t a, const int b) {
  vint32m1_t a_ext = __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vsext_vf2_i32m2(a, 4));
  return __riscv_vsll_vx_i32m1(a_ext, b, 4);
}

FORCE_INLINE int64x2_t vshll_n_s32(int32x2_t a, const int b) {
  vint64m1_t a_ext = __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vsext_vf2_i64m2(a, 2));
  return __riscv_vsll_vx_i64m1(a_ext, b, 2);
}

FORCE_INLINE uint16x8_t vshll_n_u8(uint8x8_t a, const int b) {
  vuint16m1_t a_ext = __riscv_vlmul_trunc_v_u16m2_u16m1(__riscv_vzext_vf2_u16m2(a, 8));
  return __riscv_vsll_vx_u16m1(a_ext, b, 8);
}

FORCE_INLINE uint32x4_t vshll_n_u16(uint16x4_t a, const int b) {
  vuint32m1_t a_ext = __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vzext_vf2_u32m2(a, 4));
  return __riscv_vsll_vx_u32m1(a_ext, b, 4);
}

FORCE_INLINE uint64x2_t vshll_n_u32(uint32x2_t a, const int b) {
  vuint64m1_t a_ext = __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vzext_vf2_u64m2(a, 2));
  return __riscv_vsll_vx_u64m1(a_ext, b, 2);
}

FORCE_INLINE int16x8_t vshll_high_n_s8(int8x16_t a, const int n) {
  vint8m1_t _a = __riscv_vslidedown_vx_i8m1(a, 8, 16);
  vint16m1_t a_ext = __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vsext_vf2_i16m2(_a, 8));
  return __riscv_vsll_vx_i16m1(a_ext, n, 8);
}

FORCE_INLINE int32x4_t vshll_high_n_s16(int16x8_t a, const int n) {
  vint16m1_t _a = __riscv_vslidedown_vx_i16m1(a, 4, 8);
  vint32m1_t a_ext = __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vsext_vf2_i32m2(_a, 4));
  return __riscv_vsll_vx_i32m1(a_ext, n, 4);
}

FORCE_INLINE int64x2_t vshll_high_n_s32(int32x4_t a, const int n) {
  vint32m1_t _a = __riscv_vslidedown_vx_i32m1(a, 2, 4);
  vint64m1_t a_ext = __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vsext_vf2_i64m2(_a, 2));
  return __riscv_vsll_vx_i64m1(a_ext, n, 2);
}

FORCE_INLINE uint16x8_t vshll_high_n_u8(uint8x16_t a, const int n) {
  vuint8m1_t _a = __riscv_vslidedown_vx_u8m1(a, 8, 16);
  vuint16m1_t a_ext = __riscv_vlmul_trunc_v_u16m2_u16m1(__riscv_vzext_vf2_u16m2(_a, 8));
  return __riscv_vsll_vx_u16m1(a_ext, n, 8);
}

FORCE_INLINE uint32x4_t vshll_high_n_u16(uint16x8_t a, const int n) {
  vuint16m1_t _a = __riscv_vslidedown_vx_u16m1(a, 4, 8);
  vuint32m1_t a_ext = __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vzext_vf2_u32m2(_a, 4));
  return __riscv_vsll_vx_u32m1(a_ext, n, 4);
}

FORCE_INLINE uint64x2_t vshll_high_n_u32(uint32x4_t a, const int n) {
  vuint32m1_t _a = __riscv_vslidedown_vx_u32m1(a, 2, 4);
  vuint64m1_t a_ext = __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vzext_vf2_u64m2(_a, 2));
  return __riscv_vsll_vx_u64m1(a_ext, n, 2);
}

FORCE_INLINE int8x8_t vsra_n_s8(int8x8_t a, int8x8_t b, const int c) {
  const int imm = c - (c >> 3);
  return __riscv_vadd_vv_i8m1(a, __riscv_vsra_vx_i8m1(b, imm, 8), 8);
}

FORCE_INLINE int16x4_t vsra_n_s16(int16x4_t a, int16x4_t b, const int c) {
  const int imm = c - (c >> 4);
  return __riscv_vadd_vv_i16m1(a, __riscv_vsra_vx_i16m1(b, imm, 4), 4);
}

FORCE_INLINE int32x2_t vsra_n_s32(int32x2_t a, int32x2_t b, const int c) {
  const int imm = c - (c >> 5);
  return __riscv_vadd_vv_i32m1(a, __riscv_vsra_vx_i32m1(b, imm, 2), 2);
}

FORCE_INLINE int64x1_t vsra_n_s64(int64x1_t a, int64x1_t b, const int c) {
  const int imm = c - (c >> 6);
  return __riscv_vadd_vv_i64m1(a, __riscv_vsra_vx_i64m1(b, imm, 1), 1);
}

FORCE_INLINE uint8x8_t vsra_n_u8(uint8x8_t a, uint8x8_t b, const int c) {
  const int c_half = c >> 1;
  vuint8m1_t srl1 = __riscv_vsrl_vx_u8m1(b, c_half, 8);
  vuint8m1_t srl = __riscv_vsrl_vx_u8m1(srl1, c_half + (c & 0x1), 8);
  return __riscv_vadd_vv_u8m1(a, srl, 8);
}

FORCE_INLINE uint16x4_t vsra_n_u16(uint16x4_t a, uint16x4_t b, const int c) {
  const int c_half = c >> 1;
  vuint16m1_t srl1 = __riscv_vsrl_vx_u16m1(b, c_half, 4);
  vuint16m1_t srl = __riscv_vsrl_vx_u16m1(srl1, c_half + (c & 0x1), 4);
  return __riscv_vadd_vv_u16m1(a, srl, 4);
}

FORCE_INLINE uint32x2_t vsra_n_u32(uint32x2_t a, uint32x2_t b, const int c) {
  const int c_half = c >> 1;
  vuint32m1_t srl1 = __riscv_vsrl_vx_u32m1(b, c_half, 2);
  vuint32m1_t srl = __riscv_vsrl_vx_u32m1(srl1, c_half + (c & 0x1), 2);
  return __riscv_vadd_vv_u32m1(a, srl, 2);
}

FORCE_INLINE uint64x1_t vsra_n_u64(uint64x1_t a, uint64x1_t b, const int c) {
  const int c_half = c >> 1;
  vuint64m1_t srl1 = __riscv_vsrl_vx_u64m1(b, c_half, 1);
  vuint64m1_t srl = __riscv_vsrl_vx_u64m1(srl1, c_half + (c & 0x1), 1);
  return __riscv_vadd_vv_u64m1(a, srl, 1);
}

FORCE_INLINE int8x16_t vsraq_n_s8(int8x16_t a, int8x16_t b, const int c) {
  const int imm = c - (c >> 3);
  return __riscv_vadd_vv_i8m1(a, __riscv_vsra_vx_i8m1(b, imm, 16), 16);
}

FORCE_INLINE int16x8_t vsraq_n_s16(int16x8_t a, int16x8_t b, const int c) {
  const int imm = c - (c >> 4);
  return __riscv_vadd_vv_i16m1(a, __riscv_vsra_vx_i16m1(b, imm, 8), 8);
}

FORCE_INLINE int32x4_t vsraq_n_s32(int32x4_t a, int32x4_t b, const int c) {
  const int imm = c - (c >> 5);
  return __riscv_vadd_vv_i32m1(a, __riscv_vsra_vx_i32m1(b, imm, 4), 4);
}

FORCE_INLINE int64x2_t vsraq_n_s64(int64x2_t a, int64x2_t b, const int c) {
  const int imm = c - (c >> 6);
  return __riscv_vadd_vv_i64m1(a, __riscv_vsra_vx_i64m1(b, imm, 2), 2);
}

FORCE_INLINE uint8x16_t vsraq_n_u8(uint8x16_t a, uint8x16_t b, const int c) {
  const int c_half = c >> 1;
  vuint8m1_t srl1 = __riscv_vsrl_vx_u8m1(b, c_half, 16);
  vuint8m1_t srl = __riscv_vsrl_vx_u8m1(srl1, c_half + (c & 0x1), 16);
  return __riscv_vadd_vv_u8m1(a, srl, 16);
}

FORCE_INLINE uint16x8_t vsraq_n_u16(uint16x8_t a, uint16x8_t b, const int c) {
  const int c_half = c >> 1;
  vuint16m1_t srl1 = __riscv_vsrl_vx_u16m1(b, c_half, 8);
  vuint16m1_t srl = __riscv_vsrl_vx_u16m1(srl1, c_half + (c & 0x1), 8);
  return __riscv_vadd_vv_u16m1(a, srl, 8);
}

FORCE_INLINE uint32x4_t vsraq_n_u32(uint32x4_t a, uint32x4_t b, const int c) {
  const int c_half = c >> 1;
  vuint32m1_t srl1 = __riscv_vsrl_vx_u32m1(b, c_half, 4);
  vuint32m1_t srl = __riscv_vsrl_vx_u32m1(srl1, c_half + (c & 0x1), 4);
  return __riscv_vadd_vv_u32m1(a, srl, 4);
}

FORCE_INLINE uint64x2_t vsraq_n_u64(uint64x2_t a, uint64x2_t b, const int c) {
  const int c_half = c >> 1;
  vuint64m1_t srl1 = __riscv_vsrl_vx_u64m1(b, c_half, 2);
  vuint64m1_t srl = __riscv_vsrl_vx_u64m1(srl1, c_half + (c & 0x1), 2);
  return __riscv_vadd_vv_u64m1(a, srl, 2);
}

FORCE_INLINE int64_t vsrad_n_s64(int64_t a, int64_t b, const int n) {
  if (n == 64) {
    if (b > 0) {
      return a;
    } else {
      return a - 1;
    }
  }
  return a + (b >> n);
}

FORCE_INLINE uint64_t vsrad_n_u64(uint64_t a, uint64_t b, const int n) {
  if (n == 64) {
    return a;
  }
  return a + (b >> n);
}

FORCE_INLINE int8x8_t vrsra_n_s8(int8x8_t a, int8x8_t b, const int c) {
  vint16m2_t b_w = __riscv_vsext_vf2_i16m2(b, 8);
  vint8m1_t b_rshr = __riscv_vnclip_wx_i8m1(b_w, c, __RISCV_VXRM_RNU, 8);
  return __riscv_vadd_vv_i8m1(a, b_rshr, 8);
}

FORCE_INLINE int16x4_t vrsra_n_s16(int16x4_t a, int16x4_t b, const int c) {
  vint32m2_t b_w = __riscv_vsext_vf2_i32m2(b, 4);
  vint16m1_t b_rshr = __riscv_vnclip_wx_i16m1(b_w, c, __RISCV_VXRM_RNU, 4);
  return __riscv_vadd_vv_i16m1(a, b_rshr, 4);
}

FORCE_INLINE int32x2_t vrsra_n_s32(int32x2_t a, int32x2_t b, const int c) {
  vint64m2_t b_w = __riscv_vsext_vf2_i64m2(b, 2);
  vint32m1_t b_rshr = __riscv_vnclip_wx_i32m1(b_w, c, __RISCV_VXRM_RNU, 2);
  return __riscv_vadd_vv_i32m1(a, b_rshr, 2);
}

FORCE_INLINE int64x1_t vrsra_n_s64(int64x1_t a, int64x1_t b, const int c) {
  vint64m1_t shr = __riscv_vsra_vx_i64m1(b, c - 1, 1);
  vint64m1_t rshr = __riscv_vadd_vx_i64m1(shr, 1, 1);
  vint64m1_t b_rshr = __riscv_vsra_vx_i64m1(rshr, 1, 1);
  return __riscv_vadd_vv_i64m1(a, b_rshr, 1);
}

FORCE_INLINE uint8x8_t vrsra_n_u8(uint8x8_t a, uint8x8_t b, const int c) {
  vuint16m2_t b_w = __riscv_vzext_vf2_u16m2(b, 8);
  vuint8m1_t b_rshr = __riscv_vnclipu_wx_u8m1(b_w, c, __RISCV_VXRM_RNU, 8);
  return __riscv_vadd_vv_u8m1(a, b_rshr, 8);
}

FORCE_INLINE uint16x4_t vrsra_n_u16(uint16x4_t a, uint16x4_t b, const int c) {
  vuint32m2_t b_w = __riscv_vzext_vf2_u32m2(b, 4);
  vuint16m1_t b_rshr = __riscv_vnclipu_wx_u16m1(b_w, c, __RISCV_VXRM_RNU, 4);
  return __riscv_vadd_vv_u16m1(a, b_rshr, 4);
}

FORCE_INLINE uint32x2_t vrsra_n_u32(uint32x2_t a, uint32x2_t b, const int c) {
  vuint64m2_t b_w = __riscv_vzext_vf2_u64m2(b, 2);
  vuint32m1_t b_rshr = __riscv_vnclipu_wx_u32m1(b_w, c, __RISCV_VXRM_RNU, 2);
  return __riscv_vadd_vv_u32m1(a, b_rshr, 2);
}

FORCE_INLINE uint64x1_t vrsra_n_u64(uint64x1_t a, uint64x1_t b, const int c) {
  vuint64m1_t shr = __riscv_vsrl_vx_u64m1(b, c - 1, 1);
  vuint64m1_t rshr = __riscv_vadd_vx_u64m1(shr, 1, 1);
  vuint64m1_t b_rshr = __riscv_vsrl_vx_u64m1(rshr, 1, 1);
  return __riscv_vadd_vv_u64m1(a, b_rshr, 1);
}

FORCE_INLINE int8x16_t vrsraq_n_s8(int8x16_t a, int8x16_t b, const int c) {
  vint16m2_t b_w = __riscv_vsext_vf2_i16m2(b, 16);
  vint8m1_t b_rshr = __riscv_vnclip_wx_i8m1(b_w, c, __RISCV_VXRM_RNU, 16);
  return __riscv_vadd_vv_i8m1(a, b_rshr, 16);
}

FORCE_INLINE int16x8_t vrsraq_n_s16(int16x8_t a, int16x8_t b, const int c) {
  vint32m2_t b_w = __riscv_vsext_vf2_i32m2(b, 8);
  vint16m1_t b_rshr = __riscv_vnclip_wx_i16m1(b_w, c, __RISCV_VXRM_RNU, 8);
  return __riscv_vadd_vv_i16m1(a, b_rshr, 8);
}

FORCE_INLINE int32x4_t vrsraq_n_s32(int32x4_t a, int32x4_t b, const int c) {
  vint64m2_t b_w = __riscv_vsext_vf2_i64m2(b, 4);
  vint32m1_t b_rshr = __riscv_vnclip_wx_i32m1(b_w, c, __RISCV_VXRM_RNU, 4);
  return __riscv_vadd_vv_i32m1(a, b_rshr, 4);
}

FORCE_INLINE int64x2_t vrsraq_n_s64(int64x2_t a, int64x2_t b, const int c) {
  vint64m1_t shr = __riscv_vsra_vx_i64m1(b, c - 1, 2);
  vint64m1_t rshr = __riscv_vadd_vx_i64m1(shr, 1, 2);
  vint64m1_t b_rshr = __riscv_vsra_vx_i64m1(rshr, 1, 2);
  return __riscv_vadd_vv_i64m1(a, b_rshr, 2);
}

FORCE_INLINE uint8x16_t vrsraq_n_u8(uint8x16_t a, uint8x16_t b, const int c) {
  vuint16m2_t b_w = __riscv_vzext_vf2_u16m2(b, 16);
  vuint8m1_t b_rshr = __riscv_vnclipu_wx_u8m1(b_w, c, __RISCV_VXRM_RNU, 16);
  return __riscv_vadd_vv_u8m1(a, b_rshr, 16);
}

FORCE_INLINE uint16x8_t vrsraq_n_u16(uint16x8_t a, uint16x8_t b, const int c) {
  vuint32m2_t b_w = __riscv_vzext_vf2_u32m2(b, 8);
  vuint16m1_t b_rshr = __riscv_vnclipu_wx_u16m1(b_w, c, __RISCV_VXRM_RNU, 8);
  return __riscv_vadd_vv_u16m1(a, b_rshr, 8);
}

FORCE_INLINE uint32x4_t vrsraq_n_u32(uint32x4_t a, uint32x4_t b, const int c) {
  vuint64m2_t b_w = __riscv_vzext_vf2_u64m2(b, 4);
  vuint32m1_t b_rshr = __riscv_vnclipu_wx_u32m1(b_w, c, __RISCV_VXRM_RNU, 4);
  return __riscv_vadd_vv_u32m1(a, b_rshr, 4);
}

FORCE_INLINE uint64x2_t vrsraq_n_u64(uint64x2_t a, uint64x2_t b, const int c) {
  vuint64m1_t shr = __riscv_vsrl_vx_u64m1(b, c - 1, 2);
  vuint64m1_t rshr = __riscv_vadd_vx_u64m1(shr, 1, 2);
  vuint64m1_t b_rshr = __riscv_vsrl_vx_u64m1(rshr, 1, 2);
  return __riscv_vadd_vv_u64m1(a, b_rshr, 2);
}

FORCE_INLINE int64_t vrsrad_n_s64(int64_t a, int64_t b, const int n) { return a + (((b >> (n - 1)) + 1) >> 1); }

FORCE_INLINE uint64_t vrsrad_n_u64(uint64_t a, uint64_t b, const int n) { return a + (((b >> (n - 1)) + 1) >> 1); }

FORCE_INLINE int8x8_t vsri_n_s8(int8x8_t a, int8x8_t b, const int c) {
  uint8_t mask = (uint64_t)UINT8_MAX >> c;
  vint8m1_t high = __riscv_vand_vx_i8m1(a, ~mask, 8);
  vint8m1_t low_unmasked = __riscv_vsra_vx_i8m1(b, c, 8);
  vint8m1_t low = __riscv_vand_vx_i8m1(low_unmasked, mask, 8);
  return __riscv_vor_vv_i8m1(high, low, 8);
}

FORCE_INLINE int16x4_t vsri_n_s16(int16x4_t a, int16x4_t b, const int c) {
  uint16_t mask = (uint64_t)UINT16_MAX >> c;
  vint16m1_t high = __riscv_vand_vx_i16m1(a, ~mask, 4);
  vint16m1_t low_unmasked = __riscv_vsra_vx_i16m1(b, c, 4);
  vint16m1_t low = __riscv_vand_vx_i16m1(low_unmasked, mask, 4);
  return __riscv_vor_vv_i16m1(high, low, 4);
}

FORCE_INLINE int32x2_t vsri_n_s32(int32x2_t a, int32x2_t b, const int c) {
  uint32_t mask = (uint64_t)UINT32_MAX >> c;
  vint32m1_t high = __riscv_vand_vx_i32m1(a, ~mask, 2);
  vint32m1_t low_unmasked = __riscv_vsra_vx_i32m1(b, c, 2);
  vint32m1_t low = __riscv_vand_vx_i32m1(low_unmasked, mask, 2);
  return __riscv_vor_vv_i32m1(high, low, 2);
}

FORCE_INLINE int64x1_t vsri_n_s64(int64x1_t a, int64x1_t b, const int c) {
  uint64_t mask = (c == 64) ? 0 : UINT64_MAX >> c;
  vint64m1_t high = __riscv_vand_vx_i64m1(a, ~mask, 1);
  vint64m1_t low_unmasked = __riscv_vsra_vx_i64m1(b, c, 1);
  vint64m1_t low = __riscv_vand_vx_i64m1(low_unmasked, mask, 1);
  return __riscv_vor_vv_i64m1(high, low, 1);
}

FORCE_INLINE uint8x8_t vsri_n_u8(uint8x8_t a, uint8x8_t b, const int c) {
  uint8_t mask = (uint64_t)UINT8_MAX >> c;
  vuint8m1_t high = __riscv_vand_vx_u8m1(a, ~mask, 8);
  vuint8m1_t low_unmasked = __riscv_vsrl_vx_u8m1(b, c, 8);
  vuint8m1_t low = __riscv_vand_vx_u8m1(low_unmasked, mask, 8);
  return __riscv_vor_vv_u8m1(high, low, 8);
}

FORCE_INLINE uint16x4_t vsri_n_u16(uint16x4_t a, uint16x4_t b, const int c) {
  uint16_t mask = (uint64_t)UINT16_MAX >> c;
  vuint16m1_t high = __riscv_vand_vx_u16m1(a, ~mask, 4);
  vuint16m1_t low_unmasked = __riscv_vsrl_vx_u16m1(b, c, 4);
  vuint16m1_t low = __riscv_vand_vx_u16m1(low_unmasked, mask, 4);
  return __riscv_vor_vv_u16m1(high, low, 4);
}

FORCE_INLINE uint32x2_t vsri_n_u32(uint32x2_t a, uint32x2_t b, const int c) {
  uint32_t mask = (uint64_t)UINT32_MAX >> c;
  vuint32m1_t high = __riscv_vand_vx_u32m1(a, ~mask, 2);
  vuint32m1_t low_unmasked = __riscv_vsrl_vx_u32m1(b, c, 2);
  vuint32m1_t low = __riscv_vand_vx_u32m1(low_unmasked, mask, 2);
  return __riscv_vor_vv_u32m1(high, low, 2);
}

FORCE_INLINE uint64x1_t vsri_n_u64(uint64x1_t a, uint64x1_t b, const int c) {
  uint64_t mask = (c == 64) ? 0 : UINT64_MAX >> c;
  vuint64m1_t high = __riscv_vand_vx_u64m1(a, ~mask, 1);
  vuint64m1_t low_unmasked = __riscv_vsrl_vx_u64m1(b, c, 1);
  vuint64m1_t low = __riscv_vand_vx_u64m1(low_unmasked, mask, 1);
  return __riscv_vor_vv_u64m1(high, low, 1);
}

FORCE_INLINE int8x16_t vsriq_n_s8(int8x16_t a, int8x16_t b, const int c) {
  uint8_t mask = (uint64_t)UINT8_MAX >> c;
  vint8m1_t high = __riscv_vand_vx_i8m1(a, ~mask, 16);
  vint8m1_t low_unmasked = __riscv_vsra_vx_i8m1(b, c, 16);
  vint8m1_t low = __riscv_vand_vx_i8m1(low_unmasked, mask, 16);
  return __riscv_vor_vv_i8m1(high, low, 16);
}

FORCE_INLINE int16x8_t vsriq_n_s16(int16x8_t a, int16x8_t b, const int c) {
  uint16_t mask = (uint64_t)UINT16_MAX >> c;
  vint16m1_t high = __riscv_vand_vx_i16m1(a, ~mask, 8);
  vint16m1_t low_unmasked = __riscv_vsra_vx_i16m1(b, c, 8);
  vint16m1_t low = __riscv_vand_vx_i16m1(low_unmasked, mask, 8);
  return __riscv_vor_vv_i16m1(high, low, 8);
}

FORCE_INLINE int32x4_t vsriq_n_s32(int32x4_t a, int32x4_t b, const int c) {
  uint32_t mask = (uint64_t)UINT32_MAX >> c;
  vint32m1_t high = __riscv_vand_vx_i32m1(a, ~mask, 4);
  vint32m1_t low_unmasked = __riscv_vsra_vx_i32m1(b, c, 4);
  vint32m1_t low = __riscv_vand_vx_i32m1(low_unmasked, mask, 4);
  return __riscv_vor_vv_i32m1(high, low, 4);
}

FORCE_INLINE int64x2_t vsriq_n_s64(int64x2_t a, int64x2_t b, const int c) {
  uint64_t mask = (c == 64) ? 0 : UINT64_MAX >> c;
  vint64m1_t high = __riscv_vand_vx_i64m1(a, ~mask, 2);
  vint64m1_t low_unmasked = __riscv_vsra_vx_i64m1(b, c, 2);
  vint64m1_t low = __riscv_vand_vx_i64m1(low_unmasked, mask, 2);
  return __riscv_vor_vv_i64m1(high, low, 2);
}

FORCE_INLINE uint8x16_t vsriq_n_u8(uint8x16_t a, uint8x16_t b, const int c) {
  uint8_t mask = (uint64_t)UINT8_MAX >> c;
  vuint8m1_t high = __riscv_vand_vx_u8m1(a, ~mask, 16);
  vuint8m1_t low_unmasked = __riscv_vsrl_vx_u8m1(b, c, 16);
  vuint8m1_t low = __riscv_vand_vx_u8m1(low_unmasked, mask, 16);
  return __riscv_vor_vv_u8m1(high, low, 16);
}

FORCE_INLINE uint16x8_t vsriq_n_u16(uint16x8_t a, uint16x8_t b, const int c) {
  uint16_t mask = (uint64_t)UINT16_MAX >> c;
  vuint16m1_t high = __riscv_vand_vx_u16m1(a, ~mask, 8);
  vuint16m1_t low_unmasked = __riscv_vsrl_vx_u16m1(b, c, 8);
  vuint16m1_t low = __riscv_vand_vx_u16m1(low_unmasked, mask, 8);
  return __riscv_vor_vv_u16m1(high, low, 8);
}

FORCE_INLINE uint32x4_t vsriq_n_u32(uint32x4_t a, uint32x4_t b, const int c) {
  uint32_t mask = (uint64_t)UINT32_MAX >> c;
  vuint32m1_t high = __riscv_vand_vx_u32m1(a, ~mask, 4);
  vuint32m1_t low_unmasked = __riscv_vsrl_vx_u32m1(b, c, 4);
  vuint32m1_t low = __riscv_vand_vx_u32m1(low_unmasked, mask, 4);
  return __riscv_vor_vv_u32m1(high, low, 4);
}

FORCE_INLINE uint64x2_t vsriq_n_u64(uint64x2_t a, uint64x2_t b, const int c) {
  uint64_t mask = (c == 64) ? 0 : UINT64_MAX >> c;
  vuint64m1_t high = __riscv_vand_vx_u64m1(a, ~mask, 2);
  vuint64m1_t low_unmasked = __riscv_vsrl_vx_u64m1(b, c, 2);
  vuint64m1_t low = __riscv_vand_vx_u64m1(low_unmasked, mask, 2);
  return __riscv_vor_vv_u64m1(high, low, 2);
}

// FORCE_INLINE poly64x1_t vsri_n_p64(poly64x1_t a, poly64x1_t b, const int n);

// FORCE_INLINE poly64x2_t vsriq_n_p64(poly64x2_t a, poly64x2_t b, const int n);

// FORCE_INLINE poly8x8_t vsri_n_p8(poly8x8_t a, poly8x8_t b, const int n);

// FORCE_INLINE poly8x16_t vsriq_n_p8(poly8x16_t a, poly8x16_t b, const int n);

// FORCE_INLINE poly16x4_t vsri_n_p16(poly16x4_t a, poly16x4_t b, const int n);

// FORCE_INLINE poly16x8_t vsriq_n_p16(poly16x8_t a, poly16x8_t b, const int n);

FORCE_INLINE int64_t vsrid_n_s64(int64_t a, int64_t b, const int n) {
  if (n == 64) {
    uint64_t mask = 0;
    return (a & ~mask) | (0 & mask);
  } else {
    uint64_t mask = UINT64_MAX >> n;
    return (a & ~mask) | ((b >> n) & mask);
  }
}

FORCE_INLINE uint64_t vsrid_n_u64(uint64_t a, uint64_t b, const int n) {
  if (n == 64) {
    uint64_t mask = 0;
    return (a & ~mask) | (0 & mask);
  } else {
    uint64_t mask = UINT64_MAX >> n;
    return (a & ~mask) | ((b >> n) & mask);
  }
}

FORCE_INLINE int8x8_t vsli_n_s8(int8x8_t a, int8x8_t b, const int c) {
  uint8_t mask = UINT8_MAX << c;
  vint8m1_t high = __riscv_vand_vx_i8m1(a, ~mask, 8);
  vint8m1_t low_unmasked = __riscv_vsll_vx_i8m1(b, c, 8);
  vint8m1_t low = __riscv_vand_vx_i8m1(low_unmasked, mask, 8);
  return __riscv_vor_vv_i8m1(high, low, 8);
}

FORCE_INLINE int16x4_t vsli_n_s16(int16x4_t a, int16x4_t b, const int c) {
  uint16_t mask = UINT16_MAX << c;
  vint16m1_t high = __riscv_vand_vx_i16m1(a, ~mask, 4);
  vint16m1_t low_unmasked = __riscv_vsll_vx_i16m1(b, c, 4);
  vint16m1_t low = __riscv_vand_vx_i16m1(low_unmasked, mask, 4);
  return __riscv_vor_vv_i16m1(high, low, 4);
}

FORCE_INLINE int32x2_t vsli_n_s32(int32x2_t a, int32x2_t b, const int c) {
  uint32_t mask = UINT32_MAX << c;
  vint32m1_t high = __riscv_vand_vx_i32m1(a, ~mask, 2);
  vint32m1_t low_unmasked = __riscv_vsll_vx_i32m1(b, c, 2);
  vint32m1_t low = __riscv_vand_vx_i32m1(low_unmasked, mask, 2);
  return __riscv_vor_vv_i32m1(high, low, 2);
}

FORCE_INLINE int64x1_t vsli_n_s64(int64x1_t a, int64x1_t b, const int c) {
  uint64_t mask = UINT64_MAX << c;
  vint64m1_t high = __riscv_vand_vx_i64m1(a, ~mask, 1);
  vint64m1_t low_unmasked = __riscv_vsll_vx_i64m1(b, c, 1);
  vint64m1_t low = __riscv_vand_vx_i64m1(low_unmasked, mask, 1);
  return __riscv_vor_vv_i64m1(high, low, 1);
}

FORCE_INLINE uint8x8_t vsli_n_u8(uint8x8_t a, uint8x8_t b, const int c) {
  uint8_t mask = UINT8_MAX << c;
  vuint8m1_t high = __riscv_vand_vx_u8m1(a, ~mask, 8);
  vuint8m1_t low_unmasked = __riscv_vsll_vx_u8m1(b, c, 8);
  vuint8m1_t low = __riscv_vand_vx_u8m1(low_unmasked, mask, 8);
  return __riscv_vor_vv_u8m1(high, low, 8);
}

FORCE_INLINE uint16x4_t vsli_n_u16(uint16x4_t a, uint16x4_t b, const int c) {
  uint16_t mask = UINT16_MAX << c;
  vuint16m1_t high = __riscv_vand_vx_u16m1(a, ~mask, 4);
  vuint16m1_t low_unmasked = __riscv_vsll_vx_u16m1(b, c, 4);
  vuint16m1_t low = __riscv_vand_vx_u16m1(low_unmasked, mask, 4);
  return __riscv_vor_vv_u16m1(high, low, 4);
}

FORCE_INLINE uint32x2_t vsli_n_u32(uint32x2_t a, uint32x2_t b, const int c) {
  uint32_t mask = UINT32_MAX << c;
  vuint32m1_t high = __riscv_vand_vx_u32m1(a, ~mask, 2);
  vuint32m1_t low_unmasked = __riscv_vsll_vx_u32m1(b, c, 2);
  vuint32m1_t low = __riscv_vand_vx_u32m1(low_unmasked, mask, 2);
  return __riscv_vor_vv_u32m1(high, low, 2);
}

FORCE_INLINE uint64x1_t vsli_n_u64(uint64x1_t a, uint64x1_t b, const int c) {
  uint64_t mask = UINT64_MAX << c;
  vuint64m1_t high = __riscv_vand_vx_u64m1(a, ~mask, 1);
  vuint64m1_t low_unmasked = __riscv_vsll_vx_u64m1(b, c, 1);
  vuint64m1_t low = __riscv_vand_vx_u64m1(low_unmasked, mask, 1);
  return __riscv_vor_vv_u64m1(high, low, 1);
}

FORCE_INLINE int8x16_t vsliq_n_s8(int8x16_t a, int8x16_t b, const int c) {
  uint8_t mask = UINT8_MAX << c;
  vint8m1_t high = __riscv_vand_vx_i8m1(a, ~mask, 16);
  vint8m1_t low_unmasked = __riscv_vsll_vx_i8m1(b, c, 16);
  vint8m1_t low = __riscv_vand_vx_i8m1(low_unmasked, mask, 16);
  return __riscv_vor_vv_i8m1(high, low, 16);
}

FORCE_INLINE int16x8_t vsliq_n_s16(int16x8_t a, int16x8_t b, const int c) {
  uint16_t mask = UINT16_MAX << c;
  vint16m1_t high = __riscv_vand_vx_i16m1(a, ~mask, 8);
  vint16m1_t low_unmasked = __riscv_vsll_vx_i16m1(b, c, 8);
  vint16m1_t low = __riscv_vand_vx_i16m1(low_unmasked, mask, 8);
  return __riscv_vor_vv_i16m1(high, low, 8);
}

FORCE_INLINE int32x4_t vsliq_n_s32(int32x4_t a, int32x4_t b, const int c) {
  uint32_t mask = UINT32_MAX << c;
  vint32m1_t high = __riscv_vand_vx_i32m1(a, ~mask, 4);
  vint32m1_t low_unmasked = __riscv_vsll_vx_i32m1(b, c, 4);
  vint32m1_t low = __riscv_vand_vx_i32m1(low_unmasked, mask, 4);
  return __riscv_vor_vv_i32m1(high, low, 4);
}

FORCE_INLINE int64x2_t vsliq_n_s64(int64x2_t a, int64x2_t b, const int c) {
  uint64_t mask = UINT64_MAX << c;
  vint64m1_t high = __riscv_vand_vx_i64m1(a, ~mask, 2);
  vint64m1_t low_unmasked = __riscv_vsll_vx_i64m1(b, c, 2);
  vint64m1_t low = __riscv_vand_vx_i64m1(low_unmasked, mask, 2);
  return __riscv_vor_vv_i64m1(high, low, 2);
}

FORCE_INLINE uint8x16_t vsliq_n_u8(uint8x16_t a, uint8x16_t b, const int c) {
  uint8_t mask = UINT8_MAX << c;
  vuint8m1_t high = __riscv_vand_vx_u8m1(a, ~mask, 16);
  vuint8m1_t low_unmasked = __riscv_vsll_vx_u8m1(b, c, 16);
  vuint8m1_t low = __riscv_vand_vx_u8m1(low_unmasked, mask, 16);
  return __riscv_vor_vv_u8m1(high, low, 16);
}

FORCE_INLINE uint16x8_t vsliq_n_u16(uint16x8_t a, uint16x8_t b, const int c) {
  uint16_t mask = UINT16_MAX << c;
  vuint16m1_t high = __riscv_vand_vx_u16m1(a, ~mask, 8);
  vuint16m1_t low_unmasked = __riscv_vsll_vx_u16m1(b, c, 8);
  vuint16m1_t low = __riscv_vand_vx_u16m1(low_unmasked, mask, 8);
  return __riscv_vor_vv_u16m1(high, low, 8);
}

FORCE_INLINE uint32x4_t vsliq_n_u32(uint32x4_t a, uint32x4_t b, const int c) {
  uint32_t mask = UINT32_MAX << c;
  vuint32m1_t high = __riscv_vand_vx_u32m1(a, ~mask, 4);
  vuint32m1_t low_unmasked = __riscv_vsll_vx_u32m1(b, c, 4);
  vuint32m1_t low = __riscv_vand_vx_u32m1(low_unmasked, mask, 4);
  return __riscv_vor_vv_u32m1(high, low, 4);
}

FORCE_INLINE uint64x2_t vsliq_n_u64(uint64x2_t a, uint64x2_t b, const int c) {
  uint64_t mask = UINT64_MAX << c;
  vuint64m1_t high = __riscv_vand_vx_u64m1(a, ~mask, 2);
  vuint64m1_t low_unmasked = __riscv_vsll_vx_u64m1(b, c, 2);
  vuint64m1_t low = __riscv_vand_vx_u64m1(low_unmasked, mask, 2);
  return __riscv_vor_vv_u64m1(high, low, 2);
}

// FORCE_INLINE poly64x1_t vsli_n_p64(poly64x1_t a, poly64x1_t b, const int n);

// FORCE_INLINE poly64x2_t vsliq_n_p64(poly64x2_t a, poly64x2_t b, const int n);

// FORCE_INLINE poly8x8_t vsli_n_p8(poly8x8_t a, poly8x8_t b, const int n);

// FORCE_INLINE poly8x16_t vsliq_n_p8(poly8x16_t a, poly8x16_t b, const int n);

// FORCE_INLINE poly16x4_t vsli_n_p16(poly16x4_t a, poly16x4_t b, const int n);

// FORCE_INLINE poly16x8_t vsliq_n_p16(poly16x8_t a, poly16x8_t b, const int n);

FORCE_INLINE int64_t vslid_n_s64(int64_t a, int64_t b, const int n) {
  if (n == 64) {
    uint64_t mask = 0;
    return (a & ~mask) | (0 & mask);
  }
  uint64_t mask = (uint64_t)(UINT64_MAX << n);
  return (a & ~mask) | ((b << n) & mask);
}

FORCE_INLINE uint64_t vslid_n_u64(uint64_t a, uint64_t b, const int n) {
  if (n == 64) {
    uint64_t mask = 0;
    return (a & ~mask) | (0 & mask);
  }
  uint64_t mask = (uint64_t)(UINT64_MAX << n);
  return (a & ~mask) | ((b << n) & mask);
}

FORCE_INLINE int8x8_t vneg_s8(int8x8_t a) { return __riscv_vneg_v_i8m1(a, 8); }

FORCE_INLINE int16x4_t vneg_s16(int16x4_t a) { return __riscv_vneg_v_i16m1(a, 4); }

FORCE_INLINE int32x2_t vneg_s32(int32x2_t a) { return __riscv_vneg_v_i32m1(a, 2); }

FORCE_INLINE float32x2_t vneg_f32(float32x2_t a) { return __riscv_vfneg_v_f32m1(a, 2); }

FORCE_INLINE int8x16_t vnegq_s8(int8x16_t a) { return __riscv_vneg_v_i8m1(a, 16); }

FORCE_INLINE int16x8_t vnegq_s16(int16x8_t a) { return __riscv_vneg_v_i16m1(a, 8); }

FORCE_INLINE int32x4_t vnegq_s32(int32x4_t a) { return __riscv_vneg_v_i32m1(a, 4); }

FORCE_INLINE float32x4_t vnegq_f32(float32x4_t a) { return __riscv_vfneg_v_f32m1(a, 4); }

FORCE_INLINE int64x1_t vneg_s64(int64x1_t a) { return __riscv_vneg_v_i64m1(a, 1); }

FORCE_INLINE int64_t vnegd_s64(int64_t a) { return -a; }

FORCE_INLINE int64x2_t vnegq_s64(int64x2_t a) { return __riscv_vneg_v_i64m1(a, 2); }

FORCE_INLINE float64x1_t vneg_f64(float64x1_t a) { return __riscv_vfneg_v_f64m1(a, 1); }

FORCE_INLINE float64x2_t vnegq_f64(float64x2_t a) { return __riscv_vfneg_v_f64m1(a, 2); }

FORCE_INLINE int8x8_t vqneg_s8(int8x8_t a) {
  vint16m2_t a_ext = __riscv_vsext_vf2_i16m2(a, 8);
  vint16m2_t a_neg = __riscv_vneg_v_i16m2(a_ext, 8);
  return __riscv_vnclip_wx_i8m1(a_neg, 0, __RISCV_VXRM_RDN, 8);
}

FORCE_INLINE int16x4_t vqneg_s16(int16x4_t a) {
  vint32m2_t a_ext = __riscv_vsext_vf2_i32m2(a, 4);
  vint32m2_t a_neg = __riscv_vneg_v_i32m2(a_ext, 4);
  return __riscv_vnclip_wx_i16m1(a_neg, 0, __RISCV_VXRM_RDN, 4);
}

FORCE_INLINE int32x2_t vqneg_s32(int32x2_t a) {
  vint64m2_t a_ext = __riscv_vsext_vf2_i64m2(a, 2);
  vint64m2_t a_neg = __riscv_vneg_v_i64m2(a_ext, 2);
  return __riscv_vnclip_wx_i32m1(a_neg, 0, __RISCV_VXRM_RDN, 2);
}

FORCE_INLINE int8x16_t vqnegq_s8(int8x16_t a) {
  vint16m2_t a_ext = __riscv_vsext_vf2_i16m2(a, 16);
  vint16m2_t a_neg = __riscv_vneg_v_i16m2(a_ext, 16);
  return __riscv_vnclip_wx_i8m1(a_neg, 0, __RISCV_VXRM_RDN, 16);
}

FORCE_INLINE int16x8_t vqnegq_s16(int16x8_t a) {
  vint32m2_t a_ext = __riscv_vsext_vf2_i32m2(a, 8);
  vint32m2_t a_neg = __riscv_vneg_v_i32m2(a_ext, 8);
  return __riscv_vnclip_wx_i16m1(a_neg, 0, __RISCV_VXRM_RDN, 8);
}

FORCE_INLINE int32x4_t vqnegq_s32(int32x4_t a) {
  vint64m2_t a_ext = __riscv_vsext_vf2_i64m2(a, 4);
  vint64m2_t a_neg = __riscv_vneg_v_i64m2(a_ext, 4);
  return __riscv_vnclip_wx_i32m1(a_neg, 0, __RISCV_VXRM_RDN, 4);
}

FORCE_INLINE int64x1_t vqneg_s64(int64x1_t a) {
  vbool64_t min_mask = __riscv_vmseq_vx_i64m1_b64(a, INT64_MIN, 1);
  vint64m1_t a_neg = __riscv_vneg_v_i64m1(a, 1);
  return __riscv_vmerge_vxm_i64m1(a_neg, INT64_MAX, min_mask, 1);
}

FORCE_INLINE int64x2_t vqnegq_s64(int64x2_t a) {
  vbool64_t min_mask = __riscv_vmseq_vx_i64m1_b64(a, INT64_MIN, 2);
  vint64m1_t a_neg = __riscv_vneg_v_i64m1(a, 2);
  return __riscv_vmerge_vxm_i64m1(a_neg, INT64_MAX, min_mask, 2);
}

FORCE_INLINE int8_t vqnegb_s8(int8_t a) {
  if (a == INT8_MIN) {
    return INT8_MAX;
  } else {
    return -a;
  }
}

FORCE_INLINE int16_t vqnegh_s16(int16_t a) {
  if (a == INT16_MIN) {
    return INT16_MAX;
  } else {
    return -a;
  }
}

FORCE_INLINE int32_t vqnegs_s32(int32_t a) {
  if (a == INT32_MIN) {
    return INT32_MAX;
  } else {
    return -a;
  }
}

FORCE_INLINE int64_t vqnegd_s64(int64_t a) {
  if (a == INT64_MIN) {
    return INT64_MAX;
  } else {
    return -a;
  }
}

FORCE_INLINE int8x8_t vmvn_s8(int8x8_t a) { return __riscv_vnot_v_i8m1(a, 8); }

FORCE_INLINE int16x4_t vmvn_s16(int16x4_t a) { return __riscv_vnot_v_i16m1(a, 4); }

FORCE_INLINE int32x2_t vmvn_s32(int32x2_t a) { return __riscv_vnot_v_i32m1(a, 2); }

FORCE_INLINE uint8x8_t vmvn_u8(uint8x8_t a) { return __riscv_vnot_v_u8m1(a, 8); }

FORCE_INLINE uint16x4_t vmvn_u16(uint16x4_t a) { return __riscv_vnot_v_u16m1(a, 4); }

FORCE_INLINE uint32x2_t vmvn_u32(uint32x2_t a) { return __riscv_vnot_v_u32m1(a, 2); }

FORCE_INLINE int8x16_t vmvnq_s8(int8x16_t a) { return __riscv_vnot_v_i8m1(a, 16); }

FORCE_INLINE int16x8_t vmvnq_s16(int16x8_t a) { return __riscv_vnot_v_i16m1(a, 8); }

FORCE_INLINE int32x4_t vmvnq_s32(int32x4_t a) { return __riscv_vnot_v_i32m1(a, 4); }

FORCE_INLINE uint8x16_t vmvnq_u8(uint8x16_t a) { return __riscv_vnot_v_u8m1(a, 16); }

FORCE_INLINE uint16x8_t vmvnq_u16(uint16x8_t a) { return __riscv_vnot_v_u16m1(a, 8); }

FORCE_INLINE uint32x4_t vmvnq_u32(uint32x4_t a) { return __riscv_vnot_v_u32m1(a, 4); }

// FORCE_INLINE poly8x8_t vmvn_p8(poly8x8_t a);

// FORCE_INLINE poly8x16_t vmvnq_p8(poly8x16_t a);

// FORCE_INLINE int8x8_t vcls_s8(int8x8_t a);

// FORCE_INLINE int16x4_t vcls_s16(int16x4_t a);

// FORCE_INLINE int32x2_t vcls_s32(int32x2_t a);

// FORCE_INLINE int8x16_t vclsq_s8(int8x16_t a);

// FORCE_INLINE int16x8_t vclsq_s16(int16x8_t a);

// FORCE_INLINE int32x4_t vclsq_s32(int32x4_t a);

// FORCE_INLINE int8x8_t vcls_u8(uint8x8_t a);

// FORCE_INLINE int8x16_t vclsq_u8(uint8x16_t a);

// FORCE_INLINE int16x4_t vcls_u16(uint16x4_t a);

// FORCE_INLINE int16x8_t vclsq_u16(uint16x8_t a);

// FORCE_INLINE int32x2_t vcls_u32(uint32x2_t a);

// FORCE_INLINE int32x4_t vclsq_u32(uint32x4_t a);

FORCE_INLINE int8x8_t vclz_s8(int8x8_t a) {
  // refer
  // https://stackoverflow.com/questions/23856596/how-to-count-leading-zeros-in-a-32-bit-unsigned-integer
  vuint8m1_t a_u = __riscv_vreinterpret_v_i8m1_u8m1(a);
  a_u = __riscv_vor_vv_u8m1(__riscv_vsrl_vx_u8m1(a_u, 1, 8), a_u, 8);
  a_u = __riscv_vor_vv_u8m1(__riscv_vsrl_vx_u8m1(a_u, 2, 8), a_u, 8);
  a_u = __riscv_vor_vv_u8m1(__riscv_vsrl_vx_u8m1(a_u, 4, 8), a_u, 8);
  vuint8m1_t a_not = __riscv_vnot_v_u8m1(a_u, 8);
  return vcnt_s8(__riscv_vreinterpret_v_u8m1_i8m1(a_not));
}

// FORCE_INLINE int16x4_t vclz_s16(int16x4_t a);

// FORCE_INLINE int32x2_t vclz_s32(int32x2_t a);

// FORCE_INLINE uint8x8_t vclz_u8(uint8x8_t a);

// FORCE_INLINE uint16x4_t vclz_u16(uint16x4_t a);

// FORCE_INLINE uint32x2_t vclz_u32(uint32x2_t a);

// FORCE_INLINE int8x16_t vclzq_s8(int8x16_t a);

// FORCE_INLINE int16x8_t vclzq_s16(int16x8_t a);

// FORCE_INLINE int32x4_t vclzq_s32(int32x4_t a);

// FORCE_INLINE uint8x16_t vclzq_u8(uint8x16_t a);

// FORCE_INLINE uint16x8_t vclzq_u16(uint16x8_t a);

// FORCE_INLINE uint32x4_t vclzq_u32(uint32x4_t a);

FORCE_INLINE int8x8_t vcnt_s8(int8x8_t a) {
  const int8_t bit_population_lookup_arr[16] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};
  vint8m1_t lookup = __riscv_vle8_v_i8m1(bit_population_lookup_arr, 16);
  vint8m1_t cnt_low =
      __riscv_vrgather_vv_i8m1(lookup, __riscv_vreinterpret_v_i8m1_u8m1(__riscv_vand_vx_i8m1(a, 0xf, 8)), 8);
  vint8m1_t a_high = __riscv_vreinterpret_v_u8m1_i8m1(__riscv_vsrl_vx_u8m1(__riscv_vreinterpret_v_i8m1_u8m1(a), 4, 8));
  vint8m1_t cnt_high = __riscv_vrgather_vv_i8m1(lookup, __riscv_vreinterpret_v_i8m1_u8m1(a_high), 8);
  return __riscv_vadd_vv_i8m1(cnt_low, cnt_high, 8);
}

FORCE_INLINE uint8x8_t vcnt_u8(uint8x8_t a) {
  const uint8_t bit_population_lookup_arr[16] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};
  vuint8m1_t lookup = __riscv_vle8_v_u8m1(bit_population_lookup_arr, 16);
  vuint8m1_t cnt_low = __riscv_vrgather_vv_u8m1(lookup, __riscv_vand_vx_u8m1(a, 0xf, 8), 8);
  vuint8m1_t a_high = __riscv_vsrl_vx_u8m1(a, 4, 8);
  vuint8m1_t cnt_high = __riscv_vrgather_vv_u8m1(lookup, a_high, 8);
  return __riscv_vadd_vv_u8m1(cnt_low, cnt_high, 8);
}

FORCE_INLINE int8x16_t vcntq_s8(int8x16_t a) {
  const int8_t bit_population_lookup_arr[16] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};
  vint8m1_t lookup = __riscv_vle8_v_i8m1(bit_population_lookup_arr, 16);
  vint8m1_t cnt_low =
      __riscv_vrgather_vv_i8m1(lookup, __riscv_vreinterpret_v_i8m1_u8m1(__riscv_vand_vx_i8m1(a, 0xf, 16)), 16);
  vint8m1_t a_high = __riscv_vreinterpret_v_u8m1_i8m1(__riscv_vsrl_vx_u8m1(__riscv_vreinterpret_v_i8m1_u8m1(a), 4, 16));
  vint8m1_t cnt_high = __riscv_vrgather_vv_i8m1(lookup, __riscv_vreinterpret_v_i8m1_u8m1(a_high), 16);
  return __riscv_vadd_vv_i8m1(cnt_low, cnt_high, 16);
}

FORCE_INLINE uint8x16_t vcntq_u8(uint8x16_t a) {
  const uint8_t bit_population_lookup_arr[16] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};
  vuint8m1_t lookup = __riscv_vle8_v_u8m1(bit_population_lookup_arr, 16);
  vuint8m1_t cnt_low = __riscv_vrgather_vv_u8m1(lookup, __riscv_vand_vx_u8m1(a, 0xf, 16), 16);
  vuint8m1_t a_high = __riscv_vsrl_vx_u8m1(a, 4, 16);
  vuint8m1_t cnt_high = __riscv_vrgather_vv_u8m1(lookup, a_high, 16);
  return __riscv_vadd_vv_u8m1(cnt_low, cnt_high, 16);
}

// FORCE_INLINE poly8x8_t vcnt_p8(poly8x8_t a);

// FORCE_INLINE poly8x16_t vcntq_p8(poly8x16_t a);

FORCE_INLINE float32x2_t vrecpe_f32(float32x2_t a) { return __riscv_vfrec7_v_f32m1(a, 2); }

// FORCE_INLINE uint32x2_t vrecpe_u32(uint32x2_t a);

FORCE_INLINE float32x4_t vrecpeq_f32(float32x4_t a) { return __riscv_vfrec7_v_f32m1(a, 4); }

FORCE_INLINE float64x1_t vrecpe_f64(float64x1_t a) { return __riscv_vfrec7_v_f64m1(a, 1); }

FORCE_INLINE float64x2_t vrecpeq_f64(float64x2_t a) { return __riscv_vfrec7_v_f64m1(a, 2); }

FORCE_INLINE float32_t vrecpes_f32(float32_t a) { return 1.0f / a; }

FORCE_INLINE float64_t vrecped_f64(float64_t a) { return 1.0f / a; }

// FORCE_INLINE uint32x4_t vrecpeq_u32(uint32x4_t a);

FORCE_INLINE float32x2_t vrsqrte_f32(float32x2_t a) { return __riscv_vfrsqrt7_v_f32m1(a, 2); }

// FORCE_INLINE uint32x2_t vrsqrte_u32(uint32x2_t a);

FORCE_INLINE float32x4_t vrsqrteq_f32(float32x4_t a) { return __riscv_vfrsqrt7_v_f32m1(a, 4); }

FORCE_INLINE float64x1_t vrsqrte_f64(float64x1_t a) { return __riscv_vfrsqrt7_v_f64m1(a, 1); }

FORCE_INLINE float64x2_t vrsqrteq_f64(float64x2_t a) { return __riscv_vfrsqrt7_v_f64m1(a, 2); }

FORCE_INLINE float32_t vrsqrtes_f32(float32_t a) { return 1 / sqrtf(a); }

FORCE_INLINE float64_t vrsqrted_f64(float64_t a) { return 1 / sqrt(a); }

// FORCE_INLINE uint32x4_t vrsqrteq_u32(uint32x4_t a);

FORCE_INLINE int8_t vget_lane_s8(int8x8_t a, const int b) {
  return __riscv_vmv_x_s_i8m1_i8(__riscv_vslidedown_vx_i8m1(a, b, 8));
}

FORCE_INLINE int16_t vget_lane_s16(int16x4_t a, const int b) {
  return __riscv_vmv_x_s_i16m1_i16(__riscv_vslidedown_vx_i16m1(a, b, 4));
}

FORCE_INLINE int32_t vget_lane_s32(int32x2_t a, const int b) {
  return __riscv_vmv_x_s_i32m1_i32(__riscv_vslidedown_vx_i32m1(a, b, 2));
}

FORCE_INLINE float32_t vget_lane_f32(float32x2_t a, const int b) {
  return __riscv_vfmv_f_s_f32m1_f32(__riscv_vslidedown_vx_f32m1(a, b, 2));
}

FORCE_INLINE float64_t vget_lane_f64(float64x1_t a, const int b) { return __riscv_vfmv_f_s_f64m1_f64(a); }

FORCE_INLINE uint8_t vget_lane_u8(uint8x8_t a, const int b) {
  return __riscv_vmv_x_s_u8m1_u8(__riscv_vslidedown_vx_u8m1(a, b, 8));
}

FORCE_INLINE uint16_t vget_lane_u16(uint16x4_t a, const int b) {
  return __riscv_vmv_x_s_u16m1_u16(__riscv_vslidedown_vx_u16m1(a, b, 4));
}

FORCE_INLINE uint32_t vget_lane_u32(uint32x2_t a, const int b) {
  return __riscv_vmv_x_s_u32m1_u32(__riscv_vslidedown_vx_u32m1(a, b, 2));
}

FORCE_INLINE int64_t vget_lane_s64(int64x1_t a, const int b) {
  return __riscv_vmv_x_s_i64m1_i64(__riscv_vslidedown_vx_i64m1(a, b, 1));
}

// FORCE_INLINE poly8_t vget_lane_p8(poly8x8_t v, const int lane);

// FORCE_INLINE poly16_t vget_lane_p16(poly16x4_t v, const int lane);

FORCE_INLINE uint64_t vget_lane_u64(uint64x1_t a, const int b) {
  return __riscv_vmv_x_s_u64m1_u64(__riscv_vslidedown_vx_u64m1(a, b, 1));
}

// FORCE_INLINE poly64_t vget_lane_p64(poly64x1_t v, const int lane);

FORCE_INLINE int8_t vgetq_lane_s8(int8x16_t a, const int b) {
  return __riscv_vmv_x_s_i8m1_i8(__riscv_vslidedown_vx_i8m1(a, b, 16));
}

FORCE_INLINE int16_t vgetq_lane_s16(int16x8_t a, const int b) {
  return __riscv_vmv_x_s_i16m1_i16(__riscv_vslidedown_vx_i16m1(a, b, 8));
}

FORCE_INLINE int32_t vgetq_lane_s32(int32x4_t a, const int b) {
  return __riscv_vmv_x_s_i32m1_i32(__riscv_vslidedown_vx_i32m1(a, b, 4));
}

FORCE_INLINE float32_t vgetq_lane_f32(float32x4_t a, const int b) {
  return __riscv_vfmv_f_s_f32m1_f32(__riscv_vslidedown_vx_f32m1(a, b, 4));
}

FORCE_INLINE float64_t vgetq_lane_f64(float64x2_t a, const int b) {
  return __riscv_vfmv_f_s_f64m1_f64(__riscv_vslidedown_vx_f64m1(a, b, 2));
}

FORCE_INLINE uint8_t vgetq_lane_u8(uint8x16_t a, const int b) {
  return __riscv_vmv_x_s_u8m1_u8(__riscv_vslidedown_vx_u8m1(a, b, 16));
}

FORCE_INLINE uint16_t vgetq_lane_u16(uint16x8_t a, const int b) {
  return __riscv_vmv_x_s_u16m1_u16(__riscv_vslidedown_vx_u16m1(a, b, 8));
}

FORCE_INLINE uint32_t vgetq_lane_u32(uint32x4_t a, const int b) {
  return __riscv_vmv_x_s_u32m1_u32(__riscv_vslidedown_vx_u32m1(a, b, 4));
}

FORCE_INLINE int64_t vgetq_lane_s64(int64x2_t a, const int b) {
  return __riscv_vmv_x_s_i64m1_i64(__riscv_vslidedown_vx_i64m1(a, b, 2));
}

// FORCE_INLINE poly8_t vgetq_lane_p8(poly8x16_t v, const int lane);

// FORCE_INLINE poly16_t vgetq_lane_p16(poly16x8_t v, const int lane);

// FORCE_INLINE float16_t vget_lane_f16(float16x4_t v, const int lane);

// FORCE_INLINE float16_t vgetq_lane_f16(float16x8_t v, const int lane);

FORCE_INLINE uint64_t vgetq_lane_u64(uint64x2_t a, const int b) {
  return __riscv_vmv_x_s_u64m1_u64(__riscv_vslidedown_vx_u64m1(a, b, 2));
}

// FORCE_INLINE poly64_t vgetq_lane_p64(poly64x2_t v, const int lane);

FORCE_INLINE int8x8_t vset_lane_s8(int8_t a, int8x8_t b, const int c) {
  vbool8_t mask = __riscv_vreinterpret_v_u8m1_b8(vdup_n_u8((uint8_t)(1 << c)));
  return __riscv_vmerge_vxm_i8m1(b, a, mask, 8);
}

FORCE_INLINE int16x4_t vset_lane_s16(int16_t a, int16x4_t b, const int c) {
  vbool16_t mask = __riscv_vreinterpret_v_u16m1_b16(vdup_n_u16((uint16_t)(1 << c)));
  return __riscv_vmerge_vxm_i16m1(b, a, mask, 4);
}

FORCE_INLINE int32x2_t vset_lane_s32(int32_t a, int32x2_t b, const int c) {
  vbool32_t mask = __riscv_vreinterpret_v_u32m1_b32(vdup_n_u32((uint32_t)(1 << c)));
  return __riscv_vmerge_vxm_i32m1(b, a, mask, 2);
}

FORCE_INLINE float32x2_t vset_lane_f32(float32_t a, float32x2_t b, const int c) {
  vbool32_t mask = __riscv_vreinterpret_v_u32m1_b32(vdup_n_u32((uint32_t)(1 << c)));
  return __riscv_vfmerge_vfm_f32m1(b, a, mask, 2);
}

FORCE_INLINE float64x1_t vset_lane_f64(float64_t a, float64x1_t b, const int c) {
  vbool64_t mask = __riscv_vreinterpret_v_u64m1_b64(vdup_n_u64((uint64_t)(1 << c)));
  return __riscv_vfmerge_vfm_f64m1(b, a, mask, 1);
}

FORCE_INLINE uint8x8_t vset_lane_u8(uint8_t a, uint8x8_t b, const int c) {
  vbool8_t mask = __riscv_vreinterpret_v_u8m1_b8(vdup_n_u8((uint8_t)(1 << c)));
  return __riscv_vmerge_vxm_u8m1(b, a, mask, 8);
}

FORCE_INLINE uint16x4_t vset_lane_u16(uint16_t a, uint16x4_t b, const int c) {
  vbool16_t mask = __riscv_vreinterpret_v_u16m1_b16(vdup_n_u16((uint16_t)(1 << c)));
  return __riscv_vmerge_vxm_u16m1(b, a, mask, 4);
}

FORCE_INLINE uint32x2_t vset_lane_u32(uint32_t a, uint32x2_t b, const int c) {
  vbool32_t mask = __riscv_vreinterpret_v_u32m1_b32(vdup_n_u32((uint32_t)(1 << c)));
  return __riscv_vmerge_vxm_u32m1(b, a, mask, 2);
}

FORCE_INLINE int64x1_t vset_lane_s64(int64_t a, int64x1_t b, const int c) {
  vbool64_t mask = __riscv_vreinterpret_v_u64m1_b64(vdup_n_u64((uint64_t)(1 << c)));
  return __riscv_vmerge_vxm_i64m1(b, a, mask, 1);
}

// FORCE_INLINE poly8x8_t vset_lane_p8(poly8_t a, poly8x8_t v, const int lane);

// FORCE_INLINE poly16x4_t vset_lane_p16(poly16_t a, poly16x4_t v, const int lane);

// FORCE_INLINE float16x4_t vset_lane_f16(float16_t a, float16x4_t v, const int lane);

// FORCE_INLINE float16x8_t vsetq_lane_f16(float16_t a, float16x8_t v, const int lane);

FORCE_INLINE uint64x1_t vset_lane_u64(uint64_t a, uint64x1_t b, const int c) {
  vbool64_t mask = __riscv_vreinterpret_v_u64m1_b64(vdup_n_u64((uint64_t)(1 << c)));
  return __riscv_vmerge_vxm_u64m1(b, a, mask, 1);
}

// FORCE_INLINE poly64x1_t vset_lane_p64(poly64_t a, poly64x1_t v, const int lane);

FORCE_INLINE int8x16_t vsetq_lane_s8(int8_t a, int8x16_t b, const int c) {
  vbool8_t mask = __riscv_vreinterpret_v_u16m1_b8(vdup_n_u16((uint16_t)(1 << c)));
  return __riscv_vmerge_vxm_i8m1(b, a, mask, 16);
}

FORCE_INLINE int16x8_t vsetq_lane_s16(int16_t a, int16x8_t b, const int c) {
  vbool16_t mask = __riscv_vreinterpret_v_u16m1_b16(vdup_n_u16((uint16_t)(1 << c)));
  return __riscv_vmerge_vxm_i16m1(b, a, mask, 8);
}

FORCE_INLINE int32x4_t vsetq_lane_s32(int32_t a, int32x4_t b, const int c) {
  vbool32_t mask = __riscv_vreinterpret_v_u32m1_b32(vdup_n_u32((uint32_t)(1 << c)));
  return __riscv_vmerge_vxm_i32m1(b, a, mask, 4);
}

FORCE_INLINE float32x4_t vsetq_lane_f32(float32_t a, float32x4_t b, const int c) {
  vbool32_t mask = __riscv_vreinterpret_v_u32m1_b32(vdup_n_u32((uint32_t)(1 << c)));
  return __riscv_vfmerge_vfm_f32m1(b, a, mask, 4);
}

FORCE_INLINE float64x2_t vsetq_lane_f64(float64_t a, float64x2_t b, const int c) {
  vbool64_t mask = __riscv_vreinterpret_v_u64m1_b64(vdup_n_u64((uint64_t)(1 << c)));
  return __riscv_vfmerge_vfm_f64m1(b, a, mask, 2);
}

// FORCE_INLINE float32_t vrecpxs_f32(float32_t a);

// FORCE_INLINE float64_t vrecpxd_f64(float64_t a);

FORCE_INLINE float32x2_t vfma_n_f32(float32x2_t a, float32x2_t b, float32_t n) {
  return __riscv_vfmacc_vf_f32m1(a, n, b, 2);
}

FORCE_INLINE float32x4_t vfmaq_n_f32(float32x4_t a, float32x4_t b, float32_t n) {
  return __riscv_vfmacc_vf_f32m1(a, n, b, 4);
}

FORCE_INLINE float32x2_t vfms_n_f32(float32x2_t a, float32x2_t b, float32_t n) {
  return __riscv_vfnmsac_vf_f32m1(a, n, b, 2);
}

FORCE_INLINE float32x4_t vfmsq_n_f32(float32x4_t a, float32x4_t b, float32_t n) {
  return __riscv_vfnmsac_vf_f32m1(a, n, b, 4);
}

FORCE_INLINE float64x1_t vfma_n_f64(float64x1_t a, float64x1_t b, float64_t n) {
  return __riscv_vfmacc_vf_f64m1(a, n, b, 1);
}

FORCE_INLINE float64x2_t vfmaq_n_f64(float64x2_t a, float64x2_t b, float64_t n) {
  return __riscv_vfmacc_vf_f64m1(a, n, b, 2);
}

FORCE_INLINE float64x1_t vfms_n_f64(float64x1_t a, float64x1_t b, float64_t n) {
  return __riscv_vfnmsac_vf_f64m1(a, n, b, 1);
}

FORCE_INLINE float64x2_t vfmsq_n_f64(float64x2_t a, float64x2_t b, float64_t n) {
  return __riscv_vfnmsac_vf_f64m1(a, n, b, 2);
}

FORCE_INLINE uint8x16_t vsetq_lane_u8(uint8_t a, uint8x16_t b, const int c) {
  vbool8_t mask = __riscv_vreinterpret_v_u16m1_b8(vdup_n_u16((uint16_t)(1 << c)));
  return __riscv_vmerge_vxm_u8m1(b, a, mask, 16);
}

FORCE_INLINE uint16x8_t vsetq_lane_u16(uint16_t a, uint16x8_t b, const int c) {
  vbool16_t mask = __riscv_vreinterpret_v_u16m1_b16(vdup_n_u16((uint16_t)(1 << c)));
  return __riscv_vmerge_vxm_u16m1(b, a, mask, 8);
}

FORCE_INLINE uint32x4_t vsetq_lane_u32(uint32_t a, uint32x4_t b, const int c) {
  vbool32_t mask = __riscv_vreinterpret_v_u32m1_b32(vdup_n_u32((uint32_t)(1 << c)));
  return __riscv_vmerge_vxm_u32m1(b, a, mask, 4);
}

FORCE_INLINE int64x2_t vsetq_lane_s64(int64_t a, int64x2_t b, const int c) {
  vbool64_t mask = __riscv_vreinterpret_v_u64m1_b64(vdup_n_u64((uint64_t)(1 << c)));
  return __riscv_vmerge_vxm_i64m1(b, a, mask, 2);
}

// FORCE_INLINE poly8x16_t vsetq_lane_p8(poly8_t a, poly8x16_t v, const int lane);

// FORCE_INLINE poly16x8_t vsetq_lane_p16(poly16_t a, poly16x8_t v, const int lane);

FORCE_INLINE uint64x2_t vsetq_lane_u64(uint64_t a, uint64x2_t b, const int c) {
  vbool64_t mask = __riscv_vreinterpret_v_u64m1_b64(vdup_n_u64((uint64_t)(1 << c)));
  return __riscv_vmerge_vxm_u64m1(b, a, mask, 2);
}

// FORCE_INLINE poly64x2_t vsetq_lane_p64(poly64_t a, poly64x2_t v, const int lane);

FORCE_INLINE int8x8_t vcreate_s8(uint64_t a) {
  return __riscv_vreinterpret_v_i64m1_i8m1(__riscv_vreinterpret_v_u64m1_i64m1(__riscv_vmv_v_x_u64m1(a, 8)));
}

FORCE_INLINE int16x4_t vcreate_s16(uint64_t a) {
  return __riscv_vreinterpret_v_i64m1_i16m1(__riscv_vreinterpret_v_u64m1_i64m1(__riscv_vmv_v_x_u64m1(a, 8)));
}

FORCE_INLINE int32x2_t vcreate_s32(uint64_t a) {
  return __riscv_vreinterpret_v_i64m1_i32m1(__riscv_vreinterpret_v_u64m1_i64m1(__riscv_vmv_v_x_u64m1(a, 8)));
}

FORCE_INLINE int64x1_t vcreate_s64(uint64_t a) {
  return __riscv_vreinterpret_v_u64m1_i64m1(__riscv_vmv_v_x_u64m1(a, 8));
}

FORCE_INLINE float32x2_t vcreate_f32(uint64_t a) {
  return __riscv_vreinterpret_v_i32m1_f32m1(
      __riscv_vreinterpret_v_i64m1_i32m1(__riscv_vreinterpret_v_u64m1_i64m1(__riscv_vmv_v_x_u64m1(a, 8))));
}

// FORCE_INLINE poly8x8_t vcreate_p8(uint64_t a);

// FORCE_INLINE poly16x4_t vcreate_p16(uint64_t a);

FORCE_INLINE float64x1_t vcreate_f64(uint64_t a) {
  return __riscv_vreinterpret_v_u64m1_f64m1(__riscv_vmv_v_x_u64m1(a, 8));
}

FORCE_INLINE uint8x8_t vcreate_u8(uint64_t a) {
  return __riscv_vreinterpret_v_u64m1_u8m1(
      __riscv_vreinterpret_v_i64m1_u64m1(__riscv_vreinterpret_v_u64m1_i64m1(__riscv_vmv_v_x_u64m1(a, 8))));
}

FORCE_INLINE uint16x4_t vcreate_u16(uint64_t a) {
  return __riscv_vreinterpret_v_u64m1_u16m1(
      __riscv_vreinterpret_v_i64m1_u64m1(__riscv_vreinterpret_v_u64m1_i64m1(__riscv_vmv_v_x_u64m1(a, 8))));
}

FORCE_INLINE uint32x2_t vcreate_u32(uint64_t a) {
  return __riscv_vreinterpret_v_u64m1_u32m1(
      __riscv_vreinterpret_v_i64m1_u64m1(__riscv_vreinterpret_v_u64m1_i64m1(__riscv_vmv_v_x_u64m1(a, 8))));
}

FORCE_INLINE uint64x1_t vcreate_u64(uint64_t a) { return __riscv_vmv_v_x_u64m1(a, 8); }

// FORCE_INLINE poly64x1_t vcreate_p64(uint64_t a);

// FORCE_INLINE float16x4_t vcreate_f16(uint64_t a);

FORCE_INLINE int8x8_t vdup_n_s8(int8_t a) { return __riscv_vmv_v_x_i8m1(a, 8); }

FORCE_INLINE int16x4_t vdup_n_s16(int16_t a) { return __riscv_vmv_v_x_i16m1(a, 4); }

FORCE_INLINE int32x2_t vdup_n_s32(int32_t a) { return __riscv_vmv_v_x_i32m1(a, 2); }

FORCE_INLINE float32x2_t vdup_n_f32(float32_t a) { return __riscv_vfmv_v_f_f32m1(a, 2); }

FORCE_INLINE uint8x8_t vdup_n_u8(uint8_t a) { return __riscv_vmv_v_x_u8m1(a, 8); }

FORCE_INLINE uint16x4_t vdup_n_u16(uint16_t a) { return __riscv_vmv_v_x_u16m1(a, 4); }

FORCE_INLINE uint32x2_t vdup_n_u32(uint32_t a) { return __riscv_vmv_v_x_u32m1(a, 2); }

FORCE_INLINE int64x1_t vdup_n_s64(int64_t a) { return __riscv_vmv_v_x_i64m1(a, 1); }

FORCE_INLINE uint64x1_t vdup_n_u64(uint64_t a) { return __riscv_vmv_v_x_u64m1(a, 1); }

FORCE_INLINE int8x16_t vdupq_n_s8(int8_t a) { return __riscv_vmv_v_x_i8m1(a, 16); }

FORCE_INLINE int16x8_t vdupq_n_s16(int16_t a) { return __riscv_vmv_v_x_i16m1(a, 8); }

FORCE_INLINE int32x4_t vdupq_n_s32(int32_t a) { return __riscv_vmv_v_x_i32m1(a, 4); }

FORCE_INLINE float32x4_t vdupq_n_f32(float32_t a) { return __riscv_vfmv_v_f_f32m1(a, 4); }

// FORCE_INLINE poly8x8_t vdup_n_p8(poly8_t value);

// FORCE_INLINE poly8x16_t vdupq_n_p8(poly8_t value);

// FORCE_INLINE poly16x4_t vdup_n_p16(poly16_t value);

// FORCE_INLINE poly16x8_t vdupq_n_p16(poly16_t value);

FORCE_INLINE float64x1_t vdup_n_f64(float64_t a) { return __riscv_vfmv_v_f_f64m1(a, 1); }

FORCE_INLINE float64x2_t vdupq_n_f64(float64_t a) { return __riscv_vfmv_v_f_f64m1(a, 2); }

FORCE_INLINE uint8x16_t vdupq_n_u8(uint8_t a) { return __riscv_vmv_v_x_u8m1(a, 16); }

FORCE_INLINE uint16x8_t vdupq_n_u16(uint16_t a) { return __riscv_vmv_v_x_u16m1(a, 8); }

FORCE_INLINE uint32x4_t vdupq_n_u32(uint32_t a) { return __riscv_vmv_v_x_u32m1(a, 4); }

FORCE_INLINE int64x2_t vdupq_n_s64(int64_t a) { return __riscv_vmv_v_x_i64m1(a, 2); }

FORCE_INLINE uint64x2_t vdupq_n_u64(uint64_t a) { return __riscv_vmv_v_x_u64m1(a, 2); }

// FORCE_INLINE poly64x1_t vdup_n_p64(poly64_t value);

// FORCE_INLINE poly64x2_t vdupq_n_p64(poly64_t value);

FORCE_INLINE int8x8_t vmov_n_s8(int8_t a) { return vdup_n_s8(a); }

FORCE_INLINE int16x4_t vmov_n_s16(int16_t a) { return vdup_n_s16(a); }

FORCE_INLINE int32x2_t vmov_n_s32(int32_t a) { return vdup_n_s32(a); }

FORCE_INLINE float32x2_t vmov_n_f32(float32_t a) { return vdup_n_f32(a); }

FORCE_INLINE uint8x8_t vmov_n_u8(uint8_t a) { return vdup_n_u8(a); }

FORCE_INLINE uint16x4_t vmov_n_u16(uint16_t a) { return vdup_n_u16(a); }

FORCE_INLINE uint32x2_t vmov_n_u32(uint32_t a) { return vdup_n_u32(a); }

FORCE_INLINE int64x1_t vmov_n_s64(int64_t a) { return vdup_n_s64(a); }

FORCE_INLINE uint64x1_t vmov_n_u64(uint64_t a) { return vdup_n_u64(a); }

FORCE_INLINE int8x16_t vmovq_n_s8(int8_t a) { return vdupq_n_s8(a); }

FORCE_INLINE int16x8_t vmovq_n_s16(int16_t a) { return vdupq_n_s16(a); }

FORCE_INLINE int32x4_t vmovq_n_s32(int32_t a) { return vdupq_n_s32(a); }

FORCE_INLINE float32x4_t vmovq_n_f32(float32_t a) { return vdupq_n_f32(a); }

// FORCE_INLINE poly8x8_t vmov_n_p8(poly8_t value);

// FORCE_INLINE poly8x16_t vmovq_n_p8(poly8_t value);

// FORCE_INLINE poly16x4_t vmov_n_p16(poly16_t value);

// FORCE_INLINE poly16x8_t vmovq_n_p16(poly16_t value);

FORCE_INLINE float64x1_t vmov_n_f64(float64_t a) { return vdup_n_f64(a); }

FORCE_INLINE float64x2_t vmovq_n_f64(float64_t a) { return vdupq_n_f64(a); }

FORCE_INLINE uint8x16_t vmovq_n_u8(uint8_t a) { return vdupq_n_u8(a); }

FORCE_INLINE uint16x8_t vmovq_n_u16(uint16_t a) { return vdupq_n_u16(a); }

FORCE_INLINE uint32x4_t vmovq_n_u32(uint32_t a) { return vdupq_n_u32(a); }

FORCE_INLINE int64x2_t vmovq_n_s64(int64_t a) { return vdupq_n_s64(a); }

FORCE_INLINE uint64x2_t vmovq_n_u64(uint64_t a) { return vdupq_n_u64(a); }

FORCE_INLINE int8x8_t vdup_lane_s8(int8x8_t a, const int b) { return __riscv_vrgather_vx_i8m1(a, b, 8); }

FORCE_INLINE int16x4_t vdup_lane_s16(int16x4_t a, const int b) { return __riscv_vrgather_vx_i16m1(a, b, 4); }

FORCE_INLINE int32x2_t vdup_lane_s32(int32x2_t a, const int b) { return __riscv_vrgather_vx_i32m1(a, b, 2); }

FORCE_INLINE float32x2_t vdup_lane_f32(float32x2_t a, const int b) { return __riscv_vrgather_vx_f32m1(a, b, 2); }

FORCE_INLINE uint8x8_t vdup_lane_u8(uint8x8_t a, const int b) { return __riscv_vrgather_vx_u8m1(a, b, 8); }

FORCE_INLINE uint16x4_t vdup_lane_u16(uint16x4_t a, const int b) { return __riscv_vrgather_vx_u16m1(a, b, 4); }

FORCE_INLINE uint32x2_t vdup_lane_u32(uint32x2_t a, const int b) { return __riscv_vrgather_vx_u32m1(a, b, 2); }

FORCE_INLINE int64x1_t vdup_lane_s64(int64x1_t a, const int b) { return __riscv_vrgather_vx_i64m1(a, b, 1); }

FORCE_INLINE uint64x1_t vdup_lane_u64(uint64x1_t a, const int b) { return __riscv_vrgather_vx_u64m1(a, b, 1); }

FORCE_INLINE int8x16_t vdupq_lane_s8(int8x8_t a, const int b) { return __riscv_vrgather_vx_i8m1(a, b, 16); }

FORCE_INLINE int16x8_t vdupq_lane_s16(int16x4_t a, const int b) { return __riscv_vrgather_vx_i16m1(a, b, 8); }

FORCE_INLINE int32x4_t vdupq_lane_s32(int32x2_t a, const int b) { return __riscv_vrgather_vx_i32m1(a, b, 4); }

FORCE_INLINE float32x4_t vdupq_lane_f32(float32x2_t a, const int b) { return __riscv_vrgather_vx_f32m1(a, b, 4); }

// FORCE_INLINE poly8x8_t vdup_lane_p8(poly8x8_t vec, const int lane);

// FORCE_INLINE poly8x16_t vdupq_lane_p8(poly8x8_t vec, const int lane);

// FORCE_INLINE poly16x4_t vdup_lane_p16(poly16x4_t vec, const int lane);

// FORCE_INLINE poly16x8_t vdupq_lane_p16(poly16x4_t vec, const int lane);

FORCE_INLINE float64x1_t vdup_lane_f64(float64x1_t a, const int b) { return __riscv_vrgather_vx_f64m1(a, b, 1); }

FORCE_INLINE float64x2_t vdupq_lane_f64(float64x1_t a, const int b) { return __riscv_vrgather_vx_f64m1(a, b, 2); }

FORCE_INLINE int8x8_t vdup_laneq_s8(int8x16_t a, const int b) { return __riscv_vrgather_vx_i8m1(a, b, 8); }

FORCE_INLINE int8x16_t vdupq_laneq_s8(int8x16_t a, const int b) { return __riscv_vrgather_vx_i8m1(a, b, 16); }

FORCE_INLINE int16x4_t vdup_laneq_s16(int16x8_t a, const int b) { return __riscv_vrgather_vx_i16m1(a, b, 4); }

FORCE_INLINE int16x8_t vdupq_laneq_s16(int16x8_t a, const int b) { return __riscv_vrgather_vx_i16m1(a, b, 8); }

FORCE_INLINE int32x2_t vdup_laneq_s32(int32x4_t a, const int b) { return __riscv_vrgather_vx_i32m1(a, b, 2); }

FORCE_INLINE int32x4_t vdupq_laneq_s32(int32x4_t a, const int b) { return __riscv_vrgather_vx_i32m1(a, b, 4); }

FORCE_INLINE int64x1_t vdup_laneq_s64(int64x2_t a, const int b) { return __riscv_vrgather_vx_i64m1(a, b, 1); }

FORCE_INLINE int64x2_t vdupq_laneq_s64(int64x2_t a, const int b) { return __riscv_vrgather_vx_i64m1(a, b, 2); }

FORCE_INLINE uint8x8_t vdup_laneq_u8(uint8x16_t a, const int b) { return __riscv_vrgather_vx_u8m1(a, b, 8); }

FORCE_INLINE uint8x16_t vdupq_laneq_u8(uint8x16_t a, const int b) { return __riscv_vrgather_vx_u8m1(a, b, 16); }

FORCE_INLINE uint16x4_t vdup_laneq_u16(uint16x8_t a, const int b) { return __riscv_vrgather_vx_u16m1(a, b, 4); }

FORCE_INLINE uint16x8_t vdupq_laneq_u16(uint16x8_t a, const int b) { return __riscv_vrgather_vx_u16m1(a, b, 8); }

FORCE_INLINE uint32x2_t vdup_laneq_u32(uint32x4_t a, const int b) { return __riscv_vrgather_vx_u32m1(a, b, 2); }

FORCE_INLINE uint32x4_t vdupq_laneq_u32(uint32x4_t a, const int b) { return __riscv_vrgather_vx_u32m1(a, b, 4); }

FORCE_INLINE uint64x1_t vdup_laneq_u64(uint64x2_t a, const int b) { return __riscv_vrgather_vx_u64m1(a, b, 1); }

FORCE_INLINE uint64x2_t vdupq_laneq_u64(uint64x2_t a, const int b) { return __riscv_vrgather_vx_u64m1(a, b, 2); }

// FORCE_INLINE poly64x1_t vdup_laneq_p64(poly64x2_t a, const int b);

// FORCE_INLINE poly64x2_t vdupq_laneq_p64(poly64x2_t a, const int b);

FORCE_INLINE float32x2_t vdup_laneq_f32(float32x4_t a, const int b) { return __riscv_vrgather_vx_f32m1(a, b, 2); }

FORCE_INLINE float32x4_t vdupq_laneq_f32(float32x4_t a, const int b) { return __riscv_vrgather_vx_f32m1(a, b, 4); }

// FORCE_INLINE poly8x8_t vdup_laneq_p8(poly8x16_t a, const int b);

// FORCE_INLINE poly8x16_t vdupq_laneq_p8(poly8x16_t a, const int b);

// FORCE_INLINE poly16x4_t vdup_laneq_p16(poly16x8_t a, const int b);

// FORCE_INLINE poly16x8_t vdupq_laneq_p16(poly16x8_t a, const int b);

FORCE_INLINE float64x1_t vdup_laneq_f64(float64x2_t a, const int b) { return __riscv_vrgather_vx_f64m1(a, b, 1); }

FORCE_INLINE float64x2_t vdupq_laneq_f64(float64x2_t a, const int b) { return __riscv_vrgather_vx_f64m1(a, b, 2); }

FORCE_INLINE uint8x16_t vdupq_lane_u8(uint8x8_t a, const int b) { return __riscv_vrgather_vx_u8m1(a, b, 16); }

FORCE_INLINE uint16x8_t vdupq_lane_u16(uint16x4_t a, const int b) { return __riscv_vrgather_vx_u16m1(a, b, 8); }

FORCE_INLINE uint32x4_t vdupq_lane_u32(uint32x2_t a, const int b) { return __riscv_vrgather_vx_u32m1(a, b, 4); }

FORCE_INLINE int64x2_t vdupq_lane_s64(int64x1_t a, const int b) { return __riscv_vrgather_vx_i64m1(a, b, 2); }

FORCE_INLINE uint64x2_t vdupq_lane_u64(uint64x1_t a, const int b) { return __riscv_vrgather_vx_u64m1(a, b, 2); }

// FORCE_INLINE poly64x1_t vdup_lane_p64(poly64x1_t vec, const int lane);

// FORCE_INLINE poly64x2_t vdupq_lane_p64(poly64x1_t vec, const int lane);

FORCE_INLINE int8x16_t vcombine_s8(int8x8_t a, int8x8_t b) { return __riscv_vslideup_vx_i8m1(a, b, 8, 16); }

FORCE_INLINE int16x8_t vcombine_s16(int16x4_t a, int16x4_t b) { return __riscv_vslideup_vx_i16m1(a, b, 4, 8); }

FORCE_INLINE int32x4_t vcombine_s32(int32x2_t a, int32x2_t b) { return __riscv_vslideup_vx_i32m1(a, b, 2, 4); }

FORCE_INLINE int64x2_t vcombine_s64(int64x1_t a, int64x1_t b) { return __riscv_vslideup_vx_i64m1(a, b, 1, 2); }

FORCE_INLINE float32x4_t vcombine_f32(float32x2_t a, float32x2_t b) { return __riscv_vslideup_vx_f32m1(a, b, 2, 4); }

// FORCE_INLINE poly8x16_t vcombine_p8(poly8x8_t low, poly8x8_t high);

// FORCE_INLINE poly16x8_t vcombine_p16(poly16x4_t low, poly16x4_t high);

FORCE_INLINE float64x2_t vcombine_f64(float64x1_t a, float64x1_t b) { return __riscv_vslideup_vx_f64m1(a, b, 1, 2); }

FORCE_INLINE uint8x16_t vcombine_u8(uint8x8_t a, uint8x8_t b) { return __riscv_vslideup_vx_u8m1(a, b, 8, 16); }

FORCE_INLINE uint16x8_t vcombine_u16(uint16x4_t a, uint16x4_t b) { return __riscv_vslideup_vx_u16m1(a, b, 4, 8); }

FORCE_INLINE uint32x4_t vcombine_u32(uint32x2_t a, uint32x2_t b) { return __riscv_vslideup_vx_u32m1(a, b, 2, 4); }

FORCE_INLINE uint64x2_t vcombine_u64(uint64x1_t a, uint64x1_t b) { return __riscv_vslideup_vx_u64m1(a, b, 1, 2); }

// FORCE_INLINE poly64x2_t vcombine_p64(poly64x1_t low, poly64x1_t high);

// FORCE_INLINE float16x8_t vcombine_f16(float16x4_t low, float16x4_t high);

FORCE_INLINE int8x8_t vget_high_s8(int8x16_t a) { return __riscv_vslidedown_vx_i8m1(a, 8, 16); }

FORCE_INLINE int16x4_t vget_high_s16(int16x8_t a) { return __riscv_vslidedown_vx_i16m1(a, 4, 8); }

FORCE_INLINE int32x2_t vget_high_s32(int32x4_t a) { return __riscv_vslidedown_vx_i32m1(a, 2, 4); }

FORCE_INLINE int64x1_t vget_high_s64(int64x2_t a) { return __riscv_vslidedown_vx_i64m1(a, 1, 2); }

FORCE_INLINE float32x2_t vget_high_f32(float32x4_t a) { return __riscv_vslidedown_vx_f32m1(a, 2, 4); }

// FORCE_INLINE poly8x8_t vget_high_p8(poly8x16_t a);

// FORCE_INLINE poly16x4_t vget_high_p16(poly16x8_t a);

FORCE_INLINE float64x1_t vget_high_f64(float64x2_t a) { return __riscv_vslidedown_vx_f64m1(a, 1, 2); }

FORCE_INLINE uint8x8_t vget_high_u8(uint8x16_t a) { return __riscv_vslidedown_vx_u8m1(a, 8, 16); }

FORCE_INLINE uint16x4_t vget_high_u16(uint16x8_t a) { return __riscv_vslidedown_vx_u16m1(a, 4, 8); }

FORCE_INLINE uint32x2_t vget_high_u32(uint32x4_t a) { return __riscv_vslidedown_vx_u32m1(a, 2, 4); }

FORCE_INLINE uint64x1_t vget_high_u64(uint64x2_t a) { return __riscv_vslidedown_vx_u64m1(a, 1, 2); }

// FORCE_INLINE poly64x1_t vget_high_p64(poly64x2_t a);

// FORCE_INLINE float16x4_t vget_high_f16(float16x8_t a);

FORCE_INLINE int8x8_t vget_low_s8(int8x16_t a) { return a; }

FORCE_INLINE int16x4_t vget_low_s16(int16x8_t a) { return a; }

FORCE_INLINE int32x2_t vget_low_s32(int32x4_t a) { return a; }

FORCE_INLINE float32x2_t vget_low_f32(float32x4_t a) { return a; }

// FORCE_INLINE poly8x8_t vget_low_p8(poly8x16_t a);

// FORCE_INLINE poly16x4_t vget_low_p16(poly16x8_t a);

FORCE_INLINE float64x1_t vget_low_f64(float64x2_t a) { return a; }

FORCE_INLINE int8_t vdupb_lane_s8(int8x8_t a, const int lane) {
  return __riscv_vmv_x_s_i8m1_i8(__riscv_vslidedown_vx_i8m1(a, lane, 8));
}

FORCE_INLINE int16_t vduph_lane_s16(int16x4_t a, const int lane) {
  return __riscv_vmv_x_s_i16m1_i16(__riscv_vslidedown_vx_i16m1(a, lane, 4));
}

FORCE_INLINE int32_t vdups_lane_s32(int32x2_t a, const int lane) {
  return __riscv_vmv_x_s_i32m1_i32(__riscv_vslidedown_vx_i32m1(a, lane, 2));
}

FORCE_INLINE int64_t vdupd_lane_s64(int64x1_t a, const int lane) { return __riscv_vmv_x_s_i64m1_i64(a); }

FORCE_INLINE uint8_t vdupb_lane_u8(uint8x8_t a, const int lane) {
  return __riscv_vmv_x_s_u8m1_u8(__riscv_vslidedown_vx_u8m1(a, lane, 8));
}

FORCE_INLINE uint16_t vduph_lane_u16(uint16x4_t a, const int lane) {
  return __riscv_vmv_x_s_u16m1_u16(__riscv_vslidedown_vx_u16m1(a, lane, 4));
}

FORCE_INLINE uint32_t vdups_lane_u32(uint32x2_t a, const int lane) {
  return __riscv_vmv_x_s_u32m1_u32(__riscv_vslidedown_vx_u32m1(a, lane, 2));
}

FORCE_INLINE uint64_t vdupd_lane_u64(uint64x1_t a, const int lane) { return __riscv_vmv_x_s_u64m1_u64(a); }

FORCE_INLINE float32_t vdups_lane_f32(float32x2_t a, const int lane) {
  return __riscv_vfmv_f_s_f32m1_f32(__riscv_vslidedown_vx_f32m1(a, lane, 2));
}

FORCE_INLINE float64_t vdupd_lane_f64(float64x1_t a, const int lane) { return __riscv_vfmv_f_s_f64m1_f64(a); }

// FORCE_INLINE poly8_t vdupb_lane_p8(poly8x8_t vec, const int lane);

// FORCE_INLINE poly16_t vduph_lane_p16(poly16x4_t vec, const int lane);

FORCE_INLINE int8_t vdupb_laneq_s8(int8x16_t a, const int lane) {
  return __riscv_vmv_x_s_i8m1_i8(__riscv_vslidedown_vx_i8m1(a, lane, 16));
}

FORCE_INLINE int16_t vduph_laneq_s16(int16x8_t a, const int lane) {
  return __riscv_vmv_x_s_i16m1_i16(__riscv_vslidedown_vx_i16m1(a, lane, 8));
}

FORCE_INLINE int32_t vdups_laneq_s32(int32x4_t a, const int lane) {
  return __riscv_vmv_x_s_i32m1_i32(__riscv_vslidedown_vx_i32m1(a, lane, 4));
}

FORCE_INLINE int64_t vdupd_laneq_s64(int64x2_t a, const int lane) {
  return __riscv_vmv_x_s_i64m1_i64(__riscv_vslidedown_vx_i64m1(a, lane, 2));
}

FORCE_INLINE uint8_t vdupb_laneq_u8(uint8x16_t a, const int lane) {
  return __riscv_vmv_x_s_u8m1_u8(__riscv_vslidedown_vx_u8m1(a, lane, 16));
}

FORCE_INLINE uint16_t vduph_laneq_u16(uint16x8_t a, const int lane) {
  return __riscv_vmv_x_s_u16m1_u16(__riscv_vslidedown_vx_u16m1(a, lane, 8));
}

FORCE_INLINE uint32_t vdups_laneq_u32(uint32x4_t a, const int lane) {
  return __riscv_vmv_x_s_u32m1_u32(__riscv_vslidedown_vx_u32m1(a, lane, 4));
}

FORCE_INLINE uint64_t vdupd_laneq_u64(uint64x2_t a, const int lane) {
  return __riscv_vmv_x_s_u64m1_u64(__riscv_vslidedown_vx_u64m1(a, lane, 2));
}

FORCE_INLINE float32_t vdups_laneq_f32(float32x4_t a, const int lane) {
  return __riscv_vfmv_f_s_f32m1_f32(__riscv_vslidedown_vx_f32m1(a, lane, 2));
}

FORCE_INLINE float64_t vdupd_laneq_f64(float64x2_t a, const int lane) {
  return __riscv_vfmv_f_s_f64m1_f64(__riscv_vslidedown_vx_f64m1(a, lane, 2));
}

// FORCE_INLINE poly8_t vdupb_laneq_p8(poly8x16_t vec, const int lane);

// FORCE_INLINE poly16_t vduph_laneq_p16(poly16x8_t vec, const int lane);

FORCE_INLINE uint8x8_t vget_low_u8(uint8x16_t a) { return a; }

FORCE_INLINE uint16x4_t vget_low_u16(uint16x8_t a) { return a; }

FORCE_INLINE uint32x2_t vget_low_u32(uint32x4_t a) { return a; }

FORCE_INLINE int64x1_t vget_low_s64(int64x2_t a) { return a; }

FORCE_INLINE uint64x1_t vget_low_u64(uint64x2_t a) { return a; }

// FORCE_INLINE poly64x1_t vget_low_p64(poly64x2_t a);

// FORCE_INLINE float16x4_t vget_low_f16(float16x8_t a);

FORCE_INLINE int32x2_t vcvt_s32_f32(float32x2_t a) { return __riscv_vfcvt_rtz_x_f_v_i32m1(a, 2); }

FORCE_INLINE float32x2_t vcvt_f32_s32(int32x2_t a) { return __riscv_vfcvt_f_x_v_f32m1(a, 2); }

FORCE_INLINE float32x2_t vcvt_f32_u32(uint32x2_t a) { return __riscv_vfcvt_f_xu_v_f32m1(a, 2); }

FORCE_INLINE uint32x2_t vcvt_u32_f32(float32x2_t a) { return __riscv_vfcvt_rtz_xu_f_v_u32m1(a, 2); }

FORCE_INLINE int32x4_t vcvtq_s32_f32(float32x4_t a) { return __riscv_vfcvt_rtz_x_f_v_i32m1(a, 4); }

FORCE_INLINE float32x4_t vcvtq_f32_s32(int32x4_t a) { return __riscv_vfcvt_f_x_v_f32m1(a, 4); }

FORCE_INLINE float32x4_t vcvtq_f32_u32(uint32x4_t a) { return __riscv_vfcvt_f_xu_v_f32m1(a, 4); }

FORCE_INLINE float32_t vcvts_f32_s32(int32_t a) { return (float32_t)a; }

FORCE_INLINE float32_t vcvts_f32_u32(uint32_t a) { return (float32_t)a; }

FORCE_INLINE float64x1_t vcvt_f64_s64(int64x1_t a) { return __riscv_vfcvt_f_x_v_f64m1(a, 1); }

FORCE_INLINE float64x2_t vcvtq_f64_s64(int64x2_t a) { return __riscv_vfcvt_f_x_v_f64m1(a, 2); }

FORCE_INLINE float64x1_t vcvt_f64_u64(uint64x1_t a) { return __riscv_vfcvt_f_xu_v_f64m1(a, 1); }

FORCE_INLINE float64x2_t vcvtq_f64_u64(uint64x2_t a) { return __riscv_vfcvt_f_xu_v_f64m1(a, 2); }

FORCE_INLINE float64_t vcvtd_f64_s64(int64_t a) { return (float64_t)a; }

FORCE_INLINE float64_t vcvtd_f64_u64(uint64_t a) { return (float64_t)a; }

FORCE_INLINE uint32x4_t vcvtq_u32_f32(float32x4_t a) { return __riscv_vfcvt_rtz_xu_f_v_u32m1(a, 4); }

// FORCE_INLINE int32x2_t vcvtn_s32_f32(float32x2_t a);

// FORCE_INLINE int32x4_t vcvtnq_s32_f32(float32x4_t a);

// FORCE_INLINE uint32x2_t vcvtn_u32_f32(float32x2_t a);

// FORCE_INLINE uint32x4_t vcvtnq_u32_f32(float32x4_t a);

// FORCE_INLINE int32x2_t vcvtm_s32_f32(float32x2_t a);

// FORCE_INLINE int32x4_t vcvtmq_s32_f32(float32x4_t a);

// FORCE_INLINE uint32x2_t vcvtm_u32_f32(float32x2_t a);

// FORCE_INLINE uint32x4_t vcvtmq_u32_f32(float32x4_t a);

// FORCE_INLINE int32x2_t vcvtp_s32_f32(float32x2_t a);

// FORCE_INLINE int32x4_t vcvtpq_s32_f32(float32x4_t a);

// FORCE_INLINE uint32x2_t vcvtp_u32_f32(float32x2_t a);

// FORCE_INLINE uint32x4_t vcvtpq_u32_f32(float32x4_t a);

// FORCE_INLINE int32x2_t vcvta_s32_f32(float32x2_t a);

// FORCE_INLINE int32x4_t vcvtaq_s32_f32(float32x4_t a);

// FORCE_INLINE uint32x2_t vcvta_u32_f32(float32x2_t a);

// FORCE_INLINE uint32x4_t vcvtaq_u32_f32(float32x4_t a);

// FORCE_INLINE int32_t vcvts_s32_f32(float32_t a);

// FORCE_INLINE uint32_t vcvts_u32_f32(float32_t a);

// FORCE_INLINE int32_t vcvtns_s32_f32(float32_t a);

// FORCE_INLINE uint32_t vcvtns_u32_f32(float32_t a);

// FORCE_INLINE int32_t vcvtms_s32_f32(float32_t a);

// FORCE_INLINE uint32_t vcvtms_u32_f32(float32_t a);

// FORCE_INLINE int32_t vcvtps_s32_f32(float32_t a);

// FORCE_INLINE uint32_t vcvtps_u32_f32(float32_t a);

// FORCE_INLINE int32_t vcvtas_s32_f32(float32_t a);

// FORCE_INLINE uint32_t vcvtas_u32_f32(float32_t a);

FORCE_INLINE int64x1_t vcvt_s64_f64(float64x1_t a) { return __riscv_vfcvt_rtz_x_f_v_i64m1(a, 1); }

FORCE_INLINE int64x2_t vcvtq_s64_f64(float64x2_t a) { return __riscv_vfcvt_rtz_x_f_v_i64m1(a, 2); }

FORCE_INLINE uint64x1_t vcvt_u64_f64(float64x1_t a) { return __riscv_vfcvt_rtz_xu_f_v_u64m1(a, 1); }

FORCE_INLINE uint64x2_t vcvtq_u64_f64(float64x2_t a) { return __riscv_vfcvt_rtz_xu_f_v_u64m1(a, 2); }

// FORCE_INLINE int64x1_t vcvtn_s64_f64(float64x1_t a);

// FORCE_INLINE int64x2_t vcvtnq_s64_f64(float64x2_t a);

// FORCE_INLINE uint64x1_t vcvtn_u64_f64(float64x1_t a);

// FORCE_INLINE uint64x2_t vcvtnq_u64_f64(float64x2_t a);

// FORCE_INLINE int64x1_t vcvtm_s64_f64(float64x1_t a);

// FORCE_INLINE int64x2_t vcvtmq_s64_f64(float64x2_t a);

// FORCE_INLINE uint64x1_t vcvtm_u64_f64(float64x1_t a);

// FORCE_INLINE uint64x2_t vcvtmq_u64_f64(float64x2_t a);

// FORCE_INLINE int64x1_t vcvtp_s64_f64(float64x1_t a);

// FORCE_INLINE int64x2_t vcvtpq_s64_f64(float64x2_t a);

// FORCE_INLINE uint64x1_t vcvtp_u64_f64(float64x1_t a);

// FORCE_INLINE uint64x2_t vcvtpq_u64_f64(float64x2_t a);

// FORCE_INLINE int64x1_t vcvta_s64_f64(float64x1_t a);

// FORCE_INLINE int64x2_t vcvtaq_s64_f64(float64x2_t a);

// FORCE_INLINE uint64x1_t vcvta_u64_f64(float64x1_t a);

// FORCE_INLINE uint64x2_t vcvtaq_u64_f64(float64x2_t a);

FORCE_INLINE int64_t vcvtd_s64_f64(float64_t a) { return (int64_t)a; }

FORCE_INLINE uint64_t vcvtd_u64_f64(float64_t a) { return (uint64_t)a; }

// FORCE_INLINE int64_t vcvtnd_s64_f64(float64_t a);

// FORCE_INLINE uint64_t vcvtnd_u64_f64(float64_t a);

// FORCE_INLINE int64_t vcvtmd_s64_f64(float64_t a);

// FORCE_INLINE uint64_t vcvtmd_u64_f64(float64_t a);

// FORCE_INLINE int64_t vcvtpd_s64_f64(float64_t a);

// FORCE_INLINE uint64_t vcvtpd_u64_f64(float64_t a);

// FORCE_INLINE int64_t vcvtad_s64_f64(float64_t a);

// FORCE_INLINE uint64_t vcvtad_u64_f64(float64_t a);

FORCE_INLINE int32x2_t vcvt_n_s32_f32(float32x2_t a, const int b) {
  vfloat32m1_t a_mul_pow2_b = __riscv_vfmul_vf_f32m1(a, (uint64_t)1 << b, 2);
  return __riscv_vfcvt_rtz_x_f_v_i32m1(a_mul_pow2_b, 2);
}

// FORCE_INLINE float32x2_t vcvt_n_f32_s32(int32x2_t a, const int b);

// FORCE_INLINE float32x2_t vcvt_n_f32_u32(uint32x2_t a, const int b);

// FORCE_INLINE uint32x2_t vcvt_n_u32_f32(float32x2_t a, const int b);

// FORCE_INLINE int32x4_t vcvtq_n_s32_f32(float32x4_t a, const int b);

// FORCE_INLINE float32x4_t vcvtq_n_f32_s32(int32x4_t a, const int b);

// FORCE_INLINE float32x4_t vcvtq_n_f32_u32(uint32x4_t a, const int b);

// FORCE_INLINE float32_t vcvts_n_f32_s32(int32_t a, const int n);

// FORCE_INLINE float32_t vcvts_n_f32_u32(uint32_t a, const int n);

// FORCE_INLINE float64x1_t vcvt_n_f64_s64(int64x1_t a, const int n);

// FORCE_INLINE float64x2_t vcvtq_n_f64_s64(int64x2_t a, const int n);

// FORCE_INLINE float64x1_t vcvt_n_f64_u64(uint64x1_t a, const int n);

// FORCE_INLINE float64x2_t vcvtq_n_f64_u64(uint64x2_t a, const int n);

// FORCE_INLINE float64_t vcvtd_n_f64_s64(int64_t a, const int n);

// FORCE_INLINE float64_t vcvtd_n_f64_u64(uint64_t a, const int n);

// FORCE_INLINE float16x4_t vcvt_f16_f32(float32x4_t a);

// FORCE_INLINE float16x8_t vcvt_high_f16_f32(float16x4_t r, float32x4_t a);

// FORCE_INLINE float32x2_t vcvt_f32_f64(float64x2_t a);

// FORCE_INLINE float32x4_t vcvt_high_f32_f64(float32x2_t r, float64x2_t a);

// FORCE_INLINE float32x4_t vcvt_f32_f16(float16x4_t a);

// FORCE_INLINE float32x4_t vcvt_high_f32_f16(float16x8_t a);

// FORCE_INLINE float64x2_t vcvt_f64_f32(float32x2_t a);

// FORCE_INLINE float64x2_t vcvt_high_f64_f32(float32x4_t a);

// FORCE_INLINE float32x2_t vcvtx_f32_f64(float64x2_t a);

// FORCE_INLINE float32_t vcvtxd_f32_f64(float64_t a);

// FORCE_INLINE float32x4_t vcvtx_high_f32_f64(float32x2_t r, float64x2_t a);

// FORCE_INLINE uint32x4_t vcvtq_n_u32_f32(float32x4_t a, const int b);

// FORCE_INLINE int32_t vcvts_n_s32_f32(float32_t a, const int n);

// FORCE_INLINE uint32_t vcvts_n_u32_f32(float32_t a, const int n);

// FORCE_INLINE int64x1_t vcvt_n_s64_f64(float64x1_t a, const int n);

// FORCE_INLINE int64x2_t vcvtq_n_s64_f64(float64x2_t a, const int n);

// FORCE_INLINE uint64x1_t vcvt_n_u64_f64(float64x1_t a, const int n);

// FORCE_INLINE uint64x2_t vcvtq_n_u64_f64(float64x2_t a, const int n);

// FORCE_INLINE int64_t vcvtd_n_s64_f64(float64_t a, const int n);

// FORCE_INLINE uint64_t vcvtd_n_u64_f64(float64_t a, const int n);

FORCE_INLINE int8x8_t vmovn_s16(int16x8_t a) { return __riscv_vnsra_wx_i8m1(__riscv_vlmul_ext_v_i16m1_i16m2(a), 0, 8); }

FORCE_INLINE int16x4_t vmovn_s32(int32x4_t a) {
  return __riscv_vnsra_wx_i16m1(__riscv_vlmul_ext_v_i32m1_i32m2(a), 0, 4);
}

FORCE_INLINE int32x2_t vmovn_s64(int64x2_t a) {
  return __riscv_vnsra_wx_i32m1(__riscv_vlmul_ext_v_i64m1_i64m2(a), 0, 2);
}

FORCE_INLINE uint8x8_t vmovn_u16(uint16x8_t a) {
  return __riscv_vnsrl_wx_u8m1(__riscv_vlmul_ext_v_u16m1_u16m2(a), 0, 8);
}

FORCE_INLINE uint16x4_t vmovn_u32(uint32x4_t a) {
  return __riscv_vnsrl_wx_u16m1(__riscv_vlmul_ext_v_u32m1_u32m2(a), 0, 4);
}

FORCE_INLINE uint32x2_t vmovn_u64(uint64x2_t a) {
  return __riscv_vnsrl_wx_u32m1(__riscv_vlmul_ext_v_u64m1_u64m2(a), 0, 2);
}

FORCE_INLINE int8x16_t vmovn_high_s16(int8x8_t r, int16x8_t a) {
  vint8m1_t movn = __riscv_vlmul_ext_v_i8mf2_i8m1(__riscv_vnsra_wx_i8mf2(a, 0, 8));
  return __riscv_vslideup_vx_i8m1(r, movn, 8, 16);
}

FORCE_INLINE int16x8_t vmovn_high_s32(int16x4_t r, int32x4_t a) {
  vint16m1_t movn = __riscv_vlmul_ext_v_i16mf2_i16m1(__riscv_vnsra_wx_i16mf2(a, 0, 4));
  return __riscv_vslideup_vx_i16m1(r, movn, 4, 8);
}

FORCE_INLINE int32x4_t vmovn_high_s64(int32x2_t r, int64x2_t a) {
  vint32m1_t movn = __riscv_vlmul_ext_v_i32mf2_i32m1(__riscv_vnsra_wx_i32mf2(a, 0, 2));
  return __riscv_vslideup_vx_i32m1(r, movn, 2, 4);
}

FORCE_INLINE uint8x16_t vmovn_high_u16(uint8x8_t r, uint16x8_t a) {
  vuint8m1_t movn = __riscv_vlmul_ext_v_u8mf2_u8m1(__riscv_vnsrl_wx_u8mf2(a, 0, 8));
  return __riscv_vslideup_vx_u8m1(r, movn, 8, 16);
}

FORCE_INLINE uint16x8_t vmovn_high_u32(uint16x4_t r, uint32x4_t a) {
  vuint16m1_t movn = __riscv_vlmul_ext_v_u16mf2_u16m1(__riscv_vnsrl_wx_u16mf2(a, 0, 4));
  return __riscv_vslideup_vx_u16m1(r, movn, 4, 8);
}

FORCE_INLINE uint32x4_t vmovn_high_u64(uint32x2_t r, uint64x2_t a) {
  vuint32m1_t movn = __riscv_vlmul_ext_v_u32mf2_u32m1(__riscv_vnsrl_wx_u32mf2(a, 0, 2));
  return __riscv_vslideup_vx_u32m1(r, movn, 2, 4);
}

FORCE_INLINE int8x8_t vqmovn_s16(int16x8_t a) {
  return __riscv_vlmul_ext_v_i8mf2_i8m1(__riscv_vnclip_wx_i8mf2(a, 0, __RISCV_VXRM_RDN, 8));
}

FORCE_INLINE int16x4_t vqmovn_s32(int32x4_t a) {
  return __riscv_vlmul_ext_v_i16mf2_i16m1(__riscv_vnclip_wx_i16mf2(a, 0, __RISCV_VXRM_RDN, 4));
}

FORCE_INLINE int32x2_t vqmovn_s64(int64x2_t a) {
  return __riscv_vlmul_ext_v_i32mf2_i32m1(__riscv_vnclip_wx_i32mf2(a, 0, __RISCV_VXRM_RDN, 2));
}

FORCE_INLINE uint8x8_t vqmovn_u16(uint16x8_t a) {
  return __riscv_vlmul_ext_v_u8mf2_u8m1(__riscv_vnclipu_wx_u8mf2(a, 0, __RISCV_VXRM_RDN, 8));
}

FORCE_INLINE uint16x4_t vqmovn_u32(uint32x4_t a) {
  return __riscv_vlmul_ext_v_u16mf2_u16m1(__riscv_vnclipu_wx_u16mf2(a, 0, __RISCV_VXRM_RDN, 4));
}

FORCE_INLINE uint32x2_t vqmovn_u64(uint64x2_t a) {
  return __riscv_vlmul_ext_v_u32mf2_u32m1(__riscv_vnclipu_wx_u32mf2(a, 0, __RISCV_VXRM_RDN, 2));
}

FORCE_INLINE int8_t vqmovnh_s16(int16_t a) {
  if (a > INT8_MAX)
    return (int8_t)INT8_MAX;
  if (a < INT8_MIN)
    return (int8_t)INT8_MIN;
  return (int8_t)a;
}

FORCE_INLINE int16_t vqmovns_s32(int32_t a) {
  if (a > INT16_MAX)
    return (int16_t)INT16_MAX;
  if (a < INT16_MIN)
    return (int16_t)INT16_MIN;
  return (int16_t)a;
}

FORCE_INLINE int32_t vqmovnd_s64(int64_t a) {
  if (a > INT32_MAX)
    return (int32_t)INT32_MAX;
  if (a < INT32_MIN)
    return (int32_t)INT32_MIN;
  return (int32_t)a;
}

FORCE_INLINE uint8_t vqmovnh_u16(uint16_t a) {
  if (a > UINT8_MAX) {
    return (uint8_t)UINT8_MAX;
  } else if (a < 0) {
    return 0;
  }
  return (uint8_t)a;
}

FORCE_INLINE uint16_t vqmovns_u32(uint32_t a) {
  if (a > UINT16_MAX) {
    return (uint16_t)UINT16_MAX;
  } else if (a < 0) {
    return 0;
  }
  return a;
}

FORCE_INLINE uint32_t vqmovnd_u64(uint64_t a) {
  if (a > UINT32_MAX) {
    return (uint32_t)UINT32_MAX;
  } else if (a < 0) {
    return 0;
  }
  return a;
}

FORCE_INLINE int8x16_t vqmovn_high_s16(int8x8_t r, int16x8_t a) {
  vint8m1_t qmovn = __riscv_vlmul_ext_v_i8mf2_i8m1(__riscv_vnclip_wx_i8mf2(a, 0, __RISCV_VXRM_RDN, 8));
  return __riscv_vslideup_vx_i8m1(r, qmovn, 8, 16);
}

FORCE_INLINE int16x8_t vqmovn_high_s32(int16x4_t r, int32x4_t a) {
  vint16m1_t qmovn = __riscv_vlmul_ext_v_i16mf2_i16m1(__riscv_vnclip_wx_i16mf2(a, 0, __RISCV_VXRM_RDN, 4));
  return __riscv_vslideup_vx_i16m1(r, qmovn, 4, 8);
}

FORCE_INLINE int32x4_t vqmovn_high_s64(int32x2_t r, int64x2_t a) {
  vint32m1_t qmovn = __riscv_vlmul_ext_v_i32mf2_i32m1(__riscv_vnclip_wx_i32mf2(a, 0, __RISCV_VXRM_RDN, 2));
  return __riscv_vslideup_vx_i32m1(r, qmovn, 2, 4);
}

FORCE_INLINE uint8x16_t vqmovn_high_u16(uint8x8_t r, uint16x8_t a) {
  vuint8m1_t qmovn = __riscv_vlmul_ext_v_u8mf2_u8m1(__riscv_vnclipu_wx_u8mf2(a, 0, __RISCV_VXRM_RDN, 8));
  return __riscv_vslideup_vx_u8m1(r, qmovn, 8, 16);
}

FORCE_INLINE uint16x8_t vqmovn_high_u32(uint16x4_t r, uint32x4_t a) {
  vuint16m1_t qmovn = __riscv_vlmul_ext_v_u16mf2_u16m1(__riscv_vnclipu_wx_u16mf2(a, 0, __RISCV_VXRM_RDN, 4));
  return __riscv_vslideup_vx_u16m1(r, qmovn, 4, 8);
}

FORCE_INLINE uint32x4_t vqmovn_high_u64(uint32x2_t r, uint64x2_t a) {
  vuint32m1_t qmovn = __riscv_vlmul_ext_v_u32mf2_u32m1(__riscv_vnclipu_wx_u32mf2(a, 0, __RISCV_VXRM_RDN, 2));
  return __riscv_vslideup_vx_u32m1(r, qmovn, 2, 4);
}

FORCE_INLINE uint8x8_t vqmovun_s16(int16x8_t a) {
  vuint16m1_t a_non_neg = __riscv_vreinterpret_v_i16m1_u16m1(__riscv_vmax_vx_i16m1(a, 0, 8));
  return __riscv_vlmul_ext_v_u8mf2_u8m1(__riscv_vnclipu_wx_u8mf2(a_non_neg, 0, __RISCV_VXRM_RDN, 8));
}

FORCE_INLINE uint16x4_t vqmovun_s32(int32x4_t a) {
  vuint32m1_t a_non_neg = __riscv_vreinterpret_v_i32m1_u32m1(__riscv_vmax_vx_i32m1(a, 0, 4));
  return __riscv_vlmul_ext_v_u16mf2_u16m1(__riscv_vnclipu_wx_u16mf2(a_non_neg, 0, __RISCV_VXRM_RDN, 4));
}

FORCE_INLINE uint32x2_t vqmovun_s64(int64x2_t a) {
  vuint64m1_t a_non_neg = __riscv_vreinterpret_v_i64m1_u64m1(__riscv_vmax_vx_i64m1(a, 0, 2));
  return __riscv_vlmul_ext_v_u32mf2_u32m1(__riscv_vnclipu_wx_u32mf2(a_non_neg, 0, __RISCV_VXRM_RDN, 2));
}

FORCE_INLINE uint8_t vqmovunh_s16(int16_t a) {
  if (a > UINT8_MAX) {
    return UINT8_MAX;
  }
  int16_t a_sign = ~(a >> 15);
  return a & a_sign;
}

FORCE_INLINE uint16_t vqmovuns_s32(int32_t a) {
  if (a > UINT16_MAX) {
    return UINT16_MAX;
  }
  int32_t a_sign = ~(a >> 31);
  return a & a_sign;
}

FORCE_INLINE uint32_t vqmovund_s64(int64_t a) {
  if (a > UINT32_MAX) {
    return UINT32_MAX;
  }
  int64_t a_sign = ~(a >> 63);
  return a & a_sign;
}

FORCE_INLINE uint8x16_t vqmovun_high_s16(uint8x8_t r, int16x8_t a) {
  vuint16m1_t a_non_neg = __riscv_vreinterpret_v_i16m1_u16m1(__riscv_vmax_vx_i16m1(a, 0, 8));
  vuint8m1_t vqmovun = __riscv_vlmul_ext_v_u8mf2_u8m1(__riscv_vnclipu_wx_u8mf2(a_non_neg, 0, __RISCV_VXRM_RDN, 8));
  return __riscv_vslideup_vx_u8m1(r, vqmovun, 8, 16);
}

FORCE_INLINE uint16x8_t vqmovun_high_s32(uint16x4_t r, int32x4_t a) {
  vuint32m1_t a_non_neg = __riscv_vreinterpret_v_i32m1_u32m1(__riscv_vmax_vx_i32m1(a, 0, 4));
  vuint16m1_t vqmovun = __riscv_vlmul_ext_v_u16mf2_u16m1(__riscv_vnclipu_wx_u16mf2(a_non_neg, 0, __RISCV_VXRM_RDN, 4));
  return __riscv_vslideup_vx_u16m1(r, vqmovun, 4, 8);
}

FORCE_INLINE uint32x4_t vqmovun_high_s64(uint32x2_t r, int64x2_t a) {
  vuint64m1_t a_non_neg = __riscv_vreinterpret_v_i64m1_u64m1(__riscv_vmax_vx_i64m1(a, 0, 2));
  vuint32m1_t vqmovun = __riscv_vlmul_ext_v_u32mf2_u32m1(__riscv_vnclipu_wx_u32mf2(a_non_neg, 0, __RISCV_VXRM_RDN, 2));
  return __riscv_vslideup_vx_u32m1(r, vqmovun, 2, 4);
}

FORCE_INLINE int16x8_t vmovl_s8(int8x8_t a) { return __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vsext_vf2_i16m2(a, 8)); }

FORCE_INLINE int32x4_t vmovl_s16(int16x4_t a) {
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vsext_vf2_i32m2(a, 4));
}

FORCE_INLINE int64x2_t vmovl_s32(int32x2_t a) {
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vsext_vf2_i64m2(a, 2));
}

FORCE_INLINE uint16x8_t vmovl_u8(uint8x8_t a) {
  return __riscv_vlmul_trunc_v_u16m2_u16m1(__riscv_vzext_vf2_u16m2(a, 8));
}

FORCE_INLINE uint32x4_t vmovl_u16(uint16x4_t a) {
  return __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vzext_vf2_u32m2(a, 4));
}

FORCE_INLINE uint64x2_t vmovl_u32(uint32x2_t a) {
  return __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vzext_vf2_u64m2(a, 2));
}

FORCE_INLINE int16x8_t vmovl_high_s8(int8x16_t a) {
  vint8m1_t a_high = __riscv_vslidedown_vx_i8m1(a, 8, 16);
  return __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vsext_vf2_i16m2(a_high, 8));
}

FORCE_INLINE int32x4_t vmovl_high_s16(int16x8_t a) {
  vint16m1_t a_high = __riscv_vslidedown_vx_i16m1(a, 4, 8);
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vsext_vf2_i32m2(a_high, 4));
}

FORCE_INLINE int64x2_t vmovl_high_s32(int32x4_t a) {
  vint32m1_t a_high = __riscv_vslidedown_vx_i32m1(a, 2, 4);
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vsext_vf2_i64m2(a_high, 2));
}

FORCE_INLINE uint16x8_t vmovl_high_u8(uint8x16_t a) {
  vuint8m1_t a_high = __riscv_vslidedown_vx_u8m1(a, 8, 16);
  return __riscv_vlmul_trunc_v_u16m2_u16m1(__riscv_vzext_vf2_u16m2(a_high, 8));
}

FORCE_INLINE uint32x4_t vmovl_high_u16(uint16x8_t a) {
  vuint16m1_t a_high = __riscv_vslidedown_vx_u16m1(a, 4, 8);
  return __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vzext_vf2_u32m2(a_high, 4));
}

FORCE_INLINE uint64x2_t vmovl_high_u32(uint32x4_t a) {
  vuint32m1_t a_high = __riscv_vslidedown_vx_u32m1(a, 2, 4);
  return __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vzext_vf2_u64m2(a_high, 2));
}

FORCE_INLINE int8x8_t vtbl1_s8(int8x8_t a, int8x8_t b) {
  vbool8_t mask = __riscv_vmsge_vx_i8m1_b8(b, 8, 8);
  return __riscv_vmerge_vxm_i8m1(__riscv_vrgather_vv_i8m1(a, __riscv_vreinterpret_v_i8m1_u8m1(b), 8), 0, mask, 8);
}

FORCE_INLINE uint8x8_t vtbl1_u8(uint8x8_t a, uint8x8_t b) {
  vbool8_t mask = __riscv_vmsgeu_vx_u8m1_b8(b, 8, 8);
  return __riscv_vmerge_vxm_u8m1(__riscv_vrgather_vv_u8m1(a, b, 8), 0, mask, 8);
}

// FORCE_INLINE poly8x8_t vtbl1_p8(poly8x8_t a, uint8x8_t idx);

FORCE_INLINE int8x8_t vtbl2_s8(int8x8x2_t a, int8x8_t b) {
  vint8m1_t table1 = __riscv_vget_v_i8m1x2_i8m1(a, 0);
  vint8m1_t table2 = __riscv_vget_v_i8m1x2_i8m1(a, 1);
  vint8m1_t table = __riscv_vslideup_vx_i8m1(table1, table2, 8, 16);
  vbool8_t mask = __riscv_vmsge_vx_i8m1_b8(b, 16, 8);
  return __riscv_vmerge_vxm_i8m1(__riscv_vrgather_vv_i8m1(table, __riscv_vreinterpret_v_i8m1_u8m1(b), 8), 0, mask, 8);
}

FORCE_INLINE uint8x8_t vtbl2_u8(uint8x8x2_t a, uint8x8_t b) {
  vuint8m1_t table1 = __riscv_vget_v_u8m1x2_u8m1(a, 0);
  vuint8m1_t table2 = __riscv_vget_v_u8m1x2_u8m1(a, 1);
  vuint8m1_t table = __riscv_vslideup_vx_u8m1(table1, table2, 8, 16);
  vbool8_t mask = __riscv_vmsgeu_vx_u8m1_b8(b, 16, 8);
  return __riscv_vmerge_vxm_u8m1(__riscv_vrgather_vv_u8m1(table, b, 8), 0, mask, 8);
}

// FORCE_INLINE poly8x8_t vtbl2_p8(poly8x8x2_t a, uint8x8_t idx);

FORCE_INLINE int8x8_t vtbl3_s8(int8x8x3_t a, int8x8_t b) {
  vint8m1_t table1 = __riscv_vget_v_i8m1x3_i8m1(a, 0);
  vint8m1_t table2 = __riscv_vget_v_i8m1x3_i8m1(a, 1);
  vint8m1_t table3 = __riscv_vget_v_i8m1x3_i8m1(a, 2);
  vint8m2_t table12 = __riscv_vlmul_ext_v_i8m1_i8m2(__riscv_vslideup_vx_i8m1(table1, table2, 8, 16));
  vint8m2_t table34 = __riscv_vlmul_ext_v_i8m1_i8m2(__riscv_vslideup_vx_i8m1(table3, vdup_n_s8(0), 8, 16));
  vint8m2_t table = __riscv_vslideup_vx_i8m2(table12, table34, 16, 32);
  vint8m1_t gather = __riscv_vlmul_trunc_v_i8m2_i8m1(
      __riscv_vrgather_vv_i8m2(table, __riscv_vlmul_ext_v_u8m1_u8m2(__riscv_vreinterpret_v_i8m1_u8m1(b)), 8));
  vbool8_t mask = __riscv_vmsge_vx_i8m1_b8(b, 24, 8);
  return __riscv_vmerge_vxm_i8m1(gather, 0, mask, 8);
}

FORCE_INLINE uint8x8_t vtbl3_u8(uint8x8x3_t a, uint8x8_t b) {
  vuint8m1_t table1 = __riscv_vget_v_u8m1x3_u8m1(a, 0);
  vuint8m1_t table2 = __riscv_vget_v_u8m1x3_u8m1(a, 1);
  vuint8m1_t table3 = __riscv_vget_v_u8m1x3_u8m1(a, 2);
  vuint8m2_t table12 = __riscv_vlmul_ext_v_u8m1_u8m2(__riscv_vslideup_vx_u8m1(table1, table2, 8, 16));
  vuint8m2_t table34 = __riscv_vlmul_ext_v_u8m1_u8m2(__riscv_vslideup_vx_u8m1(table3, vdup_n_u8(0), 8, 16));
  vuint8m2_t table = __riscv_vslideup_vx_u8m2(table12, table34, 16, 32);
  vuint8m1_t gather =
      __riscv_vlmul_trunc_v_u8m2_u8m1(__riscv_vrgather_vv_u8m2(table, __riscv_vlmul_ext_v_u8m1_u8m2(b), 8));
  vbool8_t mask = __riscv_vmsgeu_vx_u8m1_b8(b, 24, 8);
  return __riscv_vmerge_vxm_u8m1(gather, 0, mask, 8);
}

// FORCE_INLINE poly8x8_t vtbl3_p8(poly8x8x3_t a, uint8x8_t idx);

FORCE_INLINE int8x8_t vtbl4_s8(int8x8x4_t a, int8x8_t b) {
  vint8m1_t table1 = __riscv_vget_v_i8m1x4_i8m1(a, 0);
  vint8m1_t table2 = __riscv_vget_v_i8m1x4_i8m1(a, 1);
  vint8m1_t table3 = __riscv_vget_v_i8m1x4_i8m1(a, 2);
  vint8m1_t table4 = __riscv_vget_v_i8m1x4_i8m1(a, 3);
  vint8m2_t table12 = __riscv_vlmul_ext_v_i8m1_i8m2(__riscv_vslideup_vx_i8m1(table1, table2, 8, 16));
  vint8m2_t table34 = __riscv_vlmul_ext_v_i8m1_i8m2(__riscv_vslideup_vx_i8m1(table3, table4, 8, 16));
  vint8m2_t table = __riscv_vslideup_vx_i8m2(table12, table34, 16, 32);
  vint8m1_t gather = __riscv_vlmul_trunc_v_i8m2_i8m1(
      __riscv_vrgather_vv_i8m2(table, __riscv_vlmul_ext_v_u8m1_u8m2(__riscv_vreinterpret_v_i8m1_u8m1(b)), 8));
  vbool8_t mask = __riscv_vmsge_vx_i8m1_b8(b, 32, 8);
  return __riscv_vmerge_vxm_i8m1(gather, 0, mask, 8);
}

FORCE_INLINE uint8x8_t vtbl4_u8(uint8x8x4_t a, uint8x8_t b) {
  vuint8m1_t table1 = __riscv_vget_v_u8m1x4_u8m1(a, 0);
  vuint8m1_t table2 = __riscv_vget_v_u8m1x4_u8m1(a, 1);
  vuint8m1_t table3 = __riscv_vget_v_u8m1x4_u8m1(a, 2);
  vuint8m1_t table4 = __riscv_vget_v_u8m1x4_u8m1(a, 3);
  vuint8m2_t table12 = __riscv_vlmul_ext_v_u8m1_u8m2(__riscv_vslideup_vx_u8m1(table1, table2, 8, 16));
  vuint8m2_t table34 = __riscv_vlmul_ext_v_u8m1_u8m2(__riscv_vslideup_vx_u8m1(table3, table4, 8, 16));
  vuint8m2_t table = __riscv_vslideup_vx_u8m2(table12, table34, 16, 32);
  vuint8m1_t gather =
      __riscv_vlmul_trunc_v_u8m2_u8m1(__riscv_vrgather_vv_u8m2(table, __riscv_vlmul_ext_v_u8m1_u8m2(b), 8));
  vbool8_t mask = __riscv_vmsgeu_vx_u8m1_b8(b, 32, 8);
  return __riscv_vmerge_vxm_u8m1(gather, 0, mask, 8);
}

// FORCE_INLINE poly8x8_t vtbl4_p8(poly8x8x4_t a, uint8x8_t idx);

FORCE_INLINE int8x8_t vtbx1_s8(int8x8_t a, int8x8_t b, int8x8_t c) {
  vint8m1_t b_s = __riscv_vslideup_vx_i8m1(b, vdup_n_s8(0), 8, 16);
  vint8m1_t b_scatter = __riscv_vrgather_vv_i8m1(b_s, __riscv_vreinterpret_v_i8m1_u8m1(c), 8);
  // 0xf8 = 11111000, so any number out of the range [7:0] will return non-zero
  vint8m1_t out_range = __riscv_vand_vx_i8m1(c, 0xf8, 8);
  vbool8_t out_range_mask = __riscv_vmsne_vx_i8m1_b8(out_range, 0, 8);
  return __riscv_vmerge_vvm_i8m1(b_scatter, a, out_range_mask, 8);
}

FORCE_INLINE uint8x8_t vtbx1_u8(uint8x8_t a, uint8x8_t b, uint8x8_t c) {
  vuint8m1_t b_s = __riscv_vslideup_vx_u8m1(b, vdup_n_u8(0), 8, 16);
  vuint8m1_t b_scatter = __riscv_vrgather_vv_u8m1(b_s, c, 8);
  // 0xf8 = 11111000, so any number out of the range [7:0] will return non-zero
  vuint8m1_t out_range = __riscv_vand_vx_u8m1(c, 0xf8, 8);
  vbool8_t out_range_mask = __riscv_vmsne_vx_u8m1_b8(out_range, 0, 8);
  return __riscv_vmerge_vvm_u8m1(b_scatter, a, out_range_mask, 8);
}

// FORCE_INLINE poly8x8_t vtbx1_p8(poly8x8_t a, poly8x8_t b, uint8x8_t idx);

FORCE_INLINE int8x8_t vtbx2_s8(int8x8_t a, int8x8x2_t b, int8x8_t c) {
  vint8m1_t table1 = __riscv_vget_v_i8m1x2_i8m1(b, 0);
  vint8m1_t table2 = __riscv_vget_v_i8m1x2_i8m1(b, 1);
  vint8m1_t table = __riscv_vslideup_vx_i8m1(table1, table2, 8, 16);
  vint8m1_t b_scatter = __riscv_vrgather_vv_i8m1(table, __riscv_vreinterpret_v_i8m1_u8m1(c), 16);
  // 0xf0 = 11110000, so any number out of the range [15:0] will return non-zero
  vint8m1_t out_range = __riscv_vand_vx_i8m1(c, 0xf0, 16);
  vbool8_t out_range_mask = __riscv_vmsne_vx_i8m1_b8(out_range, 0, 16);
  return __riscv_vmerge_vvm_i8m1(b_scatter, a, out_range_mask, 16);
}

FORCE_INLINE uint8x8_t vtbx2_u8(uint8x8_t a, uint8x8x2_t b, uint8x8_t c) {
  vuint8m1_t table1 = __riscv_vget_v_u8m1x2_u8m1(b, 0);
  vuint8m1_t table2 = __riscv_vget_v_u8m1x2_u8m1(b, 1);
  vuint8m1_t table = __riscv_vslideup_vx_u8m1(table1, table2, 8, 16);
  vuint8m1_t b_scatter = __riscv_vrgather_vv_u8m1(table, c, 16);
  // 0xf0 = 11110000, so any number out of the range [15:0] will return non-zero
  vuint8m1_t out_range = __riscv_vand_vx_u8m1(c, 0xf0, 16);
  vbool8_t out_range_mask = __riscv_vmsne_vx_u8m1_b8(out_range, 0, 16);
  return __riscv_vmerge_vvm_u8m1(b_scatter, a, out_range_mask, 16);
}

// FORCE_INLINE poly8x8_t vtbx2_p8(poly8x8_t a, poly8x8x2_t b, uint8x8_t idx);

FORCE_INLINE int8x8_t vtbx3_s8(int8x8_t a, int8x8x3_t b, int8x8_t c) {
  vint8m1_t table1 = __riscv_vget_v_i8m1x3_i8m1(b, 0);
  vint8m1_t table2 = __riscv_vget_v_i8m1x3_i8m1(b, 1);
  vint8m1_t table3 = __riscv_vget_v_i8m1x3_i8m1(b, 2);
  vint8m2_t table12 = __riscv_vlmul_ext_v_i8m1_i8m2(__riscv_vslideup_vx_i8m1(table1, table2, 8, 16));
  vint8m2_t table34 = __riscv_vlmul_ext_v_i8m1_i8m2(__riscv_vslideup_vx_i8m1(table3, vdup_n_s8(0), 8, 16));
  vint8m2_t table = __riscv_vslideup_vx_i8m2(table12, table34, 16, 32);
  vint8m1_t b_scatter = __riscv_vlmul_trunc_v_i8m2_i8m1(
      __riscv_vrgather_vv_i8m2(table, __riscv_vlmul_ext_v_u8m1_u8m2(__riscv_vreinterpret_v_i8m1_u8m1(c)), 8));
  vbool8_t gt_mask = __riscv_vmsgt_vx_i8m1_b8(c, 23, 8);
  vbool8_t lt_mask = __riscv_vmslt_vx_i8m1_b8(c, 0, 8);
  vbool8_t out_range_mask = __riscv_vmor_mm_b8(gt_mask, lt_mask, 8);
  return __riscv_vmerge_vvm_i8m1(b_scatter, a, out_range_mask, 8);
}

FORCE_INLINE uint8x8_t vtbx3_u8(uint8x8_t a, uint8x8x3_t b, uint8x8_t c) {
  vuint8m1_t table1 = __riscv_vget_v_u8m1x3_u8m1(b, 0);
  vuint8m1_t table2 = __riscv_vget_v_u8m1x3_u8m1(b, 1);
  vuint8m1_t table3 = __riscv_vget_v_u8m1x3_u8m1(b, 2);
  vuint8m2_t table12 = __riscv_vlmul_ext_v_u8m1_u8m2(__riscv_vslideup_vx_u8m1(table1, table2, 8, 16));
  vuint8m2_t table34 = __riscv_vlmul_ext_v_u8m1_u8m2(__riscv_vslideup_vx_u8m1(table3, vdup_n_u8(0), 8, 16));
  vuint8m2_t table = __riscv_vslideup_vx_u8m2(table12, table34, 16, 32);
  vuint8m1_t b_scatter =
      __riscv_vlmul_trunc_v_u8m2_u8m1(__riscv_vrgather_vv_u8m2(table, __riscv_vlmul_ext_v_u8m1_u8m2(c), 8));
  vbool8_t out_range_mask = __riscv_vmsgtu_vx_u8m1_b8(c, 23, 8);
  return __riscv_vmerge_vvm_u8m1(b_scatter, a, out_range_mask, 8);
}

// FORCE_INLINE poly8x8_t vtbx3_p8(poly8x8_t a, poly8x8x3_t b, uint8x8_t idx);

FORCE_INLINE int8x8_t vtbx4_s8(int8x8_t a, int8x8x4_t b, int8x8_t c) {
  vint8m1_t table1 = __riscv_vget_v_i8m1x4_i8m1(b, 0);
  vint8m1_t table2 = __riscv_vget_v_i8m1x4_i8m1(b, 1);
  vint8m1_t table3 = __riscv_vget_v_i8m1x4_i8m1(b, 2);
  vint8m1_t table4 = __riscv_vget_v_i8m1x4_i8m1(b, 3);
  vint8m2_t table12 = __riscv_vlmul_ext_v_i8m1_i8m2(__riscv_vslideup_vx_i8m1(table1, table2, 8, 16));
  vint8m2_t table34 = __riscv_vlmul_ext_v_i8m1_i8m2(__riscv_vslideup_vx_i8m1(table3, table4, 8, 16));
  vint8m2_t table = __riscv_vslideup_vx_i8m2(table12, table34, 16, 32);
  vint8m1_t b_scatter = __riscv_vlmul_trunc_v_i8m2_i8m1(
      __riscv_vrgather_vv_i8m2(table, __riscv_vlmul_ext_v_u8m1_u8m2(__riscv_vreinterpret_v_i8m1_u8m1(c)), 8));
  // 0xe0 = 11100000, so any number out of the range [31:0] will return non-zero
  vint8m1_t out_range = __riscv_vand_vx_i8m1(c, 0xe0, 8);
  vbool8_t out_range_mask = __riscv_vmsne_vx_i8m1_b8(out_range, 0, 8);
  return __riscv_vmerge_vvm_i8m1(b_scatter, a, out_range_mask, 8);
}

FORCE_INLINE uint8x8_t vtbx4_u8(uint8x8_t a, uint8x8x4_t b, uint8x8_t c) {
  vuint8m1_t table1 = __riscv_vget_v_u8m1x4_u8m1(b, 0);
  vuint8m1_t table2 = __riscv_vget_v_u8m1x4_u8m1(b, 1);
  vuint8m1_t table3 = __riscv_vget_v_u8m1x4_u8m1(b, 2);
  vuint8m1_t table4 = __riscv_vget_v_u8m1x4_u8m1(b, 3);
  vuint8m2_t table12 = __riscv_vlmul_ext_v_u8m1_u8m2(__riscv_vslideup_vx_u8m1(table1, table2, 8, 16));
  vuint8m2_t table34 = __riscv_vlmul_ext_v_u8m1_u8m2(__riscv_vslideup_vx_u8m1(table3, table4, 8, 16));
  vuint8m2_t table = __riscv_vslideup_vx_u8m2(table12, table34, 16, 32);
  vuint8m1_t b_scatter =
      __riscv_vlmul_trunc_v_u8m2_u8m1(__riscv_vrgather_vv_u8m2(table, __riscv_vlmul_ext_v_u8m1_u8m2(c), 8));
  // 0xe0 = 11100000, so any number out of the range [31:0] will return non-zero
  vuint8m1_t out_range = __riscv_vand_vx_u8m1(c, 0xe0, 8);
  vbool8_t out_range_mask = __riscv_vmsne_vx_u8m1_b8(out_range, 0, 8);
  return __riscv_vmerge_vvm_u8m1(b_scatter, a, out_range_mask, 8);
}

// FORCE_INLINE poly8x8_t vtbx4_p8(poly8x8_t a, poly8x8x4_t b, uint8x8_t idx);

// FORCE_INLINE int8x8_t vqtbl1_s8(int8x16_t t, uint8x8_t idx);

FORCE_INLINE int8x16_t vqtbl1q_s8(int8x16_t t, uint8x16_t idx) {
  vbool8_t mask = __riscv_vmsgeu_vx_u8m1_b8(idx, 16, 16);
  return __riscv_vmerge_vxm_i8m1(__riscv_vrgather_vv_i8m1(t, idx, 16), 0, mask, 16);
}

FORCE_INLINE uint8x8_t vqtbl1_u8(uint8x16_t t, uint8x8_t idx) {
  vbool8_t mask = __riscv_vmsgeu_vx_u8m1_b8(idx, 16, 8);
  return __riscv_vmerge_vxm_u8m1(__riscv_vrgather_vv_u8m1(t, idx, 16), 0, mask, 8);
}

FORCE_INLINE uint8x16_t vqtbl1q_u8(uint8x16_t t, uint8x16_t idx) {
  vbool8_t mask = __riscv_vmsgeu_vx_u8m1_b8(idx, 16, 16);
  return __riscv_vmerge_vxm_u8m1(__riscv_vrgather_vv_u8m1(t, idx, 16), 0, mask, 16);
}

// FORCE_INLINE poly8x8_t vqtbl1_p8(poly8x16_t t, uint8x8_t idx);

// FORCE_INLINE poly8x16_t vqtbl1q_p8(poly8x16_t t, uint8x16_t idx);

// FORCE_INLINE int8x8_t vqtbx1_s8(int8x8_t a, int8x16_t t, uint8x8_t idx);

// FORCE_INLINE int8x16_t vqtbx1q_s8(int8x16_t a, int8x16_t t, uint8x16_t idx);

// FORCE_INLINE uint8x8_t vqtbx1_u8(uint8x8_t a, uint8x16_t t, uint8x8_t idx);

// FORCE_INLINE uint8x16_t vqtbx1q_u8(uint8x16_t a, uint8x16_t t, uint8x16_t idx);

// FORCE_INLINE poly8x8_t vqtbx1_p8(poly8x8_t a, poly8x16_t t, uint8x8_t idx);

// FORCE_INLINE poly8x16_t vqtbx1q_p8(poly8x16_t a, poly8x16_t t, uint8x16_t idx);

// FORCE_INLINE int8x8_t vqtbl2_s8(int8x16x2_t t, uint8x8_t idx);

FORCE_INLINE int8x16_t vqtbl2q_s8(int8x16x2_t t, uint8x16_t idx) {
  vint8m1_t table1 = __riscv_vget_v_i8m1x2_i8m1(t, 0);
  vint8m1_t table2 = __riscv_vget_v_i8m1x2_i8m1(t, 1);
  vint8m2_t table =
      __riscv_vslideup_vx_i8m2(__riscv_vlmul_ext_v_i8m1_i8m2(table1), __riscv_vlmul_ext_v_i8m1_i8m2(table2), 16, 32);
  vint8m1_t gather =
      __riscv_vlmul_trunc_v_i8m2_i8m1(__riscv_vrgather_vv_i8m2(table, __riscv_vlmul_ext_v_u8m1_u8m2(idx), 16));
  vbool8_t mask = __riscv_vmsgeu_vx_u8m1_b8(idx, 32, 16);
  return __riscv_vmerge_vxm_i8m1(gather, 0, mask, 16);
}

FORCE_INLINE uint8x8_t vqtbl2_u8(uint8x16x2_t t, uint8x8_t idx) {
  vuint8m1_t table1 = __riscv_vget_v_u8m1x2_u8m1(t, 0);
  vuint8m1_t table2 = __riscv_vget_v_u8m1x2_u8m1(t, 1);
  vuint8m2_t table =
      __riscv_vslideup_vx_u8m2(__riscv_vlmul_ext_v_u8m1_u8m2(table1), __riscv_vlmul_ext_v_u8m1_u8m2(table2), 16, 32);
  vuint8m1_t gather =
      __riscv_vlmul_trunc_v_u8m2_u8m1(__riscv_vrgather_vv_u8m2(table, __riscv_vlmul_ext_v_u8m1_u8m2(idx), 8));
  vbool8_t mask = __riscv_vmsgeu_vx_u8m1_b8(idx, 32, 8);
  return __riscv_vmerge_vxm_u8m1(gather, 0, mask, 8);
}

FORCE_INLINE uint8x16_t vqtbl2q_u8(uint8x16x2_t t, uint8x16_t idx) {
  vuint8m1_t table1 = __riscv_vget_v_u8m1x2_u8m1(t, 0);
  vuint8m1_t table2 = __riscv_vget_v_u8m1x2_u8m1(t, 1);
  vuint8m2_t table =
      __riscv_vslideup_vx_u8m2(__riscv_vlmul_ext_v_u8m1_u8m2(table1), __riscv_vlmul_ext_v_u8m1_u8m2(table2), 16, 32);
  vuint8m1_t gather =
      __riscv_vlmul_trunc_v_u8m2_u8m1(__riscv_vrgather_vv_u8m2(table, __riscv_vlmul_ext_v_u8m1_u8m2(idx), 16));
  vbool8_t mask = __riscv_vmsgeu_vx_u8m1_b8(idx, 32, 16);
  return __riscv_vmerge_vxm_u8m1(gather, 0, mask, 16);
}

// FORCE_INLINE poly8x8_t vqtbl2_p8(poly8x16x2_t t, uint8x8_t idx);

// FORCE_INLINE poly8x16_t vqtbl2q_p8(poly8x16x2_t t, uint8x16_t idx);

// FORCE_INLINE int8x8_t vqtbl3_s8(int8x16x3_t t, uint8x8_t idx);

// FORCE_INLINE int8x16_t vqtbl3q_s8(int8x16x3_t t, uint8x16_t idx);

// FORCE_INLINE uint8x8_t vqtbl3_u8(uint8x16x3_t t, uint8x8_t idx);

FORCE_INLINE uint8x16_t vqtbl3q_u8(uint8x16x3_t t, uint8x16_t idx) {
  vuint8m4_t table1 = __riscv_vlmul_ext_v_u8m1_u8m4(__riscv_vget_v_u8m1x3_u8m1(t, 0));
  vuint8m4_t table2 = __riscv_vlmul_ext_v_u8m1_u8m4(__riscv_vget_v_u8m1x3_u8m1(t, 1));
  vuint8m4_t table3 = __riscv_vlmul_ext_v_u8m1_u8m4(__riscv_vget_v_u8m1x3_u8m1(t, 2));

  vuint8m4_t table12 = __riscv_vslideup_vx_u8m4(table1, table2, 16, 32);
  vuint8m4_t table30 = __riscv_vslideup_vx_u8m4(table3, __riscv_vlmul_ext_v_u8m1_u8m4(vdupq_n_u8(0)), 16, 32);

  vuint8m4_t table = __riscv_vslideup_vx_u8m4(table12, table30, 32, 64);
  vuint8m1_t gather =
      __riscv_vlmul_trunc_v_u8m4_u8m1(__riscv_vrgather_vv_u8m4(table, __riscv_vlmul_ext_v_u8m1_u8m4(idx), 16));
  vbool8_t mask = __riscv_vmsgeu_vx_u8m1_b8(idx, 48, 16);
  return __riscv_vmerge_vxm_u8m1(gather, 0, mask, 16);
}

// FORCE_INLINE poly8x8_t vqtbl3_p8(poly8x16x3_t t, uint8x8_t idx);

// FORCE_INLINE poly8x16_t vqtbl3q_p8(poly8x16x3_t t, uint8x16_t idx);

// FORCE_INLINE int8x8_t vqtbl4_s8(int8x16x4_t t, uint8x8_t idx);

// FORCE_INLINE int8x16_t vqtbl4q_s8(int8x16x4_t t, uint8x16_t idx);

// FORCE_INLINE uint8x8_t vqtbl4_u8(uint8x16x4_t t, uint8x8_t idx);

FORCE_INLINE uint8x16_t vqtbl4q_u8(uint8x16x4_t t, uint8x16_t idx) {
  vuint8m4_t table1 = __riscv_vlmul_ext_v_u8m1_u8m4(__riscv_vget_v_u8m1x4_u8m1(t, 0));
  vuint8m4_t table2 = __riscv_vlmul_ext_v_u8m1_u8m4(__riscv_vget_v_u8m1x4_u8m1(t, 1));
  vuint8m4_t table3 = __riscv_vlmul_ext_v_u8m1_u8m4(__riscv_vget_v_u8m1x4_u8m1(t, 2));
  vuint8m4_t table4 = __riscv_vlmul_ext_v_u8m1_u8m4(__riscv_vget_v_u8m1x4_u8m1(t, 3));

  vuint8m4_t table12 = __riscv_vslideup_vx_u8m4(table1, table2, 16, 32);
  vuint8m4_t table34 = __riscv_vslideup_vx_u8m4(table3, table4, 16, 32);

  vuint8m4_t table = __riscv_vslideup_vx_u8m4(table12, table34, 32, 64);
  vuint8m1_t gather =
      __riscv_vlmul_trunc_v_u8m4_u8m1(__riscv_vrgather_vv_u8m4(table, __riscv_vlmul_ext_v_u8m1_u8m4(idx), 16));
  vbool8_t mask = __riscv_vmsgeu_vx_u8m1_b8(idx, 64, 16);
  return __riscv_vmerge_vxm_u8m1(gather, 0, mask, 16);
}

// FORCE_INLINE poly8x8_t vqtbl4_p8(poly8x16x4_t t, uint8x8_t idx);

// FORCE_INLINE poly8x16_t vqtbl4q_p8(poly8x16x4_t t, uint8x16_t idx);

// FORCE_INLINE int8x8_t vqtbx2_s8(int8x8_t a, int8x16x2_t t, uint8x8_t idx);

// FORCE_INLINE int8x16_t vqtbx2q_s8(int8x16_t a, int8x16x2_t t, uint8x16_t idx);

// FORCE_INLINE uint8x8_t vqtbx2_u8(uint8x8_t a, uint8x16x2_t t, uint8x8_t idx);

// FORCE_INLINE uint8x16_t vqtbx2q_u8(uint8x16_t a, uint8x16x2_t t, uint8x16_t idx);

// FORCE_INLINE poly8x8_t vqtbx2_p8(poly8x8_t a, poly8x16x2_t t, uint8x8_t idx);

// FORCE_INLINE poly8x16_t vqtbx2q_p8(poly8x16_t a, poly8x16x2_t t, uint8x16_t idx);

// FORCE_INLINE int8x8_t vqtbx3_s8(int8x8_t a, int8x16x3_t t, uint8x8_t idx);

// FORCE_INLINE int8x16_t vqtbx3q_s8(int8x16_t a, int8x16x3_t t, uint8x16_t idx);

// FORCE_INLINE uint8x8_t vqtbx3_u8(uint8x8_t a, uint8x16x3_t t, uint8x8_t idx);

// FORCE_INLINE uint8x16_t vqtbx3q_u8(uint8x16_t a, uint8x16x3_t t, uint8x16_t idx);

// FORCE_INLINE poly8x8_t vqtbx3_p8(poly8x8_t a, poly8x16x3_t t, uint8x8_t idx);

// FORCE_INLINE poly8x16_t vqtbx3q_p8(poly8x16_t a, poly8x16x3_t t, uint8x16_t idx);

// FORCE_INLINE int8x8_t vqtbx4_s8(int8x8_t a, int8x16x4_t t, uint8x8_t idx);

// FORCE_INLINE int8x16_t vqtbx4q_s8(int8x16_t a, int8x16x4_t t, uint8x16_t idx);

// FORCE_INLINE uint8x8_t vqtbx4_u8(uint8x8_t a, uint8x16x4_t t, uint8x8_t idx);

// FORCE_INLINE uint8x16_t vqtbx4q_u8(uint8x16_t a, uint8x16x4_t t, uint8x16_t idx);

// FORCE_INLINE poly8x8_t vqtbx4_p8(poly8x8_t a, poly8x16x4_t t, uint8x8_t idx);

// FORCE_INLINE poly8x16_t vqtbx4q_p8(poly8x16_t a, poly8x16x4_t t, uint8x16_t idx);

FORCE_INLINE int16x4_t vmul_lane_s16(int16x4_t a, int16x4_t b, const int c) {
  vint16m1_t b_dup_lane = __riscv_vrgather_vx_i16m1(b, c, 4);
  return __riscv_vmul_vv_i16m1(a, b_dup_lane, 4);
}

FORCE_INLINE int32x2_t vmul_lane_s32(int32x2_t a, int32x2_t b, const int c) {
  vint32m1_t b_dup_lane = __riscv_vrgather_vx_i32m1(b, c, 2);
  return __riscv_vmul_vv_i32m1(a, b_dup_lane, 2);
}

FORCE_INLINE float32x2_t vmul_lane_f32(float32x2_t a, float32x2_t b, const int c) {
  vfloat32m1_t b_dup_lane = __riscv_vrgather_vx_f32m1(b, c, 2);
  return __riscv_vfmul_vv_f32m1(a, b_dup_lane, 2);
}

FORCE_INLINE uint16x4_t vmul_lane_u16(uint16x4_t a, uint16x4_t b, const int c) {
  vuint16m1_t b_dup_lane = __riscv_vrgather_vx_u16m1(b, c, 4);
  return __riscv_vmul_vv_u16m1(a, b_dup_lane, 4);
}

FORCE_INLINE uint32x2_t vmul_lane_u32(uint32x2_t a, uint32x2_t b, const int c) {
  vuint32m1_t b_dup_lane = __riscv_vrgather_vx_u32m1(b, c, 2);
  return __riscv_vmul_vv_u32m1(a, b_dup_lane, 2);
}

FORCE_INLINE int16x8_t vmulq_lane_s16(int16x8_t a, int16x4_t b, const int c) {
  vint16m1_t b_dup_lane = __riscv_vrgather_vx_i16m1(b, c, 8);
  return __riscv_vmul_vv_i16m1(a, b_dup_lane, 8);
}

FORCE_INLINE int32x4_t vmulq_lane_s32(int32x4_t a, int32x2_t b, const int c) {
  vint32m1_t b_dup_lane = __riscv_vrgather_vx_i32m1(b, c, 4);
  return __riscv_vmul_vv_i32m1(a, b_dup_lane, 4);
}

FORCE_INLINE float32x4_t vmulq_lane_f32(float32x4_t a, float32x2_t b, const int c) {
  vfloat32m1_t b_dup_lane = __riscv_vrgather_vx_f32m1(b, c, 4);
  return __riscv_vfmul_vv_f32m1(a, b_dup_lane, 4);
}

FORCE_INLINE float64x1_t vmul_lane_f64(float64x1_t a, float64x1_t b, const int lane) {
  vfloat64m1_t b_dup_lane = __riscv_vrgather_vx_f64m1(b, lane, 1);
  return __riscv_vfmul_vv_f64m1(a, b_dup_lane, 1);
}

FORCE_INLINE float64x2_t vmulq_lane_f64(float64x2_t a, float64x1_t b, const int lane) {
  vfloat64m1_t b_dup_lane = __riscv_vrgather_vx_f64m1(b, lane, 2);
  return __riscv_vfmul_vv_f64m1(a, b_dup_lane, 2);
}

FORCE_INLINE float32_t vmuls_lane_f32(float32_t a, float32x2_t b, const int lane) {
  float32_t b_lane = __riscv_vfmv_f_s_f32m1_f32(__riscv_vslidedown_vx_f32m1(b, lane, 2));
  return a * b_lane;
}

FORCE_INLINE float64_t vmuld_lane_f64(float64_t a, float64x1_t b, const int lane) {
  float64_t b_lane = __riscv_vfmv_f_s_f64m1_f64(b);
  return a * b_lane;
}

FORCE_INLINE int16x4_t vmul_laneq_s16(int16x4_t a, int16x8_t b, const int lane) {
  vint16m1_t b_dup_lane = __riscv_vrgather_vx_i16m1(b, lane, 8);
  return __riscv_vmul_vv_i16m1(a, b_dup_lane, 4);
}

FORCE_INLINE int16x8_t vmulq_laneq_s16(int16x8_t a, int16x8_t b, const int lane) {
  vint16m1_t b_dup_lane = __riscv_vrgather_vx_i16m1(b, lane, 8);
  return __riscv_vmul_vv_i16m1(a, b_dup_lane, 8);
}

FORCE_INLINE int32x2_t vmul_laneq_s32(int32x2_t a, int32x4_t b, const int lane) {
  vint32m1_t b_dup_lane = __riscv_vrgather_vx_i32m1(b, lane, 4);
  return __riscv_vmul_vv_i32m1(a, b_dup_lane, 2);
}

FORCE_INLINE int32x4_t vmulq_laneq_s32(int32x4_t a, int32x4_t b, const int lane) {
  vint32m1_t b_dup_lane = __riscv_vrgather_vx_i32m1(b, lane, 4);
  return __riscv_vmul_vv_i32m1(a, b_dup_lane, 4);
}

FORCE_INLINE uint16x4_t vmul_laneq_u16(uint16x4_t a, uint16x8_t b, const int lane) {
  vuint16m1_t b_dup_lane = __riscv_vrgather_vx_u16m1(b, lane, 8);
  return __riscv_vmul_vv_u16m1(a, b_dup_lane, 4);
}

FORCE_INLINE uint16x8_t vmulq_laneq_u16(uint16x8_t a, uint16x8_t b, const int lane) {
  vuint16m1_t b_dup_lane = __riscv_vrgather_vx_u16m1(b, lane, 8);
  return __riscv_vmul_vv_u16m1(a, b_dup_lane, 8);
}

FORCE_INLINE uint32x2_t vmul_laneq_u32(uint32x2_t a, uint32x4_t b, const int lane) {
  vuint32m1_t b_dup_lane = __riscv_vrgather_vx_u32m1(b, lane, 4);
  return __riscv_vmul_vv_u32m1(a, b_dup_lane, 2);
}

FORCE_INLINE uint32x4_t vmulq_laneq_u32(uint32x4_t a, uint32x4_t b, const int lane) {
  vuint32m1_t b_dup_lane = __riscv_vrgather_vx_u32m1(b, lane, 4);
  return __riscv_vmul_vv_u32m1(a, b_dup_lane, 4);
}

FORCE_INLINE float32x2_t vmul_laneq_f32(float32x2_t a, float32x4_t b, const int lane) {
  vfloat32m1_t b_dup_lane = __riscv_vrgather_vx_f32m1(b, lane, 4);
  return __riscv_vfmul_vv_f32m1(a, b_dup_lane, 2);
}

FORCE_INLINE float32x4_t vmulq_laneq_f32(float32x4_t a, float32x4_t b, const int lane) {
  vfloat32m1_t b_dup_lane = __riscv_vrgather_vx_f32m1(b, lane, 4);
  return __riscv_vfmul_vv_f32m1(a, b_dup_lane, 4);
}

FORCE_INLINE float64x1_t vmul_laneq_f64(float64x1_t a, float64x2_t b, const int lane) {
  vfloat64m1_t b_dup_lane = __riscv_vrgather_vx_f64m1(b, lane, 2);
  return __riscv_vfmul_vv_f64m1(a, b_dup_lane, 1);
}

FORCE_INLINE float64x2_t vmulq_laneq_f64(float64x2_t a, float64x2_t b, const int lane) {
  vfloat64m1_t b_dup_lane = __riscv_vrgather_vx_f64m1(b, lane, 2);
  return __riscv_vfmul_vv_f64m1(a, b_dup_lane, 2);
}

FORCE_INLINE float32_t vmuls_laneq_f32(float32_t a, float32x4_t b, const int lane) {
  float32_t b_lane = __riscv_vfmv_f_s_f32m1_f32(__riscv_vslidedown_vx_f32m1(b, lane, 4));
  return a * b_lane;
}

FORCE_INLINE float64_t vmuld_laneq_f64(float64_t a, float64x2_t b, const int lane) {
  float64_t b_lane = __riscv_vfmv_f_s_f64m1_f64(__riscv_vslidedown_vx_f64m1(b, lane, 2));
  return a * b_lane;
}

FORCE_INLINE uint16x8_t vmulq_lane_u16(uint16x8_t a, uint16x4_t b, const int lane) {
  vuint16m1_t b_dup_lane = __riscv_vrgather_vx_u16m1(b, lane, 8);
  return __riscv_vmul_vv_u16m1(a, b_dup_lane, 8);
}

FORCE_INLINE uint32x4_t vmulq_lane_u32(uint32x4_t a, uint32x2_t b, const int lane) {
  vuint32m1_t b_dup_lane = __riscv_vrgather_vx_u32m1(b, lane, 4);
  return __riscv_vmul_vv_u32m1(a, b_dup_lane, 4);
}

FORCE_INLINE int16x4_t vmla_lane_s16(int16x4_t a, int16x4_t b, int16x4_t c, const int lane) {
  vint16m1_t c_dup_lane = __riscv_vrgather_vx_i16m1(c, lane, 4);
  return __riscv_vmacc_vv_i16m1(a, b, c_dup_lane, 4);
}

FORCE_INLINE int32x2_t vmla_lane_s32(int32x2_t a, int32x2_t b, int32x2_t c, const int lane) {
  vint32m1_t c_dup_lane = __riscv_vrgather_vx_i32m1(c, lane, 2);
  return __riscv_vmacc_vv_i32m1(a, b, c_dup_lane, 2);
}

FORCE_INLINE float32x2_t vmla_lane_f32(float32x2_t a, float32x2_t b, float32x2_t c, const int lane) {
  vfloat32m1_t c_dup_lane = __riscv_vrgather_vx_f32m1(c, lane, 2);
  return __riscv_vfmacc_vv_f32m1(a, b, c_dup_lane, 2);
}

FORCE_INLINE uint16x4_t vmla_lane_u16(uint16x4_t a, uint16x4_t b, uint16x4_t c, const int lane) {
  vuint16m1_t c_dup_lane = __riscv_vrgather_vx_u16m1(c, lane, 4);
  return __riscv_vmacc_vv_u16m1(a, b, c_dup_lane, 4);
}

FORCE_INLINE uint32x2_t vmla_lane_u32(uint32x2_t a, uint32x2_t b, uint32x2_t c, const int lane) {
  vuint32m1_t c_dup_lane = __riscv_vrgather_vx_u32m1(c, lane, 2);
  return __riscv_vmacc_vv_u32m1(a, b, c_dup_lane, 2);
}

FORCE_INLINE int16x8_t vmlaq_lane_s16(int16x8_t a, int16x8_t b, int16x4_t c, const int lane) {
  vint16m1_t c_dup_lane = __riscv_vrgather_vx_i16m1(c, lane, 8);
  return __riscv_vmacc_vv_i16m1(a, b, c_dup_lane, 8);
}

FORCE_INLINE int32x4_t vmlaq_lane_s32(int32x4_t a, int32x4_t b, int32x2_t c, const int lane) {
  vint32m1_t c_dup_lane = __riscv_vrgather_vx_i32m1(c, lane, 4);
  return __riscv_vmacc_vv_i32m1(a, b, c_dup_lane, 4);
}

FORCE_INLINE float32x4_t vmlaq_lane_f32(float32x4_t a, float32x4_t b, float32x2_t c, const int lane) {
  vfloat32m1_t c_dup_lane = __riscv_vrgather_vx_f32m1(c, lane, 4);
  return __riscv_vfmacc_vv_f32m1(a, b, c_dup_lane, 4);
}

FORCE_INLINE int16x4_t vmla_laneq_s16(int16x4_t a, int16x4_t b, int16x8_t c, const int lane) {
  vint16m1_t c_dup_lane = __riscv_vrgather_vx_i16m1(c, lane, 8);
  return __riscv_vmacc_vv_i16m1(a, b, c_dup_lane, 4);
}

FORCE_INLINE int16x8_t vmlaq_laneq_s16(int16x8_t a, int16x8_t b, int16x8_t c, const int lane) {
  vint16m1_t c_dup_lane = __riscv_vrgather_vx_i16m1(c, lane, 8);
  return __riscv_vmacc_vv_i16m1(a, b, c_dup_lane, 8);
}

FORCE_INLINE int32x2_t vmla_laneq_s32(int32x2_t a, int32x2_t b, int32x4_t c, const int lane) {
  vint32m1_t c_dup_lane = __riscv_vrgather_vx_i32m1(c, lane, 4);
  return __riscv_vmacc_vv_i32m1(a, b, c_dup_lane, 2);
}

FORCE_INLINE int32x4_t vmlaq_laneq_s32(int32x4_t a, int32x4_t b, int32x4_t c, const int lane) {
  vint32m1_t c_dup_lane = __riscv_vrgather_vx_i32m1(c, lane, 4);
  return __riscv_vmacc_vv_i32m1(a, b, c_dup_lane, 4);
}

FORCE_INLINE uint16x4_t vmla_laneq_u16(uint16x4_t a, uint16x4_t b, uint16x8_t c, const int lane) {
  vuint16m1_t c_dup_lane = __riscv_vrgather_vx_u16m1(c, lane, 8);
  return __riscv_vmacc_vv_u16m1(a, b, c_dup_lane, 4);
}

FORCE_INLINE uint16x8_t vmlaq_laneq_u16(uint16x8_t a, uint16x8_t b, uint16x8_t c, const int lane) {
  vuint16m1_t c_dup_lane = __riscv_vrgather_vx_u16m1(c, lane, 8);
  return __riscv_vmacc_vv_u16m1(a, b, c_dup_lane, 8);
}

FORCE_INLINE uint32x2_t vmla_laneq_u32(uint32x2_t a, uint32x2_t b, uint32x4_t c, const int lane) {
  vuint32m1_t c_dup_lane = __riscv_vrgather_vx_u32m1(c, lane, 4);
  return __riscv_vmacc_vv_u32m1(a, b, c_dup_lane, 2);
}

FORCE_INLINE uint32x4_t vmlaq_laneq_u32(uint32x4_t a, uint32x4_t b, uint32x4_t c, const int lane) {
  vuint32m1_t c_dup_lane = __riscv_vrgather_vx_u32m1(c, lane, 4);
  return __riscv_vmacc_vv_u32m1(a, b, c_dup_lane, 4);
}

FORCE_INLINE float32x2_t vmla_laneq_f32(float32x2_t a, float32x2_t b, float32x4_t c, const int lane) {
  vfloat32m1_t c_dup_lane = __riscv_vrgather_vx_f32m1(c, lane, 4);
  return __riscv_vfmacc_vv_f32m1(a, b, c_dup_lane, 2);
}

FORCE_INLINE float32x4_t vmlaq_laneq_f32(float32x4_t a, float32x4_t b, float32x4_t c, const int lane) {
  vfloat32m1_t c_dup_lane = __riscv_vrgather_vx_f32m1(c, lane, 4);
  return __riscv_vfmacc_vv_f32m1(a, b, c_dup_lane, 4);
}

FORCE_INLINE uint16x8_t vmlaq_lane_u16(uint16x8_t a, uint16x8_t b, uint16x4_t c, const int lane) {
  vuint16m1_t c_dup_lane = __riscv_vrgather_vx_u16m1(c, lane, 8);
  return __riscv_vmacc_vv_u16m1(a, b, c_dup_lane, 8);
}

FORCE_INLINE uint32x4_t vmlaq_lane_u32(uint32x4_t a, uint32x4_t b, uint32x2_t c, const int lane) {
  vuint32m1_t c_dup_lane = __riscv_vrgather_vx_u32m1(c, lane, 4);
  return __riscv_vmacc_vv_u32m1(a, b, c_dup_lane, 4);
}

FORCE_INLINE int32x4_t vmlal_lane_s16(int32x4_t a, int16x4_t b, int16x4_t c, const int lane) {
  vint16m1_t c_dup = __riscv_vrgather_vx_i16m1(c, lane, 4);
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmacc_vv_i32m2(__riscv_vlmul_ext_v_i32m1_i32m2(a), b, c_dup, 4));
}

FORCE_INLINE int64x2_t vmlal_lane_s32(int64x2_t a, int32x2_t b, int32x2_t c, const int lane) {
  vint32m1_t c_dup = __riscv_vrgather_vx_i32m1(c, lane, 2);
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmacc_vv_i64m2(__riscv_vlmul_ext_v_i64m1_i64m2(a), b, c_dup, 2));
}

FORCE_INLINE uint32x4_t vmlal_lane_u16(uint32x4_t a, uint16x4_t b, uint16x4_t c, const int lane) {
  vuint16m1_t c_dup = __riscv_vrgather_vx_u16m1(c, lane, 4);
  return __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwmaccu_vv_u32m2(__riscv_vlmul_ext_v_u32m1_u32m2(a), b, c_dup, 4));
}

FORCE_INLINE uint64x2_t vmlal_lane_u32(uint64x2_t a, uint32x2_t b, uint32x2_t c, const int lane) {
  vuint32m1_t c_dup = __riscv_vrgather_vx_u32m1(c, lane, 2);
  return __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwmaccu_vv_u64m2(__riscv_vlmul_ext_v_u64m1_u64m2(a), b, c_dup, 2));
}

FORCE_INLINE int32x4_t vmlal_high_lane_s16(int32x4_t a, int16x8_t b, int16x4_t c, const int lane) {
  vint16m1_t b_high = __riscv_vslidedown_vx_i16m1(b, 4, 8);
  vint16m1_t c_dup = __riscv_vrgather_vx_i16m1(c, lane, 4);
  return __riscv_vlmul_trunc_v_i32m2_i32m1(
      __riscv_vwmacc_vv_i32m2(__riscv_vlmul_ext_v_i32m1_i32m2(a), b_high, c_dup, 4));
}

FORCE_INLINE int64x2_t vmlal_high_lane_s32(int64x2_t a, int32x4_t b, int32x2_t c, const int lane) {
  vint32m1_t b_high = __riscv_vslidedown_vx_i32m1(b, 2, 4);
  vint32m1_t c_dup = __riscv_vrgather_vx_i32m1(c, lane, 2);
  return __riscv_vlmul_trunc_v_i64m2_i64m1(
      __riscv_vwmacc_vv_i64m2(__riscv_vlmul_ext_v_i64m1_i64m2(a), b_high, c_dup, 2));
}

FORCE_INLINE uint32x4_t vmlal_high_lane_u16(uint32x4_t a, uint16x8_t b, uint16x4_t c, const int lane) {
  vuint16m1_t b_high = __riscv_vslidedown_vx_u16m1(b, 4, 8);
  vuint16m1_t c_dup = __riscv_vrgather_vx_u16m1(c, lane, 4);
  return __riscv_vlmul_trunc_v_u32m2_u32m1(
      __riscv_vwmaccu_vv_u32m2(__riscv_vlmul_ext_v_u32m1_u32m2(a), b_high, c_dup, 4));
}

FORCE_INLINE uint64x2_t vmlal_high_lane_u32(uint64x2_t a, uint32x4_t b, uint32x2_t c, const int lane) {
  vuint32m1_t b_high = __riscv_vslidedown_vx_u32m1(b, 2, 4);
  vuint32m1_t c_dup = __riscv_vrgather_vx_u32m1(c, lane, 2);
  return __riscv_vlmul_trunc_v_u64m2_u64m1(
      __riscv_vwmaccu_vv_u64m2(__riscv_vlmul_ext_v_u64m1_u64m2(a), b_high, c_dup, 2));
}

FORCE_INLINE int32x4_t vmlal_laneq_s16(int32x4_t a, int16x4_t b, int16x8_t c, const int lane) {
  vint16m1_t c_dup = __riscv_vrgather_vx_i16m1(c, lane, 4);
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmacc_vv_i32m2(__riscv_vlmul_ext_v_i32m1_i32m2(a), b, c_dup, 4));
}

FORCE_INLINE int64x2_t vmlal_laneq_s32(int64x2_t a, int32x2_t b, int32x4_t c, const int lane) {
  vint32m1_t c_dup = __riscv_vrgather_vx_i32m1(c, lane, 2);
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmacc_vv_i64m2(__riscv_vlmul_ext_v_i64m1_i64m2(a), b, c_dup, 2));
}

FORCE_INLINE uint32x4_t vmlal_laneq_u16(uint32x4_t a, uint16x4_t b, uint16x8_t c, const int lane) {
  vuint16m1_t c_dup = __riscv_vrgather_vx_u16m1(c, lane, 4);
  return __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwmaccu_vv_u32m2(__riscv_vlmul_ext_v_u32m1_u32m2(a), b, c_dup, 4));
}

FORCE_INLINE uint64x2_t vmlal_laneq_u32(uint64x2_t a, uint32x2_t b, uint32x4_t c, const int lane) {
  vuint32m1_t c_dup = __riscv_vrgather_vx_u32m1(c, lane, 2);
  return __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwmaccu_vv_u64m2(__riscv_vlmul_ext_v_u64m1_u64m2(a), b, c_dup, 2));
}

FORCE_INLINE int32x4_t vmlal_high_laneq_s16(int32x4_t a, int16x8_t b, int16x8_t c, const int lane) {
  vint16m1_t b_high = __riscv_vslidedown_vx_i16m1(b, 4, 8);
  vint16m1_t c_dup = __riscv_vrgather_vx_i16m1(c, lane, 4);
  return __riscv_vlmul_trunc_v_i32m2_i32m1(
      __riscv_vwmacc_vv_i32m2(__riscv_vlmul_ext_v_i32m1_i32m2(a), b_high, c_dup, 4));
}

FORCE_INLINE int64x2_t vmlal_high_laneq_s32(int64x2_t a, int32x4_t b, int32x4_t c, const int lane) {
  vint32m1_t b_high = __riscv_vslidedown_vx_i32m1(b, 2, 4);
  vint32m1_t c_dup = __riscv_vrgather_vx_i32m1(c, lane, 2);
  return __riscv_vlmul_trunc_v_i64m2_i64m1(
      __riscv_vwmacc_vv_i64m2(__riscv_vlmul_ext_v_i64m1_i64m2(a), b_high, c_dup, 2));
}

FORCE_INLINE uint32x4_t vmlal_high_laneq_u16(uint32x4_t a, uint16x8_t b, uint16x8_t c, const int lane) {
  vuint16m1_t b_high = __riscv_vslidedown_vx_u16m1(b, 4, 8);
  vuint16m1_t c_dup = __riscv_vrgather_vx_u16m1(c, lane, 4);
  return __riscv_vlmul_trunc_v_u32m2_u32m1(
      __riscv_vwmaccu_vv_u32m2(__riscv_vlmul_ext_v_u32m1_u32m2(a), b_high, c_dup, 4));
}

FORCE_INLINE uint64x2_t vmlal_high_laneq_u32(uint64x2_t a, uint32x4_t b, uint32x4_t c, const int lane) {
  vuint32m1_t b_high = __riscv_vslidedown_vx_u32m1(b, 2, 4);
  vuint32m1_t c_dup = __riscv_vrgather_vx_u32m1(c, lane, 2);
  return __riscv_vlmul_trunc_v_u64m2_u64m1(
      __riscv_vwmaccu_vv_u64m2(__riscv_vlmul_ext_v_u64m1_u64m2(a), b_high, c_dup, 2));
}

FORCE_INLINE int32x4_t vqdmlal_lane_s16(int32x4_t a, int16x4_t b, int16x4_t c, const int lane) {
  vint16m1_t c_dup = __riscv_vrgather_vx_i16m1(c, lane, 4);
  vint32m1_t bc_mul = __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vv_i32m2(b, c_dup, 4));
  vint32m1_t bc_mulx2 = __riscv_vmul_vx_i32m1(bc_mul, 2, 4);
  return __riscv_vadd_vv_i32m1(a, bc_mulx2, 4);
}

FORCE_INLINE int64x2_t vqdmlal_lane_s32(int64x2_t a, int32x2_t b, int32x2_t c, const int lane) {
  vint32m1_t c_dup = __riscv_vrgather_vx_i32m1(c, lane, 2);
  vint64m1_t bc_mul = __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vv_i64m2(b, c_dup, 2));
  vint64m1_t bc_mulx2 = __riscv_vmul_vx_i64m1(bc_mul, 2, 2);
  return __riscv_vadd_vv_i64m1(a, bc_mulx2, 2);
}

FORCE_INLINE int32_t vqdmlalh_lane_s16(int32_t a, int16_t b, int16x4_t c, const int lane) {
  int16_t c_lane = vget_lane_s16(c, lane);
  int32_t dmull = (int32_t)b * (int32_t)c_lane;
  dmull = dmull > INT32_MAX / 2 ? INT32_MAX : dmull < INT32_MIN / 2 ? INT32_MIN : dmull * 2;
  return sat_add_int32(a, dmull);
}

FORCE_INLINE int64_t vqdmlals_lane_s32(int64_t a, int32_t b, int32x2_t c, const int lane) {
  int32_t c_lane = vget_lane_s32(c, lane);
  int64_t dmull = (int64_t)b * (int64_t)c_lane;
  dmull = dmull > INT64_MAX / 2 ? INT64_MAX : dmull < INT64_MIN / 2 ? INT64_MIN : dmull * 2;
  return sat_add_int64(a, dmull);
}

FORCE_INLINE int32x4_t vqdmlal_high_lane_s16(int32x4_t a, int16x8_t b, int16x4_t c, const int lane) {
  vint16m1_t b_high = __riscv_vslidedown_vx_i16m1(b, 4, 8);
  vint16m1_t c_dup = __riscv_vrgather_vx_i16m1(c, lane, 4);
  vint32m1_t bc_mul = __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vv_i32m2(b_high, c_dup, 4));
  vint32m1_t bc_mulx2 = __riscv_vmul_vx_i32m1(bc_mul, 2, 4);
  return __riscv_vadd_vv_i32m1(a, bc_mulx2, 4);
}

FORCE_INLINE int64x2_t vqdmlal_high_lane_s32(int64x2_t a, int32x4_t b, int32x2_t c, const int lane) {
  vint32m1_t b_high = __riscv_vslidedown_vx_i32m1(b, 2, 4);
  vint32m1_t c_dup = __riscv_vrgather_vx_i32m1(c, lane, 2);
  vint64m1_t bc_mul = __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vv_i64m2(b_high, c_dup, 2));
  vint64m1_t bc_mulx2 = __riscv_vmul_vx_i64m1(bc_mul, 2, 2);
  return __riscv_vadd_vv_i64m1(a, bc_mulx2, 2);
}

FORCE_INLINE int32x4_t vqdmlal_laneq_s16(int32x4_t a, int16x4_t b, int16x8_t c, const int lane) {
  vint16m1_t c_dup = __riscv_vrgather_vx_i16m1(c, lane, 8);
  vint32m1_t bc_mul = __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vv_i32m2(b, c_dup, 4));
  vint32m1_t bc_mulx2 = __riscv_vmul_vx_i32m1(bc_mul, 2, 4);
  return __riscv_vadd_vv_i32m1(a, bc_mulx2, 4);
}

FORCE_INLINE int64x2_t vqdmlal_laneq_s32(int64x2_t a, int32x2_t b, int32x4_t c, const int lane) {
  vint32m1_t c_dup = __riscv_vrgather_vx_i32m1(c, lane, 4);
  vint64m1_t bc_mul = __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vv_i64m2(b, c_dup, 2));
  vint64m1_t bc_mulx2 = __riscv_vmul_vx_i64m1(bc_mul, 2, 2);
  return __riscv_vadd_vv_i64m1(a, bc_mulx2, 2);
}

FORCE_INLINE int32_t vqdmlalh_laneq_s16(int32_t a, int16_t b, int16x8_t c, const int lane) {
  int16_t c_lane = vgetq_lane_s16(c, lane);
  int32_t dmull = (int32_t)b * (int32_t)c_lane;
  dmull = dmull > INT32_MAX / 2 ? INT32_MAX : dmull < INT32_MIN / 2 ? INT32_MIN : dmull * 2;
  return sat_add_int32(a, dmull);
}

FORCE_INLINE int64_t vqdmlals_laneq_s32(int64_t a, int32_t b, int32x4_t c, const int lane) {
  int32_t c_lane = vgetq_lane_s32(c, lane);
  int64_t dmull = (int64_t)b * (int64_t)c_lane;
  dmull = dmull > INT64_MAX / 2 ? INT64_MAX : dmull < INT64_MIN / 2 ? INT64_MIN : dmull * 2;
  return sat_add_int64(a, dmull);
}

FORCE_INLINE int32x4_t vqdmlal_high_laneq_s16(int32x4_t a, int16x8_t b, int16x8_t c, const int lane) {
  vint16m1_t b_high = __riscv_vslidedown_vx_i16m1(b, 4, 8);
  vint16m1_t c_dup = __riscv_vrgather_vx_i16m1(c, lane, 8);
  vint32m1_t bc_mul = __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vv_i32m2(b_high, c_dup, 4));
  vint32m1_t bc_mulx2 = __riscv_vmul_vx_i32m1(bc_mul, 2, 4);
  return __riscv_vadd_vv_i32m1(a, bc_mulx2, 4);
}

FORCE_INLINE int64x2_t vqdmlal_high_laneq_s32(int64x2_t a, int32x4_t b, int32x4_t c, const int lane) {
  vint32m1_t b_high = __riscv_vslidedown_vx_i32m1(b, 2, 4);
  vint32m1_t c_dup = __riscv_vrgather_vx_i32m1(c, lane, 4);
  vint64m1_t bc_mul = __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vv_i64m2(b_high, c_dup, 2));
  vint64m1_t bc_mulx2 = __riscv_vmul_vx_i64m1(bc_mul, 2, 2);
  return __riscv_vadd_vv_i64m1(a, bc_mulx2, 2);
}

FORCE_INLINE int16x4_t vmls_lane_s16(int16x4_t a, int16x4_t b, int16x4_t c, const int lane) {
  vint16m1_t c_dup = __riscv_vrgather_vx_i16m1(c, lane, 4);
  return __riscv_vnmsac_vv_i16m1(a, b, c_dup, 4);
}

FORCE_INLINE int32x2_t vmls_lane_s32(int32x2_t a, int32x2_t b, int32x2_t c, const int lane) {
  vint32m1_t c_dup = __riscv_vrgather_vx_i32m1(c, lane, 2);
  return __riscv_vnmsac_vv_i32m1(a, b, c_dup, 2);
}

FORCE_INLINE float32x2_t vmls_lane_f32(float32x2_t a, float32x2_t b, float32x2_t c, const int lane) {
  vfloat32m1_t c_dup = __riscv_vrgather_vx_f32m1(c, lane, 2);
  return __riscv_vfnmsac_vv_f32m1(a, b, c_dup, 2);
}

FORCE_INLINE uint16x4_t vmls_lane_u16(uint16x4_t a, uint16x4_t b, uint16x4_t c, const int lane) {
  vuint16m1_t c_dup = __riscv_vrgather_vx_u16m1(c, lane, 4);
  return __riscv_vnmsac_vv_u16m1(a, b, c_dup, 4);
}

FORCE_INLINE uint32x2_t vmls_lane_u32(uint32x2_t a, uint32x2_t b, uint32x2_t c, const int lane) {
  vuint32m1_t c_dup = __riscv_vrgather_vx_u32m1(c, lane, 2);
  return __riscv_vnmsac_vv_u32m1(a, b, c_dup, 2);
}

FORCE_INLINE int16x8_t vmlsq_lane_s16(int16x8_t a, int16x8_t b, int16x4_t c, const int lane) {
  vint16m1_t c_dup = __riscv_vrgather_vx_i16m1(c, lane, 8);
  return __riscv_vnmsac_vv_i16m1(a, b, c_dup, 8);
}

FORCE_INLINE int32x4_t vmlsq_lane_s32(int32x4_t a, int32x4_t b, int32x2_t c, const int lane) {
  vint32m1_t c_dup = __riscv_vrgather_vx_i32m1(c, lane, 4);
  return __riscv_vnmsac_vv_i32m1(a, b, c_dup, 4);
}

FORCE_INLINE float32x4_t vmlsq_lane_f32(float32x4_t a, float32x4_t b, float32x2_t c, const int lane) {
  vfloat32m1_t c_dup = __riscv_vrgather_vx_f32m1(c, lane, 4);
  return __riscv_vfnmsac_vv_f32m1(a, b, c_dup, 4);
}

FORCE_INLINE int16x4_t vmls_laneq_s16(int16x4_t a, int16x4_t b, int16x8_t c, const int lane) {
  vint16m1_t c_dup = __riscv_vrgather_vx_i16m1(c, lane, 8);
  return __riscv_vnmsac_vv_i16m1(a, b, c_dup, 4);
}

FORCE_INLINE int16x8_t vmlsq_laneq_s16(int16x8_t a, int16x8_t b, int16x8_t c, const int lane) {
  vint16m1_t c_dup = __riscv_vrgather_vx_i16m1(c, lane, 8);
  return __riscv_vnmsac_vv_i16m1(a, b, c_dup, 8);
}

FORCE_INLINE int32x2_t vmls_laneq_s32(int32x2_t a, int32x2_t b, int32x4_t c, const int lane) {
  vint32m1_t c_dup = __riscv_vrgather_vx_i32m1(c, lane, 4);
  return __riscv_vnmsac_vv_i32m1(a, b, c_dup, 2);
}

FORCE_INLINE int32x4_t vmlsq_laneq_s32(int32x4_t a, int32x4_t b, int32x4_t c, const int lane) {
  vint32m1_t c_dup = __riscv_vrgather_vx_i32m1(c, lane, 4);
  return __riscv_vnmsac_vv_i32m1(a, b, c_dup, 4);
}

FORCE_INLINE uint16x4_t vmls_laneq_u16(uint16x4_t a, uint16x4_t b, uint16x8_t c, const int lane) {
  vuint16m1_t c_dup = __riscv_vrgather_vx_u16m1(c, lane, 8);
  return __riscv_vnmsac_vv_u16m1(a, b, c_dup, 4);
}

FORCE_INLINE uint16x8_t vmlsq_laneq_u16(uint16x8_t a, uint16x8_t b, uint16x8_t c, const int lane) {
  vuint16m1_t c_dup = __riscv_vrgather_vx_u16m1(c, lane, 8);
  return __riscv_vnmsac_vv_u16m1(a, b, c_dup, 8);
}

FORCE_INLINE uint32x2_t vmls_laneq_u32(uint32x2_t a, uint32x2_t b, uint32x4_t c, const int lane) {
  vuint32m1_t c_dup = __riscv_vrgather_vx_u32m1(c, lane, 4);
  return __riscv_vnmsac_vv_u32m1(a, b, c_dup, 2);
}

FORCE_INLINE uint32x4_t vmlsq_laneq_u32(uint32x4_t a, uint32x4_t b, uint32x4_t c, const int lane) {
  vuint32m1_t c_dup = __riscv_vrgather_vx_u32m1(c, lane, 4);
  return __riscv_vnmsac_vv_u32m1(a, b, c_dup, 4);
}

FORCE_INLINE float32x2_t vmls_laneq_f32(float32x2_t a, float32x2_t b, float32x4_t c, const int lane) {
  vfloat32m1_t c_dup = __riscv_vrgather_vx_f32m1(c, lane, 4);
  return __riscv_vfnmsac_vv_f32m1(a, b, c_dup, 2);
}

FORCE_INLINE float32x4_t vmlsq_laneq_f32(float32x4_t a, float32x4_t b, float32x4_t c, const int lane) {
  vfloat32m1_t c_dup = __riscv_vrgather_vx_f32m1(c, lane, 4);
  return __riscv_vfnmsac_vv_f32m1(a, b, c_dup, 4);
}

FORCE_INLINE uint16x8_t vmlsq_lane_u16(uint16x8_t a, uint16x8_t b, uint16x4_t c, const int lane) {
  vuint16m1_t c_dup = __riscv_vrgather_vx_u16m1(c, lane, 8);
  return __riscv_vnmsac_vv_u16m1(a, b, c_dup, 8);
}

FORCE_INLINE uint32x4_t vmlsq_lane_u32(uint32x4_t a, uint32x4_t b, uint32x2_t c, const int lane) {
  vuint32m1_t c_dup = __riscv_vrgather_vx_u32m1(c, lane, 4);
  return __riscv_vnmsac_vv_u32m1(a, b, c_dup, 4);
}

FORCE_INLINE int32x4_t vmlsl_lane_s16(int32x4_t a, int16x4_t b, int16x4_t c, const int lane) {
  vint16m1_t c_dup = __riscv_vrgather_vx_i16m1(c, lane, 4);
  return __riscv_vsub_vv_i32m1(a, __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vv_i32m2(b, c_dup, 4)), 4);
}

FORCE_INLINE int64x2_t vmlsl_lane_s32(int64x2_t a, int32x2_t b, int32x2_t c, const int lane) {
  vint32m1_t c_dup = __riscv_vrgather_vx_i32m1(c, lane, 2);
  return __riscv_vsub_vv_i64m1(a, __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vv_i64m2(b, c_dup, 2)), 2);
}

FORCE_INLINE uint32x4_t vmlsl_lane_u16(uint32x4_t a, uint16x4_t b, uint16x4_t c, const int lane) {
  vuint16m1_t c_dup = __riscv_vrgather_vx_u16m1(c, lane, 4);
  return __riscv_vsub_vv_u32m1(a, __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwmulu_vv_u32m2(b, c_dup, 4)), 4);
}

FORCE_INLINE uint64x2_t vmlsl_lane_u32(uint64x2_t a, uint32x2_t b, uint32x2_t c, const int lane) {
  vuint32m1_t c_dup = __riscv_vrgather_vx_u32m1(c, lane, 2);
  return __riscv_vsub_vv_u64m1(a, __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwmulu_vv_u64m2(b, c_dup, 2)), 2);
}

FORCE_INLINE int32x4_t vmlsl_high_lane_s16(int32x4_t a, int16x8_t b, int16x4_t c, const int lane) {
  vint16m1_t b_high = __riscv_vslidedown_vx_i16m1(b, 4, 8);
  vint16m1_t c_dup = __riscv_vrgather_vx_i16m1(c, lane, 4);
  return __riscv_vsub_vv_i32m1(a, __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vv_i32m2(b_high, c_dup, 4)), 4);
}

FORCE_INLINE int64x2_t vmlsl_high_lane_s32(int64x2_t a, int32x4_t b, int32x2_t c, const int lane) {
  vint32m1_t b_high = __riscv_vslidedown_vx_i32m1(b, 2, 4);
  vint32m1_t c_dup = __riscv_vrgather_vx_i32m1(c, lane, 2);
  return __riscv_vsub_vv_i64m1(a, __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vv_i64m2(b_high, c_dup, 2)), 2);
}

FORCE_INLINE uint32x4_t vmlsl_high_lane_u16(uint32x4_t a, uint16x8_t b, uint16x4_t c, const int lane) {
  vuint16m1_t b_high = __riscv_vslidedown_vx_u16m1(b, 4, 8);
  vuint16m1_t c_dup = __riscv_vrgather_vx_u16m1(c, lane, 8);
  return __riscv_vsub_vv_u32m1(a, __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwmulu_vv_u32m2(b_high, c_dup, 4)), 4);
}

FORCE_INLINE uint64x2_t vmlsl_high_lane_u32(uint64x2_t a, uint32x4_t b, uint32x2_t c, const int lane) {
  vuint32m1_t b_high = __riscv_vslidedown_vx_u32m1(b, 2, 4);
  vuint32m1_t c_dup = __riscv_vrgather_vx_u32m1(c, lane, 4);
  return __riscv_vsub_vv_u64m1(a, __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwmulu_vv_u64m2(b_high, c_dup, 2)), 2);
}

FORCE_INLINE int32x4_t vmlsl_laneq_s16(int32x4_t a, int16x4_t b, int16x8_t c, const int lane) {
  vint16m1_t c_dup = __riscv_vrgather_vx_i16m1(c, lane, 8);
  return __riscv_vsub_vv_i32m1(a, __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vv_i32m2(b, c_dup, 4)), 4);
}

FORCE_INLINE int64x2_t vmlsl_laneq_s32(int64x2_t a, int32x2_t b, int32x4_t c, const int lane) {
  vint32m1_t c_dup = __riscv_vrgather_vx_i32m1(c, lane, 4);
  return __riscv_vsub_vv_i64m1(a, __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vv_i64m2(b, c_dup, 2)), 2);
}

FORCE_INLINE uint32x4_t vmlsl_laneq_u16(uint32x4_t a, uint16x4_t b, uint16x8_t c, const int lane) {
  vuint16m1_t c_dup = __riscv_vrgather_vx_u16m1(c, lane, 8);
  return __riscv_vsub_vv_u32m1(a, __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwmulu_vv_u32m2(b, c_dup, 4)), 4);
}

FORCE_INLINE uint64x2_t vmlsl_laneq_u32(uint64x2_t a, uint32x2_t b, uint32x4_t c, const int lane) {
  vuint32m1_t c_dup = __riscv_vrgather_vx_u32m1(c, lane, 4);
  return __riscv_vsub_vv_u64m1(a, __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwmulu_vv_u64m2(b, c_dup, 2)), 2);
}

FORCE_INLINE int32x4_t vmlsl_high_laneq_s16(int32x4_t a, int16x8_t b, int16x8_t c, const int lane) {
  vint16m1_t b_high = __riscv_vslidedown_vx_i16m1(b, 4, 8);
  vint16m1_t c_dup = __riscv_vrgather_vx_i16m1(c, lane, 4);
  return __riscv_vsub_vv_i32m1(a, __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vv_i32m2(b_high, c_dup, 8)), 8);
}

FORCE_INLINE int64x2_t vmlsl_high_laneq_s32(int64x2_t a, int32x4_t b, int32x4_t c, const int lane) {
  vint32m1_t b_high = __riscv_vslidedown_vx_i32m1(b, 2, 4);
  vint32m1_t c_dup = __riscv_vrgather_vx_i32m1(c, lane, 2);
  return __riscv_vsub_vv_i64m1(a, __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vv_i64m2(b_high, c_dup, 4)), 4);
}

FORCE_INLINE uint32x4_t vmlsl_high_laneq_u16(uint32x4_t a, uint16x8_t b, uint16x8_t c, const int lane) {
  vuint16m1_t b_high = __riscv_vslidedown_vx_u16m1(b, 4, 8);
  vuint16m1_t c_dup = __riscv_vrgather_vx_u16m1(c, lane, 8);
  return __riscv_vsub_vv_u32m1(a, __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwmulu_vv_u32m2(b_high, c_dup, 8)), 8);
}

FORCE_INLINE uint64x2_t vmlsl_high_laneq_u32(uint64x2_t a, uint32x4_t b, uint32x4_t c, const int lane) {
  vuint32m1_t b_high = __riscv_vslidedown_vx_u32m1(b, 2, 4);
  vuint32m1_t c_dup = __riscv_vrgather_vx_u32m1(c, lane, 4);
  return __riscv_vsub_vv_u64m1(a, __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwmulu_vv_u64m2(b_high, c_dup, 4)), 4);
}

FORCE_INLINE int32x4_t vqdmlsl_lane_s16(int32x4_t a, int16x4_t b, int16x4_t c, const int lane) {
  vint16m1_t c_dup = __riscv_vrgather_vx_i16m1(c, lane, 4);
  vint32m1_t bc_mul = __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vv_i32m2(b, c_dup, 4));
  vint32m1_t bc_mulx2 = __riscv_vsll_vx_i32m1(bc_mul, 1, 4);
  return __riscv_vsub_vv_i32m1(a, bc_mulx2, 4);
}

FORCE_INLINE int64x2_t vqdmlsl_lane_s32(int64x2_t a, int32x2_t b, int32x2_t c, const int lane) {
  vint32m1_t c_dup = __riscv_vrgather_vx_i32m1(c, lane, 2);
  vint64m1_t bc_mul = __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vv_i64m2(b, c_dup, 2));
  vint64m1_t bc_mulx2 = __riscv_vsll_vx_i64m1(bc_mul, 1, 2);
  return __riscv_vsub_vv_i64m1(a, bc_mulx2, 2);
}

FORCE_INLINE int32_t vqdmlslh_lane_s16(int32_t a, int16_t b, int16x4_t c, const int lane) {
  int16_t c_lane = vget_lane_s16(c, lane);
  int32_t dmull = (int32_t)b * (int32_t)c_lane;
  dmull = dmull > INT32_MAX / 2 ? INT32_MAX : dmull < INT32_MIN / 2 ? INT32_MIN : dmull * 2;
  return sat_sub_int32(a, dmull);
}

FORCE_INLINE int64_t vqdmlsls_lane_s32(int64_t a, int32_t b, int32x2_t c, const int lane) {
  int32_t c_lane = vget_lane_s32(c, lane);
  int64_t dmull = (int64_t)b * (int64_t)c_lane;
  dmull = dmull > INT64_MAX / 2 ? INT64_MAX : dmull < INT64_MIN / 2 ? INT64_MIN : dmull * 2;
  return sat_sub_int64(a, dmull);
}

FORCE_INLINE int32x4_t vqdmlsl_high_lane_s16(int32x4_t a, int16x8_t b, int16x4_t c, const int lane) {
  vint16m1_t b_high = __riscv_vslidedown_vx_i16m1(b, 4, 4);
  vint16m1_t c_dup = __riscv_vrgather_vx_i16m1(c, lane, 4);
  vint32m1_t bc_mul = __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vv_i32m2(b_high, c_dup, 4));
  vint32m1_t bc_mulx2 = __riscv_vsll_vx_i32m1(bc_mul, 1, 4);
  return __riscv_vsub_vv_i32m1(a, bc_mulx2, 4);
}

FORCE_INLINE int64x2_t vqdmlsl_high_lane_s32(int64x2_t a, int32x4_t b, int32x2_t c, const int lane) {
  vint32m1_t b_high = __riscv_vslidedown_vx_i32m1(b, 2, 2);
  vint32m1_t c_dup = __riscv_vrgather_vx_i32m1(c, lane, 2);
  vint64m1_t bc_mul = __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vv_i64m2(b_high, c_dup, 2));
  vint64m1_t bc_mulx2 = __riscv_vsll_vx_i64m1(bc_mul, 1, 2);
  return __riscv_vsub_vv_i64m1(a, bc_mulx2, 2);
}

FORCE_INLINE int32x4_t vqdmlsl_laneq_s16(int32x4_t a, int16x4_t b, int16x8_t c, const int lane) {
  vint16m1_t c_dup = __riscv_vrgather_vx_i16m1(c, lane, 8);
  vint32m1_t bc_mul = __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vv_i32m2(b, c_dup, 4));
  vint32m1_t bc_mulx2 = __riscv_vsll_vx_i32m1(bc_mul, 1, 4);
  return __riscv_vsub_vv_i32m1(a, bc_mulx2, 4);
}

FORCE_INLINE int64x2_t vqdmlsl_laneq_s32(int64x2_t a, int32x2_t b, int32x4_t c, const int lane) {
  vint32m1_t c_dup = __riscv_vrgather_vx_i32m1(c, lane, 4);
  vint64m1_t bc_mul = __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vv_i64m2(b, c_dup, 2));
  vint64m1_t bc_mulx2 = __riscv_vsll_vx_i64m1(bc_mul, 1, 2);
  return __riscv_vsub_vv_i64m1(a, bc_mulx2, 2);
}

FORCE_INLINE int32_t vqdmlslh_laneq_s16(int32_t a, int16_t b, int16x8_t c, const int lane) {
  int16_t c_lane = vgetq_lane_s16(c, lane);
  int32_t dmull = (int32_t)b * (int32_t)c_lane;
  dmull = dmull > INT32_MAX / 2 ? INT32_MAX : dmull < INT32_MIN / 2 ? INT32_MIN : dmull * 2;
  return sat_sub_int32(a, dmull);
}

FORCE_INLINE int64_t vqdmlsls_laneq_s32(int64_t a, int32_t b, int32x4_t c, const int lane) {
  int32_t c_lane = vgetq_lane_s32(c, lane);
  int64_t dmull = (int64_t)b * (int64_t)c_lane;
  dmull = dmull > INT64_MAX / 2 ? INT64_MAX : dmull < INT64_MIN / 2 ? INT64_MIN : dmull * 2;
  return sat_sub_int64(a, dmull);
}

FORCE_INLINE int32x4_t vqdmlsl_high_laneq_s16(int32x4_t a, int16x8_t b, int16x8_t c, const int lane) {
  vint16m1_t b_high = __riscv_vslidedown_vx_i16m1(b, 4, 8);
  vint16m1_t c_dup = __riscv_vrgather_vx_i16m1(c, lane, 4);
  vint32m1_t bc_mul = __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vv_i32m2(b_high, c_dup, 4));
  vint32m1_t bc_mulx2 = __riscv_vsll_vx_i32m1(bc_mul, 1, 4);
  return __riscv_vsub_vv_i32m1(a, bc_mulx2, 4);
}

FORCE_INLINE int64x2_t vqdmlsl_high_laneq_s32(int64x2_t a, int32x4_t b, int32x4_t c, const int lane) {
  vint32m1_t b_high = __riscv_vslidedown_vx_i32m1(b, 2, 4);
  vint32m1_t c_dup = __riscv_vrgather_vx_i32m1(c, lane, 2);
  vint64m1_t bc_mul = __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vv_i64m2(b_high, c_dup, 2));
  vint64m1_t bc_mulx2 = __riscv_vsll_vx_i64m1(bc_mul, 1, 2);
  return __riscv_vsub_vv_i64m1(a, bc_mulx2, 2);
}

FORCE_INLINE int32x4_t vmull_lane_s16(int16x4_t a, int16x4_t b, const int c) {
  vint16m1_t b_dup = __riscv_vrgather_vx_i16m1(b, c, 4);
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vv_i32m2(a, b_dup, 4));
}

FORCE_INLINE int64x2_t vmull_lane_s32(int32x2_t a, int32x2_t b, const int c) {
  vint32m1_t b_dup = __riscv_vrgather_vx_i32m1(b, c, 2);
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vv_i64m2(a, b_dup, 2));
}

FORCE_INLINE uint32x4_t vmull_lane_u16(uint16x4_t a, uint16x4_t b, const int c) {
  vuint16m1_t b_dup = __riscv_vrgather_vx_u16m1(b, c, 4);
  return __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwmulu_vv_u32m2(a, b_dup, 4));
}

FORCE_INLINE uint64x2_t vmull_lane_u32(uint32x2_t a, uint32x2_t b, const int c) {
  vuint32m1_t b_dup = __riscv_vrgather_vx_u32m1(b, c, 2);
  return __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwmulu_vv_u64m2(a, b_dup, 2));
}

FORCE_INLINE int32x4_t vmull_high_lane_s16(int16x8_t a, int16x4_t b, const int lane) {
  vint16m1_t a_high = __riscv_vslidedown_vx_i16m1(a, 4, 8);
  vint16m1_t b_dup = __riscv_vrgather_vx_i16m1(b, lane, 4);
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vv_i32m2(a_high, b_dup, 4));
}

FORCE_INLINE int64x2_t vmull_high_lane_s32(int32x4_t a, int32x2_t b, const int lane) {
  vint32m1_t a_high = __riscv_vslidedown_vx_i32m1(a, 2, 4);
  vint32m1_t b_dup = __riscv_vrgather_vx_i32m1(b, lane, 2);
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vv_i64m2(a_high, b_dup, 2));
}

FORCE_INLINE uint32x4_t vmull_high_lane_u16(uint16x8_t a, uint16x4_t b, const int lane) {
  vuint16m1_t a_high = __riscv_vslidedown_vx_u16m1(a, 4, 8);
  vuint16m1_t b_dup = __riscv_vrgather_vx_u16m1(b, lane, 4);
  return __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwmulu_vv_u32m2(a_high, b_dup, 4));
}

FORCE_INLINE uint64x2_t vmull_high_lane_u32(uint32x4_t a, uint32x2_t b, const int lane) {
  vuint32m1_t a_high = __riscv_vslidedown_vx_u32m1(a, 2, 4);
  vuint32m1_t b_dup = __riscv_vrgather_vx_u32m1(b, lane, 2);
  return __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwmulu_vv_u64m2(a_high, b_dup, 2));
}

FORCE_INLINE int32x4_t vmull_laneq_s16(int16x4_t a, int16x8_t b, const int lane) {
  vint16m1_t b_dup = __riscv_vrgather_vx_i16m1(b, lane, 8);
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vv_i32m2(a, b_dup, 4));
}

FORCE_INLINE int64x2_t vmull_laneq_s32(int32x2_t a, int32x4_t b, const int lane) {
  vint32m1_t b_dup = __riscv_vrgather_vx_i32m1(b, lane, 4);
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vv_i64m2(a, b_dup, 2));
}

FORCE_INLINE uint32x4_t vmull_laneq_u16(uint16x4_t a, uint16x8_t b, const int lane) {
  vuint16m1_t b_dup = __riscv_vrgather_vx_u16m1(b, lane, 8);
  return __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwmulu_vv_u32m2(a, b_dup, 4));
}

FORCE_INLINE uint64x2_t vmull_laneq_u32(uint32x2_t a, uint32x4_t b, const int lane) {
  vuint32m1_t b_dup = __riscv_vrgather_vx_u32m1(b, lane, 4);
  return __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwmulu_vv_u64m2(a, b_dup, 2));
}

FORCE_INLINE int32x4_t vmull_high_laneq_s16(int16x8_t a, int16x8_t b, const int lane) {
  vint16m1_t a_high = __riscv_vslidedown_vx_i16m1(a, 4, 8);
  vint16m1_t b_dup = __riscv_vrgather_vx_i16m1(b, lane, 8);
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vv_i32m2(a_high, b_dup, 4));
}

FORCE_INLINE int64x2_t vmull_high_laneq_s32(int32x4_t a, int32x4_t b, const int lane) {
  vint32m1_t a_high = __riscv_vslidedown_vx_i32m1(a, 2, 4);
  vint32m1_t b_dup = __riscv_vrgather_vx_i32m1(b, lane, 4);
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vv_i64m2(a_high, b_dup, 2));
}

FORCE_INLINE uint32x4_t vmull_high_laneq_u16(uint16x8_t a, uint16x8_t b, const int lane) {
  vuint16m1_t a_high = __riscv_vslidedown_vx_u16m1(a, 4, 8);
  vuint16m1_t b_dup = __riscv_vrgather_vx_u16m1(b, lane, 8);
  return __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwmulu_vv_u32m2(a_high, b_dup, 4));
}

FORCE_INLINE uint64x2_t vmull_high_laneq_u32(uint32x4_t a, uint32x4_t b, const int lane) {
  vuint32m1_t a_high = __riscv_vslidedown_vx_u32m1(a, 2, 4);
  vuint32m1_t b_dup = __riscv_vrgather_vx_u32m1(b, lane, 4);
  return __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwmulu_vv_u64m2(a_high, b_dup, 2));
}

FORCE_INLINE int32x4_t vqdmull_lane_s16(int16x4_t a, int16x4_t b, const int lane) {
  vint16m1_t b_dup_lane = __riscv_vrgather_vx_i16m1(b, lane, 4);
  vint32m2_t ab_mul = __riscv_vwmul_vv_i32m2(a, b_dup_lane, 4);
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vsll_vx_i32m2(ab_mul, 1, 4));
}

FORCE_INLINE int64x2_t vqdmull_lane_s32(int32x2_t a, int32x2_t b, const int lane) {
  vint32m1_t b_dup_lane = __riscv_vrgather_vx_i32m1(b, lane, 2);
  vint64m2_t ab_mul = __riscv_vwmul_vv_i64m2(a, b_dup_lane, 2);
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vsll_vx_i64m2(ab_mul, 1, 2));
}

FORCE_INLINE int32_t vqdmullh_lane_s16(int16_t a, int16x4_t b, const int lane) {
  int16_t b_lane = vget_lane_s16(b, lane);
  int32_t dmull = (int32_t)a * (int32_t)b_lane;
  return dmull > INT32_MAX / 2 ? INT32_MAX : dmull < INT32_MIN / 2 ? INT32_MIN : dmull * 2;
}

FORCE_INLINE int64_t vqdmulls_lane_s32(int32_t a, int32x2_t b, const int lane) {
  int32_t b_lane = vget_lane_s32(b, lane);
  int64_t dmull = (int64_t)a * (int64_t)b_lane;
  return dmull > INT64_MAX / 2 ? INT64_MAX : dmull < INT64_MIN / 2 ? INT64_MIN : dmull * 2;
}

FORCE_INLINE int32x4_t vqdmull_high_lane_s16(int16x8_t a, int16x4_t b, const int lane) {
  vint16m1_t a_high = __riscv_vslidedown_vx_i16m1(a, 4, 8);
  vint16m1_t b_dup_lane = __riscv_vrgather_vx_i16m1(b, lane, 4);
  vint32m2_t ab_mul = __riscv_vwmul_vv_i32m2(a_high, b_dup_lane, 4);
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vsll_vx_i32m2(ab_mul, 1, 4));
}

FORCE_INLINE int64x2_t vqdmull_high_lane_s32(int32x4_t a, int32x2_t b, const int lane) {
  vint32m1_t a_high = __riscv_vslidedown_vx_i32m1(a, 2, 4);
  vint32m1_t b_dup_lane = __riscv_vrgather_vx_i32m1(b, lane, 2);
  vint64m2_t ab_mul = __riscv_vwmul_vv_i64m2(a_high, b_dup_lane, 2);
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vsll_vx_i64m2(ab_mul, 1, 2));
}

FORCE_INLINE int32x4_t vqdmull_laneq_s16(int16x4_t a, int16x8_t b, const int lane) {
  vint16m1_t b_dup_lane = __riscv_vrgather_vx_i16m1(b, lane, 8);
  vint32m2_t ab_mul = __riscv_vwmul_vv_i32m2(a, b_dup_lane, 4);
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vsll_vx_i32m2(ab_mul, 1, 4));
}

FORCE_INLINE int64x2_t vqdmull_laneq_s32(int32x2_t a, int32x4_t b, const int lane) {
  vint32m1_t b_dup_lane = __riscv_vrgather_vx_i32m1(b, lane, 4);
  vint64m2_t ab_mul = __riscv_vwmul_vv_i64m2(a, b_dup_lane, 2);
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vsll_vx_i64m2(ab_mul, 1, 2));
}

FORCE_INLINE int32_t vqdmullh_laneq_s16(int16_t a, int16x8_t b, const int lane) {
  int16_t b_lane = vgetq_lane_s16(b, lane);
  int32_t dmull = (int32_t)a * (int32_t)b_lane;
  return dmull > INT32_MAX / 2 ? INT32_MAX : dmull < INT32_MIN / 2 ? INT32_MIN : dmull * 2;
}

FORCE_INLINE int64_t vqdmulls_laneq_s32(int32_t a, int32x4_t b, const int lane) {
  int32_t b_lane = vgetq_lane_s32(b, lane);
  int64_t dmull = (int64_t)a * (int64_t)b_lane;
  return dmull > INT64_MAX / 2 ? INT64_MAX : dmull < INT64_MIN / 2 ? INT64_MIN : dmull * 2;
}

FORCE_INLINE int32x4_t vqdmull_high_laneq_s16(int16x8_t a, int16x8_t b, const int lane) {
  vint16m1_t a_high = __riscv_vslidedown_vx_i16m1(a, 4, 8);
  vint16m1_t b_dup_lane = __riscv_vrgather_vx_i16m1(b, lane, 8);
  vint32m2_t ab_mul = __riscv_vwmul_vv_i32m2(a_high, b_dup_lane, 4);
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vsll_vx_i32m2(ab_mul, 1, 4));
}

FORCE_INLINE int64x2_t vqdmull_high_laneq_s32(int32x4_t a, int32x4_t b, const int lane) {
  vint32m1_t a_high = __riscv_vslidedown_vx_i32m1(a, 2, 4);
  vint32m1_t b_dup_lane = __riscv_vrgather_vx_i32m1(b, lane, 4);
  vint64m2_t ab_mul = __riscv_vwmul_vv_i64m2(a_high, b_dup_lane, 2);
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vsll_vx_i64m2(ab_mul, 1, 2));
}

FORCE_INLINE int16x8_t vqdmulhq_lane_s16(int16x8_t a, int16x4_t b, const int c) {
  vint16m1_t b_dup_lane = __riscv_vrgather_vx_i16m1(b, c, 8);
  vint32m2_t ab_mul = __riscv_vwmul_vv_i32m2(a, b_dup_lane, 8);
  vint32m2_t ab_mulx2 = __riscv_vmul_vx_i32m2(ab_mul, 2, 8);
  return __riscv_vnsra_wx_i16m1(ab_mulx2, 16, 8);
}

FORCE_INLINE int32x4_t vqdmulhq_lane_s32(int32x4_t a, int32x2_t b, const int c) {
  vint32m1_t b_dup_lane = __riscv_vrgather_vx_i32m1(b, c, 4);
  vint64m2_t ab_mul = __riscv_vwmul_vv_i64m2(a, b_dup_lane, 4);
  vint64m2_t ab_mulx2 = __riscv_vmul_vx_i64m2(ab_mul, 2, 4);
  return __riscv_vnsra_wx_i32m1(ab_mulx2, 32, 4);
}

// FORCE_INLINE int16_t vqdmulhh_lane_s16(int16_t a, int16x4_t v, const int lane);

// FORCE_INLINE int32_t vqdmulhs_lane_s32(int32_t a, int32x2_t v, const int lane);

// FORCE_INLINE int16x4_t vqdmulh_laneq_s16(int16x4_t a, int16x8_t v, const int lane);

// FORCE_INLINE int16x8_t vqdmulhq_laneq_s16(int16x8_t a, int16x8_t v, const int lane);

// FORCE_INLINE int32x2_t vqdmulh_laneq_s32(int32x2_t a, int32x4_t v, const int lane);

// FORCE_INLINE int32x4_t vqdmulhq_laneq_s32(int32x4_t a, int32x4_t v, const int lane);

// FORCE_INLINE int16_t vqdmulhh_laneq_s16(int16_t a, int16x8_t v, const int lane);

// FORCE_INLINE int32_t vqdmulhs_laneq_s32(int32_t a, int32x4_t v, const int lane);

FORCE_INLINE int16x4_t vqdmulh_lane_s16(int16x4_t a, int16x4_t b, const int c) {
  vint16m1_t b_dup_lane = __riscv_vrgather_vx_i16m1(b, c, 4);
  vint32m2_t ab_mul = __riscv_vwmul_vv_i32m2(a, b_dup_lane, 4);
  vint32m2_t ab_mulx2 = __riscv_vmul_vx_i32m2(ab_mul, 2, 4);
  return __riscv_vnsra_wx_i16m1(ab_mulx2, 16, 4);
}

FORCE_INLINE int32x2_t vqdmulh_lane_s32(int32x2_t a, int32x2_t b, const int c) {
  vint32m1_t b_dup_lane = __riscv_vrgather_vx_i32m1(b, c, 2);
  vint64m2_t ab_mul = __riscv_vwmul_vv_i64m2(a, b_dup_lane, 2);
  vint64m2_t ab_mulx2 = __riscv_vmul_vx_i64m2(ab_mul, 2, 2);
  return __riscv_vnsra_wx_i32m1(ab_mulx2, 32, 2);
}

FORCE_INLINE int16x8_t vqrdmulhq_lane_s16(int16x8_t a, int16x4_t b, const int c) {
  vint16m1_t b_dup_lane = __riscv_vrgather_vx_i16m1(b, c, 8);
  vint32m2_t ab_mul = __riscv_vwmul_vv_i32m2(a, b_dup_lane, 8);
  vint32m2_t ab_mulx2 = __riscv_vmul_vx_i32m2(ab_mul, 2, 8);
  return __riscv_vnclip_wx_i16m1(ab_mulx2, 16, __RISCV_VXRM_RNU, 8);
}

FORCE_INLINE int32x4_t vqrdmulhq_lane_s32(int32x4_t a, int32x2_t b, const int c) {
  vint32m1_t b_dup_lane = __riscv_vrgather_vx_i32m1(b, c, 4);
  vint64m2_t ab_mul = __riscv_vwmul_vv_i64m2(a, b_dup_lane, 4);
  vint64m2_t ab_mulx2 = __riscv_vmul_vx_i64m2(ab_mul, 2, 4);
  return __riscv_vnclip_wx_i32m1(ab_mulx2, 32, __RISCV_VXRM_RNU, 4);
}

// FORCE_INLINE int16_t vqrdmulhh_lane_s16(int16_t a, int16x4_t v, const int lane);

// FORCE_INLINE int32_t vqrdmulhs_lane_s32(int32_t a, int32x2_t v, const int lane);

// FORCE_INLINE int16x4_t vqrdmulh_laneq_s16(int16x4_t a, int16x8_t v, const int lane);

// FORCE_INLINE int16x8_t vqrdmulhq_laneq_s16(int16x8_t a, int16x8_t v, const int lane);

// FORCE_INLINE int32x2_t vqrdmulh_laneq_s32(int32x2_t a, int32x4_t v, const int lane);

// FORCE_INLINE int32x4_t vqrdmulhq_laneq_s32(int32x4_t a, int32x4_t v, const int lane);

// FORCE_INLINE int16_t vqrdmulhh_laneq_s16(int16_t a, int16x8_t v, const int lane);

// FORCE_INLINE int32_t vqrdmulhs_laneq_s32(int32_t a, int32x4_t v, const int lane);

FORCE_INLINE int16x4_t vqrdmulh_lane_s16(int16x4_t a, int16x4_t b, const int c) {
  vint16m1_t b_dup_lane = __riscv_vrgather_vx_i16m1(b, c, 4);
  vint32m2_t ab_mul = __riscv_vwmul_vv_i32m2(a, b_dup_lane, 4);
  vint32m2_t ab_mulx2 = __riscv_vmul_vx_i32m2(ab_mul, 2, 4);
  return __riscv_vnclip_wx_i16m1(ab_mulx2, 16, __RISCV_VXRM_RNU, 4);
}

FORCE_INLINE int32x2_t vqrdmulh_lane_s32(int32x2_t a, int32x2_t b, const int c) {
  vint32m1_t b_dup_lane = __riscv_vrgather_vx_i32m1(b, c, 2);
  vint64m2_t ab_mul = __riscv_vwmul_vv_i64m2(a, b_dup_lane, 2);
  vint64m2_t ab_mulx2 = __riscv_vmul_vx_i64m2(ab_mul, 2, 2);
  return __riscv_vnclip_wx_i32m1(ab_mulx2, 32, __RISCV_VXRM_RNU, 2);
}

FORCE_INLINE int16x8_t vqrdmlahq_lane_s16(int16x8_t a, int16x8_t b, int16x4_t c, const int __d) {
  vint16m1_t c_dup = __riscv_vrgather_vx_i16m1(c, __d, 8);
  vint32m2_t bc_mul = __riscv_vwmul_vv_i32m2(b, c_dup, 8);
  vint32m2_t bc_mulx2 = __riscv_vsll_vx_i32m2(bc_mul, 1, 8);
  vint16m1_t bc_s = __riscv_vnclip_wx_i16m1(bc_mulx2, 16, __RISCV_VXRM_RNU, 8);
  return __riscv_vsadd_vv_i16m1(a, bc_s, 8);
}

// FORCE_INLINE int16x4_t vqrdmlah_laneq_s16(int16x4_t a, int16x4_t b, int16x8_t v, const int lane);

// FORCE_INLINE int16x8_t vqrdmlahq_laneq_s16(int16x8_t a, int16x8_t b, int16x8_t v, const int lane);

FORCE_INLINE int32x4_t vqrdmlahq_lane_s32(int32x4_t a, int32x4_t b, int32x2_t c, const int __d) {
  vint32m1_t c_dup = __riscv_vrgather_vx_i32m1(c, __d, 4);
  vint64m2_t bc_mul = __riscv_vwmul_vv_i64m2(b, c_dup, 4);
  vint64m2_t bc_mulx2 = __riscv_vsll_vx_i64m2(bc_mul, 1, 4);
  vint32m1_t bc_s = __riscv_vnclip_wx_i32m1(bc_mulx2, 32, __RISCV_VXRM_RNU, 4);
  return __riscv_vsadd_vv_i32m1(a, bc_s, 4);
}

// FORCE_INLINE int32x2_t vqrdmlah_laneq_s32(int32x2_t a, int32x2_t b, int32x4_t v, const int lane);

// FORCE_INLINE int32x4_t vqrdmlahq_laneq_s32(int32x4_t a, int32x4_t b, int32x4_t v, const int lane);

FORCE_INLINE int16x4_t vqrdmlah_lane_s16(int16x4_t a, int16x4_t b, int16x4_t c, const int __d) {
  vint16m1_t c_dup = __riscv_vrgather_vx_i16m1(c, __d, 4);
  vint32m2_t bc_mul = __riscv_vwmul_vv_i32m2(b, c_dup, 4);
  vint32m2_t bc_mulx2 = __riscv_vsll_vx_i32m2(bc_mul, 1, 4);
  vint16m1_t bc_s = __riscv_vnclip_wx_i16m1(bc_mulx2, 16, __RISCV_VXRM_RNU, 4);
  return __riscv_vsadd_vv_i16m1(a, bc_s, 4);
}

FORCE_INLINE int32x2_t vqrdmlah_lane_s32(int32x2_t a, int32x2_t b, int32x2_t c, const int __d) {
  vint32m1_t c_dup = __riscv_vrgather_vx_i32m1(c, __d, 2);
  vint64m2_t bc_mul = __riscv_vwmul_vv_i64m2(b, c_dup, 2);
  vint64m2_t bc_mulx2 = __riscv_vsll_vx_i64m2(bc_mul, 1, 2);
  vint32m1_t bc_s = __riscv_vnclip_wx_i32m1(bc_mulx2, 32, __RISCV_VXRM_RNU, 2);
  return __riscv_vsadd_vv_i32m1(a, bc_s, 2);
}

FORCE_INLINE int16x8_t vqrdmlshq_lane_s16(int16x8_t a, int16x8_t b, int16x4_t c, const int __d) {
  vint16m1_t c_dup = __riscv_vrgather_vx_i16m1(c, __d, 4);
  vint32m2_t bc_mul = __riscv_vwmul_vv_i32m2(b, c_dup, 4);
  vint32m2_t bc_mulx2 = __riscv_vsll_vx_i32m2(bc_mul, 1, 4);
  vint16m1_t bc_s = __riscv_vnclip_wx_i16m1(bc_mulx2, 16, __RISCV_VXRM_RNU, 4);
  return __riscv_vssub_vv_i16m1(a, bc_s, 4);
}

// FORCE_INLINE int16x4_t vqrdmlsh_laneq_s16(int16x4_t a, int16x4_t b, int16x8_t v, const int lane);

// FORCE_INLINE int16x8_t vqrdmlshq_laneq_s16(int16x8_t a, int16x8_t b, int16x8_t v, const int lane);

FORCE_INLINE int32x4_t vqrdmlshq_lane_s32(int32x4_t a, int32x4_t b, int32x2_t c, const int __d) {
  vint32m1_t c_dup = __riscv_vrgather_vx_i32m1(c, __d, 2);
  vint64m2_t bc_mul = __riscv_vwmul_vv_i64m2(b, c_dup, 2);
  vint64m2_t bc_mulx2 = __riscv_vsll_vx_i64m2(bc_mul, 1, 2);
  vint32m1_t bc_s = __riscv_vnclip_wx_i32m1(bc_mulx2, 32, __RISCV_VXRM_RNU, 2);
  return __riscv_vssub_vv_i32m1(a, bc_s, 2);
}

// FORCE_INLINE int32x2_t vqrdmlsh_laneq_s32(int32x2_t a, int32x2_t b, int32x4_t v, const int lane);

// FORCE_INLINE int32x4_t vqrdmlshq_laneq_s32(int32x4_t a, int32x4_t b, int32x4_t v, const int lane);

// FORCE_INLINE int16_t vqrdmlahh_s16(int16_t a, int16_t b, int16_t c);

// FORCE_INLINE int32_t vqrdmlahs_s32(int32_t a, int32_t b, int32_t c);

// FORCE_INLINE int16_t vqrdmlshh_s16(int16_t a, int16_t b, int16_t c);

// FORCE_INLINE int32_t vqrdmlshs_s32(int32_t a, int32_t b, int32_t c);

// FORCE_INLINE int16_t vqrdmlahh_lane_s16(int16_t a, int16_t b, int16x4_t v, const int lane);

// FORCE_INLINE int16_t vqrdmlahh_laneq_s16(int16_t a, int16_t b, int16x8_t v, const int lane);

// FORCE_INLINE int32_t vqrdmlahs_lane_s32(int32_t a, int32_t b, int32x2_t v, const int lane);

// FORCE_INLINE int32_t vqrdmlahs_laneq_s32(int32_t a, int32_t b, int32x4_t v, const int lane);

// FORCE_INLINE int16_t vqrdmlshh_lane_s16(int16_t a, int16_t b, int16x4_t v, const int lane);

// FORCE_INLINE int16_t vqrdmlshh_laneq_s16(int16_t a, int16_t b, int16x8_t v, const int lane);

// FORCE_INLINE int32_t vqrdmlshs_lane_s32(int32_t a, int32_t b, int32x2_t v, const int lane);

// FORCE_INLINE int32_t vqrdmlshs_laneq_s32(int32_t a, int32_t b, int32x4_t v, const int lane);

// FORCE_INLINE float16_t vabsh_f16(float16_t a);

// FORCE_INLINE uint16_t vceqzh_f16(float16_t a);

// FORCE_INLINE uint16_t vcgezh_f16(float16_t a);

// FORCE_INLINE uint16_t vcgtzh_f16(float16_t a);

// FORCE_INLINE uint16_t vclezh_f16(float16_t a);

// FORCE_INLINE uint16_t vcltzh_f16(float16_t a);

// FORCE_INLINE float16_t vcvth_f16_s16(int16_t a);

// FORCE_INLINE float16_t vcvth_f16_s32(int32_t a);

// FORCE_INLINE float16_t vcvth_f16_s64(int64_t a);

// FORCE_INLINE float16_t vcvth_f16_u16(uint16_t a);

// FORCE_INLINE float16_t vcvth_f16_u32(uint32_t a);

// FORCE_INLINE float16_t vcvth_f16_u64(uint64_t a);

// FORCE_INLINE int16_t vcvth_s16_f16(float16_t a);

// FORCE_INLINE int32_t vcvth_s32_f16(float16_t a);

// FORCE_INLINE int64_t vcvth_s64_f16(float16_t a);

// FORCE_INLINE uint16_t vcvth_u16_f16(float16_t a);

// FORCE_INLINE uint32_t vcvth_u32_f16(float16_t a);

// FORCE_INLINE uint64_t vcvth_u64_f16(float16_t a);

// FORCE_INLINE int16_t vcvtah_s16_f16(float16_t a);

// FORCE_INLINE int32_t vcvtah_s32_f16(float16_t a);

// FORCE_INLINE int64_t vcvtah_s64_f16(float16_t a);

// FORCE_INLINE uint16_t vcvtah_u16_f16(float16_t a);

// FORCE_INLINE uint32_t vcvtah_u32_f16(float16_t a);

// FORCE_INLINE uint64_t vcvtah_u64_f16(float16_t a);

// FORCE_INLINE int16_t vcvtmh_s16_f16(float16_t a);

// FORCE_INLINE int32_t vcvtmh_s32_f16(float16_t a);

// FORCE_INLINE int64_t vcvtmh_s64_f16(float16_t a);

// FORCE_INLINE uint16_t vcvtmh_u16_f16(float16_t a);

// FORCE_INLINE uint32_t vcvtmh_u32_f16(float16_t a);

// FORCE_INLINE uint64_t vcvtmh_u64_f16(float16_t a);

// FORCE_INLINE int16_t vcvtnh_s16_f16(float16_t a);

// FORCE_INLINE int32_t vcvtnh_s32_f16(float16_t a);

// FORCE_INLINE int64_t vcvtnh_s64_f16(float16_t a);

// FORCE_INLINE uint16_t vcvtnh_u16_f16(float16_t a);

// FORCE_INLINE uint32_t vcvtnh_u32_f16(float16_t a);

// FORCE_INLINE uint64_t vcvtnh_u64_f16(float16_t a);

// FORCE_INLINE int16_t vcvtph_s16_f16(float16_t a);

// FORCE_INLINE int32_t vcvtph_s32_f16(float16_t a);

// FORCE_INLINE int64_t vcvtph_s64_f16(float16_t a);

// FORCE_INLINE uint16_t vcvtph_u16_f16(float16_t a);

// FORCE_INLINE uint32_t vcvtph_u32_f16(float16_t a);

// FORCE_INLINE uint64_t vcvtph_u64_f16(float16_t a);

// FORCE_INLINE float16_t vnegh_f16(float16_t a);

// FORCE_INLINE float16_t vrecpeh_f16(float16_t a);

// FORCE_INLINE float16_t vrecpxh_f16(float16_t a);

// FORCE_INLINE float16_t vrndh_f16(float16_t a);

// FORCE_INLINE float16_t vrndah_f16(float16_t a);

// FORCE_INLINE float16_t vrndih_f16(float16_t a);

// FORCE_INLINE float16_t vrndmh_f16(float16_t a);

// FORCE_INLINE float16_t vrndnh_f16(float16_t a);

// FORCE_INLINE float16_t vrndph_f16(float16_t a);

// FORCE_INLINE float16_t vrndxh_f16(float16_t a);

// FORCE_INLINE float16_t vrsqrteh_f16(float16_t a);

// FORCE_INLINE float16_t vsqrth_f16(float16_t a);

// FORCE_INLINE float16_t vaddh_f16(float16_t a, float16_t b);

// FORCE_INLINE float16_t vabdh_f16(float16_t a, float16_t b);

// FORCE_INLINE uint16_t vcageh_f16(float16_t a, float16_t b);

// FORCE_INLINE uint16_t vcagth_f16(float16_t a, float16_t b);

// FORCE_INLINE uint16_t vcaleh_f16(float16_t a, float16_t b);

// FORCE_INLINE uint16_t vcalth_f16(float16_t a, float16_t b);

// FORCE_INLINE uint16_t vceqh_f16(float16_t a, float16_t b);

// FORCE_INLINE uint16_t vcgeh_f16(float16_t a, float16_t b);

// FORCE_INLINE uint16_t vcgth_f16(float16_t a, float16_t b);

// FORCE_INLINE uint16_t vcleh_f16(float16_t a, float16_t b);

// FORCE_INLINE uint16_t vclth_f16(float16_t a, float16_t b);

// FORCE_INLINE float16_t vcvth_n_f16_s16(int16_t a, const int n);

// FORCE_INLINE float16_t vcvth_n_f16_s32(int32_t a, const int n);

// FORCE_INLINE float16_t vcvth_n_f16_s64(int64_t a, const int n);

// FORCE_INLINE float16_t vcvth_n_f16_u16(uint16_t a, const int n);

// FORCE_INLINE float16_t vcvth_n_f16_u32(uint32_t a, const int n);

// FORCE_INLINE float16_t vcvth_n_f16_u64(uint64_t a, const int n);

// FORCE_INLINE int16_t vcvth_n_s16_f16(float16_t a, const int n);

// FORCE_INLINE int32_t vcvth_n_s32_f16(float16_t a, const int n);

// FORCE_INLINE int64_t vcvth_n_s64_f16(float16_t a, const int n);

// FORCE_INLINE uint16_t vcvth_n_u16_f16(float16_t a, const int n);

// FORCE_INLINE uint32_t vcvth_n_u32_f16(float16_t a, const int n);

// FORCE_INLINE uint64_t vcvth_n_u64_f16(float16_t a, const int n);

// FORCE_INLINE float16_t vdivh_f16(float16_t a, float16_t b);

// FORCE_INLINE float16_t vmaxh_f16(float16_t a, float16_t b);

// FORCE_INLINE float16_t vmaxnmh_f16(float16_t a, float16_t b);

// FORCE_INLINE float16_t vminh_f16(float16_t a, float16_t b);

// FORCE_INLINE float16_t vminnmh_f16(float16_t a, float16_t b);

// FORCE_INLINE float16_t vmulh_f16(float16_t a, float16_t b);

// FORCE_INLINE float16_t vmulxh_f16(float16_t a, float16_t b);

// FORCE_INLINE float16_t vrecpsh_f16(float16_t a, float16_t b);

// FORCE_INLINE float16_t vrsqrtsh_f16(float16_t a, float16_t b);

// FORCE_INLINE float16_t vsubh_f16(float16_t a, float16_t b);

// FORCE_INLINE float16_t vfmah_f16(float16_t a, float16_t b, float16_t c);

// FORCE_INLINE float16_t vfmsh_f16(float16_t a, float16_t b, float16_t c);

// FORCE_INLINE float16x4_t vabs_f16(float16x4_t a);

// FORCE_INLINE float16x8_t vabsq_f16(float16x8_t a);

// FORCE_INLINE uint16x4_t vceqz_f16(float16x4_t a);

// FORCE_INLINE uint16x8_t vceqzq_f16(float16x8_t a);

// FORCE_INLINE uint16x4_t vcgez_f16(float16x4_t a);

// FORCE_INLINE uint16x8_t vcgezq_f16(float16x8_t a);

// FORCE_INLINE uint16x4_t vcgtz_f16(float16x4_t a);

// FORCE_INLINE uint16x8_t vcgtzq_f16(float16x8_t a);

// FORCE_INLINE uint16x4_t vclez_f16(float16x4_t a);

// FORCE_INLINE uint16x8_t vclezq_f16(float16x8_t a);

// FORCE_INLINE uint16x4_t vcltz_f16(float16x4_t a);

// FORCE_INLINE uint16x8_t vcltzq_f16(float16x8_t a);

// FORCE_INLINE float16x4_t vcvt_f16_s16(int16x4_t a);

// FORCE_INLINE float16x8_t vcvtq_f16_s16(int16x8_t a);

// FORCE_INLINE float16x4_t vcvt_f16_u16(uint16x4_t a);

// FORCE_INLINE float16x8_t vcvtq_f16_u16(uint16x8_t a);

// FORCE_INLINE int16x4_t vcvt_s16_f16(float16x4_t a);

// FORCE_INLINE int16x8_t vcvtq_s16_f16(float16x8_t a);

// FORCE_INLINE uint16x4_t vcvt_u16_f16(float16x4_t a);

// FORCE_INLINE uint16x8_t vcvtq_u16_f16(float16x8_t a);

// FORCE_INLINE int16x4_t vcvta_s16_f16(float16x4_t a);

// FORCE_INLINE int16x8_t vcvtaq_s16_f16(float16x8_t a);

// FORCE_INLINE uint16x4_t vcvta_u16_f16(float16x4_t a);

// FORCE_INLINE uint16x8_t vcvtaq_u16_f16(float16x8_t a);

// FORCE_INLINE int16x4_t vcvtm_s16_f16(float16x4_t a);

// FORCE_INLINE int16x8_t vcvtmq_s16_f16(float16x8_t a);

// FORCE_INLINE uint16x4_t vcvtm_u16_f16(float16x4_t a);

// FORCE_INLINE uint16x8_t vcvtmq_u16_f16(float16x8_t a);

// FORCE_INLINE int16x4_t vcvtn_s16_f16(float16x4_t a);

// FORCE_INLINE int16x8_t vcvtnq_s16_f16(float16x8_t a);

// FORCE_INLINE uint16x4_t vcvtn_u16_f16(float16x4_t a);

// FORCE_INLINE uint16x8_t vcvtnq_u16_f16(float16x8_t a);

// FORCE_INLINE int16x4_t vcvtp_s16_f16(float16x4_t a);

// FORCE_INLINE int16x8_t vcvtpq_s16_f16(float16x8_t a);

// FORCE_INLINE uint16x4_t vcvtp_u16_f16(float16x4_t a);

// FORCE_INLINE uint16x8_t vcvtpq_u16_f16(float16x8_t a);

// FORCE_INLINE float16x4_t vneg_f16(float16x4_t a);

// FORCE_INLINE float16x8_t vnegq_f16(float16x8_t a);

// FORCE_INLINE float16x4_t vrecpe_f16(float16x4_t a);

// FORCE_INLINE float16x8_t vrecpeq_f16(float16x8_t a);

// FORCE_INLINE float16x4_t vrnd_f16(float16x4_t a);

// FORCE_INLINE float16x8_t vrndq_f16(float16x8_t a);

// FORCE_INLINE float16x4_t vrnda_f16(float16x4_t a);

// FORCE_INLINE float16x8_t vrndaq_f16(float16x8_t a);

// FORCE_INLINE float16x4_t vrndi_f16(float16x4_t a);

// FORCE_INLINE float16x8_t vrndiq_f16(float16x8_t a);

// FORCE_INLINE float16x4_t vrndm_f16(float16x4_t a);

// FORCE_INLINE float16x8_t vrndmq_f16(float16x8_t a);

// FORCE_INLINE float16x4_t vrndn_f16(float16x4_t a);

// FORCE_INLINE float16x8_t vrndnq_f16(float16x8_t a);

// FORCE_INLINE float16x4_t vrndp_f16(float16x4_t a);

// FORCE_INLINE float16x8_t vrndpq_f16(float16x8_t a);

// FORCE_INLINE float16x4_t vrndx_f16(float16x4_t a);

// FORCE_INLINE float16x8_t vrndxq_f16(float16x8_t a);

// FORCE_INLINE float16x4_t vrsqrte_f16(float16x4_t a);

// FORCE_INLINE float16x8_t vrsqrteq_f16(float16x8_t a);

// FORCE_INLINE float16x4_t vsqrt_f16(float16x4_t a);

// FORCE_INLINE float16x8_t vsqrtq_f16(float16x8_t a);

// FORCE_INLINE float16x4_t vadd_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float16x8_t vaddq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float16x4_t vabd_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float16x8_t vabdq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE uint16x4_t vcage_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE uint16x8_t vcageq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE uint16x4_t vcagt_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE uint16x8_t vcagtq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE uint16x4_t vcale_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE uint16x8_t vcaleq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE uint16x4_t vcalt_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE uint16x8_t vcaltq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE uint16x4_t vceq_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE uint16x8_t vceqq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE uint16x4_t vcge_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE uint16x8_t vcgeq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE uint16x4_t vcgt_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE uint16x8_t vcgtq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE uint16x4_t vcle_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE uint16x8_t vcleq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE uint16x4_t vclt_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE uint16x8_t vcltq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float16x4_t vcvt_n_f16_s16(int16x4_t a, const int n);

// FORCE_INLINE float16x8_t vcvtq_n_f16_s16(int16x8_t a, const int n);

// FORCE_INLINE float16x4_t vcvt_n_f16_u16(uint16x4_t a, const int n);

// FORCE_INLINE float16x8_t vcvtq_n_f16_u16(uint16x8_t a, const int n);

// FORCE_INLINE int16x4_t vcvt_n_s16_f16(float16x4_t a, const int n);

// FORCE_INLINE int16x8_t vcvtq_n_s16_f16(float16x8_t a, const int n);

// FORCE_INLINE uint16x4_t vcvt_n_u16_f16(float16x4_t a, const int n);

// FORCE_INLINE uint16x8_t vcvtq_n_u16_f16(float16x8_t a, const int n);

// FORCE_INLINE float16x4_t vdiv_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float16x8_t vdivq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float16x4_t vmax_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float16x8_t vmaxq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float16x4_t vmaxnm_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float16x8_t vmaxnmq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float16x4_t vmin_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float16x8_t vminq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float16x4_t vminnm_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float16x8_t vminnmq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float16x4_t vmul_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float16x8_t vmulq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float16x4_t vmulx_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float16x8_t vmulxq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float16x4_t vpadd_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float16x8_t vpaddq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float16x4_t vpmax_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float16x8_t vpmaxq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float16x4_t vpmaxnm_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float16x8_t vpmaxnmq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float16x4_t vpmin_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float16x8_t vpminq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float16x4_t vpminnm_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float16x8_t vpminnmq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float16x4_t vrecps_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float16x8_t vrecpsq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float16x4_t vrsqrts_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float16x8_t vrsqrtsq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float16x4_t vsub_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float16x8_t vsubq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float16x4_t vfma_f16(float16x4_t a, float16x4_t b, float16x4_t c);

// FORCE_INLINE float16x8_t vfmaq_f16(float16x8_t a, float16x8_t b, float16x8_t c);

// FORCE_INLINE float16x4_t vfms_f16(float16x4_t a, float16x4_t b, float16x4_t c);

// FORCE_INLINE float16x8_t vfmsq_f16(float16x8_t a, float16x8_t b, float16x8_t c);

// FORCE_INLINE float16x4_t vfma_lane_f16(float16x4_t a, float16x4_t b, float16x4_t v, const int lane);

// FORCE_INLINE float16x8_t vfmaq_lane_f16(float16x8_t a, float16x8_t b, float16x4_t v, const int lane);

// FORCE_INLINE float16x4_t vfma_laneq_f16(float16x4_t a, float16x4_t b, float16x8_t v, const int lane);

// FORCE_INLINE float16x8_t vfmaq_laneq_f16(float16x8_t a, float16x8_t b, float16x8_t v, const int lane);

// FORCE_INLINE float16x4_t vfma_n_f16(float16x4_t a, float16x4_t b, float16_t n);

// FORCE_INLINE float16x8_t vfmaq_n_f16(float16x8_t a, float16x8_t b, float16_t n);

// FORCE_INLINE float16_t vfmah_lane_f16(float16_t a, float16_t b, float16x4_t v, const int lane);

// FORCE_INLINE float16_t vfmah_laneq_f16(float16_t a, float16_t b, float16x8_t v, const int lane);

// FORCE_INLINE float16x4_t vfms_lane_f16(float16x4_t a, float16x4_t b, float16x4_t v, const int lane);

// FORCE_INLINE float16x8_t vfmsq_lane_f16(float16x8_t a, float16x8_t b, float16x4_t v, const int lane);

// FORCE_INLINE float16x4_t vfms_laneq_f16(float16x4_t a, float16x4_t b, float16x8_t v, const int lane);

// FORCE_INLINE float16x8_t vfmsq_laneq_f16(float16x8_t a, float16x8_t b, float16x8_t v, const int lane);

// FORCE_INLINE float16x4_t vfms_n_f16(float16x4_t a, float16x4_t b, float16_t n);

// FORCE_INLINE float16x8_t vfmsq_n_f16(float16x8_t a, float16x8_t b, float16_t n);

// FORCE_INLINE float16_t vfmsh_lane_f16(float16_t a, float16_t b, float16x4_t v, const int lane);

// FORCE_INLINE float16_t vfmsh_laneq_f16(float16_t a, float16_t b, float16x8_t v, const int lane);

// FORCE_INLINE float16x4_t vmul_lane_f16(float16x4_t a, float16x4_t v, const int lane);

// FORCE_INLINE float16x8_t vmulq_lane_f16(float16x8_t a, float16x4_t v, const int lane);

// FORCE_INLINE float16x4_t vmul_laneq_f16(float16x4_t a, float16x8_t v, const int lane);

// FORCE_INLINE float16x8_t vmulq_laneq_f16(float16x8_t a, float16x8_t v, const int lane);

// FORCE_INLINE float16x4_t vmul_n_f16(float16x4_t a, float16_t n);

// FORCE_INLINE float16x8_t vmulq_n_f16(float16x8_t a, float16_t n);

// FORCE_INLINE float16_t vmulh_lane_f16(float16_t a, float16x4_t v, const int lane);

// FORCE_INLINE float16_t vmulh_laneq_f16(float16_t a, float16x8_t v, const int lane);

// FORCE_INLINE float16x4_t vmulx_lane_f16(float16x4_t a, float16x4_t v, const int lane);

// FORCE_INLINE float16x8_t vmulxq_lane_f16(float16x8_t a, float16x4_t v, const int lane);

// FORCE_INLINE float16x4_t vmulx_laneq_f16(float16x4_t a, float16x8_t v, const int lane);

// FORCE_INLINE float16x8_t vmulxq_laneq_f16(float16x8_t a, float16x8_t v, const int lane);

// FORCE_INLINE float16x4_t vmulx_n_f16(float16x4_t a, float16_t n);

// FORCE_INLINE float16x8_t vmulxq_n_f16(float16x8_t a, float16_t n);

// FORCE_INLINE float16_t vmulxh_lane_f16(float16_t a, float16x4_t v, const int lane);

// FORCE_INLINE float16_t vmulxh_laneq_f16(float16_t a, float16x8_t v, const int lane);

// FORCE_INLINE float16_t vmaxv_f16(float16x4_t a);

// FORCE_INLINE float16_t vmaxvq_f16(float16x8_t a);

// FORCE_INLINE float16_t vminv_f16(float16x4_t a);

// FORCE_INLINE float16_t vminvq_f16(float16x8_t a);

// FORCE_INLINE float16_t vmaxnmv_f16(float16x4_t a);

// FORCE_INLINE float16_t vmaxnmvq_f16(float16x8_t a);

// FORCE_INLINE float16_t vminnmv_f16(float16x4_t a);

// FORCE_INLINE float16_t vminnmvq_f16(float16x8_t a);

// FORCE_INLINE float16x4_t vbsl_f16(uint16x4_t a, float16x4_t b, float16x4_t c);

// FORCE_INLINE float16x8_t vbslq_f16(uint16x8_t a, float16x8_t b, float16x8_t c);

// FORCE_INLINE float16x4x2_t vzip_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float16x8x2_t vzipq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float16x4x2_t vuzp_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float16x8x2_t vuzpq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float16x4x2_t vtrn_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float16x8x2_t vtrnq_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float16x4_t vmov_n_f16(float16_t value);

// FORCE_INLINE float16x8_t vmovq_n_f16(float16_t value);

// FORCE_INLINE float16x4_t vdup_n_f16(float16_t value);

// FORCE_INLINE float16x8_t vdupq_n_f16(float16_t value);

// FORCE_INLINE float16x4_t vdup_lane_f16(float16x4_t vec, const int lane);

// FORCE_INLINE float16x8_t vdupq_lane_f16(float16x4_t vec, const int lane);

// FORCE_INLINE float16x4_t vext_f16(float16x4_t a, float16x4_t b, const int n);

// FORCE_INLINE float16x8_t vextq_f16(float16x8_t a, float16x8_t b, const int n);

// FORCE_INLINE float16x4_t vrev64_f16(float16x4_t vec);

// FORCE_INLINE float16x8_t vrev64q_f16(float16x8_t vec);

// FORCE_INLINE float16x4_t vzip1_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float16x8_t vzip1q_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float16x4_t vzip2_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float16x8_t vzip2q_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float16x4_t vuzp1_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float16x8_t vuzp1q_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float16x4_t vuzp2_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float16x8_t vuzp2q_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float16x4_t vtrn1_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float16x8_t vtrn1q_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float16x4_t vtrn2_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float16x8_t vtrn2q_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float16x4_t vdup_laneq_f16(float16x8_t vec, const int lane);

// FORCE_INLINE float16x8_t vdupq_laneq_f16(float16x8_t vec, const int lane);

// FORCE_INLINE float16_t vduph_lane_f16(float16x4_t vec, const int lane);

// FORCE_INLINE float16_t vduph_laneq_f16(float16x8_t vec, const int lane);

FORCE_INLINE uint32x2_t vdot_u32(uint32x2_t r, uint8x8_t a, uint8x8_t b) {
  vuint32m1_t vzero = __riscv_vmv_s_x_u32m1(0, 1);
  vuint16m1_t ab = __riscv_vlmul_trunc_v_u16m2_u16m1(__riscv_vwmulu_vv_u16m2(a, b, 8));
  vbool16_t mask = __riscv_vmsleu_vx_u16m1_b16(__riscv_vid_v_u16m1(8), 3, 8);

  vuint32m1_t r0 = __riscv_vwredsumu_vs_u16m1_u32m1_m(mask, ab, vzero, 8);
  vuint32m1_t r1 = __riscv_vwredsumu_vs_u16m1_u32m1_m(__riscv_vmnot_m_b16(mask, 8), ab, vzero, 8);
  return __riscv_vadd_vv_u32m1(r, __riscv_vslideup_vx_u32m1(r0, r1, 1, 2), 2);
}

// FORCE_INLINE int32x2_t vdot_s32(int32x2_t r, int8x8_t a, int8x8_t b);

FORCE_INLINE uint32x4_t vdotq_u32(uint32x4_t r, uint8x16_t a, uint8x16_t b) {
  vuint32m1_t vzero = __riscv_vmv_s_x_u32m1(0, 1);
  vuint16m2_t ab = __riscv_vwmulu_vv_u16m2(a, b, 16);

  vuint32m1_t r0 = __riscv_vwredsumu_vs_u16m2_u32m1(ab, vzero, 4);
  vuint32m1_t r1 = __riscv_vwredsumu_vs_u16m2_u32m1(__riscv_vslidedown_vx_u16m2(ab, 4, 4), vzero, 4);
  vuint32m1_t r2 = __riscv_vwredsumu_vs_u16m2_u32m1(__riscv_vslidedown_vx_u16m2(ab, 8, 4), vzero, 4);
  vuint32m1_t r3 = __riscv_vwredsumu_vs_u16m2_u32m1(__riscv_vslidedown_vx_u16m2(ab, 12, 4), vzero, 4);

  return __riscv_vadd_vv_u32m1(
      r,
      __riscv_vslideup_vx_u32m1(__riscv_vslideup_vx_u32m1(r0, r1, 1, 2), __riscv_vslideup_vx_u32m1(r2, r3, 1, 2), 2, 4),
      4);
}

// FORCE_INLINE int32x4_t vdotq_s32(int32x4_t r, int8x16_t a, int8x16_t b);

// FORCE_INLINE uint32x2_t vdot_lane_u32(uint32x2_t r, uint8x8_t a, uint8x8_t b, const int lane);

// FORCE_INLINE int32x2_t vdot_lane_s32(int32x2_t r, int8x8_t a, int8x8_t b, const int lane);

// FORCE_INLINE uint32x4_t vdotq_laneq_u32(uint32x4_t r, uint8x16_t a, uint8x16_t b, const int lane);

FORCE_INLINE int32x4_t vdotq_laneq_s32(int32x4_t r, int8x16_t a, int8x16_t b, const int lane) {
  vint32m1_t vzero = __riscv_vmv_s_x_i32m1(0, 1);
  vint8m1_t b_lane = __riscv_vslidedown_vx_i8m1(b, lane * 4, 4);
  b_lane = __riscv_vrgather_vv_i8m1(b_lane, __riscv_vand_vx_u8m1(__riscv_vid_v_u8m1(16), 3, 16), 16);
  vint16m2_t ab = __riscv_vwmul_vv_i16m2(b_lane, a, 16);

  vint32m1_t r0 = __riscv_vwredsum_vs_i16m2_i32m1(ab, vzero, 4);
  vint32m1_t r1 = __riscv_vwredsum_vs_i16m2_i32m1(__riscv_vslidedown_vx_i16m2(ab, 4, 4), vzero, 4);
  vint32m1_t r2 = __riscv_vwredsum_vs_i16m2_i32m1(__riscv_vslidedown_vx_i16m2(ab, 8, 4), vzero, 4);
  vint32m1_t r3 = __riscv_vwredsum_vs_i16m2_i32m1(__riscv_vslidedown_vx_i16m2(ab, 12, 4), vzero, 4);

  return __riscv_vadd_vv_i32m1(
      r,
      __riscv_vslideup_vx_i32m1(__riscv_vslideup_vx_i32m1(r0, r1, 1, 2), __riscv_vslideup_vx_i32m1(r2, r3, 1, 2), 2, 4),
      4);
}

// FORCE_INLINE uint32x2_t vdot_laneq_u32(uint32x2_t r, uint8x8_t a, uint8x16_t b, const int lane);

// FORCE_INLINE int32x2_t vdot_laneq_s32(int32x2_t r, int8x8_t a, int8x16_t b, const int lane);

// FORCE_INLINE uint32x4_t vdotq_lane_u32(uint32x4_t r, uint8x16_t a, uint8x8_t b, const int lane);

FORCE_INLINE int32x4_t vdotq_lane_s32(int32x4_t r, int8x16_t a, int8x8_t b, const int lane) {
  vint32m1_t vzero = __riscv_vmv_s_x_i32m1(0, 1);
  vint8m1_t b_lane = __riscv_vslidedown_vx_i8m1(b, lane * 4, 4);
  b_lane = __riscv_vrgather_vv_i8m1(b_lane, __riscv_vand_vx_u8m1(__riscv_vid_v_u8m1(16), 3, 16), 16);
  vint16m2_t ab = __riscv_vwmul_vv_i16m2(b_lane, a, 16);

  vint32m1_t r0 = __riscv_vwredsum_vs_i16m2_i32m1(ab, vzero, 4);
  vint32m1_t r1 = __riscv_vwredsum_vs_i16m2_i32m1(__riscv_vslidedown_vx_i16m2(ab, 4, 4), vzero, 4);
  vint32m1_t r2 = __riscv_vwredsum_vs_i16m2_i32m1(__riscv_vslidedown_vx_i16m2(ab, 8, 4), vzero, 4);
  vint32m1_t r3 = __riscv_vwredsum_vs_i16m2_i32m1(__riscv_vslidedown_vx_i16m2(ab, 12, 4), vzero, 4);

  return __riscv_vadd_vv_i32m1(
      r,
      __riscv_vslideup_vx_i32m1(__riscv_vslideup_vx_i32m1(r0, r1, 1, 2), __riscv_vslideup_vx_i32m1(r2, r3, 1, 2), 2, 4),
      4);
}

// FORCE_INLINE uint64x2_t vsha512hq_u64(uint64x2_t hash_ed, uint64x2_t hash_gf, uint64x2_t kwh_kwh2);

// FORCE_INLINE uint64x2_t vsha512h2q_u64(uint64x2_t sum_ab, uint64x2_t hash_c_, uint64x2_t hash_ab);

// FORCE_INLINE uint64x2_t vsha512su0q_u64(uint64x2_t w0_1, uint64x2_t w2_);

// FORCE_INLINE uint64x2_t vsha512su1q_u64(uint64x2_t s01_s02, uint64x2_t w14_15, uint64x2_t w9_10);

FORCE_INLINE uint8x16_t veor3q_u8(uint8x16_t a, uint8x16_t b, uint8x16_t c) {
  return __riscv_vxor_vv_u8m1(a, __riscv_vxor_vv_u8m1(b, c, 16), 16);
}

FORCE_INLINE uint16x8_t veor3q_u16(uint16x8_t a, uint16x8_t b, uint16x8_t c) {
  return __riscv_vxor_vv_u16m1(a, __riscv_vxor_vv_u16m1(b, c, 8), 8);
}

FORCE_INLINE uint32x4_t veor3q_u32(uint32x4_t a, uint32x4_t b, uint32x4_t c) {
  return __riscv_vxor_vv_u32m1(a, __riscv_vxor_vv_u32m1(b, c, 4), 4);
}

FORCE_INLINE uint64x2_t veor3q_u64(uint64x2_t a, uint64x2_t b, uint64x2_t c) {
  return __riscv_vxor_vv_u64m1(a, __riscv_vxor_vv_u64m1(b, c, 2), 2);
}

FORCE_INLINE int8x16_t veor3q_s8(int8x16_t a, int8x16_t b, int8x16_t c) {
  return __riscv_vxor_vv_i8m1(a, __riscv_vxor_vv_i8m1(b, c, 16), 16);
}

FORCE_INLINE int16x8_t veor3q_s16(int16x8_t a, int16x8_t b, int16x8_t c) {
  return __riscv_vxor_vv_i16m1(a, __riscv_vxor_vv_i16m1(b, c, 8), 8);
}

FORCE_INLINE int32x4_t veor3q_s32(int32x4_t a, int32x4_t b, int32x4_t c) {
  return __riscv_vxor_vv_i32m1(a, __riscv_vxor_vv_i32m1(b, c, 4), 4);
}

FORCE_INLINE int64x2_t veor3q_s64(int64x2_t a, int64x2_t b, int64x2_t c) {
  return __riscv_vxor_vv_i64m1(a, __riscv_vxor_vv_i64m1(b, c, 2), 2);
}

// FORCE_INLINE uint64x2_t vrax1q_u64(uint64x2_t a, uint64x2_t b);

// FORCE_INLINE uint64x2_t vxarq_u64(uint64x2_t a, uint64x2_t b, const int imm6);

// FORCE_INLINE uint8x16_t vbcaxq_u8(uint8x16_t a, uint8x16_t b, uint8x16_t c);

// FORCE_INLINE uint16x8_t vbcaxq_u16(uint16x8_t a, uint16x8_t b, uint16x8_t c);

// FORCE_INLINE uint32x4_t vbcaxq_u32(uint32x4_t a, uint32x4_t b, uint32x4_t c);

// FORCE_INLINE uint64x2_t vbcaxq_u64(uint64x2_t a, uint64x2_t b, uint64x2_t c);

// FORCE_INLINE int8x16_t vbcaxq_s8(int8x16_t a, int8x16_t b, int8x16_t c);

// FORCE_INLINE int16x8_t vbcaxq_s16(int16x8_t a, int16x8_t b, int16x8_t c);

// FORCE_INLINE int32x4_t vbcaxq_s32(int32x4_t a, int32x4_t b, int32x4_t c);

// FORCE_INLINE int64x2_t vbcaxq_s64(int64x2_t a, int64x2_t b, int64x2_t c);

// FORCE_INLINE uint32x4_t vsm3ss1q_u32(uint32x4_t a, uint32x4_t b, uint32x4_t c);

// FORCE_INLINE uint32x4_t vsm3tt1aq_u32(uint32x4_t a, uint32x4_t b, uint32x4_t c, const int imm2);

// FORCE_INLINE uint32x4_t vsm3tt1bq_u32(uint32x4_t a, uint32x4_t b, uint32x4_t c, const int imm2);

// FORCE_INLINE uint32x4_t vsm3tt2aq_u32(uint32x4_t a, uint32x4_t b, uint32x4_t c, const int imm2);

// FORCE_INLINE uint32x4_t vsm3tt2bq_u32(uint32x4_t a, uint32x4_t b, uint32x4_t c, const int imm2);

// FORCE_INLINE uint32x4_t vsm3partw1q_u32(uint32x4_t a, uint32x4_t b, uint32x4_t c);

// FORCE_INLINE uint32x4_t vsm3partw2q_u32(uint32x4_t a, uint32x4_t b, uint32x4_t c);

// FORCE_INLINE uint32x4_t vsm4eq_u32(uint32x4_t a, uint32x4_t b);

// FORCE_INLINE uint32x4_t vsm4ekeyq_u32(uint32x4_t a, uint32x4_t b);

// FORCE_INLINE float32x2_t vfmlal_low_f16(float32x2_t r, float16x4_t a, float16x4_t b);

// FORCE_INLINE float32x2_t vfmlsl_low_f16(float32x2_t r, float16x4_t a, float16x4_t b);

// FORCE_INLINE float32x4_t vfmlalq_low_f16(float32x4_t r, float16x8_t a, float16x8_t b);

// FORCE_INLINE float32x4_t vfmlslq_low_f16(float32x4_t r, float16x8_t a, float16x8_t b);

// FORCE_INLINE float32x2_t vfmlal_high_f16(float32x2_t r, float16x4_t a, float16x4_t b);

// FORCE_INLINE float32x2_t vfmlsl_high_f16(float32x2_t r, float16x4_t a, float16x4_t b);

// FORCE_INLINE float32x4_t vfmlalq_high_f16(float32x4_t r, float16x8_t a, float16x8_t b);

// FORCE_INLINE float32x4_t vfmlslq_high_f16(float32x4_t r, float16x8_t a, float16x8_t b);

// FORCE_INLINE float32x2_t vfmlal_lane_low_f16(float32x2_t r, float16x4_t a, float16x4_t b, const int lane);

// FORCE_INLINE float32x2_t vfmlal_laneq_low_f16(float32x2_t r, float16x4_t a, float16x8_t b, const int lane);

// FORCE_INLINE float32x4_t vfmlalq_lane_low_f16(float32x4_t r, float16x8_t a, float16x4_t b, const int lane);

// FORCE_INLINE float32x4_t vfmlalq_laneq_low_f16(float32x4_t r, float16x8_t a, float16x8_t b, const int lane);

// FORCE_INLINE float32x2_t vfmlsl_lane_low_f16(float32x2_t r, float16x4_t a, float16x4_t b, const int lane);

// FORCE_INLINE float32x2_t vfmlsl_laneq_low_f16(float32x2_t r, float16x4_t a, float16x8_t b, const int lane);

// FORCE_INLINE float32x4_t vfmlslq_lane_low_f16(float32x4_t r, float16x8_t a, float16x4_t b, const int lane);

// FORCE_INLINE float32x4_t vfmlslq_laneq_low_f16(float32x4_t r, float16x8_t a, float16x8_t b, const int lane);

// FORCE_INLINE float32x2_t vfmlal_lane_high_f16(float32x2_t r, float16x4_t a, float16x4_t b, const int lane);

// FORCE_INLINE float32x2_t vfmlsl_lane_high_f16(float32x2_t r, float16x4_t a, float16x4_t b, const int lane);

// FORCE_INLINE float32x4_t vfmlalq_lane_high_f16(float32x4_t r, float16x8_t a, float16x4_t b, const int lane);

// FORCE_INLINE float32x4_t vfmlslq_lane_high_f16(float32x4_t r, float16x8_t a, float16x4_t b, const int lane);

// FORCE_INLINE float32x2_t vfmlal_laneq_high_f16(float32x2_t r, float16x4_t a, float16x8_t b, const int lane);

// FORCE_INLINE float32x2_t vfmlsl_laneq_high_f16(float32x2_t r, float16x4_t a, float16x8_t b, const int lane);

// FORCE_INLINE float32x4_t vfmlalq_laneq_high_f16(float32x4_t r, float16x8_t a, float16x8_t b, const int lane);

// FORCE_INLINE float32x4_t vfmlslq_laneq_high_f16(float32x4_t r, float16x8_t a, float16x8_t b, const int lane);

// FORCE_INLINE float16x4_t vcadd_rot90_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float32x2_t vcadd_rot90_f32(float32x2_t a, float32x2_t b);

// FORCE_INLINE float16x8_t vcaddq_rot90_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float32x4_t vcaddq_rot90_f32(float32x4_t a, float32x4_t b);

// FORCE_INLINE float64x2_t vcaddq_rot90_f64(float64x2_t a, float64x2_t b);

// FORCE_INLINE float16x4_t vcadd_rot270_f16(float16x4_t a, float16x4_t b);

// FORCE_INLINE float32x2_t vcadd_rot270_f32(float32x2_t a, float32x2_t b);

// FORCE_INLINE float16x8_t vcaddq_rot270_f16(float16x8_t a, float16x8_t b);

// FORCE_INLINE float32x4_t vcaddq_rot270_f32(float32x4_t a, float32x4_t b);

// FORCE_INLINE float64x2_t vcaddq_rot270_f64(float64x2_t a, float64x2_t b);

// FORCE_INLINE float16x4_t vcmla_f16(float16x4_t r, float16x4_t a, float16x4_t b);

// FORCE_INLINE float32x2_t vcmla_f32(float32x2_t r, float32x2_t a, float32x2_t b);

// FORCE_INLINE float16x4_t vcmla_lane_f16(float16x4_t r, float16x4_t a, float16x4_t b, const int lane);

// FORCE_INLINE float32x2_t vcmla_lane_f32(float32x2_t r, float32x2_t a, float32x2_t b, const int lane);

// FORCE_INLINE float16x4_t vcmla_laneq_f16(float16x4_t r, float16x4_t a, float16x8_t b, const int lane);

// FORCE_INLINE float32x2_t vcmla_laneq_f32(float32x2_t r, float32x2_t a, float32x4_t b, const int lane);

// FORCE_INLINE float16x8_t vcmlaq_f16(float16x8_t r, float16x8_t a, float16x8_t b);

// FORCE_INLINE float32x4_t vcmlaq_f32(float32x4_t r, float32x4_t a, float32x4_t b);

// FORCE_INLINE float64x2_t vcmlaq_f64(float64x2_t r, float64x2_t a, float64x2_t b);

// FORCE_INLINE float16x8_t vcmlaq_lane_f16(float16x8_t r, float16x8_t a, float16x4_t b, const int lane);

// FORCE_INLINE float32x4_t vcmlaq_lane_f32(float32x4_t r, float32x4_t a, float32x2_t b, const int lane);

// FORCE_INLINE float16x8_t vcmlaq_laneq_f16(float16x8_t r, float16x8_t a, float16x8_t b, const int lane);

// FORCE_INLINE float32x4_t vcmlaq_laneq_f32(float32x4_t r, float32x4_t a, float32x4_t b, const int lane);

// FORCE_INLINE float16x4_t vcmla_rot90_f16(float16x4_t r, float16x4_t a, float16x4_t b);

// FORCE_INLINE float32x2_t vcmla_rot90_f32(float32x2_t r, float32x2_t a, float32x2_t b);

// FORCE_INLINE float16x4_t vcmla_rot90_lane_f16(float16x4_t r, float16x4_t a, float16x4_t b, const int lane);

// FORCE_INLINE float32x2_t vcmla_rot90_lane_f32(float32x2_t r, float32x2_t a, float32x2_t b, const int lane);

// FORCE_INLINE float16x4_t vcmla_rot90_laneq_f16(float16x4_t r, float16x4_t a, float16x8_t b, const int lane);

// FORCE_INLINE float32x2_t vcmla_rot90_laneq_f32(float32x2_t r, float32x2_t a, float32x4_t b, const int lane);

// FORCE_INLINE float16x8_t vcmlaq_rot90_f16(float16x8_t r, float16x8_t a, float16x8_t b);

// FORCE_INLINE float32x4_t vcmlaq_rot90_f32(float32x4_t r, float32x4_t a, float32x4_t b);

// FORCE_INLINE float64x2_t vcmlaq_rot90_f64(float64x2_t r, float64x2_t a, float64x2_t b);

// FORCE_INLINE float16x8_t vcmlaq_rot90_lane_f16(float16x8_t r, float16x8_t a, float16x4_t b, const int lane);

// FORCE_INLINE float32x4_t vcmlaq_rot90_lane_f32(float32x4_t r, float32x4_t a, float32x2_t b, const int lane);

// FORCE_INLINE float16x8_t vcmlaq_rot90_laneq_f16(float16x8_t r, float16x8_t a, float16x8_t b, const int lane);

// FORCE_INLINE float32x4_t vcmlaq_rot90_laneq_f32(float32x4_t r, float32x4_t a, float32x4_t b, const int lane);

// FORCE_INLINE float16x4_t vcmla_rot180_f16(float16x4_t r, float16x4_t a, float16x4_t b);

// FORCE_INLINE float32x2_t vcmla_rot180_f32(float32x2_t r, float32x2_t a, float32x2_t b);

// FORCE_INLINE float16x4_t vcmla_rot180_lane_f16(float16x4_t r, float16x4_t a, float16x4_t b, const int lane);

// FORCE_INLINE float32x2_t vcmla_rot180_lane_f32(float32x2_t r, float32x2_t a, float32x2_t b, const int lane);

// FORCE_INLINE float16x4_t vcmla_rot180_laneq_f16(float16x4_t r, float16x4_t a, float16x8_t b, const int lane);

// FORCE_INLINE float32x2_t vcmla_rot180_laneq_f32(float32x2_t r, float32x2_t a, float32x4_t b, const int lane);

// FORCE_INLINE float16x8_t vcmlaq_rot180_f16(float16x8_t r, float16x8_t a, float16x8_t b);

// FORCE_INLINE float32x4_t vcmlaq_rot180_f32(float32x4_t r, float32x4_t a, float32x4_t b);

// FORCE_INLINE float64x2_t vcmlaq_rot180_f64(float64x2_t r, float64x2_t a, float64x2_t b);

// FORCE_INLINE float16x8_t vcmlaq_rot180_lane_f16(float16x8_t r, float16x8_t a, float16x4_t b, const int lane);

// FORCE_INLINE float32x4_t vcmlaq_rot180_lane_f32(float32x4_t r, float32x4_t a, float32x2_t b, const int lane);

// FORCE_INLINE float16x8_t vcmlaq_rot180_laneq_f16(float16x8_t r, float16x8_t a, float16x8_t b, const int lane);

// FORCE_INLINE float32x4_t vcmlaq_rot180_laneq_f32(float32x4_t r, float32x4_t a, float32x4_t b, const int lane);

// FORCE_INLINE float16x4_t vcmla_rot270_f16(float16x4_t r, float16x4_t a, float16x4_t b);

// FORCE_INLINE float32x2_t vcmla_rot270_f32(float32x2_t r, float32x2_t a, float32x2_t b);

// FORCE_INLINE float16x4_t vcmla_rot270_lane_f16(float16x4_t r, float16x4_t a, float16x4_t b, const int lane);

// FORCE_INLINE float32x2_t vcmla_rot270_lane_f32(float32x2_t r, float32x2_t a, float32x2_t b, const int lane);

// FORCE_INLINE float16x4_t vcmla_rot270_laneq_f16(float16x4_t r, float16x4_t a, float16x8_t b, const int lane);

// FORCE_INLINE float32x2_t vcmla_rot270_laneq_f32(float32x2_t r, float32x2_t a, float32x4_t b, const int lane);

// FORCE_INLINE float16x8_t vcmlaq_rot270_f16(float16x8_t r, float16x8_t a, float16x8_t b);

// FORCE_INLINE float32x4_t vcmlaq_rot270_f32(float32x4_t r, float32x4_t a, float32x4_t b);

// FORCE_INLINE float64x2_t vcmlaq_rot270_f64(float64x2_t r, float64x2_t a, float64x2_t b);

// FORCE_INLINE float16x8_t vcmlaq_rot270_lane_f16(float16x8_t r, float16x8_t a, float16x4_t b, const int lane);

// FORCE_INLINE float32x4_t vcmlaq_rot270_lane_f32(float32x4_t r, float32x4_t a, float32x2_t b, const int lane);

// FORCE_INLINE float16x8_t vcmlaq_rot270_laneq_f16(float16x8_t r, float16x8_t a, float16x8_t b, const int lane);

// FORCE_INLINE float32x4_t vcmlaq_rot270_laneq_f32(float32x4_t r, float32x4_t a, float32x4_t b, const int lane);

// FORCE_INLINE float32x2_t vrnd32z_f32(float32x2_t a);

// FORCE_INLINE float32x4_t vrnd32zq_f32(float32x4_t a);

// FORCE_INLINE float64x1_t vrnd32z_f64(float64x1_t a);

// FORCE_INLINE float64x2_t vrnd32zq_f64(float64x2_t a);

// FORCE_INLINE float32x2_t vrnd64z_f32(float32x2_t a);

// FORCE_INLINE float32x4_t vrnd64zq_f32(float32x4_t a);

// FORCE_INLINE float64x1_t vrnd64z_f64(float64x1_t a);

// FORCE_INLINE float64x2_t vrnd64zq_f64(float64x2_t a);

// FORCE_INLINE float32x2_t vrnd32x_f32(float32x2_t a);

// FORCE_INLINE float32x4_t vrnd32xq_f32(float32x4_t a);

// FORCE_INLINE float64x1_t vrnd32x_f64(float64x1_t a);

// FORCE_INLINE float64x2_t vrnd32xq_f64(float64x2_t a);

// FORCE_INLINE float32x2_t vrnd64x_f32(float32x2_t a);

// FORCE_INLINE float32x4_t vrnd64xq_f32(float32x4_t a);

// FORCE_INLINE float64x1_t vrnd64x_f64(float64x1_t a);

// FORCE_INLINE float64x2_t vrnd64xq_f64(float64x2_t a);

// FORCE_INLINE int32x4_t vmmlaq_s32(int32x4_t r, int8x16_t a, int8x16_t b);

// FORCE_INLINE uint32x4_t vmmlaq_u32(uint32x4_t r, uint8x16_t a, uint8x16_t b);

// FORCE_INLINE int32x4_t vusmmlaq_s32(int32x4_t r, uint8x16_t a, int8x16_t b);

// FORCE_INLINE int32x2_t vusdot_s32(int32x2_t r, uint8x8_t a, int8x8_t b);

// FORCE_INLINE int32x2_t vusdot_lane_s32(int32x2_t r, uint8x8_t a, int8x8_t b, const int lane);

// FORCE_INLINE int32x2_t vsudot_lane_s32(int32x2_t r, int8x8_t a, uint8x8_t b, const int lane);

// FORCE_INLINE int32x2_t vusdot_laneq_s32(int32x2_t r, uint8x8_t a, int8x16_t b, const int lane);

// FORCE_INLINE int32x2_t vsudot_laneq_s32(int32x2_t r, int8x8_t a, uint8x16_t b, const int lane);

FORCE_INLINE int32x4_t vusdotq_s32(int32x4_t r, uint8x16_t a, int8x16_t b) {
  vint32m1_t vzero = __riscv_vmv_s_x_i32m1(0, 1);
  vint16m2_t ab = __riscv_vwmulsu_vv_i16m2(b, a, 16);

  vint32m1_t r0 = __riscv_vwredsum_vs_i16m2_i32m1(ab, vzero, 4);
  vint32m1_t r1 = __riscv_vwredsum_vs_i16m2_i32m1(__riscv_vslidedown_vx_i16m2(ab, 4, 4), vzero, 4);
  vint32m1_t r2 = __riscv_vwredsum_vs_i16m2_i32m1(__riscv_vslidedown_vx_i16m2(ab, 8, 4), vzero, 4);
  vint32m1_t r3 = __riscv_vwredsum_vs_i16m2_i32m1(__riscv_vslidedown_vx_i16m2(ab, 12, 4), vzero, 4);

  return __riscv_vadd_vv_i32m1(
      r,
      __riscv_vslideup_vx_i32m1(__riscv_vslideup_vx_i32m1(r0, r1, 1, 2), __riscv_vslideup_vx_i32m1(r2, r3, 1, 2), 2, 4),
      4);
}

FORCE_INLINE int32x4_t vusdotq_lane_s32(int32x4_t r, uint8x16_t a, int8x8_t b, const int lane) {
  vint32m1_t vzero = __riscv_vmv_s_x_i32m1(0, 1);
  vint8m1_t b_lane = __riscv_vslidedown_vx_i8m1(b, lane * 4, 4);
  b_lane = __riscv_vrgather_vv_i8m1(b_lane, __riscv_vand_vx_u8m1(__riscv_vid_v_u8m1(16), 3, 16), 16);
  vint16m2_t ab = __riscv_vwmulsu_vv_i16m2(b_lane, a, 16);

  vint32m1_t r0 = __riscv_vwredsum_vs_i16m2_i32m1(ab, vzero, 4);
  vint32m1_t r1 = __riscv_vwredsum_vs_i16m2_i32m1(__riscv_vslidedown_vx_i16m2(ab, 4, 4), vzero, 4);
  vint32m1_t r2 = __riscv_vwredsum_vs_i16m2_i32m1(__riscv_vslidedown_vx_i16m2(ab, 8, 4), vzero, 4);
  vint32m1_t r3 = __riscv_vwredsum_vs_i16m2_i32m1(__riscv_vslidedown_vx_i16m2(ab, 12, 4), vzero, 4);

  return __riscv_vadd_vv_i32m1(
      r,
      __riscv_vslideup_vx_i32m1(__riscv_vslideup_vx_i32m1(r0, r1, 1, 2), __riscv_vslideup_vx_i32m1(r2, r3, 1, 2), 2, 4),
      4);
}

// FORCE_INLINE int32x4_t vsudotq_lane_s32(int32x4_t r, int8x16_t a, uint8x8_t b, const int lane);

FORCE_INLINE int32x4_t vusdotq_laneq_s32(int32x4_t r, uint8x16_t a, int8x16_t b, const int lane) {
  vint32m1_t vzero = __riscv_vmv_s_x_i32m1(0, 1);
  vint8m1_t b_lane = __riscv_vslidedown_vx_i8m1(b, lane * 4, 4);
  b_lane = __riscv_vrgather_vv_i8m1(b_lane, __riscv_vand_vx_u8m1(__riscv_vid_v_u8m1(16), 3, 16), 16);
  vint16m2_t ab = __riscv_vwmulsu_vv_i16m2(b_lane, a, 16);

  vint32m1_t r0 = __riscv_vwredsum_vs_i16m2_i32m1(ab, vzero, 4);
  vint32m1_t r1 = __riscv_vwredsum_vs_i16m2_i32m1(__riscv_vslidedown_vx_i16m2(ab, 4, 4), vzero, 4);
  vint32m1_t r2 = __riscv_vwredsum_vs_i16m2_i32m1(__riscv_vslidedown_vx_i16m2(ab, 8, 4), vzero, 4);
  vint32m1_t r3 = __riscv_vwredsum_vs_i16m2_i32m1(__riscv_vslidedown_vx_i16m2(ab, 12, 4), vzero, 4);

  return __riscv_vadd_vv_i32m1(
      r,
      __riscv_vslideup_vx_i32m1(__riscv_vslideup_vx_i32m1(r0, r1, 1, 2), __riscv_vslideup_vx_i32m1(r2, r3, 1, 2), 2, 4),
      4);
}

// FORCE_INLINE int32x4_t vsudotq_laneq_s32(int32x4_t r, int8x16_t a, uint8x16_t b, const int lane);

// FORCE_INLINE bfloat16x4_t vcreate_bf16(uint64_t a);

// FORCE_INLINE bfloat16x4_t vdup_n_bf16(bfloat16_t value);

// FORCE_INLINE bfloat16x8_t vdupq_n_bf16(bfloat16_t value);

// FORCE_INLINE bfloat16x4_t vdup_lane_bf16(bfloat16x4_t vec, const int lane);

// FORCE_INLINE bfloat16x8_t vdupq_lane_bf16(bfloat16x4_t vec, const int lane);

// FORCE_INLINE bfloat16x4_t vdup_laneq_bf16(bfloat16x8_t vec, const int lane);

// FORCE_INLINE bfloat16x8_t vdupq_laneq_bf16(bfloat16x8_t vec, const int lane);

// FORCE_INLINE bfloat16x8_t vcombine_bf16(bfloat16x4_t low, bfloat16x4_t high);

// FORCE_INLINE bfloat16x4_t vget_high_bf16(bfloat16x8_t a);

// FORCE_INLINE bfloat16x4_t vget_low_bf16(bfloat16x8_t a);

// FORCE_INLINE bfloat16_t vget_lane_bf16(bfloat16x4_t v, const int lane);

// FORCE_INLINE bfloat16_t vgetq_lane_bf16(bfloat16x8_t v, const int lane);

// FORCE_INLINE bfloat16x4_t vset_lane_bf16(bfloat16_t a, bfloat16x4_t v, const int lane);

// FORCE_INLINE bfloat16x8_t vsetq_lane_bf16(bfloat16_t a, bfloat16x8_t v, const int lane);

// FORCE_INLINE bfloat16_t vduph_lane_bf16(bfloat16x4_t vec, const int lane);

// FORCE_INLINE bfloat16_t vduph_laneq_bf16(bfloat16x8_t vec, const int lane);

// FORCE_INLINE bfloat16x4_t vld1_bf16(bfloat16_t const * ptr);

// FORCE_INLINE bfloat16x8_t vld1q_bf16(bfloat16_t const * ptr);

// FORCE_INLINE bfloat16x4_t vld1_lane_bf16(bfloat16_t const * ptr, bfloat16x4_t src, const int lane);

// FORCE_INLINE bfloat16x8_t vld1q_lane_bf16(bfloat16_t const * ptr, bfloat16x8_t src, const int lane);

// FORCE_INLINE bfloat16x4_t vld1_dup_bf16(bfloat16_t const * ptr);

// FORCE_INLINE bfloat16x8_t vld1q_dup_bf16(bfloat16_t const * ptr);

// FORCE_INLINE void vst1_bf16(bfloat16_t * ptr, bfloat16x4_t val);

// FORCE_INLINE void vst1q_bf16(bfloat16_t * ptr, bfloat16x8_t val);

// FORCE_INLINE void vst1_lane_bf16(bfloat16_t * ptr, bfloat16x4_t val, const int lane);

// FORCE_INLINE void vst1q_lane_bf16(bfloat16_t * ptr, bfloat16x8_t val, const int lane);

// FORCE_INLINE bfloat16x4x2_t vld2_bf16(bfloat16_t const * ptr);

// FORCE_INLINE bfloat16x8x2_t vld2q_bf16(bfloat16_t const * ptr);

// FORCE_INLINE bfloat16x4x3_t vld3_bf16(bfloat16_t const * ptr);

// FORCE_INLINE bfloat16x8x3_t vld3q_bf16(bfloat16_t const * ptr);

// FORCE_INLINE bfloat16x4x4_t vld4_bf16(bfloat16_t const * ptr);

// FORCE_INLINE bfloat16x8x4_t vld4q_bf16(bfloat16_t const * ptr);

// FORCE_INLINE bfloat16x4x2_t vld2_dup_bf16(bfloat16_t const * ptr);

// FORCE_INLINE bfloat16x8x2_t vld2q_dup_bf16(bfloat16_t const * ptr);

// FORCE_INLINE bfloat16x4x3_t vld3_dup_bf16(bfloat16_t const * ptr);

// FORCE_INLINE bfloat16x8x3_t vld3q_dup_bf16(bfloat16_t const * ptr);

// FORCE_INLINE bfloat16x4x4_t vld4_dup_bf16(bfloat16_t const * ptr);

// FORCE_INLINE bfloat16x8x4_t vld4q_dup_bf16(bfloat16_t const * ptr);

// FORCE_INLINE void vst2_bf16(bfloat16_t * ptr, bfloat16x4x2_t val);

// FORCE_INLINE void vst2q_bf16(bfloat16_t * ptr, bfloat16x8x2_t val);

// FORCE_INLINE void vst3_bf16(bfloat16_t * ptr, bfloat16x4x3_t val);

// FORCE_INLINE void vst3q_bf16(bfloat16_t * ptr, bfloat16x8x3_t val);

// FORCE_INLINE void vst4_bf16(bfloat16_t * ptr, bfloat16x4x4_t val);

// FORCE_INLINE void vst4q_bf16(bfloat16_t * ptr, bfloat16x8x4_t val);

// FORCE_INLINE bfloat16x4x2_t vld2_lane_bf16(bfloat16_t const * ptr, bfloat16x4x2_t src, const int lane);

// FORCE_INLINE bfloat16x8x2_t vld2q_lane_bf16(bfloat16_t const * ptr, bfloat16x8x2_t src, const int lane);

// FORCE_INLINE bfloat16x4x3_t vld3_lane_bf16(bfloat16_t const * ptr, bfloat16x4x3_t src, const int lane);

// FORCE_INLINE bfloat16x8x3_t vld3q_lane_bf16(bfloat16_t const * ptr, bfloat16x8x3_t src, const int lane);

// FORCE_INLINE bfloat16x4x4_t vld4_lane_bf16(bfloat16_t const * ptr, bfloat16x4x4_t src, const int lane);

// FORCE_INLINE bfloat16x8x4_t vld4q_lane_bf16(bfloat16_t const * ptr, bfloat16x8x4_t src, const int lane);

// FORCE_INLINE void vst2_lane_bf16(bfloat16_t * ptr, bfloat16x4x2_t val, const int lane);

// FORCE_INLINE void vst2q_lane_bf16(bfloat16_t * ptr, bfloat16x8x2_t val, const int lane);

// FORCE_INLINE void vst3_lane_bf16(bfloat16_t * ptr, bfloat16x4x3_t val, const int lane);

// FORCE_INLINE void vst3q_lane_bf16(bfloat16_t * ptr, bfloat16x8x3_t val, const int lane);

// FORCE_INLINE void vst4_lane_bf16(bfloat16_t * ptr, bfloat16x4x4_t val, const int lane);

// FORCE_INLINE void vst4q_lane_bf16(bfloat16_t * ptr, bfloat16x8x4_t val, const int lane);

// FORCE_INLINE void vst1_bf16_x2(bfloat16_t * ptr, bfloat16x4x2_t val);

// FORCE_INLINE void vst1q_bf16_x2(bfloat16_t * ptr, bfloat16x8x2_t val);

// FORCE_INLINE void vst1_bf16_x3(bfloat16_t * ptr, bfloat16x4x3_t val);

// FORCE_INLINE void vst1q_bf16_x3(bfloat16_t * ptr, bfloat16x8x3_t val);

// FORCE_INLINE void vst1_bf16_x4(bfloat16_t * ptr, bfloat16x4x4_t val);

// FORCE_INLINE void vst1q_bf16_x4(bfloat16_t * ptr, bfloat16x8x4_t val);

// FORCE_INLINE bfloat16x4x2_t vld1_bf16_x2(bfloat16_t const * ptr);

// FORCE_INLINE bfloat16x8x2_t vld1q_bf16_x2(bfloat16_t const * ptr);

// FORCE_INLINE bfloat16x4x3_t vld1_bf16_x3(bfloat16_t const * ptr);

// FORCE_INLINE bfloat16x8x3_t vld1q_bf16_x3(bfloat16_t const * ptr);

// FORCE_INLINE bfloat16x4x4_t vld1_bf16_x4(bfloat16_t const * ptr);

// FORCE_INLINE bfloat16x8x4_t vld1q_bf16_x4(bfloat16_t const * ptr);

// FORCE_INLINE bfloat16x4_t vreinterpret_bf16_s8(int8x8_t a);

// FORCE_INLINE bfloat16x4_t vreinterpret_bf16_s16(int16x4_t a);

// FORCE_INLINE bfloat16x4_t vreinterpret_bf16_s32(int32x2_t a);

// FORCE_INLINE bfloat16x4_t vreinterpret_bf16_f32(float32x2_t a);

// FORCE_INLINE bfloat16x4_t vreinterpret_bf16_u8(uint8x8_t a);

// FORCE_INLINE bfloat16x4_t vreinterpret_bf16_u16(uint16x4_t a);

// FORCE_INLINE bfloat16x4_t vreinterpret_bf16_u32(uint32x2_t a);

// FORCE_INLINE bfloat16x4_t vreinterpret_bf16_p8(poly8x8_t a);

// FORCE_INLINE bfloat16x4_t vreinterpret_bf16_p16(poly16x4_t a);

// FORCE_INLINE bfloat16x4_t vreinterpret_bf16_u64(uint64x1_t a);

// FORCE_INLINE bfloat16x4_t vreinterpret_bf16_s64(int64x1_t a);

// FORCE_INLINE bfloat16x8_t vreinterpretq_bf16_s8(int8x16_t a);

// FORCE_INLINE bfloat16x8_t vreinterpretq_bf16_s16(int16x8_t a);

// FORCE_INLINE bfloat16x8_t vreinterpretq_bf16_s32(int32x4_t a);

// FORCE_INLINE bfloat16x8_t vreinterpretq_bf16_f32(float32x4_t a);

// FORCE_INLINE bfloat16x8_t vreinterpretq_bf16_u8(uint8x16_t a);

// FORCE_INLINE bfloat16x8_t vreinterpretq_bf16_u16(uint16x8_t a);

// FORCE_INLINE bfloat16x8_t vreinterpretq_bf16_u32(uint32x4_t a);

// FORCE_INLINE bfloat16x8_t vreinterpretq_bf16_p8(poly8x16_t a);

// FORCE_INLINE bfloat16x8_t vreinterpretq_bf16_p16(poly16x8_t a);

// FORCE_INLINE bfloat16x8_t vreinterpretq_bf16_u64(uint64x2_t a);

// FORCE_INLINE bfloat16x8_t vreinterpretq_bf16_s64(int64x2_t a);

// FORCE_INLINE bfloat16x4_t vreinterpret_bf16_f64(float64x1_t a);

// FORCE_INLINE bfloat16x8_t vreinterpretq_bf16_f64(float64x2_t a);

// FORCE_INLINE bfloat16x4_t vreinterpret_bf16_p64(poly64x1_t a);

// FORCE_INLINE bfloat16x8_t vreinterpretq_bf16_p64(poly64x2_t a);

// FORCE_INLINE bfloat16x8_t vreinterpretq_bf16_p128(poly128_t a);

// FORCE_INLINE int8x8_t vreinterpret_s8_bf16(bfloat16x4_t a);

// FORCE_INLINE int16x4_t vreinterpret_s16_bf16(bfloat16x4_t a);

// FORCE_INLINE int32x2_t vreinterpret_s32_bf16(bfloat16x4_t a);

// FORCE_INLINE float32x2_t vreinterpret_f32_bf16(bfloat16x4_t a);

// FORCE_INLINE uint8x8_t vreinterpret_u8_bf16(bfloat16x4_t a);

// FORCE_INLINE uint16x4_t vreinterpret_u16_bf16(bfloat16x4_t a);

// FORCE_INLINE uint32x2_t vreinterpret_u32_bf16(bfloat16x4_t a);

// FORCE_INLINE poly8x8_t vreinterpret_p8_bf16(bfloat16x4_t a);

// FORCE_INLINE poly16x4_t vreinterpret_p16_bf16(bfloat16x4_t a);

// FORCE_INLINE uint64x1_t vreinterpret_u64_bf16(bfloat16x4_t a);

// FORCE_INLINE int64x1_t vreinterpret_s64_bf16(bfloat16x4_t a);

// FORCE_INLINE float64x1_t vreinterpret_f64_bf16(bfloat16x4_t a);

// FORCE_INLINE poly64x1_t vreinterpret_p64_bf16(bfloat16x4_t a);

// FORCE_INLINE int8x16_t vreinterpretq_s8_bf16(bfloat16x8_t a);

// FORCE_INLINE int16x8_t vreinterpretq_s16_bf16(bfloat16x8_t a);

// FORCE_INLINE int32x4_t vreinterpretq_s32_bf16(bfloat16x8_t a);

// FORCE_INLINE float32x4_t vreinterpretq_f32_bf16(bfloat16x8_t a);

// FORCE_INLINE uint8x16_t vreinterpretq_u8_bf16(bfloat16x8_t a);

// FORCE_INLINE uint16x8_t vreinterpretq_u16_bf16(bfloat16x8_t a);

// FORCE_INLINE uint32x4_t vreinterpretq_u32_bf16(bfloat16x8_t a);

// FORCE_INLINE poly8x16_t vreinterpretq_p8_bf16(bfloat16x8_t a);

// FORCE_INLINE poly16x8_t vreinterpretq_p16_bf16(bfloat16x8_t a);

// FORCE_INLINE uint64x2_t vreinterpretq_u64_bf16(bfloat16x8_t a);

// FORCE_INLINE int64x2_t vreinterpretq_s64_bf16(bfloat16x8_t a);

// FORCE_INLINE float64x2_t vreinterpretq_f64_bf16(bfloat16x8_t a);

// FORCE_INLINE poly64x2_t vreinterpretq_p64_bf16(bfloat16x8_t a);

// FORCE_INLINE poly128_t vreinterpretq_p128_bf16(bfloat16x8_t a);

// FORCE_INLINE float32x4_t vcvt_f32_bf16(bfloat16x4_t a);

// FORCE_INLINE float32x4_t vcvtq_low_f32_bf16(bfloat16x8_t a);

// FORCE_INLINE float32x4_t vcvtq_high_f32_bf16(bfloat16x8_t a);

// FORCE_INLINE bfloat16x4_t vcvt_bf16_f32(float32x4_t a);

// FORCE_INLINE bfloat16x8_t vcvtq_low_bf16_f32(float32x4_t a);

// FORCE_INLINE bfloat16x8_t vcvtq_high_bf16_f32(bfloat16x8_t inactive, float32x4_t a);

// FORCE_INLINE bfloat16_t vcvth_bf16_f32(float32_t a);

// FORCE_INLINE float32_t vcvtah_f32_bf16(bfloat16_t a);

// FORCE_INLINE bfloat16x4_t vcopy_lane_bf16(bfloat16x4_t a, const int lane1, bfloat16x4_t b, const int lane2);

// FORCE_INLINE bfloat16x8_t vcopyq_lane_bf16(bfloat16x8_t a, const int lane1, bfloat16x4_t b, const int lane2);

// FORCE_INLINE bfloat16x4_t vcopy_laneq_bf16(bfloat16x4_t a, const int lane1, bfloat16x8_t b, const int lane2);

// FORCE_INLINE bfloat16x8_t vcopyq_laneq_bf16(bfloat16x8_t a, const int lane1, bfloat16x8_t b, const int lane2);

// FORCE_INLINE float32x2_t vbfdot_f32(float32x2_t r, bfloat16x4_t a, bfloat16x4_t b);

// FORCE_INLINE float32x4_t vbfdotq_f32(float32x4_t r, bfloat16x8_t a, bfloat16x8_t b);

// FORCE_INLINE float32x2_t vbfdot_lane_f32(float32x2_t r, bfloat16x4_t a, bfloat16x4_t b, const int lane);

// FORCE_INLINE float32x4_t vbfdotq_laneq_f32(float32x4_t r, bfloat16x8_t a, bfloat16x8_t b, const int lane);

// FORCE_INLINE float32x2_t vbfdot_laneq_f32(float32x2_t r, bfloat16x4_t a, bfloat16x8_t b, const int lane);

// FORCE_INLINE float32x4_t vbfdotq_lane_f32(float32x4_t r, bfloat16x8_t a, bfloat16x4_t b, const int lane);

// FORCE_INLINE float32x4_t vbfmmlaq_f32(float32x4_t r, bfloat16x8_t a, bfloat16x8_t b);

// FORCE_INLINE float32x4_t vbfmlalbq_f32(float32x4_t r, bfloat16x8_t a, bfloat16x8_t b);

// FORCE_INLINE float32x4_t vbfmlaltq_f32(float32x4_t r, bfloat16x8_t a, bfloat16x8_t b);

// FORCE_INLINE float32x4_t vbfmlalbq_lane_f32(float32x4_t r, bfloat16x8_t a, bfloat16x4_t b, const int lane);

// FORCE_INLINE float32x4_t vbfmlalbq_laneq_f32(float32x4_t r, bfloat16x8_t a, bfloat16x8_t b, const int lane);

// FORCE_INLINE float32x4_t vbfmlaltq_lane_f32(float32x4_t r, bfloat16x8_t a, bfloat16x4_t b, const int lane);

// FORCE_INLINE float32x4_t vbfmlaltq_laneq_f32(float32x4_t r, bfloat16x8_t a, bfloat16x8_t b, const int lane);

FORCE_INLINE int16x4_t vqrdmlsh_lane_s16(int16x4_t a, int16x4_t b, int16x4_t c, const int __d) {
  vint16m1_t c_dup = __riscv_vrgather_vx_i16m1(c, __d, 4);
  vint32m2_t bc_mul = __riscv_vwmul_vv_i32m2(b, c_dup, 4);
  vint32m2_t bc_mulx2 = __riscv_vsll_vx_i32m2(bc_mul, 1, 4);
  vint16m1_t bc_s = __riscv_vnclip_wx_i16m1(bc_mulx2, 16, __RISCV_VXRM_RNU, 4);
  return __riscv_vssub_vv_i16m1(a, bc_s, 4);
}

FORCE_INLINE int32x2_t vqrdmlsh_lane_s32(int32x2_t a, int32x2_t b, int32x2_t c, const int __d) {
  vint32m1_t c_dup = __riscv_vrgather_vx_i32m1(c, __d, 2);
  vint64m2_t bc_mul = __riscv_vwmul_vv_i64m2(b, c_dup, 2);
  vint64m2_t bc_mulx2 = __riscv_vsll_vx_i64m2(bc_mul, 1, 2);
  vint32m1_t bc_s = __riscv_vnclip_wx_i32m1(bc_mulx2, 32, __RISCV_VXRM_RNU, 2);
  return __riscv_vssub_vv_i32m1(a, bc_s, 2);
}

FORCE_INLINE int16x4_t vmul_n_s16(int16x4_t a, int16_t b) { return __riscv_vmul_vx_i16m1(a, b, 4); }

FORCE_INLINE int32x2_t vmul_n_s32(int32x2_t a, int32_t b) { return __riscv_vmul_vx_i32m1(a, b, 2); }

FORCE_INLINE float32x2_t vmul_n_f32(float32x2_t a, float32_t b) { return __riscv_vfmul_vf_f32m1(a, b, 2); }

FORCE_INLINE uint16x4_t vmul_n_u16(uint16x4_t a, uint16_t b) { return __riscv_vmul_vx_u16m1(a, b, 4); }

FORCE_INLINE uint32x2_t vmul_n_u32(uint32x2_t a, uint32_t b) { return __riscv_vmul_vx_u32m1(a, b, 2); }

FORCE_INLINE int16x8_t vmulq_n_s16(int16x8_t a, int16_t b) { return __riscv_vmul_vx_i16m1(a, b, 8); }

FORCE_INLINE int32x4_t vmulq_n_s32(int32x4_t a, int32_t b) { return __riscv_vmul_vx_i32m1(a, b, 4); }

FORCE_INLINE float32x4_t vmulq_n_f32(float32x4_t a, float32_t b) { return __riscv_vfmul_vf_f32m1(a, b, 4); }

FORCE_INLINE float64x1_t vmul_n_f64(float64x1_t a, float64_t b) { return __riscv_vfmul_vf_f64m1(a, b, 1); }

FORCE_INLINE float64x2_t vmulq_n_f64(float64x2_t a, float64_t b) { return __riscv_vfmul_vf_f64m1(a, b, 2); }

FORCE_INLINE uint16x8_t vmulq_n_u16(uint16x8_t a, uint16_t b) { return __riscv_vmul_vx_u16m1(a, b, 8); }

FORCE_INLINE uint32x4_t vmulq_n_u32(uint32x4_t a, uint32_t b) { return __riscv_vmul_vx_u32m1(a, b, 4); }

FORCE_INLINE int32x4_t vmull_n_s16(int16x4_t a, int16_t b) {
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vx_i32m2(a, b, 4));
}

FORCE_INLINE int64x2_t vmull_n_s32(int32x2_t a, int32_t b) {
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vx_i64m2(a, b, 2));
}

FORCE_INLINE uint32x4_t vmull_n_u16(uint16x4_t a, uint16_t b) {
  return __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwmulu_vx_u32m2(a, b, 4));
}

FORCE_INLINE uint64x2_t vmull_n_u32(uint32x2_t a, uint32_t b) {
  return __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwmulu_vx_u64m2(a, b, 4));
}

FORCE_INLINE int32x4_t vmull_high_n_s16(int16x8_t a, int16_t b) {
  vint16m1_t a_high = __riscv_vslidedown_vx_i16m1(a, 4, 8);
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vx_i32m2(a_high, b, 4));
}

FORCE_INLINE int64x2_t vmull_high_n_s32(int32x4_t a, int32_t b) {
  vint32m1_t a_high = __riscv_vslidedown_vx_i32m1(a, 2, 4);
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vx_i64m2(a_high, b, 2));
}

FORCE_INLINE uint32x4_t vmull_high_n_u16(uint16x8_t a, uint16_t b) {
  vuint16m1_t a_high = __riscv_vslidedown_vx_u16m1(a, 4, 8);
  return __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwmulu_vx_u32m2(a_high, b, 4));
}

FORCE_INLINE uint64x2_t vmull_high_n_u32(uint32x4_t a, uint32_t b) {
  vuint32m1_t a_high = __riscv_vslidedown_vx_u32m1(a, 2, 4);
  return __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwmulu_vx_u64m2(a_high, b, 4));
}

FORCE_INLINE int32x4_t vqdmull_n_s16(int16x4_t a, int16_t b) {
  vint32m2_t ab_mul = __riscv_vwmul_vx_i32m2(a, b, 4);
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vsll_vx_i32m2(ab_mul, 1, 4));
}

FORCE_INLINE int64x2_t vqdmull_n_s32(int32x2_t a, int32_t b) {
  vint64m2_t ab_mul = __riscv_vwmul_vx_i64m2(a, b, 2);
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vsll_vx_i64m2(ab_mul, 1, 2));
}

FORCE_INLINE int32x4_t vqdmull_high_n_s16(int16x8_t a, int16_t b) {
  vint16m1_t a_high = __riscv_vslidedown_vx_i16m1(a, 4, 8);
  vint32m2_t ab_mul = __riscv_vwmul_vx_i32m2(a_high, b, 4);
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vsll_vx_i32m2(ab_mul, 1, 4));
}

FORCE_INLINE int64x2_t vqdmull_high_n_s32(int32x4_t a, int32_t b) {
  vint32m1_t a_high = __riscv_vslidedown_vx_i32m1(a, 2, 4);
  vint64m2_t ab_mul = __riscv_vwmul_vx_i64m2(a_high, b, 2);
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vsll_vx_i64m2(ab_mul, 1, 2));
}

FORCE_INLINE int16x8_t vqdmulhq_n_s16(int16x8_t a, int16_t b) {
  vint16m1_t b_dup = vdupq_n_s16(b);
  vint32m2_t ab_mul = __riscv_vwmul_vv_i32m2(a, b_dup, 8);
  vint32m2_t ab_mulx2 = __riscv_vmul_vx_i32m2(ab_mul, 2, 8);
  return __riscv_vnsra_wx_i16m1(ab_mulx2, 16, 8);
}

FORCE_INLINE int32x4_t vqdmulhq_n_s32(int32x4_t a, int32_t b) {
  vint32m1_t b_dup = vdupq_n_s32(b);
  vint64m2_t ab_mul = __riscv_vwmul_vv_i64m2(a, b_dup, 4);
  vint64m2_t ab_mulx2 = __riscv_vmul_vx_i64m2(ab_mul, 2, 4);
  return __riscv_vnsra_wx_i32m1(ab_mulx2, 32, 4);
}

FORCE_INLINE int16x4_t vqdmulh_n_s16(int16x4_t a, int16_t b) {
  vint16m1_t b_dup = vdup_n_s16(b);
  vint32m2_t ab_mul = __riscv_vwmul_vv_i32m2(a, b_dup, 4);
  vint32m2_t ab_mulx2 = __riscv_vmul_vx_i32m2(ab_mul, 2, 4);
  return __riscv_vnsra_wx_i16m1(ab_mulx2, 16, 4);
}

FORCE_INLINE int32x2_t vqdmulh_n_s32(int32x2_t a, int32_t b) {
  vint32m1_t b_dup = vdup_n_s32(b);
  vint64m2_t ab_mul = __riscv_vwmul_vv_i64m2(a, b_dup, 2);
  vint64m2_t ab_mulx2 = __riscv_vmul_vx_i64m2(ab_mul, 2, 2);
  return __riscv_vnsra_wx_i32m1(ab_mulx2, 32, 2);
}

FORCE_INLINE int16x8_t vqrdmulhq_n_s16(int16x8_t a, int16_t b) {
  vint16m1_t b_dup = vdupq_n_s16(b);
  vint32m2_t ab_mul = __riscv_vwmul_vv_i32m2(a, b_dup, 8);
  vint32m2_t ab_mulx2 = __riscv_vmul_vx_i32m2(ab_mul, 2, 8);
  return __riscv_vnclip_wx_i16m1(ab_mulx2, 16, __RISCV_VXRM_RNU, 8);
}

FORCE_INLINE int32x4_t vqrdmulhq_n_s32(int32x4_t a, int32_t b) {
  vint32m1_t b_dup = vdupq_n_s32(b);
  vint64m2_t ab_mul = __riscv_vwmul_vv_i64m2(a, b_dup, 4);
  vint64m2_t ab_mulx2 = __riscv_vmul_vx_i64m2(ab_mul, 2, 4);
  return __riscv_vnclip_wx_i32m1(ab_mulx2, 32, __RISCV_VXRM_RNU, 4);
}

FORCE_INLINE int16x4_t vqrdmulh_n_s16(int16x4_t a, int16_t b) {
  vint16m1_t b_dup = vdup_n_s16(b);
  vint32m2_t ab_mul = __riscv_vwmul_vv_i32m2(a, b_dup, 4);
  vint32m2_t ab_mulx2 = __riscv_vmul_vx_i32m2(ab_mul, 2, 4);
  return __riscv_vnclip_wx_i16m1(ab_mulx2, 16, __RISCV_VXRM_RNU, 4);
}

FORCE_INLINE int32x2_t vqrdmulh_n_s32(int32x2_t a, int32_t b) {
  vint32m1_t b_dup = vdup_n_s32(b);
  vint64m2_t ab_mul = __riscv_vwmul_vv_i64m2(a, b_dup, 2);
  vint64m2_t ab_mulx2 = __riscv_vmul_vx_i64m2(ab_mul, 2, 2);
  return __riscv_vnclip_wx_i32m1(ab_mulx2, 32, __RISCV_VXRM_RNU, 2);
}

FORCE_INLINE int16x4_t vmla_n_s16(int16x4_t a, int16x4_t b, int16_t c) { return __riscv_vmacc_vx_i16m1(a, c, b, 4); }

FORCE_INLINE int32x2_t vmla_n_s32(int32x2_t a, int32x2_t b, int32_t c) { return __riscv_vmacc_vx_i32m1(a, c, b, 2); }

FORCE_INLINE float32x2_t vmla_n_f32(float32x2_t a, float32x2_t b, float32_t c) {
  return __riscv_vfmacc_vf_f32m1(a, c, b, 2);
}

FORCE_INLINE uint16x4_t vmla_n_u16(uint16x4_t a, uint16x4_t b, uint16_t c) {
  return __riscv_vmacc_vx_u16m1(a, c, b, 4);
}

FORCE_INLINE uint32x2_t vmla_n_u32(uint32x2_t a, uint32x2_t b, uint32_t c) {
  return __riscv_vmacc_vx_u32m1(a, c, b, 2);
}

FORCE_INLINE int16x8_t vmlaq_n_s16(int16x8_t a, int16x8_t b, int16_t c) { return __riscv_vmacc_vx_i16m1(a, c, b, 8); }

FORCE_INLINE int32x4_t vmlaq_n_s32(int32x4_t a, int32x4_t b, int32_t c) { return __riscv_vmacc_vx_i32m1(a, c, b, 4); }

FORCE_INLINE float32x4_t vmlaq_n_f32(float32x4_t a, float32x4_t b, float32_t c) {
  return __riscv_vfmacc_vf_f32m1(a, c, b, 4);
}

FORCE_INLINE uint16x8_t vmlaq_n_u16(uint16x8_t a, uint16x8_t b, uint16_t c) {
  return __riscv_vmacc_vx_u16m1(a, c, b, 8);
}

FORCE_INLINE uint32x4_t vmlaq_n_u32(uint32x4_t a, uint32x4_t b, uint32_t c) {
  return __riscv_vmacc_vx_u32m1(a, c, b, 4);
}

FORCE_INLINE int32x4_t vmlal_n_s16(int32x4_t a, int16x4_t b, int16_t c) {
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmacc_vx_i32m2(__riscv_vlmul_ext_v_i32m1_i32m2(a), c, b, 4));
}

FORCE_INLINE int64x2_t vmlal_n_s32(int64x2_t a, int32x2_t b, int32_t c) {
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmacc_vx_i64m2(__riscv_vlmul_ext_v_i64m1_i64m2(a), c, b, 2));
}

FORCE_INLINE uint32x4_t vmlal_n_u16(uint32x4_t a, uint16x4_t b, uint16_t c) {
  return __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwmaccu_vx_u32m2(__riscv_vlmul_ext_v_u32m1_u32m2(a), c, b, 4));
}

FORCE_INLINE uint64x2_t vmlal_n_u32(uint64x2_t a, uint32x2_t b, uint32_t c) {
  return __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwmaccu_vx_u64m2(__riscv_vlmul_ext_v_u64m1_u64m2(a), c, b, 2));
}

FORCE_INLINE int32x4_t vmlal_high_n_s16(int32x4_t a, int16x8_t b, int16_t c) {
  vint16m1_t b_high = __riscv_vslidedown_vx_i16m1(b, 4, 8);
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmacc_vx_i32m2(__riscv_vlmul_ext_v_i32m1_i32m2(a), c, b_high, 4));
}

FORCE_INLINE int64x2_t vmlal_high_n_s32(int64x2_t a, int32x4_t b, int32_t c) {
  vint32m1_t b_high = __riscv_vslidedown_vx_i32m1(b, 2, 4);
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmacc_vx_i64m2(__riscv_vlmul_ext_v_i64m1_i64m2(a), c, b_high, 2));
}

FORCE_INLINE uint32x4_t vmlal_high_n_u16(uint32x4_t a, uint16x8_t b, uint16_t c) {
  vuint16m1_t b_high = __riscv_vslidedown_vx_u16m1(b, 4, 8);
  return __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwmaccu_vx_u32m2(__riscv_vlmul_ext_v_u32m1_u32m2(a), c, b_high, 4));
}

FORCE_INLINE uint64x2_t vmlal_high_n_u32(uint64x2_t a, uint32x4_t b, uint32_t c) {
  vuint32m1_t b_high = __riscv_vslidedown_vx_u32m1(b, 2, 4);
  return __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwmaccu_vx_u64m2(__riscv_vlmul_ext_v_u64m1_u64m2(a), c, b_high, 2));
}

FORCE_INLINE int32x4_t vqdmlal_n_s16(int32x4_t a, int16x4_t b, int16_t c) {
  vint16m1_t c_dup = vdup_n_s16(c);
  vint32m1_t bc_mul = __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vv_i32m2(b, c_dup, 4));
  vint32m1_t bc_mulx2 = __riscv_vmul_vx_i32m1(bc_mul, 2, 4);
  return __riscv_vadd_vv_i32m1(a, bc_mulx2, 4);
}

FORCE_INLINE int64x2_t vqdmlal_n_s32(int64x2_t a, int32x2_t b, int32_t c) {
  vint32m1_t c_dup = vdup_n_s32(c);
  vint64m1_t bc_mul = __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vv_i64m2(b, c_dup, 2));
  vint64m1_t bc_mulx2 = __riscv_vmul_vx_i64m1(bc_mul, 2, 2);
  return __riscv_vadd_vv_i64m1(a, bc_mulx2, 2);
}

FORCE_INLINE int32x4_t vqdmlal_high_n_s16(int32x4_t a, int16x8_t b, int16_t c) {
  vint16m1_t c_dup = vdup_n_s16(c);
  vint16m1_t b_high = __riscv_vslidedown_vx_i16m1(b, 4, 8);
  vint32m1_t bc_mul = __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vv_i32m2(b_high, c_dup, 4));
  vint32m1_t bc_mulx2 = __riscv_vmul_vx_i32m1(bc_mul, 2, 4);
  return __riscv_vadd_vv_i32m1(a, bc_mulx2, 4);
}

FORCE_INLINE int64x2_t vqdmlal_high_n_s32(int64x2_t a, int32x4_t b, int32_t c) {
  vint32m1_t c_dup = vdup_n_s32(c);
  vint32m1_t b_high = __riscv_vslidedown_vx_i32m1(b, 2, 4);
  vint64m1_t bc_mul = __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vv_i64m2(b_high, c_dup, 2));
  vint64m1_t bc_mulx2 = __riscv_vmul_vx_i64m1(bc_mul, 2, 2);
  return __riscv_vadd_vv_i64m1(a, bc_mulx2, 2);
}

FORCE_INLINE int16x4_t vmls_n_s16(int16x4_t a, int16x4_t b, int16_t c) { return __riscv_vnmsac_vx_i16m1(a, c, b, 4); }

FORCE_INLINE int32x2_t vmls_n_s32(int32x2_t a, int32x2_t b, int32_t c) { return __riscv_vnmsac_vx_i32m1(a, c, b, 2); }

FORCE_INLINE float32x2_t vmls_n_f32(float32x2_t a, float32x2_t b, float32_t c) {
  return __riscv_vfnmsac_vf_f32m1(a, c, b, 2);
}

FORCE_INLINE uint16x4_t vmls_n_u16(uint16x4_t a, uint16x4_t b, uint16_t c) {
  return __riscv_vnmsac_vx_u16m1(a, c, b, 4);
}

FORCE_INLINE uint32x2_t vmls_n_u32(uint32x2_t a, uint32x2_t b, uint32_t c) {
  return __riscv_vnmsac_vx_u32m1(a, c, b, 2);
}

FORCE_INLINE int16x8_t vmlsq_n_s16(int16x8_t a, int16x8_t b, int16_t c) { return __riscv_vnmsac_vx_i16m1(a, c, b, 8); }

FORCE_INLINE int32x4_t vmlsq_n_s32(int32x4_t a, int32x4_t b, int32_t c) { return __riscv_vnmsac_vx_i32m1(a, c, b, 4); }

FORCE_INLINE float32x4_t vmlsq_n_f32(float32x4_t a, float32x4_t b, float32_t c) {
  return __riscv_vfnmsac_vf_f32m1(a, c, b, 4);
}

FORCE_INLINE uint16x8_t vmlsq_n_u16(uint16x8_t a, uint16x8_t b, uint16_t c) {
  return __riscv_vnmsac_vx_u16m1(a, c, b, 8);
}

FORCE_INLINE uint32x4_t vmlsq_n_u32(uint32x4_t a, uint32x4_t b, uint32_t c) {
  return __riscv_vnmsac_vx_u32m1(a, c, b, 4);
}

FORCE_INLINE int32x4_t vmlsl_n_s16(int32x4_t a, int16x4_t b, int16_t c) {
  return __riscv_vsub_vv_i32m1(a, __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vx_i32m2(b, c, 4)), 4);
}

FORCE_INLINE int64x2_t vmlsl_n_s32(int64x2_t a, int32x2_t b, int32_t c) {
  return __riscv_vsub_vv_i64m1(a, __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vx_i64m2(b, c, 2)), 2);
}

FORCE_INLINE uint32x4_t vmlsl_n_u16(uint32x4_t a, uint16x4_t b, uint16_t c) {
  return __riscv_vsub_vv_u32m1(a, __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwmulu_vx_u32m2(b, c, 4)), 4);
}

FORCE_INLINE uint64x2_t vmlsl_n_u32(uint64x2_t a, uint32x2_t b, uint32_t c) {
  return __riscv_vsub_vv_u64m1(a, __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwmulu_vx_u64m2(b, c, 2)), 2);
}

FORCE_INLINE int32x4_t vmlsl_high_n_s16(int32x4_t a, int16x8_t b, int16_t c) {
  vint16m1_t b_high = __riscv_vslidedown_vx_i16m1(b, 4, 8);
  return __riscv_vsub_vv_i32m1(a, __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vx_i32m2(b_high, c, 4)), 4);
}

FORCE_INLINE int64x2_t vmlsl_high_n_s32(int64x2_t a, int32x4_t b, int32_t c) {
  vint32m1_t b_high = __riscv_vslidedown_vx_i32m1(b, 2, 4);
  return __riscv_vsub_vv_i64m1(a, __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vx_i64m2(b_high, c, 2)), 2);
}

FORCE_INLINE uint32x4_t vmlsl_high_n_u16(uint32x4_t a, uint16x8_t b, uint16_t c) {
  vuint16m1_t b_high = __riscv_vslidedown_vx_u16m1(b, 4, 8);
  return __riscv_vsub_vv_u32m1(a, __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwmulu_vx_u32m2(b_high, c, 4)), 4);
}

FORCE_INLINE uint64x2_t vmlsl_high_n_u32(uint64x2_t a, uint32x4_t b, uint32_t c) {
  vuint32m1_t b_high = __riscv_vslidedown_vx_u32m1(b, 2, 4);
  return __riscv_vsub_vv_u64m1(a, __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwmulu_vx_u64m2(b_high, c, 2)), 2);
}

FORCE_INLINE int32x4_t vqdmlsl_n_s16(int32x4_t a, int16x4_t b, int16_t c) {
  vint16m1_t c_dup = vdup_n_s16(c);
  vint32m1_t bc_mul = __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vv_i32m2(b, c_dup, 4));
  vint32m1_t bc_mulx2 = __riscv_vsll_vx_i32m1(bc_mul, 1, 4);
  return __riscv_vsub_vv_i32m1(a, bc_mulx2, 4);
}

FORCE_INLINE int64x2_t vqdmlsl_n_s32(int64x2_t a, int32x2_t b, int32_t c) {
  vint32m1_t c_dup = vdup_n_s32(c);
  vint64m1_t bc_mul = __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vv_i64m2(b, c_dup, 2));
  vint64m1_t bc_mulx2 = __riscv_vsll_vx_i64m1(bc_mul, 1, 2);
  return __riscv_vsub_vv_i64m1(a, bc_mulx2, 2);
}

FORCE_INLINE int32x4_t vqdmlsl_high_n_s16(int32x4_t a, int16x8_t b, int16_t c) {
  vint16m1_t c_dup = vdup_n_s16(c);
  vint16m1_t b_high = __riscv_vslidedown_vx_i16m1(b, 4, 8);
  vint32m1_t bc_mul = __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vv_i32m2(b_high, c_dup, 4));
  vint32m1_t bc_mulx2 = __riscv_vsll_vx_i32m1(bc_mul, 1, 4);
  return __riscv_vsub_vv_i32m1(a, bc_mulx2, 4);
}

FORCE_INLINE int64x2_t vqdmlsl_high_n_s32(int64x2_t a, int32x4_t b, int32_t c) {
  vint32m1_t c_dup = vdup_n_s32(c);
  vint32m1_t b_high = __riscv_vslidedown_vx_i32m1(b, 2, 4);
  vint64m1_t bc_mul = __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vv_i64m2(b_high, c_dup, 2));
  vint64m1_t bc_mulx2 = __riscv_vsll_vx_i64m1(bc_mul, 1, 2);
  return __riscv_vsub_vv_i64m1(a, bc_mulx2, 2);
}

FORCE_INLINE int8x8_t vext_s8(int8x8_t a, int8x8_t b, const int c) {
  vint8m1_t a_slidedown = __riscv_vslidedown_vx_i8m1(a, c, 8);
  return __riscv_vslideup_vx_i8m1(a_slidedown, b, 8 - c, 8);
}

FORCE_INLINE int16x4_t vext_s16(int16x4_t a, int16x4_t b, const int c) {
  vint16m1_t a_slidedown = __riscv_vslidedown_vx_i16m1(a, c, 4);
  return __riscv_vslideup_vx_i16m1(a_slidedown, b, 4 - c, 4);
}

FORCE_INLINE int32x2_t vext_s32(int32x2_t a, int32x2_t b, const int c) {
  vint32m1_t a_slidedown = __riscv_vslidedown_vx_i32m1(a, c, 2);
  return __riscv_vslideup_vx_i32m1(a_slidedown, b, 2 - c, 2);
}

FORCE_INLINE int64x1_t vext_s64(int64x1_t a, int64x1_t b, const int c) {
  vint64m1_t a_slidedown = __riscv_vslidedown_vx_i64m1(a, c, 1);
  return __riscv_vslideup_vx_i64m1(a_slidedown, b, 1 - c, 1);
}

FORCE_INLINE float32x2_t vext_f32(float32x2_t a, float32x2_t b, const int c) {
  vfloat32m1_t a_slidedown = __riscv_vslidedown_vx_f32m1(a, c, 2);
  return __riscv_vslideup_vx_f32m1(a_slidedown, b, 2 - c, 2);
}

FORCE_INLINE uint8x8_t vext_u8(uint8x8_t a, uint8x8_t b, const int c) {
  vuint8m1_t a_slidedown = __riscv_vslidedown_vx_u8m1(a, c, 8);
  return __riscv_vslideup_vx_u8m1(a_slidedown, b, 8 - c, 8);
}

FORCE_INLINE uint16x4_t vext_u16(uint16x4_t a, uint16x4_t b, const int c) {
  vuint16m1_t a_slidedown = __riscv_vslidedown_vx_u16m1(a, c, 4);
  return __riscv_vslideup_vx_u16m1(a_slidedown, b, 4 - c, 4);
}

FORCE_INLINE uint32x2_t vext_u32(uint32x2_t a, uint32x2_t b, const int c) {
  vuint32m1_t a_slidedown = __riscv_vslidedown_vx_u32m1(a, c, 2);
  return __riscv_vslideup_vx_u32m1(a_slidedown, b, 2 - c, 2);
}

FORCE_INLINE uint64x1_t vext_u64(uint64x1_t a, uint64x1_t b, const int c) {
  vuint64m1_t a_slidedown = __riscv_vslidedown_vx_u64m1(a, c, 1);
  return __riscv_vslideup_vx_u64m1(a_slidedown, b, 1 - c, 1);
}

FORCE_INLINE int8x16_t vextq_s8(int8x16_t a, int8x16_t b, const int c) {
  vint8m1_t a_slidedown = __riscv_vslidedown_vx_i8m1(a, c, 16);
  return __riscv_vslideup_vx_i8m1(a_slidedown, b, 16 - c, 16);
}

FORCE_INLINE int16x8_t vextq_s16(int16x8_t a, int16x8_t b, const int c) {
  vint16m1_t a_slidedown = __riscv_vslidedown_vx_i16m1(a, c, 8);
  return __riscv_vslideup_vx_i16m1(a_slidedown, b, 8 - c, 8);
}

FORCE_INLINE int32x4_t vextq_s32(int32x4_t a, int32x4_t b, const int c) {
  vint32m1_t a_slidedown = __riscv_vslidedown_vx_i32m1(a, c, 4);
  return __riscv_vslideup_vx_i32m1(a_slidedown, b, 4 - c, 4);
}

FORCE_INLINE int64x2_t vextq_s64(int64x2_t a, int64x2_t b, const int c) {
  vint64m1_t a_slidedown = __riscv_vslidedown_vx_i64m1(a, c, 2);
  return __riscv_vslideup_vx_i64m1(a_slidedown, b, 2 - c, 2);
}

FORCE_INLINE float32x4_t vextq_f32(float32x4_t a, float32x4_t b, const int c) {
  vfloat32m1_t a_slidedown = __riscv_vslidedown_vx_f32m1(a, c, 4);
  return __riscv_vslideup_vx_f32m1(a_slidedown, b, 4 - c, 4);
}

FORCE_INLINE float64x1_t vext_f64(float64x1_t a, float64x1_t b, const int c) {
  vfloat64m1_t a_slidedown = __riscv_vslidedown_vx_f64m1(a, c, 1);
  return __riscv_vslideup_vx_f64m1(a_slidedown, b, 1 - c, 1);
}

FORCE_INLINE float64x2_t vextq_f64(float64x2_t a, float64x2_t b, const int c) {
  vfloat64m1_t a_slidedown = __riscv_vslidedown_vx_f64m1(a, c, 2);
  return __riscv_vslideup_vx_f64m1(a_slidedown, b, 2 - c, 2);
}

// FORCE_INLINE poly8x8_t vext_p8(poly8x8_t a, poly8x8_t b, const int n);

// FORCE_INLINE poly8x16_t vextq_p8(poly8x16_t a, poly8x16_t b, const int n);

// FORCE_INLINE poly16x4_t vext_p16(poly16x4_t a, poly16x4_t b, const int n);

// FORCE_INLINE poly16x8_t vextq_p16(poly16x8_t a, poly16x8_t b, const int n);

FORCE_INLINE uint8x16_t vextq_u8(uint8x16_t a, uint8x16_t b, const int c) {
  vuint8m1_t a_slidedown = __riscv_vslidedown_vx_u8m1(a, c, 16);
  return __riscv_vslideup_vx_u8m1(a_slidedown, b, 16 - c, 16);
}

FORCE_INLINE uint16x8_t vextq_u16(uint16x8_t a, uint16x8_t b, const int c) {
  vuint16m1_t a_slidedown = __riscv_vslidedown_vx_u16m1(a, c, 8);
  return __riscv_vslideup_vx_u16m1(a_slidedown, b, 8 - c, 8);
}

FORCE_INLINE uint32x4_t vextq_u32(uint32x4_t a, uint32x4_t b, const int c) {
  vuint32m1_t a_slidedown = __riscv_vslidedown_vx_u32m1(a, c, 4);
  return __riscv_vslideup_vx_u32m1(a_slidedown, b, 4 - c, 4);
}

FORCE_INLINE uint64x2_t vextq_u64(uint64x2_t a, uint64x2_t b, const int c) {
  vuint64m1_t a_slidedown = __riscv_vslidedown_vx_u64m1(a, c, 2);
  return __riscv_vslideup_vx_u64m1(a_slidedown, b, 2 - c, 2);
}

// FORCE_INLINE poly64x1_t vext_p64(poly64x1_t a, poly64x1_t b, const int n);

// FORCE_INLINE poly64x2_t vextq_p64(poly64x2_t a, poly64x2_t b, const int n);

FORCE_INLINE int8x8_t vrev64_s8(int8x8_t a) {
  // generate element index
  vuint8m1_t vid = __riscv_vid_v_u8m1(8);
  // make the indexes reversed
  vuint8m1_t idxs = __riscv_vsub_vv_u8m1(vdup_n_u8(7), vid, 8);
  return __riscv_vrgather_vv_i8m1(a, idxs, 8);
}

FORCE_INLINE int16x4_t vrev64_s16(int16x4_t a) {
  vuint16m1_t vid = __riscv_vid_v_u16m1(4);
  vuint16m1_t idxs = __riscv_vsub_vv_u16m1(vdup_n_u16(3), vid, 4);
  return __riscv_vrgather_vv_i16m1(a, idxs, 4);
}

FORCE_INLINE int32x2_t vrev64_s32(int32x2_t a) {
  vuint32m1_t vid = __riscv_vid_v_u32m1(2);
  vuint32m1_t idxs = __riscv_vsub_vv_u32m1(vdup_n_u32(1), vid, 2);
  return __riscv_vrgather_vv_i32m1(a, idxs, 2);
}

FORCE_INLINE float32x2_t vrev64_f32(float32x2_t a) {
  vuint32m1_t vid = __riscv_vid_v_u32m1(2);
  vuint32m1_t idxs = __riscv_vsub_vv_u32m1(vdup_n_u32(1), vid, 2);
  return __riscv_vrgather_vv_f32m1(a, idxs, 2);
}

FORCE_INLINE uint8x8_t vrev64_u8(uint8x8_t a) {
  vuint8m1_t vid = __riscv_vid_v_u8m1(8);
  vuint8m1_t idxs = __riscv_vsub_vv_u8m1(vdup_n_u8(7), vid, 8);
  return __riscv_vrgather_vv_u8m1(a, idxs, 8);
}

FORCE_INLINE uint16x4_t vrev64_u16(uint16x4_t a) {
  vuint16m1_t vid = __riscv_vid_v_u16m1(4);
  vuint16m1_t idxs = __riscv_vsub_vv_u16m1(vdup_n_u16(3), vid, 4);
  return __riscv_vrgather_vv_u16m1(a, idxs, 4);
}

FORCE_INLINE uint32x2_t vrev64_u32(uint32x2_t a) {
  vuint32m1_t vid = __riscv_vid_v_u32m1(2);
  vuint32m1_t idxs = __riscv_vsub_vv_u32m1(vdup_n_u32(1), vid, 2);
  return __riscv_vrgather_vv_u32m1(a, idxs, 2);
}

FORCE_INLINE int8x16_t vrev64q_s8(int8x16_t a) {
  // FIXME improve the following intrinsics
  vuint8m1_t vid = __riscv_vid_v_u8m1(8);
  vuint8m1_t vid_slideup = __riscv_vslideup_vx_u8m1(vid, vid, 8, 16);
  vuint8m1_t sub = __riscv_vslideup_vx_u8m1(vdupq_n_u8(7), vdupq_n_u8(7 + 8), 8, 16);
  vuint8m1_t idxs = __riscv_vsub_vv_u8m1(sub, vid_slideup, 16);
  return __riscv_vrgather_vv_i8m1(a, idxs, 16);
}

FORCE_INLINE int16x8_t vrev64q_s16(int16x8_t a) {
  vuint16m1_t vid = __riscv_vid_v_u16m1(4);
  vuint16m1_t vid_slideup = __riscv_vslideup_vx_u16m1(vid, vid, 4, 8);
  vuint16m1_t sub = __riscv_vslideup_vx_u16m1(vdupq_n_u16(3), vdupq_n_u16(3 + 4), 4, 8);
  vuint16m1_t idxs = __riscv_vsub_vv_u16m1(sub, vid_slideup, 8);
  return __riscv_vrgather_vv_i16m1(a, idxs, 8);
}

FORCE_INLINE int32x4_t vrev64q_s32(int32x4_t a) {
  vuint32m1_t vid = __riscv_vid_v_u32m1(2);
  vuint32m1_t vid_slideup = __riscv_vslideup_vx_u32m1(vid, vid, 2, 4);
  vuint32m1_t sub = __riscv_vslideup_vx_u32m1(vdupq_n_u32(1), vdupq_n_u32(1 + 2), 2, 4);
  vuint32m1_t idxs = __riscv_vsub_vv_u32m1(sub, vid_slideup, 4);
  return __riscv_vrgather_vv_i32m1(a, idxs, 4);
}

FORCE_INLINE float32x4_t vrev64q_f32(float32x4_t a) {
  vuint32m1_t vid = __riscv_vid_v_u32m1(2);
  vuint32m1_t vid_slideup = __riscv_vslideup_vx_u32m1(vid, vid, 2, 4);
  vuint32m1_t sub = __riscv_vslideup_vx_u32m1(vdupq_n_u32(1), vdupq_n_u32(1 + 2), 2, 4);
  vuint32m1_t idxs = __riscv_vsub_vv_u32m1(sub, vid_slideup, 4);
  return __riscv_vrgather_vv_f32m1(a, idxs, 4);
}

// FORCE_INLINE poly8x8_t vrev64_p8(poly8x8_t vec);

// FORCE_INLINE poly8x16_t vrev64q_p8(poly8x16_t vec);

// FORCE_INLINE poly16x4_t vrev64_p16(poly16x4_t vec);

// FORCE_INLINE poly16x8_t vrev64q_p16(poly16x8_t vec);

FORCE_INLINE uint8x16_t vrev64q_u8(uint8x16_t a) {
  vuint8m1_t vid = __riscv_vid_v_u8m1(8);
  vuint8m1_t vid_slideup = __riscv_vslideup_vx_u8m1(vid, vid, 8, 16);
  vuint8m1_t sub = __riscv_vslideup_vx_u8m1(vdupq_n_u8(7), vdupq_n_u8(7 + 8), 8, 16);
  vuint8m1_t idxs = __riscv_vsub_vv_u8m1(sub, vid_slideup, 16);
  return __riscv_vrgather_vv_u8m1(a, idxs, 16);
}

FORCE_INLINE uint16x8_t vrev64q_u16(uint16x8_t a) {
  vuint16m1_t vid = __riscv_vid_v_u16m1(4);
  vuint16m1_t vid_slideup = __riscv_vslideup_vx_u16m1(vid, vid, 4, 8);
  vuint16m1_t sub = __riscv_vslideup_vx_u16m1(vdupq_n_u16(3), vdupq_n_u16(3 + 4), 4, 8);
  vuint16m1_t idxs = __riscv_vsub_vv_u16m1(sub, vid_slideup, 8);
  return __riscv_vrgather_vv_u16m1(a, idxs, 8);
}

FORCE_INLINE uint32x4_t vrev64q_u32(uint32x4_t a) {
  vuint32m1_t vid = __riscv_vid_v_u32m1(2);
  vuint32m1_t vid_slideup = __riscv_vslideup_vx_u32m1(vid, vid, 2, 4);
  vuint32m1_t sub = __riscv_vslideup_vx_u32m1(vdupq_n_u32(1), vdupq_n_u32(1 + 2), 2, 4);
  vuint32m1_t idxs = __riscv_vsub_vv_u32m1(sub, vid_slideup, 4);
  return __riscv_vrgather_vv_u32m1(a, idxs, 4);
}

FORCE_INLINE int8x8_t vrev32_s8(int8x8_t a) {
  vuint8m1_t vid = __riscv_vid_v_u8m1(4);
  vuint8m1_t vid_slideup = __riscv_vslideup_vx_u8m1(vid, vid, 4, 8);
  vuint8m1_t sub = __riscv_vslideup_vx_u8m1(vdup_n_u8(3), vdup_n_u8(3 + 4), 4, 8);
  vuint8m1_t idxs = __riscv_vsub_vv_u8m1(sub, vid_slideup, 8);
  return __riscv_vrgather_vv_i8m1(a, idxs, 8);
}

FORCE_INLINE int16x4_t vrev32_s16(int16x4_t a) {
  vuint16m1_t vid = __riscv_vid_v_u16m1(2);
  vuint16m1_t vid_slideup = __riscv_vslideup_vx_u16m1(vid, vid, 2, 4);
  vuint16m1_t sub = __riscv_vslideup_vx_u16m1(vdup_n_u16(1), vdup_n_u16(1 + 2), 2, 4);
  vuint16m1_t idxs = __riscv_vsub_vv_u16m1(sub, vid_slideup, 4);
  return __riscv_vrgather_vv_i16m1(a, idxs, 4);
}

FORCE_INLINE uint8x8_t vrev32_u8(uint8x8_t a) {
  vuint8m1_t vid = __riscv_vid_v_u8m1(4);
  vuint8m1_t vid_slideup = __riscv_vslideup_vx_u8m1(vid, vid, 4, 8);
  vuint8m1_t sub = __riscv_vslideup_vx_u8m1(vdup_n_u8(3), vdup_n_u8(3 + 4), 4, 8);
  vuint8m1_t idxs = __riscv_vsub_vv_u8m1(sub, vid_slideup, 8);
  return __riscv_vrgather_vv_u8m1(a, idxs, 8);
}

FORCE_INLINE uint16x4_t vrev32_u16(uint16x4_t a) {
  vuint16m1_t vid = __riscv_vid_v_u16m1(2);
  vuint16m1_t vid_slideup = __riscv_vslideup_vx_u16m1(vid, vid, 2, 4);
  vuint16m1_t sub = __riscv_vslideup_vx_u16m1(vdup_n_u16(1), vdup_n_u16(1 + 2), 2, 4);
  vuint16m1_t idxs = __riscv_vsub_vv_u16m1(sub, vid_slideup, 4);
  return __riscv_vrgather_vv_u16m1(a, idxs, 4);
}

FORCE_INLINE int8x16_t vrev32q_s8(int8x16_t a) {
  // uint8 vid[] = {0, 1, 2, 3} is '50462976' in uint32
  vuint8m1_t vid_inside_u32s = __riscv_vreinterpret_v_u32m1_u8m1(vdupq_n_u32(50462976));
  vuint32m1_t accumulator = __riscv_vreinterpret_v_u8m1_u32m1(vdupq_n_u8(3));
  vuint32m1_t lane_elt_num = __riscv_vreinterpret_v_u8m1_u32m1(vdupq_n_u8(4));
  vuint32m1_t lane_idx = __riscv_vid_v_u32m1(4);
  // 'sub' should be {3, 3, 3, 3, 3+4*1, 3+4*1, 3+4*1, 3+4*1, 3+4*2, 3+4*2, 3+4*2, 3+4*2, 3+4*3, 3+4*3, 3+4*3, 3+4*3}
  vuint8m1_t sub = __riscv_vreinterpret_v_u32m1_u8m1(__riscv_vmacc_vv_u32m1(accumulator, lane_elt_num, lane_idx, 4));
  vuint8m1_t idxs = __riscv_vsub_vv_u8m1(sub, vid_inside_u32s, 16);
  return __riscv_vrgather_vv_i8m1(a, idxs, 16);
}

FORCE_INLINE int16x8_t vrev32q_s16(int16x8_t a) {
  // uint16 vid[] = {0, 1} is '65536' in uint32
  vuint16m1_t vid_inside_u32s = __riscv_vreinterpret_v_u32m1_u16m1(vdupq_n_u32(65536));
  vuint32m1_t accumulator = __riscv_vreinterpret_v_u16m1_u32m1(vdupq_n_u16(1));
  vuint32m1_t lane_elt_num = __riscv_vreinterpret_v_u16m1_u32m1(vdupq_n_u16(2));
  vuint32m1_t lane_idx = __riscv_vid_v_u32m1(4);
  // 'sub' should be {1, 1, 1+2*1, 1+2*1, 1+2*2, 1+2*2, 1+2*3, 1+2*3}
  vuint16m1_t sub = __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vmacc_vv_u32m1(accumulator, lane_elt_num, lane_idx, 4));
  vuint16m1_t idxs = __riscv_vsub_vv_u16m1(sub, vid_inside_u32s, 8);
  return __riscv_vrgather_vv_i16m1(a, idxs, 8);
}

FORCE_INLINE uint8x16_t vrev32q_u8(uint8x16_t a) {
  // uint8 vid[] = {0, 1, 2, 3} is '50462976' in uint32
  vuint8m1_t vid_inside_u32s = __riscv_vreinterpret_v_u32m1_u8m1(vdupq_n_u32(50462976));
  vuint32m1_t accumulator = __riscv_vreinterpret_v_u8m1_u32m1(vdupq_n_u8(3));
  vuint32m1_t lane_elt_num = __riscv_vreinterpret_v_u8m1_u32m1(vdupq_n_u8(4));
  vuint32m1_t lane_idx = __riscv_vid_v_u32m1(4);
  // 'sub' should be {3, 3, 3, 3, 3+4*1, 3+4*1, 3+4*1, 3+4*1, 3+4*2, 3+4*2, 3+4*2, 3+4*2, 3+4*3, 3+4*3, 3+4*3, 3+4*3}
  vuint8m1_t sub = __riscv_vreinterpret_v_u32m1_u8m1(__riscv_vmacc_vv_u32m1(accumulator, lane_elt_num, lane_idx, 4));
  vuint8m1_t idxs = __riscv_vsub_vv_u8m1(sub, vid_inside_u32s, 16);
  return __riscv_vrgather_vv_u8m1(a, idxs, 16);
}

FORCE_INLINE uint16x8_t vrev32q_u16(uint16x8_t a) {
  // uint16 vid[] = {0, 1} is '65536' in uint32
  vuint16m1_t vid_inside_u32s = __riscv_vreinterpret_v_u32m1_u16m1(vdupq_n_u32(65536));
  vuint32m1_t accumulator = __riscv_vreinterpret_v_u16m1_u32m1(vdupq_n_u16(1));
  vuint32m1_t lane_elt_num = __riscv_vreinterpret_v_u16m1_u32m1(vdupq_n_u16(2));
  vuint32m1_t lane_idx = __riscv_vid_v_u32m1(4);
  // 'sub' should be {1, 1, 1+2*1, 1+2*1, 1+2*2, 1+2*2, 1+2*3, 1+2*3}
  vuint16m1_t sub = __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vmacc_vv_u32m1(accumulator, lane_elt_num, lane_idx, 4));
  vuint16m1_t idxs = __riscv_vsub_vv_u16m1(sub, vid_inside_u32s, 8);
  return __riscv_vrgather_vv_u16m1(a, idxs, 8);
}

// FORCE_INLINE poly8x8_t vrev32_p8(poly8x8_t vec);

// FORCE_INLINE poly8x16_t vrev32q_p8(poly8x16_t vec);

// FORCE_INLINE poly16x4_t vrev32_p16(poly16x4_t vec);

// FORCE_INLINE poly16x8_t vrev32q_p16(poly16x8_t vec);

FORCE_INLINE int8x8_t vrev16_s8(int8x8_t a) {
  vuint16m1_t a_u16 = __riscv_vreinterpret_v_u8m1_u16m1(__riscv_vreinterpret_v_i8m1_u8m1(a));
  vuint16m1_t low = __riscv_vsrl_vx_u16m1(a_u16, 8, 8);
  vuint16m1_t high = __riscv_vsll_vx_u16m1(a_u16, 8, 8);
  return __riscv_vreinterpret_v_u8m1_i8m1(__riscv_vreinterpret_v_u16m1_u8m1(__riscv_vor_vv_u16m1(low, high, 8)));
}

FORCE_INLINE uint8x8_t vrev16_u8(uint8x8_t a) {
  vuint16m1_t a_u16 = __riscv_vreinterpret_v_u8m1_u16m1(a);
  vuint16m1_t low = __riscv_vsrl_vx_u16m1(a_u16, 8, 8);
  vuint16m1_t high = __riscv_vsll_vx_u16m1(a_u16, 8, 8);
  return __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vor_vv_u16m1(low, high, 8));
}

FORCE_INLINE int8x16_t vrev16q_s8(int8x16_t a) {
  vuint16m1_t a_u16 = __riscv_vreinterpret_v_u8m1_u16m1(__riscv_vreinterpret_v_i8m1_u8m1(a));
  vuint16m1_t low = __riscv_vsrl_vx_u16m1(a_u16, 8, 16);
  vuint16m1_t high = __riscv_vsll_vx_u16m1(a_u16, 8, 16);
  return __riscv_vreinterpret_v_u8m1_i8m1(__riscv_vreinterpret_v_u16m1_u8m1(__riscv_vor_vv_u16m1(low, high, 16)));
}

FORCE_INLINE uint8x16_t vrev16q_u8(uint8x16_t a) {
  vuint16m1_t a_u16 = __riscv_vreinterpret_v_u8m1_u16m1(a);
  vuint16m1_t low = __riscv_vsrl_vx_u16m1(a_u16, 8, 16);
  vuint16m1_t high = __riscv_vsll_vx_u16m1(a_u16, 8, 16);
  return __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vor_vv_u16m1(low, high, 16));
}

// FORCE_INLINE poly8x8_t vrev16_p8(poly8x8_t vec);

// FORCE_INLINE poly8x16_t vrev16q_p8(poly8x16_t vec);

// FORCE_INLINE int8x8_t vzip1_s8(int8x8_t a, int8x8_t b);

// FORCE_INLINE int8x16_t vzip1q_s8(int8x16_t a, int8x16_t b);

// FORCE_INLINE int16x4_t vzip1_s16(int16x4_t a, int16x4_t b);

FORCE_INLINE int16x8_t vzip1q_s16(int16x8_t a, int16x8_t b) {
  vuint16m1_t a_u16 = __riscv_vreinterpret_v_i16m1_u16m1(a);
  vuint16m1_t b_u16 = __riscv_vreinterpret_v_i16m1_u16m1(b);
  vuint32m2_t ab_waddu = __riscv_vwaddu_vv_u32m2(a_u16, b_u16, 8);
  vuint32m2_t zip_u32 = __riscv_vwmaccu_vx_u32m2(ab_waddu, UINT16_MAX, b_u16, 8);
  vint16m2_t zip = __riscv_vreinterpret_v_i32m2_i16m2(__riscv_vreinterpret_v_u32m2_i32m2(zip_u32));
  return __riscv_vget_v_i16m2_i16m1(zip, 0);
}

// FORCE_INLINE int32x2_t vzip1_s32(int32x2_t a, int32x2_t b);

FORCE_INLINE int32x4_t vzip1q_s32(int32x4_t a, int32x4_t b) {
  vuint32m1_t a_u32 = __riscv_vreinterpret_v_i32m1_u32m1(a);
  vuint32m1_t b_u32 = __riscv_vreinterpret_v_i32m1_u32m1(b);
  vuint64m2_t ab_waddu = __riscv_vwaddu_vv_u64m2(a_u32, b_u32, 4);
  vuint64m2_t zip_u64 = __riscv_vwmaccu_vx_u64m2(ab_waddu, UINT32_MAX, b_u32, 4);
  vint32m2_t zip = __riscv_vreinterpret_v_i64m2_i32m2(__riscv_vreinterpret_v_u64m2_i64m2(zip_u64));
  return __riscv_vget_v_i32m2_i32m1(zip, 0);
}

FORCE_INLINE int64x2_t vzip1q_s64(int64x2_t a, int64x2_t b) { return __riscv_vslideup_vx_i64m1(a, b, 1, 2); }

// FORCE_INLINE uint8x8_t vzip1_u8(uint8x8_t a, uint8x8_t b);

// FORCE_INLINE uint8x16_t vzip1q_u8(uint8x16_t a, uint8x16_t b);

// FORCE_INLINE uint16x4_t vzip1_u16(uint16x4_t a, uint16x4_t b);

// FORCE_INLINE uint16x8_t vzip1q_u16(uint16x8_t a, uint16x8_t b);

// FORCE_INLINE uint32x2_t vzip1_u32(uint32x2_t a, uint32x2_t b);

// FORCE_INLINE uint32x4_t vzip1q_u32(uint32x4_t a, uint32x4_t b);

// FORCE_INLINE uint64x2_t vzip1q_u64(uint64x2_t a, uint64x2_t b);

// FORCE_INLINE poly64x2_t vzip1q_p64(poly64x2_t a, poly64x2_t b);

// FORCE_INLINE float32x2_t vzip1_f32(float32x2_t a, float32x2_t b);

// FORCE_INLINE float32x4_t vzip1q_f32(float32x4_t a, float32x4_t b);

// FORCE_INLINE float64x2_t vzip1q_f64(float64x2_t a, float64x2_t b);

// FORCE_INLINE poly8x8_t vzip1_p8(poly8x8_t a, poly8x8_t b);

// FORCE_INLINE poly8x16_t vzip1q_p8(poly8x16_t a, poly8x16_t b);

// FORCE_INLINE poly16x4_t vzip1_p16(poly16x4_t a, poly16x4_t b);

// FORCE_INLINE poly16x8_t vzip1q_p16(poly16x8_t a, poly16x8_t b);

// FORCE_INLINE int8x8_t vzip2_s8(int8x8_t a, int8x8_t b);

// FORCE_INLINE int8x16_t vzip2q_s8(int8x16_t a, int8x16_t b);

// FORCE_INLINE int16x4_t vzip2_s16(int16x4_t a, int16x4_t b);

// FORCE_INLINE int16x8_t vzip2q_s16(int16x8_t a, int16x8_t b);

// FORCE_INLINE int32x2_t vzip2_s32(int32x2_t a, int32x2_t b);

// FORCE_INLINE int32x4_t vzip2q_s32(int32x4_t a, int32x4_t b);

FORCE_INLINE int64x2_t vzip2q_s64(int64x2_t a, int64x2_t b) {
  return __riscv_vslide1down_vx_i64m1(a, __riscv_vmv_x_s_i64m1_i64(__riscv_vslidedown_vx_i64m1(b, 1, 2)), 2);
}

// FORCE_INLINE uint8x8_t vzip2_u8(uint8x8_t a, uint8x8_t b);

// FORCE_INLINE uint8x16_t vzip2q_u8(uint8x16_t a, uint8x16_t b);

// FORCE_INLINE uint16x4_t vzip2_u16(uint16x4_t a, uint16x4_t b);

// FORCE_INLINE uint16x8_t vzip2q_u16(uint16x8_t a, uint16x8_t b);

// FORCE_INLINE uint32x2_t vzip2_u32(uint32x2_t a, uint32x2_t b);

// FORCE_INLINE uint32x4_t vzip2q_u32(uint32x4_t a, uint32x4_t b);

// FORCE_INLINE uint64x2_t vzip2q_u64(uint64x2_t a, uint64x2_t b);

// FORCE_INLINE poly64x2_t vzip2q_p64(poly64x2_t a, poly64x2_t b);

// FORCE_INLINE float32x2_t vzip2_f32(float32x2_t a, float32x2_t b);

// FORCE_INLINE float32x4_t vzip2q_f32(float32x4_t a, float32x4_t b);

// FORCE_INLINE float64x2_t vzip2q_f64(float64x2_t a, float64x2_t b);

// FORCE_INLINE poly8x8_t vzip2_p8(poly8x8_t a, poly8x8_t b);

// FORCE_INLINE poly8x16_t vzip2q_p8(poly8x16_t a, poly8x16_t b);

// FORCE_INLINE poly16x4_t vzip2_p16(poly16x4_t a, poly16x4_t b);

// FORCE_INLINE poly16x8_t vzip2q_p16(poly16x8_t a, poly16x8_t b);

// FORCE_INLINE int8x8_t vuzp1_s8(int8x8_t a, int8x8_t b);

// FORCE_INLINE int8x16_t vuzp1q_s8(int8x16_t a, int8x16_t b);

// FORCE_INLINE int16x4_t vuzp1_s16(int16x4_t a, int16x4_t b);

// FORCE_INLINE int16x8_t vuzp1q_s16(int16x8_t a, int16x8_t b);

// FORCE_INLINE int32x2_t vuzp1_s32(int32x2_t a, int32x2_t b);

FORCE_INLINE int32x4_t vuzp1q_s32(int32x4_t a, int32x4_t b) {
  vint64m2_t ab =
      __riscv_vslideup_vx_i64m2(__riscv_vlmul_ext_v_i64m1_i64m2(__riscv_vreinterpret_v_i32m1_i64m1(a)),
                                __riscv_vlmul_ext_v_i64m1_i64m2(__riscv_vreinterpret_v_i32m1_i64m1(b)), 2, 4);
  return __riscv_vnsra_wx_i32m1(ab, 0, 4);
}

// FORCE_INLINE int64x2_t vuzp1q_s64(int64x2_t a, int64x2_t b);

// FORCE_INLINE uint8x8_t vuzp1_u8(uint8x8_t a, uint8x8_t b);

FORCE_INLINE uint8x16_t vuzp1q_u8(uint8x16_t a, uint8x16_t b) {
  vuint16m2_t ab =
      __riscv_vslideup_vx_u16m2(__riscv_vlmul_ext_v_u16m1_u16m2(__riscv_vreinterpret_v_u8m1_u16m1(a)),
                                __riscv_vlmul_ext_v_u16m1_u16m2(__riscv_vreinterpret_v_u8m1_u16m1(b)), 8, 16);
  return __riscv_vnsrl_wx_u8m1(ab, 0, 16);
}

// FORCE_INLINE uint16x4_t vuzp1_u16(uint16x4_t a, uint16x4_t b);

// FORCE_INLINE uint16x8_t vuzp1q_u16(uint16x8_t a, uint16x8_t b);

// FORCE_INLINE uint32x2_t vuzp1_u32(uint32x2_t a, uint32x2_t b);

// FORCE_INLINE uint32x4_t vuzp1q_u32(uint32x4_t a, uint32x4_t b);

// FORCE_INLINE uint64x2_t vuzp1q_u64(uint64x2_t a, uint64x2_t b);

// FORCE_INLINE poly64x2_t vuzp1q_p64(poly64x2_t a, poly64x2_t b);

// FORCE_INLINE float32x2_t vuzp1_f32(float32x2_t a, float32x2_t b);

// FORCE_INLINE float32x4_t vuzp1q_f32(float32x4_t a, float32x4_t b);

// FORCE_INLINE float64x2_t vuzp1q_f64(float64x2_t a, float64x2_t b);

// FORCE_INLINE poly8x8_t vuzp1_p8(poly8x8_t a, poly8x8_t b);

// FORCE_INLINE poly8x16_t vuzp1q_p8(poly8x16_t a, poly8x16_t b);

// FORCE_INLINE poly16x4_t vuzp1_p16(poly16x4_t a, poly16x4_t b);

// FORCE_INLINE poly16x8_t vuzp1q_p16(poly16x8_t a, poly16x8_t b);

// FORCE_INLINE int8x8_t vuzp2_s8(int8x8_t a, int8x8_t b);

// FORCE_INLINE int8x16_t vuzp2q_s8(int8x16_t a, int8x16_t b);

// FORCE_INLINE int16x4_t vuzp2_s16(int16x4_t a, int16x4_t b);

// FORCE_INLINE int16x8_t vuzp2q_s16(int16x8_t a, int16x8_t b);

// FORCE_INLINE int32x2_t vuzp2_s32(int32x2_t a, int32x2_t b);

// FORCE_INLINE int32x4_t vuzp2q_s32(int32x4_t a, int32x4_t b);

// FORCE_INLINE int64x2_t vuzp2q_s64(int64x2_t a, int64x2_t b);

// FORCE_INLINE uint8x8_t vuzp2_u8(uint8x8_t a, uint8x8_t b);

// FORCE_INLINE uint8x16_t vuzp2q_u8(uint8x16_t a, uint8x16_t b);

// FORCE_INLINE uint16x4_t vuzp2_u16(uint16x4_t a, uint16x4_t b);

// FORCE_INLINE uint16x8_t vuzp2q_u16(uint16x8_t a, uint16x8_t b);

// FORCE_INLINE uint32x2_t vuzp2_u32(uint32x2_t a, uint32x2_t b);

// FORCE_INLINE uint32x4_t vuzp2q_u32(uint32x4_t a, uint32x4_t b);

// FORCE_INLINE uint64x2_t vuzp2q_u64(uint64x2_t a, uint64x2_t b);

// FORCE_INLINE poly64x2_t vuzp2q_p64(poly64x2_t a, poly64x2_t b);

// FORCE_INLINE float32x2_t vuzp2_f32(float32x2_t a, float32x2_t b);

// FORCE_INLINE float32x4_t vuzp2q_f32(float32x4_t a, float32x4_t b);

// FORCE_INLINE float64x2_t vuzp2q_f64(float64x2_t a, float64x2_t b);

// FORCE_INLINE poly8x8_t vuzp2_p8(poly8x8_t a, poly8x8_t b);

// FORCE_INLINE poly8x16_t vuzp2q_p8(poly8x16_t a, poly8x16_t b);

// FORCE_INLINE poly16x4_t vuzp2_p16(poly16x4_t a, poly16x4_t b);

// FORCE_INLINE poly16x8_t vuzp2q_p16(poly16x8_t a, poly16x8_t b);

// FORCE_INLINE int8x8_t vtrn1_s8(int8x8_t a, int8x8_t b);

// FORCE_INLINE int8x16_t vtrn1q_s8(int8x16_t a, int8x16_t b);

// FORCE_INLINE int16x4_t vtrn1_s16(int16x4_t a, int16x4_t b);

// FORCE_INLINE int16x8_t vtrn1q_s16(int16x8_t a, int16x8_t b);

// FORCE_INLINE int32x2_t vtrn1_s32(int32x2_t a, int32x2_t b);

// FORCE_INLINE int32x4_t vtrn1q_s32(int32x4_t a, int32x4_t b);

FORCE_INLINE int64x2_t vtrn1q_s64(int64x2_t a, int64x2_t b) {
  vbool64_t mask = __riscv_vmseq_vx_u64m1_b64(__riscv_vand_vx_u64m1(__riscv_vid_v_u64m1(2), 1, 2), 0, 2);
  return __riscv_vmerge_vvm_i64m1(__riscv_vslide1up_vx_i64m1(b, 0, 2), a, mask, 2);
}

FORCE_INLINE uint8x8_t vtrn1_u8(uint8x8_t a, uint8x8_t b) {
  vbool8_t mask = __riscv_vmseq_vx_u8m1_b8(__riscv_vand_vx_u8m1(__riscv_vid_v_u8m1(8), 1, 8), 0, 8);
  return __riscv_vmerge_vvm_u8m1(__riscv_vslide1up_vx_u8m1(b, 0, 8), a, mask, 8);
}

FORCE_INLINE uint8x16_t vtrn1q_u8(uint8x16_t a, uint8x16_t b) {
  vbool8_t mask = __riscv_vmseq_vx_u8m1_b8(__riscv_vand_vx_u8m1(__riscv_vid_v_u8m1(16), 1, 16), 0, 16);
  return __riscv_vmerge_vvm_u8m1(__riscv_vslide1up_vx_u8m1(b, 0, 16), a, mask, 16);
}

// FORCE_INLINE uint16x4_t vtrn1_u16(uint16x4_t a, uint16x4_t b);

// FORCE_INLINE uint16x8_t vtrn1q_u16(uint16x8_t a, uint16x8_t b);

// FORCE_INLINE uint32x2_t vtrn1_u32(uint32x2_t a, uint32x2_t b);

// FORCE_INLINE uint32x4_t vtrn1q_u32(uint32x4_t a, uint32x4_t b);

FORCE_INLINE uint64x2_t vtrn1q_u64(uint64x2_t a, uint64x2_t b) {
  vbool64_t mask = __riscv_vmseq_vx_u64m1_b64(__riscv_vand_vx_u64m1(__riscv_vid_v_u64m1(2), 1, 2), 0, 2);
  return __riscv_vmerge_vvm_u64m1(__riscv_vslide1up_vx_u64m1(b, 0, 2), a, mask, 2);
}
// FORCE_INLINE poly64x2_t vtrn1q_p64(poly64x2_t a, poly64x2_t b);

// FORCE_INLINE float32x2_t vtrn1_f32(float32x2_t a, float32x2_t b);

// FORCE_INLINE float32x4_t vtrn1q_f32(float32x4_t a, float32x4_t b);

// FORCE_INLINE float64x2_t vtrn1q_f64(float64x2_t a, float64x2_t b);

// FORCE_INLINE poly8x8_t vtrn1_p8(poly8x8_t a, poly8x8_t b);

// FORCE_INLINE poly8x16_t vtrn1q_p8(poly8x16_t a, poly8x16_t b);

// FORCE_INLINE poly16x4_t vtrn1_p16(poly16x4_t a, poly16x4_t b);

// FORCE_INLINE poly16x8_t vtrn1q_p16(poly16x8_t a, poly16x8_t b);

// FORCE_INLINE int8x8_t vtrn2_s8(int8x8_t a, int8x8_t b);

// FORCE_INLINE int8x16_t vtrn2q_s8(int8x16_t a, int8x16_t b);

// FORCE_INLINE int16x4_t vtrn2_s16(int16x4_t a, int16x4_t b);

// FORCE_INLINE int16x8_t vtrn2q_s16(int16x8_t a, int16x8_t b);

// FORCE_INLINE int32x2_t vtrn2_s32(int32x2_t a, int32x2_t b);

// FORCE_INLINE int32x4_t vtrn2q_s32(int32x4_t a, int32x4_t b);

FORCE_INLINE int64x2_t vtrn2q_s64(int64x2_t a, int64x2_t b) {
  vbool64_t mask = __riscv_vmseq_vx_u64m1_b64(__riscv_vand_vx_u64m1(__riscv_vid_v_u64m1(2), 1, 2), 0, 2);
  return __riscv_vmerge_vvm_i64m1(b, __riscv_vslide1down_vx_i64m1(a, 0, 2), mask, 2);
}

// FORCE_INLINE uint8x8_t vtrn2_u8(uint8x8_t a, uint8x8_t b);

// FORCE_INLINE uint8x16_t vtrn2q_u8(uint8x16_t a, uint8x16_t b);

// FORCE_INLINE uint16x4_t vtrn2_u16(uint16x4_t a, uint16x4_t b);

// FORCE_INLINE uint16x8_t vtrn2q_u16(uint16x8_t a, uint16x8_t b);

// FORCE_INLINE uint32x2_t vtrn2_u32(uint32x2_t a, uint32x2_t b);

// FORCE_INLINE uint32x4_t vtrn2q_u32(uint32x4_t a, uint32x4_t b);

FORCE_INLINE uint64x2_t vtrn2q_u64(uint64x2_t a, uint64x2_t b) {
  vbool64_t mask = __riscv_vmseq_vx_u64m1_b64(__riscv_vand_vx_u64m1(__riscv_vid_v_u64m1(2), 1, 2), 0, 2);
  return __riscv_vmerge_vvm_u64m1(b, __riscv_vslide1down_vx_u64m1(a, 0, 2), mask, 2);
}

// FORCE_INLINE poly64x2_t vtrn2q_p64(poly64x2_t a, poly64x2_t b);

// FORCE_INLINE float32x2_t vtrn2_f32(float32x2_t a, float32x2_t b);

// FORCE_INLINE float32x4_t vtrn2q_f32(float32x4_t a, float32x4_t b);

// FORCE_INLINE float64x2_t vtrn2q_f64(float64x2_t a, float64x2_t b);

// FORCE_INLINE poly8x8_t vtrn2_p8(poly8x8_t a, poly8x8_t b);

// FORCE_INLINE poly8x16_t vtrn2q_p8(poly8x16_t a, poly8x16_t b);

// FORCE_INLINE poly16x4_t vtrn2_p16(poly16x4_t a, poly16x4_t b);

// FORCE_INLINE poly16x8_t vtrn2q_p16(poly16x8_t a, poly16x8_t b);

FORCE_INLINE int8x8_t vbsl_s8(uint8x8_t a, int8x8_t b, int8x8_t c) {
  return __riscv_vxor_vv_i8m1(
      __riscv_vand_vv_i8m1(__riscv_vxor_vv_i8m1(c, b, 8), __riscv_vreinterpret_v_u8m1_i8m1(a), 8), c, 8);
}

FORCE_INLINE int16x4_t vbsl_s16(uint16x4_t a, int16x4_t b, int16x4_t c) {
  return __riscv_vxor_vv_i16m1(
      __riscv_vand_vv_i16m1(__riscv_vxor_vv_i16m1(c, b, 4), __riscv_vreinterpret_v_u16m1_i16m1(a), 4), c, 4);
}

FORCE_INLINE int32x2_t vbsl_s32(uint32x2_t a, int32x2_t b, int32x2_t c) {
  return __riscv_vxor_vv_i32m1(
      __riscv_vand_vv_i32m1(__riscv_vxor_vv_i32m1(c, b, 2), __riscv_vreinterpret_v_u32m1_i32m1(a), 2), c, 2);
}

FORCE_INLINE int64x1_t vbsl_s64(uint64x1_t a, int64x1_t b, int64x1_t c) {
  return __riscv_vxor_vv_i64m1(
      __riscv_vand_vv_i64m1(__riscv_vxor_vv_i64m1(c, b, 1), __riscv_vreinterpret_v_u64m1_i64m1(a), 1), c, 1);
}

FORCE_INLINE float32x2_t vbsl_f32(uint32x2_t a, float32x2_t b, float32x2_t c) {
  vuint32m1_t b_u32 = __riscv_vreinterpret_v_f32m1_u32m1(b);
  vuint32m1_t c_u32 = __riscv_vreinterpret_v_f32m1_u32m1(c);
  return __riscv_vreinterpret_v_u32m1_f32m1(
      __riscv_vxor_vv_u32m1(__riscv_vand_vv_u32m1(__riscv_vxor_vv_u32m1(c_u32, b_u32, 2), a, 2), c_u32, 2));
}

FORCE_INLINE uint8x8_t vbsl_u8(uint8x8_t a, uint8x8_t b, uint8x8_t c) {
  return __riscv_vxor_vv_u8m1(__riscv_vand_vv_u8m1(__riscv_vxor_vv_u8m1(c, b, 8), a, 8), c, 8);
}

FORCE_INLINE uint16x4_t vbsl_u16(uint16x4_t a, uint16x4_t b, uint16x4_t c) {
  return __riscv_vxor_vv_u16m1(__riscv_vand_vv_u16m1(__riscv_vxor_vv_u16m1(c, b, 4), a, 4), c, 4);
}

FORCE_INLINE uint32x2_t vbsl_u32(uint32x2_t a, uint32x2_t b, uint32x2_t c) {
  return __riscv_vxor_vv_u32m1(__riscv_vand_vv_u32m1(__riscv_vxor_vv_u32m1(c, b, 2), a, 2), c, 2);
}

FORCE_INLINE uint64x1_t vbsl_u64(uint64x1_t a, uint64x1_t b, uint64x1_t c) {
  return __riscv_vxor_vv_u64m1(__riscv_vand_vv_u64m1(__riscv_vxor_vv_u64m1(c, b, 1), a, 1), c, 1);
}

FORCE_INLINE int8x16_t vbslq_s8(uint8x16_t a, int8x16_t b, int8x16_t c) {
  return __riscv_vxor_vv_i8m1(
      __riscv_vand_vv_i8m1(__riscv_vxor_vv_i8m1(c, b, 16), __riscv_vreinterpret_v_u8m1_i8m1(a), 16), c, 16);
}

FORCE_INLINE int16x8_t vbslq_s16(uint16x8_t a, int16x8_t b, int16x8_t c) {
  return __riscv_vxor_vv_i16m1(
      __riscv_vand_vv_i16m1(__riscv_vxor_vv_i16m1(c, b, 8), __riscv_vreinterpret_v_u16m1_i16m1(a), 8), c, 8);
}

FORCE_INLINE int32x4_t vbslq_s32(uint32x4_t a, int32x4_t b, int32x4_t c) {
  return __riscv_vxor_vv_i32m1(
      __riscv_vand_vv_i32m1(__riscv_vxor_vv_i32m1(c, b, 4), __riscv_vreinterpret_v_u32m1_i32m1(a), 4), c, 4);
}

FORCE_INLINE int64x2_t vbslq_s64(uint64x2_t a, int64x2_t b, int64x2_t c) {
  return __riscv_vxor_vv_i64m1(
      __riscv_vand_vv_i64m1(__riscv_vxor_vv_i64m1(c, b, 2), __riscv_vreinterpret_v_u64m1_i64m1(a), 2), c, 2);
}

FORCE_INLINE float32x4_t vbslq_f32(uint32x4_t a, float32x4_t b, float32x4_t c) {
  vuint32m1_t b_u32 = __riscv_vreinterpret_v_f32m1_u32m1(b);
  vuint32m1_t c_u32 = __riscv_vreinterpret_v_f32m1_u32m1(c);
  return __riscv_vreinterpret_v_u32m1_f32m1(
      __riscv_vxor_vv_u32m1(__riscv_vand_vv_u32m1(__riscv_vxor_vv_u32m1(c_u32, b_u32, 4), a, 4), c_u32, 4));
}

// FORCE_INLINE poly8x8_t vbsl_p8(uint8x8_t a, poly8x8_t b, poly8x8_t c);

// FORCE_INLINE poly8x16_t vbslq_p8(uint8x16_t a, poly8x16_t b, poly8x16_t c);

// FORCE_INLINE poly16x4_t vbsl_p16(uint16x4_t a, poly16x4_t b, poly16x4_t c);

// FORCE_INLINE poly16x8_t vbslq_p16(uint16x8_t a, poly16x8_t b, poly16x8_t c);

FORCE_INLINE float64x1_t vbsl_f64(uint64x1_t a, float64x1_t b, float64x1_t c) {
  vuint64m1_t b_u64 = __riscv_vreinterpret_v_f64m1_u64m1(b);
  vuint64m1_t c_u64 = __riscv_vreinterpret_v_f64m1_u64m1(c);
  return __riscv_vreinterpret_v_u64m1_f64m1(
      __riscv_vxor_vv_u64m1(__riscv_vand_vv_u64m1(__riscv_vxor_vv_u64m1(c_u64, b_u64, 1), a, 1), c_u64, 1));
}

FORCE_INLINE float64x2_t vbslq_f64(uint64x2_t a, float64x2_t b, float64x2_t c) {
  vuint64m1_t b_u64 = __riscv_vreinterpret_v_f64m1_u64m1(b);
  vuint64m1_t c_u64 = __riscv_vreinterpret_v_f64m1_u64m1(c);
  return __riscv_vreinterpret_v_u64m1_f64m1(
      __riscv_vxor_vv_u64m1(__riscv_vand_vv_u64m1(__riscv_vxor_vv_u64m1(c_u64, b_u64, 2), a, 2), c_u64, 2));
}

FORCE_INLINE int8x8_t vcopy_lane_s8(int8x8_t a, const int lane1, int8x8_t b, const int lane2) {
  vint8m1_t dup_b = __riscv_vrgather_vx_i8m1(b, lane2, 8);
  vbool8_t set_mask = __riscv_vreinterpret_v_u8m1_b8(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_i8m1(a, dup_b, set_mask, 8);
}

FORCE_INLINE int8x16_t vcopyq_lane_s8(int8x16_t a, const int lane1, int8x8_t b, const int lane2) {
  vint8m1_t dup_b = __riscv_vrgather_vx_i8m1(b, lane2, 16);
  vbool8_t set_mask = __riscv_vreinterpret_v_u16m1_b8(vdup_n_u16((uint16_t)(1 << lane1)));
  return __riscv_vmerge_vvm_i8m1(a, dup_b, set_mask, 16);
}

FORCE_INLINE int16x4_t vcopy_lane_s16(int16x4_t a, const int lane1, int16x4_t b, const int lane2) {
  vint16m1_t dup_b = __riscv_vrgather_vx_i16m1(b, lane2, 4);
  vbool16_t set_mask = __riscv_vreinterpret_v_u8m1_b16(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_i16m1(a, dup_b, set_mask, 4);
}

FORCE_INLINE int16x8_t vcopyq_lane_s16(int16x8_t a, const int lane1, int16x4_t b, const int lane2) {
  vint16m1_t dup_b = __riscv_vrgather_vx_i16m1(b, lane2, 8);
  vbool16_t set_mask = __riscv_vreinterpret_v_u8m1_b16(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_i16m1(a, dup_b, set_mask, 8);
}

FORCE_INLINE int32x2_t vcopy_lane_s32(int32x2_t a, const int lane1, int32x2_t b, const int lane2) {
  vint32m1_t dup_b = __riscv_vrgather_vx_i32m1(b, lane2, 2);
  vbool32_t set_mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_i32m1(a, dup_b, set_mask, 2);
}

FORCE_INLINE int32x4_t vcopyq_lane_s32(int32x4_t a, const int lane1, int32x2_t b, const int lane2) {
  vint32m1_t dup_b = __riscv_vrgather_vx_i32m1(b, lane2, 4);
  vbool32_t set_mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_i32m1(a, dup_b, set_mask, 4);
}

FORCE_INLINE int64x1_t vcopy_lane_s64(int64x1_t a, const int lane1, int64x1_t b, const int lane2) {
  vint64m1_t dup_b = __riscv_vrgather_vx_i64m1(b, lane2, 1);
  vbool64_t set_mask = __riscv_vreinterpret_v_u8m1_b64(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_i64m1(a, dup_b, set_mask, 1);
}

FORCE_INLINE int64x2_t vcopyq_lane_s64(int64x2_t a, const int lane1, int64x1_t b, const int lane2) {
  vint64m1_t dup_b = __riscv_vrgather_vx_i64m1(b, lane2, 2);
  vbool64_t set_mask = __riscv_vreinterpret_v_u8m1_b64(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_i64m1(a, dup_b, set_mask, 2);
}

FORCE_INLINE uint8x8_t vcopy_lane_u8(uint8x8_t a, const int lane1, uint8x8_t b, const int lane2) {
  vuint8m1_t dup_b = __riscv_vrgather_vx_u8m1(b, lane2, 8);
  vbool8_t set_mask = __riscv_vreinterpret_v_u8m1_b8(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_u8m1(a, dup_b, set_mask, 8);
}

FORCE_INLINE uint8x16_t vcopyq_lane_u8(uint8x16_t a, const int lane1, uint8x8_t b, const int lane2) {
  vuint8m1_t dup_b = __riscv_vrgather_vx_u8m1(b, lane2, 16);
  vbool8_t set_mask = __riscv_vreinterpret_v_u16m1_b8(vdup_n_u16((uint16_t)(1 << lane1)));
  return __riscv_vmerge_vvm_u8m1(a, dup_b, set_mask, 16);
}

FORCE_INLINE uint16x4_t vcopy_lane_u16(uint16x4_t a, const int lane1, uint16x4_t b, const int lane2) {
  vuint16m1_t dup_b = __riscv_vrgather_vx_u16m1(b, lane2, 4);
  vbool16_t set_mask = __riscv_vreinterpret_v_u8m1_b16(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_u16m1(a, dup_b, set_mask, 4);
}

FORCE_INLINE uint16x8_t vcopyq_lane_u16(uint16x8_t a, const int lane1, uint16x4_t b, const int lane2) {
  vuint16m1_t dup_b = __riscv_vrgather_vx_u16m1(b, lane2, 8);
  vbool16_t set_mask = __riscv_vreinterpret_v_u8m1_b16(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_u16m1(a, dup_b, set_mask, 8);
}

FORCE_INLINE uint32x2_t vcopy_lane_u32(uint32x2_t a, const int lane1, uint32x2_t b, const int lane2) {
  vuint32m1_t dup_b = __riscv_vrgather_vx_u32m1(b, lane2, 2);
  vbool32_t set_mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_u32m1(a, dup_b, set_mask, 2);
}

FORCE_INLINE uint32x4_t vcopyq_lane_u32(uint32x4_t a, const int lane1, uint32x2_t b, const int lane2) {
  vuint32m1_t dup_b = __riscv_vrgather_vx_u32m1(b, lane2, 4);
  vbool32_t set_mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_u32m1(a, dup_b, set_mask, 4);
}

FORCE_INLINE uint64x1_t vcopy_lane_u64(uint64x1_t a, const int lane1, uint64x1_t b, const int lane2) {
  vuint64m1_t dup_b = __riscv_vrgather_vx_u64m1(b, lane2, 1);
  vbool64_t set_mask = __riscv_vreinterpret_v_u8m1_b64(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_u64m1(a, dup_b, set_mask, 1);
}

FORCE_INLINE uint64x2_t vcopyq_lane_u64(uint64x2_t a, const int lane1, uint64x1_t b, const int lane2) {
  vuint64m1_t dup_b = __riscv_vrgather_vx_u64m1(b, lane2, 2);
  vbool64_t set_mask = __riscv_vreinterpret_v_u8m1_b64(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_u64m1(a, dup_b, set_mask, 2);
}

// FORCE_INLINE poly64x1_t vcopy_lane_p64(poly64x1_t a, const int lane1, poly64x1_t b, const int lane2);

// FORCE_INLINE poly64x2_t vcopyq_lane_p64(poly64x2_t a, const int lane1, poly64x1_t b, const int lane2);

FORCE_INLINE float32x2_t vcopy_lane_f32(float32x2_t a, const int lane1, float32x2_t b, const int lane2) {
  vfloat32m1_t dup_b = __riscv_vrgather_vx_f32m1(b, lane2, 2);
  vbool32_t set_mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_f32m1(a, dup_b, set_mask, 2);
}

FORCE_INLINE float32x4_t vcopyq_lane_f32(float32x4_t a, const int lane1, float32x2_t b, const int lane2) {
  vfloat32m1_t dup_b = __riscv_vrgather_vx_f32m1(b, lane2, 4);
  vbool32_t set_mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_f32m1(a, dup_b, set_mask, 4);
}

FORCE_INLINE float64x1_t vcopy_lane_f64(float64x1_t a, const int lane1, float64x1_t b, const int lane2) {
  vfloat64m1_t dup_b = __riscv_vrgather_vx_f64m1(b, lane2, 1);
  vbool64_t set_mask = __riscv_vreinterpret_v_u8m1_b64(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_f64m1(a, dup_b, set_mask, 1);
}

FORCE_INLINE float64x2_t vcopyq_lane_f64(float64x2_t a, const int lane1, float64x1_t b, const int lane2) {
  vfloat64m1_t dup_b = __riscv_vrgather_vx_f64m1(b, lane2, 2);
  vbool64_t set_mask = __riscv_vreinterpret_v_u8m1_b64(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_f64m1(a, dup_b, set_mask, 2);
}

// FORCE_INLINE poly8x8_t vcopy_lane_p8(poly8x8_t a, const int lane1, poly8x8_t b, const int lane2);

// FORCE_INLINE poly8x16_t vcopyq_lane_p8(poly8x16_t a, const int lane1, poly8x8_t b, const int lane2);

// FORCE_INLINE poly16x4_t vcopy_lane_p16(poly16x4_t a, const int lane1, poly16x4_t b, const int lane2);

// FORCE_INLINE poly16x8_t vcopyq_lane_p16(poly16x8_t a, const int lane1, poly16x4_t b, const int lane2);

FORCE_INLINE int8x8_t vcopy_laneq_s8(int8x8_t a, const int lane1, int8x16_t b, const int lane2) {
  vint8m1_t dup_b = __riscv_vrgather_vx_i8m1(b, lane2, 16);
  vbool8_t set_mask = __riscv_vreinterpret_v_u16m1_b8(vdup_n_u16((uint16_t)(1 << lane1)));
  return __riscv_vmerge_vvm_i8m1(a, dup_b, set_mask, 8);
}

FORCE_INLINE int8x16_t vcopyq_laneq_s8(int8x16_t a, const int lane1, int8x16_t b, const int lane2) {
  vint8m1_t dup_b = __riscv_vrgather_vx_i8m1(b, lane2, 16);
  vbool8_t set_mask = __riscv_vreinterpret_v_u16m1_b8(vdup_n_u16((uint16_t)(1 << lane1)));
  return __riscv_vmerge_vvm_i8m1(a, dup_b, set_mask, 16);
}

FORCE_INLINE int16x4_t vcopy_laneq_s16(int16x4_t a, const int lane1, int16x8_t b, const int lane2) {
  vint16m1_t dup_b = __riscv_vrgather_vx_i16m1(b, lane2, 8);
  vbool16_t set_mask = __riscv_vreinterpret_v_u8m1_b16(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_i16m1(a, dup_b, set_mask, 4);
}

FORCE_INLINE int16x8_t vcopyq_laneq_s16(int16x8_t a, const int lane1, int16x8_t b, const int lane2) {
  vint16m1_t dup_b = __riscv_vrgather_vx_i16m1(b, lane2, 8);
  vbool16_t set_mask = __riscv_vreinterpret_v_u8m1_b16(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_i16m1(a, dup_b, set_mask, 8);
}

FORCE_INLINE int32x2_t vcopy_laneq_s32(int32x2_t a, const int lane1, int32x4_t b, const int lane2) {
  vint32m1_t dup_b = __riscv_vrgather_vx_i32m1(b, lane2, 4);
  vbool32_t set_mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_i32m1(a, dup_b, set_mask, 2);
}

FORCE_INLINE int32x4_t vcopyq_laneq_s32(int32x4_t a, const int lane1, int32x4_t b, const int lane2) {
  vint32m1_t dup_b = __riscv_vrgather_vx_i32m1(b, lane2, 4);
  vbool32_t set_mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_i32m1(a, dup_b, set_mask, 4);
}

FORCE_INLINE int64x1_t vcopy_laneq_s64(int64x1_t a, const int lane1, int64x2_t b, const int lane2) {
  vint64m1_t dup_b = __riscv_vrgather_vx_i64m1(b, lane2, 2);
  vbool64_t set_mask = __riscv_vreinterpret_v_u8m1_b64(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_i64m1(a, dup_b, set_mask, 1);
}

FORCE_INLINE int64x2_t vcopyq_laneq_s64(int64x2_t a, const int lane1, int64x2_t b, const int lane2) {
  vint64m1_t dup_b = __riscv_vrgather_vx_i64m1(b, lane2, 2);
  vbool64_t set_mask = __riscv_vreinterpret_v_u8m1_b64(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_i64m1(a, dup_b, set_mask, 2);
}

FORCE_INLINE uint8x8_t vcopy_laneq_u8(uint8x8_t a, const int lane1, uint8x16_t b, const int lane2) {
  vuint8m1_t dup_b = __riscv_vrgather_vx_u8m1(b, lane2, 16);
  vbool8_t set_mask = __riscv_vreinterpret_v_u16m1_b8(vdup_n_u16((uint16_t)(1 << lane1)));
  return __riscv_vmerge_vvm_u8m1(a, dup_b, set_mask, 8);
}

FORCE_INLINE uint8x16_t vcopyq_laneq_u8(uint8x16_t a, const int lane1, uint8x16_t b, const int lane2) {
  vuint8m1_t dup_b = __riscv_vrgather_vx_u8m1(b, lane2, 16);
  vbool8_t set_mask = __riscv_vreinterpret_v_u16m1_b8(vdup_n_u16((uint16_t)(1 << lane1)));
  return __riscv_vmerge_vvm_u8m1(a, dup_b, set_mask, 16);
}

FORCE_INLINE uint16x4_t vcopy_laneq_u16(uint16x4_t a, const int lane1, uint16x8_t b, const int lane2) {
  vuint16m1_t dup_b = __riscv_vrgather_vx_u16m1(b, lane2, 8);
  vbool16_t set_mask = __riscv_vreinterpret_v_u8m1_b16(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_u16m1(a, dup_b, set_mask, 4);
}

FORCE_INLINE uint16x8_t vcopyq_laneq_u16(uint16x8_t a, const int lane1, uint16x8_t b, const int lane2) {
  vuint16m1_t dup_b = __riscv_vrgather_vx_u16m1(b, lane2, 8);
  vbool16_t set_mask = __riscv_vreinterpret_v_u8m1_b16(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_u16m1(a, dup_b, set_mask, 8);
}

FORCE_INLINE uint32x2_t vcopy_laneq_u32(uint32x2_t a, const int lane1, uint32x4_t b, const int lane2) {
  vuint32m1_t dup_b = __riscv_vrgather_vx_u32m1(b, lane2, 4);
  vbool32_t set_mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_u32m1(a, dup_b, set_mask, 2);
}

FORCE_INLINE uint32x4_t vcopyq_laneq_u32(uint32x4_t a, const int lane1, uint32x4_t b, const int lane2) {
  vuint32m1_t dup_b = __riscv_vrgather_vx_u32m1(b, lane2, 4);
  vbool32_t set_mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_u32m1(a, dup_b, set_mask, 4);
}

FORCE_INLINE uint64x1_t vcopy_laneq_u64(uint64x1_t a, const int lane1, uint64x2_t b, const int lane2) {
  vuint64m1_t dup_b = __riscv_vrgather_vx_u64m1(b, lane2, 2);
  vbool64_t set_mask = __riscv_vreinterpret_v_u8m1_b64(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_u64m1(a, dup_b, set_mask, 1);
}

FORCE_INLINE uint64x2_t vcopyq_laneq_u64(uint64x2_t a, const int lane1, uint64x2_t b, const int lane2) {
  vuint64m1_t dup_b = __riscv_vrgather_vx_u64m1(b, lane2, 2);
  vbool64_t set_mask = __riscv_vreinterpret_v_u8m1_b64(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_u64m1(a, dup_b, set_mask, 2);
}

// FORCE_INLINE poly64x1_t vcopy_laneq_p64(poly64x1_t a, const int lane1, poly64x2_t b, const int lane2);

// FORCE_INLINE poly64x2_t vcopyq_laneq_p64(poly64x2_t a, const int lane1, poly64x2_t b, const int lane2);

FORCE_INLINE float32x2_t vcopy_laneq_f32(float32x2_t a, const int lane1, float32x4_t b, const int lane2) {
  vfloat32m1_t dup_b = __riscv_vrgather_vx_f32m1(b, lane2, 4);
  vbool32_t set_mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_f32m1(a, dup_b, set_mask, 2);
}

FORCE_INLINE float32x4_t vcopyq_laneq_f32(float32x4_t a, const int lane1, float32x4_t b, const int lane2) {
  vfloat32m1_t dup_b = __riscv_vrgather_vx_f32m1(b, lane2, 4);
  vbool32_t set_mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_f32m1(a, dup_b, set_mask, 4);
}

FORCE_INLINE float64x1_t vcopy_laneq_f64(float64x1_t a, const int lane1, float64x2_t b, const int lane2) {
  vfloat64m1_t dup_b = __riscv_vrgather_vx_f64m1(b, lane2, 2);
  vbool64_t set_mask = __riscv_vreinterpret_v_u8m1_b64(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_f64m1(a, dup_b, set_mask, 1);
}

FORCE_INLINE float64x2_t vcopyq_laneq_f64(float64x2_t a, const int lane1, float64x2_t b, const int lane2) {
  vfloat64m1_t dup_b = __riscv_vrgather_vx_f64m1(b, lane2, 2);
  vbool64_t set_mask = __riscv_vreinterpret_v_u8m1_b64(vdup_n_u8((uint8_t)(1 << lane1)));
  return __riscv_vmerge_vvm_f64m1(a, dup_b, set_mask, 2);
}

// FORCE_INLINE poly8x8_t vcopy_laneq_p8(poly8x8_t a, const int lane1, poly8x16_t b, const int lane2);

// FORCE_INLINE poly8x16_t vcopyq_laneq_p8(poly8x16_t a, const int lane1, poly8x16_t b, const int lane2);

// FORCE_INLINE poly16x4_t vcopy_laneq_p16(poly16x4_t a, const int lane1, poly16x8_t b, const int lane2);

// FORCE_INLINE poly16x8_t vcopyq_laneq_p16(poly16x8_t a, const int lane1, poly16x8_t b, const int lane2);

// FORCE_INLINE int8x8_t vrbit_s8(int8x8_t a);

// FORCE_INLINE int8x16_t vrbitq_s8(int8x16_t a);

// FORCE_INLINE uint8x8_t vrbit_u8(uint8x8_t a);

// FORCE_INLINE uint8x16_t vrbitq_u8(uint8x16_t a);

// FORCE_INLINE poly8x8_t vrbit_p8(poly8x8_t a);

// FORCE_INLINE poly8x16_t vrbitq_p8(poly8x16_t a);

FORCE_INLINE uint8x16_t vbslq_u8(uint8x16_t a, uint8x16_t b, uint8x16_t c) {
  return __riscv_vxor_vv_u8m1(__riscv_vand_vv_u8m1(__riscv_vxor_vv_u8m1(c, b, 16), a, 16), c, 16);
}

FORCE_INLINE uint16x8_t vbslq_u16(uint16x8_t a, uint16x8_t b, uint16x8_t c) {
  return __riscv_vxor_vv_u16m1(__riscv_vand_vv_u16m1(__riscv_vxor_vv_u16m1(c, b, 8), a, 8), c, 8);
}

FORCE_INLINE uint32x4_t vbslq_u32(uint32x4_t a, uint32x4_t b, uint32x4_t c) {
  return __riscv_vxor_vv_u32m1(__riscv_vand_vv_u32m1(__riscv_vxor_vv_u32m1(c, b, 4), a, 4), c, 4);
}

FORCE_INLINE uint64x2_t vbslq_u64(uint64x2_t a, uint64x2_t b, uint64x2_t c) {
  return __riscv_vxor_vv_u64m1(__riscv_vand_vv_u64m1(__riscv_vxor_vv_u64m1(c, b, 2), a, 2), c, 2);
}

// FORCE_INLINE poly64x1_t vbsl_p64(poly64x1_t a, poly64x1_t b, poly64x1_t c);

// FORCE_INLINE poly64x2_t vbslq_p64(poly64x2_t a, poly64x2_t b, poly64x2_t c);

FORCE_INLINE int8x8x2_t vtrn_s8(int8x8_t a, int8x8_t b) {
  vuint16m1_t a_u16 = __riscv_vreinterpret_v_i16m1_u16m1(__riscv_vreinterpret_v_i8m1_i16m1(a));
  vuint16m1_t b_u16 = __riscv_vreinterpret_v_i16m1_u16m1(__riscv_vreinterpret_v_i8m1_i16m1(b));

  vuint8m1_t a1 = __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vsrl_vx_u16m1(__riscv_vsll_vx_u16m1(a_u16, 8, 4), 8, 4));
  vuint8m1_t b1 = __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vsll_vx_u16m1(b_u16, 8, 4));
  vint8m1_t trn1 = __riscv_vreinterpret_v_u8m1_i8m1(__riscv_vor_vv_u8m1(a1, b1, 8));

  vuint8m1_t a2 = __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vsrl_vx_u16m1(a_u16, 8, 4));
  vuint8m1_t b2 = __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vsll_vx_u16m1(__riscv_vsrl_vx_u16m1(b_u16, 8, 4), 8, 4));
  vint8m1_t trn2 = __riscv_vreinterpret_v_u8m1_i8m1(__riscv_vor_vv_u8m1(a2, b2, 8));
  return __riscv_vcreate_v_i8m1x2(trn1, trn2);
}

FORCE_INLINE int16x4x2_t vtrn_s16(int16x4_t a, int16x4_t b) {
  vuint32m1_t a_u32 = __riscv_vreinterpret_v_i32m1_u32m1(__riscv_vreinterpret_v_i16m1_i32m1(a));
  vuint32m1_t b_u32 = __riscv_vreinterpret_v_i32m1_u32m1(__riscv_vreinterpret_v_i16m1_i32m1(b));

  vuint16m1_t a1 =
      __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vsrl_vx_u32m1(__riscv_vsll_vx_u32m1(a_u32, 16, 2), 16, 2));
  vuint16m1_t b1 = __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vsll_vx_u32m1(b_u32, 16, 2));
  vint16m1_t trn1 = __riscv_vreinterpret_v_u16m1_i16m1(__riscv_vor_vv_u16m1(a1, b1, 4));

  vuint16m1_t a2 = __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vsrl_vx_u32m1(a_u32, 16, 2));
  vuint16m1_t b2 =
      __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vsll_vx_u32m1(__riscv_vsrl_vx_u32m1(b_u32, 16, 2), 16, 2));
  vint16m1_t trn2 = __riscv_vreinterpret_v_u16m1_i16m1(__riscv_vor_vv_u16m1(a2, b2, 4));
  return __riscv_vcreate_v_i16m1x2(trn1, trn2);
}

FORCE_INLINE uint8x8x2_t vtrn_u8(uint8x8_t a, uint8x8_t b) {
  vuint16m1_t a_u16 = __riscv_vreinterpret_v_u8m1_u16m1(a);
  vuint16m1_t b_u16 = __riscv_vreinterpret_v_u8m1_u16m1(b);

  vuint8m1_t a1 = __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vsrl_vx_u16m1(__riscv_vsll_vx_u16m1(a_u16, 8, 4), 8, 4));
  vuint8m1_t b1 = __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vsll_vx_u16m1(b_u16, 8, 4));
  vuint8m1_t trn1 = __riscv_vor_vv_u8m1(a1, b1, 8);

  vuint8m1_t a2 = __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vsrl_vx_u16m1(a_u16, 8, 4));
  vuint8m1_t b2 = __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vsll_vx_u16m1(__riscv_vsrl_vx_u16m1(b_u16, 8, 4), 8, 4));
  vuint8m1_t trn2 = __riscv_vor_vv_u8m1(a2, b2, 8);
  return __riscv_vcreate_v_u8m1x2(trn1, trn2);
}

FORCE_INLINE uint16x4x2_t vtrn_u16(uint16x4_t a, uint16x4_t b) {
  vuint32m1_t a_u32 = __riscv_vreinterpret_v_u16m1_u32m1(a);
  vuint32m1_t b_u32 = __riscv_vreinterpret_v_u16m1_u32m1(b);

  vuint16m1_t a1 =
      __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vsrl_vx_u32m1(__riscv_vsll_vx_u32m1(a_u32, 16, 2), 16, 2));
  vuint16m1_t b1 = __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vsll_vx_u32m1(b_u32, 16, 2));
  vuint16m1_t trn1 = __riscv_vor_vv_u16m1(a1, b1, 4);

  vuint16m1_t a2 = __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vsrl_vx_u32m1(a_u32, 16, 2));
  vuint16m1_t b2 =
      __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vsll_vx_u32m1(__riscv_vsrl_vx_u32m1(b_u32, 16, 2), 16, 2));
  vuint16m1_t trn2 = __riscv_vor_vv_u16m1(a2, b2, 4);
  return __riscv_vcreate_v_u16m1x2(trn1, trn2);
}

// FORCE_INLINE poly8x8x2_t vtrn_p8(poly8x8_t a, poly8x8_t b);

// FORCE_INLINE poly16x4x2_t vtrn_p16(poly16x4_t a, poly16x4_t b);

FORCE_INLINE int32x2x2_t vtrn_s32(int32x2_t a, int32x2_t b) {
  vuint64m1_t a_u64 = __riscv_vreinterpret_v_i64m1_u64m1(__riscv_vreinterpret_v_i32m1_i64m1(a));
  vuint64m1_t b_u64 = __riscv_vreinterpret_v_i64m1_u64m1(__riscv_vreinterpret_v_i32m1_i64m1(b));

  vuint32m1_t a1 =
      __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vsrl_vx_u64m1(__riscv_vsll_vx_u64m1(a_u64, 32, 2), 32, 2));
  vuint32m1_t b1 = __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vsll_vx_u64m1(b_u64, 32, 2));
  vint32m1_t trn1 = __riscv_vreinterpret_v_u32m1_i32m1(__riscv_vor_vv_u32m1(a1, b1, 4));

  vuint32m1_t a2 = __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vsrl_vx_u64m1(a_u64, 32, 2));
  vuint32m1_t b2 =
      __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vsll_vx_u64m1(__riscv_vsrl_vx_u64m1(b_u64, 32, 2), 32, 2));
  vint32m1_t trn2 = __riscv_vreinterpret_v_u32m1_i32m1(__riscv_vor_vv_u32m1(a2, b2, 4));
  return __riscv_vcreate_v_i32m1x2(trn1, trn2);
}

FORCE_INLINE float32x2x2_t vtrn_f32(float32x2_t a, float32x2_t b) {
  vuint64m1_t a_u64 =
      __riscv_vreinterpret_v_i64m1_u64m1(__riscv_vreinterpret_v_i32m1_i64m1(__riscv_vreinterpret_v_f32m1_i32m1(a)));
  vuint64m1_t b_u64 =
      __riscv_vreinterpret_v_i64m1_u64m1(__riscv_vreinterpret_v_i32m1_i64m1(__riscv_vreinterpret_v_f32m1_i32m1(b)));

  vuint32m1_t a1 =
      __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vsrl_vx_u64m1(__riscv_vsll_vx_u64m1(a_u64, 32, 2), 32, 2));
  vuint32m1_t b1 = __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vsll_vx_u64m1(b_u64, 32, 2));
  vfloat32m1_t trn1 = __riscv_vreinterpret_v_u32m1_f32m1(__riscv_vor_vv_u32m1(a1, b1, 4));

  vuint32m1_t a2 = __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vsrl_vx_u64m1(a_u64, 32, 2));
  vuint32m1_t b2 =
      __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vsll_vx_u64m1(__riscv_vsrl_vx_u64m1(b_u64, 32, 2), 32, 2));
  vfloat32m1_t trn2 = __riscv_vreinterpret_v_u32m1_f32m1(__riscv_vor_vv_u32m1(a2, b2, 4));
  return __riscv_vcreate_v_f32m1x2(trn1, trn2);
}

FORCE_INLINE uint32x2x2_t vtrn_u32(uint32x2_t a, uint32x2_t b) {
  vuint64m1_t a_u64 = __riscv_vreinterpret_v_u32m1_u64m1(a);
  vuint64m1_t b_u64 = __riscv_vreinterpret_v_u32m1_u64m1(b);

  vuint32m1_t a1 =
      __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vsrl_vx_u64m1(__riscv_vsll_vx_u64m1(a_u64, 32, 2), 32, 2));
  vuint32m1_t b1 = __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vsll_vx_u64m1(b_u64, 32, 2));
  vuint32m1_t trn1 = __riscv_vor_vv_u32m1(a1, b1, 4);

  vuint32m1_t a2 = __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vsrl_vx_u64m1(a_u64, 32, 2));
  vuint32m1_t b2 =
      __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vsll_vx_u64m1(__riscv_vsrl_vx_u64m1(b_u64, 32, 2), 32, 2));
  vuint32m1_t trn2 = __riscv_vor_vv_u32m1(a2, b2, 4);
  return __riscv_vcreate_v_u32m1x2(trn1, trn2);
}

FORCE_INLINE int8x16x2_t vtrnq_s8(int8x16_t a, int8x16_t b) {
  vuint16m1_t a_u16 = __riscv_vreinterpret_v_i16m1_u16m1(__riscv_vreinterpret_v_i8m1_i16m1(a));
  vuint16m1_t b_u16 = __riscv_vreinterpret_v_i16m1_u16m1(__riscv_vreinterpret_v_i8m1_i16m1(b));

  vuint8m1_t a1 = __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vsrl_vx_u16m1(__riscv_vsll_vx_u16m1(a_u16, 8, 8), 8, 8));
  vuint8m1_t b1 = __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vsll_vx_u16m1(b_u16, 8, 8));
  vint8m1_t trn1 = __riscv_vreinterpret_v_u8m1_i8m1(__riscv_vor_vv_u8m1(a1, b1, 16));

  vuint8m1_t a2 = __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vsrl_vx_u16m1(a_u16, 8, 8));
  vuint8m1_t b2 = __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vsll_vx_u16m1(__riscv_vsrl_vx_u16m1(b_u16, 8, 8), 8, 8));
  vint8m1_t trn2 = __riscv_vreinterpret_v_u8m1_i8m1(__riscv_vor_vv_u8m1(a2, b2, 16));
  return __riscv_vcreate_v_i8m1x2(trn1, trn2);
}

FORCE_INLINE int16x8x2_t vtrnq_s16(int16x8_t a, int16x8_t b) {
  vuint32m1_t a_u32 = __riscv_vreinterpret_v_i32m1_u32m1(__riscv_vreinterpret_v_i16m1_i32m1(a));
  vuint32m1_t b_u32 = __riscv_vreinterpret_v_i32m1_u32m1(__riscv_vreinterpret_v_i16m1_i32m1(b));

  vuint16m1_t a1 =
      __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vsrl_vx_u32m1(__riscv_vsll_vx_u32m1(a_u32, 16, 4), 16, 4));
  vuint16m1_t b1 = __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vsll_vx_u32m1(b_u32, 16, 4));
  vint16m1_t trn1 = __riscv_vreinterpret_v_u16m1_i16m1(__riscv_vor_vv_u16m1(a1, b1, 8));

  vuint16m1_t a2 = __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vsrl_vx_u32m1(a_u32, 16, 4));
  vuint16m1_t b2 =
      __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vsll_vx_u32m1(__riscv_vsrl_vx_u32m1(b_u32, 16, 4), 16, 4));
  vint16m1_t trn2 = __riscv_vreinterpret_v_u16m1_i16m1(__riscv_vor_vv_u16m1(a2, b2, 8));
  return __riscv_vcreate_v_i16m1x2(trn1, trn2);
}

FORCE_INLINE int32x4x2_t vtrnq_s32(int32x4_t a, int32x4_t b) {
  vuint64m1_t a_u64 = __riscv_vreinterpret_v_i64m1_u64m1(__riscv_vreinterpret_v_i32m1_i64m1(a));
  vuint64m1_t b_u64 = __riscv_vreinterpret_v_i64m1_u64m1(__riscv_vreinterpret_v_i32m1_i64m1(b));

  vuint32m1_t a1 =
      __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vsrl_vx_u64m1(__riscv_vsll_vx_u64m1(a_u64, 32, 4), 32, 4));
  vuint32m1_t b1 = __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vsll_vx_u64m1(b_u64, 32, 4));
  vint32m1_t trn1 = __riscv_vreinterpret_v_u32m1_i32m1(__riscv_vor_vv_u32m1(a1, b1, 8));

  vuint32m1_t a2 = __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vsrl_vx_u64m1(a_u64, 32, 4));
  vuint32m1_t b2 =
      __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vsll_vx_u64m1(__riscv_vsrl_vx_u64m1(b_u64, 32, 4), 32, 4));
  vint32m1_t trn2 = __riscv_vreinterpret_v_u32m1_i32m1(__riscv_vor_vv_u32m1(a2, b2, 8));
  return __riscv_vcreate_v_i32m1x2(trn1, trn2);
}

FORCE_INLINE float32x4x2_t vtrnq_f32(float32x4_t a, float32x4_t b) {
  vuint64m1_t a_u64 =
      __riscv_vreinterpret_v_i64m1_u64m1(__riscv_vreinterpret_v_i32m1_i64m1(__riscv_vreinterpret_v_f32m1_i32m1(a)));
  vuint64m1_t b_u64 =
      __riscv_vreinterpret_v_i64m1_u64m1(__riscv_vreinterpret_v_i32m1_i64m1(__riscv_vreinterpret_v_f32m1_i32m1(b)));

  vuint32m1_t a1 =
      __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vsrl_vx_u64m1(__riscv_vsll_vx_u64m1(a_u64, 32, 4), 32, 4));
  vuint32m1_t b1 = __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vsll_vx_u64m1(b_u64, 32, 4));
  vfloat32m1_t trn1 = __riscv_vreinterpret_v_u32m1_f32m1(__riscv_vor_vv_u32m1(a1, b1, 8));

  vuint32m1_t a2 = __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vsrl_vx_u64m1(a_u64, 32, 4));
  vuint32m1_t b2 =
      __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vsll_vx_u64m1(__riscv_vsrl_vx_u64m1(b_u64, 32, 4), 32, 4));
  vfloat32m1_t trn2 = __riscv_vreinterpret_v_u32m1_f32m1(__riscv_vor_vv_u32m1(a2, b2, 8));
  return __riscv_vcreate_v_f32m1x2(trn1, trn2);
}

FORCE_INLINE uint8x16x2_t vtrnq_u8(uint8x16_t a, uint8x16_t b) {
  vuint16m1_t a_u16 = __riscv_vreinterpret_v_u8m1_u16m1(a);
  vuint16m1_t b_u16 = __riscv_vreinterpret_v_u8m1_u16m1(b);

  vuint8m1_t a1 = __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vsrl_vx_u16m1(__riscv_vsll_vx_u16m1(a_u16, 8, 8), 8, 8));
  vuint8m1_t b1 = __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vsll_vx_u16m1(b_u16, 8, 8));
  vuint8m1_t trn1 = __riscv_vor_vv_u8m1(a1, b1, 16);

  vuint8m1_t a2 = __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vsrl_vx_u16m1(a_u16, 8, 8));
  vuint8m1_t b2 = __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vsll_vx_u16m1(__riscv_vsrl_vx_u16m1(b_u16, 8, 8), 8, 8));
  vuint8m1_t trn2 = __riscv_vor_vv_u8m1(a2, b2, 16);
  return __riscv_vcreate_v_u8m1x2(trn1, trn2);
}

FORCE_INLINE uint16x8x2_t vtrnq_u16(uint16x8_t a, uint16x8_t b) {
  vuint32m1_t a_u32 = __riscv_vreinterpret_v_u16m1_u32m1(a);
  vuint32m1_t b_u32 = __riscv_vreinterpret_v_u16m1_u32m1(b);

  vuint16m1_t a1 =
      __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vsrl_vx_u32m1(__riscv_vsll_vx_u32m1(a_u32, 16, 4), 16, 4));
  vuint16m1_t b1 = __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vsll_vx_u32m1(b_u32, 16, 4));
  vuint16m1_t trn1 = __riscv_vor_vv_u16m1(a1, b1, 8);

  vuint16m1_t a2 = __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vsrl_vx_u32m1(a_u32, 16, 4));
  vuint16m1_t b2 =
      __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vsll_vx_u32m1(__riscv_vsrl_vx_u32m1(b_u32, 16, 4), 16, 4));
  vuint16m1_t trn2 = __riscv_vor_vv_u16m1(a2, b2, 8);
  return __riscv_vcreate_v_u16m1x2(trn1, trn2);
}

FORCE_INLINE uint32x4x2_t vtrnq_u32(uint32x4_t a, uint32x4_t b) {
  vuint64m1_t a_u64 = __riscv_vreinterpret_v_u32m1_u64m1(a);
  vuint64m1_t b_u64 = __riscv_vreinterpret_v_u32m1_u64m1(b);

  vuint32m1_t a1 =
      __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vsrl_vx_u64m1(__riscv_vsll_vx_u64m1(a_u64, 32, 4), 32, 4));
  vuint32m1_t b1 = __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vsll_vx_u64m1(b_u64, 32, 4));
  vuint32m1_t trn1 = __riscv_vor_vv_u32m1(a1, b1, 8);

  vuint32m1_t a2 = __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vsrl_vx_u64m1(a_u64, 32, 4));
  vuint32m1_t b2 =
      __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vsll_vx_u64m1(__riscv_vsrl_vx_u64m1(b_u64, 32, 4), 32, 4));
  vuint32m1_t trn2 = __riscv_vor_vv_u32m1(a2, b2, 8);
  return __riscv_vcreate_v_u32m1x2(trn1, trn2);
}

// FORCE_INLINE poly8x16x2_t vtrnq_p8(poly8x16_t a, poly8x16_t b);

// FORCE_INLINE poly16x8x2_t vtrnq_p16(poly16x8_t a, poly16x8_t b);

FORCE_INLINE int8x8x2_t vzip_s8(int8x8_t a, int8x8_t b) {
  // TODO add explaination. source:
  // https://github.com/riscv-non-isa/rvv-intrinsic-doc/issues/289#issuecomment-1781385001
  vuint8m1_t a_u8 = __riscv_vreinterpret_v_i8m1_u8m1(a);
  vuint8m1_t b_u8 = __riscv_vreinterpret_v_i8m1_u8m1(b);
  vuint16m2_t ab_waddu = __riscv_vwaddu_vv_u16m2(a_u8, b_u8, 8);
  vuint16m1_t zip_u16 = __riscv_vlmul_trunc_v_u16m2_u16m1(__riscv_vwmaccu_vx_u16m2(ab_waddu, UINT8_MAX, b_u8, 8));
  vint8m1_t zip = __riscv_vreinterpret_v_i16m1_i8m1(__riscv_vreinterpret_v_u16m1_i16m1(zip_u16));
  return __riscv_vcreate_v_i8m1x2(zip, __riscv_vslidedown_vx_i8m1(zip, 8, 16));
}

FORCE_INLINE int16x4x2_t vzip_s16(int16x4_t a, int16x4_t b) {
  vuint16m1_t a_u16 = __riscv_vreinterpret_v_i16m1_u16m1(a);
  vuint16m1_t b_u16 = __riscv_vreinterpret_v_i16m1_u16m1(b);
  vuint32m2_t ab_waddu = __riscv_vwaddu_vv_u32m2(a_u16, b_u16, 4);
  vuint32m1_t zip_u32 = __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwmaccu_vx_u32m2(ab_waddu, UINT16_MAX, b_u16, 4));
  vint16m1_t zip = __riscv_vreinterpret_v_i32m1_i16m1(__riscv_vreinterpret_v_u32m1_i32m1(zip_u32));
  return __riscv_vcreate_v_i16m1x2(zip, __riscv_vslidedown_vx_i16m1(zip, 4, 8));
}

FORCE_INLINE uint8x8x2_t vzip_u8(uint8x8_t a, uint8x8_t b) {
  vuint16m2_t ab_waddu = __riscv_vwaddu_vv_u16m2(a, b, 8);
  vuint16m2_t res_m2 = __riscv_vwmaccu_vx_u16m2(ab_waddu, UINT8_MAX, b, 8);
  vuint8m1_t res = __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vlmul_trunc_v_u16m2_u16m1(res_m2));
  return __riscv_vcreate_v_u8m1x2(res, __riscv_vslidedown_vx_u8m1(res, 8, 16));
}

FORCE_INLINE uint16x4x2_t vzip_u16(uint16x4_t a, uint16x4_t b) {
  vuint32m2_t ab_waddu = __riscv_vwaddu_vv_u32m2(a, b, 4);
  vuint32m2_t zip_u32 = __riscv_vwmaccu_vx_u32m2(ab_waddu, UINT16_MAX, b, 4);
  vuint16m1_t zip = __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vlmul_trunc_v_u32m2_u32m1(zip_u32));
  return __riscv_vcreate_v_u16m1x2(zip, __riscv_vslidedown_vx_u16m1(zip, 4, 8));
}

// FORCE_INLINE poly8x8x2_t vzip_p8(poly8x8_t a, poly8x8_t b);

// FORCE_INLINE poly16x4x2_t vzip_p16(poly16x4_t a, poly16x4_t b);

FORCE_INLINE int32x2x2_t vzip_s32(int32x2_t a, int32x2_t b) {
  vuint32m1_t a_u32 = __riscv_vreinterpret_v_i32m1_u32m1(a);
  vuint32m1_t b_u32 = __riscv_vreinterpret_v_i32m1_u32m1(b);
  vuint64m2_t ab_waddu = __riscv_vwaddu_vv_u64m2(a_u32, b_u32, 2);
  vuint64m1_t zip_u64 = __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwmaccu_vx_u64m2(ab_waddu, UINT32_MAX, b_u32, 2));
  vint32m1_t zip = __riscv_vreinterpret_v_i64m1_i32m1(__riscv_vreinterpret_v_u64m1_i64m1(zip_u64));
  return __riscv_vcreate_v_i32m1x2(zip, __riscv_vslidedown_vx_i32m1(zip, 2, 4));
}

FORCE_INLINE float32x2x2_t vzip_f32(float32x2_t a, float32x2_t b) {
  vuint32m1_t a_u32 = __riscv_vreinterpret_v_f32m1_u32m1(a);
  vuint32m1_t b_u32 = __riscv_vreinterpret_v_f32m1_u32m1(b);
  vuint64m2_t ab_waddu = __riscv_vwaddu_vv_u64m2(a_u32, b_u32, 2);
  vuint64m1_t zip_u64 = __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwmaccu_vx_u64m2(ab_waddu, UINT32_MAX, b_u32, 2));
  vfloat32m1_t zip = __riscv_vreinterpret_v_u32m1_f32m1(__riscv_vreinterpret_v_u64m1_u32m1(zip_u64));
  return __riscv_vcreate_v_f32m1x2(zip, __riscv_vslidedown_vx_f32m1(zip, 2, 4));
}

FORCE_INLINE uint32x2x2_t vzip_u32(uint32x2_t a, uint32x2_t b) {
  vuint64m2_t ab_waddu = __riscv_vwaddu_vv_u64m2(a, b, 2);
  vuint64m2_t zip_u64 = __riscv_vwmaccu_vx_u64m2(ab_waddu, UINT32_MAX, b, 2);
  vuint32m1_t zip = __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vlmul_trunc_v_u64m2_u64m1(zip_u64));
  return __riscv_vcreate_v_u32m1x2(zip, __riscv_vslidedown_vx_u32m1(zip, 2, 4));
}

FORCE_INLINE int8x16x2_t vzipq_s8(int8x16_t a, int8x16_t b) {
  vuint8m1_t a_u8 = __riscv_vreinterpret_v_i8m1_u8m1(a);
  vuint8m1_t b_u8 = __riscv_vreinterpret_v_i8m1_u8m1(b);
  vuint16m2_t ab_waddu = __riscv_vwaddu_vv_u16m2(a_u8, b_u8, 16);
  vuint16m2_t zip_u16 = __riscv_vwmaccu_vx_u16m2(ab_waddu, UINT8_MAX, b_u8, 16);
  vint8m2_t zip = __riscv_vreinterpret_v_i16m2_i8m2(__riscv_vreinterpret_v_u16m2_i16m2(zip_u16));
  return __riscv_vcreate_v_i8m1x2(__riscv_vget_v_i8m2_i8m1(zip, 0),
                                  __riscv_vget_v_i8m2_i8m1(__riscv_vslidedown_vx_i8m2(zip, 16, 32), 0));
}

FORCE_INLINE int16x8x2_t vzipq_s16(int16x8_t a, int16x8_t b) {
  vuint16m1_t a_u16 = __riscv_vreinterpret_v_i16m1_u16m1(a);
  vuint16m1_t b_u16 = __riscv_vreinterpret_v_i16m1_u16m1(b);
  vuint32m2_t ab_waddu = __riscv_vwaddu_vv_u32m2(a_u16, b_u16, 8);
  vuint32m2_t zip_u32 = __riscv_vwmaccu_vx_u32m2(ab_waddu, UINT16_MAX, b_u16, 8);
  vint16m2_t zip = __riscv_vreinterpret_v_i32m2_i16m2(__riscv_vreinterpret_v_u32m2_i32m2(zip_u32));
  return __riscv_vcreate_v_i16m1x2(__riscv_vget_v_i16m2_i16m1(zip, 0),
                                   __riscv_vget_v_i16m2_i16m1(__riscv_vslidedown_vx_i16m2(zip, 8, 16), 0));
}

FORCE_INLINE int32x4x2_t vzipq_s32(int32x4_t a, int32x4_t b) {
  vuint32m1_t a_u32 = __riscv_vreinterpret_v_i32m1_u32m1(a);
  vuint32m1_t b_u32 = __riscv_vreinterpret_v_i32m1_u32m1(b);
  vuint64m2_t ab_waddu = __riscv_vwaddu_vv_u64m2(a_u32, b_u32, 4);
  vuint64m2_t zip_u64 = __riscv_vwmaccu_vx_u64m2(ab_waddu, UINT32_MAX, b_u32, 4);
  vint32m2_t zip = __riscv_vreinterpret_v_i64m2_i32m2(__riscv_vreinterpret_v_u64m2_i64m2(zip_u64));
  return __riscv_vcreate_v_i32m1x2(__riscv_vget_v_i32m2_i32m1(zip, 0),
                                   __riscv_vget_v_i32m2_i32m1(__riscv_vslidedown_vx_i32m2(zip, 4, 8), 0));
}

FORCE_INLINE float32x4x2_t vzipq_f32(float32x4_t a, float32x4_t b) {
  vuint32m1_t a_u32 = __riscv_vreinterpret_v_f32m1_u32m1(a);
  vuint32m1_t b_u32 = __riscv_vreinterpret_v_f32m1_u32m1(b);
  vuint64m2_t ab_waddu = __riscv_vwaddu_vv_u64m2(a_u32, b_u32, 4);
  vuint64m2_t zip_u64 = __riscv_vwmaccu_vx_u64m2(ab_waddu, UINT32_MAX, b_u32, 4);
  vfloat32m2_t zip = __riscv_vreinterpret_v_i32m2_f32m2(
      __riscv_vreinterpret_v_i64m2_i32m2(__riscv_vreinterpret_v_u64m2_i64m2(zip_u64)));
  return __riscv_vcreate_v_f32m1x2(__riscv_vget_v_f32m2_f32m1(zip, 0),
                                   __riscv_vget_v_f32m2_f32m1(__riscv_vslidedown_vx_f32m2(zip, 4, 8), 0));
}

FORCE_INLINE uint8x16x2_t vzipq_u8(uint8x16_t a, uint8x16_t b) {
  vuint16m2_t ab_waddu = __riscv_vwaddu_vv_u16m2(a, b, 16);
  vuint16m2_t zip_u16 = __riscv_vwmaccu_vx_u16m2(ab_waddu, UINT8_MAX, b, 16);
  vuint8m2_t zip = __riscv_vreinterpret_v_u16m2_u8m2(zip_u16);
  return __riscv_vcreate_v_u8m1x2(__riscv_vget_v_u8m2_u8m1(zip, 0),
                                  __riscv_vget_v_u8m2_u8m1(__riscv_vslidedown_vx_u8m2(zip, 16, 32), 0));
}

FORCE_INLINE uint16x8x2_t vzipq_u16(uint16x8_t a, uint16x8_t b) {
  vuint32m2_t ab_waddu = __riscv_vwaddu_vv_u32m2(a, b, 8);
  vuint32m2_t zip_u32 = __riscv_vwmaccu_vx_u32m2(ab_waddu, UINT16_MAX, b, 8);
  vuint16m2_t zip = __riscv_vreinterpret_v_u32m2_u16m2(zip_u32);
  return __riscv_vcreate_v_u16m1x2(__riscv_vget_v_u16m2_u16m1(zip, 0),
                                   __riscv_vget_v_u16m2_u16m1(__riscv_vslidedown_vx_u16m2(zip, 8, 16), 0));
}

FORCE_INLINE uint32x4x2_t vzipq_u32(uint32x4_t a, uint32x4_t b) {
  vuint64m2_t ab_waddu = __riscv_vwaddu_vv_u64m2(a, b, 4);
  vuint64m2_t zip_u64 = __riscv_vwmaccu_vx_u64m2(ab_waddu, UINT32_MAX, b, 4);
  vuint32m2_t zip = __riscv_vreinterpret_v_u64m2_u32m2(zip_u64);
  return __riscv_vcreate_v_u32m1x2(__riscv_vget_v_u32m2_u32m1(zip, 0),
                                   __riscv_vget_v_u32m2_u32m1(__riscv_vslidedown_vx_u32m2(zip, 4, 8), 0));
}

// FORCE_INLINE poly8x16x2_t vzipq_p8(poly8x16_t a, poly8x16_t b);

// FORCE_INLINE poly16x8x2_t vzipq_p16(poly16x8_t a, poly16x8_t b);

FORCE_INLINE int8x8x2_t vuzp_s8(int8x8_t a, int8x8_t b) {
  vint8m1_t ab = __riscv_vslideup_vx_i8m1(a, b, 8, 16);
  vint16m2_t ab_i16 = __riscv_vlmul_ext_v_i16m1_i16m2(__riscv_vreinterpret_v_i8m1_i16m1(ab));
  vint8m1_t uzp1 = __riscv_vnsra_wx_i8m1(ab_i16, 0, 8);
  vint8m1_t uzp2 = __riscv_vnsra_wx_i8m1(ab_i16, 8, 8);
  return __riscv_vcreate_v_i8m1x2(uzp1, uzp2);
}

FORCE_INLINE int16x4x2_t vuzp_s16(int16x4_t a, int16x4_t b) {
  vint16m1_t ab = __riscv_vslideup_vx_i16m1(a, b, 4, 8);
  vint32m2_t ab_i32 = __riscv_vlmul_ext_v_i32m1_i32m2(__riscv_vreinterpret_v_i16m1_i32m1(ab));
  vint16m1_t uzp1 = __riscv_vnsra_wx_i16m1(ab_i32, 0, 4);
  vint16m1_t uzp2 = __riscv_vnsra_wx_i16m1(ab_i32, 16, 4);
  return __riscv_vcreate_v_i16m1x2(uzp1, uzp2);
}

FORCE_INLINE int32x2x2_t vuzp_s32(int32x2_t a, int32x2_t b) {
  vint32m1_t ab = __riscv_vslideup_vx_i32m1(a, b, 2, 4);
  vint64m2_t ab_i64 = __riscv_vlmul_ext_v_i64m1_i64m2(__riscv_vreinterpret_v_i32m1_i64m1(ab));
  vint32m1_t uzp1 = __riscv_vnsra_wx_i32m1(ab_i64, 0, 2);
  vint32m1_t uzp2 = __riscv_vnsra_wx_i32m1(ab_i64, 32, 2);
  return __riscv_vcreate_v_i32m1x2(uzp1, uzp2);
}

FORCE_INLINE float32x2x2_t vuzp_f32(float32x2_t a, float32x2_t b) {
  vfloat32m1_t ab = __riscv_vslideup_vx_f32m1(a, b, 2, 4);
  vint64m2_t ab_i64 =
      __riscv_vlmul_ext_v_i64m1_i64m2(__riscv_vreinterpret_v_i32m1_i64m1(__riscv_vreinterpret_v_f32m1_i32m1(ab)));
  vfloat32m1_t uzp1 = __riscv_vreinterpret_v_i32m1_f32m1(__riscv_vnsra_wx_i32m1(ab_i64, 0, 2));
  vfloat32m1_t uzp2 = __riscv_vreinterpret_v_i32m1_f32m1(__riscv_vnsra_wx_i32m1(ab_i64, 32, 2));
  return __riscv_vcreate_v_f32m1x2(uzp1, uzp2);
}

FORCE_INLINE uint8x8x2_t vuzp_u8(uint8x8_t a, uint8x8_t b) {
  vuint8m1_t ab = __riscv_vslideup_vx_u8m1(a, b, 8, 16);
  vuint16m2_t ab_u16 = __riscv_vlmul_ext_v_u16m1_u16m2(__riscv_vreinterpret_v_u8m1_u16m1(ab));
  vuint8m1_t uzp1 = __riscv_vnsrl_wx_u8m1(ab_u16, 0, 8);
  vuint8m1_t uzp2 = __riscv_vnsrl_wx_u8m1(ab_u16, 8, 8);
  return __riscv_vcreate_v_u8m1x2(uzp1, uzp2);
}

FORCE_INLINE uint16x4x2_t vuzp_u16(uint16x4_t a, uint16x4_t b) {
  vuint16m1_t ab = __riscv_vslideup_vx_u16m1(a, b, 4, 8);
  vuint32m2_t ab_u32 = __riscv_vlmul_ext_v_u32m1_u32m2(__riscv_vreinterpret_v_u16m1_u32m1(ab));
  vuint16m1_t uzp1 = __riscv_vnsrl_wx_u16m1(ab_u32, 0, 4);
  vuint16m1_t uzp2 = __riscv_vnsrl_wx_u16m1(ab_u32, 16, 4);
  return __riscv_vcreate_v_u16m1x2(uzp1, uzp2);
}

FORCE_INLINE uint32x2x2_t vuzp_u32(uint32x2_t a, uint32x2_t b) {
  vuint32m1_t ab = __riscv_vslideup_vx_u32m1(a, b, 2, 4);
  vuint64m2_t ab_u64 = __riscv_vlmul_ext_v_u64m1_u64m2(__riscv_vreinterpret_v_u32m1_u64m1(ab));
  vuint32m1_t uzp1 = __riscv_vnsrl_wx_u32m1(ab_u64, 0, 2);
  vuint32m1_t uzp2 = __riscv_vnsrl_wx_u32m1(ab_u64, 32, 2);
  return __riscv_vcreate_v_u32m1x2(uzp1, uzp2);
}

// FORCE_INLINE poly8x8x2_t vuzp_p8(poly8x8_t a, poly8x8_t b);

// FORCE_INLINE poly16x4x2_t vuzp_p16(poly16x4_t a, poly16x4_t b);

FORCE_INLINE int8x16x2_t vuzpq_s8(int8x16_t a, int8x16_t b) {
  vint16m2_t ab =
      __riscv_vslideup_vx_i16m2(__riscv_vlmul_ext_v_i16m1_i16m2(__riscv_vreinterpret_v_i8m1_i16m1(a)),
                                __riscv_vlmul_ext_v_i16m1_i16m2(__riscv_vreinterpret_v_i8m1_i16m1(b)), 8, 16);
  vint8m1_t uzp1 = __riscv_vnsra_wx_i8m1(ab, 0, 16);
  vint8m1_t uzp2 = __riscv_vnsra_wx_i8m1(ab, 8, 16);
  return __riscv_vcreate_v_i8m1x2(uzp1, uzp2);
}

FORCE_INLINE int16x8x2_t vuzpq_s16(int16x8_t a, int16x8_t b) {
  vint32m2_t ab =
      __riscv_vslideup_vx_i32m2(__riscv_vlmul_ext_v_i32m1_i32m2(__riscv_vreinterpret_v_i16m1_i32m1(a)),
                                __riscv_vlmul_ext_v_i32m1_i32m2(__riscv_vreinterpret_v_i16m1_i32m1(b)), 4, 8);
  vint16m1_t uzp1 = __riscv_vnsra_wx_i16m1(ab, 0, 8);
  vint16m1_t uzp2 = __riscv_vnsra_wx_i16m1(ab, 16, 8);
  return __riscv_vcreate_v_i16m1x2(uzp1, uzp2);
}

FORCE_INLINE int32x4x2_t vuzpq_s32(int32x4_t a, int32x4_t b) {
  vint64m2_t ab =
      __riscv_vslideup_vx_i64m2(__riscv_vlmul_ext_v_i64m1_i64m2(__riscv_vreinterpret_v_i32m1_i64m1(a)),
                                __riscv_vlmul_ext_v_i64m1_i64m2(__riscv_vreinterpret_v_i32m1_i64m1(b)), 2, 4);
  vint32m1_t uzp1 = __riscv_vnsra_wx_i32m1(ab, 0, 4);
  vint32m1_t uzp2 = __riscv_vnsra_wx_i32m1(ab, 32, 4);
  return __riscv_vcreate_v_i32m1x2(uzp1, uzp2);
}

FORCE_INLINE float32x4x2_t vuzpq_f32(float32x4_t a, float32x4_t b) {
  vint64m2_t ab = __riscv_vslideup_vx_i64m2(
      __riscv_vlmul_ext_v_i64m1_i64m2(__riscv_vreinterpret_v_i32m1_i64m1(__riscv_vreinterpret_v_f32m1_i32m1(a))),
      __riscv_vlmul_ext_v_i64m1_i64m2(__riscv_vreinterpret_v_i32m1_i64m1(__riscv_vreinterpret_v_f32m1_i32m1(b))), 2, 4);
  vfloat32m1_t uzp1 = __riscv_vreinterpret_v_i32m1_f32m1(__riscv_vnsra_wx_i32m1(ab, 0, 4));
  vfloat32m1_t uzp2 = __riscv_vreinterpret_v_i32m1_f32m1(__riscv_vnsra_wx_i32m1(ab, 32, 4));
  return __riscv_vcreate_v_f32m1x2(uzp1, uzp2);
}

FORCE_INLINE uint8x16x2_t vuzpq_u8(uint8x16_t a, uint8x16_t b) {
  vuint16m2_t ab =
      __riscv_vslideup_vx_u16m2(__riscv_vlmul_ext_v_u16m1_u16m2(__riscv_vreinterpret_v_u8m1_u16m1(a)),
                                __riscv_vlmul_ext_v_u16m1_u16m2(__riscv_vreinterpret_v_u8m1_u16m1(b)), 8, 16);
  vuint8m1_t uzp1 = __riscv_vnsrl_wx_u8m1(ab, 0, 16);
  vuint8m1_t uzp2 = __riscv_vnsrl_wx_u8m1(ab, 8, 16);
  return __riscv_vcreate_v_u8m1x2(uzp1, uzp2);
}

FORCE_INLINE uint16x8x2_t vuzpq_u16(uint16x8_t a, uint16x8_t b) {
  vuint32m2_t ab =
      __riscv_vslideup_vx_u32m2(__riscv_vlmul_ext_v_u32m1_u32m2(__riscv_vreinterpret_v_u16m1_u32m1(a)),
                                __riscv_vlmul_ext_v_u32m1_u32m2(__riscv_vreinterpret_v_u16m1_u32m1(b)), 4, 8);
  vuint16m1_t uzp1 = __riscv_vnsrl_wx_u16m1(ab, 0, 8);
  vuint16m1_t uzp2 = __riscv_vnsrl_wx_u16m1(ab, 16, 8);
  return __riscv_vcreate_v_u16m1x2(uzp1, uzp2);
}

FORCE_INLINE uint32x4x2_t vuzpq_u32(uint32x4_t a, uint32x4_t b) {
  vuint64m2_t ab =
      __riscv_vslideup_vx_u64m2(__riscv_vlmul_ext_v_u64m1_u64m2(__riscv_vreinterpret_v_u32m1_u64m1(a)),
                                __riscv_vlmul_ext_v_u64m1_u64m2(__riscv_vreinterpret_v_u32m1_u64m1(b)), 2, 4);
  vuint32m1_t uzp1 = __riscv_vnsrl_wx_u32m1(ab, 0, 4);
  vuint32m1_t uzp2 = __riscv_vnsrl_wx_u32m1(ab, 32, 4);
  return __riscv_vcreate_v_u32m1x2(uzp1, uzp2);
}

// FORCE_INLINE poly8x16x2_t vuzpq_p8(poly8x16_t a, poly8x16_t b);

// FORCE_INLINE poly16x8x2_t vuzpq_p16(poly16x8_t a, poly16x8_t b);

FORCE_INLINE int8x8_t vld1_s8(const int8_t *ptr) { return __riscv_vle8_v_i8m1(ptr, 8); }

FORCE_INLINE int16x4_t vld1_s16(const int16_t *ptr) { return __riscv_vle16_v_i16m1(ptr, 4); }

FORCE_INLINE int32x2_t vld1_s32(const int32_t *ptr) { return __riscv_vle32_v_i32m1(ptr, 2); }

FORCE_INLINE int64x1_t vld1_s64(const int64_t *ptr) { return __riscv_vle64_v_i64m1(ptr, 1); }

FORCE_INLINE float32x2_t vld1_f32(const float32_t *ptr) { return __riscv_vle32_v_f32m1(ptr, 2); }

FORCE_INLINE uint8x8_t vld1_u8(const uint8_t *ptr) { return __riscv_vle8_v_u8m1(ptr, 8); }

FORCE_INLINE uint16x4_t vld1_u16(const uint16_t *ptr) { return __riscv_vle16_v_u16m1(ptr, 4); }

FORCE_INLINE uint32x2_t vld1_u32(const uint32_t *ptr) { return __riscv_vle32_v_u32m1(ptr, 2); }

FORCE_INLINE uint64x1_t vld1_u64(const uint64_t *ptr) { return __riscv_vle64_v_u64m1(ptr, 1); }

FORCE_INLINE int8x16_t vld1q_s8(const int8_t *ptr) { return __riscv_vle8_v_i8m1(ptr, 16); }

FORCE_INLINE int16x8_t vld1q_s16(const int16_t *ptr) { return __riscv_vle16_v_i16m1(ptr, 8); }

FORCE_INLINE int32x4_t vld1q_s32(const int32_t *ptr) { return __riscv_vle32_v_i32m1(ptr, 4); }

FORCE_INLINE int64x2_t vld1q_s64(const int64_t *ptr) { return __riscv_vle64_v_i64m1(ptr, 2); }

FORCE_INLINE float32x4_t vld1q_f32(const float32_t *ptr) { return __riscv_vle32_v_f32m1(ptr, 4); }

// FORCE_INLINE poly8x8_t vld1_p8(poly8_t const * ptr);

// FORCE_INLINE poly8x16_t vld1q_p8(poly8_t const * ptr);

// FORCE_INLINE poly16x4_t vld1_p16(poly16_t const * ptr);

// FORCE_INLINE poly16x8_t vld1q_p16(poly16_t const * ptr);

FORCE_INLINE float64x1_t vld1_f64(float64_t const *ptr) { return __riscv_vle64_v_f64m1(ptr, 1); }

FORCE_INLINE float64x2_t vld1q_f64(float64_t const *ptr) { return __riscv_vle64_v_f64m1(ptr, 2); }

FORCE_INLINE uint8x16_t vld1q_u8(const uint8_t *ptr) { return __riscv_vle8_v_u8m1(ptr, 16); }

FORCE_INLINE uint16x8_t vld1q_u16(const uint16_t *ptr) { return __riscv_vle16_v_u16m1(ptr, 8); }

FORCE_INLINE uint32x4_t vld1q_u32(const uint32_t *ptr) { return __riscv_vle32_v_u32m1(ptr, 4); }

FORCE_INLINE uint64x2_t vld1q_u64(const uint64_t *ptr) { return __riscv_vle64_v_u64m1(ptr, 2); }

// FORCE_INLINE poly64x1_t vld1_p64(poly64_t const * ptr);

// FORCE_INLINE poly64x2_t vld1q_p64(poly64_t const * ptr);

// FORCE_INLINE float16x4_t vld1_f16(float16_t const * ptr);

// FORCE_INLINE float16x8_t vld1q_f16(float16_t const * ptr);

FORCE_INLINE int8x8_t vld1_lane_s8(const int8_t *a, int8x8_t b, const int lane) {
  vbool8_t mask = __riscv_vreinterpret_v_u8m1_b8(vdup_n_u8((uint8_t)(1 << lane)));
  vint8m1_t a_dup = vdup_n_s8(a[0]);
  return __riscv_vmerge_vvm_i8m1(b, a_dup, mask, 8);
}

FORCE_INLINE int16x4_t vld1_lane_s16(const int16_t *a, int16x4_t b, const int lane) {
  vbool16_t mask = __riscv_vreinterpret_v_u8m1_b16(vdup_n_u8((uint8_t)(1 << lane)));
  vint16m1_t a_dup = vdup_n_s16(a[0]);
  return __riscv_vmerge_vvm_i16m1(b, a_dup, mask, 4);
}

FORCE_INLINE int32x2_t vld1_lane_s32(const int32_t *a, int32x2_t b, const int lane) {
  vbool32_t mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << lane)));
  vint32m1_t a_dup = vdup_n_s32(a[0]);
  return __riscv_vmerge_vvm_i32m1(b, a_dup, mask, 2);
}

FORCE_INLINE float32x2_t vld1_lane_f32(const float32_t *a, float32x2_t b, const int lane) {
  vbool32_t mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << lane)));
  vfloat32m1_t a_dup = vdup_n_f32(a[0]);
  return __riscv_vmerge_vvm_f32m1(b, a_dup, mask, 2);
}

FORCE_INLINE uint8x8_t vld1_lane_u8(const uint8_t *a, uint8x8_t b, const int lane) {
  vbool8_t mask = __riscv_vreinterpret_v_u8m1_b8(vdup_n_u8((uint8_t)(1 << lane)));
  vuint8m1_t a_dup = vdup_n_u8(a[0]);
  return __riscv_vmerge_vvm_u8m1(b, a_dup, mask, 8);
}

FORCE_INLINE uint16x4_t vld1_lane_u16(const uint16_t *a, uint16x4_t b, const int lane) {
  vbool16_t mask = __riscv_vreinterpret_v_u8m1_b16(vdup_n_u8((uint8_t)(1 << lane)));
  vuint16m1_t a_dup = vdup_n_u16(a[0]);
  return __riscv_vmerge_vvm_u16m1(b, a_dup, mask, 4);
}

FORCE_INLINE uint32x2_t vld1_lane_u32(const uint32_t *a, uint32x2_t b, const int lane) {
  vbool32_t mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << lane)));
  vuint32m1_t a_dup = vdup_n_u32(a[0]);
  return __riscv_vmerge_vvm_u32m1(b, a_dup, mask, 2);
}

FORCE_INLINE int64x1_t vld1_lane_s64(const int64_t *a, int64x1_t b, const int lane) {
  vbool64_t mask = __riscv_vreinterpret_v_u8m1_b64(vdup_n_u8((uint8_t)(1 << lane)));
  vint64m1_t a_dup = vdup_n_s64(a[0]);
  return __riscv_vmerge_vvm_i64m1(b, a_dup, mask, 1);
}

FORCE_INLINE uint64x1_t vld1_lane_u64(const uint64_t *a, uint64x1_t b, const int lane) {
  vbool64_t mask = __riscv_vreinterpret_v_u8m1_b64(vdup_n_u8((uint8_t)(1 << lane)));
  vuint64m1_t a_dup = vdup_n_u64(a[0]);
  return __riscv_vmerge_vvm_u64m1(b, a_dup, mask, 1);
}

FORCE_INLINE int8x16_t vld1q_lane_s8(const int8_t *a, int8x16_t b, const int lane) {
  vbool8_t mask = __riscv_vreinterpret_v_u16m1_b8(vdup_n_u16((uint16_t)(1 << lane)));
  vint8m1_t a_dup = vdupq_n_s8(a[0]);
  return __riscv_vmerge_vvm_i8m1(b, a_dup, mask, 16);
}

FORCE_INLINE int16x8_t vld1q_lane_s16(const int16_t *a, int16x8_t b, const int lane) {
  vbool16_t mask = __riscv_vreinterpret_v_u8m1_b16(vdup_n_u8((uint8_t)(1 << lane)));
  vint16m1_t a_dup = vdupq_n_s16(a[0]);
  return __riscv_vmerge_vvm_i16m1(b, a_dup, mask, 8);
}

FORCE_INLINE int32x4_t vld1q_lane_s32(const int32_t *a, int32x4_t b, const int lane) {
  vbool32_t mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << lane)));
  vint32m1_t a_dup = vdupq_n_s32(a[0]);
  return __riscv_vmerge_vvm_i32m1(b, a_dup, mask, 4);
}

FORCE_INLINE float32x4_t vld1q_lane_f32(const float32_t *a, float32x4_t b, const int lane) {
  vbool32_t mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << lane)));
  vfloat32m1_t a_dup = vdupq_n_f32(a[0]);
  return __riscv_vmerge_vvm_f32m1(b, a_dup, mask, 4);
}

// FORCE_INLINE poly8x8_t vld1_lane_p8(poly8_t const * ptr, poly8x8_t src, const int lane);

// FORCE_INLINE poly8x16_t vld1q_lane_p8(poly8_t const * ptr, poly8x16_t src, const int lane);

// FORCE_INLINE poly16x4_t vld1_lane_p16(poly16_t const * ptr, poly16x4_t src, const int lane);

// FORCE_INLINE poly16x8_t vld1q_lane_p16(poly16_t const * ptr, poly16x8_t src, const int lane);

FORCE_INLINE float64x1_t vld1_lane_f64(float64_t const *a, float64x1_t b, const int lane) {
  vbool64_t mask = __riscv_vreinterpret_v_u8m1_b64(vdup_n_u8((uint8_t)(1 << lane)));
  vfloat64m1_t a_dup = vdup_n_f64(a[0]);
  return __riscv_vmerge_vvm_f64m1(b, a_dup, mask, 1);
}

FORCE_INLINE float64x2_t vld1q_lane_f64(float64_t const *a, float64x2_t b, const int lane) {
  vbool64_t mask = __riscv_vreinterpret_v_u8m1_b64(vdup_n_u8((uint8_t)(1 << lane)));
  vfloat64m1_t a_dup = vdupq_n_f64(a[0]);
  return __riscv_vmerge_vvm_f64m1(b, a_dup, mask, 2);
}

FORCE_INLINE uint8x16_t vld1q_lane_u8(const uint8_t *a, uint8x16_t b, const int lane) {
  vbool8_t mask = __riscv_vreinterpret_v_u16m1_b8(vdup_n_u16((uint16_t)(1 << lane)));
  vuint8m1_t a_dup = vdupq_n_u8(a[0]);
  return __riscv_vmerge_vvm_u8m1(b, a_dup, mask, 16);
}

FORCE_INLINE uint16x8_t vld1q_lane_u16(const uint16_t *a, uint16x8_t b, const int lane) {
  vbool16_t mask = __riscv_vreinterpret_v_u8m1_b16(vdup_n_u8((uint8_t)(1 << lane)));
  vuint16m1_t a_dup = vdupq_n_u16(a[0]);
  return __riscv_vmerge_vvm_u16m1(b, a_dup, mask, 8);
}

FORCE_INLINE uint32x4_t vld1q_lane_u32(const uint32_t *a, uint32x4_t b, const int lane) {
  vbool32_t mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << lane)));
  vuint32m1_t a_dup = vdupq_n_u32(a[0]);
  return __riscv_vmerge_vvm_u32m1(b, a_dup, mask, 4);
}

FORCE_INLINE int64x2_t vld1q_lane_s64(const int64_t *a, int64x2_t b, const int lane) {
  vbool64_t mask = __riscv_vreinterpret_v_u8m1_b64(vdup_n_u8((uint8_t)(1 << lane)));
  vint64m1_t a_dup = vdupq_n_s64(a[0]);
  return __riscv_vmerge_vvm_i64m1(b, a_dup, mask, 2);
}

FORCE_INLINE uint64x2_t vld1q_lane_u64(const uint64_t *a, uint64x2_t b, const int lane) {
  vbool64_t mask = __riscv_vreinterpret_v_u8m1_b64(vdup_n_u8((uint8_t)(1 << lane)));
  vuint64m1_t a_dup = vdupq_n_u64(a[0]);
  return __riscv_vmerge_vvm_u64m1(b, a_dup, mask, 2);
}

// FORCE_INLINE poly64x1_t vld1_lane_p64(poly64_t const * ptr, poly64x1_t src, const int lane);

// FORCE_INLINE poly64x2_t vld1q_lane_p64(poly64_t const * ptr, poly64x2_t src, const int lane);

// FORCE_INLINE float16x4_t vld1_lane_f16(float16_t const * ptr, float16x4_t src, const int lane);

// FORCE_INLINE float16x8_t vld1q_lane_f16(float16_t const * ptr, float16x8_t src, const int lane);

FORCE_INLINE int8x8_t vld1_dup_s8(const int8_t *a) { return vdup_n_s8(a[0]); }

FORCE_INLINE int16x4_t vld1_dup_s16(const int16_t *a) { return vdup_n_s16(a[0]); }

FORCE_INLINE int32x2_t vld1_dup_s32(const int32_t *a) { return vdup_n_s32(a[0]); }

FORCE_INLINE float32x2_t vld1_dup_f32(const float32_t *a) { return vdup_n_f32(a[0]); }

FORCE_INLINE uint8x8_t vld1_dup_u8(const uint8_t *a) { return vdup_n_u8(a[0]); }

FORCE_INLINE uint16x4_t vld1_dup_u16(const uint16_t *a) { return vdup_n_u16(a[0]); }

FORCE_INLINE uint32x2_t vld1_dup_u32(const uint32_t *a) { return vdup_n_u32(a[0]); }

FORCE_INLINE int64x1_t vld1_dup_s64(const int64_t *a) { return vdup_n_s64(a[0]); }

FORCE_INLINE uint64x1_t vld1_dup_u64(const uint64_t *a) { return vdup_n_u64(a[0]); }

FORCE_INLINE int8x16_t vld1q_dup_s8(const int8_t *a) { return vdupq_n_s8(a[0]); }

FORCE_INLINE int16x8_t vld1q_dup_s16(const int16_t *a) { return vdupq_n_s16(a[0]); }

FORCE_INLINE int32x4_t vld1q_dup_s32(const int32_t *a) { return vdupq_n_s32(a[0]); }

FORCE_INLINE float32x4_t vld1q_dup_f32(const float32_t *a) { return vdupq_n_f32(a[0]); }

// FORCE_INLINE poly8x8_t vld1_dup_p8(poly8_t const * ptr);

// FORCE_INLINE poly8x16_t vld1q_dup_p8(poly8_t const * ptr);

// FORCE_INLINE poly16x4_t vld1_dup_p16(poly16_t const * ptr);

// FORCE_INLINE poly16x8_t vld1q_dup_p16(poly16_t const * ptr);

FORCE_INLINE float64x1_t vld1_dup_f64(float64_t const *a) { return vdup_n_f64(a[0]); }

FORCE_INLINE float64x2_t vld1q_dup_f64(float64_t const *a) { return vdupq_n_f64(a[0]); }

FORCE_INLINE uint8x16_t vld1q_dup_u8(const uint8_t *a) { return vdupq_n_u8(a[0]); }

FORCE_INLINE uint16x8_t vld1q_dup_u16(const uint16_t *a) { return vdupq_n_u16(a[0]); }

FORCE_INLINE uint32x4_t vld1q_dup_u32(const uint32_t *a) { return vdupq_n_u32(a[0]); }

FORCE_INLINE int64x2_t vld1q_dup_s64(const int64_t *a) { return vdupq_n_s64(a[0]); }

FORCE_INLINE uint64x2_t vld1q_dup_u64(const uint64_t *a) { return vdupq_n_u64(a[0]); }

// FORCE_INLINE poly64x1_t vld1_dup_p64(poly64_t const * ptr);

// FORCE_INLINE poly64x2_t vld1q_dup_p64(poly64_t const * ptr);

// FORCE_INLINE float16x4_t vld1_dup_f16(float16_t const * ptr);

// FORCE_INLINE float16x8_t vld1q_dup_f16(float16_t const * ptr);

FORCE_INLINE void vst1_s8(int8_t *a, int8x8_t b) { __riscv_vse8_v_i8m1(a, b, 8); }

FORCE_INLINE void vst1_s16(int16_t *a, int16x4_t b) { __riscv_vse16_v_i16m1(a, b, 4); }

FORCE_INLINE void vst1_s32(int32_t *a, int32x2_t b) { __riscv_vse32_v_i32m1(a, b, 2); }

FORCE_INLINE void vst1_s64(int64_t *a, int64x1_t b) { __riscv_vse64_v_i64m1(a, b, 1); }

FORCE_INLINE void vst1_f32(float32_t *a, float32x2_t b) { __riscv_vse32_v_f32m1(a, b, 2); }

FORCE_INLINE void vst1_u8(uint8_t *a, uint8x8_t b) { __riscv_vse8_v_u8m1(a, b, 8); }

FORCE_INLINE void vst1_u16(uint16_t *a, uint16x4_t b) { __riscv_vse16_v_u16m1(a, b, 4); }

FORCE_INLINE void vst1_u32(uint32_t *a, uint32x2_t b) { __riscv_vse32_v_u32m1(a, b, 2); }

FORCE_INLINE void vst1_u64(uint64_t *a, uint64x1_t b) { __riscv_vse64_v_u64m1(a, b, 1); }

FORCE_INLINE void vst1q_s8(int8_t *a, int8x16_t b) { __riscv_vse8_v_i8m1(a, b, 16); }

FORCE_INLINE void vst1q_s16(int16_t *a, int16x8_t b) { __riscv_vse16_v_i16m1(a, b, 8); }

FORCE_INLINE void vst1q_s32(int32_t *a, int32x4_t b) { __riscv_vse32_v_i32m1(a, b, 4); }

FORCE_INLINE void vst1q_s64(int64_t *a, int64x2_t b) { __riscv_vse64_v_i64m1(a, b, 2); }

FORCE_INLINE void vst1q_f32(float32_t *a, float32x4_t b) { __riscv_vse32_v_f32m1(a, b, 4); }

// FORCE_INLINE void vst1_p8(poly8_t * ptr, poly8x8_t val);

// FORCE_INLINE void vst1q_p8(poly8_t * ptr, poly8x16_t val);

// FORCE_INLINE void vst1_p16(poly16_t * ptr, poly16x4_t val);

// FORCE_INLINE void vst1q_p16(poly16_t * ptr, poly16x8_t val);

// FORCE_INLINE void vst1_f64(float64_t * ptr, float64x1_t val);

// FORCE_INLINE void vst1q_f64(float64_t * ptr, float64x2_t val);

FORCE_INLINE void vst1q_u8(uint8_t *a, uint8x16_t b) { __riscv_vse8_v_u8m1(a, b, 16); }

FORCE_INLINE void vst1q_u16(uint16_t *a, uint16x8_t b) { __riscv_vse16_v_u16m1(a, b, 8); }

FORCE_INLINE void vst1q_u32(uint32_t *a, uint32x4_t b) { __riscv_vse32_v_u32m1(a, b, 4); }

FORCE_INLINE void vst1q_u64(uint64_t *a, uint64x2_t b) { __riscv_vse64_v_u64m1(a, b, 2); }

// FORCE_INLINE void vst1_p64(poly64_t * ptr, poly64x1_t val);

// FORCE_INLINE void vst1q_p64(poly64_t * ptr, poly64x2_t val);

// FORCE_INLINE void vst1_f16(float16_t * ptr, float16x4_t val);

// FORCE_INLINE void vst1q_f16(float16_t * ptr, float16x8_t val);

FORCE_INLINE void vst1_lane_s8(int8_t *a, int8x8_t b, const int lane) {
  vint8m1_t b_s = __riscv_vslidedown_vx_i8m1(b, lane, 8);
  *a = __riscv_vmv_x_s_i8m1_i8(b_s);
}

FORCE_INLINE void vst1_lane_s16(int16_t *a, int16x4_t b, const int lane) {
  vint16m1_t b_s = __riscv_vslidedown_vx_i16m1(b, lane, 4);
  *a = __riscv_vmv_x_s_i16m1_i16(b_s);
}

FORCE_INLINE void vst1_lane_s32(int32_t *a, int32x2_t b, const int lane) {
  vint32m1_t b_s = __riscv_vslidedown_vx_i32m1(b, lane, 2);
  *a = __riscv_vmv_x_s_i32m1_i32(b_s);
}

FORCE_INLINE void vst1_lane_f32(float32_t *a, float32x2_t b, const int lane) {
  vfloat32m1_t b_s = __riscv_vslidedown_vx_f32m1(b, lane, 2);
  *a = __riscv_vfmv_f_s_f32m1_f32(b_s);
}

FORCE_INLINE void vst1_lane_u8(uint8_t *a, uint8x8_t b, const int lane) {
  vuint8m1_t b_s = __riscv_vslidedown_vx_u8m1(b, lane, 8);
  *a = __riscv_vmv_x_s_u8m1_u8(b_s);
}

FORCE_INLINE void vst1_lane_u16(uint16_t *a, uint16x4_t b, const int lane) {
  vuint16m1_t b_s = __riscv_vslidedown_vx_u16m1(b, lane, 4);
  *a = __riscv_vmv_x_s_u16m1_u16(b_s);
}

FORCE_INLINE void vst1_lane_u32(uint32_t *a, uint32x2_t b, const int lane) {
  vuint32m1_t b_s = __riscv_vslidedown_vx_u32m1(b, lane, 2);
  *a = __riscv_vmv_x_s_u32m1_u32(b_s);
}

FORCE_INLINE void vst1_lane_s64(int64_t *a, int64x1_t b, const int lane) {
  vint64m1_t b_s = __riscv_vslidedown_vx_i64m1(b, lane, 1);
  *a = __riscv_vmv_x_s_i64m1_i64(b_s);
}

FORCE_INLINE void vst1_lane_u64(uint64_t *a, uint64x1_t b, const int lane) {
  vuint64m1_t b_s = __riscv_vslidedown_vx_u64m1(b, lane, 1);
  *a = __riscv_vmv_x_s_u64m1_u64(b_s);
}

FORCE_INLINE void vst1q_lane_s8(int8_t *a, int8x16_t b, const int lane) {
  int8x8_t b_s = __riscv_vslidedown_vx_i8m1(b, lane, 8);
  *a = __riscv_vmv_x_s_i8m1_i8(b_s);
}

FORCE_INLINE void vst1q_lane_s16(int16_t *a, int16x8_t b, const int lane) {
  vint16m1_t b_s = __riscv_vslidedown_vx_i16m1(b, lane, 4);
  *a = __riscv_vmv_x_s_i16m1_i16(b_s);
}

FORCE_INLINE void vst1q_lane_s32(int32_t *a, int32x4_t b, const int lane) {
  vint32m1_t b_s = __riscv_vslidedown_vx_i32m1(b, lane, 4);
  *a = __riscv_vmv_x_s_i32m1_i32(b_s);
}

FORCE_INLINE void vst1q_lane_f32(float32_t *a, float32x4_t b, const int lane) {
  vfloat32m1_t b_s = __riscv_vslidedown_vx_f32m1(b, lane, 4);
  *a = __riscv_vfmv_f_s_f32m1_f32(b_s);
}

// FORCE_INLINE void vst1_lane_p8(poly8_t * ptr, poly8x8_t val, const int lane);

// FORCE_INLINE void vst1q_lane_p8(poly8_t * ptr, poly8x16_t val, const int lane);

// FORCE_INLINE void vst1_lane_p16(poly16_t * ptr, poly16x4_t val, const int lane);

// FORCE_INLINE void vst1q_lane_p16(poly16_t * ptr, poly16x8_t val, const int lane);

FORCE_INLINE void vst1_lane_f64(float64_t *a, float64x1_t b, const int lane) {
  vfloat64m1_t b_s = __riscv_vslidedown_vx_f64m1(b, lane, 1);
  *a = __riscv_vfmv_f_s_f64m1_f64(b_s);
}

FORCE_INLINE void vst1q_lane_f64(float64_t *a, float64x2_t b, const int lane) {
  vfloat64m1_t b_s = __riscv_vslidedown_vx_f64m1(b, lane, 2);
  *a = __riscv_vfmv_f_s_f64m1_f64(b_s);
}

FORCE_INLINE void vst1q_lane_u8(uint8_t *a, uint8x16_t b, const int c) {
  vuint8m1_t b_s = __riscv_vslidedown_vx_u8m1(b, c, 8);
  *a = __riscv_vmv_x_s_u8m1_u8(b_s);
}

FORCE_INLINE void vst1q_lane_u16(uint16_t *a, uint16x8_t b, const int c) {
  vuint16m1_t b_s = __riscv_vslidedown_vx_u16m1(b, c, 4);
  *a = __riscv_vmv_x_s_u16m1_u16(b_s);
}

FORCE_INLINE void vst1q_lane_u32(uint32_t *a, uint32x4_t b, const int c) {
  vuint32m1_t b_s = __riscv_vslidedown_vx_u32m1(b, c, 4);
  *a = __riscv_vmv_x_s_u32m1_u32(b_s);
}

FORCE_INLINE void vst1q_lane_s64(int64_t *a, int64x2_t b, const int c) {
  vint64m1_t b_s = __riscv_vslidedown_vx_i64m1(b, c, 1);
  *a = __riscv_vmv_x_s_i64m1_i64(b_s);
}

FORCE_INLINE void vst1q_lane_u64(uint64_t *a, uint64x2_t b, const int c) {
  vuint64m1_t b_s = __riscv_vslidedown_vx_u64m1(b, c, 1);
  *a = __riscv_vmv_x_s_u64m1_u64(b_s);
}

// FORCE_INLINE void vst1_lane_p64(poly64_t * ptr, poly64x1_t val, const int lane);

// FORCE_INLINE void vst1q_lane_p64(poly64_t * ptr, poly64x2_t val, const int lane);

// FORCE_INLINE void vst1_lane_f16(float16_t * ptr, float16x4_t val, const int lane);

// FORCE_INLINE void vst1q_lane_f16(float16_t * ptr, float16x8_t val, const int lane);

FORCE_INLINE int8x8x2_t vld2_s8(const int8_t *a) { return __riscv_vlseg2e8_v_i8m1x2(a, 8); }

FORCE_INLINE int16x4x2_t vld2_s16(const int16_t *a) { return __riscv_vlseg2e16_v_i16m1x2(a, 4); }

FORCE_INLINE int32x2x2_t vld2_s32(const int32_t *a) { return __riscv_vlseg2e32_v_i32m1x2(a, 2); }

FORCE_INLINE float32x2x2_t vld2_f32(const float32_t *a) { return __riscv_vlseg2e32_v_f32m1x2(a, 2); }

FORCE_INLINE uint8x8x2_t vld2_u8(const uint8_t *a) { return __riscv_vlseg2e8_v_u8m1x2(a, 8); }

FORCE_INLINE uint16x4x2_t vld2_u16(const uint16_t *a) { return __riscv_vlseg2e16_v_u16m1x2(a, 4); }

FORCE_INLINE uint32x2x2_t vld2_u32(const uint32_t *a) { return __riscv_vlseg2e32_v_u32m1x2(a, 2); }

FORCE_INLINE int64x1x2_t vld2_s64(const int64_t *a) { return __riscv_vlseg2e64_v_i64m1x2(a, 1); }

FORCE_INLINE uint64x1x2_t vld2_u64(const uint64_t *a) { return __riscv_vlseg2e64_v_u64m1x2(a, 1); }

// FORCE_INLINE poly64x1x2_t vld2_p64(poly64_t const * a);

FORCE_INLINE int64x2x2_t vld2q_s64(int64_t const *a) { return __riscv_vlseg2e64_v_i64m1x2(a, 2); }

FORCE_INLINE uint64x2x2_t vld2q_u64(uint64_t const *a) { return __riscv_vlseg2e64_v_u64m1x2(a, 2); }

// FORCE_INLINE poly64x2x2_t vld2q_p64(poly64_t const * a);

FORCE_INLINE float64x1x2_t vld2_f64(float64_t const *a) { return __riscv_vlseg2e64_v_f64m1x2(a, 1); }

FORCE_INLINE float64x2x2_t vld2q_f64(float64_t const *a) { return __riscv_vlseg2e64_v_f64m1x2(a, 2); }

FORCE_INLINE int8x16x2_t vld2q_s8(const int8_t *a) { return __riscv_vlseg2e8_v_i8m1x2(a, 16); }

FORCE_INLINE int16x8x2_t vld2q_s16(const int16_t *a) { return __riscv_vlseg2e16_v_i16m1x2(a, 8); }

FORCE_INLINE int32x4x2_t vld2q_s32(const int32_t *a) { return __riscv_vlseg2e32_v_i32m1x2(a, 4); }

FORCE_INLINE float32x4x2_t vld2q_f32(const float32_t *a) { return __riscv_vlseg2e32_v_f32m1x2(a, 4); }

// FORCE_INLINE poly8x8x2_t vld2_p8(poly8_t const * ptr);

// FORCE_INLINE poly8x16x2_t vld2q_p8(poly8_t const * ptr);

// FORCE_INLINE poly16x4x2_t vld2_p16(poly16_t const * ptr);

// FORCE_INLINE poly16x8x2_t vld2q_p16(poly16_t const * ptr);

FORCE_INLINE uint8x16x2_t vld2q_u8(const uint8_t *a) { return __riscv_vlseg2e8_v_u8m1x2(a, 16); }

FORCE_INLINE uint16x8x2_t vld2q_u16(const uint16_t *a) { return __riscv_vlseg2e16_v_u16m1x2(a, 8); }

FORCE_INLINE uint32x4x2_t vld2q_u32(const uint32_t *a) { return __riscv_vlseg2e32_v_u32m1x2(a, 4); }

// FORCE_INLINE float16x4x2_t vld2_f16(float16_t const * ptr);

// FORCE_INLINE float16x8x2_t vld2q_f16(float16_t const * ptr);

FORCE_INLINE int8x8x2_t vld2_lane_s8(const int8_t *a, int8x8x2_t b, const int c) {
  vbool8_t mask = __riscv_vreinterpret_v_u8m1_b8(vdup_n_u8((uint8_t)(1 << c)));
  vint8m1_t c0 = __riscv_vmerge_vxm_i8m1(__riscv_vget_v_i8m1x2_i8m1(b, 0), a[0], mask, 8);
  vint8m1_t c1 = __riscv_vmerge_vxm_i8m1(__riscv_vget_v_i8m1x2_i8m1(b, 1), a[1], mask, 8);
  return __riscv_vcreate_v_i8m1x2(c0, c1);
}

FORCE_INLINE int16x4x2_t vld2_lane_s16(const int16_t *a, int16x4x2_t b, const int c) {
  vbool16_t mask = __riscv_vreinterpret_v_u16m1_b16(vdup_n_u16((uint8_t)(1 << c)));
  vint16m1_t c0 = __riscv_vmerge_vxm_i16m1(__riscv_vget_v_i16m1x2_i16m1(b, 0), a[0], mask, 4);
  vint16m1_t c1 = __riscv_vmerge_vxm_i16m1(__riscv_vget_v_i16m1x2_i16m1(b, 1), a[1], mask, 4);
  return __riscv_vcreate_v_i16m1x2(c0, c1);
}

FORCE_INLINE int32x2x2_t vld2_lane_s32(const int32_t *a, int32x2x2_t b, const int c) {
  vbool32_t mask = __riscv_vreinterpret_v_u32m1_b32(vdup_n_u32((uint8_t)(1 << c)));
  vint32m1_t c0 = __riscv_vmerge_vxm_i32m1(__riscv_vget_v_i32m1x2_i32m1(b, 0), a[0], mask, 2);
  vint32m1_t c1 = __riscv_vmerge_vxm_i32m1(__riscv_vget_v_i32m1x2_i32m1(b, 1), a[1], mask, 2);
  return __riscv_vcreate_v_i32m1x2(c0, c1);
}

FORCE_INLINE float32x2x2_t vld2_lane_f32(const float32_t *a, float32x2x2_t b, const int c) {
  vbool32_t mask = __riscv_vreinterpret_v_u32m1_b32(vdup_n_u32((uint8_t)(1 << c)));
  vfloat32m1_t c0 = __riscv_vfmerge_vfm_f32m1(__riscv_vget_v_f32m1x2_f32m1(b, 0), a[0], mask, 2);
  vfloat32m1_t c1 = __riscv_vfmerge_vfm_f32m1(__riscv_vget_v_f32m1x2_f32m1(b, 1), a[1], mask, 2);
  return __riscv_vcreate_v_f32m1x2(c0, c1);
}

FORCE_INLINE uint8x8x2_t vld2_lane_u8(const uint8_t *a, uint8x8x2_t b, const int c) {
  vbool8_t mask = __riscv_vreinterpret_v_u8m1_b8(vdup_n_u8((uint8_t)(1 << c)));
  vuint8m1_t c0 = __riscv_vmerge_vxm_u8m1(__riscv_vget_v_u8m1x2_u8m1(b, 0), a[0], mask, 8);
  vuint8m1_t c1 = __riscv_vmerge_vxm_u8m1(__riscv_vget_v_u8m1x2_u8m1(b, 1), a[1], mask, 8);
  return __riscv_vcreate_v_u8m1x2(c0, c1);
}

// FORCE_INLINE poly8x8x2_t vld2_lane_p8(poly8_t const * ptr, poly8x8x2_t src, const int lane);

// FORCE_INLINE int8x16x2_t vld2q_lane_s8(int8_t const * ptr, int8x16x2_t src, const int lane);

// FORCE_INLINE uint8x16x2_t vld2q_lane_u8(uint8_t const * ptr, uint8x16x2_t src, const int lane);

// FORCE_INLINE poly8x16x2_t vld2q_lane_p8(poly8_t const * ptr, poly8x16x2_t src, const int lane);

// FORCE_INLINE int64x1x2_t vld2_lane_s64(int64_t const * ptr, int64x1x2_t src, const int lane);

// FORCE_INLINE int64x2x2_t vld2q_lane_s64(int64_t const * ptr, int64x2x2_t src, const int lane);

// FORCE_INLINE uint64x1x2_t vld2_lane_u64(uint64_t const * ptr, uint64x1x2_t src, const int lane);

// FORCE_INLINE uint64x2x2_t vld2q_lane_u64(uint64_t const * ptr, uint64x2x2_t src, const int lane);

// FORCE_INLINE poly64x1x2_t vld2_lane_p64(poly64_t const * ptr, poly64x1x2_t src, const int lane);

// FORCE_INLINE poly64x2x2_t vld2q_lane_p64(poly64_t const * ptr, poly64x2x2_t src, const int lane);

// FORCE_INLINE float64x1x2_t vld2_lane_f64(float64_t const * ptr, float64x1x2_t src, const int lane);

// FORCE_INLINE float64x2x2_t vld2q_lane_f64(float64_t const * ptr, float64x2x2_t src, const int lane);

FORCE_INLINE uint16x4x2_t vld2_lane_u16(const uint16_t *a, uint16x4x2_t b, const int c) {
  vbool16_t mask = __riscv_vreinterpret_v_u16m1_b16(vdup_n_u16((uint8_t)(1 << c)));
  vuint16m1_t c0 = __riscv_vmerge_vxm_u16m1(__riscv_vget_v_u16m1x2_u16m1(b, 0), a[0], mask, 4);
  vuint16m1_t c1 = __riscv_vmerge_vxm_u16m1(__riscv_vget_v_u16m1x2_u16m1(b, 1), a[1], mask, 4);
  return __riscv_vcreate_v_u16m1x2(c0, c1);
}

FORCE_INLINE uint32x2x2_t vld2_lane_u32(const uint32_t *a, uint32x2x2_t b, const int c) {
  vbool32_t mask = __riscv_vreinterpret_v_u32m1_b32(vdup_n_u32((uint8_t)(1 << c)));
  vuint32m1_t c0 = __riscv_vmerge_vxm_u32m1(__riscv_vget_v_u32m1x2_u32m1(b, 0), a[0], mask, 2);
  vuint32m1_t c1 = __riscv_vmerge_vxm_u32m1(__riscv_vget_v_u32m1x2_u32m1(b, 1), a[1], mask, 2);
  return __riscv_vcreate_v_u32m1x2(c0, c1);
}

FORCE_INLINE int16x8x2_t vld2q_lane_s16(const int16_t *a, int16x8x2_t b, const int c) {
  vbool16_t mask = __riscv_vreinterpret_v_u16m1_b16(vdup_n_u16((uint8_t)(1 << c)));
  vint16m1_t c0 = __riscv_vmerge_vxm_i16m1(__riscv_vget_v_i16m1x2_i16m1(b, 0), a[0], mask, 8);
  vint16m1_t c1 = __riscv_vmerge_vxm_i16m1(__riscv_vget_v_i16m1x2_i16m1(b, 1), a[1], mask, 8);
  return __riscv_vcreate_v_i16m1x2(c0, c1);
}

FORCE_INLINE int32x4x2_t vld2q_lane_s32(const int32_t *a, int32x4x2_t b, const int c) {
  vbool32_t mask = __riscv_vreinterpret_v_u32m1_b32(vdup_n_u32((uint8_t)(1 << c)));
  vint32m1_t c0 = __riscv_vmerge_vxm_i32m1(__riscv_vget_v_i32m1x2_i32m1(b, 0), a[0], mask, 4);
  vint32m1_t c1 = __riscv_vmerge_vxm_i32m1(__riscv_vget_v_i32m1x2_i32m1(b, 1), a[1], mask, 4);
  return __riscv_vcreate_v_i32m1x2(c0, c1);
}

FORCE_INLINE float32x4x2_t vld2q_lane_f32(const float32_t *a, float32x4x2_t b, const int c) {
  vbool32_t mask = __riscv_vreinterpret_v_u32m1_b32(vdup_n_u32((uint8_t)(1 << c)));
  vfloat32m1_t c0 = __riscv_vfmerge_vfm_f32m1(__riscv_vget_v_f32m1x2_f32m1(b, 0), a[0], mask, 4);
  vfloat32m1_t c1 = __riscv_vfmerge_vfm_f32m1(__riscv_vget_v_f32m1x2_f32m1(b, 1), a[1], mask, 4);
  return __riscv_vcreate_v_f32m1x2(c0, c1);
}

// FORCE_INLINE poly16x4x2_t vld2_lane_p16(poly16_t const * ptr, poly16x4x2_t src, const int lane);

// FORCE_INLINE poly16x8x2_t vld2q_lane_p16(poly16_t const * ptr, poly16x8x2_t src, const int lane);

FORCE_INLINE uint16x8x2_t vld2q_lane_u16(const uint16_t *a, uint16x8x2_t b, const int c) {
  vbool16_t mask = __riscv_vreinterpret_v_u16m1_b16(vdup_n_u16((uint8_t)(1 << c)));
  vuint16m1_t c0 = __riscv_vmerge_vxm_u16m1(__riscv_vget_v_u16m1x2_u16m1(b, 0), a[0], mask, 8);
  vuint16m1_t c1 = __riscv_vmerge_vxm_u16m1(__riscv_vget_v_u16m1x2_u16m1(b, 1), a[1], mask, 8);
  return __riscv_vcreate_v_u16m1x2(c0, c1);
}

FORCE_INLINE uint32x4x2_t vld2q_lane_u32(const uint32_t *a, uint32x4x2_t b, const int c) {
  vbool32_t mask = __riscv_vreinterpret_v_u32m1_b32(vdup_n_u32((uint8_t)(1 << c)));
  vuint32m1_t c0 = __riscv_vmerge_vxm_u32m1(__riscv_vget_v_u32m1x2_u32m1(b, 0), a[0], mask, 4);
  vuint32m1_t c1 = __riscv_vmerge_vxm_u32m1(__riscv_vget_v_u32m1x2_u32m1(b, 1), a[1], mask, 4);
  return __riscv_vcreate_v_u32m1x2(c0, c1);
}

// FORCE_INLINE float16x4x2_t vld2_lane_f16(float16_t const * ptr, float16x4x2_t src, const int lane);

// FORCE_INLINE float16x8x2_t vld2q_lane_f16(float16_t const * ptr, float16x8x2_t src, const int lane);

FORCE_INLINE int8x8x2_t vld2_dup_s8(const int8_t *a) {
  return __riscv_vcreate_v_i8m1x2(vdup_n_s8(a[0]), vdup_n_s8(a[1]));
}

// FORCE_INLINE int8x16x2_t vld2q_dup_s8(int8_t const * ptr);

FORCE_INLINE int16x4x2_t vld2_dup_s16(const int16_t *a) {
  return __riscv_vcreate_v_i16m1x2(vdup_n_s16(a[0]), vdup_n_s16(a[1]));
}

// FORCE_INLINE int16x8x2_t vld2q_dup_s16(int16_t const * ptr);

FORCE_INLINE int32x2x2_t vld2_dup_s32(const int32_t *a) {
  return __riscv_vcreate_v_i32m1x2(vdup_n_s32(a[0]), vdup_n_s32(a[1]));
}

// FORCE_INLINE int32x4x2_t vld2q_dup_s32(int32_t const * ptr);

FORCE_INLINE float32x2x2_t vld2_dup_f32(const float32_t *a) {
  return __riscv_vcreate_v_f32m1x2(vdup_n_f32(a[0]), vdup_n_f32(a[1]));
}

// FORCE_INLINE float32x4x2_t vld2q_dup_f32(float32_t const * ptr);

// FORCE_INLINE poly8x8x2_t vld2_dup_p8(poly8_t const * ptr);

// FORCE_INLINE poly8x16x2_t vld2q_dup_p8(poly8_t const * ptr);

// FORCE_INLINE poly16x4x2_t vld2_dup_p16(poly16_t const * ptr);

// FORCE_INLINE poly16x8x2_t vld2q_dup_p16(poly16_t const * ptr);

FORCE_INLINE uint8x8x2_t vld2_dup_u8(const uint8_t *a) {
  return __riscv_vcreate_v_u8m1x2(vdup_n_u8(a[0]), vdup_n_u8(a[1]));
}

// FORCE_INLINE uint8x16x2_t vld2q_dup_u8(uint8_t const * ptr);

FORCE_INLINE uint16x4x2_t vld2_dup_u16(const uint16_t *a) {
  return __riscv_vcreate_v_u16m1x2(vdup_n_u16(a[0]), vdup_n_u16(a[1]));
}

// FORCE_INLINE uint16x8x2_t vld2q_dup_u16(uint16_t const * ptr);

FORCE_INLINE uint32x2x2_t vld2_dup_u32(const uint32_t *a) {
  return __riscv_vcreate_v_u32m1x2(vdup_n_u32(a[0]), vdup_n_u32(a[1]));
}

// FORCE_INLINE uint32x4x2_t vld2q_dup_u32(uint32_t const * ptr);

// FORCE_INLINE float16x4x2_t vld2_dup_f16(float16_t const * ptr);

// FORCE_INLINE float16x8x2_t vld2q_dup_f16(float16_t const * ptr);

FORCE_INLINE int64x1x2_t vld2_dup_s64(const int64_t *a) {
  return __riscv_vcreate_v_i64m1x2(vdup_n_s64(a[0]), vdup_n_s64(a[1]));
}

FORCE_INLINE uint64x1x2_t vld2_dup_u64(const uint64_t *a) {
  return __riscv_vcreate_v_u64m1x2(vdup_n_u64(a[0]), vdup_n_u64(a[1]));
}

// FORCE_INLINE poly64x1x2_t vld2_dup_p64(poly64_t const * ptr);

// FORCE_INLINE int64x2x2_t vld2q_dup_s64(int64_t const * ptr);

// FORCE_INLINE uint64x2x2_t vld2q_dup_u64(uint64_t const * ptr);

// FORCE_INLINE poly64x2x2_t vld2q_dup_p64(poly64_t const * ptr);

// FORCE_INLINE float64x1x2_t vld2_dup_f64(float64_t const * ptr);

// FORCE_INLINE float64x2x2_t vld2q_dup_f64(float64_t const * ptr);

FORCE_INLINE void vst2_s8(int8_t *a, int8x8x2_t b) { return __riscv_vsseg2e8_v_i8m1x2(a, b, 8); }

FORCE_INLINE void vst2_s16(int16_t *a, int16x4x2_t b) { return __riscv_vsseg2e16_v_i16m1x2(a, b, 4); }

FORCE_INLINE void vst2_s32(int32_t *a, int32x2x2_t b) { return __riscv_vsseg2e32_v_i32m1x2(a, b, 2); }

FORCE_INLINE void vst2_f32(float32_t *a, float32x2x2_t b) { return __riscv_vsseg2e32_v_f32m1x2(a, b, 2); }

FORCE_INLINE void vst2_u8(uint8_t *a, uint8x8x2_t b) { return __riscv_vsseg2e8_v_u8m1x2(a, b, 8); }

FORCE_INLINE void vst2_u16(uint16_t *a, uint16x4x2_t b) { return __riscv_vsseg2e16_v_u16m1x2(a, b, 4); }

FORCE_INLINE void vst2_u32(uint32_t *a, uint32x2x2_t b) { return __riscv_vsseg2e32_v_u32m1x2(a, b, 2); }

FORCE_INLINE void vst2_s64(int64_t *a, int64x1x2_t b) { return __riscv_vsseg2e64_v_i64m1x2(a, b, 1); }

FORCE_INLINE void vst2_u64(uint64_t *a, uint64x1x2_t b) { return __riscv_vsseg2e64_v_u64m1x2(a, b, 1); }

// FORCE_INLINE void vst2_p64(poly64_t * ptr, poly64x1x2_t val);

// FORCE_INLINE void vst2q_s64(int64_t * ptr, int64x2x2_t val);

// FORCE_INLINE void vst2q_u64(uint64_t * ptr, uint64x2x2_t val);

// FORCE_INLINE void vst2q_p64(poly64_t * ptr, poly64x2x2_t val);

// FORCE_INLINE void vst2_f64(float64_t * ptr, float64x1x2_t val);

// FORCE_INLINE void vst2q_f64(float64_t * ptr, float64x2x2_t val);

FORCE_INLINE void vst2q_s8(int8_t *a, int8x16x2_t b) { return __riscv_vsseg2e8_v_i8m1x2(a, b, 16); }

FORCE_INLINE void vst2q_s16(int16_t *a, int16x8x2_t b) { return __riscv_vsseg2e16_v_i16m1x2(a, b, 8); }

FORCE_INLINE void vst2q_s32(int32_t *a, int32x4x2_t b) { return __riscv_vsseg2e32_v_i32m1x2(a, b, 4); }

FORCE_INLINE void vst2q_f32(float32_t *a, float32x4x2_t b) { return __riscv_vsseg2e32_v_f32m1x2(a, b, 4); }

// FORCE_INLINE void vst2_p8(poly8_t * ptr, poly8x8x2_t val);

// FORCE_INLINE void vst2q_p8(poly8_t * ptr, poly8x16x2_t val);

// FORCE_INLINE void vst2_p16(poly16_t * ptr, poly16x4x2_t val);

// FORCE_INLINE void vst2q_p16(poly16_t * ptr, poly16x8x2_t val);

FORCE_INLINE void vst2q_u8(uint8_t *a, uint8x16x2_t b) { return __riscv_vsseg2e8_v_u8m1x2(a, b, 16); }

FORCE_INLINE void vst2q_u16(uint16_t *a, uint16x8x2_t b) { return __riscv_vsseg2e16_v_u16m1x2(a, b, 8); }

FORCE_INLINE void vst2q_u32(uint32_t *a, uint32x4x2_t b) { return __riscv_vsseg2e32_v_u32m1x2(a, b, 4); }

// FORCE_INLINE void vst2_f16(float16_t * ptr, float16x4x2_t val);

// FORCE_INLINE void vst2q_f16(float16_t * ptr, float16x8x2_t val);

FORCE_INLINE void vst2_lane_s8(int8_t *a, int8x8x2_t b, const int c) {
  vint8m1_t b0 = __riscv_vget_v_i8m1x2_i8m1(b, 0);
  vint8m1_t b1 = __riscv_vget_v_i8m1x2_i8m1(b, 1);
  int8_t *_b0 = (int8_t *)&b0;
  int8_t *_b1 = (int8_t *)&b1;
  a[0] = _b0[c];
  a[1] = _b1[c];
}

FORCE_INLINE void vst2_lane_s16(int16_t *a, int16x4x2_t b, const int c) {
  vint16m1_t b0 = __riscv_vget_v_i16m1x2_i16m1(b, 0);
  vint16m1_t b1 = __riscv_vget_v_i16m1x2_i16m1(b, 1);
  int16_t *_b0 = (int16_t *)&b0;
  int16_t *_b1 = (int16_t *)&b1;
  a[0] = _b0[c];
  a[1] = _b1[c];
}

FORCE_INLINE void vst2_lane_s32(int32_t *a, int32x2x2_t b, const int c) {
  vint32m1_t b0 = __riscv_vget_v_i32m1x2_i32m1(b, 0);
  vint32m1_t b1 = __riscv_vget_v_i32m1x2_i32m1(b, 1);
  int32_t *_b0 = (int32_t *)&b0;
  int32_t *_b1 = (int32_t *)&b1;
  a[0] = _b0[c];
  a[1] = _b1[c];
}

FORCE_INLINE void vst2_lane_f32(float32_t *a, float32x2x2_t b, const int c) {
  vfloat32m1_t b0 = __riscv_vget_v_f32m1x2_f32m1(b, 0);
  vfloat32m1_t b1 = __riscv_vget_v_f32m1x2_f32m1(b, 1);
  float *_b0 = (float *)&b0;
  float *_b1 = (float *)&b1;
  a[0] = _b0[c];
  a[1] = _b1[c];
}

FORCE_INLINE void vst2_lane_u8(uint8_t *a, uint8x8x2_t b, const int c) {
  vuint8m1_t b0 = __riscv_vget_v_u8m1x2_u8m1(b, 0);
  vuint8m1_t b1 = __riscv_vget_v_u8m1x2_u8m1(b, 1);
  uint8_t *_b0 = (uint8_t *)&b0;
  uint8_t *_b1 = (uint8_t *)&b1;
  a[0] = _b0[c];
  a[1] = _b1[c];
}

// FORCE_INLINE void vst2_lane_p8(poly8_t * ptr, poly8x8x2_t val, const int lane);

FORCE_INLINE void vst2_lane_u16(uint16_t *a, uint16x4x2_t b, const int c) {
  vuint16m1_t b0 = __riscv_vget_v_u16m1x2_u16m1(b, 0);
  vuint16m1_t b1 = __riscv_vget_v_u16m1x2_u16m1(b, 1);
  uint16_t *_b0 = (uint16_t *)&b0;
  uint16_t *_b1 = (uint16_t *)&b1;
  a[0] = _b0[c];
  a[1] = _b1[c];
}

FORCE_INLINE void vst2_lane_u32(uint32_t *a, uint32x2x2_t b, const int c) {
  vuint32m1_t b0 = __riscv_vget_v_u32m1x2_u32m1(b, 0);
  vuint32m1_t b1 = __riscv_vget_v_u32m1x2_u32m1(b, 1);
  uint32_t *_b0 = (uint32_t *)&b0;
  uint32_t *_b1 = (uint32_t *)&b1;
  a[0] = _b0[c];
  a[1] = _b1[c];
}

FORCE_INLINE void vst2q_lane_s16(int16_t *a, int16x8x2_t b, const int c) {
  vint16m1_t b0 = __riscv_vget_v_i16m1x2_i16m1(b, 0);
  vint16m1_t b1 = __riscv_vget_v_i16m1x2_i16m1(b, 1);
  int16_t *_b0 = (int16_t *)&b0;
  int16_t *_b1 = (int16_t *)&b1;
  a[0] = _b0[c];
  a[1] = _b1[c];
}

FORCE_INLINE void vst2q_lane_s32(int32_t *a, int32x4x2_t b, const int c) {
  vint32m1_t b0 = __riscv_vget_v_i32m1x2_i32m1(b, 0);
  vint32m1_t b1 = __riscv_vget_v_i32m1x2_i32m1(b, 1);
  int32_t *_b0 = (int32_t *)&b0;
  int32_t *_b1 = (int32_t *)&b1;
  a[0] = _b0[c];
  a[1] = _b1[c];
}

FORCE_INLINE void vst2q_lane_f32(float32_t *a, float32x4x2_t b, const int c) {
  vfloat32m1_t b0 = __riscv_vget_v_f32m1x2_f32m1(b, 0);
  vfloat32m1_t b1 = __riscv_vget_v_f32m1x2_f32m1(b, 1);
  float *_b0 = (float *)&b0;
  float *_b1 = (float *)&b1;
  a[0] = _b0[c];
  a[1] = _b1[c];
}

// FORCE_INLINE void vst2_lane_p16(poly16_t * ptr, poly16x4x2_t val, const int lane);

// FORCE_INLINE void vst2q_lane_p16(poly16_t * ptr, poly16x8x2_t val, const int lane);

// FORCE_INLINE void vst2q_lane_s8(int8_t * ptr, int8x16x2_t val, const int lane);

// FORCE_INLINE void vst2q_lane_u8(uint8_t * ptr, uint8x16x2_t val, const int lane);

// FORCE_INLINE void vst2q_lane_p8(poly8_t * ptr, poly8x16x2_t val, const int lane);

// FORCE_INLINE void vst2_lane_s64(int64_t * ptr, int64x1x2_t val, const int lane);

// FORCE_INLINE void vst2q_lane_s64(int64_t * ptr, int64x2x2_t val, const int lane);

// FORCE_INLINE void vst2_lane_u64(uint64_t * ptr, uint64x1x2_t val, const int lane);

// FORCE_INLINE void vst2q_lane_u64(uint64_t * ptr, uint64x2x2_t val, const int lane);

// FORCE_INLINE void vst2_lane_p64(poly64_t * ptr, poly64x1x2_t val, const int lane);

// FORCE_INLINE void vst2q_lane_p64(poly64_t * ptr, poly64x2x2_t val, const int lane);

// FORCE_INLINE void vst2_lane_f64(float64_t * ptr, float64x1x2_t val, const int lane);

// FORCE_INLINE void vst2q_lane_f64(float64_t * ptr, float64x2x2_t val, const int lane);

FORCE_INLINE void vst2q_lane_u16(uint16_t *a, uint16x8x2_t b, const int c) {
  vuint16m1_t b0 = __riscv_vget_v_u16m1x2_u16m1(b, 0);
  vuint16m1_t b1 = __riscv_vget_v_u16m1x2_u16m1(b, 1);
  uint16_t *_b0 = (uint16_t *)&b0;
  uint16_t *_b1 = (uint16_t *)&b1;
  a[0] = _b0[c];
  a[1] = _b1[c];
}

FORCE_INLINE void vst2q_lane_u32(uint32_t *a, uint32x4x2_t b, const int c) {
  vuint32m1_t b0 = __riscv_vget_v_u32m1x2_u32m1(b, 0);
  vuint32m1_t b1 = __riscv_vget_v_u32m1x2_u32m1(b, 1);
  uint32_t *_b0 = (uint32_t *)&b0;
  uint32_t *_b1 = (uint32_t *)&b1;
  a[0] = _b0[c];
  a[1] = _b1[c];
}

// FORCE_INLINE void vst2_lane_f16(float16_t * ptr, float16x4x2_t val, const int lane);

// FORCE_INLINE void vst2q_lane_f16(float16_t * ptr, float16x8x2_t val, const int lane);

FORCE_INLINE int8x8x3_t vld3_s8(const int8_t *a) { return __riscv_vlseg3e8_v_i8m1x3(a, 8); }

FORCE_INLINE int16x4x3_t vld3_s16(const int16_t *a) { return __riscv_vlseg3e16_v_i16m1x3(a, 4); }

FORCE_INLINE int32x2x3_t vld3_s32(const int32_t *a) { return __riscv_vlseg3e32_v_i32m1x3(a, 2); }

FORCE_INLINE float32x2x3_t vld3_f32(const float32_t *a) { return __riscv_vlseg3e32_v_f32m1x3(a, 2); }

FORCE_INLINE uint8x8x3_t vld3_u8(const uint8_t *a) { return __riscv_vlseg3e8_v_u8m1x3(a, 8); }

FORCE_INLINE uint16x4x3_t vld3_u16(const uint16_t *a) { return __riscv_vlseg3e16_v_u16m1x3(a, 4); }

FORCE_INLINE uint32x2x3_t vld3_u32(const uint32_t *a) { return __riscv_vlseg3e32_v_u32m1x3(a, 2); }

FORCE_INLINE int64x1x3_t vld3_s64(const int64_t *a) { return __riscv_vlseg3e64_v_i64m1x3(a, 1); }

FORCE_INLINE uint64x1x3_t vld3_u64(const uint64_t *a) { return __riscv_vlseg3e64_v_u64m1x3(a, 1); }

// FORCE_INLINE poly64x1x3_t vld3_p64(poly64_t const * ptr);

// FORCE_INLINE int64x2x3_t vld3q_s64(int64_t const * ptr);

// FORCE_INLINE uint64x2x3_t vld3q_u64(uint64_t const * ptr);

// FORCE_INLINE poly64x2x3_t vld3q_p64(poly64_t const * ptr);

// FORCE_INLINE float64x1x3_t vld3_f64(float64_t const * ptr);

// FORCE_INLINE float64x2x3_t vld3q_f64(float64_t const * ptr);

FORCE_INLINE int8x16x3_t vld3q_s8(const int8_t *a) { return __riscv_vlseg3e8_v_i8m1x3(a, 16); }

FORCE_INLINE int16x8x3_t vld3q_s16(const int16_t *a) { return __riscv_vlseg3e16_v_i16m1x3(a, 8); }

FORCE_INLINE int32x4x3_t vld3q_s32(const int32_t *a) { return __riscv_vlseg3e32_v_i32m1x3(a, 4); }

FORCE_INLINE float32x4x3_t vld3q_f32(const float32_t *a) { return __riscv_vlseg3e32_v_f32m1x3(a, 4); }

// FORCE_INLINE poly8x8x3_t vld3_p8(poly8_t const * ptr);

// FORCE_INLINE poly8x16x3_t vld3q_p8(poly8_t const * ptr);

// FORCE_INLINE poly16x4x3_t vld3_p16(poly16_t const * ptr);

// FORCE_INLINE poly16x8x3_t vld3q_p16(poly16_t const * ptr);

FORCE_INLINE uint8x16x3_t vld3q_u8(const uint8_t *a) { return __riscv_vlseg3e8_v_u8m1x3(a, 16); }

FORCE_INLINE uint16x8x3_t vld3q_u16(const uint16_t *a) { return __riscv_vlseg3e16_v_u16m1x3(a, 8); }

FORCE_INLINE uint32x4x3_t vld3q_u32(const uint32_t *a) { return __riscv_vlseg3e32_v_u32m1x3(a, 4); }

// FORCE_INLINE float16x4x3_t vld3_f16(float16_t const * ptr);

// FORCE_INLINE float16x8x3_t vld3q_f16(float16_t const * ptr);

FORCE_INLINE int8x8x3_t vld3_lane_s8(const int8_t *a, int8x8x3_t b, const int c) {
  vbool8_t mask = __riscv_vreinterpret_v_u8m1_b8(vdup_n_u8((uint8_t)(1 << c)));
  vint8m1_t c0 = __riscv_vmerge_vxm_i8m1(__riscv_vget_v_i8m1x3_i8m1(b, 0), a[0], mask, 8);
  vint8m1_t c1 = __riscv_vmerge_vxm_i8m1(__riscv_vget_v_i8m1x3_i8m1(b, 1), a[1], mask, 8);
  vint8m1_t c2 = __riscv_vmerge_vxm_i8m1(__riscv_vget_v_i8m1x3_i8m1(b, 2), a[2], mask, 8);
  return __riscv_vcreate_v_i8m1x3(c0, c1, c2);
}

FORCE_INLINE int16x4x3_t vld3_lane_s16(const int16_t *a, int16x4x3_t b, const int c) {
  vbool16_t mask = __riscv_vreinterpret_v_u8m1_b16(vdup_n_u8((uint8_t)(1 << c)));
  vint16m1_t c0 = __riscv_vmerge_vxm_i16m1(__riscv_vget_v_i16m1x3_i16m1(b, 0), a[0], mask, 4);
  vint16m1_t c1 = __riscv_vmerge_vxm_i16m1(__riscv_vget_v_i16m1x3_i16m1(b, 1), a[1], mask, 4);
  vint16m1_t c2 = __riscv_vmerge_vxm_i16m1(__riscv_vget_v_i16m1x3_i16m1(b, 2), a[2], mask, 4);
  return __riscv_vcreate_v_i16m1x3(c0, c1, c2);
}

FORCE_INLINE int32x2x3_t vld3_lane_s32(const int32_t *a, int32x2x3_t b, const int c) {
  vbool32_t mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << c)));
  vint32m1_t c0 = __riscv_vmerge_vxm_i32m1(__riscv_vget_v_i32m1x3_i32m1(b, 0), a[0], mask, 2);
  vint32m1_t c1 = __riscv_vmerge_vxm_i32m1(__riscv_vget_v_i32m1x3_i32m1(b, 1), a[1], mask, 2);
  vint32m1_t c2 = __riscv_vmerge_vxm_i32m1(__riscv_vget_v_i32m1x3_i32m1(b, 2), a[2], mask, 2);
  return __riscv_vcreate_v_i32m1x3(c0, c1, c2);
}

FORCE_INLINE float32x2x3_t vld3_lane_f32(const float32_t *a, float32x2x3_t b, const int c) {
  vbool32_t mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << c)));
  vfloat32m1_t c0 = __riscv_vfmerge_vfm_f32m1(__riscv_vget_v_f32m1x3_f32m1(b, 0), a[0], mask, 2);
  vfloat32m1_t c1 = __riscv_vfmerge_vfm_f32m1(__riscv_vget_v_f32m1x3_f32m1(b, 1), a[1], mask, 2);
  vfloat32m1_t c2 = __riscv_vfmerge_vfm_f32m1(__riscv_vget_v_f32m1x3_f32m1(b, 2), a[2], mask, 2);
  return __riscv_vcreate_v_f32m1x3(c0, c1, c2);
}

FORCE_INLINE uint8x8x3_t vld3_lane_u8(const uint8_t *a, uint8x8x3_t b, const int c) {
  vbool8_t mask = __riscv_vreinterpret_v_u8m1_b8(vdup_n_u8((uint8_t)(1 << c)));
  vuint8m1_t c0 = __riscv_vmerge_vxm_u8m1(__riscv_vget_v_u8m1x3_u8m1(b, 0), a[0], mask, 8);
  vuint8m1_t c1 = __riscv_vmerge_vxm_u8m1(__riscv_vget_v_u8m1x3_u8m1(b, 1), a[1], mask, 8);
  vuint8m1_t c2 = __riscv_vmerge_vxm_u8m1(__riscv_vget_v_u8m1x3_u8m1(b, 2), a[2], mask, 8);
  return __riscv_vcreate_v_u8m1x3(c0, c1, c2);
}

// FORCE_INLINE poly8x8x3_t vld3_lane_p8(poly8_t const * ptr, poly8x8x3_t src, const int lane);

// FORCE_INLINE int8x16x3_t vld3q_lane_s8(int8_t const * ptr, int8x16x3_t src, const int lane);

// FORCE_INLINE uint8x16x3_t vld3q_lane_u8(uint8_t const * ptr, uint8x16x3_t src, const int lane);

// FORCE_INLINE poly8x16x3_t vld3q_lane_p8(poly8_t const * ptr, poly8x16x3_t src, const int lane);

// FORCE_INLINE int64x1x3_t vld3_lane_s64(int64_t const * ptr, int64x1x3_t src, const int lane);

// FORCE_INLINE int64x2x3_t vld3q_lane_s64(int64_t const * ptr, int64x2x3_t src, const int lane);

// FORCE_INLINE uint64x1x3_t vld3_lane_u64(uint64_t const * ptr, uint64x1x3_t src, const int lane);

// FORCE_INLINE uint64x2x3_t vld3q_lane_u64(uint64_t const * ptr, uint64x2x3_t src, const int lane);

// FORCE_INLINE poly64x1x3_t vld3_lane_p64(poly64_t const * ptr, poly64x1x3_t src, const int lane);

// FORCE_INLINE poly64x2x3_t vld3q_lane_p64(poly64_t const * ptr, poly64x2x3_t src, const int lane);

// FORCE_INLINE float64x1x3_t vld3_lane_f64(float64_t const * ptr, float64x1x3_t src, const int lane);

// FORCE_INLINE float64x2x3_t vld3q_lane_f64(float64_t const * ptr, float64x2x3_t src, const int lane);

FORCE_INLINE uint16x4x3_t vld3_lane_u16(const uint16_t *a, uint16x4x3_t b, const int c) {
  vbool16_t mask = __riscv_vreinterpret_v_u8m1_b16(vdup_n_u8((uint8_t)(1 << c)));
  vuint16m1_t c0 = __riscv_vmerge_vxm_u16m1(__riscv_vget_v_u16m1x3_u16m1(b, 0), a[0], mask, 4);
  vuint16m1_t c1 = __riscv_vmerge_vxm_u16m1(__riscv_vget_v_u16m1x3_u16m1(b, 1), a[1], mask, 4);
  vuint16m1_t c2 = __riscv_vmerge_vxm_u16m1(__riscv_vget_v_u16m1x3_u16m1(b, 2), a[2], mask, 4);
  return __riscv_vcreate_v_u16m1x3(c0, c1, c2);
}

FORCE_INLINE uint32x2x3_t vld3_lane_u32(const uint32_t *a, uint32x2x3_t b, const int c) {
  vbool32_t mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << c)));
  vuint32m1_t c0 = __riscv_vmerge_vxm_u32m1(__riscv_vget_v_u32m1x3_u32m1(b, 0), a[0], mask, 2);
  vuint32m1_t c1 = __riscv_vmerge_vxm_u32m1(__riscv_vget_v_u32m1x3_u32m1(b, 1), a[1], mask, 2);
  vuint32m1_t c2 = __riscv_vmerge_vxm_u32m1(__riscv_vget_v_u32m1x3_u32m1(b, 2), a[2], mask, 2);
  return __riscv_vcreate_v_u32m1x3(c0, c1, c2);
}

FORCE_INLINE int16x8x3_t vld3q_lane_s16(const int16_t *a, int16x8x3_t b, const int c) {
  vbool16_t mask = __riscv_vreinterpret_v_u8m1_b16(vdup_n_u8((uint8_t)(1 << c)));
  vint16m1_t c0 = __riscv_vmerge_vxm_i16m1(__riscv_vget_v_i16m1x3_i16m1(b, 0), a[0], mask, 8);
  vint16m1_t c1 = __riscv_vmerge_vxm_i16m1(__riscv_vget_v_i16m1x3_i16m1(b, 1), a[1], mask, 8);
  vint16m1_t c2 = __riscv_vmerge_vxm_i16m1(__riscv_vget_v_i16m1x3_i16m1(b, 2), a[2], mask, 8);
  return __riscv_vcreate_v_i16m1x3(c0, c1, c2);
}

FORCE_INLINE int32x4x3_t vld3q_lane_s32(const int32_t *a, int32x4x3_t b, const int c) {
  vbool32_t mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << c)));
  vint32m1_t c0 = __riscv_vmerge_vxm_i32m1(__riscv_vget_v_i32m1x3_i32m1(b, 0), a[0], mask, 4);
  vint32m1_t c1 = __riscv_vmerge_vxm_i32m1(__riscv_vget_v_i32m1x3_i32m1(b, 1), a[1], mask, 4);
  vint32m1_t c2 = __riscv_vmerge_vxm_i32m1(__riscv_vget_v_i32m1x3_i32m1(b, 2), a[2], mask, 4);
  return __riscv_vcreate_v_i32m1x3(c0, c1, c2);
}

FORCE_INLINE float32x4x3_t vld3q_lane_f32(const float32_t *a, float32x4x3_t b, const int c) {
  vbool32_t mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << c)));
  vfloat32m1_t c0 = __riscv_vfmerge_vfm_f32m1(__riscv_vget_v_f32m1x3_f32m1(b, 0), a[0], mask, 4);
  vfloat32m1_t c1 = __riscv_vfmerge_vfm_f32m1(__riscv_vget_v_f32m1x3_f32m1(b, 1), a[1], mask, 4);
  vfloat32m1_t c2 = __riscv_vfmerge_vfm_f32m1(__riscv_vget_v_f32m1x3_f32m1(b, 2), a[2], mask, 4);
  return __riscv_vcreate_v_f32m1x3(c0, c1, c2);
}

// FORCE_INLINE poly16x4x3_t vld3_lane_p16(poly16_t const * ptr, poly16x4x3_t src, const int lane);

// FORCE_INLINE poly16x8x3_t vld3q_lane_p16(poly16_t const * ptr, poly16x8x3_t src, const int lane);

FORCE_INLINE uint16x8x3_t vld3q_lane_u16(const uint16_t *a, uint16x8x3_t b, const int c) {
  vbool16_t mask = __riscv_vreinterpret_v_u8m1_b16(vdup_n_u8((uint8_t)(1 << c)));
  vuint16m1_t c0 = __riscv_vmerge_vxm_u16m1(__riscv_vget_v_u16m1x3_u16m1(b, 0), a[0], mask, 8);
  vuint16m1_t c1 = __riscv_vmerge_vxm_u16m1(__riscv_vget_v_u16m1x3_u16m1(b, 1), a[1], mask, 8);
  vuint16m1_t c2 = __riscv_vmerge_vxm_u16m1(__riscv_vget_v_u16m1x3_u16m1(b, 2), a[2], mask, 8);
  return __riscv_vcreate_v_u16m1x3(c0, c1, c2);
}

FORCE_INLINE uint32x4x3_t vld3q_lane_u32(const uint32_t *a, uint32x4x3_t b, const int c) {
  vbool32_t mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << c)));
  vuint32m1_t c0 = __riscv_vmerge_vxm_u32m1(__riscv_vget_v_u32m1x3_u32m1(b, 0), a[0], mask, 4);
  vuint32m1_t c1 = __riscv_vmerge_vxm_u32m1(__riscv_vget_v_u32m1x3_u32m1(b, 1), a[1], mask, 4);
  vuint32m1_t c2 = __riscv_vmerge_vxm_u32m1(__riscv_vget_v_u32m1x3_u32m1(b, 2), a[2], mask, 4);
  return __riscv_vcreate_v_u32m1x3(c0, c1, c2);
}

// FORCE_INLINE float16x4x3_t vld3_lane_f16(float16_t const * ptr, float16x4x3_t src, const int lane);

// FORCE_INLINE float16x8x3_t vld3q_lane_f16(float16_t const * ptr, float16x8x3_t src, const int lane);

FORCE_INLINE int8x8x3_t vld3_dup_s8(const int8_t *a) {
  return __riscv_vcreate_v_i8m1x3(vdup_n_s8(a[0]), vdup_n_s8(a[1]), vdup_n_s8(a[2]));
}

// FORCE_INLINE int8x16x3_t vld3q_dup_s8(int8_t const * ptr);

FORCE_INLINE int16x4x3_t vld3_dup_s16(const int16_t *a) {
  return __riscv_vcreate_v_i16m1x3(vdup_n_s16(a[0]), vdup_n_s16(a[1]), vdup_n_s16(a[2]));
}

// FORCE_INLINE int16x8x3_t vld3q_dup_s16(int16_t const * ptr);

FORCE_INLINE int32x2x3_t vld3_dup_s32(const int32_t *a) {
  return __riscv_vcreate_v_i32m1x3(vdup_n_s32(a[0]), vdup_n_s32(a[1]), vdup_n_s32(a[2]));
}

// FORCE_INLINE int32x4x3_t vld3q_dup_s32(int32_t const * ptr);

FORCE_INLINE float32x2x3_t vld3_dup_f32(const float32_t *a) {
  return __riscv_vcreate_v_f32m1x3(vdup_n_f32(a[0]), vdup_n_f32(a[1]), vdup_n_f32(a[2]));
}

// FORCE_INLINE float32x4x3_t vld3q_dup_f32(float32_t const * ptr);

// FORCE_INLINE poly8x8x3_t vld3_dup_p8(poly8_t const * ptr);

// FORCE_INLINE poly8x16x3_t vld3q_dup_p8(poly8_t const * ptr);

// FORCE_INLINE poly16x4x3_t vld3_dup_p16(poly16_t const * ptr);

// FORCE_INLINE poly16x8x3_t vld3q_dup_p16(poly16_t const * ptr);

FORCE_INLINE uint8x8x3_t vld3_dup_u8(const uint8_t *a) {
  return __riscv_vcreate_v_u8m1x3(vdup_n_u8(a[0]), vdup_n_u8(a[1]), vdup_n_u8(a[2]));
}

// FORCE_INLINE uint8x16x3_t vld3q_dup_u8(uint8_t const * ptr);

FORCE_INLINE uint16x4x3_t vld3_dup_u16(const uint16_t *a) {
  return __riscv_vcreate_v_u16m1x3(vdup_n_u16(a[0]), vdup_n_u16(a[1]), vdup_n_u16(a[2]));
}

// FORCE_INLINE uint16x8x3_t vld3q_dup_u16(uint16_t const * ptr);

FORCE_INLINE uint32x2x3_t vld3_dup_u32(const uint32_t *a) {
  return __riscv_vcreate_v_u32m1x3(vdup_n_u32(a[0]), vdup_n_u32(a[1]), vdup_n_u32(a[2]));
}

// FORCE_INLINE uint32x4x3_t vld3q_dup_u32(uint32_t const * ptr);

// FORCE_INLINE float16x4x3_t vld3_dup_f16(float16_t const * ptr);

// FORCE_INLINE float16x8x3_t vld3q_dup_f16(float16_t const * ptr);

FORCE_INLINE int64x1x3_t vld3_dup_s64(const int64_t *a) {
  return __riscv_vcreate_v_i64m1x3(vdup_n_s64(a[0]), vdup_n_s64(a[1]), vdup_n_s64(a[2]));
}

FORCE_INLINE uint64x1x3_t vld3_dup_u64(const uint64_t *a) {
  return __riscv_vcreate_v_u64m1x3(vdup_n_u64(a[0]), vdup_n_u64(a[1]), vdup_n_u64(a[2]));
}

// FORCE_INLINE poly64x1x3_t vld3_dup_p64(poly64_t const * ptr);

// FORCE_INLINE int64x2x3_t vld3q_dup_s64(int64_t const * ptr);

// FORCE_INLINE uint64x2x3_t vld3q_dup_u64(uint64_t const * ptr);

// FORCE_INLINE poly64x2x3_t vld3q_dup_p64(poly64_t const * ptr);

// FORCE_INLINE float64x1x3_t vld3_dup_f64(float64_t const * ptr);

// FORCE_INLINE float64x2x3_t vld3q_dup_f64(float64_t const * ptr);

FORCE_INLINE void vst3_s8(int8_t *a, int8x8x3_t b) { return __riscv_vsseg3e8_v_i8m1x3(a, b, 8); }

FORCE_INLINE void vst3_s16(int16_t *a, int16x4x3_t b) { return __riscv_vsseg3e16_v_i16m1x3(a, b, 4); }

FORCE_INLINE void vst3_s32(int32_t *a, int32x2x3_t b) { return __riscv_vsseg3e32_v_i32m1x3(a, b, 2); }

FORCE_INLINE void vst3_f32(float32_t *a, float32x2x3_t b) { return __riscv_vsseg3e32_v_f32m1x3(a, b, 2); }

FORCE_INLINE void vst3_u8(uint8_t *a, uint8x8x3_t b) { return __riscv_vsseg3e8_v_u8m1x3(a, b, 8); }

FORCE_INLINE void vst3_u16(uint16_t *a, uint16x4x3_t b) { return __riscv_vsseg3e16_v_u16m1x3(a, b, 4); }

FORCE_INLINE void vst3_u32(uint32_t *a, uint32x2x3_t b) { return __riscv_vsseg3e32_v_u32m1x3(a, b, 2); }

FORCE_INLINE void vst3_s64(int64_t *a, int64x1x3_t b) { return __riscv_vsseg3e64_v_i64m1x3(a, b, 1); }

FORCE_INLINE void vst3_u64(uint64_t *a, uint64x1x3_t b) { return __riscv_vsseg3e64_v_u64m1x3(a, b, 1); }

// FORCE_INLINE void vst3_p64(poly64_t * ptr, poly64x1x3_t val);

// FORCE_INLINE void vst3q_s64(int64_t * ptr, int64x2x3_t val);

// FORCE_INLINE void vst3q_u64(uint64_t * ptr, uint64x2x3_t val);

// FORCE_INLINE void vst3q_p64(poly64_t * ptr, poly64x2x3_t val);

// FORCE_INLINE void vst3_f64(float64_t * ptr, float64x1x3_t val);

// FORCE_INLINE void vst3q_f64(float64_t * ptr, float64x2x3_t val);

FORCE_INLINE void vst3q_s8(int8_t *a, int8x16x3_t b) { return __riscv_vsseg3e8_v_i8m1x3(a, b, 16); }

FORCE_INLINE void vst3q_s16(int16_t *a, int16x8x3_t b) { return __riscv_vsseg3e16_v_i16m1x3(a, b, 8); }

FORCE_INLINE void vst3q_s32(int32_t *a, int32x4x3_t b) { return __riscv_vsseg3e32_v_i32m1x3(a, b, 4); }

FORCE_INLINE void vst3q_f32(float32_t *a, float32x4x3_t b) { return __riscv_vsseg3e32_v_f32m1x3(a, b, 4); }

// FORCE_INLINE void vst3_p8(poly8_t * ptr, poly8x8x3_t val);

// FORCE_INLINE void vst3q_p8(poly8_t * ptr, poly8x16x3_t val);

// FORCE_INLINE void vst3_p16(poly16_t * ptr, poly16x4x3_t val);

// FORCE_INLINE void vst3q_p16(poly16_t * ptr, poly16x8x3_t val);

FORCE_INLINE void vst3q_u8(uint8_t *a, uint8x16x3_t b) { return __riscv_vsseg3e8_v_u8m1x3(a, b, 16); }

FORCE_INLINE void vst3q_u16(uint16_t *a, uint16x8x3_t b) { return __riscv_vsseg3e16_v_u16m1x3(a, b, 8); }

FORCE_INLINE void vst3q_u32(uint32_t *a, uint32x4x3_t b) { return __riscv_vsseg3e32_v_u32m1x3(a, b, 4); }

// FORCE_INLINE void vst3_f16(float16_t * ptr, float16x4x3_t val);

// FORCE_INLINE void vst3q_f16(float16_t * ptr, float16x8x3_t val);

FORCE_INLINE void vst3_lane_s8(int8_t *a, int8x8x3_t b, const int c) {
  vint8m1_t b0 = __riscv_vget_v_i8m1x3_i8m1(b, 0);
  vint8m1_t b1 = __riscv_vget_v_i8m1x3_i8m1(b, 1);
  vint8m1_t b2 = __riscv_vget_v_i8m1x3_i8m1(b, 2);
  int8_t *_b0 = (int8_t *)&b0;
  int8_t *_b1 = (int8_t *)&b1;
  int8_t *_b2 = (int8_t *)&b2;
  a[0] = _b0[c];
  a[1] = _b1[c];
  a[2] = _b2[c];
}

FORCE_INLINE void vst3_lane_s16(int16_t *a, int16x4x3_t b, const int c) {
  vint16m1_t b0 = __riscv_vget_v_i16m1x3_i16m1(b, 0);
  vint16m1_t b1 = __riscv_vget_v_i16m1x3_i16m1(b, 1);
  vint16m1_t b2 = __riscv_vget_v_i16m1x3_i16m1(b, 2);
  int16_t *_b0 = (int16_t *)&b0;
  int16_t *_b1 = (int16_t *)&b1;
  int16_t *_b2 = (int16_t *)&b2;
  a[0] = _b0[c];
  a[1] = _b1[c];
  a[2] = _b2[c];
}

FORCE_INLINE void vst3_lane_s32(int32_t *a, int32x2x3_t b, const int c) {
  vint32m1_t b0 = __riscv_vget_v_i32m1x3_i32m1(b, 0);
  vint32m1_t b1 = __riscv_vget_v_i32m1x3_i32m1(b, 1);
  vint32m1_t b2 = __riscv_vget_v_i32m1x3_i32m1(b, 2);
  int32_t *_b0 = (int32_t *)&b0;
  int32_t *_b1 = (int32_t *)&b1;
  int32_t *_b2 = (int32_t *)&b2;
  a[0] = _b0[c];
  a[1] = _b1[c];
  a[2] = _b2[c];
}

FORCE_INLINE void vst3_lane_f32(float32_t *a, float32x2x3_t b, const int c) {
  vfloat32m1_t b0 = __riscv_vget_v_f32m1x3_f32m1(b, 0);
  vfloat32m1_t b1 = __riscv_vget_v_f32m1x3_f32m1(b, 1);
  vfloat32m1_t b2 = __riscv_vget_v_f32m1x3_f32m1(b, 2);
  float *_b0 = (float *)&b0;
  float *_b1 = (float *)&b1;
  float *_b2 = (float *)&b2;
  a[0] = _b0[c];
  a[1] = _b1[c];
  a[2] = _b2[c];
}

FORCE_INLINE void vst3_lane_u8(uint8_t *a, uint8x8x3_t b, const int c) {
  vuint8m1_t b0 = __riscv_vget_v_u8m1x3_u8m1(b, 0);
  vuint8m1_t b1 = __riscv_vget_v_u8m1x3_u8m1(b, 1);
  vuint8m1_t b2 = __riscv_vget_v_u8m1x3_u8m1(b, 2);
  uint8_t *_b0 = (uint8_t *)&b0;
  uint8_t *_b1 = (uint8_t *)&b1;
  uint8_t *_b2 = (uint8_t *)&b2;
  a[0] = _b0[c];
  a[1] = _b1[c];
  a[2] = _b2[c];
}

// FORCE_INLINE void vst3_lane_p8(poly8_t * ptr, poly8x8x3_t val, const int lane);

FORCE_INLINE void vst3_lane_u16(uint16_t *a, uint16x4x3_t b, const int c) {
  vuint16m1_t b0 = __riscv_vget_v_u16m1x3_u16m1(b, 0);
  vuint16m1_t b1 = __riscv_vget_v_u16m1x3_u16m1(b, 1);
  vuint16m1_t b2 = __riscv_vget_v_u16m1x3_u16m1(b, 2);
  uint16_t *_b0 = (uint16_t *)&b0;
  uint16_t *_b1 = (uint16_t *)&b1;
  uint16_t *_b2 = (uint16_t *)&b2;
  a[0] = _b0[c];
  a[1] = _b1[c];
  a[2] = _b2[c];
}

FORCE_INLINE void vst3_lane_u32(uint32_t *a, uint32x2x3_t b, const int c) {
  vuint32m1_t b0 = __riscv_vget_v_u32m1x3_u32m1(b, 0);
  vuint32m1_t b1 = __riscv_vget_v_u32m1x3_u32m1(b, 1);
  vuint32m1_t b2 = __riscv_vget_v_u32m1x3_u32m1(b, 2);
  uint32_t *_b0 = (uint32_t *)&b0;
  uint32_t *_b1 = (uint32_t *)&b1;
  uint32_t *_b2 = (uint32_t *)&b2;
  a[0] = _b0[c];
  a[1] = _b1[c];
  a[2] = _b2[c];
}

FORCE_INLINE void vst3q_lane_s16(int16_t *a, int16x8x3_t b, const int c) {
  vint16m1_t b0 = __riscv_vget_v_i16m1x3_i16m1(b, 0);
  vint16m1_t b1 = __riscv_vget_v_i16m1x3_i16m1(b, 1);
  vint16m1_t b2 = __riscv_vget_v_i16m1x3_i16m1(b, 2);
  int16_t *_b0 = (int16_t *)&b0;
  int16_t *_b1 = (int16_t *)&b1;
  int16_t *_b2 = (int16_t *)&b2;
  a[0] = _b0[c];
  a[1] = _b1[c];
  a[2] = _b2[c];
}

FORCE_INLINE void vst3q_lane_s32(int32_t *a, int32x4x3_t b, const int c) {
  vint32m1_t b0 = __riscv_vget_v_i32m1x3_i32m1(b, 0);
  vint32m1_t b1 = __riscv_vget_v_i32m1x3_i32m1(b, 1);
  vint32m1_t b2 = __riscv_vget_v_i32m1x3_i32m1(b, 2);
  int32_t *_b0 = (int32_t *)&b0;
  int32_t *_b1 = (int32_t *)&b1;
  int32_t *_b2 = (int32_t *)&b2;
  a[0] = _b0[c];
  a[1] = _b1[c];
  a[2] = _b2[c];
}

FORCE_INLINE void vst3q_lane_f32(float32_t *a, float32x4x3_t b, const int c) {
  vfloat32m1_t b0 = __riscv_vget_v_f32m1x3_f32m1(b, 0);
  vfloat32m1_t b1 = __riscv_vget_v_f32m1x3_f32m1(b, 1);
  vfloat32m1_t b2 = __riscv_vget_v_f32m1x3_f32m1(b, 2);
  float *_b0 = (float *)&b0;
  float *_b1 = (float *)&b1;
  float *_b2 = (float *)&b2;
  a[0] = _b0[c];
  a[1] = _b1[c];
  a[2] = _b2[c];
}

// FORCE_INLINE void vst3_lane_p16(poly16_t * ptr, poly16x4x3_t val, const int lane);

// FORCE_INLINE void vst3q_lane_p16(poly16_t * ptr, poly16x8x3_t val, const int lane);

// FORCE_INLINE void vst3q_lane_s8(int8_t * ptr, int8x16x3_t val, const int lane);

// FORCE_INLINE void vst3q_lane_u8(uint8_t * ptr, uint8x16x3_t val, const int lane);

// FORCE_INLINE void vst3q_lane_p8(poly8_t * ptr, poly8x16x3_t val, const int lane);

// FORCE_INLINE void vst3_lane_s64(int64_t * ptr, int64x1x3_t val, const int lane);

// FORCE_INLINE void vst3q_lane_s64(int64_t * ptr, int64x2x3_t val, const int lane);

// FORCE_INLINE void vst3_lane_u64(uint64_t * ptr, uint64x1x3_t val, const int lane);

// FORCE_INLINE void vst3q_lane_u64(uint64_t * ptr, uint64x2x3_t val, const int lane);

// FORCE_INLINE void vst3_lane_p64(poly64_t * ptr, poly64x1x3_t val, const int lane);

// FORCE_INLINE void vst3q_lane_p64(poly64_t * ptr, poly64x2x3_t val, const int lane);

// FORCE_INLINE void vst3_lane_f64(float64_t * ptr, float64x1x3_t val, const int lane);

// FORCE_INLINE void vst3q_lane_f64(float64_t * ptr, float64x2x3_t val, const int lane);

FORCE_INLINE void vst3q_lane_u16(uint16_t *a, uint16x8x3_t b, const int c) {
  vuint16m1_t b0 = __riscv_vget_v_u16m1x3_u16m1(b, 0);
  vuint16m1_t b1 = __riscv_vget_v_u16m1x3_u16m1(b, 1);
  vuint16m1_t b2 = __riscv_vget_v_u16m1x3_u16m1(b, 2);
  uint16_t *_b0 = (uint16_t *)&b0;
  uint16_t *_b1 = (uint16_t *)&b1;
  uint16_t *_b2 = (uint16_t *)&b2;
  a[0] = _b0[c];
  a[1] = _b1[c];
  a[2] = _b2[c];
}

FORCE_INLINE void vst3q_lane_u32(uint32_t *a, uint32x4x3_t b, const int c) {
  vuint32m1_t b0 = __riscv_vget_v_u32m1x3_u32m1(b, 0);
  vuint32m1_t b1 = __riscv_vget_v_u32m1x3_u32m1(b, 1);
  vuint32m1_t b2 = __riscv_vget_v_u32m1x3_u32m1(b, 2);
  uint32_t *_b0 = (uint32_t *)&b0;
  uint32_t *_b1 = (uint32_t *)&b1;
  uint32_t *_b2 = (uint32_t *)&b2;
  a[0] = _b0[c];
  a[1] = _b1[c];
  a[2] = _b2[c];
}

// FORCE_INLINE void vst3_lane_f16(float16_t * ptr, float16x4x3_t val, const int lane);

// FORCE_INLINE void vst3q_lane_f16(float16_t * ptr, float16x8x3_t val, const int lane);

FORCE_INLINE int8x8x4_t vld4_s8(const int8_t *a) { return __riscv_vlseg4e8_v_i8m1x4(a, 8); }

FORCE_INLINE int16x4x4_t vld4_s16(const int16_t *a) { return __riscv_vlseg4e16_v_i16m1x4(a, 4); }

FORCE_INLINE int32x2x4_t vld4_s32(const int32_t *a) { return __riscv_vlseg4e32_v_i32m1x4(a, 2); }

FORCE_INLINE float32x2x4_t vld4_f32(const float32_t *a) { return __riscv_vlseg4e32_v_f32m1x4(a, 2); }

FORCE_INLINE uint8x8x4_t vld4_u8(const uint8_t *a) { return __riscv_vlseg4e8_v_u8m1x4(a, 8); }

FORCE_INLINE uint16x4x4_t vld4_u16(const uint16_t *a) { return __riscv_vlseg4e16_v_u16m1x4(a, 4); }

FORCE_INLINE uint32x2x4_t vld4_u32(const uint32_t *a) { return __riscv_vlseg4e32_v_u32m1x4(a, 2); }

FORCE_INLINE int64x1x4_t vld4_s64(const int64_t *a) { return __riscv_vlseg4e64_v_i64m1x4(a, 1); }

FORCE_INLINE uint64x1x4_t vld4_u64(const uint64_t *a) { return __riscv_vlseg4e64_v_u64m1x4(a, 1); }

// FORCE_INLINE poly64x1x4_t vld4_p64(poly64_t const * ptr);

// FORCE_INLINE int64x2x4_t vld4q_s64(int64_t const * ptr);

// FORCE_INLINE uint64x2x4_t vld4q_u64(uint64_t const * ptr);

// FORCE_INLINE poly64x2x4_t vld4q_p64(poly64_t const * ptr);

// FORCE_INLINE float64x1x4_t vld4_f64(float64_t const * ptr);

// FORCE_INLINE float64x2x4_t vld4q_f64(float64_t const * ptr);

FORCE_INLINE int8x16x4_t vld4q_s8(const int8_t *a) { return __riscv_vlseg4e8_v_i8m1x4(a, 16); }

FORCE_INLINE int16x8x4_t vld4q_s16(const int16_t *a) { return __riscv_vlseg4e16_v_i16m1x4(a, 8); }

FORCE_INLINE int32x4x4_t vld4q_s32(const int32_t *a) { return __riscv_vlseg4e32_v_i32m1x4(a, 4); }

FORCE_INLINE float32x4x4_t vld4q_f32(const float32_t *a) { return __riscv_vlseg4e32_v_f32m1x4(a, 4); }

// FORCE_INLINE poly8x8x4_t vld4_p8(poly8_t const * ptr);

// FORCE_INLINE poly8x16x4_t vld4q_p8(poly8_t const * ptr);

// FORCE_INLINE poly16x4x4_t vld4_p16(poly16_t const * ptr);

// FORCE_INLINE poly16x8x4_t vld4q_p16(poly16_t const * ptr);

FORCE_INLINE uint8x16x4_t vld4q_u8(const uint8_t *a) { return __riscv_vlseg4e8_v_u8m1x4(a, 16); }

FORCE_INLINE uint16x8x4_t vld4q_u16(const uint16_t *a) { return __riscv_vlseg4e16_v_u16m1x4(a, 8); }

FORCE_INLINE uint32x4x4_t vld4q_u32(const uint32_t *a) { return __riscv_vlseg4e32_v_u32m1x4(a, 4); }

// FORCE_INLINE float16x4x4_t vld4_f16(float16_t const * ptr);

// FORCE_INLINE float16x8x4_t vld4q_f16(float16_t const * ptr);

FORCE_INLINE int8x8x4_t vld4_lane_s8(const int8_t *a, int8x8x4_t b, const int c) {
  vbool8_t mask = __riscv_vreinterpret_v_u8m1_b8(vdup_n_u8((uint8_t)(1 << c)));
  vint8m1_t c0 = __riscv_vmerge_vxm_i8m1(__riscv_vget_v_i8m1x4_i8m1(b, 0), a[0], mask, 8);
  vint8m1_t c1 = __riscv_vmerge_vxm_i8m1(__riscv_vget_v_i8m1x4_i8m1(b, 1), a[1], mask, 8);
  vint8m1_t c2 = __riscv_vmerge_vxm_i8m1(__riscv_vget_v_i8m1x4_i8m1(b, 2), a[2], mask, 8);
  vint8m1_t c3 = __riscv_vmerge_vxm_i8m1(__riscv_vget_v_i8m1x4_i8m1(b, 3), a[3], mask, 8);
  return __riscv_vcreate_v_i8m1x4(c0, c1, c2, c3);
}

FORCE_INLINE int16x4x4_t vld4_lane_s16(const int16_t *a, int16x4x4_t b, const int c) {
  vbool16_t mask = __riscv_vreinterpret_v_u8m1_b16(vdup_n_u8((uint8_t)(1 << c)));
  vint16m1_t c0 = __riscv_vmerge_vxm_i16m1(__riscv_vget_v_i16m1x4_i16m1(b, 0), a[0], mask, 4);
  vint16m1_t c1 = __riscv_vmerge_vxm_i16m1(__riscv_vget_v_i16m1x4_i16m1(b, 1), a[1], mask, 4);
  vint16m1_t c2 = __riscv_vmerge_vxm_i16m1(__riscv_vget_v_i16m1x4_i16m1(b, 2), a[2], mask, 4);
  vint16m1_t c3 = __riscv_vmerge_vxm_i16m1(__riscv_vget_v_i16m1x4_i16m1(b, 3), a[3], mask, 4);
  return __riscv_vcreate_v_i16m1x4(c0, c1, c2, c3);
}

FORCE_INLINE int32x2x4_t vld4_lane_s32(const int32_t *a, int32x2x4_t b, const int c) {
  vbool32_t mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << c)));
  vint32m1_t c0 = __riscv_vmerge_vxm_i32m1(__riscv_vget_v_i32m1x4_i32m1(b, 0), a[0], mask, 2);
  vint32m1_t c1 = __riscv_vmerge_vxm_i32m1(__riscv_vget_v_i32m1x4_i32m1(b, 1), a[1], mask, 2);
  vint32m1_t c2 = __riscv_vmerge_vxm_i32m1(__riscv_vget_v_i32m1x4_i32m1(b, 2), a[2], mask, 2);
  vint32m1_t c3 = __riscv_vmerge_vxm_i32m1(__riscv_vget_v_i32m1x4_i32m1(b, 3), a[3], mask, 2);
  return __riscv_vcreate_v_i32m1x4(c0, c1, c2, c3);
}

FORCE_INLINE float32x2x4_t vld4_lane_f32(const float32_t *a, float32x2x4_t b, const int c) {
  vbool32_t mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << c)));
  vfloat32m1_t c0 = __riscv_vfmerge_vfm_f32m1(__riscv_vget_v_f32m1x4_f32m1(b, 0), a[0], mask, 2);
  vfloat32m1_t c1 = __riscv_vfmerge_vfm_f32m1(__riscv_vget_v_f32m1x4_f32m1(b, 1), a[1], mask, 2);
  vfloat32m1_t c2 = __riscv_vfmerge_vfm_f32m1(__riscv_vget_v_f32m1x4_f32m1(b, 2), a[2], mask, 2);
  vfloat32m1_t c3 = __riscv_vfmerge_vfm_f32m1(__riscv_vget_v_f32m1x4_f32m1(b, 3), a[3], mask, 2);
  return __riscv_vcreate_v_f32m1x4(c0, c1, c2, c3);
}

FORCE_INLINE uint8x8x4_t vld4_lane_u8(const uint8_t *a, uint8x8x4_t b, const int c) {
  vbool8_t mask = __riscv_vreinterpret_v_u8m1_b8(vdup_n_u8((uint8_t)(1 << c)));
  vuint8m1_t c0 = __riscv_vmerge_vxm_u8m1(__riscv_vget_v_u8m1x4_u8m1(b, 0), a[0], mask, 8);
  vuint8m1_t c1 = __riscv_vmerge_vxm_u8m1(__riscv_vget_v_u8m1x4_u8m1(b, 1), a[1], mask, 8);
  vuint8m1_t c2 = __riscv_vmerge_vxm_u8m1(__riscv_vget_v_u8m1x4_u8m1(b, 2), a[2], mask, 8);
  vuint8m1_t c3 = __riscv_vmerge_vxm_u8m1(__riscv_vget_v_u8m1x4_u8m1(b, 3), a[3], mask, 8);
  return __riscv_vcreate_v_u8m1x4(c0, c1, c2, c3);
}

// FORCE_INLINE poly8x8x4_t vld4_lane_p8(poly8_t const * ptr, poly8x8x4_t src, const int lane);

// FORCE_INLINE int8x16x4_t vld4q_lane_s8(int8_t const * ptr, int8x16x4_t src, const int lane);

// FORCE_INLINE uint8x16x4_t vld4q_lane_u8(uint8_t const * ptr, uint8x16x4_t src, const int lane);

// FORCE_INLINE poly8x16x4_t vld4q_lane_p8(poly8_t const * ptr, poly8x16x4_t src, const int lane);

// FORCE_INLINE int64x1x4_t vld4_lane_s64(int64_t const * ptr, int64x1x4_t src, const int lane);

// FORCE_INLINE int64x2x4_t vld4q_lane_s64(int64_t const * ptr, int64x2x4_t src, const int lane);

// FORCE_INLINE uint64x1x4_t vld4_lane_u64(uint64_t const * ptr, uint64x1x4_t src, const int lane);

// FORCE_INLINE uint64x2x4_t vld4q_lane_u64(uint64_t const * ptr, uint64x2x4_t src, const int lane);

// FORCE_INLINE poly64x1x4_t vld4_lane_p64(poly64_t const * ptr, poly64x1x4_t src, const int lane);

// FORCE_INLINE poly64x2x4_t vld4q_lane_p64(poly64_t const * ptr, poly64x2x4_t src, const int lane);

// FORCE_INLINE float64x1x4_t vld4_lane_f64(float64_t const * ptr, float64x1x4_t src, const int lane);

// FORCE_INLINE float64x2x4_t vld4q_lane_f64(float64_t const * ptr, float64x2x4_t src, const int lane);

FORCE_INLINE uint16x4x4_t vld4_lane_u16(const uint16_t *a, uint16x4x4_t b, const int c) {
  vbool16_t mask = __riscv_vreinterpret_v_u8m1_b16(vdup_n_u8((uint8_t)(1 << c)));
  vuint16m1_t c0 = __riscv_vmerge_vxm_u16m1(__riscv_vget_v_u16m1x4_u16m1(b, 0), a[0], mask, 4);
  vuint16m1_t c1 = __riscv_vmerge_vxm_u16m1(__riscv_vget_v_u16m1x4_u16m1(b, 1), a[1], mask, 4);
  vuint16m1_t c2 = __riscv_vmerge_vxm_u16m1(__riscv_vget_v_u16m1x4_u16m1(b, 2), a[2], mask, 4);
  vuint16m1_t c3 = __riscv_vmerge_vxm_u16m1(__riscv_vget_v_u16m1x4_u16m1(b, 3), a[3], mask, 4);
  return __riscv_vcreate_v_u16m1x4(c0, c1, c2, c3);
}

FORCE_INLINE uint32x2x4_t vld4_lane_u32(const uint32_t *a, uint32x2x4_t b, const int c) {
  vbool32_t mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << c)));
  vuint32m1_t c0 = __riscv_vmerge_vxm_u32m1(__riscv_vget_v_u32m1x4_u32m1(b, 0), a[0], mask, 2);
  vuint32m1_t c1 = __riscv_vmerge_vxm_u32m1(__riscv_vget_v_u32m1x4_u32m1(b, 1), a[1], mask, 2);
  vuint32m1_t c2 = __riscv_vmerge_vxm_u32m1(__riscv_vget_v_u32m1x4_u32m1(b, 2), a[2], mask, 2);
  vuint32m1_t c3 = __riscv_vmerge_vxm_u32m1(__riscv_vget_v_u32m1x4_u32m1(b, 3), a[3], mask, 2);
  return __riscv_vcreate_v_u32m1x4(c0, c1, c2, c3);
}

FORCE_INLINE int16x8x4_t vld4q_lane_s16(const int16_t *a, int16x8x4_t b, const int c) {
  vbool16_t mask = __riscv_vreinterpret_v_u8m1_b16(vdup_n_u8((uint8_t)(1 << c)));
  vint16m1_t c0 = __riscv_vmerge_vxm_i16m1(__riscv_vget_v_i16m1x4_i16m1(b, 0), a[0], mask, 8);
  vint16m1_t c1 = __riscv_vmerge_vxm_i16m1(__riscv_vget_v_i16m1x4_i16m1(b, 1), a[1], mask, 8);
  vint16m1_t c2 = __riscv_vmerge_vxm_i16m1(__riscv_vget_v_i16m1x4_i16m1(b, 2), a[2], mask, 8);
  vint16m1_t c3 = __riscv_vmerge_vxm_i16m1(__riscv_vget_v_i16m1x4_i16m1(b, 3), a[3], mask, 8);
  return __riscv_vcreate_v_i16m1x4(c0, c1, c2, c3);
}

FORCE_INLINE int32x4x4_t vld4q_lane_s32(const int32_t *a, int32x4x4_t b, const int c) {
  vbool32_t mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << c)));
  vint32m1_t c0 = __riscv_vmerge_vxm_i32m1(__riscv_vget_v_i32m1x4_i32m1(b, 0), a[0], mask, 4);
  vint32m1_t c1 = __riscv_vmerge_vxm_i32m1(__riscv_vget_v_i32m1x4_i32m1(b, 1), a[1], mask, 4);
  vint32m1_t c2 = __riscv_vmerge_vxm_i32m1(__riscv_vget_v_i32m1x4_i32m1(b, 2), a[2], mask, 4);
  vint32m1_t c3 = __riscv_vmerge_vxm_i32m1(__riscv_vget_v_i32m1x4_i32m1(b, 3), a[3], mask, 4);
  return __riscv_vcreate_v_i32m1x4(c0, c1, c2, c3);
}

FORCE_INLINE float32x4x4_t vld4q_lane_f32(const float32_t *a, float32x4x4_t b, const int c) {
  vbool32_t mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << c)));
  vfloat32m1_t c0 = __riscv_vfmerge_vfm_f32m1(__riscv_vget_v_f32m1x4_f32m1(b, 0), a[0], mask, 4);
  vfloat32m1_t c1 = __riscv_vfmerge_vfm_f32m1(__riscv_vget_v_f32m1x4_f32m1(b, 1), a[1], mask, 4);
  vfloat32m1_t c2 = __riscv_vfmerge_vfm_f32m1(__riscv_vget_v_f32m1x4_f32m1(b, 2), a[2], mask, 4);
  vfloat32m1_t c3 = __riscv_vfmerge_vfm_f32m1(__riscv_vget_v_f32m1x4_f32m1(b, 3), a[3], mask, 4);
  return __riscv_vcreate_v_f32m1x4(c0, c1, c2, c3);
}

// FORCE_INLINE poly16x4x4_t vld4_lane_p16(poly16_t const * ptr, poly16x4x4_t src, const int lane);

// FORCE_INLINE poly16x8x4_t vld4q_lane_p16(poly16_t const * ptr, poly16x8x4_t src, const int lane);

FORCE_INLINE uint16x8x4_t vld4q_lane_u16(const uint16_t *a, uint16x8x4_t b, const int c) {
  vbool16_t mask = __riscv_vreinterpret_v_u8m1_b16(vdup_n_u8((uint8_t)(1 << c)));
  vuint16m1_t c0 = __riscv_vmerge_vxm_u16m1(__riscv_vget_v_u16m1x4_u16m1(b, 0), a[0], mask, 8);
  vuint16m1_t c1 = __riscv_vmerge_vxm_u16m1(__riscv_vget_v_u16m1x4_u16m1(b, 1), a[1], mask, 8);
  vuint16m1_t c2 = __riscv_vmerge_vxm_u16m1(__riscv_vget_v_u16m1x4_u16m1(b, 2), a[2], mask, 8);
  vuint16m1_t c3 = __riscv_vmerge_vxm_u16m1(__riscv_vget_v_u16m1x4_u16m1(b, 3), a[3], mask, 8);
  return __riscv_vcreate_v_u16m1x4(c0, c1, c2, c3);
}

FORCE_INLINE uint32x4x4_t vld4q_lane_u32(const uint32_t *a, uint32x4x4_t b, const int c) {
  vbool32_t mask = __riscv_vreinterpret_v_u8m1_b32(vdup_n_u8((uint8_t)(1 << c)));
  vuint32m1_t c0 = __riscv_vmerge_vxm_u32m1(__riscv_vget_v_u32m1x4_u32m1(b, 0), a[0], mask, 4);
  vuint32m1_t c1 = __riscv_vmerge_vxm_u32m1(__riscv_vget_v_u32m1x4_u32m1(b, 1), a[1], mask, 4);
  vuint32m1_t c2 = __riscv_vmerge_vxm_u32m1(__riscv_vget_v_u32m1x4_u32m1(b, 2), a[2], mask, 4);
  vuint32m1_t c3 = __riscv_vmerge_vxm_u32m1(__riscv_vget_v_u32m1x4_u32m1(b, 3), a[3], mask, 4);
  return __riscv_vcreate_v_u32m1x4(c0, c1, c2, c3);
}

// FORCE_INLINE float16x4x4_t vld4_lane_f16(float16_t const * ptr, float16x4x4_t src, const int lane);

// FORCE_INLINE float16x8x4_t vld4q_lane_f16(float16_t const * ptr, float16x8x4_t src, const int lane);

FORCE_INLINE int8x8x4_t vld4_dup_s8(const int8_t *a) {
  return __riscv_vcreate_v_i8m1x4(vdup_n_s8(a[0]), vdup_n_s8(a[1]), vdup_n_s8(a[2]), vdup_n_s8(a[3]));
}

// FORCE_INLINE int8x16x4_t vld4q_dup_s8(int8_t const * ptr);

FORCE_INLINE int16x4x4_t vld4_dup_s16(const int16_t *a) {
  return __riscv_vcreate_v_i16m1x4(vdup_n_s16(a[0]), vdup_n_s16(a[1]), vdup_n_s16(a[2]), vdup_n_s16(a[3]));
}

// FORCE_INLINE int16x8x4_t vld4q_dup_s16(int16_t const * ptr);

FORCE_INLINE int32x2x4_t vld4_dup_s32(const int32_t *a) {
  return __riscv_vcreate_v_i32m1x4(vdup_n_s32(a[0]), vdup_n_s32(a[1]), vdup_n_s32(a[2]), vdup_n_s32(a[3]));
}

// FORCE_INLINE int32x4x4_t vld4q_dup_s32(int32_t const * ptr);

FORCE_INLINE float32x2x4_t vld4_dup_f32(const float32_t *a) {
  return __riscv_vcreate_v_f32m1x4(vdup_n_f32(a[0]), vdup_n_f32(a[1]), vdup_n_f32(a[2]), vdup_n_f32(a[3]));
}

// FORCE_INLINE float32x4x4_t vld4q_dup_f32(float32_t const * ptr);

// FORCE_INLINE poly8x8x4_t vld4_dup_p8(poly8_t const * ptr);

// FORCE_INLINE poly8x16x4_t vld4q_dup_p8(poly8_t const * ptr);

// FORCE_INLINE poly16x4x4_t vld4_dup_p16(poly16_t const * ptr);

// FORCE_INLINE poly16x8x4_t vld4q_dup_p16(poly16_t const * ptr);

FORCE_INLINE uint8x8x4_t vld4_dup_u8(const uint8_t *a) {
  return __riscv_vcreate_v_u8m1x4(vdup_n_u8(a[0]), vdup_n_u8(a[1]), vdup_n_u8(a[2]), vdup_n_u8(a[3]));
}

// FORCE_INLINE uint8x16x4_t vld4q_dup_u8(uint8_t const * ptr);

FORCE_INLINE uint16x4x4_t vld4_dup_u16(const uint16_t *a) {
  return __riscv_vcreate_v_u16m1x4(vdup_n_u16(a[0]), vdup_n_u16(a[1]), vdup_n_u16(a[2]), vdup_n_u16(a[3]));
}

// FORCE_INLINE uint16x8x4_t vld4q_dup_u16(uint16_t const * ptr);

FORCE_INLINE uint32x2x4_t vld4_dup_u32(const uint32_t *a) {
  return __riscv_vcreate_v_u32m1x4(vdup_n_u32(a[0]), vdup_n_u32(a[1]), vdup_n_u32(a[2]), vdup_n_u32(a[3]));
}

// FORCE_INLINE uint32x4x4_t vld4q_dup_u32(uint32_t const * ptr);

// FORCE_INLINE float16x4x4_t vld4_dup_f16(float16_t const * ptr);

// FORCE_INLINE float16x8x4_t vld4q_dup_f16(float16_t const * ptr);

FORCE_INLINE int64x1x4_t vld4_dup_s64(const int64_t *a) {
  return __riscv_vcreate_v_i64m1x4(vdup_n_s64(a[0]), vdup_n_s64(a[1]), vdup_n_s64(a[2]), vdup_n_s64(a[3]));
}

FORCE_INLINE uint64x1x4_t vld4_dup_u64(const uint64_t *a) {
  return __riscv_vcreate_v_u64m1x4(vdup_n_u64(a[0]), vdup_n_u64(a[1]), vdup_n_u64(a[2]), vdup_n_u64(a[3]));
}

// FORCE_INLINE poly64x1x4_t vld4_dup_p64(poly64_t const * ptr);

// FORCE_INLINE int64x2x4_t vld4q_dup_s64(int64_t const * ptr);

// FORCE_INLINE uint64x2x4_t vld4q_dup_u64(uint64_t const * ptr);

// FORCE_INLINE poly64x2x4_t vld4q_dup_p64(poly64_t const * ptr);

// FORCE_INLINE float64x1x4_t vld4_dup_f64(float64_t const * ptr);

// FORCE_INLINE float64x2x4_t vld4q_dup_f64(float64_t const * ptr);

FORCE_INLINE void vst4_s8(int8_t *a, int8x8x4_t b) { return __riscv_vsseg4e8_v_i8m1x4(a, b, 8); }

FORCE_INLINE void vst4_s16(int16_t *a, int16x4x4_t b) { return __riscv_vsseg4e16_v_i16m1x4(a, b, 4); }

FORCE_INLINE void vst4_s32(int32_t *a, int32x2x4_t b) { return __riscv_vsseg4e32_v_i32m1x4(a, b, 2); }

FORCE_INLINE void vst4_f32(float32_t *a, float32x2x4_t b) { return __riscv_vsseg4e32_v_f32m1x4(a, b, 2); }

FORCE_INLINE void vst4_u8(uint8_t *a, uint8x8x4_t b) { return __riscv_vsseg4e8_v_u8m1x4(a, b, 8); }

FORCE_INLINE void vst4_u16(uint16_t *a, uint16x4x4_t b) { return __riscv_vsseg4e16_v_u16m1x4(a, b, 4); }

FORCE_INLINE void vst4_u32(uint32_t *a, uint32x2x4_t b) { return __riscv_vsseg4e32_v_u32m1x4(a, b, 2); }

FORCE_INLINE void vst4_s64(int64_t *a, int64x1x4_t b) { return __riscv_vsseg4e64_v_i64m1x4(a, b, 1); }

FORCE_INLINE void vst4_u64(uint64_t *a, uint64x1x4_t b) { return __riscv_vsseg4e64_v_u64m1x4(a, b, 1); }

// FORCE_INLINE void vst4_p64(poly64_t * ptr, poly64x1x4_t val);

// FORCE_INLINE void vst4q_s64(int64_t * ptr, int64x2x4_t val);

// FORCE_INLINE void vst4q_u64(uint64_t * ptr, uint64x2x4_t val);

// FORCE_INLINE void vst4q_p64(poly64_t * ptr, poly64x2x4_t val);

// FORCE_INLINE void vst4_f64(float64_t * ptr, float64x1x4_t val);

// FORCE_INLINE void vst4q_f64(float64_t * ptr, float64x2x4_t val);

FORCE_INLINE void vst4q_s8(int8_t *a, int8x16x4_t b) { return __riscv_vsseg4e8_v_i8m1x4(a, b, 16); }

FORCE_INLINE void vst4q_s16(int16_t *a, int16x8x4_t b) { return __riscv_vsseg4e16_v_i16m1x4(a, b, 8); }

FORCE_INLINE void vst4q_s32(int32_t *a, int32x4x4_t b) { return __riscv_vsseg4e32_v_i32m1x4(a, b, 4); }

FORCE_INLINE void vst4q_f32(float32_t *a, float32x4x4_t b) { return __riscv_vsseg4e32_v_f32m1x4(a, b, 4); }

// FORCE_INLINE void vst4_p8(poly8_t * ptr, poly8x8x4_t val);

// FORCE_INLINE void vst4q_p8(poly8_t * ptr, poly8x16x4_t val);

// FORCE_INLINE void vst4_p16(poly16_t * ptr, poly16x4x4_t val);

// FORCE_INLINE void vst4q_p16(poly16_t * ptr, poly16x8x4_t val);

FORCE_INLINE void vst4q_u8(uint8_t *a, uint8x16x4_t b) { return __riscv_vsseg4e8_v_u8m1x4(a, b, 16); }

FORCE_INLINE void vst4q_u16(uint16_t *a, uint16x8x4_t b) { return __riscv_vsseg4e16_v_u16m1x4(a, b, 8); }

FORCE_INLINE void vst4q_u32(uint32_t *a, uint32x4x4_t b) { return __riscv_vsseg4e32_v_u32m1x4(a, b, 4); }

// FORCE_INLINE void vst4_f16(float16_t * ptr, float16x4x4_t val);

// FORCE_INLINE void vst4q_f16(float16_t * ptr, float16x8x4_t val);

FORCE_INLINE void vst4_lane_s8(int8_t *a, int8x8x4_t b, const int c) {
  vint8m1_t b0 = __riscv_vget_v_i8m1x4_i8m1(b, 0);
  vint8m1_t b1 = __riscv_vget_v_i8m1x4_i8m1(b, 1);
  vint8m1_t b2 = __riscv_vget_v_i8m1x4_i8m1(b, 2);
  vint8m1_t b3 = __riscv_vget_v_i8m1x4_i8m1(b, 3);
  int8_t *_b0 = (int8_t *)&b0;
  int8_t *_b1 = (int8_t *)&b1;
  int8_t *_b2 = (int8_t *)&b2;
  int8_t *_b3 = (int8_t *)&b3;
  a[0] = _b0[c];
  a[1] = _b1[c];
  a[2] = _b2[c];
  a[3] = _b3[c];
}

FORCE_INLINE void vst4_lane_s16(int16_t *a, int16x4x4_t b, const int c) {
  vint16m1_t b0 = __riscv_vget_v_i16m1x4_i16m1(b, 0);
  vint16m1_t b1 = __riscv_vget_v_i16m1x4_i16m1(b, 1);
  vint16m1_t b2 = __riscv_vget_v_i16m1x4_i16m1(b, 2);
  vint16m1_t b3 = __riscv_vget_v_i16m1x4_i16m1(b, 3);
  int16_t *_b0 = (int16_t *)&b0;
  int16_t *_b1 = (int16_t *)&b1;
  int16_t *_b2 = (int16_t *)&b2;
  int16_t *_b3 = (int16_t *)&b3;
  a[0] = _b0[c];
  a[1] = _b1[c];
  a[2] = _b2[c];
  a[3] = _b3[c];
}

FORCE_INLINE void vst4_lane_s32(int32_t *a, int32x2x4_t b, const int c) {
  vint32m1_t b0 = __riscv_vget_v_i32m1x4_i32m1(b, 0);
  vint32m1_t b1 = __riscv_vget_v_i32m1x4_i32m1(b, 1);
  vint32m1_t b2 = __riscv_vget_v_i32m1x4_i32m1(b, 2);
  vint32m1_t b3 = __riscv_vget_v_i32m1x4_i32m1(b, 3);
  int32_t *_b0 = (int32_t *)&b0;
  int32_t *_b1 = (int32_t *)&b1;
  int32_t *_b2 = (int32_t *)&b2;
  int32_t *_b3 = (int32_t *)&b3;
  a[0] = _b0[c];
  a[1] = _b1[c];
  a[2] = _b2[c];
  a[3] = _b3[c];
}

FORCE_INLINE void vst4_lane_f32(float32_t *a, float32x2x4_t b, const int c) {
  vfloat32m1_t b0 = __riscv_vget_v_f32m1x4_f32m1(b, 0);
  vfloat32m1_t b1 = __riscv_vget_v_f32m1x4_f32m1(b, 1);
  vfloat32m1_t b2 = __riscv_vget_v_f32m1x4_f32m1(b, 2);
  vfloat32m1_t b3 = __riscv_vget_v_f32m1x4_f32m1(b, 3);
  float *_b0 = (float *)&b0;
  float *_b1 = (float *)&b1;
  float *_b2 = (float *)&b2;
  float *_b3 = (float *)&b3;
  a[0] = _b0[c];
  a[1] = _b1[c];
  a[2] = _b2[c];
  a[3] = _b3[c];
}

FORCE_INLINE void vst4_lane_u8(uint8_t *a, uint8x8x4_t b, const int c) {
  vuint8m1_t b0 = __riscv_vget_v_u8m1x4_u8m1(b, 0);
  vuint8m1_t b1 = __riscv_vget_v_u8m1x4_u8m1(b, 1);
  vuint8m1_t b2 = __riscv_vget_v_u8m1x4_u8m1(b, 2);
  vuint8m1_t b3 = __riscv_vget_v_u8m1x4_u8m1(b, 3);
  uint8_t *_b0 = (uint8_t *)&b0;
  uint8_t *_b1 = (uint8_t *)&b1;
  uint8_t *_b2 = (uint8_t *)&b2;
  uint8_t *_b3 = (uint8_t *)&b3;
  a[0] = _b0[c];
  a[1] = _b1[c];
  a[2] = _b2[c];
  a[3] = _b3[c];
}

// FORCE_INLINE void vst4_lane_p8(poly8_t * ptr, poly8x8x4_t val, const int lane);

FORCE_INLINE void vst4_lane_u16(uint16_t *a, uint16x4x4_t b, const int c) {
  vuint16m1_t b0 = __riscv_vget_v_u16m1x4_u16m1(b, 0);
  vuint16m1_t b1 = __riscv_vget_v_u16m1x4_u16m1(b, 1);
  vuint16m1_t b2 = __riscv_vget_v_u16m1x4_u16m1(b, 2);
  vuint16m1_t b3 = __riscv_vget_v_u16m1x4_u16m1(b, 3);
  uint16_t *_b0 = (uint16_t *)&b0;
  uint16_t *_b1 = (uint16_t *)&b1;
  uint16_t *_b2 = (uint16_t *)&b2;
  uint16_t *_b3 = (uint16_t *)&b3;
  a[0] = _b0[c];
  a[1] = _b1[c];
  a[2] = _b2[c];
  a[3] = _b3[c];
}

FORCE_INLINE void vst4_lane_u32(uint32_t *a, uint32x2x4_t b, const int c) {
  vuint32m1_t b0 = __riscv_vget_v_u32m1x4_u32m1(b, 0);
  vuint32m1_t b1 = __riscv_vget_v_u32m1x4_u32m1(b, 1);
  vuint32m1_t b2 = __riscv_vget_v_u32m1x4_u32m1(b, 2);
  vuint32m1_t b3 = __riscv_vget_v_u32m1x4_u32m1(b, 3);
  uint32_t *_b0 = (uint32_t *)&b0;
  uint32_t *_b1 = (uint32_t *)&b1;
  uint32_t *_b2 = (uint32_t *)&b2;
  uint32_t *_b3 = (uint32_t *)&b3;
  a[0] = _b0[c];
  a[1] = _b1[c];
  a[2] = _b2[c];
  a[3] = _b3[c];
}

FORCE_INLINE void vst4q_lane_s16(int16_t *a, int16x8x4_t b, const int c) {
  vint16m1_t b0 = __riscv_vget_v_i16m1x4_i16m1(b, 0);
  vint16m1_t b1 = __riscv_vget_v_i16m1x4_i16m1(b, 1);
  vint16m1_t b2 = __riscv_vget_v_i16m1x4_i16m1(b, 2);
  vint16m1_t b3 = __riscv_vget_v_i16m1x4_i16m1(b, 3);
  int16_t *_b0 = (int16_t *)&b0;
  int16_t *_b1 = (int16_t *)&b1;
  int16_t *_b2 = (int16_t *)&b2;
  int16_t *_b3 = (int16_t *)&b3;
  a[0] = _b0[c];
  a[1] = _b1[c];
  a[2] = _b2[c];
  a[3] = _b3[c];
}

FORCE_INLINE void vst4q_lane_s32(int32_t *a, int32x4x4_t b, const int c) {
  vint32m1_t b0 = __riscv_vget_v_i32m1x4_i32m1(b, 0);
  vint32m1_t b1 = __riscv_vget_v_i32m1x4_i32m1(b, 1);
  vint32m1_t b2 = __riscv_vget_v_i32m1x4_i32m1(b, 2);
  vint32m1_t b3 = __riscv_vget_v_i32m1x4_i32m1(b, 3);
  int32_t *_b0 = (int32_t *)&b0;
  int32_t *_b1 = (int32_t *)&b1;
  int32_t *_b2 = (int32_t *)&b2;
  int32_t *_b3 = (int32_t *)&b3;
  a[0] = _b0[c];
  a[1] = _b1[c];
  a[2] = _b2[c];
  a[3] = _b3[c];
}

FORCE_INLINE void vst4q_lane_f32(float32_t *a, float32x4x4_t b, const int c) {
  vfloat32m1_t b0 = __riscv_vget_v_f32m1x4_f32m1(b, 0);
  vfloat32m1_t b1 = __riscv_vget_v_f32m1x4_f32m1(b, 1);
  vfloat32m1_t b2 = __riscv_vget_v_f32m1x4_f32m1(b, 2);
  vfloat32m1_t b3 = __riscv_vget_v_f32m1x4_f32m1(b, 3);
  float *_b0 = (float *)&b0;
  float *_b1 = (float *)&b1;
  float *_b2 = (float *)&b2;
  float *_b3 = (float *)&b3;
  a[0] = _b0[c];
  a[1] = _b1[c];
  a[2] = _b2[c];
  a[3] = _b3[c];
}

// FORCE_INLINE void vst4_lane_p16(poly16_t * ptr, poly16x4x4_t val, const int lane);

// FORCE_INLINE void vst4q_lane_p16(poly16_t * ptr, poly16x8x4_t val, const int lane);

// FORCE_INLINE void vst4q_lane_s8(int8_t * ptr, int8x16x4_t val, const int lane);

// FORCE_INLINE void vst4q_lane_u8(uint8_t * ptr, uint8x16x4_t val, const int lane);

// FORCE_INLINE void vst4q_lane_p8(poly8_t * ptr, poly8x16x4_t val, const int lane);

// FORCE_INLINE void vst4_lane_s64(int64_t * ptr, int64x1x4_t val, const int lane);

// FORCE_INLINE void vst4q_lane_s64(int64_t * ptr, int64x2x4_t val, const int lane);

// FORCE_INLINE void vst4_lane_u64(uint64_t * ptr, uint64x1x4_t val, const int lane);

// FORCE_INLINE void vst4q_lane_u64(uint64_t * ptr, uint64x2x4_t val, const int lane);

// FORCE_INLINE void vst4_lane_p64(poly64_t * ptr, poly64x1x4_t val, const int lane);

// FORCE_INLINE void vst4q_lane_p64(poly64_t * ptr, poly64x2x4_t val, const int lane);

// FORCE_INLINE void vst4_lane_f64(float64_t * ptr, float64x1x4_t val, const int lane);

// FORCE_INLINE void vst4q_lane_f64(float64_t * ptr, float64x2x4_t val, const int lane);

FORCE_INLINE void vst1_s8_x2(int8_t *ptr, int8x8x2_t val) {
  vint8m1_t val0 = __riscv_vget_v_i8m1x2_i8m1(val, 0);
  vint8m1_t val1 = __riscv_vget_v_i8m1x2_i8m1(val, 1);
  vint8m1_t v = __riscv_vslideup_vx_i8m1(val0, val1, 8, 16);
  __riscv_vse8_v_i8m1(ptr, v, 16);
}

FORCE_INLINE void vst1q_s8_x2(int8_t *ptr, int8x16x2_t val) {
  vint8m2_t val0 = __riscv_vlmul_ext_v_i8m1_i8m2(__riscv_vget_v_i8m1x2_i8m1(val, 0));
  vint8m2_t val1 = __riscv_vlmul_ext_v_i8m1_i8m2(__riscv_vget_v_i8m1x2_i8m1(val, 1));
  vint8m2_t v = __riscv_vslideup_vx_i8m2(val0, val1, 16, 32);
  __riscv_vse8_v_i8m2(ptr, v, 32);
}

FORCE_INLINE void vst1_s16_x2(int16_t *ptr, int16x4x2_t val) {
  vint16m1_t val0 = __riscv_vget_v_i16m1x2_i16m1(val, 0);
  vint16m1_t val1 = __riscv_vget_v_i16m1x2_i16m1(val, 1);
  vint16m1_t v = __riscv_vslideup_vx_i16m1(val0, val1, 4, 8);
  __riscv_vse16_v_i16m1(ptr, v, 8);
}

FORCE_INLINE void vst1q_s16_x2(int16_t *ptr, int16x8x2_t val) {
  vint16m2_t val0 = __riscv_vlmul_ext_v_i16m1_i16m2(__riscv_vget_v_i16m1x2_i16m1(val, 0));
  vint16m2_t val1 = __riscv_vlmul_ext_v_i16m1_i16m2(__riscv_vget_v_i16m1x2_i16m1(val, 1));
  vint16m2_t v = __riscv_vslideup_vx_i16m2(val0, val1, 8, 16);
  __riscv_vse16_v_i16m2(ptr, v, 16);
}

FORCE_INLINE void vst1_s32_x2(int32_t *ptr, int32x2x2_t val) {
  vint32m1_t val0 = __riscv_vget_v_i32m1x2_i32m1(val, 0);
  vint32m1_t val1 = __riscv_vget_v_i32m1x2_i32m1(val, 1);
  vint32m1_t v = __riscv_vslideup_vx_i32m1(val0, val1, 2, 4);
  __riscv_vse32_v_i32m1(ptr, v, 4);
}

FORCE_INLINE void vst1q_s32_x2(int32_t *ptr, int32x4x2_t val) {
  vint32m2_t val0 = __riscv_vlmul_ext_v_i32m1_i32m2(__riscv_vget_v_i32m1x2_i32m1(val, 0));
  vint32m2_t val1 = __riscv_vlmul_ext_v_i32m1_i32m2(__riscv_vget_v_i32m1x2_i32m1(val, 1));
  vint32m2_t v = __riscv_vslideup_vx_i32m2(val0, val1, 4, 8);
  __riscv_vse32_v_i32m2(ptr, v, 8);
}

FORCE_INLINE void vst1_u8_x2(uint8_t *ptr, uint8x8x2_t val) {
  vuint8m1_t val0 = __riscv_vget_v_u8m1x2_u8m1(val, 0);
  vuint8m1_t val1 = __riscv_vget_v_u8m1x2_u8m1(val, 1);
  vuint8m1_t v = __riscv_vslideup_vx_u8m1(val0, val1, 8, 16);
  __riscv_vse8_v_u8m1(ptr, v, 16);
}

FORCE_INLINE void vst1q_u8_x2(uint8_t *ptr, uint8x16x2_t val) {
  vuint8m2_t val0 = __riscv_vlmul_ext_v_u8m1_u8m2(__riscv_vget_v_u8m1x2_u8m1(val, 0));
  vuint8m2_t val1 = __riscv_vlmul_ext_v_u8m1_u8m2(__riscv_vget_v_u8m1x2_u8m1(val, 1));
  vuint8m2_t v = __riscv_vslideup_vx_u8m2(val0, val1, 16, 32);
  __riscv_vse8_v_u8m2(ptr, v, 32);
}

FORCE_INLINE void vst1_u16_x2(uint16_t *ptr, uint16x4x2_t val) {
  vuint16m1_t val0 = __riscv_vget_v_u16m1x2_u16m1(val, 0);
  vuint16m1_t val1 = __riscv_vget_v_u16m1x2_u16m1(val, 1);
  vuint16m1_t v = __riscv_vslideup_vx_u16m1(val0, val1, 4, 8);
  __riscv_vse16_v_u16m1(ptr, v, 8);
}

FORCE_INLINE void vst1q_u16_x2(uint16_t *ptr, uint16x8x2_t val) {
  vuint16m2_t val0 = __riscv_vlmul_ext_v_u16m1_u16m2(__riscv_vget_v_u16m1x2_u16m1(val, 0));
  vuint16m2_t val1 = __riscv_vlmul_ext_v_u16m1_u16m2(__riscv_vget_v_u16m1x2_u16m1(val, 1));
  vuint16m2_t v = __riscv_vslideup_vx_u16m2(val0, val1, 8, 16);
  __riscv_vse16_v_u16m2(ptr, v, 16);
}

FORCE_INLINE void vst1_u32_x2(uint32_t *ptr, uint32x2x2_t val) {
  vuint32m1_t val0 = __riscv_vget_v_u32m1x2_u32m1(val, 0);
  vuint32m1_t val1 = __riscv_vget_v_u32m1x2_u32m1(val, 1);
  vuint32m1_t v = __riscv_vslideup_vx_u32m1(val0, val1, 2, 4);
  __riscv_vse32_v_u32m1(ptr, v, 4);
}

FORCE_INLINE void vst1q_u32_x2(uint32_t *ptr, uint32x4x2_t val) {
  vuint32m2_t val0 = __riscv_vlmul_ext_v_u32m1_u32m2(__riscv_vget_v_u32m1x2_u32m1(val, 0));
  vuint32m2_t val1 = __riscv_vlmul_ext_v_u32m1_u32m2(__riscv_vget_v_u32m1x2_u32m1(val, 1));
  vuint32m2_t v = __riscv_vslideup_vx_u32m2(val0, val1, 4, 8);
  __riscv_vse32_v_u32m2(ptr, v, 8);
}

// FORCE_INLINE void vst1_f16_x2(float16_t * ptr, float16x4x2_t val);

// FORCE_INLINE void vst1q_f16_x2(float16_t * ptr, float16x8x2_t val);

FORCE_INLINE void vst1_f32_x2(float32_t *ptr, float32x2x2_t val) {
  vfloat32m1_t val0 = __riscv_vget_v_f32m1x2_f32m1(val, 0);
  vfloat32m1_t val1 = __riscv_vget_v_f32m1x2_f32m1(val, 1);
  vfloat32m1_t v = __riscv_vslideup_vx_f32m1(val0, val1, 2, 4);
  __riscv_vse32_v_f32m1(ptr, v, 4);
}

FORCE_INLINE void vst1q_f32_x2(float32_t *ptr, float32x4x2_t val) {
  vfloat32m2_t val0 = __riscv_vlmul_ext_v_f32m1_f32m2(__riscv_vget_v_f32m1x2_f32m1(val, 0));
  vfloat32m2_t val1 = __riscv_vlmul_ext_v_f32m1_f32m2(__riscv_vget_v_f32m1x2_f32m1(val, 1));
  vfloat32m2_t v = __riscv_vslideup_vx_f32m2(val0, val1, 4, 8);
  __riscv_vse32_v_f32m2(ptr, v, 8);
}

// FORCE_INLINE void vst1_p8_x2(poly8_t * ptr, poly8x8x2_t val);

// FORCE_INLINE void vst1q_p8_x2(poly8_t * ptr, poly8x16x2_t val);

// FORCE_INLINE void vst1_p16_x2(poly16_t * ptr, poly16x4x2_t val);

// FORCE_INLINE void vst1q_p16_x2(poly16_t * ptr, poly16x8x2_t val);

FORCE_INLINE void vst1_s64_x2(int64_t *ptr, int64x1x2_t val) {
  vint64m1_t val0 = __riscv_vget_v_i64m1x2_i64m1(val, 0);
  vint64m1_t val1 = __riscv_vget_v_i64m1x2_i64m1(val, 1);
  vint64m1_t v = __riscv_vslideup_vx_i64m1(val0, val1, 1, 2);
  __riscv_vse64_v_i64m1(ptr, v, 2);
}

FORCE_INLINE void vst1_u64_x2(uint64_t *ptr, uint64x1x2_t val) {
  vuint64m1_t val0 = __riscv_vget_v_u64m1x2_u64m1(val, 0);
  vuint64m1_t val1 = __riscv_vget_v_u64m1x2_u64m1(val, 1);
  vuint64m1_t v = __riscv_vslideup_vx_u64m1(val0, val1, 1, 2);
  __riscv_vse64_v_u64m1(ptr, v, 2);
}

// FORCE_INLINE void vst1_p64_x2(poly64_t * ptr, poly64x1x2_t val);

FORCE_INLINE void vst1q_s64_x2(int64_t *ptr, int64x2x2_t val) {
  vint64m2_t val0 = __riscv_vlmul_ext_v_i64m1_i64m2(__riscv_vget_v_i64m1x2_i64m1(val, 0));
  vint64m2_t val1 = __riscv_vlmul_ext_v_i64m1_i64m2(__riscv_vget_v_i64m1x2_i64m1(val, 1));
  vint64m2_t v = __riscv_vslideup_vx_i64m2(val0, val1, 2, 4);
  __riscv_vse64_v_i64m2(ptr, v, 4);
}

FORCE_INLINE void vst1q_u64_x2(uint64_t *ptr, uint64x2x2_t val) {
  vuint64m2_t val0 = __riscv_vlmul_ext_v_u64m1_u64m2(__riscv_vget_v_u64m1x2_u64m1(val, 0));
  vuint64m2_t val1 = __riscv_vlmul_ext_v_u64m1_u64m2(__riscv_vget_v_u64m1x2_u64m1(val, 1));
  vuint64m2_t v = __riscv_vslideup_vx_u64m2(val0, val1, 2, 4);
  __riscv_vse64_v_u64m2(ptr, v, 4);
}

// FORCE_INLINE void vst1q_p64_x2(poly64_t * ptr, poly64x2x2_t val);

FORCE_INLINE void vst1_f64_x2(float64_t *ptr, float64x1x2_t val) {
  vfloat64m1_t val0 = __riscv_vget_v_f64m1x2_f64m1(val, 0);
  vfloat64m1_t val1 = __riscv_vget_v_f64m1x2_f64m1(val, 1);
  vfloat64m1_t v = __riscv_vslideup_vx_f64m1(val0, val1, 1, 2);
  __riscv_vse64_v_f64m1(ptr, v, 2);
}

FORCE_INLINE void vst1q_f64_x2(float64_t *ptr, float64x2x2_t val) {
  vfloat64m2_t val0 = __riscv_vlmul_ext_v_f64m1_f64m2(__riscv_vget_v_f64m1x2_f64m1(val, 0));
  vfloat64m2_t val1 = __riscv_vlmul_ext_v_f64m1_f64m2(__riscv_vget_v_f64m1x2_f64m1(val, 1));
  vfloat64m2_t v = __riscv_vslideup_vx_f64m2(val0, val1, 2, 4);
  __riscv_vse64_v_f64m2(ptr, v, 4);
}

// FORCE_INLINE void vst1_s8_x3(int8_t * ptr, int8x8x3_t val);

// FORCE_INLINE void vst1q_s8_x3(int8_t * ptr, int8x16x3_t val);

// FORCE_INLINE void vst1_s16_x3(int16_t * ptr, int16x4x3_t val);

// FORCE_INLINE void vst1q_s16_x3(int16_t * ptr, int16x8x3_t val);

// FORCE_INLINE void vst1_s32_x3(int32_t * ptr, int32x2x3_t val);

// FORCE_INLINE void vst1q_s32_x3(int32_t * ptr, int32x4x3_t val);

// FORCE_INLINE void vst1_u8_x3(uint8_t * ptr, uint8x8x3_t val);

// FORCE_INLINE void vst1q_u8_x3(uint8_t * ptr, uint8x16x3_t val);

// FORCE_INLINE void vst1_u16_x3(uint16_t * ptr, uint16x4x3_t val);

// FORCE_INLINE void vst1q_u16_x3(uint16_t * ptr, uint16x8x3_t val);

// FORCE_INLINE void vst1_u32_x3(uint32_t * ptr, uint32x2x3_t val);

// FORCE_INLINE void vst1q_u32_x3(uint32_t * ptr, uint32x4x3_t val);

// FORCE_INLINE void vst1_f16_x3(float16_t * ptr, float16x4x3_t val);

// FORCE_INLINE void vst1q_f16_x3(float16_t * ptr, float16x8x3_t val);

// FORCE_INLINE void vst1_f32_x3(float32_t * ptr, float32x2x3_t val);

// FORCE_INLINE void vst1q_f32_x3(float32_t * ptr, float32x4x3_t val);

// FORCE_INLINE void vst1_p8_x3(poly8_t * ptr, poly8x8x3_t val);

// FORCE_INLINE void vst1q_p8_x3(poly8_t * ptr, poly8x16x3_t val);

// FORCE_INLINE void vst1_p16_x3(poly16_t * ptr, poly16x4x3_t val);

// FORCE_INLINE void vst1q_p16_x3(poly16_t * ptr, poly16x8x3_t val);

// FORCE_INLINE void vst1_s64_x3(int64_t * ptr, int64x1x3_t val);

// FORCE_INLINE void vst1_u64_x3(uint64_t * ptr, uint64x1x3_t val);

// FORCE_INLINE void vst1_p64_x3(poly64_t * ptr, poly64x1x3_t val);

// FORCE_INLINE void vst1q_s64_x3(int64_t * ptr, int64x2x3_t val);

// FORCE_INLINE void vst1q_u64_x3(uint64_t * ptr, uint64x2x3_t val);

// FORCE_INLINE void vst1q_p64_x3(poly64_t * ptr, poly64x2x3_t val);

// FORCE_INLINE void vst1_f64_x3(float64_t * ptr, float64x1x3_t val);

// FORCE_INLINE void vst1q_f64_x3(float64_t * ptr, float64x2x3_t val);

// FORCE_INLINE void vst1_s8_x4(int8_t * ptr, int8x8x4_t val);

// FORCE_INLINE void vst1q_s8_x4(int8_t * ptr, int8x16x4_t val);

// FORCE_INLINE void vst1_s16_x4(int16_t * ptr, int16x4x4_t val);

// FORCE_INLINE void vst1q_s16_x4(int16_t * ptr, int16x8x4_t val);

// FORCE_INLINE void vst1_s32_x4(int32_t * ptr, int32x2x4_t val);

// FORCE_INLINE void vst1q_s32_x4(int32_t * ptr, int32x4x4_t val);

// FORCE_INLINE void vst1_u8_x4(uint8_t * ptr, uint8x8x4_t val);

// FORCE_INLINE void vst1q_u8_x4(uint8_t * ptr, uint8x16x4_t val);

// FORCE_INLINE void vst1_u16_x4(uint16_t * ptr, uint16x4x4_t val);

// FORCE_INLINE void vst1q_u16_x4(uint16_t * ptr, uint16x8x4_t val);

// FORCE_INLINE void vst1_u32_x4(uint32_t * ptr, uint32x2x4_t val);

// FORCE_INLINE void vst1q_u32_x4(uint32_t * ptr, uint32x4x4_t val);

// FORCE_INLINE void vst1_f16_x4(float16_t * ptr, float16x4x4_t val);

// FORCE_INLINE void vst1q_f16_x4(float16_t * ptr, float16x8x4_t val);

// FORCE_INLINE void vst1_f32_x4(float32_t * ptr, float32x2x4_t val);

// FORCE_INLINE void vst1q_f32_x4(float32_t * ptr, float32x4x4_t val);

// FORCE_INLINE void vst1_p8_x4(poly8_t * ptr, poly8x8x4_t val);

// FORCE_INLINE void vst1q_p8_x4(poly8_t * ptr, poly8x16x4_t val);

// FORCE_INLINE void vst1_p16_x4(poly16_t * ptr, poly16x4x4_t val);

// FORCE_INLINE void vst1q_p16_x4(poly16_t * ptr, poly16x8x4_t val);

// FORCE_INLINE void vst1_s64_x4(int64_t * ptr, int64x1x4_t val);

// FORCE_INLINE void vst1_u64_x4(uint64_t * ptr, uint64x1x4_t val);

// FORCE_INLINE void vst1_p64_x4(poly64_t * ptr, poly64x1x4_t val);

// FORCE_INLINE void vst1q_s64_x4(int64_t * ptr, int64x2x4_t val);

// FORCE_INLINE void vst1q_u64_x4(uint64_t * ptr, uint64x2x4_t val);

// FORCE_INLINE void vst1q_p64_x4(poly64_t * ptr, poly64x2x4_t val);

// FORCE_INLINE void vst1_f64_x4(float64_t * ptr, float64x1x4_t val);

// FORCE_INLINE void vst1q_f64_x4(float64_t * ptr, float64x2x4_t val);

// FORCE_INLINE int8x8x2_t vld1_s8_x2(int8_t const * ptr);

FORCE_INLINE int8x16x2_t vld1q_s8_x2(int8_t const *ptr) {
  return __riscv_vcreate_v_i8m1x2(__riscv_vle8_v_i8m1(ptr, 16), __riscv_vle8_v_i8m1(ptr + 16, 16));
}

// FORCE_INLINE int16x4x2_t vld1_s16_x2(int16_t const * ptr);

// FORCE_INLINE int16x8x2_t vld1q_s16_x2(int16_t const * ptr);

// FORCE_INLINE int32x2x2_t vld1_s32_x2(int32_t const * ptr);

// FORCE_INLINE int32x4x2_t vld1q_s32_x2(int32_t const * ptr);

// FORCE_INLINE uint8x8x2_t vld1_u8_x2(uint8_t const * ptr);

FORCE_INLINE uint8x16x2_t vld1q_u8_x2(uint8_t const *ptr) {
  return __riscv_vcreate_v_u8m1x2(__riscv_vle8_v_u8m1(ptr, 16), __riscv_vle8_v_u8m1(ptr + 16, 16));
}

// FORCE_INLINE uint16x4x2_t vld1_u16_x2(uint16_t const * ptr);

FORCE_INLINE uint16x8x2_t vld1q_u16_x2(uint16_t const *ptr) {
  return __riscv_vcreate_v_u16m1x2(__riscv_vle16_v_u16m1(ptr, 8), __riscv_vle16_v_u16m1(ptr + 8, 8));
}

// FORCE_INLINE uint32x2x2_t vld1_u32_x2(uint32_t const * ptr);

// FORCE_INLINE uint32x4x2_t vld1q_u32_x2(uint32_t const * ptr);

// FORCE_INLINE float16x4x2_t vld1_f16_x2(float16_t const * ptr);

// FORCE_INLINE float16x8x2_t vld1q_f16_x2(float16_t const * ptr);

// FORCE_INLINE float32x2x2_t vld1_f32_x2(float32_t const * ptr);

// FORCE_INLINE float32x4x2_t vld1q_f32_x2(float32_t const * ptr);

// FORCE_INLINE poly8x8x2_t vld1_p8_x2(poly8_t const * ptr);

// FORCE_INLINE poly8x16x2_t vld1q_p8_x2(poly8_t const * ptr);

// FORCE_INLINE poly16x4x2_t vld1_p16_x2(poly16_t const * ptr);

// FORCE_INLINE poly16x8x2_t vld1q_p16_x2(poly16_t const * ptr);

// FORCE_INLINE int64x1x2_t vld1_s64_x2(int64_t const * ptr);

// FORCE_INLINE uint64x1x2_t vld1_u64_x2(uint64_t const * ptr);

// FORCE_INLINE poly64x1x2_t vld1_p64_x2(poly64_t const * ptr);

// FORCE_INLINE int64x2x2_t vld1q_s64_x2(int64_t const * ptr);

// FORCE_INLINE uint64x2x2_t vld1q_u64_x2(uint64_t const * ptr);

// FORCE_INLINE poly64x2x2_t vld1q_p64_x2(poly64_t const * ptr);

// FORCE_INLINE float64x1x2_t vld1_f64_x2(float64_t const * ptr);

// FORCE_INLINE float64x2x2_t vld1q_f64_x2(float64_t const * ptr);

// FORCE_INLINE int8x8x3_t vld1_s8_x3(int8_t const * ptr);

// FORCE_INLINE int8x16x3_t vld1q_s8_x3(int8_t const * ptr);

// FORCE_INLINE int16x4x3_t vld1_s16_x3(int16_t const * ptr);

// FORCE_INLINE int16x8x3_t vld1q_s16_x3(int16_t const * ptr);

// FORCE_INLINE int32x2x3_t vld1_s32_x3(int32_t const * ptr);

// FORCE_INLINE int32x4x3_t vld1q_s32_x3(int32_t const * ptr);

// FORCE_INLINE uint8x8x3_t vld1_u8_x3(uint8_t const * ptr);

FORCE_INLINE uint8x16x3_t vld1q_u8_x3(uint8_t const *ptr) {
  return __riscv_vcreate_v_u8m1x3(__riscv_vle8_v_u8m1(ptr, 16), __riscv_vle8_v_u8m1(ptr + 16, 16),
                                  __riscv_vle8_v_u8m1(ptr + 32, 16));
}

// FORCE_INLINE uint16x4x3_t vld1_u16_x3(uint16_t const * ptr);

FORCE_INLINE uint16x8x3_t vld1q_u16_x3(uint16_t const *ptr) {
  return __riscv_vcreate_v_u16m1x3(__riscv_vle16_v_u16m1(ptr, 8), __riscv_vle16_v_u16m1(ptr + 8, 8),
                                   __riscv_vle16_v_u16m1(ptr + 16, 8));
}

// FORCE_INLINE uint32x2x3_t vld1_u32_x3(uint32_t const * ptr);

// FORCE_INLINE uint32x4x3_t vld1q_u32_x3(uint32_t const * ptr);

// FORCE_INLINE float16x4x3_t vld1_f16_x3(float16_t const * ptr);

// FORCE_INLINE float16x8x3_t vld1q_f16_x3(float16_t const * ptr);

// FORCE_INLINE float32x2x3_t vld1_f32_x3(float32_t const * ptr);

// FORCE_INLINE float32x4x3_t vld1q_f32_x3(float32_t const * ptr);

// FORCE_INLINE poly8x8x3_t vld1_p8_x3(poly8_t const * ptr);

// FORCE_INLINE poly8x16x3_t vld1q_p8_x3(poly8_t const * ptr);

// FORCE_INLINE poly16x4x3_t vld1_p16_x3(poly16_t const * ptr);

// FORCE_INLINE poly16x8x3_t vld1q_p16_x3(poly16_t const * ptr);

// FORCE_INLINE int64x1x3_t vld1_s64_x3(int64_t const * ptr);

// FORCE_INLINE uint64x1x3_t vld1_u64_x3(uint64_t const * ptr);

// FORCE_INLINE poly64x1x3_t vld1_p64_x3(poly64_t const * ptr);

// FORCE_INLINE int64x2x3_t vld1q_s64_x3(int64_t const * ptr);

// FORCE_INLINE uint64x2x3_t vld1q_u64_x3(uint64_t const * ptr);

// FORCE_INLINE poly64x2x3_t vld1q_p64_x3(poly64_t const * ptr);

// FORCE_INLINE float64x1x3_t vld1_f64_x3(float64_t const * ptr);

// FORCE_INLINE float64x2x3_t vld1q_f64_x3(float64_t const * ptr);

// FORCE_INLINE int8x8x4_t vld1_s8_x4(int8_t const * ptr);

// FORCE_INLINE int8x16x4_t vld1q_s8_x4(int8_t const * ptr);

// FORCE_INLINE int16x4x4_t vld1_s16_x4(int16_t const * ptr);

// FORCE_INLINE int16x8x4_t vld1q_s16_x4(int16_t const * ptr);

// FORCE_INLINE int32x2x4_t vld1_s32_x4(int32_t const * ptr);

// FORCE_INLINE int32x4x4_t vld1q_s32_x4(int32_t const * ptr);

// FORCE_INLINE uint8x8x4_t vld1_u8_x4(uint8_t const * ptr);

FORCE_INLINE uint8x16x4_t vld1q_u8_x4(uint8_t const *ptr) {
  return __riscv_vcreate_v_u8m1x4(__riscv_vle8_v_u8m1(ptr, 16), __riscv_vle8_v_u8m1(ptr + 16, 16),
                                  __riscv_vle8_v_u8m1(ptr + 32, 16), __riscv_vle8_v_u8m1(ptr + 48, 16));
}

// FORCE_INLINE uint16x4x4_t vld1_u16_x4(uint16_t const * ptr);

FORCE_INLINE uint16x8x4_t vld1q_u16_x4(uint16_t const *ptr) {
  return __riscv_vcreate_v_u16m1x4(__riscv_vle16_v_u16m1(ptr, 8), __riscv_vle16_v_u16m1(ptr + 8, 8),
                                   __riscv_vle16_v_u16m1(ptr + 16, 8), __riscv_vle16_v_u16m1(ptr + 24, 8));
}

// FORCE_INLINE uint32x2x4_t vld1_u32_x4(uint32_t const * ptr);

// FORCE_INLINE uint32x4x4_t vld1q_u32_x4(uint32_t const * ptr);

// FORCE_INLINE float16x4x4_t vld1_f16_x4(float16_t const * ptr);

// FORCE_INLINE float16x8x4_t vld1q_f16_x4(float16_t const * ptr);

// FORCE_INLINE float32x2x4_t vld1_f32_x4(float32_t const * ptr);

// FORCE_INLINE float32x4x4_t vld1q_f32_x4(float32_t const * ptr);

// FORCE_INLINE poly8x8x4_t vld1_p8_x4(poly8_t const * ptr);

// FORCE_INLINE poly8x16x4_t vld1q_p8_x4(poly8_t const * ptr);

// FORCE_INLINE poly16x4x4_t vld1_p16_x4(poly16_t const * ptr);

// FORCE_INLINE poly16x8x4_t vld1q_p16_x4(poly16_t const * ptr);

// FORCE_INLINE int64x1x4_t vld1_s64_x4(int64_t const * ptr);

// FORCE_INLINE uint64x1x4_t vld1_u64_x4(uint64_t const * ptr);

// FORCE_INLINE poly64x1x4_t vld1_p64_x4(poly64_t const * ptr);

// FORCE_INLINE int64x2x4_t vld1q_s64_x4(int64_t const * ptr);

// FORCE_INLINE uint64x2x4_t vld1q_u64_x4(uint64_t const * ptr);

// FORCE_INLINE poly64x2x4_t vld1q_p64_x4(poly64_t const * ptr);

// FORCE_INLINE float64x1x4_t vld1_f64_x4(float64_t const * ptr);

// FORCE_INLINE float64x2x4_t vld1q_f64_x4(float64_t const * ptr);

FORCE_INLINE void vst4q_lane_u16(uint16_t *a, uint16x8x4_t b, const int c) {
  vuint16m1_t b0 = __riscv_vget_v_u16m1x4_u16m1(b, 0);
  vuint16m1_t b1 = __riscv_vget_v_u16m1x4_u16m1(b, 1);
  vuint16m1_t b2 = __riscv_vget_v_u16m1x4_u16m1(b, 2);
  vuint16m1_t b3 = __riscv_vget_v_u16m1x4_u16m1(b, 3);
  uint16_t *_b0 = (uint16_t *)&b0;
  uint16_t *_b1 = (uint16_t *)&b1;
  uint16_t *_b2 = (uint16_t *)&b2;
  uint16_t *_b3 = (uint16_t *)&b3;
  a[0] = _b0[c];
  a[1] = _b1[c];
  a[2] = _b2[c];
  a[3] = _b3[c];
}

FORCE_INLINE void vst4q_lane_u32(uint32_t *a, uint32x4x4_t b, const int c) {
  vuint32m1_t b0 = __riscv_vget_v_u32m1x4_u32m1(b, 0);
  vuint32m1_t b1 = __riscv_vget_v_u32m1x4_u32m1(b, 1);
  vuint32m1_t b2 = __riscv_vget_v_u32m1x4_u32m1(b, 2);
  vuint32m1_t b3 = __riscv_vget_v_u32m1x4_u32m1(b, 3);
  uint32_t *_b0 = (uint32_t *)&b0;
  uint32_t *_b1 = (uint32_t *)&b1;
  uint32_t *_b2 = (uint32_t *)&b2;
  uint32_t *_b3 = (uint32_t *)&b3;
  a[0] = _b0[c];
  a[1] = _b1[c];
  a[2] = _b2[c];
  a[3] = _b3[c];
}

// FORCE_INLINE void vst4_lane_f16(float16_t * ptr, float16x4x4_t val, const int lane);

// FORCE_INLINE void vst4q_lane_f16(float16_t * ptr, float16x8x4_t val, const int lane);

FORCE_INLINE int8x8_t vand_s8(int8x8_t a, int8x8_t b) { return __riscv_vand_vv_i8m1(a, b, 8); }

FORCE_INLINE int16x4_t vand_s16(int16x4_t a, int16x4_t b) { return __riscv_vand_vv_i16m1(a, b, 4); }

FORCE_INLINE int32x2_t vand_s32(int32x2_t a, int32x2_t b) { return __riscv_vand_vv_i32m1(a, b, 2); }

FORCE_INLINE uint8x8_t vand_u8(uint8x8_t a, uint8x8_t b) { return __riscv_vand_vv_u8m1(a, b, 8); }

FORCE_INLINE uint16x4_t vand_u16(uint16x4_t a, uint16x4_t b) { return __riscv_vand_vv_u16m1(a, b, 4); }

FORCE_INLINE uint32x2_t vand_u32(uint32x2_t a, uint32x2_t b) { return __riscv_vand_vv_u32m1(a, b, 2); }

FORCE_INLINE int64x1_t vand_s64(int64x1_t a, int64x1_t b) { return __riscv_vand_vv_i64m1(a, b, 1); }

FORCE_INLINE uint64x1_t vand_u64(uint64x1_t a, uint64x1_t b) { return __riscv_vand_vv_u64m1(a, b, 1); }

FORCE_INLINE int8x16_t vandq_s8(int8x16_t a, int8x16_t b) { return __riscv_vand_vv_i8m1(a, b, 16); }

FORCE_INLINE int16x8_t vandq_s16(int16x8_t a, int16x8_t b) { return __riscv_vand_vv_i16m1(a, b, 8); }

FORCE_INLINE int32x4_t vandq_s32(int32x4_t a, int32x4_t b) { return __riscv_vand_vv_i32m1(a, b, 4); }

FORCE_INLINE int64x2_t vandq_s64(int64x2_t a, int64x2_t b) { return __riscv_vand_vv_i64m1(a, b, 2); }

FORCE_INLINE uint8x16_t vandq_u8(uint8x16_t a, uint8x16_t b) { return __riscv_vand_vv_u8m1(a, b, 16); }

FORCE_INLINE uint16x8_t vandq_u16(uint16x8_t a, uint16x8_t b) { return __riscv_vand_vv_u16m1(a, b, 8); }

FORCE_INLINE uint32x4_t vandq_u32(uint32x4_t a, uint32x4_t b) { return __riscv_vand_vv_u32m1(a, b, 4); }

FORCE_INLINE uint64x2_t vandq_u64(uint64x2_t a, uint64x2_t b) { return __riscv_vand_vv_u64m1(a, b, 2); }

FORCE_INLINE int8x8_t vorr_s8(int8x8_t a, int8x8_t b) { return __riscv_vor_vv_i8m1(a, b, 8); }

FORCE_INLINE int16x4_t vorr_s16(int16x4_t a, int16x4_t b) { return __riscv_vor_vv_i16m1(a, b, 4); }

FORCE_INLINE int32x2_t vorr_s32(int32x2_t a, int32x2_t b) { return __riscv_vor_vv_i32m1(a, b, 2); }

FORCE_INLINE uint8x8_t vorr_u8(uint8x8_t a, uint8x8_t b) { return __riscv_vor_vv_u8m1(a, b, 8); }

FORCE_INLINE uint16x4_t vorr_u16(uint16x4_t a, uint16x4_t b) { return __riscv_vor_vv_u16m1(a, b, 4); }

FORCE_INLINE uint32x2_t vorr_u32(uint32x2_t a, uint32x2_t b) { return __riscv_vor_vv_u32m1(a, b, 2); }

FORCE_INLINE int64x1_t vorr_s64(int64x1_t a, int64x1_t b) { return __riscv_vor_vv_i64m1(a, b, 1); }

FORCE_INLINE uint64x1_t vorr_u64(uint64x1_t a, uint64x1_t b) { return __riscv_vor_vv_u64m1(a, b, 1); }

FORCE_INLINE int8x16_t vorrq_s8(int8x16_t a, int8x16_t b) { return __riscv_vor_vv_i8m1(a, b, 16); }

FORCE_INLINE int16x8_t vorrq_s16(int16x8_t a, int16x8_t b) { return __riscv_vor_vv_i16m1(a, b, 8); }

FORCE_INLINE int32x4_t vorrq_s32(int32x4_t a, int32x4_t b) { return __riscv_vor_vv_i32m1(a, b, 4); }

FORCE_INLINE int64x2_t vorrq_s64(int64x2_t a, int64x2_t b) { return __riscv_vor_vv_i64m1(a, b, 2); }

FORCE_INLINE uint8x16_t vorrq_u8(uint8x16_t a, uint8x16_t b) { return __riscv_vor_vv_u8m1(a, b, 16); }

FORCE_INLINE uint16x8_t vorrq_u16(uint16x8_t a, uint16x8_t b) { return __riscv_vor_vv_u16m1(a, b, 8); }

FORCE_INLINE uint32x4_t vorrq_u32(uint32x4_t a, uint32x4_t b) { return __riscv_vor_vv_u32m1(a, b, 4); }

FORCE_INLINE uint64x2_t vorrq_u64(uint64x2_t a, uint64x2_t b) { return __riscv_vor_vv_u64m1(a, b, 2); }

FORCE_INLINE int8x8_t veor_s8(int8x8_t a, int8x8_t b) { return __riscv_vxor_vv_i8m1(a, b, 8); }

FORCE_INLINE int16x4_t veor_s16(int16x4_t a, int16x4_t b) { return __riscv_vxor_vv_i16m1(a, b, 4); }

FORCE_INLINE int32x2_t veor_s32(int32x2_t a, int32x2_t b) { return __riscv_vxor_vv_i32m1(a, b, 2); }

FORCE_INLINE uint8x8_t veor_u8(uint8x8_t a, uint8x8_t b) { return __riscv_vxor_vv_u8m1(a, b, 8); }

FORCE_INLINE uint16x4_t veor_u16(uint16x4_t a, uint16x4_t b) { return __riscv_vxor_vv_u16m1(a, b, 4); }

FORCE_INLINE uint32x2_t veor_u32(uint32x2_t a, uint32x2_t b) { return __riscv_vxor_vv_u32m1(a, b, 2); }

FORCE_INLINE int64x1_t veor_s64(int64x1_t a, int64x1_t b) { return __riscv_vxor_vv_i64m1(a, b, 1); }

FORCE_INLINE uint64x1_t veor_u64(uint64x1_t a, uint64x1_t b) { return __riscv_vxor_vv_u64m1(a, b, 1); }

FORCE_INLINE int8x16_t veorq_s8(int8x16_t a, int8x16_t b) { return __riscv_vxor_vv_i8m1(a, b, 16); }

FORCE_INLINE int16x8_t veorq_s16(int16x8_t a, int16x8_t b) { return __riscv_vxor_vv_i16m1(a, b, 8); }

FORCE_INLINE int32x4_t veorq_s32(int32x4_t a, int32x4_t b) { return __riscv_vxor_vv_i32m1(a, b, 4); }

FORCE_INLINE int64x2_t veorq_s64(int64x2_t a, int64x2_t b) { return __riscv_vxor_vv_i64m1(a, b, 2); }

FORCE_INLINE uint8x16_t veorq_u8(uint8x16_t a, uint8x16_t b) { return __riscv_vxor_vv_u8m1(a, b, 16); }

FORCE_INLINE uint16x8_t veorq_u16(uint16x8_t a, uint16x8_t b) { return __riscv_vxor_vv_u16m1(a, b, 8); }

FORCE_INLINE uint32x4_t veorq_u32(uint32x4_t a, uint32x4_t b) { return __riscv_vxor_vv_u32m1(a, b, 4); }

FORCE_INLINE uint64x2_t veorq_u64(uint64x2_t a, uint64x2_t b) { return __riscv_vxor_vv_u64m1(a, b, 2); }

FORCE_INLINE int8x8_t vbic_s8(int8x8_t a, int8x8_t b) { return __riscv_vand_vv_i8m1(a, __riscv_vnot_v_i8m1(b, 8), 8); }

FORCE_INLINE int16x4_t vbic_s16(int16x4_t a, int16x4_t b) {
  return __riscv_vand_vv_i16m1(a, __riscv_vnot_v_i16m1(b, 4), 4);
}

FORCE_INLINE int32x2_t vbic_s32(int32x2_t a, int32x2_t b) {
  return __riscv_vand_vv_i32m1(a, __riscv_vnot_v_i32m1(b, 2), 2);
}

FORCE_INLINE uint8x8_t vbic_u8(uint8x8_t a, uint8x8_t b) {
  return __riscv_vand_vv_u8m1(a, __riscv_vnot_v_u8m1(b, 8), 8);
}

FORCE_INLINE uint16x4_t vbic_u16(uint16x4_t a, uint16x4_t b) {
  return __riscv_vand_vv_u16m1(a, __riscv_vnot_v_u16m1(b, 4), 4);
}

FORCE_INLINE uint32x2_t vbic_u32(uint32x2_t a, uint32x2_t b) {
  return __riscv_vand_vv_u32m1(a, __riscv_vnot_v_u32m1(b, 2), 2);
}

FORCE_INLINE int64x1_t vbic_s64(int64x1_t a, int64x1_t b) {
  return __riscv_vand_vv_i64m1(a, __riscv_vnot_v_i64m1(b, 1), 1);
}

FORCE_INLINE uint64x1_t vbic_u64(uint64x1_t a, uint64x1_t b) {
  return __riscv_vand_vv_u64m1(a, __riscv_vnot_v_u64m1(b, 1), 1);
}

FORCE_INLINE int8x16_t vbicq_s8(int8x16_t a, int8x16_t b) {
  return __riscv_vand_vv_i8m1(a, __riscv_vnot_v_i8m1(b, 16), 16);
}

FORCE_INLINE int16x8_t vbicq_s16(int16x8_t a, int16x8_t b) {
  return __riscv_vand_vv_i16m1(a, __riscv_vnot_v_i16m1(b, 8), 8);
}

FORCE_INLINE int32x4_t vbicq_s32(int32x4_t a, int32x4_t b) {
  return __riscv_vand_vv_i32m1(a, __riscv_vnot_v_i32m1(b, 4), 4);
}

FORCE_INLINE int64x2_t vbicq_s64(int64x2_t a, int64x2_t b) {
  return __riscv_vand_vv_i64m1(a, __riscv_vnot_v_i64m1(b, 2), 2);
}

FORCE_INLINE uint8x16_t vbicq_u8(uint8x16_t a, uint8x16_t b) {
  return __riscv_vand_vv_u8m1(a, __riscv_vnot_v_u8m1(b, 16), 16);
}

FORCE_INLINE uint16x8_t vbicq_u16(uint16x8_t a, uint16x8_t b) {
  return __riscv_vand_vv_u16m1(a, __riscv_vnot_v_u16m1(b, 8), 8);
}

FORCE_INLINE uint32x4_t vbicq_u32(uint32x4_t a, uint32x4_t b) {
  return __riscv_vand_vv_u32m1(a, __riscv_vnot_v_u32m1(b, 4), 4);
}

FORCE_INLINE uint64x2_t vbicq_u64(uint64x2_t a, uint64x2_t b) {
  return __riscv_vand_vv_u64m1(a, __riscv_vnot_v_u64m1(b, 2), 2);
}

FORCE_INLINE int8x8_t vorn_s8(int8x8_t a, int8x8_t b) { return __riscv_vor_vv_i8m1(a, __riscv_vnot_v_i8m1(b, 8), 8); }

FORCE_INLINE int16x4_t vorn_s16(int16x4_t a, int16x4_t b) {
  return __riscv_vor_vv_i16m1(a, __riscv_vnot_v_i16m1(b, 4), 4);
}

FORCE_INLINE int32x2_t vorn_s32(int32x2_t a, int32x2_t b) {
  return __riscv_vor_vv_i32m1(a, __riscv_vnot_v_i32m1(b, 2), 2);
}

FORCE_INLINE uint8x8_t vorn_u8(uint8x8_t a, uint8x8_t b) {
  return __riscv_vor_vv_u8m1(a, __riscv_vnot_v_u8m1(b, 8), 8);
}

FORCE_INLINE uint16x4_t vorn_u16(uint16x4_t a, uint16x4_t b) {
  return __riscv_vor_vv_u16m1(a, __riscv_vnot_v_u16m1(b, 4), 4);
}

FORCE_INLINE uint32x2_t vorn_u32(uint32x2_t a, uint32x2_t b) {
  return __riscv_vor_vv_u32m1(a, __riscv_vnot_v_u32m1(b, 2), 2);
}

FORCE_INLINE int64x1_t vorn_s64(int64x1_t a, int64x1_t b) {
  return __riscv_vor_vv_i64m1(a, __riscv_vnot_v_i64m1(b, 1), 1);
}

FORCE_INLINE uint64x1_t vorn_u64(uint64x1_t a, uint64x1_t b) {
  return __riscv_vor_vv_u64m1(a, __riscv_vnot_v_u64m1(b, 1), 1);
}

FORCE_INLINE int8x16_t vornq_s8(int8x16_t a, int8x16_t b) {
  return __riscv_vor_vv_i8m1(a, __riscv_vnot_v_i8m1(b, 16), 16);
}

FORCE_INLINE int16x8_t vornq_s16(int16x8_t a, int16x8_t b) {
  return __riscv_vor_vv_i16m1(a, __riscv_vnot_v_i16m1(b, 8), 8);
}

FORCE_INLINE int32x4_t vornq_s32(int32x4_t a, int32x4_t b) {
  return __riscv_vor_vv_i32m1(a, __riscv_vnot_v_i32m1(b, 4), 4);
}

FORCE_INLINE int64x2_t vornq_s64(int64x2_t a, int64x2_t b) {
  return __riscv_vor_vv_i64m1(a, __riscv_vnot_v_i64m1(b, 2), 2);
}

FORCE_INLINE uint8x16_t vornq_u8(uint8x16_t a, uint8x16_t b) {
  return __riscv_vor_vv_u8m1(a, __riscv_vnot_v_u8m1(b, 16), 16);
}

FORCE_INLINE uint16x8_t vornq_u16(uint16x8_t a, uint16x8_t b) {
  return __riscv_vor_vv_u16m1(a, __riscv_vnot_v_u16m1(b, 8), 8);
}

FORCE_INLINE uint32x4_t vornq_u32(uint32x4_t a, uint32x4_t b) {
  return __riscv_vor_vv_u32m1(a, __riscv_vnot_v_u32m1(b, 4), 4);
}

FORCE_INLINE uint64x2_t vornq_u64(uint64x2_t a, uint64x2_t b) {
  return __riscv_vor_vv_u64m1(a, __riscv_vnot_v_u64m1(b, 2), 2);
}

FORCE_INLINE float32x2_t vreinterpret_f32_s64(int64x1_t a) {
  return __riscv_vreinterpret_v_i32m1_f32m1(__riscv_vreinterpret_v_i64m1_i32m1(a));
}

FORCE_INLINE float32x2_t vreinterpret_f32_u64(uint64x1_t a) {
  return __riscv_vreinterpret_v_u32m1_f32m1(__riscv_vreinterpret_v_u64m1_u32m1(a));
}

FORCE_INLINE float32x2_t vreinterpret_f32_s8(int8x8_t a) {
  return __riscv_vreinterpret_v_i32m1_f32m1(__riscv_vreinterpret_v_i8m1_i32m1(a));
}

FORCE_INLINE float32x2_t vreinterpret_f32_s16(int16x4_t a) {
  return __riscv_vreinterpret_v_i32m1_f32m1(__riscv_vreinterpret_v_i16m1_i32m1(a));
}

FORCE_INLINE float32x2_t vreinterpret_f32_s32(int32x2_t a) { return __riscv_vreinterpret_v_i32m1_f32m1(a); }

FORCE_INLINE float32x2_t vreinterpret_f32_u8(uint8x8_t a) {
  return __riscv_vreinterpret_v_u32m1_f32m1(__riscv_vreinterpret_v_u8m1_u32m1(a));
}

FORCE_INLINE float32x2_t vreinterpret_f32_u16(uint16x4_t a) {
  return __riscv_vreinterpret_v_u32m1_f32m1(__riscv_vreinterpret_v_u16m1_u32m1(a));
}

FORCE_INLINE float32x2_t vreinterpret_f32_u32(uint32x2_t a) { return __riscv_vreinterpret_v_u32m1_f32m1(a); }

FORCE_INLINE int64x1_t vreinterpret_s64_f32(float32x2_t a) {
  return __riscv_vreinterpret_v_i32m1_i64m1(__riscv_vreinterpret_v_f32m1_i32m1(a));
}

FORCE_INLINE float64x1_t vreinterpret_f64_f32(float32x2_t a) {
  return __riscv_vreinterpret_v_u64m1_f64m1(__riscv_vreinterpret_v_u32m1_u64m1(__riscv_vreinterpret_v_f32m1_u32m1(a)));
}

// FORCE_INLINE poly64x1_t vreinterpret_p64_f32(float32x2_t a);

// FORCE_INLINE poly64x1_t vreinterpret_p64_f64(float64x1_t a);

// FORCE_INLINE float16x4_t vreinterpret_f16_f32(float32x2_t a);

FORCE_INLINE int64x1_t vreinterpret_s64_u64(uint64x1_t a) { return __riscv_vreinterpret_v_u64m1_i64m1(a); }

FORCE_INLINE float64x1_t vreinterpret_f64_u64(uint64x1_t a) { return __riscv_vreinterpret_v_u64m1_f64m1(a); }

// FORCE_INLINE poly64x1_t vreinterpret_p64_u64(uint64x1_t a);

// FORCE_INLINE float16x4_t vreinterpret_f16_u64(uint64x1_t a);

FORCE_INLINE int64x1_t vreinterpret_s64_s8(int8x8_t a) { return __riscv_vreinterpret_v_i8m1_i64m1(a); }

FORCE_INLINE float64x1_t vreinterpret_f64_s8(int8x8_t a) {
  return __riscv_vreinterpret_v_i64m1_f64m1(__riscv_vreinterpret_v_i8m1_i64m1(a));
}

// FORCE_INLINE poly64x1_t vreinterpret_p64_s8(int8x8_t a);

// FORCE_INLINE float16x4_t vreinterpret_f16_s8(int8x8_t a);

FORCE_INLINE int64x1_t vreinterpret_s64_s16(int16x4_t a) { return __riscv_vreinterpret_v_i16m1_i64m1(a); }

FORCE_INLINE float64x1_t vreinterpret_f64_s16(int16x4_t a) {
  return __riscv_vreinterpret_v_i64m1_f64m1(__riscv_vreinterpret_v_i16m1_i64m1(a));
}

// FORCE_INLINE poly64x1_t vreinterpret_p64_s16(int16x4_t a);

// FORCE_INLINE float16x4_t vreinterpret_f16_s16(int16x4_t a);

FORCE_INLINE int64x1_t vreinterpret_s64_s32(int32x2_t a) { return __riscv_vreinterpret_v_i32m1_i64m1(a); }

FORCE_INLINE float64x1_t vreinterpret_f64_s32(int32x2_t a) {
  return __riscv_vreinterpret_v_i64m1_f64m1(__riscv_vreinterpret_v_i32m1_i64m1(a));
}

// FORCE_INLINE poly64x1_t vreinterpret_p64_s32(int32x2_t a);

// FORCE_INLINE float16x4_t vreinterpret_f16_s32(int32x2_t a);

FORCE_INLINE int64x1_t vreinterpret_s64_u8(uint8x8_t a) {
  return __riscv_vreinterpret_v_i8m1_i64m1(__riscv_vreinterpret_v_u8m1_i8m1(a));
}

FORCE_INLINE float64x1_t vreinterpret_f64_u8(uint8x8_t a) {
  return __riscv_vreinterpret_v_u64m1_f64m1(__riscv_vreinterpret_v_u8m1_u64m1(a));
}

// FORCE_INLINE poly64x1_t vreinterpret_p64_u8(uint8x8_t a);

// FORCE_INLINE float16x4_t vreinterpret_f16_u8(uint8x8_t a);

FORCE_INLINE int64x1_t vreinterpret_s64_u16(uint16x4_t a) {
  return __riscv_vreinterpret_v_i16m1_i64m1(__riscv_vreinterpret_v_u16m1_i16m1(a));
}

FORCE_INLINE float64x1_t vreinterpret_f64_u16(uint16x4_t a) {
  return __riscv_vreinterpret_v_u64m1_f64m1(__riscv_vreinterpret_v_u16m1_u64m1(a));
}

// FORCE_INLINE poly64x1_t vreinterpret_p64_u16(uint16x4_t a);

// FORCE_INLINE float16x4_t vreinterpret_f16_u16(uint16x4_t a);

FORCE_INLINE int64x1_t vreinterpret_s64_u32(uint32x2_t a) {
  return __riscv_vreinterpret_v_i32m1_i64m1(__riscv_vreinterpret_v_u32m1_i32m1(a));
}

FORCE_INLINE float64x1_t vreinterpret_f64_u32(uint32x2_t a) {
  return __riscv_vreinterpret_v_u64m1_f64m1(__riscv_vreinterpret_v_u32m1_u64m1(a));
}

// FORCE_INLINE poly64x1_t vreinterpret_p64_u32(uint32x2_t a);

// FORCE_INLINE float16x4_t vreinterpret_f16_u32(uint32x2_t a);

// FORCE_INLINE int8x8_t vreinterpret_s8_p8(poly8x8_t a);

// FORCE_INLINE int16x4_t vreinterpret_s16_p8(poly8x8_t a);

// FORCE_INLINE int32x2_t vreinterpret_s32_p8(poly8x8_t a);

// FORCE_INLINE float32x2_t vreinterpret_f32_p8(poly8x8_t a);

// FORCE_INLINE uint8x8_t vreinterpret_u8_p8(poly8x8_t a);

// FORCE_INLINE uint16x4_t vreinterpret_u16_p8(poly8x8_t a);

// FORCE_INLINE uint32x2_t vreinterpret_u32_p8(poly8x8_t a);

// FORCE_INLINE poly16x4_t vreinterpret_p16_p8(poly8x8_t a);

// FORCE_INLINE uint64x1_t vreinterpret_u64_p8(poly8x8_t a);

// FORCE_INLINE int64x1_t vreinterpret_s64_p8(poly8x8_t a);

// FORCE_INLINE float64x1_t vreinterpret_f64_p8(poly8x8_t a);

// FORCE_INLINE poly64x1_t vreinterpret_p64_p8(poly8x8_t a);

// FORCE_INLINE float16x4_t vreinterpret_f16_p8(poly8x8_t a);

// FORCE_INLINE int8x8_t vreinterpret_s8_p16(poly16x4_t a);

// FORCE_INLINE int16x4_t vreinterpret_s16_p16(poly16x4_t a);

// FORCE_INLINE int32x2_t vreinterpret_s32_p16(poly16x4_t a);

// FORCE_INLINE float32x2_t vreinterpret_f32_p16(poly16x4_t a);

// FORCE_INLINE uint8x8_t vreinterpret_u8_p16(poly16x4_t a);

// FORCE_INLINE uint16x4_t vreinterpret_u16_p16(poly16x4_t a);

// FORCE_INLINE uint32x2_t vreinterpret_u32_p16(poly16x4_t a);

// FORCE_INLINE poly8x8_t vreinterpret_p8_p16(poly16x4_t a);

// FORCE_INLINE uint64x1_t vreinterpret_u64_p16(poly16x4_t a);

// FORCE_INLINE int64x1_t vreinterpret_s64_p16(poly16x4_t a);

// FORCE_INLINE float64x1_t vreinterpret_f64_p16(poly16x4_t a);

// FORCE_INLINE poly64x1_t vreinterpret_p64_p16(poly16x4_t a);

// FORCE_INLINE float16x4_t vreinterpret_f16_p16(poly16x4_t a);

FORCE_INLINE uint64x1_t vreinterpret_u64_f32(float32x2_t a) {
  return __riscv_vreinterpret_v_u32m1_u64m1(__riscv_vreinterpret_v_f32m1_u32m1(a));
}

FORCE_INLINE uint64x1_t vreinterpret_u64_s64(int64x1_t a) { return __riscv_vreinterpret_v_i64m1_u64m1(a); }

FORCE_INLINE float64x1_t vreinterpret_f64_s64(int64x1_t a) { return __riscv_vreinterpret_v_i64m1_f64m1(a); }

// FORCE_INLINE uint64x1_t vreinterpret_u64_p64(poly64x1_t a);

// FORCE_INLINE float16x4_t vreinterpret_f16_s64(int64x1_t a);

// FORCE_INLINE int8x8_t vreinterpret_s8_f16(float16x4_t a);

// FORCE_INLINE int16x4_t vreinterpret_s16_f16(float16x4_t a);

// FORCE_INLINE int32x2_t vreinterpret_s32_f16(float16x4_t a);

// FORCE_INLINE float32x2_t vreinterpret_f32_f16(float16x4_t a);

// FORCE_INLINE uint8x8_t vreinterpret_u8_f16(float16x4_t a);

// FORCE_INLINE uint16x4_t vreinterpret_u16_f16(float16x4_t a);

// FORCE_INLINE uint32x2_t vreinterpret_u32_f16(float16x4_t a);

// FORCE_INLINE poly8x8_t vreinterpret_p8_f16(float16x4_t a);

// FORCE_INLINE poly16x4_t vreinterpret_p16_f16(float16x4_t a);

// FORCE_INLINE uint64x1_t vreinterpret_u64_f16(float16x4_t a);

// FORCE_INLINE int64x1_t vreinterpret_s64_f16(float16x4_t a);

// FORCE_INLINE float64x1_t vreinterpret_f64_f16(float16x4_t a);

// FORCE_INLINE poly64x1_t vreinterpret_p64_f16(float16x4_t a);

FORCE_INLINE uint64x1_t vreinterpret_u64_s8(int8x8_t a) {
  return __riscv_vreinterpret_v_u8m1_u64m1(__riscv_vreinterpret_v_i8m1_u8m1(a));
}

FORCE_INLINE uint64x1_t vreinterpret_u64_s16(int16x4_t a) {
  return __riscv_vreinterpret_v_u16m1_u64m1(__riscv_vreinterpret_v_i16m1_u16m1(a));
}

FORCE_INLINE uint64x1_t vreinterpret_u64_s32(int32x2_t a) {
  return __riscv_vreinterpret_v_u32m1_u64m1(__riscv_vreinterpret_v_i32m1_u32m1(a));
}

FORCE_INLINE uint64x1_t vreinterpret_u64_u8(uint8x8_t a) { return __riscv_vreinterpret_v_u8m1_u64m1(a); }

FORCE_INLINE uint64x1_t vreinterpret_u64_u16(uint16x4_t a) { return __riscv_vreinterpret_v_u16m1_u64m1(a); }

FORCE_INLINE uint64x1_t vreinterpret_u64_u32(uint32x2_t a) { return __riscv_vreinterpret_v_u32m1_u64m1(a); }

FORCE_INLINE int8x8_t vreinterpret_s8_f32(float32x2_t a) {
  return __riscv_vreinterpret_v_i32m1_i8m1(__riscv_vreinterpret_v_f32m1_i32m1(a));
}

FORCE_INLINE int8x8_t vreinterpret_s8_s64(int64x1_t a) { return __riscv_vreinterpret_v_i64m1_i8m1(a); }

FORCE_INLINE int8x8_t vreinterpret_s8_u64(uint64x1_t a) {
  return __riscv_vreinterpret_v_i64m1_i8m1(__riscv_vreinterpret_v_u64m1_i64m1(a));
}

FORCE_INLINE int8x8_t vreinterpret_s8_s16(int16x4_t a) { return __riscv_vreinterpret_v_i16m1_i8m1(a); }

FORCE_INLINE int8x8_t vreinterpret_s8_s32(int32x2_t a) { return __riscv_vreinterpret_v_i32m1_i8m1(a); }

FORCE_INLINE int8x8_t vreinterpret_s8_u8(uint8x8_t a) { return __riscv_vreinterpret_v_u8m1_i8m1(a); }

FORCE_INLINE int8x8_t vreinterpret_s8_u16(uint16x4_t a) {
  return __riscv_vreinterpret_v_i16m1_i8m1(__riscv_vreinterpret_v_u16m1_i16m1(a));
}

FORCE_INLINE int8x8_t vreinterpret_s8_u32(uint32x2_t a) {
  return __riscv_vreinterpret_v_i32m1_i8m1(__riscv_vreinterpret_v_u32m1_i32m1(a));
}

FORCE_INLINE int16x4_t vreinterpret_s16_f32(float32x2_t a) {
  return __riscv_vreinterpret_v_i32m1_i16m1(__riscv_vreinterpret_v_f32m1_i32m1(a));
}

FORCE_INLINE int16x4_t vreinterpret_s16_s64(int64x1_t a) { return __riscv_vreinterpret_v_i64m1_i16m1(a); }

FORCE_INLINE int16x4_t vreinterpret_s16_u64(uint64x1_t a) {
  return __riscv_vreinterpret_v_i64m1_i16m1(__riscv_vreinterpret_v_u64m1_i64m1(a));
}

FORCE_INLINE int16x4_t vreinterpret_s16_s8(int8x8_t a) { return __riscv_vreinterpret_v_i8m1_i16m1(a); }

FORCE_INLINE int16x4_t vreinterpret_s16_s32(int32x2_t a) { return __riscv_vreinterpret_v_i32m1_i16m1(a); }

FORCE_INLINE int16x4_t vreinterpret_s16_u8(uint8x8_t a) {
  return __riscv_vreinterpret_v_i8m1_i16m1(__riscv_vreinterpret_v_u8m1_i8m1(a));
}

FORCE_INLINE int16x4_t vreinterpret_s16_u16(uint16x4_t a) { return __riscv_vreinterpret_v_u16m1_i16m1(a); }

FORCE_INLINE int16x4_t vreinterpret_s16_u32(uint32x2_t a) {
  return __riscv_vreinterpret_v_i32m1_i16m1(__riscv_vreinterpret_v_u32m1_i32m1(a));
}

FORCE_INLINE int32x2_t vreinterpret_s32_f32(float32x2_t a) { return __riscv_vreinterpret_v_f32m1_i32m1(a); }

FORCE_INLINE int32x2_t vreinterpret_s32_s64(int64x1_t a) { return __riscv_vreinterpret_v_i64m1_i32m1(a); }

FORCE_INLINE int32x2_t vreinterpret_s32_u64(uint64x1_t a) {
  return __riscv_vreinterpret_v_i64m1_i32m1(__riscv_vreinterpret_v_u64m1_i64m1(a));
}

FORCE_INLINE int32x2_t vreinterpret_s32_s8(int8x8_t a) { return __riscv_vreinterpret_v_i8m1_i32m1(a); }

FORCE_INLINE int32x2_t vreinterpret_s32_s16(int16x4_t a) { return __riscv_vreinterpret_v_i16m1_i32m1(a); }

FORCE_INLINE int32x2_t vreinterpret_s32_u8(uint8x8_t a) {
  return __riscv_vreinterpret_v_i8m1_i32m1(__riscv_vreinterpret_v_u8m1_i8m1(a));
}

FORCE_INLINE int32x2_t vreinterpret_s32_u16(uint16x4_t a) {
  return __riscv_vreinterpret_v_i16m1_i32m1(__riscv_vreinterpret_v_u16m1_i16m1(a));
}

FORCE_INLINE int32x2_t vreinterpret_s32_u32(uint32x2_t a) { return __riscv_vreinterpret_v_u32m1_i32m1(a); }

FORCE_INLINE uint8x8_t vreinterpret_u8_f32(float32x2_t a) {
  return __riscv_vreinterpret_v_u32m1_u8m1(__riscv_vreinterpret_v_f32m1_u32m1(a));
}

FORCE_INLINE uint8x8_t vreinterpret_u8_s64(int64x1_t a) {
  return __riscv_vreinterpret_v_u64m1_u8m1(__riscv_vreinterpret_v_i64m1_u64m1(a));
}

FORCE_INLINE uint8x8_t vreinterpret_u8_u64(uint64x1_t a) { return __riscv_vreinterpret_v_u64m1_u8m1(a); }

FORCE_INLINE uint8x8_t vreinterpret_u8_s8(int8x8_t a) { return __riscv_vreinterpret_v_i8m1_u8m1(a); }

FORCE_INLINE uint8x8_t vreinterpret_u8_s16(int16x4_t a) {
  return __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vreinterpret_v_i16m1_u16m1(a));
}

FORCE_INLINE uint8x8_t vreinterpret_u8_s32(int32x2_t a) {
  return __riscv_vreinterpret_v_u32m1_u8m1(__riscv_vreinterpret_v_i32m1_u32m1(a));
}

FORCE_INLINE uint8x8_t vreinterpret_u8_u16(uint16x4_t a) { return __riscv_vreinterpret_v_u16m1_u8m1(a); }

FORCE_INLINE uint8x8_t vreinterpret_u8_u32(uint32x2_t a) { return __riscv_vreinterpret_v_u32m1_u8m1(a); }

FORCE_INLINE uint16x4_t vreinterpret_u16_f32(float32x2_t a) {
  return __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vreinterpret_v_f32m1_u32m1(a));
}

FORCE_INLINE uint16x4_t vreinterpret_u16_s64(int64x1_t a) {
  return __riscv_vreinterpret_v_u64m1_u16m1(__riscv_vreinterpret_v_i64m1_u64m1(a));
}

FORCE_INLINE uint16x4_t vreinterpret_u16_u64(uint64x1_t a) { return __riscv_vreinterpret_v_u64m1_u16m1(a); }

FORCE_INLINE uint16x4_t vreinterpret_u16_s8(int8x8_t a) {
  return __riscv_vreinterpret_v_u8m1_u16m1(__riscv_vreinterpret_v_i8m1_u8m1(a));
}

FORCE_INLINE uint16x4_t vreinterpret_u16_s16(int16x4_t a) { return __riscv_vreinterpret_v_i16m1_u16m1(a); }

FORCE_INLINE uint16x4_t vreinterpret_u16_s32(int32x2_t a) {
  return __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vreinterpret_v_i32m1_u32m1(a));
}

FORCE_INLINE uint16x4_t vreinterpret_u16_u8(uint8x8_t a) { return __riscv_vreinterpret_v_u8m1_u16m1(a); }

FORCE_INLINE uint16x4_t vreinterpret_u16_u32(uint32x2_t a) { return __riscv_vreinterpret_v_u32m1_u16m1(a); }

// FORCE_INLINE poly8x8_t vreinterpret_p8_u32(uint32x2_t a);

// FORCE_INLINE poly16x4_t vreinterpret_p16_u32(uint32x2_t a);

FORCE_INLINE uint32x2_t vreinterpret_u32_f32(float32x2_t a) { return __riscv_vreinterpret_v_f32m1_u32m1(a); }

// FORCE_INLINE poly8x8_t vreinterpret_p8_f32(float32x2_t a);

// FORCE_INLINE poly16x4_t vreinterpret_p16_f32(float32x2_t a);

FORCE_INLINE uint32x2_t vreinterpret_u32_s64(int64x1_t a) {
  return __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vreinterpret_v_i64m1_u64m1(a));
}

// FORCE_INLINE poly8x8_t vreinterpret_p8_s64(int64x1_t a);

// FORCE_INLINE poly16x4_t vreinterpret_p16_s64(int64x1_t a);

FORCE_INLINE uint32x2_t vreinterpret_u32_u64(uint64x1_t a) { return __riscv_vreinterpret_v_u64m1_u32m1(a); }

// FORCE_INLINE poly8x8_t vreinterpret_p8_u64(uint64x1_t a);

// FORCE_INLINE poly16x4_t vreinterpret_p16_u64(uint64x1_t a);

FORCE_INLINE uint32x2_t vreinterpret_u32_s8(int8x8_t a) {
  return __riscv_vreinterpret_v_u8m1_u32m1(__riscv_vreinterpret_v_i8m1_u8m1(a));
}

// FORCE_INLINE poly8x8_t vreinterpret_p8_s8(int8x8_t a);

// FORCE_INLINE poly16x4_t vreinterpret_p16_s8(int8x8_t a);

FORCE_INLINE uint32x2_t vreinterpret_u32_s16(int16x4_t a) {
  return __riscv_vreinterpret_v_u16m1_u32m1(__riscv_vreinterpret_v_i16m1_u16m1(a));
}

// FORCE_INLINE poly8x8_t vreinterpret_p8_s16(int16x4_t a);

// FORCE_INLINE poly16x4_t vreinterpret_p16_s16(int16x4_t a);

FORCE_INLINE uint32x2_t vreinterpret_u32_s32(int32x2_t a) { return __riscv_vreinterpret_v_i32m1_u32m1(a); }

// FORCE_INLINE poly8x8_t vreinterpret_p8_s32(int32x2_t a);

// FORCE_INLINE poly16x4_t vreinterpret_p16_s32(int32x2_t a);

FORCE_INLINE uint32x2_t vreinterpret_u32_u8(uint8x8_t a) { return __riscv_vreinterpret_v_u8m1_u32m1(a); }

// FORCE_INLINE poly8x8_t vreinterpret_p8_u8(uint8x8_t a);

// FORCE_INLINE poly16x4_t vreinterpret_p16_u8(uint8x8_t a);

FORCE_INLINE uint32x2_t vreinterpret_u32_u16(uint16x4_t a) { return __riscv_vreinterpret_v_u16m1_u32m1(a); }

// FORCE_INLINE poly8x8_t vreinterpret_p8_u16(uint16x4_t a);

// FORCE_INLINE poly16x4_t vreinterpret_p16_u16(uint16x4_t a);

FORCE_INLINE float32x4_t vreinterpretq_f32_s64(int64x2_t a) {
  return __riscv_vreinterpret_v_i32m1_f32m1(__riscv_vreinterpret_v_i64m1_i32m1(a));
}

FORCE_INLINE float32x4_t vreinterpretq_f32_u64(uint64x2_t a) {
  return __riscv_vreinterpret_v_u32m1_f32m1(__riscv_vreinterpret_v_u64m1_u32m1(a));
}

FORCE_INLINE float32x4_t vreinterpretq_f32_s8(int8x16_t a) {
  return __riscv_vreinterpret_v_i32m1_f32m1(__riscv_vreinterpret_v_i8m1_i32m1(a));
}

FORCE_INLINE float32x4_t vreinterpretq_f32_s16(int16x8_t a) {
  return __riscv_vreinterpret_v_i32m1_f32m1(__riscv_vreinterpret_v_i16m1_i32m1(a));
}

FORCE_INLINE float32x4_t vreinterpretq_f32_s32(int32x4_t a) { return __riscv_vreinterpret_v_i32m1_f32m1(a); }

FORCE_INLINE float32x4_t vreinterpretq_f32_u8(uint8x16_t a) {
  return __riscv_vreinterpret_v_u32m1_f32m1(__riscv_vreinterpret_v_u8m1_u32m1(a));
}

FORCE_INLINE float32x4_t vreinterpretq_f32_u16(uint16x8_t a) {
  return __riscv_vreinterpret_v_u32m1_f32m1(__riscv_vreinterpret_v_u16m1_u32m1(a));
}

FORCE_INLINE float32x4_t vreinterpretq_f32_u32(uint32x4_t a) { return __riscv_vreinterpret_v_u32m1_f32m1(a); }

FORCE_INLINE int64x2_t vreinterpretq_s64_f32(float32x4_t a) {
  return __riscv_vreinterpret_v_i32m1_i64m1(__riscv_vreinterpret_v_f32m1_i32m1(a));
}

FORCE_INLINE float64x2_t vreinterpretq_f64_f32(float32x4_t a) {
  return __riscv_vreinterpret_v_u64m1_f64m1(__riscv_vreinterpret_v_u32m1_u64m1(__riscv_vreinterpret_v_f32m1_u32m1(a)));
}

// FORCE_INLINE poly64x2_t vreinterpretq_p64_f32(float32x4_t a);

// FORCE_INLINE poly128_t vreinterpretq_p128_f32(float32x4_t a);

// FORCE_INLINE poly64x2_t vreinterpretq_p64_f64(float64x2_t a);

// FORCE_INLINE poly128_t vreinterpretq_p128_f64(float64x2_t a);

// FORCE_INLINE float16x8_t vreinterpretq_f16_f32(float32x4_t a);

FORCE_INLINE int64x2_t vreinterpretq_s64_u64(uint64x2_t a) { return __riscv_vreinterpret_v_u64m1_i64m1(a); }

FORCE_INLINE float64x2_t vreinterpretq_f64_u64(uint64x2_t a) { return __riscv_vreinterpret_v_u64m1_f64m1(a); }

FORCE_INLINE float64x2_t vreinterpretq_f64_s64(int64x2_t a) { return __riscv_vreinterpret_v_i64m1_f64m1(a); }

// FORCE_INLINE poly64x2_t vreinterpretq_p64_s64(int64x2_t a);

// FORCE_INLINE poly128_t vreinterpretq_p128_s64(int64x2_t a);

// FORCE_INLINE poly64x2_t vreinterpretq_p64_u64(uint64x2_t a);

// FORCE_INLINE poly128_t vreinterpretq_p128_u64(uint64x2_t a);

// FORCE_INLINE float16x8_t vreinterpretq_f16_u64(uint64x2_t a);

FORCE_INLINE int64x2_t vreinterpretq_s64_s8(int8x16_t a) { return __riscv_vreinterpret_v_i8m1_i64m1(a); }

FORCE_INLINE float64x2_t vreinterpretq_f64_s8(int8x16_t a) {
  return __riscv_vreinterpret_v_i64m1_f64m1(__riscv_vreinterpret_v_i8m1_i64m1(a));
}

// FORCE_INLINE poly64x2_t vreinterpretq_p64_s8(int8x16_t a);

// FORCE_INLINE poly128_t vreinterpretq_p128_s8(int8x16_t a);

// FORCE_INLINE float16x8_t vreinterpretq_f16_s8(int8x16_t a);

FORCE_INLINE int64x2_t vreinterpretq_s64_s16(int16x8_t a) { return __riscv_vreinterpret_v_i16m1_i64m1(a); }

FORCE_INLINE float64x2_t vreinterpretq_f64_s16(int16x8_t a) {
  return __riscv_vreinterpret_v_i64m1_f64m1(__riscv_vreinterpret_v_i16m1_i64m1(a));
}

// FORCE_INLINE poly64x2_t vreinterpretq_p64_s16(int16x8_t a);

// FORCE_INLINE poly128_t vreinterpretq_p128_s16(int16x8_t a);

// FORCE_INLINE float16x8_t vreinterpretq_f16_s16(int16x8_t a);

FORCE_INLINE int64x2_t vreinterpretq_s64_s32(int32x4_t a) { return __riscv_vreinterpret_v_i32m1_i64m1(a); }

FORCE_INLINE float64x2_t vreinterpretq_f64_s32(int32x4_t a) {
  return __riscv_vreinterpret_v_i64m1_f64m1(__riscv_vreinterpret_v_i32m1_i64m1(a));
}

// FORCE_INLINE poly64x2_t vreinterpretq_p64_s32(int32x4_t a);

// FORCE_INLINE poly128_t vreinterpretq_p128_s32(int32x4_t a);

// FORCE_INLINE float16x8_t vreinterpretq_f16_s32(int32x4_t a);

FORCE_INLINE int64x2_t vreinterpretq_s64_u8(uint8x16_t a) {
  return __riscv_vreinterpret_v_i8m1_i64m1(__riscv_vreinterpret_v_u8m1_i8m1(a));
}

FORCE_INLINE float64x2_t vreinterpretq_f64_u8(uint8x16_t a) {
  return __riscv_vreinterpret_v_u64m1_f64m1(__riscv_vreinterpret_v_u8m1_u64m1(a));
}

// FORCE_INLINE poly64x2_t vreinterpretq_p64_u8(uint8x16_t a);

// FORCE_INLINE poly128_t vreinterpretq_p128_u8(uint8x16_t a);

// FORCE_INLINE float16x8_t vreinterpretq_f16_u8(uint8x16_t a);

FORCE_INLINE int64x2_t vreinterpretq_s64_u16(uint16x8_t a) {
  return __riscv_vreinterpret_v_i16m1_i64m1(__riscv_vreinterpret_v_u16m1_i16m1(a));
}

FORCE_INLINE float64x2_t vreinterpretq_f64_u16(uint16x8_t a) {
  return __riscv_vreinterpret_v_u64m1_f64m1(__riscv_vreinterpret_v_u16m1_u64m1(a));
}

// FORCE_INLINE poly64x2_t vreinterpretq_p64_u16(uint16x8_t a);

// FORCE_INLINE poly128_t vreinterpretq_p128_u16(uint16x8_t a);

// FORCE_INLINE float16x8_t vreinterpretq_f16_u16(uint16x8_t a);

FORCE_INLINE int64x2_t vreinterpretq_s64_u32(uint32x4_t a) {
  return __riscv_vreinterpret_v_i32m1_i64m1(__riscv_vreinterpret_v_u32m1_i32m1(a));
}

FORCE_INLINE float64x2_t vreinterpretq_f64_u32(uint32x4_t a) {
  return __riscv_vreinterpret_v_u64m1_f64m1(__riscv_vreinterpret_v_u32m1_u64m1(a));
}

// FORCE_INLINE poly64x2_t vreinterpretq_p64_u32(uint32x4_t a);

// FORCE_INLINE poly128_t vreinterpretq_p128_u32(uint32x4_t a);

// FORCE_INLINE float16x8_t vreinterpretq_f16_u32(uint32x4_t a);

// FORCE_INLINE int8x16_t vreinterpretq_s8_p8(poly8x16_t a);

// FORCE_INLINE int16x8_t vreinterpretq_s16_p8(poly8x16_t a);

// FORCE_INLINE int32x4_t vreinterpretq_s32_p8(poly8x16_t a);

// FORCE_INLINE float32x4_t vreinterpretq_f32_p8(poly8x16_t a);

// FORCE_INLINE uint8x16_t vreinterpretq_u8_p8(poly8x16_t a);

// FORCE_INLINE uint16x8_t vreinterpretq_u16_p8(poly8x16_t a);

// FORCE_INLINE uint32x4_t vreinterpretq_u32_p8(poly8x16_t a);

// FORCE_INLINE poly16x8_t vreinterpretq_p16_p8(poly8x16_t a);

// FORCE_INLINE uint64x2_t vreinterpretq_u64_p8(poly8x16_t a);

// FORCE_INLINE int64x2_t vreinterpretq_s64_p8(poly8x16_t a);

// FORCE_INLINE float64x2_t vreinterpretq_f64_p8(poly8x16_t a);

// FORCE_INLINE poly64x2_t vreinterpretq_p64_p8(poly8x16_t a);

// FORCE_INLINE poly128_t vreinterpretq_p128_p8(poly8x16_t a);

// FORCE_INLINE float16x8_t vreinterpretq_f16_p8(poly8x16_t a);

// FORCE_INLINE int8x16_t vreinterpretq_s8_p16(poly16x8_t a);

// FORCE_INLINE int16x8_t vreinterpretq_s16_p16(poly16x8_t a);

// FORCE_INLINE int32x4_t vreinterpretq_s32_p16(poly16x8_t a);

// FORCE_INLINE float32x4_t vreinterpretq_f32_p16(poly16x8_t a);

// FORCE_INLINE uint8x16_t vreinterpretq_u8_p16(poly16x8_t a);

// FORCE_INLINE uint16x8_t vreinterpretq_u16_p16(poly16x8_t a);

// FORCE_INLINE uint32x4_t vreinterpretq_u32_p16(poly16x8_t a);

// FORCE_INLINE poly8x16_t vreinterpretq_p8_p16(poly16x8_t a);

// FORCE_INLINE uint64x2_t vreinterpretq_u64_p16(poly16x8_t a);

// FORCE_INLINE int64x2_t vreinterpretq_s64_p16(poly16x8_t a);

// FORCE_INLINE float64x2_t vreinterpretq_f64_p16(poly16x8_t a);

// FORCE_INLINE poly64x2_t vreinterpretq_p64_p16(poly16x8_t a);

// FORCE_INLINE poly128_t vreinterpretq_p128_p16(poly16x8_t a);

// FORCE_INLINE float16x8_t vreinterpretq_f16_p16(poly16x8_t a);

FORCE_INLINE uint64x2_t vreinterpretq_u64_f32(float32x4_t a) {
  return __riscv_vreinterpret_v_u32m1_u64m1(__riscv_vreinterpret_v_f32m1_u32m1(a));
}

FORCE_INLINE uint64x2_t vreinterpretq_u64_s64(int64x2_t a) { return __riscv_vreinterpret_v_i64m1_u64m1(a); }

// FORCE_INLINE uint64x2_t vreinterpretq_u64_p64(poly64x2_t a);

// FORCE_INLINE float16x8_t vreinterpretq_f16_s64(int64x2_t a);

// FORCE_INLINE int8x16_t vreinterpretq_s8_f16(float16x8_t a);

// FORCE_INLINE int16x8_t vreinterpretq_s16_f16(float16x8_t a);

// FORCE_INLINE int32x4_t vreinterpretq_s32_f16(float16x8_t a);

// FORCE_INLINE float32x4_t vreinterpretq_f32_f16(float16x8_t a);

// FORCE_INLINE uint8x16_t vreinterpretq_u8_f16(float16x8_t a);

// FORCE_INLINE uint16x8_t vreinterpretq_u16_f16(float16x8_t a);

// FORCE_INLINE uint32x4_t vreinterpretq_u32_f16(float16x8_t a);

// FORCE_INLINE poly8x16_t vreinterpretq_p8_f16(float16x8_t a);

// FORCE_INLINE poly16x8_t vreinterpretq_p16_f16(float16x8_t a);

// FORCE_INLINE uint64x2_t vreinterpretq_u64_f16(float16x8_t a);

// FORCE_INLINE int64x2_t vreinterpretq_s64_f16(float16x8_t a);

// FORCE_INLINE float64x2_t vreinterpretq_f64_f16(float16x8_t a);

// FORCE_INLINE poly64x2_t vreinterpretq_p64_f16(float16x8_t a);

// FORCE_INLINE poly128_t vreinterpretq_p128_f16(float16x8_t a);

FORCE_INLINE int8x8_t vreinterpret_s8_f64(float64x1_t a) {
  return __riscv_vreinterpret_v_i64m1_i8m1(__riscv_vreinterpret_v_f64m1_i64m1(a));
}

FORCE_INLINE int16x4_t vreinterpret_s16_f64(float64x1_t a) {
  return __riscv_vreinterpret_v_i64m1_i16m1(__riscv_vreinterpret_v_f64m1_i64m1(a));
}

FORCE_INLINE int32x2_t vreinterpret_s32_f64(float64x1_t a) {
  return __riscv_vreinterpret_v_i64m1_i32m1(__riscv_vreinterpret_v_f64m1_i64m1(a));
}

FORCE_INLINE uint8x8_t vreinterpret_u8_f64(float64x1_t a) {
  return __riscv_vreinterpret_v_u64m1_u8m1(__riscv_vreinterpret_v_f64m1_u64m1(a));
}

FORCE_INLINE uint16x4_t vreinterpret_u16_f64(float64x1_t a) {
  return __riscv_vreinterpret_v_u64m1_u16m1(__riscv_vreinterpret_v_f64m1_u64m1(a));
}

FORCE_INLINE uint32x2_t vreinterpret_u32_f64(float64x1_t a) {
  return __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vreinterpret_v_f64m1_u64m1(a));
}

// FORCE_INLINE poly8x8_t vreinterpret_p8_f64(float64x1_t a);

// FORCE_INLINE poly16x4_t vreinterpret_p16_f64(float64x1_t a);

FORCE_INLINE uint64x1_t vreinterpret_u64_f64(float64x1_t a) { return __riscv_vreinterpret_v_f64m1_u64m1(a); }

FORCE_INLINE int64x1_t vreinterpret_s64_f64(float64x1_t a) { return __riscv_vreinterpret_v_f64m1_i64m1(a); }

// FORCE_INLINE float16x4_t vreinterpret_f16_f64(float64x1_t a);

FORCE_INLINE float32x2_t vreinterpret_f32_f64(float64x1_t a) {
  return __riscv_vreinterpret_v_u32m1_f32m1(__riscv_vreinterpret_v_u64m1_u32m1(__riscv_vreinterpret_v_f64m1_u64m1(a)));
}

FORCE_INLINE int8x16_t vreinterpretq_s8_f64(float64x2_t a) {
  return __riscv_vreinterpret_v_i64m1_i8m1(__riscv_vreinterpret_v_f64m1_i64m1(a));
}

FORCE_INLINE int16x8_t vreinterpretq_s16_f64(float64x2_t a) {
  return __riscv_vreinterpret_v_i64m1_i16m1(__riscv_vreinterpret_v_f64m1_i64m1(a));
}

FORCE_INLINE int32x4_t vreinterpretq_s32_f64(float64x2_t a) {
  return __riscv_vreinterpret_v_i64m1_i32m1(__riscv_vreinterpret_v_f64m1_i64m1(a));
}

FORCE_INLINE uint8x16_t vreinterpretq_u8_f64(float64x2_t a) {
  return __riscv_vreinterpret_v_u64m1_u8m1(__riscv_vreinterpret_v_f64m1_u64m1(a));
}

FORCE_INLINE uint16x8_t vreinterpretq_u16_f64(float64x2_t a) {
  return __riscv_vreinterpret_v_u64m1_u16m1(__riscv_vreinterpret_v_f64m1_u64m1(a));
}

FORCE_INLINE uint32x4_t vreinterpretq_u32_f64(float64x2_t a) {
  return __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vreinterpret_v_f64m1_u64m1(a));
}

// FORCE_INLINE poly8x16_t vreinterpretq_p8_f64(float64x2_t a);

// FORCE_INLINE poly16x8_t vreinterpretq_p16_f64(float64x2_t a);

FORCE_INLINE uint64x2_t vreinterpretq_u64_f64(float64x2_t a) { return __riscv_vreinterpret_v_f64m1_u64m1(a); }

FORCE_INLINE int64x2_t vreinterpretq_s64_f64(float64x2_t a) { return __riscv_vreinterpret_v_f64m1_i64m1(a); }

// FORCE_INLINE float16x8_t vreinterpretq_f16_f64(float64x2_t a);

FORCE_INLINE float32x4_t vreinterpretq_f32_f64(float64x2_t a) {
  return __riscv_vreinterpret_v_u32m1_f32m1(__riscv_vreinterpret_v_u64m1_u32m1(__riscv_vreinterpret_v_f64m1_u64m1(a)));
}

// FORCE_INLINE int8x8_t vreinterpret_s8_p64(poly64x1_t a);

// FORCE_INLINE int16x4_t vreinterpret_s16_p64(poly64x1_t a);

// FORCE_INLINE int32x2_t vreinterpret_s32_p64(poly64x1_t a);

// FORCE_INLINE uint8x8_t vreinterpret_u8_p64(poly64x1_t a);

// FORCE_INLINE uint16x4_t vreinterpret_u16_p64(poly64x1_t a);

// FORCE_INLINE uint32x2_t vreinterpret_u32_p64(poly64x1_t a);

// FORCE_INLINE poly8x8_t vreinterpret_p8_p64(poly64x1_t a);

// FORCE_INLINE poly16x4_t vreinterpret_p16_p64(poly64x1_t a);

// FORCE_INLINE int64x1_t vreinterpret_s64_p64(poly64x1_t a);

// FORCE_INLINE float64x1_t vreinterpret_f64_p64(poly64x1_t a);

// FORCE_INLINE float16x4_t vreinterpret_f16_p64(poly64x1_t a);

// FORCE_INLINE int8x16_t vreinterpretq_s8_p64(poly64x2_t a);

// FORCE_INLINE int16x8_t vreinterpretq_s16_p64(poly64x2_t a);

// FORCE_INLINE int32x4_t vreinterpretq_s32_p64(poly64x2_t a);

// FORCE_INLINE uint8x16_t vreinterpretq_u8_p64(poly64x2_t a);

// FORCE_INLINE uint16x8_t vreinterpretq_u16_p64(poly64x2_t a);

// FORCE_INLINE uint32x4_t vreinterpretq_u32_p64(poly64x2_t a);

// FORCE_INLINE poly8x16_t vreinterpretq_p8_p64(poly64x2_t a);

// FORCE_INLINE poly16x8_t vreinterpretq_p16_p64(poly64x2_t a);

// FORCE_INLINE int64x2_t vreinterpretq_s64_p64(poly64x2_t a);

// FORCE_INLINE float64x2_t vreinterpretq_f64_p64(poly64x2_t a);

// FORCE_INLINE float16x8_t vreinterpretq_f16_p64(poly64x2_t a);

// FORCE_INLINE int8x16_t vreinterpretq_s8_p128(poly128_t a);

// FORCE_INLINE int16x8_t vreinterpretq_s16_p128(poly128_t a);

// FORCE_INLINE int32x4_t vreinterpretq_s32_p128(poly128_t a);

// FORCE_INLINE uint8x16_t vreinterpretq_u8_p128(poly128_t a);

// FORCE_INLINE uint16x8_t vreinterpretq_u16_p128(poly128_t a);

// FORCE_INLINE uint32x4_t vreinterpretq_u32_p128(poly128_t a);

// FORCE_INLINE poly8x16_t vreinterpretq_p8_p128(poly128_t a);

// FORCE_INLINE poly16x8_t vreinterpretq_p16_p128(poly128_t a);

// FORCE_INLINE uint64x2_t vreinterpretq_u64_p128(poly128_t a);

// FORCE_INLINE int64x2_t vreinterpretq_s64_p128(poly128_t a);

// FORCE_INLINE float64x2_t vreinterpretq_f64_p128(poly128_t a);

// FORCE_INLINE float16x8_t vreinterpretq_f16_p128(poly128_t a);

// FORCE_INLINE poly128_t vldrq_p128(poly128_t const * ptr);

// FORCE_INLINE void vstrq_p128(poly128_t * ptr, poly128_t val);

FORCE_INLINE uint64x2_t vreinterpretq_u64_s8(int8x16_t a) {
  return __riscv_vreinterpret_v_u8m1_u64m1(__riscv_vreinterpret_v_i8m1_u8m1(a));
}

FORCE_INLINE uint64x2_t vreinterpretq_u64_s16(int16x8_t a) {
  return __riscv_vreinterpret_v_u16m1_u64m1(__riscv_vreinterpret_v_i16m1_u16m1(a));
}

FORCE_INLINE uint64x2_t vreinterpretq_u64_s32(int32x4_t a) {
  return __riscv_vreinterpret_v_u32m1_u64m1(__riscv_vreinterpret_v_i32m1_u32m1(a));
}

FORCE_INLINE uint64x2_t vreinterpretq_u64_u8(uint8x16_t a) { return __riscv_vreinterpret_v_u8m1_u64m1(a); }

FORCE_INLINE uint64x2_t vreinterpretq_u64_u16(uint16x8_t a) { return __riscv_vreinterpret_v_u16m1_u64m1(a); }

FORCE_INLINE uint64x2_t vreinterpretq_u64_u32(uint32x4_t a) { return __riscv_vreinterpret_v_u32m1_u64m1(a); }

FORCE_INLINE int8x16_t vreinterpretq_s8_f32(float32x4_t a) {
  return __riscv_vreinterpret_v_i32m1_i8m1(__riscv_vreinterpret_v_f32m1_i32m1(a));
}

FORCE_INLINE int8x16_t vreinterpretq_s8_s64(int64x2_t a) { return __riscv_vreinterpret_v_i64m1_i8m1(a); }

FORCE_INLINE int8x16_t vreinterpretq_s8_u64(uint64x2_t a) {
  return __riscv_vreinterpret_v_i64m1_i8m1(__riscv_vreinterpret_v_u64m1_i64m1(a));
}

FORCE_INLINE int8x16_t vreinterpretq_s8_s16(int16x8_t a) { return __riscv_vreinterpret_v_i16m1_i8m1(a); }

FORCE_INLINE int8x16_t vreinterpretq_s8_s32(int32x4_t a) { return __riscv_vreinterpret_v_i32m1_i8m1(a); }

FORCE_INLINE int8x16_t vreinterpretq_s8_u8(uint8x16_t a) { return __riscv_vreinterpret_v_u8m1_i8m1(a); }

FORCE_INLINE int8x16_t vreinterpretq_s8_u16(uint16x8_t a) {
  return __riscv_vreinterpret_v_i16m1_i8m1(__riscv_vreinterpret_v_u16m1_i16m1(a));
}

FORCE_INLINE int8x16_t vreinterpretq_s8_u32(uint32x4_t a) {
  return __riscv_vreinterpret_v_i32m1_i8m1(__riscv_vreinterpret_v_u32m1_i32m1(a));
}

FORCE_INLINE int16x8_t vreinterpretq_s16_f32(float32x4_t a) {
  return __riscv_vreinterpret_v_i32m1_i16m1(__riscv_vreinterpret_v_f32m1_i32m1(a));
}

FORCE_INLINE int16x8_t vreinterpretq_s16_s64(int64x2_t a) { return __riscv_vreinterpret_v_i64m1_i16m1(a); }

FORCE_INLINE int16x8_t vreinterpretq_s16_u64(uint64x2_t a) {
  return __riscv_vreinterpret_v_i64m1_i16m1(__riscv_vreinterpret_v_u64m1_i64m1(a));
}

FORCE_INLINE int16x8_t vreinterpretq_s16_s8(int8x16_t a) { return __riscv_vreinterpret_v_i8m1_i16m1(a); }

FORCE_INLINE int16x8_t vreinterpretq_s16_s32(int32x4_t a) { return __riscv_vreinterpret_v_i32m1_i16m1(a); }

FORCE_INLINE int16x8_t vreinterpretq_s16_u8(uint8x16_t a) {
  return __riscv_vreinterpret_v_i8m1_i16m1(__riscv_vreinterpret_v_u8m1_i8m1(a));
}

FORCE_INLINE int16x8_t vreinterpretq_s16_u16(uint16x8_t a) { return __riscv_vreinterpret_v_u16m1_i16m1(a); }

FORCE_INLINE int16x8_t vreinterpretq_s16_u32(uint32x4_t a) {
  return __riscv_vreinterpret_v_i32m1_i16m1(__riscv_vreinterpret_v_u32m1_i32m1(a));
}

FORCE_INLINE int32x4_t vreinterpretq_s32_f32(float32x4_t a) { return __riscv_vreinterpret_v_f32m1_i32m1(a); }

FORCE_INLINE int32x4_t vreinterpretq_s32_s64(int64x2_t a) { return __riscv_vreinterpret_v_i64m1_i32m1(a); }

FORCE_INLINE int32x4_t vreinterpretq_s32_u64(uint64x2_t a) {
  return __riscv_vreinterpret_v_i64m1_i32m1(__riscv_vreinterpret_v_u64m1_i64m1(a));
}

FORCE_INLINE int32x4_t vreinterpretq_s32_s8(int8x16_t a) { return __riscv_vreinterpret_v_i8m1_i32m1(a); }

FORCE_INLINE int32x4_t vreinterpretq_s32_s16(int16x8_t a) { return __riscv_vreinterpret_v_i16m1_i32m1(a); }

FORCE_INLINE int32x4_t vreinterpretq_s32_u8(uint8x16_t a) {
  return __riscv_vreinterpret_v_i8m1_i32m1(__riscv_vreinterpret_v_u8m1_i8m1(a));
}

FORCE_INLINE int32x4_t vreinterpretq_s32_u16(uint16x8_t a) {
  return __riscv_vreinterpret_v_i16m1_i32m1(__riscv_vreinterpret_v_u16m1_i16m1(a));
}

FORCE_INLINE int32x4_t vreinterpretq_s32_u32(uint32x4_t a) { return __riscv_vreinterpret_v_u32m1_i32m1(a); }

FORCE_INLINE uint8x16_t vreinterpretq_u8_f32(float32x4_t a) {
  return __riscv_vreinterpret_v_u32m1_u8m1(__riscv_vreinterpret_v_f32m1_u32m1(a));
}

FORCE_INLINE uint8x16_t vreinterpretq_u8_s64(int64x2_t a) {
  return __riscv_vreinterpret_v_u64m1_u8m1(__riscv_vreinterpret_v_i64m1_u64m1(a));
}

FORCE_INLINE uint8x16_t vreinterpretq_u8_u64(uint64x2_t a) { return __riscv_vreinterpret_v_u64m1_u8m1(a); }

FORCE_INLINE uint8x16_t vreinterpretq_u8_s8(int8x16_t a) { return __riscv_vreinterpret_v_i8m1_u8m1(a); }

FORCE_INLINE uint8x16_t vreinterpretq_u8_s16(int16x8_t a) {
  return __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vreinterpret_v_i16m1_u16m1(a));
}

FORCE_INLINE uint8x16_t vreinterpretq_u8_s32(int32x4_t a) {
  return __riscv_vreinterpret_v_u32m1_u8m1(__riscv_vreinterpret_v_i32m1_u32m1(a));
}

FORCE_INLINE uint8x16_t vreinterpretq_u8_u16(uint16x8_t a) { return __riscv_vreinterpret_v_u16m1_u8m1(a); }

FORCE_INLINE uint8x16_t vreinterpretq_u8_u32(uint32x4_t a) { return __riscv_vreinterpret_v_u32m1_u8m1(a); }

FORCE_INLINE uint16x8_t vreinterpretq_u16_f32(float32x4_t a) {
  return __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vreinterpret_v_f32m1_u32m1(a));
}

FORCE_INLINE uint16x8_t vreinterpretq_u16_s64(int64x2_t a) {
  return __riscv_vreinterpret_v_u64m1_u16m1(__riscv_vreinterpret_v_i64m1_u64m1(a));
}

FORCE_INLINE uint16x8_t vreinterpretq_u16_u64(uint64x2_t a) { return __riscv_vreinterpret_v_u64m1_u16m1(a); }

FORCE_INLINE uint16x8_t vreinterpretq_u16_s8(int8x16_t a) {
  return __riscv_vreinterpret_v_u8m1_u16m1(__riscv_vreinterpret_v_i8m1_u8m1(a));
}

FORCE_INLINE uint16x8_t vreinterpretq_u16_s16(int16x8_t a) { return __riscv_vreinterpret_v_i16m1_u16m1(a); }

FORCE_INLINE uint16x8_t vreinterpretq_u16_s32(int32x4_t a) {
  return __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vreinterpret_v_i32m1_u32m1(a));
}

FORCE_INLINE uint16x8_t vreinterpretq_u16_u8(uint8x16_t a) { return __riscv_vreinterpret_v_u8m1_u16m1(a); }

FORCE_INLINE uint16x8_t vreinterpretq_u16_u32(uint32x4_t a) { return __riscv_vreinterpret_v_u32m1_u16m1(a); }

// FORCE_INLINE poly8x16_t vreinterpretq_p8_u32(uint32x4_t a);

// FORCE_INLINE poly16x8_t vreinterpretq_p16_u32(uint32x4_t a);

FORCE_INLINE uint32x4_t vreinterpretq_u32_f32(float32x4_t a) { return __riscv_vreinterpret_v_f32m1_u32m1(a); }

// FORCE_INLINE poly8x16_t vreinterpretq_p8_f32(float32x4_t a);

// FORCE_INLINE poly16x8_t vreinterpretq_p16_f32(float32x4_t a);

FORCE_INLINE uint32x4_t vreinterpretq_u32_s64(int64x2_t a) {
  return __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vreinterpret_v_i64m1_u64m1(a));
}

// FORCE_INLINE poly8x16_t vreinterpretq_p8_s64(int64x2_t a);

// FORCE_INLINE poly16x8_t vreinterpretq_p16_s64(int64x2_t a);

FORCE_INLINE uint32x4_t vreinterpretq_u32_u64(uint64x2_t a) { return __riscv_vreinterpret_v_u64m1_u32m1(a); }

// FORCE_INLINE poly8x16_t vreinterpretq_p8_u64(uint64x2_t a);

// FORCE_INLINE poly16x8_t vreinterpretq_p16_u64(uint64x2_t a);

FORCE_INLINE uint32x4_t vreinterpretq_u32_s8(int8x16_t a) {
  return __riscv_vreinterpret_v_u8m1_u32m1(__riscv_vreinterpret_v_i8m1_u8m1(a));
}

// FORCE_INLINE poly8x16_t vreinterpretq_p8_s8(int8x16_t a);

// FORCE_INLINE poly16x8_t vreinterpretq_p16_s8(int8x16_t a);

FORCE_INLINE uint32x4_t vreinterpretq_u32_s16(int16x8_t a) {
  return __riscv_vreinterpret_v_u16m1_u32m1(__riscv_vreinterpret_v_i16m1_u16m1(a));
}

// FORCE_INLINE poly8x16_t vreinterpretq_p8_s16(int16x8_t a);

// FORCE_INLINE poly16x8_t vreinterpretq_p16_s16(int16x8_t a);

FORCE_INLINE uint32x4_t vreinterpretq_u32_s32(int32x4_t a) { return __riscv_vreinterpret_v_i32m1_u32m1(a); }

// FORCE_INLINE poly8x16_t vreinterpretq_p8_s32(int32x4_t a);

// FORCE_INLINE poly16x8_t vreinterpretq_p16_s32(int32x4_t a);

FORCE_INLINE uint32x4_t vreinterpretq_u32_u8(uint8x16_t a) { return __riscv_vreinterpret_v_u8m1_u32m1(a); }

// FORCE_INLINE poly8x16_t vreinterpretq_p8_u8(uint8x16_t a);

// FORCE_INLINE poly16x8_t vreinterpretq_p16_u8(uint8x16_t a);

FORCE_INLINE uint32x4_t vreinterpretq_u32_u16(uint16x8_t a) { return __riscv_vreinterpret_v_u16m1_u32m1(a); }

// FORCE_INLINE poly8x16_t vreinterpretq_p8_u16(uint16x8_t a);

// FORCE_INLINE poly16x8_t vreinterpretq_p16_u16(uint16x8_t a);

// FORCE_INLINE uint8x16_t vaeseq_u8(uint8x16_t __data, uint8x16_t __key);

// FORCE_INLINE uint8x16_t vaesdq_u8(uint8x16_t __data, uint8x16_t __key);

// FORCE_INLINE uint8x16_t vaesmcq_u8(uint8x16_t __data);

// FORCE_INLINE uint8x16_t vaesimcq_u8(uint8x16_t __data);

// FORCE_INLINE uint32_t vsha1h_u32(uint32_t __hash_e);

// FORCE_INLINE uint32x4_t vsha1cq_u32(uint32x4_t __hash_abcd, uint32_t __hash_e, uint32x4_t __wk);

// FORCE_INLINE uint32x4_t vsha1pq_u32(uint32x4_t __hash_abcd, uint32_t __hash_e, uint32x4_t __wk);

// FORCE_INLINE uint32x4_t vsha1mq_u32(uint32x4_t __hash_abcd, uint32_t __hash_e, uint32x4_t __wk);

// FORCE_INLINE uint32x4_t vsha1su0q_u32(uint32x4_t __w0_3, uint32x4_t __w4_7, uint32x4_t __w8_11);

// FORCE_INLINE uint32x4_t vsha1su1q_u32(uint32x4_t __tw0_3, uint32x4_t __w12_15);

// FORCE_INLINE uint32x4_t vsha256hq_u32(uint32x4_t __hash_abcd, uint32x4_t __hash_efgh, uint32x4_t __wk);

// FORCE_INLINE uint32x4_t vsha256h2q_u32(uint32x4_t __hash_abcd, uint32x4_t __hash_efgh, uint32x4_t __wk);

// FORCE_INLINE uint32x4_t vsha256su0q_u32(uint32x4_t __w0_3, uint32x4_t __w4_7);

// FORCE_INLINE uint32x4_t vsha256su1q_u32(uint32x4_t __tw0_3, uint32x4_t __w8_11, uint32x4_t __w12_15);

// FORCE_INLINE poly128_t vmull_p64(poly64_t a, poly64_t b);

// FORCE_INLINE poly128_t vmull_high_p64(poly64x2_t a, poly64x2_t b);

// FORCE_INLINE poly8x8_t vadd_p8(poly8x8_t a, poly8x8_t b);

// FORCE_INLINE poly16x4_t vadd_p16(poly16x4_t a, poly16x4_t b);

// FORCE_INLINE poly64x1_t vadd_p64(poly64x1_t a, poly64x1_t b);

// FORCE_INLINE poly8x16_t vaddq_p8(poly8x16_t a, poly8x16_t b);

// FORCE_INLINE poly16x8_t vaddq_p16(poly16x8_t a, poly16x8_t b);

// FORCE_INLINE poly64x2_t vaddq_p64(poly64x2_t a, poly64x2_t b);

// FORCE_INLINE poly128_t vaddq_p128(poly128_t a, poly128_t b);

// FORCE_INLINE uint32_t __crc32b(uint32_t a, uint8_t b);

// FORCE_INLINE uint32_t __crc32h(uint32_t a, uint16_t b);

// FORCE_INLINE uint32_t __crc32w(uint32_t a, uint32_t b);

// FORCE_INLINE uint32_t __crc32d(uint32_t a, uint64_t b);

// FORCE_INLINE uint32_t __crc32cb(uint32_t a, uint8_t b);

// FORCE_INLINE uint32_t __crc32ch(uint32_t a, uint16_t b);

// FORCE_INLINE uint32_t __crc32cw(uint32_t a, uint32_t b);

// FORCE_INLINE uint32_t __crc32cd(uint32_t a, uint64_t b);

#ifdef __cplusplus
}
#endif

#if defined(__GNUC__) || defined(__clang__)
#pragma pop_macro("ALIGN_STRUCT")
#pragma pop_macro("FORCE_INLINE")
#endif

// TODO uncomment this and put all the implementation into `#elif defined(__riscv) || defined(__riscv__)`
// #endif /* #elif (defined(__riscv) || defined(__riscv__)) */

#endif /* NEON2RVV_H */
