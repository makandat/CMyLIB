/* my_convert.c */
#pragma GCC diagnostic ignored "-Wpointer-sign"
#include "my_convert.h"

/* 整数から文字列に変換する。 */
MY_HEAP int8_t* my_itos(int32_t n) {
    int8_t buf[80];
    sprintf(buf, "%d", n);
    size_t sz = strlen(buf) + 1;
    char* ret = (char*)malloc(sz);
    strcpy(ret, buf);
    return ret;
}

/* 長整数から文字列に変換する。 */
MY_HEAP int8_t* my_ltos(int64_t n) {
    int8_t buf[80];
    sprintf(buf, "%ld", n);
    size_t sz = strlen(buf) + 1;
    char* ret = (char*)malloc(sz);
    strcpy(ret, buf);
    return ret;
}

/* 倍精度浮動小数点数から文字列に変換する。 */
MY_HEAP int8_t* my_ftos(double x) {
    int8_t buf[80];
    sprintf(buf, "%lf", x);
    size_t sz = strlen(buf) + 1;
    char* ret = (char*)malloc(sz);
    strcpy(ret, buf);
    return ret;
}

/* 文字列から整数に変換する。 */
int32_t my_stoi(int8_t* s) {
    int32_t ret;
    sscanf(s, "%d", &ret);
    return ret;
}

/* 文字列から長整数に変換する。 */
int64_t my_stol(int8_t* s) {
    int64_t ret;
    sscanf(s, "%ld", &ret);
    return ret;
}

/* 文字列から倍精度浮動小数点数に変換する。 */
double  my_stof(int8_t* s) {
    double ret;
    sscanf(s, "%lf", &ret);
    return ret;
}

/* 整数からヘキサ文字列に変換する。 */
MY_HEAP int8_t* my_itoh(int32_t n) {
    char buf[80];
    sprintf(buf, "0x%08x", n);
    size_t sz = strlen(buf) + 1;
    char* ret = (char*)malloc(sz);
    strcpy(ret, buf);
    return ret;
}

/* 長整数からヘキサ文字列に変換する。 */
MY_HEAP int8_t* my_ltoh(int64_t n) {
    char buf[80];
    sprintf(buf, "0x%016lx", n);
    size_t sz = strlen(buf) + 1;
    char* ret = (char*)malloc(sz);
    strcpy(ret, buf);
    return ret;
}
