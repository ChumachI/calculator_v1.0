#include "../backend.h"

// Инициализация узла списка
Stack *_init_node(char *opt, int order) {
  Stack *newNode = (Stack *)calloc(1, sizeof(Stack));
  strcat(newNode->opt, opt);
  newNode->order = order;
  newNode->next = NULL;
  return newNode;
}

// Добавление узла в начало списка (пуш)
void _push(Stack **top, char *opt, int order) {
  Stack *newNode = _init_node(opt, order);
  newNode->next = *top;
  *top = newNode;
}

// Удаление узла с начала списка (поп)
void _pop(Stack **top) {
  if (*top != NULL) {
    Stack *temp = *top;
    *top = (*top)->next;
    free(temp);
  }
}
