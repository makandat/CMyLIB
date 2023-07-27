/* test_fs3.c: ファイル入出力 */
#include "my_filesystem.h"

/* main */
int main(int argc, char* argv[]) {
  puts("test_fs3.c");
  char* path = "~/temp/test.txt";
  if (argc > 1) {
    path = argv[1];
  }
  // 書き込み
  my_file_write(path, "my_file_read\nmy_file_write\n");
  // 読み出し
  char* buf = my_file_read(path, 10000);
  if (buf == NULL) {
    fputs("Failed to read.\n", stderr);
    return EXIT_FAILURE;
  }
  printf("%s\n", buf);
  free(buf);
  // 終わり
  puts("Done.");
  return EXIT_SUCCESS;
}
