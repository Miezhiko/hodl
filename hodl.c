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
store_value(const char* key, double value) {
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

  hodl_entry* entry = (hodl_entry*) memory;
  while (entry->key[0] != '\0' && strcmp(entry->key, key) != 0) {
    entry++;
  }

  const double value = entry->value;

  munmap(memory, sizeof(hodl_entry));
  close(fd);

  return value;
}

int
main(int argc, char* argv[]) {
  struct stat sb;
  if (stat(MEMORY_FILE, &sb) == -1) {
    init_file();
  }

  if (argc == 3) {
    store_value(argv[1], atof(argv[2]));
  } else if (argc == 2) {
    const double value = get_value(argv[1]);
    printf("%f\n", value);
  } else {
    printf("Usage: %s <key> [<value>]\n", argv[0]);
    return 1;
  }

  return 0;
}
