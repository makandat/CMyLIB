/* test_str3.c : MyString オブジェクトの関数 */
#include "my_string.h"

/* main */
int main(int argc, char* argv[]) {
    // my_string_wrap, my_string_dup
    MY_HEAP MyString* str1 = my_string_wrap("my_string_wrap");
    MY_HEAP MyString* str2 = my_string_dup(str1);
    my_string_print(str2);
    // my_string_append
    my_string_append(str2, " #2");
    my_string_print(str2);
    // my_string_get, my_string_set
    const char* s1 = my_string_get(str1);
    printf("s1='%s'\n", s1);
    my_string_set(str1, "my_string_set");
    my_string_print(str1);
    // 終わり
    my_release_str(str1);
    my_release_str(str2);
    puts("Done.");
    return EXIT_SUCCESS;
}
