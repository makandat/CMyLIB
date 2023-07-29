/* test_dict1.c */
#include "cmylib.h"

// 辞書
static DictEntry** dict;

/* main */
int main(int argc, char* argv[]) {
  puts("test_dict1.c");
  dict = my_dict_new(DICT_ENTRY);
  my_dict_setval(dict, "KEY1", "VALUE1", 7);
  my_dict_setval(dict, "KEY2", "VALUE2", 7);
  my_dict_setval(dict, "KEY3", "VALUE3", 7);
  my_dict_setval(dict, "KEY4", "VALUE4", 7);
  my_dump_hashtable(dict, false);
  char* pl1 = (char*)my_dict_getval(dict, "KEY1");
  if (pl1 == NULL)
    puts("KEY1 NULL");
  else
    printf("%s : %s\n", "KEY1", pl1);
  char* pl2 = (char*)my_dict_getval(dict, "KEY2");
  if (pl2 == NULL)
    puts("KEY2 NULL");
  else
    printf("%s : %s\n", "KEY2", pl2);
  char* pl3 = (char*)my_dict_getval(dict, "KEY3");
  if (pl3 == NULL)
    puts("KEY3 NULL");
  else
    printf("%s : %s\n", "KEY3", pl3);
  char* pl4 = (char*)my_dict_getval(dict, "KEY4");
  if (pl4 == NULL)
    puts("KEY4 NULL");
  else
    printf("%s : %s\n", "KEY4", pl4);
  char* pl5 = (char*)my_dict_getval(dict, "KEY5");
  if (pl5 == NULL)
    puts("KEY5 NULL");
  else
    printf("%s : %s\n", "KEY5", pl5);
  // 終わり
  puts("Done.");
  return EXIT_SUCCESS;
}
