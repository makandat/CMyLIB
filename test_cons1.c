/* test_cons1.c : my_on_noargs(), my_on_exit(), my_on_int(), my_input() */
#include "cmylib.h"

void on_exit();
void on_break(int);

/* main */
int main(int argc, char* argv[]) {
     my_on_noargs(argc, "No args error\n");
     my_on_exit(on_exit);
     my_on_int(on_break);
     char* input = my_input("> ");
     puts(input);
     return EXIT_SUCCESS;
}

/* on closing main. */
void on_exit() {
    puts("Done.");  
}

/* on key input ^C */
void on_break(int n) {
    puts("  SIGNAL Received (Ctrl+C)");  
}
