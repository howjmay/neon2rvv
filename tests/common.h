#ifndef NEON2RVV_COMMON_H
#define NEON2RVV_COMMON_H

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
#endif

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
#endif

#endif

#define ASSERT_RETURN(x) \
  if (!(x))              \
    return TEST_FAIL;

namespace NEON2RVV {
enum result_t {
  TEST_SUCCESS = 1,
  TEST_FAIL = 0,
  TEST_UNIMPL = -1,
};
extern int32_t NaN;
extern int64_t NaN64;
#define ALL_BIT_1_32 (*(float *)&NaN)
#define ALL_BIT_1_64 (*(double *)&NaN64)

template <typename T>
result_t validate_128bits(T a, T b) {
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
}  // namespace NEON2RVV

#endif  // NEON2RVV_COMMON_H
