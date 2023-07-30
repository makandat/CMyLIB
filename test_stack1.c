/* test_stack1.c */
#include "cmylib.h"

/* main */
int main(int argc, char* argv[]) {
  char buff[100];
  size_t size;
  puts("test_stack1.c");
  StackRoot* stack = my_stack_new();
  if (my_stack_empty(stack))
    puts("stack empty");
  else
    puts("stack not empty");
  my_stack_push(stack, "1234", 5);
  my_stack_push(stack, "5678", 5);
  my_stack_push(stack, "9ABC", 5);
  my_stack_push(stack, "DEF0", 5);
  my_stack_peek(stack, buff, &size);
  printf("peek \"%s\", %lu\n", buff, size);

  while (my_stack_pop(stack, buff, &size)) {
      printf("pop \"%s\", %lu\n", buff, size);
  }
  // 終わり
  puts("Done.");
  return EXIT_SUCCESS;
}
