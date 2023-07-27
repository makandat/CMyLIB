/* test_fs1.c */
#include "my_filesystem.h"

/* main */
int main(int argc, char* argv[]) {
  puts("test_fs1.c");
  char* path = "/usr/bin/bash";
  if (argc > 1) {
    path = argv[1];
  }
  // ファイルの存在など
  printf("my_exists(\"%s\") = %s\n", path, my_exists(path) ? "true" : "false");
  printf("my_isfille(\"%s\") = %s\n", path, my_isfile(path) ? "true" : "false");
  printf("my_isdir(\"%s\") = %s\n", path, my_isdir(path) ? "true" : "false");
  printf("my_issymlink(\"%s\") = %s\n", path, my_issymlink(path) ? "true" : "false");
  if (my_isfile(path)) {
    // ファイルののみ属性
    printf("my_file_readable(\"%s\") = %s\n", path, my_file_readable(path) ? "true" : "false");
    printf("my_file_writable(\"%s\") = %s\n", path, my_file_writable(path) ? "true" : "false");
    printf("my_file_executable(\"%s\") = %s\n", path, my_file_executable(path) ? "true" : "false");
    printf("my_file_length(\"%s\") = %lu\n", path, my_file_length(path));
  }
  // ファイルのタイムスタンプ
  printf("my_file_time(\"%s\") = %lu\n", path, my_file_time(path));
  printf("my_file_strtime(\"%s\") = %s\n", path, my_file_strtime(path));
  // ファイルの所有者とグループ
  uid_t uid = my_file_owner(path);
  gid_t gid = my_file_group(path);
  printf("my_file_owner(\"%s\") = %d\n", path, uid);
  const char* username = my_getname(uid, false);
  printf("username = %s\n", username);
  printf("my_file_group(\"%s\") = %d\n", path, gid);
  const char* groupname = my_getname(gid, true);
  printf("groupname = %s\n", groupname);
  // ファイルシステム情報
  printf("my_pwd() = %s\n", my_pwd());
  printf("my_home() = %s\n", my_home());
  // 終わり
  puts("Done.");
  return EXIT_SUCCESS;
}
