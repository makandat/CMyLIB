/* my_convert.h */
#ifdef MY_CONVERTH
#else
#include "my_object.h"

MY_HEAP int8_t* itos(int32_t);  // 整数から文字列に変換する。
MY_HEAP int8_t* ltos(int64_t);  // 長整数から文字列に変換する。
MY_HEAP int8_t* ftos(double);   // 倍精度浮動小数点数から文字列に変換する。
int32_t stoi(int8_t*);  // 文字列から整数に変換する。
int64_t stol(int8_t*);  // 文字列から長整数に変換する。
double  stof(int8_t*);  // 文字列から倍精度浮動小数点数に変換する。
MY_HEAP int8_t* itoh(int32_t);  // 整数からヘキサ文字列に変換する。
MY_HEAP int8_t* ltoh(int64_t);  // 長整数からヘキサ文字列に変換する。

#endif