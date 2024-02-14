#ifndef TESTS_H
#define TESTS_H
#include <check.h>

#include "../backend.h"

Suite * suite_to_rpn();
Suite * suite_calculate();
Suite *suite_calc_rpn();
#endif