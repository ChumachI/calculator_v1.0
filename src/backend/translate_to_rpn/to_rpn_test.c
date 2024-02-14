#include "../_tests/tests.h"

START_TEST(translate_to_rpn_1) {
  char *expression = "sin(2*3.14)";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(rpn, "2 3.14 * sin");
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_2) {
  char *expression = "2+3";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(rpn, "2 3 +");
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_3) {
  char *expression = "4*5-6";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(rpn, "4 5 * 6 -");
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_4) {
  char *expression = "(1+2)*(3-4)";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(rpn, "1 2 + 3 4 - *");
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_5) {
  char *expression = "1+2-3*4/5";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(rpn, "1 2 + 3 4 * 5 / -");
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_6) {
  char *expression = "-5+-(-2)";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(rpn, "5 ~ 2 ~ ~ +");
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_7) {
  char *expression = "(-3+-4)*-2";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(rpn, "3 ~ 4 ~ + 2 ~ *");
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_8) {
  char *expression = "((2+3)*4)-5";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(rpn, "2 3 + 4 * 5 -");
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_9) {
  char *expression = "((1+2)*3)-(4*(5-6))";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(rpn, "1 2 + 3 * 4 5 6 - * -");
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_10) {
  char *expression = "cos(3.14/238)";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(rpn, "3.14 238 / cos");
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_11) {
  char *expression = "atan(1)+atan(1/2)";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(rpn, "1 atan 1 2 / atan +");
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_12) {
  char *expression = "ln(2.71828^3)";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(rpn, "2.71828 3 ^ ln");
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_13) {
  char *expression = "log(10)+log(1000)";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(rpn, "10 log 1000 log +");
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_14) {
  char *expression = "sqrt(16)+sqrt(9)";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(rpn, "16 sqrt 9 sqrt +");
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_15) {
  char *expression = "sin(3.14/4)+ln(2.71828^2)*atan(1)";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(rpn, "3.14 4 / sin 2.71828 2 ^ ln 1 atan * +");
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_16) {
  char *expression = "sqrt(4+sin(3.14/2))*(cos(3.14)-log(2.71828^3.10))";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(rpn,
                   "4 3.14 2 / sin + sqrt 3.14 cos 2.71828 3.10 ^ log - *");
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_17) {
  char *expression = "2mod3";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(rpn, "2 3 mod");
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_18) {
  char *expression = "log(sqrt(16))+tan(sin(3.14/4))";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(rpn, "16 sqrt log 3.14 4 / sin tan +");
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_19) {
  char *expression = "2+pi";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 1);
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_20) {
  char *expression = "(2+3";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 1);
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_21) {
  char *expression = "2+3)";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 1);
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_22) {
  char *expression = "2*sin(3^-4)";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(rpn, "2 3 4 ~ ^ sin *");
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_23) {
  char *expression = "2*sin(-3^4)";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(rpn, "2 3 4 ^ ~ sin *");
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_24) {
  char *expression = "asin(-3^4)";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(rpn, "3 4 ^ ~ asin");
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_25) {
  char *expression = "acos(-3^4)";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(rpn, "3 4 ^ ~ acos");
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_26) {
  char *expression = "actg(-3^4)";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 1);
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_27) {
  char *expression = "ctg(-3^4)";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 1);
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_28) {
  char *expression = "lag(-3^4)";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 1);
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_29) {
  char *expression = "mad(-3^4)";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 1);
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_30) {
  char *expression = "squt(-3^4)";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 1);
  free(rpn);
}
END_TEST

START_TEST(translate_to_rpn_31) {
  char *expression = "tag(-3^4)";
  char *rpn;
  int status = _translate_to_rpn(expression, &rpn);
  ck_assert_int_eq(status, 1);
  free(rpn);
}
END_TEST

Suite *suite_to_rpn() {
  Suite *s = suite_create("test_translate_to_rpn");
  TCase *tc = tcase_create("tc_translate_to_rpn");
  tcase_add_test(tc, translate_to_rpn_1);
  tcase_add_test(tc, translate_to_rpn_2);
  tcase_add_test(tc, translate_to_rpn_3);
  tcase_add_test(tc, translate_to_rpn_4);
  tcase_add_test(tc, translate_to_rpn_5);
  tcase_add_test(tc, translate_to_rpn_6);
  tcase_add_test(tc, translate_to_rpn_7);
  tcase_add_test(tc, translate_to_rpn_8);
  tcase_add_test(tc, translate_to_rpn_9);
  tcase_add_test(tc, translate_to_rpn_10);
  tcase_add_test(tc, translate_to_rpn_11);
  tcase_add_test(tc, translate_to_rpn_12);
  tcase_add_test(tc, translate_to_rpn_13);
  tcase_add_test(tc, translate_to_rpn_14);
  tcase_add_test(tc, translate_to_rpn_15);
  tcase_add_test(tc, translate_to_rpn_16);
  tcase_add_test(tc, translate_to_rpn_17);
  tcase_add_test(tc, translate_to_rpn_18);
  tcase_add_test(tc, translate_to_rpn_19);
  tcase_add_test(tc, translate_to_rpn_20);
  tcase_add_test(tc, translate_to_rpn_21);
  tcase_add_test(tc, translate_to_rpn_22);
  tcase_add_test(tc, translate_to_rpn_23);
  tcase_add_test(tc, translate_to_rpn_24);
  tcase_add_test(tc, translate_to_rpn_25);
  tcase_add_test(tc, translate_to_rpn_26);
  tcase_add_test(tc, translate_to_rpn_27);
  tcase_add_test(tc, translate_to_rpn_28);
  tcase_add_test(tc, translate_to_rpn_29);
  tcase_add_test(tc, translate_to_rpn_30);
  tcase_add_test(tc, translate_to_rpn_31);
  suite_add_tcase(s, tc);
  return s;
}