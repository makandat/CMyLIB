/* test_str1.c : MyStringArray オブジェクトの関数 */
#include "my_string.h"

/* main */
int main(int argc, char* argv[]) {
    MY_HEAP MyStringArray* array1 = my_stringarray_new();
    my_stringarray_print(array1);
    my_stringarray_append2(array1, "Hello ");
    my_stringarray_append2(array1, "World");
    my_stringarray_append2(array1, "!");
    my_stringarray_print(array1);
    // 終わり
    puts("Done.");
    return EXIT_SUCCESS;
}
