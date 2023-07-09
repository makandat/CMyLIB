/* my_console.c */
#include "my_console.h"

/* main が終了するとき実行されるハンドラを登録する。 */
inline void my_on_exit(func0_t handler) {
    atexit(handler);
}

/* シグナル SIGUSR1 を発生させる。 */
inline void my_raise_user() {
    raise(SIGUSR1);
}

/* シグナル sig が発生したときのハンドラを登録する。 */
inline void my_on_signal(int sig, func1_t handler) {
    signal(sig, handler);
}

/* Ctrl+C が押されたときのハンドラを登録する。 */
inline void my_on_int(func1_t handler) {
    signal(SIGINT, handler);
}

/* メモリの不正アクセスがあったときのハンドラを登録する。 */
inline void my_on_access(func1_t handler) {
    signal(SIGSEGV, handler);
}

/* abort() がコールされたときのハンドラを登録する。*/
inline void my_on_abort(func1_t handler) {
    signal(SIGABRT, handler);
}

/* ユーザ定義シグナルが発せられたときのハンドラを登録する。*/
inline void my_on_user(func1_t handler) {
    signal(SIGUSR1, handler);
}

/* longjmp を行ったときのハンドラを登録する。 */
void my_on_jump(jmp_buf* saved, func0_t setup, func0_t handler) {
    if (setjmp(*saved) == 0) {
        setup();
    }
    else {
        handler();
    }
}

/* longjmp を実行する。 */
inline void my_longjump(jmp_buf* saved) {
    longjmp(*saved, 1);
}

/* コマンド引数がないとき、メッセージを stderr に出力して EXIT_FAILURE を返して main を終了する。 */
void my_on_noargs(int argc, const char* message) {
    if (argc == 1) {
        fputs(message, stderr);
        exit(EXIT_FAILURE);
    }
}

/* メッセージを stdout に表示してから stdin から１行入力する。 */
MY_HEAP char* my_input(const char* message) {
    char s[1024];
    if (message != NULL) {
        fputs(message, stdout);
    }
    fgets(s, sizeof(s), stdin);
    size_t sz = strlen(s) + 1;
    char* ret = (char*)malloc(sz);
    strcpy(ret, s);
    return ret;
}

/* コンソール・エスケープコードを出力し続けてメッセージを stdout へ出力する。esccode=NULL の場合はエスケープコードは出力しない。 */
void my_print(const char* esccode, const char* message) {
    char* escstr = (char*)esccode;
    if (esccode == NULL) {
        escstr = "\e[m";
    }
    size_t size = strlen(escstr) + strlen(message) + 1;
    char* buf = (char*)malloc(size);
    strcpy(buf, escstr);
    strcat(buf, message);
    fputs(buf, stdout);
    fputs("\e[m", stdout);
    free(buf);
    return;
}

/* my_print() と同じだが message の後に改行を出力する。 */
void my_println(const char* esccode, const char* message) {
    my_print(esccode, message);
    putchar('\n');
}

/* メッセージを stdout (exitcode=0) または stderr (exitcode!=0) に出力して、プログラムを exitcode を返し終了する。 */
void my_exit(int exitcode, const char* message) {
    if (message != NULL) {
        if (exitcode == 0)
            fputs(message, stdout);
        else
            fputs(message, stderr);
    }
    exit(exitcode);
}

/* 最後に発生したシステムエラーを stderr へ出力する。 */
void my_lasterror(void) {
    fprintf(stderr, "errno=%d: %s\n", errno, strerror(errno));
}

