/* test_convert.c */
#include "mylib.h"

/* main */
int main(int argc, char* argv[]) {
    // 数から文字列への変換
    char* s1 = my_itos(1000);
    printf("my_itos(1000)=\"%s\"\n", s1);
    free(s1);
    char* s2 = my_ltos(1000000000000L);
    printf("my_ltos(1000000000000L)=\"%s\"\n", s2);
    free(s2);
    char* s3 = my_ftos(1.25e-6);
    printf("my_ftos(1.25e-6)=\"%s\"\n", s3);
    free(s3);
    char* s4 = my_itoh(0xabcd);
    printf("my_itoh(0xabcd)=\"%s\"\n", s4);
    free(s4);
    char* s5 = my_ltoh(0x11111abcd);
    printf("my_ltoh(0x11111abcd)=\"%s\"\n", s5);
    free(s5);

    // 文字列から数への変換
    int32_t n = my_stoi("12345");
    printf("my_stoi(\"12345\")=%d\n", n);
    int64_t n2 = my_stol("12312312345");
    printf("my_stol(\"12312312345\")=%ld\n", n2);
    double x = my_stof("9.87e+3");
    printf("my_stof(\"9.87e+3\")=%12.3lf\n", x);
    // 終わり
    puts("Done.");
    return EXIT_SUCCESS;
}
