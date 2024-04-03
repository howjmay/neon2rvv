#ifndef NEON2RVV_DEBUG_TOOLS_H
#define NEON2RVV_DEBUG_TOOLS_H

#include <stdio.h>
#include <cstdint>

#if defined(__riscv) || defined(__riscv__)
#include "neon2rvv.h"
#elif (defined(__aarch64__) || defined(_M_ARM64)) || defined(__arm__)
#include <arm_neon.h>
#endif

namespace NEON2RVV {

void print_64_bits_u8_arr(const char *var_name, const uint8_t *u);
void print_64_bits_s8_arr(const char *var_name, const int8_t *u);
void print_64_bits_u16_arr(const char *var_name, const uint16_t *u);
void print_64_bits_s16_arr(const char *var_name, const int16_t *u);
void print_64_bits_u32_arr(const char *var_name, const uint32_t *u);
void print_64_bits_s32_arr(const char *var_name, const int32_t *u);
void print_64_bits_u64_arr(const char *var_name, const uint64_t *u);
void print_64_bits_s64_arr(const char *var_name, const int64_t *u);
void print_64_bits_f32_arr(const char *var_name, const float *f);
void print_64_bits_f64_arr(const char *var_name, const double *f);
void print_128_bits_u8_arr(const char *var_name, const uint8_t *u);
void print_128_bits_s8_arr(const char *var_name, const int8_t *u);
void print_128_bits_u16_arr(const char *var_name, const uint16_t *u);
void print_128_bits_s16_arr(const char *var_name, const int16_t *u);
void print_128_bits_u32_arr(const char *var_name, const uint32_t *u);
void print_128_bits_s32_arr(const char *var_name, const int32_t *u);
void print_128_bits_u64_arr(const char *var_name, const uint64_t *u);
void print_128_bits_s64_arr(const char *var_name, const int64_t *u);
void print_128_bits_f32_arr(const char *var_name, const float *f);
void print_128_bits_f64_arr(const char *var_name, const double *f);

void print_u8_64(const char *var_name, uint8_t u0, uint8_t u1, uint8_t u2, uint8_t u3, uint8_t u4, uint8_t u5,
                 uint8_t u6, uint8_t u7);
void print_u8_64(const char *var_name, int8_t i0, int8_t i1, int8_t i2, int8_t i3, int8_t i4, int8_t i5, int8_t i6,
                 int8_t i7);
void print_u8_64(const char *var_name, uint16_t u0, uint16_t u1, uint16_t u2, uint16_t u3);
void print_u8_64(const char *var_name, int16_t i0, int16_t i1, int16_t i2, int16_t i3);
void print_u8_64(const char *var_name, uint32_t u0, uint32_t u1);
void print_u8_64(const char *var_name, int32_t i0, int32_t i1);
void print_u8_64(const char *var_name, uint64_t u0);
void print_u8_64(const char *var_name, int64_t i0);

void print_u8_128(const char *var_name, uint8_t u0, uint8_t u1, uint8_t u2, uint8_t u3, uint8_t u4, uint8_t u5,
                  uint8_t u6, uint8_t u7, uint8_t u8, uint8_t u9, uint8_t u10, uint8_t u11, uint8_t u12, uint8_t u13,
                  uint8_t u14, uint8_t u15);
void print_u8_128(const char *var_name, int8_t i0, int8_t i1, int8_t i2, int8_t i3, int8_t i4, int8_t i5, int8_t i6,
                  int8_t i7, int8_t i8, int8_t i9, int8_t i10, int8_t i11, int8_t i12, int8_t i13, int8_t i14,
                  int8_t i15);
void print_u8_128(const char *var_name, uint16_t u0, uint16_t u1, uint16_t u2, uint16_t u3, uint16_t u4, uint16_t u5,
                  uint16_t u6, uint16_t u7);
void print_u8_128(const char *var_name, int16_t i0, int16_t i1, int16_t i2, int16_t i3, int16_t i4, int16_t i5,
                  int16_t i6, int16_t i7);
void print_u8_128(const char *var_name, uint32_t u0, uint32_t u1, uint32_t u2, uint32_t u3);
void print_u8_128(const char *var_name, int32_t i0, int32_t i1, int32_t i2, int32_t i3);
void print_u8_128(const char *var_name, uint64_t u0, uint64_t u1);
void print_u8_128(const char *var_name, int64_t i0, int64_t i1);

template <typename T>
void print_u8_64(const char *var_name, T a) {
  const uint8_t *u = (const uint8_t *)&a;
  print_64_bits_u8_arr(var_name, u);
}
template <typename T>
void print_u8_64(const char *var_name, T *a) {
  const uint8_t *u = (const uint8_t *)a;
  print_64_bits_u8_arr(var_name, u);
}
template <typename T>
void print_s8_64(const char *var_name, T a) {
  const int8_t *s = (const int8_t *)&a;
  print_64_bits_s8_arr(var_name, s);
}
template <typename T>
void print_s8_64(const char *var_name, T *a) {
  const int8_t *s = (const int8_t *)a;
  print_64_bits_s8_arr(var_name, s);
}
template <typename T>
void print_u16_64(const char *var_name, T a) {
  const uint16_t *u = (const uint16_t *)&a;
  print_64_bits_u16_arr(var_name, u);
}
template <typename T>
void print_u16_64(const char *var_name, T *a) {
  const uint16_t *u = (const uint16_t *)a;
  print_64_bits_u16_arr(var_name, u);
}
template <typename T>
void print_s16_64(const char *var_name, T a) {
  const int16_t *s = (const int16_t *)&a;
  print_64_bits_s16_arr(var_name, s);
}
template <typename T>
void print_s16_64(const char *var_name, T *a) {
  const int16_t *s = (const int16_t *)a;
  print_64_bits_s16_arr(var_name, s);
}
template <typename T>
void print_u32_64(const char *var_name, T a) {
  const uint32_t *u = (const uint32_t *)&a;
  print_64_bits_u32_arr(var_name, u);
}
template <typename T>
void print_u32_64(const char *var_name, T *a) {
  const uint32_t *u = (const uint32_t *)a;
  print_64_bits_u32_arr(var_name, u);
}
template <typename T>
void print_s32_64(const char *var_name, T a) {
  const int32_t *s = (const int32_t *)&a;
  print_64_bits_s32_arr(var_name, s);
}
template <typename T>
void print_s32_64(const char *var_name, T *a) {
  const int32_t *s = (const int32_t *)a;
  print_64_bits_s32_arr(var_name, s);
}
template <typename T>
void print_u64_64(const char *var_name, T a) {
  const uint64_t *u = (const uint64_t *)&a;
  print_64_bits_u64_arr(var_name, u);
}
template <typename T>
void print_u64_64(const char *var_name, T *a) {
  const uint64_t *u = (const uint64_t *)a;
  print_64_bits_u64_arr(var_name, u);
}
template <typename T>
void print_s64_64(const char *var_name, T a) {
  const int64_t *s = (const int64_t *)&a;
  print_64_bits_s64_arr(var_name, s);
}
template <typename T>
void print_s64_64(const char *var_name, T *a) {
  const int64_t *s = (const int64_t *)a;
  print_64_bits_s64_arr(var_name, s);
}
template <typename T>
void print_f32_64(const char *var_name, T a) {
  const float *f = (const float *)&a;
  print_64_bits_f32_arr(var_name, f);
}
template <typename T>
void print_f32_64(const char *var_name, T *a) {
  const float *f = (const float *)a;
  print_64_bits_f32_arr(var_name, f);
}
template <typename T>
void print_f64_64(const char *var_name, T a) {
  const double *f = (const double *)&a;
  print_64_bits_f64_arr(var_name, f);
}
template <typename T>
void print_f64_64(const char *var_name, T *a) {
  const double *f = (const double *)a;
  print_64_bits_f64_arr(var_name, f);
}
template <typename T>
void print_u8_128(const char *var_name, T a) {
  const uint8_t *u = (const uint8_t *)&a;
  print_128_bits_u8_arr(var_name, u);
}
template <typename T>
void print_u8_128(const char *var_name, T *a) {
  const uint8_t *u = (const uint8_t *)a;
  print_128_bits_u8_arr(var_name, u);
}
template <typename T>
void print_s8_128(const char *var_name, T a) {
  const int8_t *u = (const int8_t *)&a;
  print_128_bits_s8_arr(var_name, u);
}
template <typename T>
void print_s8_128(const char *var_name, T *a) {
  const int8_t *u = (const int8_t *)a;
  print_128_bits_s8_arr(var_name, u);
}
template <typename T>
void print_u16_128(const char *var_name, T a) {
  const uint16_t *u = (const uint16_t *)&a;
  print_128_bits_u16_arr(var_name, u);
}
template <typename T>
void print_u16_128(const char *var_name, T *a) {
  const uint16_t *u = (const uint16_t *)a;
  print_128_bits_u16_arr(var_name, u);
}
template <typename T>
void print_s16_128(const char *var_name, T a) {
  const int16_t *u = (const int16_t *)&a;
  print_128_bits_s16_arr(var_name, u);
}
template <typename T>
void print_s16_128(const char *var_name, T *a) {
  const int16_t *u = (const int16_t *)a;
  print_128_bits_s16_arr(var_name, u);
}
template <typename T>
void print_u32_128(const char *var_name, T a) {
  const uint32_t *u = (const uint32_t *)&a;
  print_128_bits_u32_arr(var_name, u);
}
template <typename T>
void print_u32_128(const char *var_name, T *a) {
  const uint32_t *u = (const uint32_t *)a;
  print_128_bits_u32_arr(var_name, u);
}
template <typename T>
void print_s32_128(const char *var_name, T a) {
  const int32_t *u = (const int32_t *)&a;
  print_128_bits_s32_arr(var_name, u);
}
template <typename T>
void print_s32_128(const char *var_name, T *a) {
  const int32_t *u = (const int32_t *)a;
  print_128_bits_s32_arr(var_name, u);
}
template <typename T>
void print_u64_128(const char *var_name, T a) {
  const uint64_t *u = (const uint64_t *)&a;
  print_128_bits_u64_arr(var_name, u);
}
template <typename T>
void print_u64_128(const char *var_name, T *a) {
  const uint64_t *u = (const uint64_t *)a;
  print_128_bits_u64_arr(var_name, u);
}
template <typename T>
void print_s64_128(const char *var_name, T a) {
  const int64_t *u = (const int64_t *)&a;
  print_128_bits_s64_arr(var_name, u);
}
template <typename T>
void print_s64_128(const char *var_name, T *a) {
  const int64_t *u = (const int64_t *)a;
  print_128_bits_s64_arr(var_name, u);
}
template <typename T>
void print_f32_128(const char *var_name, T a) {
  const float *f = (const float *)&a;
  print_128_bits_f32_arr(var_name, f);
}
template <typename T>
void print_f32_128(const char *var_name, T *a) {
  const float *f = (const float *)a;
  print_128_bits_f32_arr(var_name, f);
}
template <typename T>
void print_f64_128(const char *var_name, T a) {
  const double *f = (const double *)&a;
  print_128_bits_f64_arr(var_name, f);
}
template <typename T>
void print_f64_128(const char *var_name, T *a) {
  const double *f = (const double *)a;
  print_128_bits_f64_arr(var_name, f);
}

}  // namespace NEON2RVV

#endif  // NEON2RVV_DEBUG_TOOLS_H
