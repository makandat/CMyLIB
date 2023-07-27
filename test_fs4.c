/* test_fs4.c: ディレクトリ内のオブジェクト一覧 */
#include "my_filesystem.h"

#define N 1024
void print(struct dirent* entry);

/* main */
int main(int argc, char* argv[]) {
  puts("test_fs4.c");
  char* path = "/usr/lib/python3.11/json";
  if (argc > 1) {
    path = argv[1];
  }
  // ディレクトリ内の項目一覧を得る。
  DirentList entlist1;
  my_dir_entries(&entlist1, path);
  my_dir_foreach(&entlist1, print);
  puts("");
  // 一覧を配列に変換
  DirEntryCell* entries[N];
  int n = my_dir_toarray(&entlist1, entries, N);
  for (int i = 0; i < n; i++) {
    puts(entries[i]->dir_entry->d_name);
  }
  puts("");
  // 再帰的にディレクトリ内の項目一覧を得る。
  DirentList entlist2;
  my_dir_recursive(&entlist2, path);
  my_dir_foreach(&entlist2, print);
  // 終わり
  puts("Done.");
  return EXIT_SUCCESS;
}

/* entry を表示する。 */
void print(struct dirent* entry) {
  printf("* %s\n", entry->d_name);
}
