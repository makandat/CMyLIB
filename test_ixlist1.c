/* test_ixlist1.c */
#include "cmylib.h"

/* main */
int main(int argc, char* argv[]) {
  puts("test_ixlist1.c");
  // リストにデータを追加する。
  IxRoot* ixlist = my_ixlist_new();
  my_ixlist_setval(ixlist, "ABC", 4);
  my_ixlist_setval(ixlist, "xxxx", 5);
  my_ixlist_setval(ixlist, "0245", 5);
  my_ixlist_setval(ixlist, "abc", 4);
  // リストを順にたどってデータを表示する。
  IxCell* cell = my_ixlist_first(ixlist);
  while (cell != NULL) {
    printf("\"%s\"\n", (char*)(cell->payload));
    cell = my_ixlist_next(ixlist);
  }
  // インデックスのダンプ表示
  my_ixlist_dump_indexes(ixlist);
  // 終わり
  puts("Done.");
  return EXIT_SUCCESS;
}
