#pragma once

#include "hodl_types.h"

void
init_file() {
  const int fd = open(MEMORY_FILE, O_RDWR | O_CREAT, FILE_MODE);
  if (fd == -1) {
    perror("open");
    exit(1);
  }

  const int ft = ftruncate(fd, sysconf(_SC_PAGESIZE));
  if (ft == -1) {
    perror("ftruncate");
    exit(1);
  }

  close(fd);
}

void
store_value(const char* key, const double value) {
  const int fd = open(MEMORY_FILE, O_RDWR, FILE_MODE);
  if (fd == -1) {
    perror("open");
    exit(1);
  }

  void* memory = mmap(NULL, sizeof(hodl_entry), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (memory == MAP_FAILED) {
    perror("mmap");
    exit(1);
  }

  hodl_entry* entry = (hodl_entry*) memory;
  while (entry->key[0] != '\0' && strcmp(entry->key, key) != 0) {
    entry++;
  }

  strcpy(entry->key, key);
  entry->value = value;

  munmap(memory, sizeof(hodl_entry));
  close(fd);
}
