/* test_list3.c */
#include "my_collections.h"

void print(void*, size_t);

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
  my_list_foreach(list, print);
  int n0 = 0;
  my_list_value(list, &n0);
  printf("n = %d\n", n0);
  my_list_free(list);
  puts("Done.");
  return EXIT_SUCCESS;
}

/* ペイロードをバイトごとに表示する。*/
void print(void* payload, size_t sz) {
  uint8_t* p = (uint8_t*)payload;
  for (int i = 0; i < (int)sz; i++) {
    printf("%02x ", *p++);
  }
  puts(";");
}
