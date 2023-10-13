#include "binding.h"

#include <stdio.h>
#include <stdlib.h>

namespace NEON2RVV {
void *platform_aligned_alloc(size_t size) {
  void *address;
#if defined(_WIN32)
  address = _aligned_malloc(size, 16);
#else
  // FIXME
  // int ret = posix_memalign(&address, 16, size);
  address = malloc(size);
#endif
  if (!address) {
    fprintf(stderr, "Error at File %s line number %d\n", __FILE__, __LINE__);
    exit(EXIT_FAILURE);
  }
  return address;
}

void platform_aligned_free(void *ptr) {
#if defined(_WIN32)
  _aligned_free(ptr);
#else
  free(ptr);
#endif
}

}  // namespace NEON2RVV
