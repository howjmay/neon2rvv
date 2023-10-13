#include <stdint.h>
#include <stdio.h>
#include "impl.h"

int main(int /*argc*/, const char ** /*argv*/) {
  NEON2RVV::NEON2RVV_TEST *test = NEON2RVV::NEON2RVV_TEST::create();
  uint32_t pass_count = 0;
  uint32_t failed_count = 0;
  uint32_t ignore_count = 0;
  for (uint32_t i = 0; i < NEON2RVV::it_last; i++) {
    NEON2RVV::INSTRUCTION_TEST test_iter = NEON2RVV::INSTRUCTION_TEST(i);
    NEON2RVV::result_t ret = test->run_test(test_iter);
    // If the test fails, we will run it again so we can step into the
    // debugger and figure out why!
    if (ret == NEON2RVV::TEST_FAIL) {
      printf("Test %-30s failed\n", NEON2RVV::instruction_string[test_iter]);
      failed_count++;
    } else if (ret == NEON2RVV::TEST_UNIMPL) {
      printf("Test %-30s skipped\n", NEON2RVV::instruction_string[test_iter]);
      ignore_count++;
    } else {
      printf("Test %-30s passed\n", NEON2RVV::instruction_string[test_iter]);
      pass_count++;
    }
  }
  test->release();
  printf(
      "NEON2RVV_TEST Complete!\n"
      "Passed:  %d\n"
      "Failed:  %d\n"
      "Ignored: %d\n"
      "Coverage rate: %.2f%%\n",
      pass_count, failed_count, ignore_count, (float)pass_count / (pass_count + failed_count + ignore_count) * 100);

  return failed_count ? -1 : 0;
}
