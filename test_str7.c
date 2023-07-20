/* test_str7.c : trim, chomp, pad */
#include "my_string.h"

/* main */
int main(int argc, char* argv[]) {
    // trim, trim_begin, trim_end
    MyString* str1 = my_string_wrap("\t  trim test  \n");
    MyString* str2 = my_string_trim(str1);
    const char* s1 = my_string_get(str2);
    printf("strlen(s1)=%lu, '%s'\n", strlen(s1), s1);
    MyString* str3 = my_string_trim_begin(str1);
    const char* s2 = my_string_get(str3);
    printf("strlen(s2)=%lu, '%s'\n", strlen(s2), s2);
    MyString* str4 = my_string_trim_end(str1);
    const char* s3 = my_string_get(str4);
    printf("strlen(s3)=%lu, '%s'\n", strlen(s3), s3);
    // pad_left, pad_right
    str1 = my_string_wrap("1234");
    str2 = my_string_pad_left(str1, '0', 10);
    const char* s4 = my_string_get(str2);
    puts(s4);
    str3 = my_string_pad_right(str1, '_', 10);
    const char* s5 = my_string_get(str3);
    puts(s5);
    // chomp, strip
    MyString* str5 = my_string_wrap("ABC\n");
    MyString* str6 = my_string_chomp(str5);
    const char* s6 = my_string_get(str6);
    puts(s6);
    MyString* str7 = my_string_wrap("ABCD");
    MyString* str8 = my_string_chomp(str7);
    const char* s8 = my_string_get(str8);
    puts(s8);
    MyString* str9 = my_string_wrap("\"0987\"");
    MyString* str10 = my_string_strip(str9, '"');
    const char* s10 = my_string_get(str10);
    puts(s10);
    // 終わり
    puts("Done.");
    return EXIT_SUCCESS;
}
