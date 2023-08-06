/* test_stack2.c */
#include "cmylib.h"

/* main */
int main(int argc, char* argv) {
  int n;
  size_t size;
  int data[4] = {1234, 5678, 900, 130};
  puts("test_stack2.c");
  StackRoot* stack = my_stack_new();
  my_stack_push(stack, &data[0], sizeof(int));
  my_stack_push(stack, &data[1], sizeof(int));
  my_stack_push(stack, &data[2], sizeof(int));
  my_stack_push(stack, &data[3], sizeof(int));
  
  my_stack_first(stack, &n, &size);
  printf("my_stack_first = %d size = %lu\n", n, size);
  my_stack_next(stack, &n, &size);
  printf("my_stack_next = %d size = %lu\n", n, size);
  my_stack_last(stack, &n, &size);
  printf("my_stack_last = %d size = %lu\n", n, size);
  my_stack_prev(stack, &n, &size);
  printf("my_stack_prev = %d size = %lu\n", n, size);
  
  // End
  puts("Done.");
  return EXIT_SUCCESS;
}
