#include "hodl_types.h"
#include "hodl_write.h"
#include "hodl_read.h"
#include "hodl_list.h"
#include "hodl_reset.h"

void
usage(char* appName) {
  printf("Usage:\n%s <key> [<value>] : to store or read value\n\
 --list to list all values\n\
 --reset to remove memory file\n\n\
 --help to show this help\n", appName);
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
    if (strcmp(argv[1], "--list") == 0) {
      list_values();
    } else if (strcmp(argv[1], "--reset") == 0) {
      reset();
    } else if (strcmp(argv[1], "--help") == 0) {
      usage(argv[0]);
    } else {
      const double value = get_value(argv[1]);
      printf("%f\n", value);
    }
  } else {
    usage(argv[0]);
  }

  return 0;
}
