/* 端末エスケープ文字列のテスト */
#include "cmylib.h"

/* main */
int main(int argc, char** argv) {
    char attr[80];
    my_println(NULL, "NULL");
    my_println(MY_ESC_BOLD, "MY_ESC_BOLD");
    my_println(MY_ESC_DIM, "MY_ESC_DIM");
    my_println(MY_ESC_ITALIC, "MY_ESC_ITALIC");
    my_println(MY_ESC_UNDERLINE, "MY_ESC_UNDERLINE");
    my_println(MY_ESC_BLINK, "MY_ESC_BLINK");
    my_println(MY_ESC_HBLINK, "MY_ESC_HBLINK");
    my_println(MY_ESC_REVERSE, "MY_ESC_REVERSE");
    my_println(MY_ESC_FGRED, "MY_ESC_FGRED");
    my_println(MY_ESC_FGGREEN, "MY_ESC_FGGREEN");
    my_println(MY_ESC_FGBLUE, "MY_ESC_FGBLUE");
    my_println(MY_ESC_FGYELLOW, "MY_ESC_FGYELLOW");
    my_println(MY_ESC_FGMAGENTA, "MY_ESC_FGMAGENTA");
    my_println(MY_ESC_FGCYAN, "MY_ESC_FGCYAN");
    my_println(MY_ESC_BGRED, "MY_ESC_BGRED");
    my_println(MY_ESC_BGGREEN, "MY_ESC_BGGREEN");
    my_println(MY_ESC_BGBLUE, "MY_ESC_BGBLUE");
    my_println(MY_ESC_BGYELLOW, "MY_ESC_BGYELLOW");
    my_println(MY_ESC_BGMAGENTA, "MY_ESC_BGMAGENTA");
    my_println(MY_ESC_BGCYAN, "MY_ESC_BGCYAN");
    strcpy(attr, MY_ESC_FGBLACK);
    strcat(attr, MY_ESC_BGYELLOW);
    my_println(attr, "MY_ESC_FGBLACK, MY_ESC_BGYELLOW");
    strcpy(attr, MY_ESC_FGBLUE);
    strcat(attr, MY_ESC_BGCYAN);
    my_println(attr, "MY_ESC_FGBLUE, MY_ESC_BGCYAN");
    my_println(MY_ESC_RESET, "MY_ESC_RESET");
    return EXIT_SUCCESS;
}
