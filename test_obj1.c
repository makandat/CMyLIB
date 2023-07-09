/* test_obj1.c */
#include "mylib.h"

/* main */
int main(int argc, char* argv[]) {
    int n = 10;
    MyObject* mo1 = my_object_wrap(&n, MY_INT32, sizeof(int), 1);
    char* str = my_object_string(mo1);
    puts(str);
    int m = my_object_int32(mo1);
    printf("m = %d\n", m)
    puts("Done.");
    return EXIT_SUCCESS;
}
