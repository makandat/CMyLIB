/* test_cons2.c: try..catch シミュレーション */
#include "mylib.h"

// setjmp/longjmp が使う環境保存バッファ */
jmp_buf env;

void catch();
void try();
void on_abort(int);

/* main */
int main(int argc, char* argv[]) {
    my_on_abort(on_abort);
    my_on_jump(&env, try, catch);
    puts("Done.");
}

/* 例外を受け取る。 */
void catch() {
    puts("caught");
    my_lasterror();
}

/* 例外を発生させる。 */
void try() {
    puts("try abort");
    abort();
}

/* abort() 関数がコールされたときのイベントハンドラ */
void on_abort(int) {
    my_longjump(&env);
}
