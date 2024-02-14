#include "../backend.h"

int _calculate_rpn(char *expression, char **result) {
  setlocale(LC_NUMERIC, "C");
  int status = 0;
  int len = strlen(expression);
  char *tmp = malloc(len * sizeof(expression));
  strcpy(tmp, expression);
  char *ptr = strtok(tmp, " ");
  PL_Stack *root = _PL_init(ptr);
  if (_is_number(ptr) == 0)
    status = ERROR_ILLEGAL_EXPRESSION;
  PL_Stack *current = root;
  while (ptr != NULL && status == 0) {
    ptr = strtok(NULL, " ");
    if (ptr != NULL && _is_number(ptr)) {
      _PL_push(&current, ptr);
    } else if (ptr != NULL) {
      _process_operation(ptr, &current, &status);
    }
  }
  _calculate_result(current, result, status);
  _PL_destroy(&root);
  free(tmp);
  return status;
}

void _process_operation(const char *ptr, PL_Stack **current, int *status) {
  if (strcmp(ptr, "+") == 0)
    *current = _plus(*current, status);
  else if (strcmp(ptr, "-") == 0)
    *current = _minus(*current, status);
  else if (strcmp(ptr, "*") == 0)
    *current = _multi(*current, status);
  else if (strcmp(ptr, "/") == 0)
    *current = _devide(*current, status);
  else if (strcmp(ptr, "^") == 0)
    *current = _power(*current, status);
  else if (strcmp(ptr, "~") == 0)
    *current = _uniminus(*current, status);
  else if (strcmp(ptr, "acos") == 0)
    *current = _acos(*current, status);
  else if (strcmp(ptr, "asin") == 0)
    *current = _asin(*current, status);
  else if (strcmp(ptr, "atan") == 0)
    *current = _atan(*current, status);
  else if (strcmp(ptr, "cos") == 0)
    *current = _cos(*current, status);
  else if (strcmp(ptr, "ln") == 0)
    *current = _ln(*current, status);
  else if (strcmp(ptr, "log") == 0)
    *current = _log(*current, status);
  else if (strcmp(ptr, "mod") == 0)
    *current = _mod(*current, status);
  else if (strcmp(ptr, "sqrt") == 0)
    *current = _sqrt(*current, status);
  else if (strcmp(ptr, "sin") == 0)
    *current = _sin(*current, status);
  else if (strcmp(ptr, "tan") == 0)
    *current = _tan(*current, status);
  else {
    *status = 1;
  }
}

void _calculate_result(PL_Stack *current, char **result, int status) {
  if (isinf(current->num)) {
    *result = strdup("Расчет невозможен");
  } else if (status == 0) {
    if (current->num > 1e+20) {
      *result = calloc(1000, sizeof(char));
      sprintf(*result, "%e", current->num);
    } else {
      *result = calloc(1000, sizeof(char));
      sprintf(*result, "%.7lf", current->num);
    }
    _remove_trailing_zeros(result);
  } else if (status == ERROR_DIVISION_BY_ZERO) {
    *result = strdup("Деление на ноль");
  } else if (status == ERROR_ILLEGAL_ARGUMENT) {
    *result = strdup("Некорректный аргумент");
  } else if (status == ERROR_ILLEGAL_EXPRESSION) {
    *result = strdup("Некорректное выражение");
  } else {
    *result = strdup("0");
  }
}

PL_Stack *_plus(PL_Stack *current, int *status) {
  if (current == NULL || current->next == NULL) {
    *status = ERROR_ILLEGAL_EXPRESSION;
  } else {
    double result = current->num + current->next->num;
    _PL_pop(&current);
    current->num = result;
  }
  return current;
}

PL_Stack *_minus(PL_Stack *current, int *status) {
  if (current == NULL || current->next == NULL) {
    *status = ERROR_ILLEGAL_EXPRESSION;
  } else {
    double result = current->next->num - current->num;
    _PL_pop(&current);
    current->num = result;
  }
  return current;
}

PL_Stack *_multi(PL_Stack *current, int *status) {
  if (current == NULL || current->next == NULL) {
    *status = ERROR_ILLEGAL_EXPRESSION;
  } else {
    double result = current->num * current->next->num;
    _PL_pop(&current);
    current->num = result;
  }
  return current;
}

PL_Stack *_devide(PL_Stack *current, int *status) {
  if (current == NULL || current->next == NULL) {
    *status = ERROR_ILLEGAL_EXPRESSION;
  } else if (current->num < 1e-7 && current->num > -1e-7) {
    *status = ERROR_DIVISION_BY_ZERO;
  } else {
    double result = current->next->num / current->num;
    _PL_pop(&current);
    current->num = result;
  }
  return current;
}

PL_Stack *_power(PL_Stack *current, int *status) {
  if (current == NULL || current->next == NULL) {
    *status = ERROR_ILLEGAL_EXPRESSION;
  } else {
    double result = pow(current->next->num, current->num);
    _PL_pop(&current);
    current->num = result;
  }
  return current;
}

PL_Stack *_uniminus(PL_Stack *current, int *status) {
  if (current == NULL) {
    *status = ERROR_ILLEGAL_EXPRESSION;
  } else {
    double result = current->num * -1;
    current->num = result;
  }
  return current;
}

PL_Stack *_acos(PL_Stack *current, int *status) {
  if (current == NULL) {
    *status = ERROR_ILLEGAL_EXPRESSION;
  } else if (current->num > 1 || current->num < -1) {
    *status = ERROR_ILLEGAL_ARGUMENT;
  } else {
    double result = acos(current->num);
    current->num = result;
  }
  return current;
}

PL_Stack *_asin(PL_Stack *current, int *status) {
  if (current == NULL) {
    *status = ERROR_ILLEGAL_EXPRESSION;
  } else if (current->num > 1 || current->num < -1) {
    *status = ERROR_ILLEGAL_ARGUMENT;
  } else {
    double result = asin(current->num);
    current->num = result;
  }
  return current;
}

PL_Stack *_atan(PL_Stack *current, int *status) {
  if (current == NULL) {
    *status = ERROR_ILLEGAL_EXPRESSION;
  } else {
    double result = atan(current->num);
    current->num = result;
  }
  return current;
}

PL_Stack *_cos(PL_Stack *current, int *status) {
  if (current == NULL) {
    *status = ERROR_ILLEGAL_EXPRESSION;
  } else {
    double result = cos(current->num);
    current->num = result;
  }
  return current;
}

PL_Stack *_ln(PL_Stack *current, int *status) {
  if (current == NULL) {
    *status = ERROR_ILLEGAL_EXPRESSION;
  } else if (current->num <= 1e-7) {
    *status = ERROR_ILLEGAL_ARGUMENT;
  } else {
    double result = log(current->num);
    current->num = result;
  }
  return current;
}

PL_Stack *_log(PL_Stack *current, int *status) {
  if (current == NULL) {
    *status = ERROR_ILLEGAL_EXPRESSION;
  } else if (current->num <= 1e-7) {
    *status = ERROR_ILLEGAL_ARGUMENT;
  } else {
    double result = log10(current->num);
    current->num = result;
  }
  return current;
}

PL_Stack *_mod(PL_Stack *current, int *status) {
  if (current == NULL || current->next == NULL) {
    *status = ERROR_ILLEGAL_EXPRESSION;
  } else {
    double result = fmod(current->next->num, current->num);
    _PL_pop(&current);
    current->num = result;
  }
  return current;
}

PL_Stack *_sqrt(PL_Stack *current, int *status) {
  if (current == NULL) {
    *status = ERROR_ILLEGAL_EXPRESSION;
  } else if (current->num < 0) {
    *status = ERROR_ILLEGAL_ARGUMENT;
  } else {
    double result = sqrt(current->num);
    current->num = result;
  }
  return current;
}

PL_Stack *_sin(PL_Stack *current, int *status) {
  if (current == NULL) {
    *status = ERROR_ILLEGAL_EXPRESSION;
  } else {
    double result = sin(current->num);
    current->num = result;
  }
  return current;
}

PL_Stack *_tan(PL_Stack *current, int *status) {
  if (current == NULL) {
    *status = ERROR_ILLEGAL_EXPRESSION;
  } else {
    double result = tan(current->num);
    current->num = result;
  }
  return current;
}

int _is_number(char *ptr) {
  int status = 1;
  int mem = 0;
  for (int i = 0; ptr[i] != '\0' && status == 1; i++) {
    if (ptr[i] == 'e' && (ptr[i + 1] == '-' || ptr[i + 1] == '+') && mem == 0) {
      i++;
      mem = 1;
      continue;
    } else if (isdigit(ptr[i]) == 0 && ptr[i] != '.')
      status = 0;
  }
  return status;
}

void _remove_trailing_zeros(char **str) {
  int len = strlen(*str);
  int i = len - 1;
  while ((*str)[i] == '0') {
    (*str)[i--] = '\0';
  }
  if ((*str)[i] == '.') {
    (*str)[i] = '\0';
  }
}