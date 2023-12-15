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
result_t validate_uint64(uint64x2_t a, uint64_t u0, uint64_t u1);
result_t validate_int64(int64x2x2_t a, int64_t i0, int64_t i1, int64_t i2, int64_t i3);
result_t validate_uint64(uint64x2x2_t a, uint64_t u0, uint64_t u1, uint64_t u2, uint64_t u3);
result_t validate_int64(int64x1_t a, int64_t i0);
result_t validate_uint64(uint64x1_t a, uint64_t u0);
result_t validate_int64(int64x1x2_t a, int64_t i0, int64_t i1);
result_t validate_uint64(uint64x1x2_t a, uint64_t u0, uint64_t u1);
result_t validate_int32(int32x4_t a, int32_t i0, int32_t i1, int32_t i2, int32_t i3);
result_t validate_uint32(uint32x4_t a, uint32_t u0, uint32_t u1, uint32_t u2, uint32_t u3);
result_t validate_int32(int32x4x2_t a, int32_t i0, int32_t i1, int32_t i2, int32_t i3, int32_t i4, int32_t i5,
                        int32_t i6, int32_t i7);
result_t validate_uint32(uint32x4x2_t a, uint32_t u0, uint32_t u1, uint32_t u2, uint32_t u3, uint32_t u4, uint32_t u5,
                         uint32_t u6, uint32_t u7);
result_t validate_int32(int32x2_t a, int32_t i0, int32_t i1);
result_t validate_uint32(uint32x2_t a, uint32_t u0, uint32_t u1);
result_t validate_int32(int32x2x2_t a, int32_t i0, int32_t i1, int32_t i2, int32_t i3);
result_t validate_uint32(uint32x2x2_t a, uint32_t u0, uint32_t u1, uint32_t u2, uint32_t u3);
result_t validate_int16(int16x8_t a, int16_t i0, int16_t i1, int16_t i2, int16_t i3, int16_t i4, int16_t i5, int16_t i6,
                        int16_t i7);
result_t validate_uint16(uint16x8_t a, uint16_t u0, uint16_t u1, uint16_t u2, uint16_t u3, uint16_t u4, uint16_t u5,
                         uint16_t u6, uint16_t u7);
result_t validate_int16(int16x8x2_t a, int16_t i0, int16_t i1, int16_t i2, int16_t i3, int16_t i4, int16_t i5,
                        int16_t i6, int16_t i7, int16_t i8, int16_t i9, int16_t i10, int16_t i11, int16_t i12,
                        int16_t i13, int16_t i14, int16_t i15);
result_t validate_uint16(uint16x8x2_t a, uint16_t u0, uint16_t u1, uint16_t u2, uint16_t u3, uint16_t u4, uint16_t u5,
                         uint16_t u6, uint16_t u7, uint16_t u8, uint16_t u9, uint16_t u10, uint16_t u11, uint16_t u12,
                         uint16_t u13, uint16_t u14, uint16_t u15);
result_t validate_int16(int16x4_t a, int16_t i0, int16_t i1, int16_t i2, int16_t i3);
result_t validate_uint16(uint16x4_t a, uint16_t u0, uint16_t u1, uint16_t u2, uint16_t u3);
result_t validate_int16(int16x4x2_t a, int16_t i0, int16_t i1, int16_t i2, int16_t i3, int16_t i4, int16_t i5,
                        int16_t i6, int16_t i7);
result_t validate_uint16(uint16x4x2_t a, uint16_t u0, uint16_t u1, uint16_t u2, uint16_t u3, uint16_t u4, uint16_t u5,
                         uint16_t u6, uint16_t u7);
result_t validate_int8(int8x16_t a, int8_t i0, int8_t i1, int8_t i2, int8_t i3, int8_t i4, int8_t i5, int8_t i6,
                       int8_t i7, int8_t i8, int8_t i9, int8_t i10, int8_t i11, int8_t i12, int8_t i13, int8_t i14,
                       int8_t i15);
result_t validate_uint8(uint8x16_t a, uint8_t u0, uint8_t u1, uint8_t u2, uint8_t u3, uint8_t u4, uint8_t u5,
                        uint8_t u6, uint8_t u7, uint8_t u8, uint8_t u9, uint8_t u10, uint8_t u11, uint8_t u12,
                        uint8_t u13, uint8_t u14, uint8_t u15);
result_t validate_int8(int8x16x2_t a, int8_t i0, int8_t i1, int8_t i2, int8_t i3, int8_t i4, int8_t i5, int8_t i6,
                       int8_t i7, int8_t i8, int8_t i9, int8_t i10, int8_t i11, int8_t i12, int8_t i13, int8_t i14,
                       int8_t i15, int8_t i16, int8_t i17, int8_t i18, int8_t i19, int8_t i20, int8_t i21, int8_t i22,
                       int8_t i23, int8_t i24, int8_t i25, int8_t i26, int8_t i27, int8_t i28, int8_t i29, int8_t i30,
                       int8_t i31);
result_t validate_uint8(uint8x16x2_t u, uint8_t u0, uint8_t u1, uint8_t u2, uint8_t u3, uint8_t u4, uint8_t u5,
                        uint8_t u6, uint8_t u7, uint8_t u8, uint8_t u9, uint8_t u10, uint8_t u11, uint8_t u12,
                        uint8_t u13, uint8_t u14, uint8_t u15, uint8_t u16, uint8_t u17, uint8_t u18, uint8_t u19,
                        uint8_t u20, uint8_t u21, uint8_t u22, uint8_t u23, uint8_t u24, uint8_t u25, uint8_t u26,
                        uint8_t u27, uint8_t u28, uint8_t u29, uint8_t u30, uint8_t u31);
result_t validate_int8(int8x8_t a, int8_t i0, int8_t i1, int8_t i2, int8_t i3, int8_t i4, int8_t i5, int8_t i6,
                       int8_t i7);
result_t validate_uint8(uint8x8_t a, uint8_t u0, uint8_t u1, uint8_t u2, uint8_t u3, uint8_t u4, uint8_t u5, uint8_t u6,
                        uint8_t u7);
result_t validate_int8(int8x8x2_t a, int8_t i0, int8_t i1, int8_t i2, int8_t i3, int8_t i4, int8_t i5, int8_t i6,
                       int8_t i7, int8_t i8, int8_t i9, int8_t i10, int8_t i11, int8_t i12, int8_t i13, int8_t i14,
                       int8_t i15);
result_t validate_uint8(uint8x8x2_t a, uint8_t u0, uint8_t u1, uint8_t u2, uint8_t u3, uint8_t u4, uint8_t u5,
                        uint8_t u6, uint8_t u7, uint8_t u8, uint8_t u9, uint8_t u10, uint8_t u11, uint8_t u12,
                        uint8_t u13, uint8_t u14, uint8_t u15);
result_t validate_float(float32x4_t a, float f0, float f1, float f2, float f3);
result_t validate_float(float32x4x2_t a, float f0, float f1, float f2, float f3, float f4, float f5, float f6,
                        float f7);
result_t validate_float(float32x2_t a, float f0, float f1);
result_t validate_float(float32x2x2_t a, float f0, float f1, float f2, float f3);
result_t validate_float_error(float32x4_t a, float f0, float f1, float f2, float f3, float err);
result_t validate_float_error(float32x2_t a, float f0, float f1, float err);
result_t validate_double(float64x2_t a, double d0, double d1);
result_t validate_double(float64x1_t a, double d0);
result_t validate_double_error(float64x2_t a, double d0, double d1, double err);
result_t validate_double_error(float64x2_t a, double d0, double err);
result_t validate_float_pair(float a, float b);

int8_t saturate_int8(int a);
uint8_t saturate_uint8(int a);
int16_t saturate_int16(int a);
uint16_t saturate_uint16(int a);
int32_t saturate_int32(int64_t a);
uint32_t saturate_uint32(int64_t a);

#if defined(__riscv) || defined(__riscv__)
#define DEFINE_TUPLEx2_GET(TYPE, SIGN, BIT, ELT_NUM)                                                          \
  __attribute__((unused)) static void TYPE##x2_get_##TYPE(TYPE##x##ELT_NUM##x2_t a, TYPE##x##ELT_NUM##_t *a0, \
                                                          TYPE##x##ELT_NUM##_t *a1) {                         \
    *a0 = __riscv_vget_v_##SIGN##BIT##m1x2_##SIGN##BIT##m1(a, 0);                                             \
    *a1 = __riscv_vget_v_##SIGN##BIT##m1x2_##SIGN##BIT##m1(a, 1);                                             \
  }
#define DEFINE_TUPLEx3_GET(TYPE, SIGN, BIT, ELT_NUM)                                                            \
  __attribute__((unused)) static void TYPE##x3_get_##TYPE(TYPE##x##ELT_NUM##x3_t a, TYPE##x##ELT_NUM##_t *a0,   \
                                                          TYPE##x##ELT_NUM##_t *a1, TYPE##x##ELT_NUM##_t *a2) { \
    *a0 = __riscv_vget_v_##SIGN##BIT##m1x3_##SIGN##BIT##m1(a, 0);                                               \
    *a1 = __riscv_vget_v_##SIGN##BIT##m1x3_##SIGN##BIT##m1(a, 1);                                               \
    *a2 = __riscv_vget_v_##SIGN##BIT##m1x3_##SIGN##BIT##m1(a, 2);                                               \
  }
#define DEFINE_TUPLEx4_GET(TYPE, SIGN, BIT, ELT_NUM)                                                          \
  __attribute__((unused)) static void TYPE##x4_get_##TYPE(TYPE##x##ELT_NUM##x4_t a, TYPE##x##ELT_NUM##_t *a0, \
                                                          TYPE##x##ELT_NUM##_t *a1, TYPE##x##ELT_NUM##_t *a2, \
                                                          TYPE##x##ELT_NUM##_t *a3) {                         \
    *a0 = __riscv_vget_v_##SIGN##BIT##m1x4_##SIGN##BIT##m1(a, 0);                                             \
    *a1 = __riscv_vget_v_##SIGN##BIT##m1x4_##SIGN##BIT##m1(a, 1);                                             \
    *a2 = __riscv_vget_v_##SIGN##BIT##m1x4_##SIGN##BIT##m1(a, 2);                                             \
    *a3 = __riscv_vget_v_##SIGN##BIT##m1x4_##SIGN##BIT##m1(a, 3);                                             \
  }
#elif defined(__aarch64__) || defined(_M_ARM64)
#define DEFINE_TUPLEx2_GET(TYPE, SIGN, BIT, ELT_NUM)                                                          \
  __attribute__((unused)) static void TYPE##x2_get_##TYPE(TYPE##x##ELT_NUM##x2_t a, TYPE##x##ELT_NUM##_t *a0, \
                                                          TYPE##x##ELT_NUM##_t *a1) {                         \
    *a0 = a.val[0];                                                                                           \
    *a1 = a.val[1];                                                                                           \
  }
#define DEFINE_TUPLEx3_GET(TYPE, SIGN, BIT, ELT_NUM)                                                            \
  __attribute__((unused)) static void TYPE##x3_get_##TYPE(TYPE##x##ELT_NUM##x3_t a, TYPE##x##ELT_NUM##_t *a0,   \
                                                          TYPE##x##ELT_NUM##_t *a1, TYPE##x##ELT_NUM##_t *a2) { \
    *a0 = a.val[0];                                                                                             \
    *a1 = a.val[1];                                                                                             \
    *a2 = a.val[2];                                                                                             \
  }
#define DEFINE_TUPLEx4_GET(TYPE, SIGN, BIT, ELT_NUM)                                                          \
  __attribute__((unused)) static void TYPE##x4_get_##TYPE(TYPE##x##ELT_NUM##x4_t a, TYPE##x##ELT_NUM##_t *a0, \
                                                          TYPE##x##ELT_NUM##_t *a1, TYPE##x##ELT_NUM##_t *a2, \
                                                          TYPE##x##ELT_NUM##_t *a3) {                         \
    *a0 = a.val[0];                                                                                           \
    *a1 = a.val[1];                                                                                           \
    *a2 = a.val[2];                                                                                           \
    *a3 = a.val[3];                                                                                           \
  }
#endif

DEFINE_TUPLEx2_GET(int8, i, 8, 8);
DEFINE_TUPLEx2_GET(uint8, u, 8, 8);
DEFINE_TUPLEx2_GET(int16, i, 16, 4);
DEFINE_TUPLEx2_GET(uint16, u, 16, 4);
DEFINE_TUPLEx2_GET(int32, i, 32, 2);
DEFINE_TUPLEx2_GET(uint32, u, 32, 2);
DEFINE_TUPLEx2_GET(float32, f, 32, 2);
DEFINE_TUPLEx2_GET(int64, i, 64, 1);
DEFINE_TUPLEx2_GET(uint64, u, 64, 1);
DEFINE_TUPLEx3_GET(int8, i, 8, 8);
DEFINE_TUPLEx3_GET(uint8, u, 8, 8);
DEFINE_TUPLEx3_GET(int16, i, 16, 4);
DEFINE_TUPLEx3_GET(uint16, u, 16, 4);
DEFINE_TUPLEx3_GET(int32, i, 32, 2);
DEFINE_TUPLEx3_GET(uint32, u, 32, 2);
DEFINE_TUPLEx3_GET(float32, f, 32, 2);
DEFINE_TUPLEx3_GET(int64, i, 64, 1);
DEFINE_TUPLEx3_GET(uint64, u, 64, 1);
DEFINE_TUPLEx4_GET(int8, i, 8, 8);
DEFINE_TUPLEx4_GET(uint8, u, 8, 8);
DEFINE_TUPLEx4_GET(int16, i, 16, 4);
DEFINE_TUPLEx4_GET(uint16, u, 16, 4);
DEFINE_TUPLEx4_GET(int32, i, 32, 2);
DEFINE_TUPLEx4_GET(uint32, u, 32, 2);
DEFINE_TUPLEx4_GET(float32, f, 32, 2);
DEFINE_TUPLEx4_GET(int64, i, 64, 1);
DEFINE_TUPLEx4_GET(uint64, u, 64, 1);
#if defined(__aarch64__) || defined(_M_ARM64)
DEFINE_TUPLEx2_GET(int16, i, 16, 8);
DEFINE_TUPLEx2_GET(uint16, u, 16, 8);
DEFINE_TUPLEx2_GET(int32, i, 32, 4);
DEFINE_TUPLEx2_GET(uint32, u, 32, 4);
DEFINE_TUPLEx2_GET(float32, f, 32, 4);
DEFINE_TUPLEx2_GET(int64, i, 64, 2);
DEFINE_TUPLEx2_GET(uint64, u, 64, 2);
DEFINE_TUPLEx3_GET(int16, i, 16, 8);
DEFINE_TUPLEx3_GET(uint16, u, 16, 8);
DEFINE_TUPLEx3_GET(int32, i, 32, 4);
DEFINE_TUPLEx3_GET(uint32, u, 32, 4);
DEFINE_TUPLEx3_GET(float32, f, 32, 4);
DEFINE_TUPLEx3_GET(int64, i, 64, 2);
DEFINE_TUPLEx3_GET(uint64, u, 64, 2);
DEFINE_TUPLEx4_GET(int16, i, 16, 8);
DEFINE_TUPLEx4_GET(uint16, u, 16, 8);
DEFINE_TUPLEx4_GET(int32, i, 32, 4);
DEFINE_TUPLEx4_GET(uint32, u, 32, 4);
DEFINE_TUPLEx4_GET(float32, f, 32, 4);
DEFINE_TUPLEx4_GET(int64, i, 64, 2);
DEFINE_TUPLEx4_GET(uint64, u, 64, 2);
#endif

float ranf(float low, float high);

template <typename T, typename U>
static void merge_arrays(const T *arr1, const T *arr2, U *out, size_t single_arr_size) {
  const U *_arr1 = (const U *)arr1;
  const U *_arr2 = (const U *)arr2;
  for (size_t i = 0; i < single_arr_size; i++) {
    out[i] = _arr1[i];
    out[i + single_arr_size] = _arr2[i];
  }
}
template <typename T, typename U>
static void merge_arrays(const T *arr1, const T *arr2, const T *arr3, U *out, size_t single_arr_size) {
  const U *_arr1 = (const U *)arr1;
  const U *_arr2 = (const U *)arr2;
  const U *_arr3 = (const U *)arr3;
  for (size_t i = 0; i < single_arr_size; i++) {
    out[i] = _arr1[i];
    out[i + single_arr_size] = _arr2[i];
    out[i + single_arr_size * 2] = _arr3[i];
  }
}
template <typename T, typename U>
static void merge_arrays(const T *arr1, const T *arr2, const T *arr3, const T *arr4, U *out, size_t single_arr_size) {
  const U *_arr1 = (const U *)arr1;
  const U *_arr2 = (const U *)arr2;
  const U *_arr3 = (const U *)arr3;
  const U *_arr4 = (const U *)arr4;
  for (size_t i = 0; i < single_arr_size; i++) {
    out[i] = _arr1[i];
    out[i + single_arr_size] = _arr2[i];
    out[i + single_arr_size * 2] = _arr3[i];
    out[i + single_arr_size * 3] = _arr4[i];
  }
}
template <typename T, typename U>
static void merge_arrays(const T *arr1, const T *arr2, const T *arr3, const T *arr4, U *out) {
  size_t len = 128 / (sizeof(U) * 8);
  const U *_arr1 = (const U *)arr1;
  const U *_arr2 = (const U *)arr2;
  const U *_arr3 = (const U *)arr3;
  const U *_arr4 = (const U *)arr4;
  for (size_t i = 0; i < len; i++) {
    out[i] = _arr1[i];
    out[i + len] = _arr2[i];
    out[i + len * 2] = _arr3[i];
    out[i + len * 3] = _arr4[i];
  }
}

#define CHECK_RESULT(EXP)    \
  if (EXP != TEST_SUCCESS) { \
    return TEST_FAIL;        \
  }
#define IMM_1_ITER TEST_IMPL(0)
#define IMM_2_ITER \
  IMM_1_ITER       \
  TEST_IMPL(1)
#define IMM_3_ITER \
  IMM_2_ITER       \
  TEST_IMPL(2)
#define IMM_4_ITER \
  IMM_3_ITER       \
  TEST_IMPL(3)
#define IMM_7_ITER \
  IMM_4_ITER       \
  TEST_IMPL(4)     \
  TEST_IMPL(5)     \
  TEST_IMPL(6)
#define IMM_8_ITER \
  IMM_7_ITER       \
  TEST_IMPL(7)
#define IMM_15_ITER \
  IMM_8_ITER        \
  TEST_IMPL(8)      \
  TEST_IMPL(9)      \
  TEST_IMPL(10)     \
  TEST_IMPL(11)     \
  TEST_IMPL(12)     \
  TEST_IMPL(13)     \
  TEST_IMPL(14)
#define IMM_16_ITER \
  IMM_15_ITER       \
  TEST_IMPL(15)
#define IMM_31_ITER \
  IMM_16_ITER       \
  TEST_IMPL(16)     \
  TEST_IMPL(17)     \
  TEST_IMPL(18)     \
  TEST_IMPL(19)     \
  TEST_IMPL(20)     \
  TEST_IMPL(21)     \
  TEST_IMPL(22)     \
  TEST_IMPL(23)     \
  TEST_IMPL(24)     \
  TEST_IMPL(25)     \
  TEST_IMPL(26)     \
  TEST_IMPL(27)     \
  TEST_IMPL(28)     \
  TEST_IMPL(29)     \
  TEST_IMPL(30)
#define IMM_32_ITER \
  IMM_31_ITER       \
  TEST_IMPL(31)
#define IMM_63_ITER \
  IMM_32_ITER       \
  TEST_IMPL(32)     \
  TEST_IMPL(33)     \
  TEST_IMPL(34)     \
  TEST_IMPL(35)     \
  TEST_IMPL(36)     \
  TEST_IMPL(37)     \
  TEST_IMPL(38)     \
  TEST_IMPL(39)     \
  TEST_IMPL(40)     \
  TEST_IMPL(41)     \
  TEST_IMPL(42)     \
  TEST_IMPL(43)     \
  TEST_IMPL(44)     \
  TEST_IMPL(45)     \
  TEST_IMPL(46)     \
  TEST_IMPL(47)     \
  TEST_IMPL(48)     \
  TEST_IMPL(49)     \
  TEST_IMPL(50)     \
  TEST_IMPL(51)     \
  TEST_IMPL(52)     \
  TEST_IMPL(53)     \
  TEST_IMPL(54)     \
  TEST_IMPL(55)     \
  TEST_IMPL(56)     \
  TEST_IMPL(57)     \
  TEST_IMPL(58)     \
  TEST_IMPL(59)     \
  TEST_IMPL(60)     \
  TEST_IMPL(61)     \
  TEST_IMPL(62)
#define IMM_64_ITER \
  IMM_63_ITER       \
  TEST_IMPL(63)
#define IMM_127_ITER \
  IMM_64_ITER        \
  TEST_IMPL(64)      \
  TEST_IMPL(65)      \
  TEST_IMPL(66)      \
  TEST_IMPL(67)      \
  TEST_IMPL(68)      \
  TEST_IMPL(69)      \
  TEST_IMPL(70)      \
  TEST_IMPL(71)      \
  TEST_IMPL(72)      \
  TEST_IMPL(73)      \
  TEST_IMPL(74)      \
  TEST_IMPL(75)      \
  TEST_IMPL(76)      \
  TEST_IMPL(77)      \
  TEST_IMPL(78)      \
  TEST_IMPL(79)      \
  TEST_IMPL(80)      \
  TEST_IMPL(81)      \
  TEST_IMPL(82)      \
  TEST_IMPL(83)      \
  TEST_IMPL(84)      \
  TEST_IMPL(85)      \
  TEST_IMPL(86)      \
  TEST_IMPL(87)      \
  TEST_IMPL(88)      \
  TEST_IMPL(89)      \
  TEST_IMPL(90)      \
  TEST_IMPL(91)      \
  TEST_IMPL(92)      \
  TEST_IMPL(93)      \
  TEST_IMPL(94)      \
  TEST_IMPL(95)      \
  TEST_IMPL(96)      \
  TEST_IMPL(97)      \
  TEST_IMPL(98)      \
  TEST_IMPL(99)      \
  TEST_IMPL(100)     \
  TEST_IMPL(101)     \
  TEST_IMPL(102)     \
  TEST_IMPL(103)     \
  TEST_IMPL(104)     \
  TEST_IMPL(105)     \
  TEST_IMPL(106)     \
  TEST_IMPL(107)     \
  TEST_IMPL(108)     \
  TEST_IMPL(109)     \
  TEST_IMPL(110)     \
  TEST_IMPL(111)     \
  TEST_IMPL(112)     \
  TEST_IMPL(113)     \
  TEST_IMPL(114)     \
  TEST_IMPL(115)     \
  TEST_IMPL(116)     \
  TEST_IMPL(117)     \
  TEST_IMPL(118)     \
  TEST_IMPL(119)     \
  TEST_IMPL(120)     \
  TEST_IMPL(121)     \
  TEST_IMPL(122)     \
  TEST_IMPL(123)     \
  TEST_IMPL(124)     \
  TEST_IMPL(125)     \
  TEST_IMPL(126)
#define IMM_128_ITER \
  IMM_127_ITER       \
  TEST_IMPL(127)
#define IMM_255_ITER \
  IMM_128_ITER       \
  TEST_IMPL(128)     \
  TEST_IMPL(129)     \
  TEST_IMPL(130)     \
  TEST_IMPL(131)     \
  TEST_IMPL(132)     \
  TEST_IMPL(133)     \
  TEST_IMPL(134)     \
  TEST_IMPL(135)     \
  TEST_IMPL(136)     \
  TEST_IMPL(137)     \
  TEST_IMPL(138)     \
  TEST_IMPL(139)     \
  TEST_IMPL(140)     \
  TEST_IMPL(141)     \
  TEST_IMPL(142)     \
  TEST_IMPL(143)     \
  TEST_IMPL(144)     \
  TEST_IMPL(145)     \
  TEST_IMPL(146)     \
  TEST_IMPL(147)     \
  TEST_IMPL(148)     \
  TEST_IMPL(149)     \
  TEST_IMPL(150)     \
  TEST_IMPL(151)     \
  TEST_IMPL(152)     \
  TEST_IMPL(153)     \
  TEST_IMPL(154)     \
  TEST_IMPL(155)     \
  TEST_IMPL(156)     \
  TEST_IMPL(157)     \
  TEST_IMPL(158)     \
  TEST_IMPL(159)     \
  TEST_IMPL(160)     \
  TEST_IMPL(161)     \
  TEST_IMPL(162)     \
  TEST_IMPL(163)     \
  TEST_IMPL(164)     \
  TEST_IMPL(165)     \
  TEST_IMPL(166)     \
  TEST_IMPL(167)     \
  TEST_IMPL(168)     \
  TEST_IMPL(169)     \
  TEST_IMPL(170)     \
  TEST_IMPL(171)     \
  TEST_IMPL(172)     \
  TEST_IMPL(173)     \
  TEST_IMPL(174)     \
  TEST_IMPL(175)     \
  TEST_IMPL(176)     \
  TEST_IMPL(177)     \
  TEST_IMPL(178)     \
  TEST_IMPL(179)     \
  TEST_IMPL(180)     \
  TEST_IMPL(181)     \
  TEST_IMPL(182)     \
  TEST_IMPL(183)     \
  TEST_IMPL(184)     \
  TEST_IMPL(185)     \
  TEST_IMPL(186)     \
  TEST_IMPL(187)     \
  TEST_IMPL(188)     \
  TEST_IMPL(189)     \
  TEST_IMPL(190)     \
  TEST_IMPL(191)     \
  TEST_IMPL(192)     \
  TEST_IMPL(193)     \
  TEST_IMPL(194)     \
  TEST_IMPL(195)     \
  TEST_IMPL(196)     \
  TEST_IMPL(197)     \
  TEST_IMPL(198)     \
  TEST_IMPL(199)     \
  TEST_IMPL(200)     \
  TEST_IMPL(201)     \
  TEST_IMPL(202)     \
  TEST_IMPL(203)     \
  TEST_IMPL(204)     \
  TEST_IMPL(205)     \
  TEST_IMPL(206)     \
  TEST_IMPL(207)     \
  TEST_IMPL(208)     \
  TEST_IMPL(209)     \
  TEST_IMPL(210)     \
  TEST_IMPL(211)     \
  TEST_IMPL(212)     \
  TEST_IMPL(213)     \
  TEST_IMPL(214)     \
  TEST_IMPL(215)     \
  TEST_IMPL(216)     \
  TEST_IMPL(217)     \
  TEST_IMPL(218)     \
  TEST_IMPL(219)     \
  TEST_IMPL(220)     \
  TEST_IMPL(221)     \
  TEST_IMPL(222)     \
  TEST_IMPL(223)     \
  TEST_IMPL(224)     \
  TEST_IMPL(225)     \
  TEST_IMPL(226)     \
  TEST_IMPL(227)     \
  TEST_IMPL(228)     \
  TEST_IMPL(229)     \
  TEST_IMPL(230)     \
  TEST_IMPL(231)     \
  TEST_IMPL(232)     \
  TEST_IMPL(233)     \
  TEST_IMPL(234)     \
  TEST_IMPL(235)     \
  TEST_IMPL(236)     \
  TEST_IMPL(237)     \
  TEST_IMPL(238)     \
  TEST_IMPL(239)     \
  TEST_IMPL(240)     \
  TEST_IMPL(241)     \
  TEST_IMPL(242)     \
  TEST_IMPL(243)     \
  TEST_IMPL(244)     \
  TEST_IMPL(245)     \
  TEST_IMPL(246)     \
  TEST_IMPL(247)     \
  TEST_IMPL(248)     \
  TEST_IMPL(249)     \
  TEST_IMPL(250)     \
  TEST_IMPL(251)     \
  TEST_IMPL(252)     \
  TEST_IMPL(253)     \
  TEST_IMPL(254)
#define IMM_256_ITER \
  IMM_255_ITER       \
  TEST_IMPL(255)

}  // namespace NEON2RVV

#endif  // NEON2RVV_COMMON_H
