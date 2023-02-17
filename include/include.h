// LIBRARIES

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

// DEFINES

#define MAX_STR_LEN 1024
#define MAX_DICT_LEN 100
#define BIN "/usr/bin/"
#define ENV_VAR 'e'
#define VAR 'v'

// ENUM

typedef enum{
    SUCCESS, // 0
    QUIT, // 1
    ERROR, // 2
}status_t;

typedef enum{
    CD,
    ECHO,
    SETENV,
    UNSETENV,
    ENV,
    EXIT,
    PWD,
    WHICH,
    RUN,
    EXECUTE,
    UNKNOWN,
}builtins_t;

// STRUCTS

typedef struct arguments_s{
    int size;
    char **args;
    char **env;
    int env_length;
    int paths_size;
    char **paths;
    builtins_t command;
}argument;

// --------------------------------------------------------------------------------

#ifndef STRING_H
#define STRING_H

char* my_strcat(char*, char*);
size_t my_strlen(char*);
int is_exec(char*);
char *my_strcpy(char*, char*);
int my_strcmp(char*, char*);
int is_digit(char);
int is_char(char);
int arg_count(char*);
int my_getchar();
void my_putstr(char*);
void my_putchar(int, char*);

#endif
// --------------------------------------------------------------------------------

#ifndef UTILITY_H
#define UTILITY_H

void print_current_dir();
void display_prompt();
status_t handle_signal(char*, int);

#endif
// --------------------------------------------------------------------------------

#ifndef MY_READLINE_H
#define MY_READLINE_H

char *my_readline();

#endif
// --------------------------------------------------------------------------------

#ifndef PARSE_H
#define PARSE_H

char **parse_input(argument*, char*);
void free_argument(argument*);
char **get_paths(argument*);
void free_table(argument*);
void free_env(argument*);
void free_paths(argument*);

#endif
// --------------------------------------------------------------------------------

#ifndef MY_ZSH_H
#define MY_ZSH_H

status_t my_zsh(argument*);
status_t echo(argument*);
status_t cd(argument*);
status_t which(argument*);
status_t env(argument*);
status_t my_setenv(argument*);
char **get_env(argument*,char**);
int check_variable_exist(char*, char*);
status_t my_unsetenv(argument*);
char* get_run(argument*);
status_t run(argument*);
status_t execute(argument*);

#endif
// --------------------------------------------------------------------------------

#ifndef MY_ECHO_H
#define MY_ECHO_H

status_t echo(argument*);
char *cut_dollar(char*);
char *cut_variable(char*);

#endif
