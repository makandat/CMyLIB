/* test_misc1.c */
#include "my_misc.h"

/* main */
int main(int argc, char* argv[]) {
    char* now = my_now();
    puts(now);

    // 終わり
    puts("終わり");
    return EXIT_SUCCESS;
}
