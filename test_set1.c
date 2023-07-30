/* test_set1.c */
#include "cmylib.h"

void print(const char* s);

/* main */
int main(int argc, char* argv[]) {
  puts("test_set1.c");
  SetEntry** set = my_set_new();
  printf("set empty = %d, count = %d\n", my_set_empty(set), my_set_count(set));
  my_set_setitem(set, "AAA");
  my_set_setitem(set, "A");
  my_set_setitem(set, "AB");
  my_set_setitem(set, "CBA");
  if (my_set_exists(set, "A"))
    puts("\"A\" exists");
  if (my_set_exists(set, "X"))
    puts("\"X\" exists");
  my_set_foreach(set, print);

  puts("my_set_remove");  
  my_set_remove(set, "A");
  my_set_remove(set, "AB");
  my_set_foreach(set, print);

  // 終わり
  puts("Done.");
  return EXIT_SUCCESS;
}

void print(const char* s) {
    puts(s);  
}
