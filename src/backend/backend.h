#ifndef BACKEND_H
#define BACKEND_H

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ERROR_DIVISION_BY_ZERO 2
#define ERROR_ILLEGAL_ARGUMENT 3
#define ERROR_ILLEGAL_EXPRESSION 4

typedef struct Stack{
    char opt[7];
    int order;
    struct Stack * next;
} Stack;

typedef struct PL_Stack {
    char* str;
    double num;
    struct PL_Stack* next;
} PL_Stack;


/*принимает строку в инфиксном виде от пользователя*/
int calculate(char *expression, char ** result);

/*получение польской нотации из инфиксной*/
int _translate_to_rpn(char* expression, char ** result);

/*вычисление польской записи*/
int _calculate_rpn(char *expression, char **result);

/*парсинг математических операторов при вычислении результата польской записи*/
void _process_operation(const char* ptr, PL_Stack** current, int* status);

/*определение результата и парсинг ошибок при вычислении польской записи*/
void _calculate_result(PL_Stack* current, char** result, int status);

/*создание узла*/
Stack * _init_node(char * opt, int order);

/*Добавление узла в стек*/
void _push(Stack** top, char * opt, int order);

/*удаление элемента стека*/
void _pop(Stack** top);

/*начинается ли str на pre*/
bool _starts_with(const char *pre, const char *str);

/*схлопывание множественных пробелов*/
void _removeExtraSpaces(char *str);

/*перевод в польскую нотацию знака минус (унарного и бинарного)*/
void _process_minus(char* expression, int i, Stack** top, char** result);

/*перевод в польскую нотацию знака плюс*/
void _process_plus(char* expression, int i, Stack** top, char** result);

/*перевод в польскую нотацию знака умножение*/
void _process_mul(Stack** top, char** result);

/*перевод в польскую нотацию знака деления*/
void _process_div(Stack** top, char** result);

/*перевод в польскую нотацию знака возведения в степень*/
void _process_pow(Stack** top);

/*перевод в польскую нотацию acos asin и atan*/
int _process_a(char* expression, int* i, Stack** top);

/*перевод в польскую нотацию cos*/
int _process_c(char* expression, int* i, Stack** top);

/*перевод в польскую нотацию ln и log*/
int _process_l(char* expression, int* i, Stack** top);

/*перевод в польскую нотацию mod*/
int _process_m(char* expression, int* i, Stack** top);

/*перевод в польскую нотацию sqrt и sin*/
int _process_s(char* expression, int* i, Stack** top);

/*перевод в польскую нотацию tan*/
int _process_t(char* expression, int* i, Stack** top);

/*обработка чисел при переводе в польскую нотацию*/
int _process_num(char* expression, int* i, char** result);

/*обработка правой скобки при переводе в польскую нотацию*/
int _process_rb(Stack** top, char** result);

/*финальная очистка стека при переводе в польскую нотацию*/
int _free_stack(Stack** top, char** result);

/*Функции стека для польской математики*/

PL_Stack* _PL_push(PL_Stack** stk, char* str);

void _PL_pop(PL_Stack** stk);

PL_Stack* _PL_init(char* str);

void _PL_destroy(PL_Stack **root);

/*функции польской математики*/

/*сложение*/
PL_Stack *_plus(PL_Stack *current, int * status);

/*вычитание*/
PL_Stack *_minus(PL_Stack *current, int *status);

/*умножение*/
PL_Stack *_multi(PL_Stack *current, int *status);

/*деление*/
PL_Stack *_devide(PL_Stack *current, int * status);

/*возведение в степень*/
PL_Stack* _power(PL_Stack *current, int * status);

/*унарный минус*/
PL_Stack *_uniminus(PL_Stack *current, int *status);

/*арккосинус*/
PL_Stack *_acos(PL_Stack *current, int * status) ;

/*арксинус*/
PL_Stack *_asin(PL_Stack *current, int *status);

/*арктангенс*/
PL_Stack *_atan(PL_Stack *current, int * status);

/*косинус*/
PL_Stack *_cos(PL_Stack *current, int * status);

/*натуральный логарифм*/
PL_Stack *_ln(PL_Stack *current, int * status);

/*десятичный логарифм*/
PL_Stack *_log(PL_Stack *current, int *status);

/*получение остатка от деления*/
PL_Stack *_mod(PL_Stack *current, int *status);

/*получение квадратного корня*/
PL_Stack *_sqrt(PL_Stack *current, int *status);

/*получение синуса*/
PL_Stack *_sin(PL_Stack *current, int *status);

/*получение тангенса*/
PL_Stack *_tan(PL_Stack *current, int *status);

/*приводим в порядок строку результат, удаляем нули с конца*/
void _remove_trailing_zeros(char ** str);

/*является ли строка числом*/
int _is_number(char *ptr);

#ifdef __cplusplus
}
#endif

#endif