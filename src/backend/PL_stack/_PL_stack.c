#include "../backend.h"

PL_Stack *_PL_push(PL_Stack **stk, char *str) {
  PL_Stack *node = _PL_init(str);
  node->next = *stk;
  *stk = node;
  return node;
}

void _PL_pop(PL_Stack **stk) {
  PL_Stack *tmp = *stk;
  *stk = tmp->next;
  free(tmp);
}

PL_Stack *_PL_init(char *str) {
  PL_Stack *node = (PL_Stack *)malloc(sizeof(PL_Stack));
  if (NULL != node) {
    node->num = atof(str);
    node->str = str;
    node->next = NULL;
  }
  return node;
}

void _PL_destroy(PL_Stack **root) {
  if (NULL != root && NULL != *root) {
    PL_Stack *current = *root;
    PL_Stack *next = NULL;
    while (current != NULL) {
      next = current->next;
      free(current);
      current = next;
    }
    *root = NULL;
  }
}