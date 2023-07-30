/* test_quque1.c */
#include "cmylib.h"

/* main */
int main(int argc, char* argv[]) {
  char buff[100];
  size_t size;
  puts("test_queue1.c");
  QueueRoot* queue = my_queue_new();
  if (my_queue_empty(queue))
    puts("queue empty");
  else
    puts("queue not empty");
  my_queue_push(queue, "1234", 5);
  my_queue_push(queue, "5678", 5);
  my_queue_push(queue, "9ABC", 5);
  my_queue_push(queue, "DEF0", 5);
  my_queue_peek(queue, buff, &size);
  printf("peek \"%s\", %lu\n", buff, size);

  while (my_queue_deque(queue, buff, &size)) {
      printf("deque \"%s\", %lu\n", buff, size);
  }

  // 終わり
  puts("Done.");
  return EXIT_SUCCESS;
}
