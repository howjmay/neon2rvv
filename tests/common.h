#ifndef NEON2RVV_COMMON_H
#define NEON2RVV_COMMON_H

#include <stdio.h>
#include <cstdint>

#if defined(__riscv) || defined(__riscv__)
#include "neon2rvv.h"
#elif (defined(__aarch64__) || defined(_M_ARM64)) || defined(__arm__)
#include <arm_neon.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma push_macro("ALIGN_STRUCT")
#define ALIGN_STRUCT(x) __attribute__((aligned(x)))
#else
#define ALIGN_STRUCT(x) __declspec(align(x))
#endif  // defined(__GNUC__) || defined(__clang__)

typedef union ALIGN_STRUCT(16) SIMDVec {
  float m128_f32[4];     // as floats - DON'T USE. Added for convenience.
  int8_t m128_i8[16];    // as signed 8-bit integers.
  int16_t m128_i16[8];   // as signed 16-bit integers.
  int32_t m128_i32[4];   // as signed 32-bit integers.
  int64_t m128_i64[2];   // as signed 64-bit integers.
  uint8_t m128_u8[16];   // as unsigned 8-bit integers.
  uint16_t m128_u16[8];  // as unsigned 16-bit integers.
  uint32_t m128_u32[4];  // as unsigned 32-bit integers.
  uint64_t m128_u64[2];  // as unsigned 64-bit integers.
} SIMDVec;

#if defined(__GNUC__) || defined(__clang__)
#pragma pop_macro("ALIGN_STRUCT")
#endif  // defined(__GNUC__) || defined(__clang__)
#endif  // defined(__riscv) || defined(__riscv__)

#define ASSERT_RETURN(x) \
  if (!(x))              \
    return TEST_FAIL;

namespace NEON2RVV {

// A replica of typedefs in neon2rvv.h. This is only to make implementing tests easier.
#if __riscv_v_min_vlen == 128
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

// FIXME wrong typedefs, just for passing compilation
typedef vint8m1x2_t int8x8x2_t;
typedef vuint8m1x2_t uint8x8x2_t;
typedef vint8m2_t int8x16x2_t;
typedef vuint8m2_t uint8x16x2_t;
typedef vint8m4_t int8x16x3_t;
typedef vuint8m4_t uint8x16x3_t;
typedef vint8m4_t int8x16x4_t;
typedef vuint8m4_t uint8x16x4_t;
typedef vint8m4_t int8x8x3_t;
typedef vuint8m4_t uint8x8x3_t;
typedef vint8m4_t int8x8x4_t;
typedef vuint8m4_t uint8x8x4_t;
typedef vint16m2_t int16x4x2_t;
typedef vuint16m2_t uint16x4x2_t;
typedef vint16m4_t int16x4x3_t;
typedef vuint16m4_t uint16x4x3_t;
typedef vint16m4_t int16x4x4_t;
typedef vuint16m4_t uint16x4x4_t;
typedef vint16m2_t int16x8x2_t;
typedef vuint16m2_t uint16x8x2_t;
typedef vint16m4_t int16x8x3_t;
typedef vuint16m4_t uint16x8x3_t;
typedef vint16m4_t int16x8x4_t;
typedef vuint16m4_t uint16x8x4_t;
typedef vint32m2_t int32x2x2_t;
typedef vuint32m2_t uint32x2x2_t;
typedef vint32m4_t int32x2x3_t;
typedef vuint32m4_t uint32x2x3_t;
typedef vint32m4_t int32x2x4_t;
typedef vuint32m4_t uint32x2x4_t;
typedef vint32m4_t int32x2x4_t;
typedef vuint32m4_t uint32x2x4_t;
typedef vint32m2_t int32x4x2_t;
typedef vuint32m2_t uint32x4x2_t;
typedef vint32m4_t int32x4x3_t;
typedef vuint32m4_t uint32x4x3_t;
typedef vint32m4_t int32x4x4_t;
typedef vuint32m4_t uint32x4x4_t;
typedef vfloat32m2_t float32x2x2_t;
typedef vfloat32m4_t float32x2x3_t;
typedef vfloat32m4_t float32x2x4_t;
typedef vfloat32m2_t float32x4x2_t;
typedef vfloat32m4_t float32x4x3_t;
typedef vfloat32m4_t float32x4x4_t;
typedef vint64m2_t int64x1x2_t;
typedef vuint64m2_t uint64x1x2_t;
typedef vint64m4_t int64x1x3_t;
typedef vuint64m4_t uint64x1x3_t;
typedef vint64m4_t int64x1x4_t;
typedef vuint64m4_t uint64x1x4_t;
#elif __riscv_v_min_vlen == 256
#elif __riscv_v_min_vlen == 512
#else
// typedef for other VLEN
#endif

enum result_t {
  TEST_SUCCESS = 1,
  TEST_FAIL = 0,
  TEST_UNIMPL = -1,
};
extern int32_t NaN;
extern int64_t NaN64;
#define ALL_BIT_1_32 (*(float *)&NaN)
#define ALL_BIT_1_64 (*(double *)&NaN64)

template <typename T, typename U>
result_t validate_64_bits(T a, U b) {
  const int32_t *t1 = (const int32_t *)&a;
  const int32_t *t2 = (const int32_t *)&b;

  ASSERT_RETURN(t1[0] == t2[0]);
  ASSERT_RETURN(t1[1] == t2[1]);
  return TEST_SUCCESS;
}
template <typename T, typename U>
result_t validate_128_bits(T a, U b) {
  const int32_t *t1 = (const int32_t *)&a;
  const int32_t *t2 = (const int32_t *)&b;

  ASSERT_RETURN(t1[0] == t2[0]);
  ASSERT_RETURN(t1[1] == t2[1]);
  ASSERT_RETURN(t1[2] == t2[2]);
  ASSERT_RETURN(t1[3] == t2[3]);
  return TEST_SUCCESS;
}
result_t validate_int64(int64x2_t a, int64_t i0, int64_t i1);
result_t validate_uint64(uint64x2_t a, uint64_t i0, uint64_t i1);
result_t validate_int64(int64x1_t a, int64_t i0);
result_t validate_uint64(uint64x1_t a, uint64_t i0);
result_t validate_int32(int32x4_t a, int32_t i0, int32_t i1, int32_t i2, int32_t i3);
result_t validate_uint32(uint32x4_t a, uint32_t u0, uint32_t u1, uint32_t u2, uint32_t u3);
result_t validate_int32(int32x2_t a, int32_t u0, int32_t u1);
result_t validate_uint32(uint32x2_t a, uint32_t u0, uint32_t u1);
result_t validate_int16(int16x8_t a, int16_t i0, int16_t i1, int16_t i2, int16_t i3, int16_t i4, int16_t i5, int16_t i6,
                        int16_t i7);
result_t validate_uint16(uint16x8_t a, uint16_t u0, uint16_t u1, uint16_t u2, uint16_t u3, uint16_t u4, uint16_t u5,
                         uint16_t u6, uint16_t u7);
result_t validate_int16(int16x4_t a, int16_t i0, int16_t i1, int16_t i2, int16_t i3);
result_t validate_uint16(uint16x4_t a, uint16_t u0, uint16_t u1, uint16_t u2, uint16_t u3);
result_t validate_int8(int8x16_t a, int8_t i0, int8_t i1, int8_t i2, int8_t i3, int8_t i4, int8_t i5, int8_t i6,
                       int8_t i7, int8_t i8, int8_t i9, int8_t i10, int8_t i11, int8_t i12, int8_t i13, int8_t i14,
                       int8_t i15);
result_t validate_uint8(uint8x16_t a, uint8_t u0, uint8_t u1, uint8_t u2, uint8_t u3, uint8_t u4, uint8_t u5,
                        uint8_t u6, uint8_t u7, uint8_t u8, uint8_t u9, uint8_t u10, uint8_t u11, uint8_t u12,
                        uint8_t u13, uint8_t u14, uint8_t u15);
result_t validate_int8(int8x8x2_t a, int8_t i0, int8_t i1, int8_t i2, int8_t i3, int8_t i4, int8_t i5, int8_t i6,
                       int8_t i7, int8_t i8, int8_t i9, int8_t i10, int8_t i11, int8_t i12, int8_t i13, int8_t i14,
                       int8_t i15);
result_t validate_uint8(uint8x8x2_t a, uint8_t u0, uint8_t u1, uint8_t u2, uint8_t u3, uint8_t u4, uint8_t u5,
                        uint8_t u6, uint8_t u7, uint8_t u8, uint8_t u9, uint8_t u10, uint8_t u11, uint8_t u12,
                        uint8_t u13, uint8_t u14, uint8_t u15);
result_t validate_int8(int8x8_t a, int8_t i0, int8_t i1, int8_t i2, int8_t i3, int8_t i4, int8_t i5, int8_t i6,
                       int8_t i7);
result_t validate_uint8(uint8x8_t a, uint8_t u0, uint8_t u1, uint8_t u2, uint8_t u3, uint8_t u4, uint8_t u5, uint8_t u6,
                        uint8_t u7);
result_t validate_float_pair(float a, float b);
result_t validate_double_pair(double a, double b);
result_t validate_float(float32x2_t a, float f0, float f1);
result_t validate_float(float32x4_t a, float f0, float f1, float f2, float f3);
result_t validate_float_epsilon(float32x4_t a, float f0, float f1, float f2, float f3, float epsilon);
result_t validate_float_error(float32x4_t a, float f0, float f1, float f2, float f3, float err);
result_t validate_double(float64x2_t a, double d0, double d1);
result_t validate_float_error(float64x2_t a, double d0, double d1, double err);

int saturate_int16(int a);
long int saturate_int32(int a);

void print_64_bits_u8_arr(char *var_name, const uint8_t *u);
void print_128_bits_u8_arr(char *var_name, const uint8_t *u);

void print_64_bits_in_u8(char *var_name, uint8_t u0, uint8_t u1, uint8_t u2, uint8_t u3, uint8_t u4, uint8_t u5,
                         uint8_t u6, uint8_t u7);
void print_64_bits_in_u8(char *var_name, int8_t i0, int8_t i1, int8_t i2, int8_t i3, int8_t i4, int8_t i5, int8_t i6,
                         int8_t i7);
void print_64_bits_in_u8(char *var_name, uint16_t u0, uint16_t u1, uint16_t u2, uint16_t u3);
void print_64_bits_in_u8(char *var_name, int16_t i0, int16_t i1, int16_t i2, int16_t i3);
void print_64_bits_in_u8(char *var_name, uint32_t u0, uint32_t u1);
void print_64_bits_in_u8(char *var_name, int32_t i0, int32_t i1);
void print_64_bits_in_u8(char *var_name, uint64_t u0);
void print_64_bits_in_u8(char *var_name, int64_t i0);
template <typename T>
void print_64_bits_in_u8(char *var_name, T a) {
  const uint8_t *u = (const uint8_t *)&a;
  print_64_bits_u8_arr(var_name, u);
}
template <typename T>
void print_64_bits_in_u8(char *var_name, T *a) {
  const uint8_t *u = (const uint8_t *)a;
  print_64_bits_u8_arr(var_name, u);
}

void print_128_bits_in_u8(char *var_name, uint8_t u0, uint8_t u1, uint8_t u2, uint8_t u3, uint8_t u4, uint8_t u5,
                          uint8_t u6, uint8_t u7, uint8_t u8, uint8_t u9, uint8_t u10, uint8_t u11, uint8_t u12,
                          uint8_t u13, uint8_t u14, uint8_t u15);
void print_128_bits_in_u8(char *var_name, int8_t i0, int8_t i1, int8_t i2, int8_t i3, int8_t i4, int8_t i5, int8_t i6,
                          int8_t i7, int8_t i8, int8_t i9, int8_t i10, int8_t i11, int8_t i12, int8_t i13, int8_t i14,
                          int8_t i15);
void print_128_bits_in_u8(char *var_name, uint16_t u0, uint16_t u1, uint16_t u2, uint16_t u3, uint16_t u4, uint16_t u5,
                          uint16_t u6, uint16_t u7);
void print_128_bits_in_u8(char *var_name, int16_t i0, int16_t i1, int16_t i2, int16_t i3, int16_t i4, int16_t i5,
                          int16_t i6, int16_t i7);
void print_128_bits_in_u8(char *var_name, uint32_t u0, uint32_t u1, uint32_t u2, uint32_t u3);
void print_128_bits_in_u8(char *var_name, int32_t i0, int32_t i1, int32_t i2, int32_t i3);
void print_128_bits_in_u8(char *var_name, uint64_t u0, uint64_t u1);
void print_128_bits_in_u8(char *var_name, int64_t i0, int64_t i1);
template <typename T>
void print_128_bits_in_u8(char *var_name, T a) {
  const uint8_t *u = (const uint8_t *)&a;
  print_128_bits_u8_arr(var_name, u);
}
template <typename T>
void print_128_bits_in_u8(char *var_name, T *a) {
  const uint8_t *u = (const uint8_t *)a;
  print_128_bits_u8_arr(var_name, u);
}

}  // namespace NEON2RVV

#endif  // NEON2RVV_COMMON_H
