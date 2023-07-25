/* test_list1.c */
#include "my_collections.h"

/* main */
int main(int argc, char* argv[]) {
  puts("test_list1.c");
  ListRoot* list = my_list_new();
  my_list_append(list, "ABC", 4);
  my_list_append(list, "defgh", 6);
  my_list_append(list, "1234", 5);
  printf("count=%d\n", list->count);
  for (int i = 0; i < list->count; i++) {
    printf("%d '%s'\n", i, (char*)list->current->payload);
    list->current = list->current->next;
  }
  my_list_free(list);
  puts("Done.");
  return EXIT_SUCCESS;
}
