/* test_ixlist2.c */
#include "cmylib.h"

#define N 5
static int data[N] = {112, -50, 1009, 6548, 63};

/* main */
int main(int argc, char* argv[]) {
  puts("test_ixlist2.c");
  // リストにデータを追加する。
  IxRoot* ixlist = my_ixlist_new();
  for (int i = 0; i < N; i++) {
    void* nv = &data[i];
    my_ixlist_setval(ixlist, nv, sizeof(int));
  }
  // リスト内容を表示する。
  int n = my_ixlist_count(ixlist);
  int* vp;
  for (int i = 0; i < n; i++) {
    vp = (int*)my_ixlist_getval(ixlist, i);
    printf("ixlist[%d] = %d\n", i, *vp);
  }
  // 終わり
  my_ixlist_free(ixlist);
  puts("Done.");
  return EXIT_SUCCESS;
}
