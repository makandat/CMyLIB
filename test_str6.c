/* test_str6.c : replace */
#include "my_string.h"

/* main */
int main(int argc, char* argv[]) {
    // 文字列の途中にターゲットがある場合
    MY_HEAP MyString* str1 = my_string_wrap("my_string_split my_string_replace");
    MY_HEAP MyString* str2 = my_string_replace(str1,"string", "STR");
    const char* s1 = my_string_get(str2);
    puts(s1);
    // 文字列の先頭にターゲットがある場合
    my_release_str(str2);
    str2 = my_string_replace(str1,"my", "MINE");
    const char* s2 = my_string_get(str2);
    puts(s2);
    // 文字列の終わりにターゲットがある場合
    my_release_str(str2);
    str2 = my_string_replace(str1,"replace", "REPL");
    const char* s3 = my_string_get(str2);
    puts(s3);
    // 終わり
    my_release_str(str1);
    my_release_str(str2);
    puts("Done.");
    return EXIT_SUCCESS;
}
