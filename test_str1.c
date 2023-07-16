/* test_str1.c */
#include "my_string.h"

/* main */
int main(int argc, char* argv[]) {
    // バッファを確保する。
    MY_HEAP char* buf = my_bytes_new(81);
    printf("strlen(buf) = %lu\n", strlen(buf));
    // バッファに空白文字列をセットする。
    my_string_times(buf, ' ', 80);
    // 長さを確認する。
    printf("strlen(buf) = %lu\n", strlen(buf));
    free(buf);
    // 文字列オブジェクトを作成する。
    MY_HEAP MyString* s1 = my_string_new();
    my_string_print(s1);

    // 終わり
    puts("Done.");
    return EXIT_SUCCESS;
}
