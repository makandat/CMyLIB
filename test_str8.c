/* test_str8.c  toupper, tolower, startswith, endswith */
#include "my_string.h"

/* main */
int main(int argc, char* argv[]) {
    // toupper, tolower
    MyString* str1 = my_string_wrap("abCD.369");
    MyString* str2 = my_string_toupper(str1);
    const char* s1 = my_string_get(str2);
    puts(s1);
    MyString* str3 = my_string_tolower(str1);
    const char* s2 = my_string_get(str3);
    puts(s2);
    // startswith
    bool b = my_string_startswith(str1, "ab");
    puts(b ? "true" : "false");
    b = my_string_startswith(str1, "Xb");
    puts(b ? "true" : "false");
    // endswith
    b = my_string_endswith(str1, "369");
    puts(b ? "true" : "false");
    b = my_string_endswith(str1, "X");
    puts(b ? "true" : "false");
    // 終わり
    puts("Done.");
    return EXIT_SUCCESS;
}
