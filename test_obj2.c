/* test_obj2.c: */
#include "cmylib.h"

/* main */
int main(int argc, char* argv[]) {
    // MyObject を作ってそのコピーも作る。
    char* str0 = "Hello World.";
    MyObject* mo1 = my_object_wrap((void*)str0, MY_STRING, sizeof(char), strlen(str0) + 1);
    MyObject* mo2 = my_object_copy(mo1);
    // 1 オリジナルとコピーの値が等しいか？
    char* sb = my_object_equal(mo1, mo2) ? "true" : "false";
    printf("1 equal=%s\n", sb);
    // 2 オリジナルとコピーのハッシュ値を確認する。
    uint16_t hash1 = my_object_hash(mo1);
    uint16_t hash2 = my_object_hash(mo2);
    printf("2 hash1=%d, hash2=%d\n", hash1, hash2);
    // 3 オリジナルとコピーが同一のオブジェクトでないことを確認する。
    sb = my_object_identical(mo1, mo2) ? "true" : "false";
    printf("3 identical=%s\n", sb);
    // 4 オリジナルとオリジナルの参照が同一のオブジェクトであることを確認する。
    MyObject* mp = mo1;
    sb = my_object_identical(mo1, mp) ? "true" : "false";
    printf("4 identical=%s\n", sb);
    // 5 新しいオブジェクト mo3 を作りオリジナルとが同一のオブジェクトでないことを確認する。
    char* str1 = "hello world.";
    MyObject* mo3 = my_object_wrap((void*)str1, MY_STRING, sizeof(char), strlen(str1) + 1);
    sb = my_object_identical(mo1, mo3) ? "true" : "false";
    printf("5 identical=%s\n", sb);
    // 6 オリジナルと新しいオブジェクトの値が異なることを確認する。
    sb = my_object_equal(mo1, mo3) ? "true" : "false";
    printf("6 equal=%s\n", sb);
    // オブジェクトを解放する。
    my_object_release(mo1);
    my_object_release(mo2);
    my_object_release(mo3);
    // 終わり
    puts("Done.");
    return EXIT_SUCCESS;
}
