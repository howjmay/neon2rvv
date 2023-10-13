#include <assert.h>
#include <float.h>
#include <inttypes.h>
#include <math.h>
#include <stdalign.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utility>

#include "binding.h"
#include "impl.h"

// Try 10,000 random floating point values for each test we run
#define MAX_TEST_VALUE 10000

/* Pattern Matching for C macros.
 * https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms
 */

/* catenate */
#define PRIMITIVE_CAT(a, ...) a##__VA_ARGS__

#define IIF(c) PRIMITIVE_CAT(IIF_, c)
/* run the 2nd parameter */
#define IIF_0(t, ...) __VA_ARGS__
/* run the 1st parameter */
#define IIF_1(t, ...) t

// This program a set of unit tests to ensure that each NEON call provide the
// output we expect.  If this fires an assert, then something didn't match up.
//
// Functions with "test_" prefix will be called in run_single_test.
namespace NEON2RVV {
// Forward declaration
class NEON2RVV_TEST_IMPL : public NEON2RVV_TEST {
public:
  NEON2RVV_TEST_IMPL(void);
  result_t load_test_float_pointers(uint32_t i);
  result_t load_test_int_pointers(uint32_t i);
  result_t run_single_test(INSTRUCTION_TEST test, uint32_t i);

  float *test_cases_float_pointer1;
  float *test_cases_float_pointer2;
  int32_t *test_cases_int_pointer1;
  int32_t *test_cases_int_pointer2;
  float test_cases_floats[MAX_TEST_VALUE];
  int32_t test_cases_ints[MAX_TEST_VALUE];

  virtual ~NEON2RVV_TEST_IMPL(void) {
    platform_aligned_free(test_cases_float_pointer1);
    platform_aligned_free(test_cases_float_pointer2);
    platform_aligned_free(test_cases_int_pointer1);
    platform_aligned_free(test_cases_int_pointer2);
  }
  virtual void release(void) { delete this; }
  virtual result_t run_test(INSTRUCTION_TEST test) {
    result_t ret = TEST_SUCCESS;

    // Test a whole bunch of values
    for (uint32_t i = 0; i < (MAX_TEST_VALUE - 8); i++) {
      ret = load_test_float_pointers(i); // Load some random float values
      if (ret == TEST_FAIL)
        break;                         // load test float failed??
      ret = load_test_int_pointers(i); // load some random int values
      if (ret == TEST_FAIL)
        break; // load test float failed??
      // If we are testing the reciprocal, then invert the input data
      // (easier for debugging)
      if (test == it_vrecps_f32 || test == it_vrecpsq_f32 ||
          test == it_vrecpe_f32 || test == it_vrecpe_u32 ||
          test == it_vrecpeq_f32 || test == it_vrecpeq_u32 ||
          test == it_vrecpe_f16 || test == it_vrecpeq_f16 ||
          test == it_vrecps_f16 || test == it_vrecpsq_f16) {
        test_cases_float_pointer1[0] = 1.0f / test_cases_float_pointer1[0];
        test_cases_float_pointer1[1] = 1.0f / test_cases_float_pointer1[1];
        test_cases_float_pointer1[2] = 1.0f / test_cases_float_pointer1[2];
        test_cases_float_pointer1[3] = 1.0f / test_cases_float_pointer1[3];
      }
      if (test == it_vrecps_f32 || test == it_vrecpsq_f32 ||
          test == it_vrecpe_f32 || test == it_vrecpe_u32 ||
          test == it_vrecpeq_f32 || test == it_vrecpeq_u32 ||
          test == it_vrecpe_f16 || test == it_vrecpeq_f16 ||
          test == it_vrecps_f16 || test == it_vrecpsq_f16 ||
          test == it_vrsqrts_f32 || test == it_vrsqrtsq_f32 ||
          test == it_vrsqrte_f32 || test == it_vrsqrte_u32 ||
          test == it_vrsqrteq_f32 || test == it_vrsqrteq_u32 ||
          test == it_vrsqrte_f16 || test == it_vrsqrteq_f16 ||
          test == it_vrsqrts_f16 || test == it_vrsqrtsq_f16) {
        if ((rand() & 3) == 0) {
          uint32_t r1 = rand() & 3;
          uint32_t r2 = rand() & 3;
          uint32_t r3 = rand() & 3;
          uint32_t r4 = rand() & 3;
          uint32_t r5 = rand() & 3;
          uint32_t r6 = rand() & 3;
          uint32_t r7 = rand() & 3;
          uint32_t r8 = rand() & 3;
          test_cases_float_pointer1[r1] = 0.0f;
          test_cases_float_pointer1[r2] = 0.0f;
          test_cases_float_pointer1[r3] = 0.0f;
          test_cases_float_pointer1[r4] = 0.0f;
          test_cases_float_pointer1[r5] = -0.0f;
          test_cases_float_pointer1[r6] = -0.0f;
          test_cases_float_pointer1[r7] = -0.0f;
          test_cases_float_pointer1[r8] = -0.0f;
        }
      }
      if (test == it_vceq_s8 || test == it_vceq_s16 || test == it_vceq_s32 ||
          test == it_vceq_f32 || test == it_vceq_u8 || test == it_vceq_u16 ||
          test == it_vceq_u32 || test == it_vceq_p8 || test == it_vceqq_s8 ||
          test == it_vceqq_s16 || test == it_vceqq_s32 ||
          test == it_vceqq_f32 || test == it_vceqq_u8 || test == it_vceqq_u16 ||
          test == it_vceqq_u32 || test == it_vceqq_p8 || test == it_vcge_s8 ||
          test == it_vcge_s16 || test == it_vcge_s32 || test == it_vcge_f32 ||
          test == it_vcge_u8 || test == it_vcge_u16 || test == it_vcge_u32 ||
          test == it_vcgeq_s8 || test == it_vcgeq_s16 || test == it_vcgeq_s32 ||
          test == it_vcgeq_f32 || test == it_vcgeq_u8 || test == it_vcgeq_u16 ||
          test == it_vcgeq_u32 || test == it_vcle_s8 || test == it_vcle_s16 ||
          test == it_vcle_s32 || test == it_vcle_f32 || test == it_vcle_u8 ||
          test == it_vcle_u16 || test == it_vcle_u32 || test == it_vcleq_s8 ||
          test == it_vcleq_s16 || test == it_vcleq_s32 ||
          test == it_vcleq_f32 || test == it_vcleq_u8 || test == it_vcleq_u16 ||
          test == it_vcleq_u32) {
        // Make sure at least one value is the same.
        test_cases_float_pointer1[3] = test_cases_float_pointer2[3];
      }

      if (test == it_vceq_s8 || test == it_vceq_s16 || test == it_vceq_s32 ||
          test == it_vceq_f32 || test == it_vceq_u8 || test == it_vceq_u16 ||
          test == it_vceq_u32 || test == it_vceq_p8 || test == it_vceqq_s8 ||
          test == it_vceqq_s16 || test == it_vceqq_s32 ||
          test == it_vceqq_f32 || test == it_vceqq_u8 || test == it_vceqq_u16 ||
          test == it_vceqq_u32 || test == it_vceqq_p8 || test == it_vcge_s8 ||
          test == it_vcge_s16 || test == it_vcge_s32 || test == it_vcge_f32 ||
          test == it_vcge_u8 || test == it_vcge_u16 || test == it_vcge_u32 ||
          test == it_vcgeq_s8 || test == it_vcgeq_s16 || test == it_vcgeq_s32 ||
          test == it_vcgeq_f32 || test == it_vcgeq_u8 || test == it_vcgeq_u16 ||
          test == it_vcgeq_u32 || test == it_vcle_s8 || test == it_vcle_s16 ||
          test == it_vcle_s32 || test == it_vcle_f32 || test == it_vcle_u8 ||
          test == it_vcle_u16 || test == it_vcle_u32 || test == it_vcleq_s8 ||
          test == it_vcleq_s16 || test == it_vcleq_s32 ||
          test == it_vcleq_f32 || test == it_vcleq_u8 || test == it_vcleq_u16 ||
          test == it_vcleq_u32 || test == it_vcgt_s8 || test == it_vcgt_s16 ||
          test == it_vcgt_s32 || test == it_vcgt_f32 || test == it_vcgt_u8 ||
          test == it_vcgt_u16 || test == it_vcgt_u32 || test == it_vcgtq_s8 ||
          test == it_vcgtq_s16 || test == it_vcgtq_s32 ||
          test == it_vcgtq_f32 || test == it_vcgtq_u8 || test == it_vcgtq_u16 ||
          test == it_vcgtq_u32 || test == it_vclt_s8 || test == it_vclt_s16 ||
          test == it_vclt_s32 || test == it_vclt_f32 || test == it_vclt_u8 ||
          test == it_vclt_u16 || test == it_vclt_u32 || test == it_vcltq_s8 ||
          test == it_vcltq_s16 || test == it_vcltq_s32 ||
          test == it_vcltq_f32 || test == it_vcltq_u8 || test == it_vcltq_u16 ||
          test == it_vcltq_u32) {
        // Make sure the NaN values are included in the testing
        // one out of four times.
        if ((rand() & 3) == 0) {
          uint32_t r1 = rand() & 3;
          uint32_t r2 = rand() & 3;
          test_cases_float_pointer1[r1] = nanf("");
          test_cases_float_pointer2[r2] = nanf("");
        }
      }

      if (test == it_vmax_s8 || test == it_vmax_s16 || test == it_vmax_s32 ||
          test == it_vmax_f32 || test == it_vmax_u8 || test == it_vmax_u16 ||
          test == it_vmax_u32 || test == it_vpmax_s8 || test == it_vpmax_s16 ||
          test == it_vpmax_s32 || test == it_vpmax_f32 || test == it_vpmax_u8 ||
          test == it_vpmax_u16 || test == it_vpmax_u32 || test == it_vmax_f16 ||
          test == it_vpmax_f16 || test == it_vminnm_f32 ||
          test == it_vminnmq_f32 || test == it_vmin_s8 || test == it_vmin_s16 ||
          test == it_vmin_s32 || test == it_vmin_f32 || test == it_vmin_u8 ||
          test == it_vmin_u16 || test == it_vmin_u32 || test == it_vminq_s8 ||
          test == it_vminq_s16 || test == it_vminq_s32 ||
          test == it_vminq_f32 || test == it_vminq_u8 || test == it_vminq_u16 ||
          test == it_vminq_u32 || test == it_vmin_f16 || test == it_vminq_f16 ||
          test == it_vminnm_f16 || test == it_vminnmq_f16) {
        // Make sure the positive/negative infinity values are included
        // in the testing one out of four times.
        if ((rand() & 3) == 0) {
          uint32_t r1 = ((rand() & 1) << 1) + 1;
          uint32_t r2 = ((rand() & 1) << 1) + 1;
          uint32_t r3 = ((rand() & 1) << 1) + 1;
          uint32_t r4 = ((rand() & 1) << 1) + 1;
          test_cases_float_pointer1[r1] = INFINITY;
          test_cases_float_pointer2[r2] = INFINITY;
          test_cases_float_pointer1[r3] = -INFINITY;
          test_cases_float_pointer1[r4] = -INFINITY;
        }
      }

      // one out of every random 64 times or so, mix up the test floats to
      // contain some integer values
      if ((rand() & 63) == 0) {
        uint32_t option = rand() & 3;
        switch (option) {
        // All integers..
        case 0:
          test_cases_float_pointer1[0] = float(test_cases_int_pointer1[0]);
          test_cases_float_pointer1[1] = float(test_cases_int_pointer1[1]);
          test_cases_float_pointer1[2] = float(test_cases_int_pointer1[2]);
          test_cases_float_pointer1[3] = float(test_cases_int_pointer1[3]);

          test_cases_float_pointer2[0] = float(test_cases_int_pointer2[0]);
          test_cases_float_pointer2[1] = float(test_cases_int_pointer2[1]);
          test_cases_float_pointer2[2] = float(test_cases_int_pointer2[2]);
          test_cases_float_pointer2[3] = float(test_cases_int_pointer2[3]);

          break;
        case 1: {
          uint32_t index = rand() & 3;
          test_cases_float_pointer1[index] =
              float(test_cases_int_pointer1[index]);
          index = rand() & 3;
          test_cases_float_pointer2[index] =
              float(test_cases_int_pointer2[index]);
        } break;
        case 2: {
          uint32_t index1 = rand() & 3;
          uint32_t index2 = rand() & 3;
          test_cases_float_pointer1[index1] =
              float(test_cases_int_pointer1[index1]);
          test_cases_float_pointer1[index2] =
              float(test_cases_int_pointer1[index2]);
          index1 = rand() & 3;
          index2 = rand() & 3;
          test_cases_float_pointer1[index1] =
              float(test_cases_int_pointer1[index1]);
          test_cases_float_pointer1[index2] =
              float(test_cases_int_pointer1[index2]);
        } break;
        case 3:
          test_cases_float_pointer1[0] = float(test_cases_int_pointer1[0]);
          test_cases_float_pointer1[1] = float(test_cases_int_pointer1[1]);
          test_cases_float_pointer1[2] = float(test_cases_int_pointer1[2]);
          test_cases_float_pointer1[3] = float(test_cases_int_pointer1[3]);
          break;
        }
        if ((rand() & 3) == 0) { // one out of 4 times, make halves
          for (uint32_t j = 0; j < 4; j++) {
            test_cases_float_pointer1[j] *= 0.5f;
            test_cases_float_pointer2[j] *= 0.5f;
          }
        }
      }

      ret = run_single_test(test, i);
      if (ret == TEST_FAIL) // the test failed...
      {
        // Set a breakpoint here if you want to step through the failure
        // case in the debugger
        ret = run_single_test(test, i);
        break;
      }
    }
    return ret;
  }
};

const char *instruction_string[] = {
#define _(x) #x,
    INTRIN_LIST
#undef _
};

// FIXME may not need in this project
// Produce rounding which is the same as SSE instructions with _MM_ROUND_NEAREST
// rounding mode
static inline float bankers_rounding(float val) {
  if (val < 0)
    return -bankers_rounding(-val);

  float ret;
  float round_down = floorf(val); // Round down value
  float round_up = ceilf(val);    // Round up value
  float diff_down = val - round_down;
  float diff_up = round_up - val;

  if (diff_down < diff_up) {
    /* If it's closer to the round down value, then use it */
    ret = round_down;
  } else if (diff_down > diff_up) {
    /* If it's closer to the round up value, then use it */
    ret = round_up;
  } else {
    /* If it's equidistant between round up and round down value, pick the
     * one which is an even number */
    float half = round_down / 2;
    if (half != floorf(half)) {
      /* If the round down value is odd, return the round up value */
      ret = round_up;
    } else {
      /* If the round up value is odd, return the round down value */
      ret = round_down;
    }
  }
  return ret;
}

static inline double bankers_rounding(double val) {
  if (val < 0)
    return -bankers_rounding(-val);

  double ret;
  double round_down = floor(val); // Round down value
  double round_up = ceil(val);    // Round up value
  double diff_down = val - round_down;
  double diff_up = round_up - val;

  if (diff_down < diff_up) {
    /* If it's closer to the round down value, then use it */
    ret = round_down;
  } else if (diff_down > diff_up) {
    /* If it's closer to the round up value, then use it */
    ret = round_up;
  } else {
    /* If it's equidistant between round up and round down value, pick the
     * one which is an even number */
    double half = round_down / 2;
    if (half != floor(half)) {
      /* If the round down value is odd, return the round up value */
      ret = round_up;
    } else {
      /* If the round up value is odd, return the round down value */
      ret = round_down;
    }
  }
  return ret;
}

static float ranf(void) {
  uint32_t ir = rand() & 0x7FFF;
  return (float)ir * (1.0f / 32768.0f);
}

static float ranf(float low, float high) { return ranf() * (high - low) + low; }

result_t test_vadd_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vadd_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vadd_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vadd_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vadd_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vadd_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vadd_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vadd_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vadd_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddq_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddq_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddl_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddl_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddl_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddl_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddl_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddl_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddw_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddw_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddw_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddw_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddw_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddw_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vhadd_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vhadd_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vhadd_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vhadd_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vhadd_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vhadd_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vhaddq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vhaddq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vhaddq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vhaddq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vhaddq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vhaddq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrhadd_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrhadd_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrhadd_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrhadd_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrhadd_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrhadd_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrhaddq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrhaddq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrhaddq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrhaddq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrhaddq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrhaddq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqadd_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqadd_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqadd_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqadd_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqadd_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqadd_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqadd_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqadd_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqaddq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqaddq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqaddq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqaddq_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqaddq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqaddq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqaddq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqaddq_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddhn_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddhn_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddhn_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddhn_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddhn_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddhn_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vraddhn_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vraddhn_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vraddhn_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vraddhn_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vraddhn_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vraddhn_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmul_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmul_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmul_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmul_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmul_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmul_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmul_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmulq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmulq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmulq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmulq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmulq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmulq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmulq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmul_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmulq_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmulh_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmulh_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmulhq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmulhq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmulh_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmulh_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmulhq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmulhq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmlah_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmlah_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmlahq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmlahq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmlsh_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmlsh_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmlshq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmlshq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmull_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmull_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmull_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmull_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmull_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmull_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmull_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmull_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmull_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmla_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmla_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmla_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmla_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmla_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmla_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmla_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlaq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlaq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlaq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlaq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlaq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlaq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlaq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlal_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlal_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlal_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlal_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlal_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlal_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmlal_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmlal_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmls_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmls_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmls_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmls_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmls_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmls_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmls_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsl_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsl_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsl_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsl_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsl_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsl_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmlsl_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmlsl_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfma_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmaq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfms_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmsq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrndn_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrndnq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrnda_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrndaq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrndp_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrndpq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrndm_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrndmq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrndx_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrndxq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrnd_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrndq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsub_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsub_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsub_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsub_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsub_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsub_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsub_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsub_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsub_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubq_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubq_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubl_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubl_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubl_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubl_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubl_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubl_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubw_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubw_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubw_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubw_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubw_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubw_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vhsub_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vhsub_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vhsub_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vhsub_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vhsub_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vhsub_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vhsubq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vhsubq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vhsubq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vhsubq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vhsubq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vhsubq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqsub_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqsub_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqsub_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqsub_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqsub_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqsub_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqsub_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqsub_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqsubq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqsubq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqsubq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqsubq_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqsubq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqsubq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqsubq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqsubq_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubhn_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubhn_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubhn_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubhn_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubhn_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubhn_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsubhn_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsubhn_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsubhn_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsubhn_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsubhn_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsubhn_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vceq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vceq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vceq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vceq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vceq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vceq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vceq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vceq_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vceqq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vceqq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vceqq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vceqq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vceqq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vceqq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vceqq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vceqq_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcge_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcge_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcge_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcge_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcge_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcge_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcge_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgeq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgeq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgeq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgeq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgeq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgeq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgeq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcle_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcle_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcle_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcle_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcle_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcle_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcle_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcleq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcleq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcleq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcleq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcleq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcleq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcleq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgt_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgt_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgt_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgt_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgt_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgt_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgt_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgtq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgtq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgtq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgtq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgtq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgtq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgtq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vclt_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vclt_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vclt_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vclt_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vclt_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vclt_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vclt_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcltq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcltq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcltq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcltq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcltq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcltq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcltq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabs_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabs_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabs_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabs_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabsq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabsq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabsq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabsq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqabs_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqabs_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqabs_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqabsq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqabsq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqabsq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcage_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcageq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcale_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcaleq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcagt_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcagtq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcalt_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcaltq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtst_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtst_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtst_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtst_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtst_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtst_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtst_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtst_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtstq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtstq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtstq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtstq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtstq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtstq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtstq_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtstq_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabd_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabd_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabd_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabd_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabd_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabd_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabd_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabdq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabdq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabdq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabdq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabdq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabdq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabdq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabdl_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabdl_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabdl_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabdl_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabdl_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabdl_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaba_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaba_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaba_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaba_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaba_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaba_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabaq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabaq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabaq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabaq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabaq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabaq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabal_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabal_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabal_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabal_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabal_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabal_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmax_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmax_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmax_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmax_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmax_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmax_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmax_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmaxq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmaxq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmaxq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmaxq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmaxnm_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmaxnmq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vminnm_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vminnmq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmaxq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmaxq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmaxq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmin_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmin_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmin_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmin_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmin_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmin_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmin_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vminq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vminq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vminq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vminq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vminq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vminq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vminq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpadd_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpadd_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpadd_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpadd_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpadd_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpadd_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpadd_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpaddl_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpaddl_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpaddl_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpaddl_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpaddl_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpaddl_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpaddlq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpaddlq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpaddlq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpaddlq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpaddlq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpaddlq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpadal_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpadal_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpadal_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpadal_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpadal_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpadal_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpadalq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpadalq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpadalq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpadalq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpadalq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpadalq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpmax_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpmax_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpmax_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpmax_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpmax_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpmax_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpmax_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpmin_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpmin_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpmin_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpmin_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpmin_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpmin_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpmin_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrecps_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrecpsq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsqrts_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsqrtsq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshl_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshl_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshl_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshl_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshl_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshl_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshl_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshl_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshlq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshlq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshlq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshlq_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshlq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshlq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshlq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshlq_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshl_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshl_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshl_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshl_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshl_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshl_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshl_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshl_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshlq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshlq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshlq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshlq_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshlq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshlq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshlq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshlq_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshl_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshl_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshl_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshl_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshl_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshl_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshl_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshl_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshlq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshlq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshlq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshlq_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshlq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshlq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshlq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshlq_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrshl_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrshl_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrshl_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrshl_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrshl_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrshl_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrshl_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrshl_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrshlq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrshlq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrshlq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrshlq_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrshlq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrshlq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrshlq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrshlq_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshr_n_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshr_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshr_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshr_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshr_n_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshr_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshr_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshr_n_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshrq_n_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshrq_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshrq_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshrq_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshrq_n_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshrq_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshrq_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshrq_n_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshr_n_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshr_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshr_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshr_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshr_n_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshr_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshr_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshr_n_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshrq_n_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshrq_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshrq_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshrq_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshrq_n_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshrq_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshrq_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshrq_n_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshrn_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshrn_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshrn_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshrn_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshrn_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshrn_n_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshrn_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshrn_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshrn_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshrn_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshrn_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrshrn_n_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshrn_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshrn_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshrn_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshrn_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshrn_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshrn_n_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrshrn_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrshrn_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrshrn_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrshrn_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrshrn_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrshrn_n_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshrun_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshrun_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshrun_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrshrun_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrshrun_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrshrun_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshl_n_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshl_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshl_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshl_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshl_n_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshl_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshl_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshl_n_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshlq_n_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshlq_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshlq_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshlq_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshlq_n_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshlq_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshlq_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshlq_n_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshl_n_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshl_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshl_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshl_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshl_n_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshl_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshl_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshl_n_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshlq_n_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshlq_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshlq_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshlq_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshlq_n_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshlq_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshlq_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshlq_n_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshlu_n_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshlu_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshlu_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshlu_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshluq_n_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshluq_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshluq_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqshluq_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshll_n_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshll_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshll_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshll_n_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshll_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vshll_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsra_n_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsra_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsra_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsra_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsra_n_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsra_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsra_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsra_n_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsraq_n_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsraq_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsraq_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsraq_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsraq_n_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsraq_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsraq_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsraq_n_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsra_n_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsra_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsra_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsra_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsra_n_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsra_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsra_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsra_n_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsraq_n_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsraq_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsraq_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsraq_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsraq_n_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsraq_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsraq_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsraq_n_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsri_n_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsri_n_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsri_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsri_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsri_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsri_n_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsri_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsri_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsri_n_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsri_n_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsri_n_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsriq_n_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsriq_n_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsriq_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsriq_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsriq_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsriq_n_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsriq_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsriq_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsriq_n_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsriq_n_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsriq_n_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsli_n_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsli_n_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsli_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsli_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsli_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsli_n_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsli_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsli_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsli_n_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsli_n_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsli_n_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsliq_n_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsliq_n_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsliq_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsliq_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsliq_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsliq_n_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsliq_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsliq_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsliq_n_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsliq_n_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsliq_n_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vneg_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vneg_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vneg_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vneg_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vnegq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vnegq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vnegq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vnegq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqneg_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqneg_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqneg_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqnegq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqnegq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqnegq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmvn_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmvn_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmvn_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmvn_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmvn_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmvn_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmvn_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmvnq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmvnq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmvnq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmvnq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmvnq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmvnq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmvnq_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcls_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcls_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcls_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vclsq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vclsq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vclsq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vclz_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vclz_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vclz_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vclz_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vclz_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vclz_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vclzq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vclzq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vclzq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vclzq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vclzq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vclzq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcnt_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcnt_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcnt_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcntq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcntq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcntq_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrecpe_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrecpe_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrecpeq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrecpeq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsqrte_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsqrte_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsqrteq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsqrteq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_lane_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_lane_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_lane_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_lane_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_lane_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_lane_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_lane_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vgetq_lane_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vgetq_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vgetq_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vgetq_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vgetq_lane_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vgetq_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vgetq_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vgetq_lane_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vgetq_lane_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vgetq_lane_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vgetq_lane_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vgetq_lane_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vset_lane_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vset_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vset_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vset_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vset_lane_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vset_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vset_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vset_lane_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vset_lane_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vset_lane_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vset_lane_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vset_lane_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsetq_lane_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsetq_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsetq_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsetq_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsetq_lane_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsetq_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsetq_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsetq_lane_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsetq_lane_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsetq_lane_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsetq_lane_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsetq_lane_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcreate_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcreate_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcreate_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcreate_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcreate_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcreate_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcreate_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcreate_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcreate_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcreate_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcreate_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcreate_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcreate_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdup_n_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdup_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdup_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdup_n_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdup_n_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdup_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdup_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdup_n_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdup_n_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdup_n_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdup_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdup_n_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdupq_n_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdupq_n_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdupq_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdupq_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdupq_n_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdupq_n_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdupq_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdupq_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdupq_n_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdupq_n_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdupq_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdupq_n_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmov_n_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmov_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmov_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmov_n_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmov_n_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmov_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmov_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmov_n_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmov_n_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmov_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmov_n_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmovq_n_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmovq_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmovq_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmovq_n_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmovq_n_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmovq_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmovq_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmovq_n_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmovq_n_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmovq_n_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmovq_n_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdup_lane_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdup_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdup_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdup_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdup_lane_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdup_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdup_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdup_lane_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdup_lane_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdup_lane_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdup_lane_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdup_lane_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdupq_lane_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdupq_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdupq_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdupq_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdupq_lane_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdupq_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdupq_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdupq_lane_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdupq_lane_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdupq_lane_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdupq_lane_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdupq_lane_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcombine_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcombine_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcombine_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcombine_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcombine_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcombine_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcombine_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcombine_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcombine_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcombine_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcombine_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcombine_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcombine_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_high_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_high_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_high_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_high_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_high_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_high_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_high_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_high_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_high_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_high_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_high_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_high_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_high_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_low_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_low_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_low_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_low_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_low_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_low_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_low_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_low_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_low_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_low_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_low_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_low_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vget_low_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvt_s32_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvt_f32_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvt_f32_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvt_u32_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtq_s32_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtq_f32_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtq_f32_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtq_u32_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvt_f16_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvt_f32_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvt_n_s32_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvt_n_f32_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvt_n_f32_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvt_n_u32_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtq_n_s32_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtq_n_f32_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtq_n_f32_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtq_n_u32_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmovn_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmovn_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmovn_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmovn_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmovn_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmovn_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqmovn_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqmovn_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqmovn_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqmovn_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqmovn_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqmovn_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqmovun_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqmovun_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqmovun_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmovl_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmovl_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmovl_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmovl_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmovl_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmovl_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtbl1_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtbl1_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtbl1_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtbl2_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtbl2_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtbl2_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtbl3_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtbl3_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtbl3_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtbl4_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtbl4_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtbl4_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtbx1_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtbx1_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtbx1_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtbx2_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtbx2_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtbx2_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtbx3_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtbx3_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtbx3_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtbx4_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtbx4_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtbx4_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmul_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmul_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmul_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmul_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmul_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmulq_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmulq_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmulq_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmulq_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmulq_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmla_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmla_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmla_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmla_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmla_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlaq_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlaq_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlaq_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlaq_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlaq_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlal_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlal_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlal_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlal_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmlal_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmlal_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmls_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmls_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmls_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmls_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmls_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsq_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsq_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsq_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsq_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsq_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsl_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsl_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsl_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsl_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmlsl_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmlsl_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmull_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmull_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmull_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmull_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmull_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmull_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmulhq_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmulhq_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmulh_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmulh_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmulhq_lane_s16(const NEON2RVV_TEST_IMPL &impl,
                                 uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmulhq_lane_s32(const NEON2RVV_TEST_IMPL &impl,
                                 uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmulh_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmulh_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmlahq_lane_s16(const NEON2RVV_TEST_IMPL &impl,
                                 uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmlahq_lane_s32(const NEON2RVV_TEST_IMPL &impl,
                                 uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmlah_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmlah_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmlshq_lane_s16(const NEON2RVV_TEST_IMPL &impl,
                                 uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmlshq_lane_s32(const NEON2RVV_TEST_IMPL &impl,
                                 uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmlsh_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmlsh_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmul_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmul_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmul_n_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmul_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmul_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmulq_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmulq_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmulq_n_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmulq_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmulq_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmull_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmull_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmull_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmull_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmull_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmull_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmulhq_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmulhq_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmulh_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmulh_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmulhq_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmulhq_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmulh_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqrdmulh_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmla_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmla_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmla_n_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmla_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmla_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlaq_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlaq_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlaq_n_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlaq_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlaq_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlal_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlal_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlal_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlal_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmlal_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmlal_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmls_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmls_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmls_n_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmls_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmls_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsq_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsq_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsq_n_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsq_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsq_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsl_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsl_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsl_n_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmlsl_n_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmlsl_n_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vqdmlsl_n_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vext_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vext_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vext_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vext_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vext_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vext_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vext_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vext_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vext_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vext_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vext_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vext_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vextq_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vextq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vextq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vextq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vextq_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vextq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vextq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vextq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vextq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vextq_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vextq_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vextq_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev64_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev64_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev64_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev64_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev64_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev64_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev64_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev64_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev64_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev64q_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev64q_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev64q_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev64q_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev64q_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev64q_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev64q_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev64q_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev64q_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev32_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev32_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev32_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev32_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev32_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev32_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev32q_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev32q_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev32q_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev32q_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev32q_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev32q_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev16_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev16_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev16_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev16q_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev16q_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev16q_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbsl_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbsl_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbsl_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbsl_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbsl_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbsl_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbsl_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbsl_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbsl_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbsl_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbsl_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbsl_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbslq_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbslq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbslq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbslq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbslq_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbslq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbslq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbslq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbslq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbslq_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbslq_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbslq_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtrn_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtrn_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtrn_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtrn_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtrn_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtrn_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtrn_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtrn_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtrn_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtrnq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtrnq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtrnq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtrnq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtrnq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtrnq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtrnq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtrnq_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtrnq_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vzip_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vzip_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vzip_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vzip_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vzip_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vzip_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vzip_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vzip_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vzip_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vzipq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vzipq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vzipq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vzipq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vzipq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vzipq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vzipq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vzipq_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vzipq_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vuzp_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vuzp_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vuzp_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vuzp_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vuzp_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vuzp_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vuzp_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vuzp_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vuzp_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vuzpq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vuzpq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vuzpq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vuzpq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vuzpq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vuzpq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vuzpq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vuzpq_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vuzpq_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_lane_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_lane_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_lane_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_lane_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_lane_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_lane_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_lane_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_lane_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_lane_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_lane_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_lane_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_lane_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_lane_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_lane_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_lane_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_lane_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_dup_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_dup_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_dup_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_dup_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_dup_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_dup_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_dup_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_dup_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_dup_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_dup_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_dup_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_dup_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1_dup_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_dup_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_dup_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_dup_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_dup_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_dup_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_dup_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_dup_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_dup_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_dup_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_dup_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_dup_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_dup_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld1q_dup_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1q_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1q_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1q_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1q_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1q_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1q_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1q_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1q_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1q_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1q_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1q_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1q_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1q_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1_lane_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1_lane_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1_lane_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1_lane_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1_lane_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1_lane_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1_lane_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1_lane_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1q_lane_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1q_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1q_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1q_lane_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1q_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1q_lane_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1q_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1q_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1q_lane_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1q_lane_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1q_lane_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1q_lane_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst1q_lane_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2q_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2q_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2q_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2q_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2q_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2q_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2q_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2q_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2q_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2q_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_lane_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_lane_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_lane_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_lane_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_lane_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2q_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2q_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2q_lane_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2q_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2q_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2q_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2q_lane_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_dup_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_dup_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_dup_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_dup_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_dup_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_dup_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_dup_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_dup_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_dup_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_dup_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_dup_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_dup_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld2_dup_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2q_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2q_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2q_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2q_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2q_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2q_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2q_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2q_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2q_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2q_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2_lane_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2_lane_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2_lane_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2_lane_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2_lane_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2q_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2q_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2q_lane_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2q_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2q_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2q_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst2q_lane_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3q_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3q_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3q_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3q_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3q_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3q_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3q_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3q_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3q_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3q_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_lane_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_lane_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_lane_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_lane_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_lane_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3q_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3q_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3q_lane_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3q_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3q_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3q_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3q_lane_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_dup_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_dup_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_dup_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_dup_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_dup_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_dup_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_dup_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_dup_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_dup_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_dup_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_dup_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_dup_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld3_dup_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3q_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3q_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3q_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3q_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3q_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3q_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3q_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3q_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3q_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3q_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3_lane_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3_lane_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3_lane_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3_lane_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3_lane_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3q_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3q_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3q_lane_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3q_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3q_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3q_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst3q_lane_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4q_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4q_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4q_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4q_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4q_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4q_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4q_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4q_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4q_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4q_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_lane_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_lane_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_lane_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_lane_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_lane_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4q_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4q_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4q_lane_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4q_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4q_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4q_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4q_lane_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_dup_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_dup_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_dup_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_dup_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_dup_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_dup_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_dup_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_dup_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_dup_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_dup_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_dup_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_dup_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vld4_dup_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4q_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4q_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4q_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4q_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4q_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4q_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4q_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4q_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4q_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4q_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4_lane_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4_lane_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4_lane_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4_lane_p8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4_lane_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4q_lane_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4q_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4q_lane_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4q_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4q_lane_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4q_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vst4q_lane_p16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vand_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vand_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vand_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vand_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vand_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vand_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vand_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vand_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vandq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vandq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vandq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vandq_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vandq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vandq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vandq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vandq_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vorr_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vorr_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vorr_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vorr_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vorr_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vorr_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vorr_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vorr_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vorrq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vorrq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vorrq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vorrq_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vorrq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vorrq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vorrq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vorrq_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_veor_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_veor_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_veor_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_veor_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_veor_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_veor_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_veor_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_veor_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_veorq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_veorq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_veorq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_veorq_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_veorq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_veorq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_veorq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_veorq_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbic_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbic_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbic_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbic_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbic_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbic_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbic_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbic_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbicq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbicq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbicq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbicq_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbicq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbicq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbicq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbicq_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vorn_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vorn_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vorn_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vorn_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vorn_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vorn_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vorn_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vorn_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vornq_s8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vornq_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vornq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vornq_s64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vornq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vornq_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vornq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vornq_u64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p8_p16(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p8_f16(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p8_f32(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p8_p64(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p8_s64(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p8_u64(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p8_s8(const NEON2RVV_TEST_IMPL &impl,
                                 uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p8_s16(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p8_s32(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p8_u8(const NEON2RVV_TEST_IMPL &impl,
                                 uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p8_u16(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p8_u32(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p16_p8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p16_f16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p16_f32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p16_p64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p16_s64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p16_u64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p16_s8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p16_s16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p16_s32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p16_u8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p16_u16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p16_u32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_f16_bf16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_f16_p8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_f16_p16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_f16_f32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_f16_p64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_f16_s64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_f16_u64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_f16_s8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_f16_s16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_f16_s32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_f16_u8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_f16_u16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_f16_u32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_f32_p8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_f32_p16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_f32_f16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_f32_p64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_f32_s64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_f32_u64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_f32_s8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_f32_s16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_f32_s32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_f32_u8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_f32_u16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_f32_u32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p64_p8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p64_p16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p64_f16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p64_f32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p64_s64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p64_u64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p64_s8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p64_s16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p64_s32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p64_u8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p64_u16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_p64_u32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s64_p8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s64_p16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s64_f16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s64_f32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s64_p64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s64_u64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s64_s8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s64_s16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s64_s32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s64_u8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s64_u16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s64_u32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u64_p8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u64_p16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u64_f16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u64_f32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u64_p64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u64_s64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u64_s8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u64_s16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u64_s32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u64_u8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u64_u16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u64_u32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s8_p8(const NEON2RVV_TEST_IMPL &impl,
                                 uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s8_p16(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s8_f16(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s8_f32(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s8_p64(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s8_s64(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s8_u64(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s8_s16(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s8_s32(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s8_u8(const NEON2RVV_TEST_IMPL &impl,
                                 uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s8_u16(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s8_u32(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s16_p8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s16_p16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s16_f16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s16_f32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s16_p64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s16_s64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s16_u64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s16_s8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s16_s32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s16_u8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s16_u16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s16_u32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s32_p8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s32_p16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s32_f16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s32_f32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s32_p64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s32_s64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s32_u64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s32_s8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s32_s16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s32_u8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s32_u16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_s32_u32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u8_p8(const NEON2RVV_TEST_IMPL &impl,
                                 uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u8_p16(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u8_f16(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u8_f32(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u8_p64(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u8_s64(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u8_u64(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u8_s8(const NEON2RVV_TEST_IMPL &impl,
                                 uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u8_s16(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u8_s32(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u8_u16(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u8_u32(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u16_p8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u16_p16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u16_f16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u16_f32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u16_p64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u16_s64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u16_u64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u16_s8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u16_s16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u16_s32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u16_u8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u16_u32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u32_p8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u32_p16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u32_f16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u32_f32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u32_p64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u32_s64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u32_u64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u32_s8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u32_s16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u32_s32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u32_u8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpret_u32_u16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p8_p16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p8_f16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p8_f32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p8_p64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p8_p128(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p8_s64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p8_u64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p8_s8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p8_s16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p8_s32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p8_u8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p8_u16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p8_u32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p16_p8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p16_f16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p16_f32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p16_p64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p16_p128(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p16_s64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p16_u64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p16_s8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p16_s16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p16_s32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p16_u8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p16_u16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p16_u32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f16_p8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f16_p16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f16_bf16(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f16_f32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f16_p64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f16_p128(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f16_s64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f16_u64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f16_s8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f16_s16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f16_s32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f16_u8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f16_u16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f16_u32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f32_p8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f32_p16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f32_f16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f32_p64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f32_p128(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f32_s64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f32_u64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f32_s8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f32_s16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f32_s32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f32_u8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f32_u16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_f32_u32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p64_p8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p64_p16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p64_f16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p64_f32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p64_p128(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p64_s64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p64_u64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p64_s8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p64_s16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p64_s32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p64_u8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p64_u16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p64_u32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p128_p8(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p128_p16(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p128_f16(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p128_f32(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p128_p64(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p128_s64(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p128_u64(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p128_s8(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p128_s16(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p128_s32(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p128_u8(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p128_u16(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_p128_u32(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s64_p8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s64_p16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s64_f16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s64_f32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s64_p64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s64_p128(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s64_u64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s64_s8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s64_s16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s64_s32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s64_u8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s64_u16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s64_u32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u64_p8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u64_p16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u64_f16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u64_f32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u64_p64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u64_p128(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u64_s64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u64_s8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u64_s16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u64_s32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u64_u8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u64_u16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u64_u32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s8_p8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s8_p16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s8_f16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s8_f32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s8_p64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s8_p128(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s8_s64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s8_u64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s8_s16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s8_s32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s8_u8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s8_u16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s8_u32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s16_p8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s16_p16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s16_f16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s16_f32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s16_p64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s16_p128(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s16_s64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s16_u64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s16_s8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s16_s32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s16_u8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s16_u16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s16_u32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s32_p8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s32_p16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s32_f16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s32_f32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s32_p64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s32_p128(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s32_s64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s32_u64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s32_s8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s32_s16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s32_u8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s32_u16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_s32_u32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u8_p8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u8_p16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u8_f16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u8_f32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u8_p64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u8_p128(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u8_s64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u8_u64(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u8_s8(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u8_s16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u8_s32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u8_u16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u8_u32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u16_p8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u16_p16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u16_f16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u16_f32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u16_p64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u16_p128(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u16_s64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u16_u64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u16_s8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u16_s16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u16_s32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u16_u8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u16_u32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u32_p8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u32_p16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u32_f16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u32_f32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u32_p64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u32_p128(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u32_s64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u32_u64(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u32_s8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u32_s16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u32_s32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u32_u8(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vreinterpretq_u32_u16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vldrq_p128(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vstrq_p128(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vceq_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vceqz_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vceqq_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vceqzq_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtst_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaeseq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaesdq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaesmcq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaesimcq_u8(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsha1h_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsha1cq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsha1pq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsha1mq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsha1su0q_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsha1su1q_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsha256hq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsha256h2q_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsha256su0q_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsha256su1q_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmull_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmull_high_p64(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabd_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabdq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabs_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vabsq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vadd_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vaddq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcage_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcageq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcagt_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcagtq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcale_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcaleq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcalt_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcaltq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vceq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vceqq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vceqz_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vceqzq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcge_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgeq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgez_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgezq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgt_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgtq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgtz_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcgtzq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcle_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcleq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vclez_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vclezq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vclt_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcltq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcltz_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcltzq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvt_f16_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvt_f16_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvt_s16_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvt_u16_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtq_f16_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtq_f16_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtq_s16_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtq_u16_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvta_s16_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvta_u16_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtaq_s16_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtaq_u16_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtm_s16_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtm_u16_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtmq_s16_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtmq_u16_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtn_s16_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtn_u16_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtnq_s16_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtnq_u16_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtp_s16_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtp_u16_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtpq_s16_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtpq_u16_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvt_n_f16_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvt_n_f16_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtq_n_f16_s16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtq_n_f16_u16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvt_n_s16_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvt_n_u16_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtq_n_s16_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcvtq_n_u16_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfma_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmaq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfms_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmsq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmax_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmaxq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmaxnm_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmaxnmq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmin_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vminq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vminnm_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vminnmq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmul_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmul_lane_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmul_n_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmulq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmulq_lane_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmulq_n_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vneg_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vnegq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpadd_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpmax_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vpmin_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrecpe_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrecpeq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrnd_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrndq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrnda_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrndaq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrndm_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrndmq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrndn_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrndnq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrndp_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrndpq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrndx_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrndxq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsqrte_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsqrteq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrecps_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrecpsq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsqrts_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrsqrtsq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsub_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsubq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbsl_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vbslq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdup_n_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdupq_n_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdup_lane_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdupq_lane_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vext_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vextq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmov_n_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vmovq_n_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev64_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vrev64q_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtrn_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vtrnq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vuzp_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vuzpq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vzip_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vzipq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdot_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdotq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdot_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdotq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdot_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdotq_lane_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdot_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdotq_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdot_laneq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdotq_laneq_u32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdot_laneq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vdotq_laneq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmlal_low_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmlsl_low_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmlal_high_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmlsl_high_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmlalq_low_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmlslq_low_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmlalq_high_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmlslq_high_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmlal_lane_low_f16(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmlal_lane_high_f16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmlalq_laneq_low_f16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmlalq_lane_low_f16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmlal_laneq_low_f16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmlalq_laneq_high_f16(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmlalq_lane_high_f16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmlal_laneq_high_f16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmlsl_lane_low_f16(const NEON2RVV_TEST_IMPL &impl,
                                  uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmlsl_lane_high_f16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmlslq_laneq_low_f16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmlslq_lane_low_f16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmlsl_laneq_low_f16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmlslq_laneq_high_f16(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmlslq_lane_high_f16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vfmlsl_laneq_high_f16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcadd_rot90_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcaddq_rot90_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcadd_rot270_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcaddq_rot270_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmla_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmlaq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmla_lane_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmla_laneq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmlaq_lane_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmlaq_laneq_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmla_rot90_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmlaq_rot90_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmla_rot90_lane_f16(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmla_rot90_laneq_f16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmlaq_rot90_lane_f16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmlaq_rot90_laneq_f16(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmla_rot180_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmlaq_rot180_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmla_rot180_lane_f16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmla_rot180_laneq_f16(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmlaq_rot180_lane_f16(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmlaq_rot180_laneq_f16(const NEON2RVV_TEST_IMPL &impl,
                                      uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmla_rot270_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmlaq_rot270_f16(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmla_rot270_lane_f16(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmla_rot270_laneq_f16(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmlaq_rot270_lane_f16(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmlaq_rot270_laneq_f16(const NEON2RVV_TEST_IMPL &impl,
                                      uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcadd_rot90_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcaddq_rot90_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcadd_rot270_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcaddq_rot270_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmla_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmlaq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmla_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmla_laneq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmlaq_lane_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmlaq_laneq_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmla_rot90_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmlaq_rot90_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmla_rot90_lane_f32(const NEON2RVV_TEST_IMPL &impl,
                                   uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmla_rot90_laneq_f32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmlaq_rot90_lane_f32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmlaq_rot90_laneq_f32(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmla_rot180_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmlaq_rot180_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmla_rot180_lane_f32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmla_rot180_laneq_f32(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmlaq_rot180_lane_f32(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmlaq_rot180_laneq_f32(const NEON2RVV_TEST_IMPL &impl,
                                      uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmla_rot270_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmlaq_rot270_f32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmla_rot270_lane_f32(const NEON2RVV_TEST_IMPL &impl,
                                    uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmla_rot270_laneq_f32(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmlaq_rot270_lane_f32(const NEON2RVV_TEST_IMPL &impl,
                                     uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vcmlaq_rot270_laneq_f32(const NEON2RVV_TEST_IMPL &impl,
                                      uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vusdot_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vusdotq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vusdot_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vusdotq_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsudot_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsudotq_lane_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vusdot_laneq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vusdotq_laneq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsudot_laneq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

result_t test_vsudotq_laneq_s32(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_UNIMPL;
}

// Dummy function to match the case label in run_single_test.
result_t test_last(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {
  return TEST_SUCCESS;
}

NEON2RVV_TEST_IMPL::NEON2RVV_TEST_IMPL(void) {
  test_cases_float_pointer1 = (float *)platform_aligned_alloc(__riscv_v_elen);
  test_cases_float_pointer2 = (float *)platform_aligned_alloc(__riscv_v_elen);
  test_cases_int_pointer1 = (int32_t *)platform_aligned_alloc(__riscv_v_elen);
  test_cases_int_pointer2 = (int32_t *)platform_aligned_alloc(__riscv_v_elen);
  srand(0);
  for (uint32_t i = 0; i < MAX_TEST_VALUE; i++) {
    test_cases_floats[i] = ranf(-100000, 100000);
    test_cases_ints[i] = (int32_t)ranf(-100000, 100000);
  }
}

result_t NEON2RVV_TEST_IMPL::load_test_float_pointers(uint32_t i) {
  for (int i = 0; i < 4; i++) {
    test_cases_float_pointer1[i] = test_cases_floats[i];
    test_cases_float_pointer2[i + 4] = test_cases_floats[i + 4];
  }
  return TEST_SUCCESS;
}

result_t NEON2RVV_TEST_IMPL::load_test_int_pointers(uint32_t i) {
  for (int i = 0; i < 4; i++) {
    test_cases_int_pointer1[i] = test_cases_ints[i];
    test_cases_int_pointer2[i + 4] = test_cases_ints[i + 4];
  }
  return TEST_SUCCESS;
}

result_t NEON2RVV_TEST_IMPL::run_single_test(INSTRUCTION_TEST test,
                                             uint32_t i) {
  result_t ret = TEST_SUCCESS;

  switch (test) {
#define _(x)                                                                   \
  case it_##x:                                                                 \
    ret = test_##x(*this, i);                                                  \
    break;
    INTRIN_LIST
#undef _
  }

  return ret;
}

NEON2RVV_TEST *NEON2RVV_TEST::create(void) {
  NEON2RVV_TEST_IMPL *st = new NEON2RVV_TEST_IMPL;
  return static_cast<NEON2RVV_TEST *>(st);
}

} // namespace NEON2RVV
