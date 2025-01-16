#pragma once

#include "hodl_types.h"

void
list_values(void) {
  const int fd = open(MEMORY_FILE, O_RDONLY);
  if (fd == -1) {
    perror("open");
    exit(1);
  }

  const size_t hold_entry_size = sizeof(hodl_entry);
  const off_t fileSize = lseek(fd, 0, SEEK_END);

  if (fileSize == -1) {
    perror("lseek");
    exit(1);
  }
  lseek(fd, 0, SEEK_SET);

  const size_t numEntries = fileSize / hold_entry_size;
  void* memory = mmap(NULL, hold_entry_size, PROT_READ, MAP_SHARED, fd, 0);
  if (memory == MAP_FAILED) {
    perror("mmap");
    exit(1);
  }

  const hodl_entry* entry = (hodl_entry*) memory;

  int maxKeyLength = 0;
  for (size_t i = 0; i < numEntries; i++) {
    if (entry[i].key[0] == '\0') break;
    const size_t keyLen = strlen(entry[i].key);
    maxKeyLength = keyLen > maxKeyLength
                 ? keyLen : maxKeyLength;
  }

  for (size_t i = 0; i < numEntries; i++) {
    if (entry[i].key[0] == '\0') break;
    printf("%-*s : %f\n", maxKeyLength, entry[i].key, entry[i].value);
  }

  munmap(memory, sizeof(hodl_entry));
  close(fd);
}
