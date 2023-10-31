#include "common.h"
#include <cmath>
#include <cstdint>

namespace NEON2RVV {
int32_t NaN = ~0;
int64_t NaN64 = ~0;

result_t validate_int64(int64x2_t a, int64_t i0, int64_t i1) {
  const int64_t *t = (const int64_t *)&a;
  ASSERT_RETURN(t[0] == i0);
  ASSERT_RETURN(t[1] == i1);
  return TEST_SUCCESS;
}

result_t validate_uint64(uint64x2_t a, uint64_t i0, uint64_t i1) {
  const uint64_t *t = (const uint64_t *)&a;
  ASSERT_RETURN(t[0] == i0);
  ASSERT_RETURN(t[1] == i1);
  return TEST_SUCCESS;
}

result_t validate_int64(int64x1_t a, int64_t i0) {
  const int64_t *t = (const int64_t *)&a;
  ASSERT_RETURN(t[0] == i0);
  return TEST_SUCCESS;
}

result_t validate_uint64(uint64x1_t a, uint64_t i0) {
  const uint64_t *t = (const uint64_t *)&a;
  ASSERT_RETURN(t[0] == i0);
  return TEST_SUCCESS;
}

result_t validate_int32(int32x4_t a, int32_t i0, int32_t i1, int32_t i2, int32_t i3) {
  const int32_t *t = (const int32_t *)&a;
  ASSERT_RETURN(t[0] == i0);
  ASSERT_RETURN(t[1] == i1);
  ASSERT_RETURN(t[2] == i2);
  ASSERT_RETURN(t[3] == i3);
  return TEST_SUCCESS;
}

result_t validate_uint32(uint32x4_t a, uint32_t u0, uint32_t u1, uint32_t u2, uint32_t u3) {
  const uint32_t *t = (const uint32_t *)&a;
  ASSERT_RETURN(t[0] == u0);
  ASSERT_RETURN(t[1] == u1);
  ASSERT_RETURN(t[2] == u2);
  ASSERT_RETURN(t[3] == u3);
  return TEST_SUCCESS;
}

result_t validate_int32(int32x2_t a, int32_t u0, int32_t u1) {
  const int32_t *t = (const int32_t *)&a;
  ASSERT_RETURN(t[0] == u0);
  ASSERT_RETURN(t[1] == u1);
  return TEST_SUCCESS;
}

result_t validate_uint32(uint32x2_t a, uint32_t u0, uint32_t u1) {
  const uint32_t *t = (const uint32_t *)&a;
  ASSERT_RETURN(t[0] == u0);
  ASSERT_RETURN(t[1] == u1);
  return TEST_SUCCESS;
}

result_t validate_int16(int16x8_t a, int16_t i0, int16_t i1, int16_t i2, int16_t i3, int16_t i4, int16_t i5, int16_t i6,
                        int16_t i7) {
  const int16_t *t = (const int16_t *)&a;
  ASSERT_RETURN(t[0] == i0);
  ASSERT_RETURN(t[1] == i1);
  ASSERT_RETURN(t[2] == i2);
  ASSERT_RETURN(t[3] == i3);
  ASSERT_RETURN(t[4] == i4);
  ASSERT_RETURN(t[5] == i5);
  ASSERT_RETURN(t[6] == i6);
  ASSERT_RETURN(t[7] == i7);
  return TEST_SUCCESS;
}

result_t validate_uint16(uint16x8_t a, uint16_t u0, uint16_t u1, uint16_t u2, uint16_t u3, uint16_t u4, uint16_t u5,
                         uint16_t u6, uint16_t u7) {
  const uint16_t *t = (const uint16_t *)&a;
  ASSERT_RETURN(t[0] == u0);
  ASSERT_RETURN(t[1] == u1);
  ASSERT_RETURN(t[2] == u2);
  ASSERT_RETURN(t[3] == u3);
  ASSERT_RETURN(t[4] == u4);
  ASSERT_RETURN(t[5] == u5);
  ASSERT_RETURN(t[6] == u6);
  ASSERT_RETURN(t[7] == u7);
  return TEST_SUCCESS;
}

result_t validate_int16(int16x4_t a, int16_t i0, int16_t i1, int16_t i2, int16_t i3) {
  const int16_t *t = (const int16_t *)&a;
  ASSERT_RETURN(t[0] == i0);
  ASSERT_RETURN(t[1] == i1);
  ASSERT_RETURN(t[2] == i2);
  ASSERT_RETURN(t[3] == i3);
  return TEST_SUCCESS;
}

result_t validate_uint16(uint16x4_t a, uint16_t u0, uint16_t u1, uint16_t u2, uint16_t u3) {
  const uint16_t *t = (const uint16_t *)&a;
  ASSERT_RETURN(t[0] == u0);
  ASSERT_RETURN(t[1] == u1);
  ASSERT_RETURN(t[2] == u2);
  ASSERT_RETURN(t[3] == u3);
  return TEST_SUCCESS;
}

result_t validate_int8(int8x16_t a, int8_t i0, int8_t i1, int8_t i2, int8_t i3, int8_t i4, int8_t i5, int8_t i6,
                       int8_t i7, int8_t i8, int8_t i9, int8_t i10, int8_t i11, int8_t i12, int8_t i13, int8_t i14,
                       int8_t i15) {
  const int8_t *t = (const int8_t *)&a;
  ASSERT_RETURN(t[0] == i0);
  ASSERT_RETURN(t[1] == i1);
  ASSERT_RETURN(t[2] == i2);
  ASSERT_RETURN(t[3] == i3);
  ASSERT_RETURN(t[4] == i4);
  ASSERT_RETURN(t[5] == i5);
  ASSERT_RETURN(t[6] == i6);
  ASSERT_RETURN(t[7] == i7);
  ASSERT_RETURN(t[8] == i8);
  ASSERT_RETURN(t[9] == i9);
  ASSERT_RETURN(t[10] == i10);
  ASSERT_RETURN(t[11] == i11);
  ASSERT_RETURN(t[12] == i12);
  ASSERT_RETURN(t[13] == i13);
  ASSERT_RETURN(t[14] == i14);
  ASSERT_RETURN(t[15] == i15);
  return TEST_SUCCESS;
}

result_t validate_uint8(uint8x16_t a, uint8_t u0, uint8_t u1, uint8_t u2, uint8_t u3, uint8_t u4, uint8_t u5,
                        uint8_t u6, uint8_t u7, uint8_t u8, uint8_t u9, uint8_t u10, uint8_t u11, uint8_t u12,
                        uint8_t u13, uint8_t u14, uint8_t u15) {
  const uint8_t *t = (const uint8_t *)&a;
  ASSERT_RETURN(t[0] == u0);
  ASSERT_RETURN(t[1] == u1);
  ASSERT_RETURN(t[2] == u2);
  ASSERT_RETURN(t[3] == u3);
  ASSERT_RETURN(t[4] == u4);
  ASSERT_RETURN(t[5] == u5);
  ASSERT_RETURN(t[6] == u6);
  ASSERT_RETURN(t[7] == u7);
  ASSERT_RETURN(t[8] == u8);
  ASSERT_RETURN(t[9] == u9);
  ASSERT_RETURN(t[10] == u10);
  ASSERT_RETURN(t[11] == u11);
  ASSERT_RETURN(t[12] == u12);
  ASSERT_RETURN(t[13] == u13);
  ASSERT_RETURN(t[14] == u14);
  ASSERT_RETURN(t[15] == u15);
  return TEST_SUCCESS;
}

result_t validate_int8(int8x8_t a, int8_t i0, int8_t i1, int8_t i2, int8_t i3, int8_t i4, int8_t i5, int8_t i6,
                       int8_t i7) {
  const int8_t *t = (const int8_t *)&a;
  ASSERT_RETURN(t[0] == i0);
  ASSERT_RETURN(t[1] == i1);
  ASSERT_RETURN(t[2] == i2);
  ASSERT_RETURN(t[3] == i3);
  ASSERT_RETURN(t[4] == i4);
  ASSERT_RETURN(t[5] == i5);
  ASSERT_RETURN(t[6] == i6);
  ASSERT_RETURN(t[7] == i7);
  return TEST_SUCCESS;
}

result_t validate_uint8(uint8x8_t a, uint8_t u0, uint8_t u1, uint8_t u2, uint8_t u3, uint8_t u4, uint8_t u5, uint8_t u6,
                        uint8_t u7) {
  const uint8_t *t = (const uint8_t *)&a;
  ASSERT_RETURN(t[0] == u0);
  ASSERT_RETURN(t[1] == u1);
  ASSERT_RETURN(t[2] == u2);
  ASSERT_RETURN(t[3] == u3);
  ASSERT_RETURN(t[4] == u4);
  ASSERT_RETURN(t[5] == u5);
  ASSERT_RETURN(t[6] == u6);
  ASSERT_RETURN(t[7] == u7);
  return TEST_SUCCESS;
}

result_t validate_float_pair(float a, float b) {
  const uint32_t *ua = (const uint32_t *)&a;
  const uint32_t *ub = (const uint32_t *)&b;
  // We do an integer (binary) compare rather than a
  // floating point compare to take NaNs and infinities
  // into account as well.
  return (*ua) == (*ub) ? TEST_SUCCESS : TEST_FAIL;
}

result_t validate_double_pair(double a, double b) {
  const uint64_t *ua = (const uint64_t *)&a;
  const uint64_t *ub = (const uint64_t *)&b;
  // We do an integer (binary) compare rather than a
  // floating point compare to take NaNs and infinities
  // into account as well.

  if (std::isnan(a) && std::isnan(b)) {
    return TEST_SUCCESS;
  }

  return (*ua) == (*ub) ? TEST_SUCCESS : TEST_FAIL;
}

result_t validate_float(float32x2_t a, float f0, float f1) {
  const float *t = (const float *)&a;
  ASSERT_RETURN(validate_float_pair(t[0], f0));
  ASSERT_RETURN(validate_float_pair(t[1], f1));
  return TEST_SUCCESS;
}

result_t validate_float(float32x4_t a, float f0, float f1, float f2, float f3) {
  const float *t = (const float *)&a;
  ASSERT_RETURN(validate_float_pair(t[0], f0));
  ASSERT_RETURN(validate_float_pair(t[1], f1));
  ASSERT_RETURN(validate_float_pair(t[2], f2));
  ASSERT_RETURN(validate_float_pair(t[3], f3));
  return TEST_SUCCESS;
}

result_t validate_float_epsilon(float32x4_t a, float f0, float f1, float f2, float f3, float epsilon) {
  const float *t = (const float *)&a;
  float df0 = fabsf(t[0] - f0);
  float df1 = fabsf(t[1] - f1);
  float df2 = fabsf(t[2] - f2);
  float df3 = fabsf(t[3] - f3);

  // Due to floating-point error, subtracting floating-point number with NaN
  // and zero value usually produces erroneous result. Therefore, we directly
  // define the difference of two floating-point numbers to zero if both
  // numbers are NaN or zero.
  if ((std::isnan(t[0]) && std::isnan(f0)) || (t[0] == 0 && f0 == 0)) {
    df0 = 0;
  }

  if ((std::isnan(t[1]) && std::isnan(f1)) || (t[1] == 0 && f1 == 0)) {
    df1 = 0;
  }

  if ((std::isnan(t[2]) && std::isnan(f2)) || (t[2] == 0 && f2 == 0)) {
    df2 = 0;
  }

  if ((std::isnan(t[3]) && std::isnan(f3)) || (t[3] == 0 && f3 == 0)) {
    df3 = 0;
  }

  ASSERT_RETURN(df0 < epsilon);
  ASSERT_RETURN(df1 < epsilon);
  ASSERT_RETURN(df2 < epsilon);
  ASSERT_RETURN(df3 < epsilon);
  return TEST_SUCCESS;
}

result_t validate_float_error(float32x4_t a, float f0, float f1, float f2, float f3, float err) {
  const float *t = (const float *)&a;
  float df0 = fabsf((t[0] - f0) / f0);
  float df1 = fabsf((t[1] - f1) / f1);
  float df2 = fabsf((t[2] - f2) / f2);
  float df3 = fabsf((t[3] - f3) / f3);

  if ((std::isnan(t[0]) && std::isnan(f0)) || (t[0] == 0 && f0 == 0) || (std::isinf(t[0]) && std::isinf(f0))) {
    df0 = 0;
  }

  if ((std::isnan(t[1]) && std::isnan(f1)) || (t[1] == 0 && f1 == 0) || (std::isinf(t[1]) && std::isinf(f1))) {
    df1 = 0;
  }

  if ((std::isnan(t[2]) && std::isnan(f2)) || (t[2] == 0 && f2 == 0) || (std::isinf(t[2]) && std::isinf(f2))) {
    df2 = 0;
  }

  if ((std::isnan(t[3]) && std::isnan(f3)) || (t[3] == 0 && f3 == 0) || (std::isinf(t[3]) && std::isinf(f3))) {
    df3 = 0;
  }

  ASSERT_RETURN(df0 < err);
  ASSERT_RETURN(df1 < err);
  ASSERT_RETURN(df2 < err);
  ASSERT_RETURN(df3 < err);
  return TEST_SUCCESS;
}

result_t validate_double(float64x2_t a, double d0, double d1) {
  const double *t = (const double *)&a;
  ASSERT_RETURN(validate_float_pair(t[0], d0));
  ASSERT_RETURN(validate_float_pair(t[1], d1));
  return TEST_SUCCESS;
}

result_t validate_float_error(float64x2_t a, double d0, double d1, double err) {
  const double *t = (const double *)&a;
  double td0 = fabs((t[0] - d0) / d0);
  double td1 = fabs((t[1] - d1) / d1);

  if (std::isnan(t[0]) && std::isnan(d0)) {
    td0 = 0;
  }

  if (std::isnan(t[1]) && std::isnan(d1)) {
    td1 = 0;
  }

  ASSERT_RETURN(td0 < err);
  ASSERT_RETURN(td1 < err);
  return TEST_SUCCESS;
}

void print_64_bits_u8_arr(char *var_name, const uint8_t *u) {
  printf("%s0: %3u, %s1: %3u, %s2: %3u, %s3: %3u, %s4: %3u, %s5: %3u, %s6: %3u, %s7: %3u\n", var_name, u[0], var_name,
         u[1], var_name, u[2], var_name, u[3], var_name, u[4], var_name, u[5], var_name, u[6], var_name, u[7]);
}
void print_128_bits_u8_arr(char *var_name, const uint8_t *u) {
  printf(
      "%s0: %3u, %s1: %3u, %s2: %3u, %s3: %3u, %s4: %3u, %s5: %3u, %s6: %3u, %s7: %3u, %s8: %3u, %s9: %3u, %s10: %3u, "
      "%s11: %3u, "
      "%s12: %3u, %s13: "
      "%3u, %s14: %3u, %s15: %3u\n",
      var_name, u[0], var_name, u[1], var_name, u[2], var_name, u[3], var_name, u[4], var_name, u[5], var_name, u[6],
      var_name, u[7], var_name, u[8], var_name, u[9], var_name, u[10], var_name, u[11], var_name, u[12], var_name,
      u[13], var_name, u[14], var_name, u[15]);
}

void print_64_bits_in_u8(char *var_name, uint8_t u0, uint8_t u1, uint8_t u2, uint8_t u3, uint8_t u4, uint8_t u5,
                         uint8_t u6, uint8_t u7) {
  uint8_t a[] = {u0, u1, u2, u3, u4, u5, u6, u7};
  const uint8_t *u = (const uint8_t *)&a;
  print_64_bits_u8_arr(var_name, u);
}
void print_64_bits_in_u8(char *var_name, int8_t i0, int8_t i1, int8_t i2, int8_t i3, int8_t i4, int8_t i5, int8_t i6,
                         int8_t i7) {
  int8_t a[] = {i0, i1, i2, i3, i4, i5, i6, i7};
  const uint8_t *u = (const uint8_t *)&a;
  print_64_bits_u8_arr(var_name, u);
}
void print_64_bits_in_u8(char *var_name, uint16_t u0, uint16_t u1, uint16_t u2, uint16_t u3) {
  uint16_t a[] = {u0, u1, u2, u3};
  const uint8_t *u = (const uint8_t *)&a;
  print_64_bits_u8_arr(var_name, u);
}
void print_64_bits_in_u8(char *var_name, int16_t i0, int16_t i1, int16_t i2, int16_t i3) {
  int16_t a[] = {i0, i1, i2, i3};
  const uint8_t *u = (const uint8_t *)&a;
  print_64_bits_u8_arr(var_name, u);
}
void print_64_bits_in_u8(char *var_name, uint32_t u0, uint32_t u1) {
  uint32_t a[] = {u0, u1};
  const uint8_t *u = (const uint8_t *)&a;
  print_64_bits_u8_arr(var_name, u);
}
void print_64_bits_in_u8(char *var_name, int32_t i0, int32_t i1) {
  int32_t a[] = {i0, i1};
  const uint8_t *u = (const uint8_t *)&a;
  print_64_bits_u8_arr(var_name, u);
}
void print_64_bits_in_u8(char *var_name, uint64_t u0) {
  uint64_t a[] = {u0};
  const uint8_t *u = (const uint8_t *)&a;
  print_64_bits_u8_arr(var_name, u);
}
void print_64_bits_in_u8(char *var_name, int64_t i0) {
  int64_t a[] = {i0};
  const uint8_t *u = (const uint8_t *)&a;
  print_64_bits_u8_arr(var_name, u);
}

void print_128_bits_in_u8(char *var_name, uint8_t u0, uint8_t u1, uint8_t u2, uint8_t u3, uint8_t u4, uint8_t u5,
                          uint8_t u6, uint8_t u7, uint8_t u8, uint8_t u9, uint8_t u10, uint8_t u11, uint8_t u12,
                          uint8_t u13, uint8_t u14, uint8_t u15) {
  uint8_t a[] = {u0, u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11, u12, u13, u14, u15};
  const uint8_t *u = (const uint8_t *)&a;
  print_128_bits_u8_arr(var_name, u);
}
void print_128_bits_in_u8(char *var_name, int8_t i0, int8_t i1, int8_t i2, int8_t i3, int8_t i4, int8_t i5, int8_t i6,
                          int8_t i7, int8_t i8, int8_t i9, int8_t i10, int8_t i11, int8_t i12, int8_t i13, int8_t i14,
                          int8_t i15) {
  int8_t a[] = {i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15};
  const uint8_t *u = (const uint8_t *)&a;
  print_128_bits_u8_arr(var_name, u);
}
void print_128_bits_in_u8(char *var_name, uint16_t u0, uint16_t u1, uint16_t u2, uint16_t u3, uint16_t u4, uint16_t u5,
                          uint16_t u6, uint16_t u7) {
  uint16_t a[] = {u0, u1, u2, u3, u4, u5, u6, u7};
  const uint8_t *u = (const uint8_t *)&a;
  print_128_bits_u8_arr(var_name, u);
}
void print_128_bits_in_u8(char *var_name, int16_t i0, int16_t i1, int16_t i2, int16_t i3, int16_t i4, int16_t i5,
                          int16_t i6, int16_t i7) {
  int16_t a[] = {i0, i1, i2, i3, i4, i5, i6, i7};
  const uint8_t *u = (const uint8_t *)&a;
  print_128_bits_u8_arr(var_name, u);
}
void print_128_bits_in_u8(char *var_name, uint32_t u0, uint32_t u1, uint32_t u2, uint32_t u3) {
  uint32_t a[] = {u0, u1, u2, u3};
  const uint8_t *u = (const uint8_t *)&a;
  print_128_bits_u8_arr(var_name, u);
}
void print_128_bits_in_u8(char *var_name, int32_t i0, int32_t i1, int32_t i2, int32_t i3) {
  int32_t a[] = {i0, i1, i2, i3};
  const uint8_t *u = (const uint8_t *)&a;
  print_128_bits_u8_arr(var_name, u);
}
void print_128_bits_in_u8(char *var_name, uint64_t u0, uint64_t u1) {
  uint64_t a[] = {u0, u1};
  const uint8_t *u = (const uint8_t *)&a;
  print_128_bits_u8_arr(var_name, u);
}
void print_128_bits_in_u8(char *var_name, int64_t i0, int64_t i1) {
  int64_t a[] = {i0, i1};
  const uint8_t *u = (const uint8_t *)&a;
  print_128_bits_u8_arr(var_name, u);
}

}  // namespace NEON2RVV
