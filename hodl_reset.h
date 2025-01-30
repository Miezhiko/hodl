#pragma once

#include "hodl_types.h"

void reset() {
  if (unlink(MEMORY_FILE) == -1) {
    perror("unlink");
    exit(1);
  }

  printf("MEMORY_FILE '%s' has been safely removed.\n", MEMORY_FILE);
}
