/* my_console.h */
#ifdef MY_CONSOLEH
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>
#include <errno.h>
#include <assert.h>
#include "my_object.h"

/* コンソール・エスケープコード */
#define MY_ESC_RESET     "\e[0m"
#define MY_ESC_BOLD      "\e[1m"
#define MY_ESC_DIM       "\e[2m"
#define MY_ESC_ITALIC    "\e[3m"
#define MY_ESC_UNDERLINE "\e[4m"
#define MY_ESC_BLINK     "\e[5m"
#define MY_ESC_HBLINK    "\e[6m"
#define MY_ESC_REVERSE   "\e[7m"
#define MY_ESC_FGBLACK   "\e[30m"
#define MY_ESC_BGBLACK   "\e[40m"
#define MY_ESC_FGRED     "\e[31m"
#define MY_ESC_BGRED     "\e[41m"
#define MY_ESC_FGGREEN   "\e[32m"
#define MY_ESC_BGGREEN   "\e[42m"
#define MY_ESC_FGYELLOW  "\e[33m"
#define MY_ESC_BGYELLOW  "\e[43m"
#define MY_ESC_FGBLUE    "\e[34m"
#define MY_ESC_BGBLUE    "\e[44m"
#define MY_ESC_FGMAGENTA "\e[35m"
#define MY_ESC_BGMAGENTA "\e[45m"
#define MY_ESC_FGCYAN    "\e[36m"
#define MY_ESC_BGCYAN    "\e[46m"
#define MY_ESC_FGWHITE   "\e[37m"
#define MY_ESC_BGWHITE   "\e[47m"

/* ハンドラの関数型 */
typedef void (*func0_t)(void);
typedef void (*func1_t)(int);

void my_on_exit(func0_t handler); // main が終了するとき実行されるハンドラを登録する。
void my_on_signal(int sig, func1_t handler);  // シグナル sig が発生したときのハンドラを登録する。
void my_raise_user();  // シグナル SIGUSR1 を発生させる。
void my_on_int(func1_t handler);  // Ctrl+C が押されたときのハンドラを登録する。
void my_on_access(func1_t handler);  // メモリ不正アクセスがあったときのハンドラを登録する。
void my_on_abort(func1_t handler);  // abort() がコールされたときのハンドラを登録する。
void my_on_user(func1_t handler);  // ユーザ定義シグナルが発せられたときのハンドラを登録する。
void my_on_jump(jmp_buf* saved, func0_t setup, func0_t handler);  // longjmp を行ったときのハンドラを登録する。
void my_longjump(jmp_buf* saved);  // longjmp を実行する。
void my_on_noargs(int argc, const char* message);  // コマンド引数がないとき、メッセージを stderr に出力して EXIT_FAILURE を返して main を終了する。
MY_HEAP char* my_input(const char* message);  // メッセージを stdout に表示してから stdin から１行入力する。
void my_print(const char* esccode, const char* message);  // コンソール・エスケープコードを出力し続けてメッセージを stdout へ出力する。esccode=NULL の場合はエスケープコードは出力しない。
void my_println(const char* esccode, const char* message);  // コンソール・エスケープコードを出力し続けてメッセージを stdout へ出力する。esccode=NULL の場合はエスケープコードは出力しない。
void my_exit(int exitcode, const char* message);  // メッセージを stdout (exitcode=0) または stderr (exitcode!=0) に出力して、プログラムを exitcode を返し終了する。
void my_lasterror(void);  // 最後に発生したシステムエラーを stderr へ出力する。 

#endif
