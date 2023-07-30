/* my_misc.c */
#include "my_misc.h"

/* 現在日付時刻を文字列として返す。 */
MY_HEAP char* my_now() {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    char* buf = (char*)malloc(20);
    strftime(buf, 20, "%Y-%m-%d %H:%M:%S", local);
    return buf;
}
