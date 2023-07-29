/* test_dict2.c */
#include "cmylib.h"
#define N 10

// 辞書
static DictEntry** dict;
static char* key[N] = {"09", "06", "10", "06", "-5", "08", "-2", "55", "00", "01"};
static int data[N] = {9, 6, 10, 2, -5, 8, -2, -5, 0, 1};

// コールバック関数
void print(char* key, void* payload, size_t sz);

/* main */
int main(int argc, char* argv[]) {
  puts("test_dict2.c");
  dict = my_dict_new();
  for (int i = 0; i < N; i++) {
     my_dict_setval(dict, key[i], (void*)&data[i], (uint64_t)sizeof(int)); 
  }
  my_dict_foreach(dict, print);
  
  // 終わり
  puts("Done.");
  return EXIT_SUCCESS;
}

/* コールバック関数 */
void print(char* key, void* payload, size_t sz) {
    printf("Key=%s, Payload=%d Size=%d\n", key, *(int*)payload, (int)sz);
}
