/* test_ixlist3.c */
#include "cmylib.h"

#define N 8
static int data[N] = {98, 870, -9, 77, 1066, 7098, 8, 665};

void print(void* data, size_t sz);

/* main */
int main(int argc, char* argv[]) {
  puts("test_ixlist3.c");
  // リストにデータを追加する。
  IxRoot* ixlist = my_ixlist_new();
  for (int i = 0; i < N; i++) {
    void* nv = &data[i];
    my_ixlist_setval(ixlist, nv, sizeof(int));
  }
  // foreach でリスト内容を表示する。
  my_ixlist_foreach(ixlist, print);
  
  // 終わり
  my_ixlist_free(ixlist);
  puts("Done.");
  return EXIT_SUCCESS;
}

/* コールバック関数 */
void print(void* data, size_t sz) {
  printf("%d, %lu\n", *(int*)data, sz);
}
