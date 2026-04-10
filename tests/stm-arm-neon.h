/*
 * Shim header used by the arm-neon-tests suite when building on non-ARM
 * platforms.  Redirect to neon2rvv so the test harness exercises our RVV
 * implementation rather than native ARM NEON.
 */
#include "../neon2rvv.h"
