/* test_obj3.c : オブジェクトの値の変更と取得 */
#include "cmylib.h"

/* main */
int main(int argc, char* argv[]) {
    // 32ビット整数
    int n = 1234;
    MyObject *mo1 = my_object_wrap(&n, MY_INT32, sizeof(int32_t), 1);
    int m = my_object_int32(mo1);
    printf("m=%d\n", m);
    my_object_set_int32(mo1, -n);
    m = my_object_int32(mo1);
    printf("m=%d\n", m);
    my_object_release(mo1);
    // 文字列
    char* str1 = "my_object";
    size_t sz = strlen(str1) + sizeof(char);
    mo1 = my_object_wrap(str1, MY_STRING, sz, 1);
    char* str2 = my_object_str(mo1);
    printf("mo1->data = \"%s\"\n", str2);
    my_object_set_str(mo1, "my_object->MY_OBJECT");
    str2 = my_object_str(mo1);
    printf("mo1->data = \"%s\"\n", str2);
    my_object_release(mo1);
    puts("Done.");
}
