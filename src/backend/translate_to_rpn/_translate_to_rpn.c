#include "../backend.h"

int _translate_to_rpn(char *expression, char **result) {
  int status = 0;
  int exit = 0;
  *result = calloc(2000, sizeof(char));
  Stack *root = calloc(1, sizeof(Stack));
  Stack *top = root;
  for (int i = 0; expression[i] != '\0' && status == 0 && exit == 0; i++) {
    status = _process_num(expression, &i, result);
    switch (expression[i]) {
    case '-':
      _process_minus(expression, i, &top, result);
      break;
    case '+':
      _process_plus(expression, i, &top, result);
      break;
    case '*':
      _process_mul(&top, result);
      break;
    case '/':
      _process_div(&top, result);
      break;
    case '^':
      _process_pow(&top);
      break;
    case 'a':
      status = _process_a(expression, &i, &top);
      break;
    case 'c':
      status = _process_c(expression, &i, &top);
      break;
    case 'l':
      status = _process_l(expression, &i, &top);
      break;
    case 'm':
      status = _process_m(expression, &i, &top);
      break;
    case 's':
      status = _process_s(expression, &i, &top);
      break;
    case 't':
      status = _process_t(expression, &i, &top);
      break;
    case '(':
      _push(&top, " ( ", 0);
      break;
    case ')':
      status = _process_rb(&top, result);
      break;
    case '\0':
      exit = 1;
      break;
    default:
      status = 1;
    }
  }
  if (status == 0)
    status = _free_stack(&top, result);
  else
    _free_stack(&top, result);
  _removeExtraSpaces(*result);
  return status;
}

int _free_stack(Stack **top, char **result) {
  int status = 0;
  while ((*top)->opt != NULL) {
    if (strcmp((*top)->opt, " ( ") == 0 || strcmp((*top)->opt, " ) ") == 0) {
      status = 1;
    }
    strcat(*result, (*top)->opt);
    _pop(top);
  }
  return status;
}

int _process_rb(Stack **top, char **result) {
  int status = 0;
  while ((*top != NULL) && strcmp((*top)->opt, " ( ")) {
    strcat(*result, (*top)->opt);
    _pop(top);
  }
  if (((*top) != NULL) && strcmp((*top)->opt, " ( ") == 0) {
    _pop(top);
  } else {
    status = 1;
  }
  return status;
}

int _process_num(char *expression, int *i, char **result) {
  int status = 0;
  int n = 0;

  while (isdigit(expression[*i]) || expression[*i] == '.' ||
         expression[*i] == 'e') {
    if (expression[*i] == 'e') {
      if ((expression[(*i) + 1] == '-' || expression[(*i) + 1] == '+') &&
          isdigit(expression[(*i) - 1]) && isdigit(expression[(*i) + 2])) {
        (*i)++;
        n++;
      } else {
        status = 1;
      }
    }
    n++;
    (*i)++;
  }
  strncat(*result, &expression[(*i) - n], n);
  if (n)
    strcat(*result, " ");
  return status;
}

bool _starts_with(const char *pre, const char *str) {
  return strncmp(pre, str, strlen(pre)) == 0;
}

void _removeExtraSpaces(char *str) {
  bool foundSpace = false;
  char *dst = str;
  for (size_t i = 0; str[i] != '\0'; i++) {
    if (isspace(str[i])) {
      if (!foundSpace) {
        foundSpace = true;
        *dst++ = ' ';
      }
    } else {
      foundSpace = false;
      *dst++ = str[i];
    }
  }
  while (dst > str && isspace(*(dst - 1))) {
    dst--;
  }
  *dst = '\0';
}

void _process_minus(char *expression, int i, Stack **top, char **result) {
  if (isdigit(expression[i - 1]) || expression[i - 1] == ')') {
    while (*top && (*top)->order >= 1) {
      strcat(*result, (*top)->opt);
      _pop(top);
    }
    _push(top, " - ", 1);
  } else {
    _push(top, " ~ ", 3);
  }
}

void _process_plus(char *expression, int i, Stack **top, char **result) {
  if (isdigit(expression[i - 1]) || expression[i - 1] == ')') {
    while (*top && (*top)->order >= 1) {
      strcat(*result, (*top)->opt);
      _pop(top);
    }
    _push(top, " + ", 1);
  }
}

void _process_mul(Stack **top, char **result) {
  while (*top && (*top)->order >= 2) {
    strcat(*result, (*top)->opt);
    _pop(top);
  }
  _push(top, " * ", 2);
}

void _process_div(Stack **top, char **result) {
  while (*top && (*top)->order >= 2) {
    strcat(*result, (*top)->opt);
    _pop(top);
  }
  _push(top, " / ", 2);
}

void _process_pow(Stack **top) { _push(top, " ^ ", 3); }

int _process_a(char *expression, int *i, Stack **top) {
  int status = 0;
  if (_starts_with("acos", &expression[*i])) {
    _push(top, " acos ", 5);
    (*i) += 3;
  } else if (_starts_with("asin", &expression[*i])) {
    _push(top, " asin ", 5);
    (*i) += 3;
  } else if (_starts_with("atan", &expression[*i])) {
    _push(top, " atan ", 5);
    (*i) += 3;
  } else {
    status = 1;
  }
  return status;
}

int _process_c(char *expression, int *i, Stack **top) {
  int status = 0;
  if (_starts_with("cos", &expression[*i])) {
    _push(top, " cos ", 5);
    (*i) += 2;
  } else {
    status = 1;
  }
  return status;
}

int _process_l(char *expression, int *i, Stack **top) {
  int status = 0;
  if (_starts_with("ln", &expression[*i])) {
    _push(top, " ln ", 5);
    (*i) += 1;
  } else if (_starts_with("log", &expression[*i])) {
    _push(top, " log ", 5);
    (*i) += 2;
  } else {
    status = 1;
  }
  return status;
}

int _process_m(char *expression, int *i, Stack **top) {
  int status = 0;
  if (_starts_with("mod", &expression[*i])) {
    _push(top, " mod ", 2);
    (*i) += 2;
  } else {
    status = 1;
  }
  return status;
}

int _process_s(char *expression, int *i, Stack **top) {
  int status = 0;
  if (_starts_with("sqrt", &expression[*i])) {
    _push(top, " sqrt ", 5);
    (*i) += 3;
  } else if (_starts_with("sin", &expression[*i])) {
    _push(top, " sin ", 5);
    (*i) += 2;
  } else {
    status = 1;
  }
  return status;
}

int _process_t(char *expression, int *i, Stack **top) {
  int status = 0;
  if (_starts_with("tan", &expression[*i])) {
    _push(top, " tan ", 5);
    (*i) += 2;
  } else {
    status = 1;
  }
  return status;
}