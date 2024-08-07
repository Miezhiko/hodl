#include "hodl_types.h"
#include "hodl_write.h"
#include "hodl_read.h"

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
