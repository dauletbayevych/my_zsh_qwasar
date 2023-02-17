#include "../include/include.h"

void print_current_dir()
{
    char current_dir[MAX_STR_LEN];
    getcwd(current_dir, MAX_STR_LEN);
    my_putstr(current_dir);
    my_putstr("\n");
}

void display_prompt()
{
    write(0, "> ", 3);
}

status_t handle_signal(char *cmd, int status){

    if(status == 0)
        return SUCCESS;

    if(WTERMSIG(status) == SIGSEGV){
        my_putstr("Segmentation fault (core dumped) ");
        my_putstr(cmd);
    }else if(WTERMSIG(status) == SIGFPE){
        my_putstr("Floating-point exception");
    }else if(WTERMSIG(status) == SIGILL){
        my_putstr("Illegal Instruction");
    }else if(WTERMSIG(status) == SIGBUS){
        my_putstr("Bad memory access (SIGBUS)");
    }else if(WTERMSIG(status) == SIGABRT){
        my_putstr("Abort signal");
    }else if(WTERMSIG(status) == SIGSYS){
        my_putstr("Bad system call (SVr4)");
    }else if(WTERMSIG(status) == SIGTRAP){
        my_putstr("Trace/breakpoint trap");
    }

    my_putstr("\n");
    return ERROR;
}
