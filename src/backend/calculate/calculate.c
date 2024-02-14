#include "../backend.h"

int calculate(char *expression, char **result) {
  int status = 0;
  char *rpn = NULL;
  status = _translate_to_rpn(expression, &rpn);
  if (status == 0)
    status = _calculate_rpn(rpn, result);
  else {
    *result = strdup("Некорректное выражение");
    free(rpn); // Освобождение памяти для rpn в случае ошибки
    rpn = NULL;
  }
  if (rpn != NULL)
    free(rpn); // Освобождение памяти для rpn в случае успешного результата
  return status;
}