/* test_obj1.c : my_object_wrap(), my_object_string(), my_object_in32(), my_object_str(), my_object_release() */
#include "mylib.h"

/* main */
int main(int argc, char* argv[]) {
    // 整数のオブジェクト
    int n = 10;
    MyObject* mo1 = my_object_wrap(&n, MY_INT32, sizeof(int), 1);
    char* str = my_object_string(mo1);
    puts(str);
    int m = my_object_int32(mo1);
    printf("m = %d\n", m);
    my_object_release(mo1);

    // 文字列のオブジェクト
    mo1 = my_object_wrap("MY_STRING", MY_STRING, sizeof(char), strlen("MY_STRING") + 1);
    str = my_object_string(mo1);
    puts(str);
    char* s = my_object_str(mo1);
    printf("s = %s\n", s);
    my_object_release(mo1);

    // 終わり
    puts("Done.");
    return EXIT_SUCCESS;
}
