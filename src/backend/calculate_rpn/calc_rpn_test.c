#include "../_tests/tests.h"

START_TEST(calculate_rpn_1) {
  char *expression = "a+b";
  char *rpn;
  int status = _calculate_rpn(expression, &rpn);
  ck_assert_int_eq(status, ERROR_ILLEGAL_EXPRESSION);
  free(rpn);
}
END_TEST

START_TEST(calculate_rpn_2) {
  int status;
  _process_operation("aran", NULL, &status);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(calculate_rpn_3) {
  char *expression = "a+b";
  int status = 5;
  PL_Stack *current = _PL_init("10");
  _calculate_result(current, &expression, status);
  ck_assert_str_eq(expression, "0");
  free(expression);
  _PL_destroy(&current);
}
END_TEST

START_TEST(calculate_rpn_4) {
  char *expression = "10 +";
  char *result;
  int status = _calculate_rpn(expression, &result);
  ck_assert_int_eq(status, ERROR_ILLEGAL_EXPRESSION);
  free(result);
}
END_TEST

START_TEST(calculate_rpn_5) {
  char *expression = "10 -";
  char *result;
  int status = _calculate_rpn(expression, &result);
  ck_assert_int_eq(status, ERROR_ILLEGAL_EXPRESSION);
  free(result);
}
END_TEST

START_TEST(calculate_rpn_6) {
  char *expression = "10 *";
  char *result;
  int status = _calculate_rpn(expression, &result);
  ck_assert_int_eq(status, ERROR_ILLEGAL_EXPRESSION);
  free(result);
}
END_TEST

START_TEST(calculate_rpn_7) {
  char *expression = "10 /";
  char *result;
  int status = _calculate_rpn(expression, &result);
  ck_assert_int_eq(status, ERROR_ILLEGAL_EXPRESSION);
  free(result);
}
END_TEST

START_TEST(calculate_rpn_8) {
  char *expression = "10 ^";
  char *result;
  int status = _calculate_rpn(expression, &result);
  ck_assert_int_eq(status, ERROR_ILLEGAL_EXPRESSION);
  free(result);
}
END_TEST

START_TEST(calculate_rpn_9) {
  int status = 0;
  _uniminus(NULL, &status);
  ck_assert_int_eq(status, ERROR_ILLEGAL_EXPRESSION);
}
END_TEST

START_TEST(calculate_rpn_10) {
  int status = 0;
  _acos(NULL, &status);
  ck_assert_int_eq(status, ERROR_ILLEGAL_EXPRESSION);
}
END_TEST

START_TEST(calculate_rpn_11) {
  int status = 0;
  _asin(NULL, &status);
  ck_assert_int_eq(status, ERROR_ILLEGAL_EXPRESSION);
}
END_TEST

START_TEST(calculate_rpn_12) {
  int status = 0;
  _atan(NULL, &status);
  ck_assert_int_eq(status, ERROR_ILLEGAL_EXPRESSION);
}
END_TEST

START_TEST(calculate_rpn_13) {
  int status = 0;
  _cos(NULL, &status);
  ck_assert_int_eq(status, ERROR_ILLEGAL_EXPRESSION);
}
END_TEST

START_TEST(calculate_rpn_14) {
  int status = 0;
  _ln(NULL, &status);
  ck_assert_int_eq(status, ERROR_ILLEGAL_EXPRESSION);
}
END_TEST

START_TEST(calculate_rpn_15) {
  int status = 0;
  _log(NULL, &status);
  ck_assert_int_eq(status, ERROR_ILLEGAL_EXPRESSION);
}
END_TEST

START_TEST(calculate_rpn_16) {
  char *expression = "10 mod";
  char *result;
  int status = _calculate_rpn(expression, &result);
  ck_assert_int_eq(status, ERROR_ILLEGAL_EXPRESSION);
  free(result);
}
END_TEST

START_TEST(calculate_rpn_17) {
  int status = 0;
  _tan(NULL, &status);
  ck_assert_int_eq(status, ERROR_ILLEGAL_EXPRESSION);
}
END_TEST

START_TEST(calculate_rpn_18) {
  int status = 0;
  _sin(NULL, &status);
  ck_assert_int_eq(status, ERROR_ILLEGAL_EXPRESSION);
}
END_TEST

START_TEST(calculate_rpn_19) {
  int status = 0;
  _sqrt(NULL, &status);
  ck_assert_int_eq(status, ERROR_ILLEGAL_EXPRESSION);
}
END_TEST

// START_TEST(calculate_rpn_20) {
//   PL_Stack *root = _PL_init("10");
//   PL_Stack *current = root;
//   _PL_push(&current, "11");
//   _PL_push(&current, "12");
//   _PL_destroy(&current);
//   ck_assert_ptr_null(root);
//   ck_assert_ptr_null(current);
// }
// END_TEST

Suite *suite_calc_rpn() {
  Suite *s = suite_create("test_calculate_rpn");
  TCase *tc = tcase_create("tc_calculate_rpn");
  tcase_add_test(tc, calculate_rpn_1);
  tcase_add_test(tc, calculate_rpn_2);
  tcase_add_test(tc, calculate_rpn_3);
  tcase_add_test(tc, calculate_rpn_4);
  tcase_add_test(tc, calculate_rpn_5);
  tcase_add_test(tc, calculate_rpn_6);
  tcase_add_test(tc, calculate_rpn_7);
  tcase_add_test(tc, calculate_rpn_8);
  tcase_add_test(tc, calculate_rpn_9);
  tcase_add_test(tc, calculate_rpn_10);
  tcase_add_test(tc, calculate_rpn_11);
  tcase_add_test(tc, calculate_rpn_12);
  tcase_add_test(tc, calculate_rpn_13);
  tcase_add_test(tc, calculate_rpn_14);
  tcase_add_test(tc, calculate_rpn_15);
  tcase_add_test(tc, calculate_rpn_16);
  tcase_add_test(tc, calculate_rpn_17);
  tcase_add_test(tc, calculate_rpn_18);
  tcase_add_test(tc, calculate_rpn_19);
  // tcase_add_test(tc, calculate_rpn_20);

  suite_add_tcase(s, tc);
  return s;
}