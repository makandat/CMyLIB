/* test_str4.c : MyString オブジェクトの関数 */
#include "my_string.h"

/* main */
int main(int argc, char* argv[]) {
    // my_string_indexof
    MY_HEAP MyString* str1 = my_string_wrap("my_string_wrap");
    int i = my_string_indexof(str1, "string", 0);
    printf("my_string_indexof=%d\n", i);
    // my_string_equal
    bool b = my_string_equal(str1, "my_string_wrap");
    printf("my_string_equal=%s\n", b ? "true":"false");
    // my_string_compare
    i = my_string_compare(str1, "my_string_wrap");
    printf("%d\n", i);
    i = my_string_compare(str1, "ay_string_wrap");
    printf("%d\n", i);
    i = my_string_compare(str1, "xy_string_wrap");
    printf("%d\n", i);
    // my_string_slice
    MY_HEAP MyString* str2 = my_string_slice(str1, 3, 8);
    printf("slice='%s'\n", my_string_get(str2));
    // my_string_substring
    MY_HEAP MyString* str3 = my_string_substring(str1, 3, 6);
    printf("substrng='%s'\n", my_string_get(str3));
    // 終わり
    my_release_str(str1);
    my_release_str(str2);
    my_release_str(str3);
    puts("Done.");
    return EXIT_SUCCESS;
}
