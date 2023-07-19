/* test_str5.c : split, join */
#include "my_string.h"

/* main */
int main(int argc, char* argv[]) {
    // 文字列の途中にセパレータがある場合
    MY_HEAP MyString* str1 = my_string_wrap("my_string_split");
    MY_HEAP MyStringArray* array1 = my_string_split(str1, '_');
    my_stringarray_print(array1);
    MY_HEAP MyString* str2 = my_string_join(array1, '-');
    const char* s2 = my_string_get(str2);
    puts(s2);
    // 文字列の先頭にセパレータがある場合
    my_release_str(str1);
    my_release_strarray(array1);
    str1 = my_string_wrap("_my_string_split");
    array1 = my_string_split(str1, '_');
    my_stringarray_print(array1);
    // 文字列の終わりにセパレータがある場合
    my_release_str(str1);
    my_release_strarray(array1);
    str1 = my_string_wrap("my_string_split_");
    array1 = my_string_split(str1, '_');
    my_stringarray_print(array1);
    // 終わり
    my_release_str(str1);
    my_release_str(str2);
    my_release_strarray(array1);
    puts("Done.");
    return EXIT_SUCCESS;
}
