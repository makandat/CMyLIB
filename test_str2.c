/* test_str2.c : MyStringArray オブジェクトの関数 */
#include "my_string.h"

/* main */
int main(int argc, char* argv[]) {
    MY_HEAP MyStringArray* array1 = my_stringarray_new();
    my_stringarray_print(array1);
    my_stringarray_append2(array1, "Hello ");
    my_stringarray_append2(array1, "World");
    my_stringarray_append2(array1, "!");
    my_stringarray_print(array1);
    MY_HEAP char* buf = my_stringarray_tostr(array1, NULL);
    printf("buf='%s'\n", buf);
    free(buf);
    buf = my_stringarray_tostr(array1, "**");
    printf("buf='%s'\n", buf);
    free(buf);
    // 終わり
    my_release_strarray(array1);
    puts("Done.");
    return EXIT_SUCCESS;
}
