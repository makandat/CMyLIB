/* test_list2.c */
#include "my_collections.h"

/* main */
int main(int argc, char* argv[]) {
  int numbers[4] = {6701, 5500, 80186, 9090};
  puts("test_list2.c");
  ListRoot* list = my_list_new();
  int n = sizeof(numbers) / sizeof(int);
  for (int i = 0; i < n; i++) {
    my_list_append(list, &numbers[i], sizeof(int));
  }
  printf("count=%d\n", list->count);
  ListCell* cell = (ListCell*)my_list_first(list);
  while (cell != NULL) {
    int* pn = (int*)cell->payload;
    printf("%d\n", *pn);
    cell = (ListCell*)my_list_next(list);
  }
  my_list_free(list);
  puts("Done.");
  return EXIT_SUCCESS;
}
