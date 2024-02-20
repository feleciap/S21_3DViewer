#include "test.h"

void run_test(Suite *s, int *fail) {
  SRunner *runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  *fail = srunner_ntests_failed(runner);
  srunner_free(runner);
}

int main() {
  int num_of_fail = 0;
  run_test(test_file_parser(), &num_of_fail);
  // run_test(test_affine(), &num_of_fail);

  return num_of_fail == 0 ? 0 : 1;
}
