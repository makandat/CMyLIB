/* test_fs2.c: パス */
#include "my_filesystem.h"
#pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"

/* main */
int main(int argc, char* argv[]) {
  puts("test_fs2.c");
  char* path = "/usr/bin/vim";
  if (argc > 1) {
    path = argv[1];
  }
  MY_HEAP const char* ext = my_file_ext(path);
  printf("my_file_ext(\"%s\") = \"%s\"\n", path, ext);
  free(ext);
  MY_HEAP const char* filename = my_file_filename(path);
  printf("my_file_filename(\"%s\") = %s\n", path, filename);
  free(filename);
  MY_HEAP const char* dir = my_file_dir(path);
  printf("my_file_dir(\"%s\") = %s\n", path, dir);
  free(dir);
  MY_HEAP const char* newpath = my_file_append("/home/user", "temp/path.a");
  printf("my_file_dir(\"%s\") = %s\n", path, newpath);
  free(newpath);
  const char* abspath = my_file_absolute("../");
  printf("my_file_absolute(\"../\") = %s\n", abspath);
  // 終わり
  puts("Done.");
  return EXIT_SUCCESS;
}
