/* my_convert.h */
#ifdef MY_CONVERTH
#else
#include "my_object.h"

MY_HEAP int8_t* my_itos(int32_t);  // 整数から文字列に変換する。
MY_HEAP int8_t* my_ltos(int64_t);  // 長整数から文字列に変換する。
MY_HEAP int8_t* my_ftos(double);   // 倍精度浮動小数点数から文字列に変換する。
int32_t my_stoi(int8_t*);  // 文字列から整数に変換する。
int64_t my_stol(int8_t*);  // 文字列から長整数に変換する。
double  my_stof(int8_t*);  // 文字列から倍精度浮動小数点数に変換する。
MY_HEAP int8_t* my_itoh(int32_t);  // 整数からヘキサ文字列に変換する。
MY_HEAP int8_t* my_ltoh(int64_t);  // 長整数からヘキサ文字列に変換する。

#endif
