#include "../_tests/tests.h"

START_TEST(calculate_1) {
  char *expression = "sin(2*3.14)";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(result, "-0.0031853");
  free(result);
}
END_TEST

START_TEST(calculate_2) {
  char *expression = "2+3";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(result, "5");
  free(result);
}
END_TEST

START_TEST(calculate_3) {
  char *expression = "4*5-6";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(result, "14");
  free(result);
}
END_TEST

START_TEST(calculate_4) {
  char *expression = "(1+2)*(3-4)";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(result, "-3");
  free(result);
}
END_TEST

START_TEST(calculate_5) {
  char *expression = "1+2-3*4/5";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(result, "0.6");
  free(result);
}
END_TEST

START_TEST(calculate_6) {
  char *expression = "-5+-(-2)";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(result, "-3");
  free(result);
}
END_TEST

START_TEST(calculate_7) {
  char *expression = "(-3+-4)*-2";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(result, "14");
  free(result);
}
END_TEST

START_TEST(calculate_8) {
  char *expression = "((2+3)*4)-5";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(result, "15");
  free(result);
}
END_TEST

START_TEST(calculate_9) {
  char *expression = "((1+2)*3)-(4*(5-6))";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(result, "13");
  free(result);
}
END_TEST

START_TEST(calculate_10) {
  char *expression = "cos(3.14/238)";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(result, "0.999913");
  free(result);
}
END_TEST

START_TEST(calculate_11) {
  char *expression = "atan(1)+atan(1/2)";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(result, "1.2490458");
  free(result);
}
END_TEST

START_TEST(calculate_12) {
  char *expression = "ln(2.71828^3)";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(result, "2.999998");
  free(result);
}
END_TEST

START_TEST(calculate_13) {
  char *expression = "log(10)+log(1000)";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(result, "4");
  free(result);
}
END_TEST

START_TEST(calculate_14) {
  char *expression = "sqrt(16)+sqrt(9)";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(result, "7");
  free(result);
}
END_TEST

START_TEST(calculate_15) {
  char *expression = "sin(3.14/4)+ln(2.71828^2)*atan(1)";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(result, "2.2776205");
  free(result);
}
END_TEST

START_TEST(calculate_16) {
  char *expression = "sqrt(4+sin(3.14/2))*(cos(3.14)-log(2.71828^3.10))";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(result, "-5.2465101");
  free(result);
}
END_TEST

START_TEST(calculate_17) {
  char *expression = "2mod3";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(result, "2");
  free(result);
}
END_TEST

START_TEST(calculate_18) {
  char *expression = "log(sqrt(16))+tan(sin(3.14/4))";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(result, "1.4560833");
  free(result);
}
END_TEST

START_TEST(calculate_19) {
  char *expression = "2+pi";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 1);
  free(result);
}
END_TEST

START_TEST(calculate_20) {
  char *expression = "(2+3";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 1);
  free(result);
}
END_TEST

START_TEST(calculate_21) {
  char *expression = "2+3)";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 1);
  free(result);
}
END_TEST

START_TEST(calculate_22) {
  char *expression = "2*sin(3^-4)";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(result, "0.0246907");
  free(result);
}
END_TEST

START_TEST(calculate_23) {
  char *expression = "2*sin(-3^4)";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(result, "1.259776");
  free(result);
}
END_TEST

START_TEST(calculate_24) {
  char *expression = "asin(-3^4)";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, ERROR_ILLEGAL_ARGUMENT);
  free(result);
}
END_TEST

START_TEST(calculate_25) {
  char *expression = "acos(-3^4)";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, ERROR_ILLEGAL_ARGUMENT);
  free(result);
}
END_TEST

START_TEST(calculate_26) {
  char *expression = "actg(-3^4)";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 1);
  free(result);
}
END_TEST

START_TEST(calculate_27) {
  char *expression = "ctg(-3^4)";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 1);
  free(result);
}
END_TEST

START_TEST(calculate_28) {
  char *expression = "lag(-3^4)";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 1);
  free(result);
}
END_TEST

START_TEST(calculate_29) {
  char *expression = "mad(-3^4)";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 1);
  free(result);
}
END_TEST

START_TEST(calculate_30) {
  char *expression = "squt(-3^4)";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 1);
  free(result);
}
END_TEST

START_TEST(calculate_31) {
  char *expression = "tag(-3^4)";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 1);
  free(result);
}
END_TEST

START_TEST(calculate_32) {
  char *expression = "1/0";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, ERROR_DIVISION_BY_ZERO);
  ck_assert_str_eq(result, "Деление на ноль");
  free(result);
}
END_TEST

START_TEST(calculate_33) {
  char *expression = "100000000000000000000000^100000000000000000000000000000";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(result, "Расчет невозможен");
  free(result);
}
END_TEST

START_TEST(calculate_34) {
  char *expression = "1e+20*10";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 0);
  free(result);
}
END_TEST

START_TEST(calculate_35) {
  char *expression = "1e*20*10";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 1);
  free(result);
}
END_TEST

START_TEST(calculate_36) {
  char *expression = "acos(0.2)";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(result, "1.3694384");
  free(result);
}
END_TEST

START_TEST(calculate_37) {
  char *expression = "asin(0.2)";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_str_eq(result, "0.2013579");
  free(result);
}
END_TEST

START_TEST(calculate_38) {
  char *expression = "ln(0)";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, ERROR_ILLEGAL_ARGUMENT);
  ck_assert_str_eq(result, "Некорректный аргумент");
  free(result);
}
END_TEST

START_TEST(calculate_39) {
  char *expression = "log(0)";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, ERROR_ILLEGAL_ARGUMENT);
  ck_assert_str_eq(result, "Некорректный аргумент");
  free(result);
}
END_TEST

START_TEST(calculate_40) {
  char *expression = "sqrt(-1)";
  char *result;
  int status = calculate(expression, &result);
  ck_assert_int_eq(status, ERROR_ILLEGAL_ARGUMENT);
  ck_assert_str_eq(result, "Некорректный аргумент");
  free(result);
}
END_TEST

Suite *suite_calculate() {
  Suite *s = suite_create("test_calculate");
  TCase *tc = tcase_create("tc_calculate");
  tcase_add_test(tc, calculate_1);
  tcase_add_test(tc, calculate_2);
  tcase_add_test(tc, calculate_3);
  tcase_add_test(tc, calculate_4);
  tcase_add_test(tc, calculate_5);
  tcase_add_test(tc, calculate_6);
  tcase_add_test(tc, calculate_7);
  tcase_add_test(tc, calculate_8);
  tcase_add_test(tc, calculate_9);
  tcase_add_test(tc, calculate_10);
  tcase_add_test(tc, calculate_11);
  tcase_add_test(tc, calculate_12);
  tcase_add_test(tc, calculate_13);
  tcase_add_test(tc, calculate_14);
  tcase_add_test(tc, calculate_15);
  tcase_add_test(tc, calculate_16);
  tcase_add_test(tc, calculate_17);
  tcase_add_test(tc, calculate_18);
  tcase_add_test(tc, calculate_19);
  tcase_add_test(tc, calculate_20);
  tcase_add_test(tc, calculate_21);
  tcase_add_test(tc, calculate_22);
  tcase_add_test(tc, calculate_23);
  tcase_add_test(tc, calculate_24);
  tcase_add_test(tc, calculate_25);
  tcase_add_test(tc, calculate_26);
  tcase_add_test(tc, calculate_27);
  tcase_add_test(tc, calculate_28);
  tcase_add_test(tc, calculate_29);
  tcase_add_test(tc, calculate_30);
  tcase_add_test(tc, calculate_31);
  tcase_add_test(tc, calculate_32);
  tcase_add_test(tc, calculate_33);
  tcase_add_test(tc, calculate_34);
  tcase_add_test(tc, calculate_35);
  tcase_add_test(tc, calculate_36);
  tcase_add_test(tc, calculate_37);
  tcase_add_test(tc, calculate_38);
  tcase_add_test(tc, calculate_39);
  tcase_add_test(tc, calculate_40);

  suite_add_tcase(s, tc);
  return s;
}