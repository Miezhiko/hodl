#pragma once

#include "hodl_types.h"

const double
get_value(const char* key) {
  const int fd = open(MEMORY_FILE, O_RDONLY);
  if (fd == -1) {
    perror("open");
    exit(1);
  }

  void* memory = mmap(NULL, sizeof(hodl_entry), PROT_READ, MAP_SHARED, fd, 0);
  if (memory == MAP_FAILED) {
    perror("mmap");
    exit(1);
  }

  const hodl_entry* entry = (hodl_entry*) memory;
  while (entry->key[0] != '\0' && strcmp(entry->key, key) != 0) {
    entry++;
  }

  const double value = entry->value;

  munmap(memory, sizeof(hodl_entry));
  close(fd);

  return value;
}
