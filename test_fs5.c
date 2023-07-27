/* test_fs5.c */
#include "cmylib.h"

#define SRC "/home/makandat/.bashrc"
#define DST "/home/makandat/temp/bashrc"

/* main */
int main(int argc, char* argv[]) {
  puts("test_fs5.c");
  if (argc == 1) {
    puts("Usage: test_fs5 test_number");
    return EXIT_FAILURE;
  }
  int code = my_stoi(argv[1]);
  bool b;
  switch (code) {
  case 1: // copy
    b = my_copy(SRC, DST, true);
    break;
  case 2: // rename, chdir
    my_chdir("/home/makandat/temp");
    b = my_rename("bashrc", "moved");
    break;

  case 3: // delete
    b = my_delete(DST);
    break;
    
  case 4:  // chmod
    b = my_chmod(DST, 0777);
    break;
  
  case 5: // mkdir
    b = my_mkdir("/home/makandat/temp/0");
    break;
    
  case 6: // rmdir
    b = my_rmdir("/home/makandat/temp/0");
    break;
    
  case 7: { // write_temp, read_temp
      FILE* fp = my_write_temp("temporary");
      char buff[256];
      b = my_read_temp(fp, buff, 256, true);
      puts(buff);
    }
    break;

  default:
    puts("Not implemented.");
    break;
  }

  // 終わり
  if (b) {
    puts("Done.");
    return EXIT_SUCCESS;
  }
  else {
    puts("Failed");
    return EXIT_FAILURE;
  }
}
