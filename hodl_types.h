#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/mman.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <unistd.h>

#define MEMORY_FILE "/tmp/hodl_memory"
#define MAX_KEY_LENGTH 256
#define MAX_VALUE_LENGTH 256
#define FILE_MODE 0644

typedef struct {
  char key[MAX_KEY_LENGTH];
  double value;
} hodl_entry;
