#include "tests.h"

int main() {
  int number_failed;
  Suite *to_rpn, *calc, *calc_rpn;
  to_rpn = suite_to_rpn();
  calc = suite_calculate();
  calc_rpn = suite_calc_rpn();
  SRunner *sr = srunner_create(to_rpn);
  srunner_add_suite(sr, calc);
  srunner_add_suite(sr, calc_rpn);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed == 0 ? 0 : 1;
}
