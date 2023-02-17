#include "../include/include.h"

char **get_home(argument *table){

    free_argument(table);
    table->size = 3;
    table->args = malloc(sizeof(char*)*table->size);
    int index = 0;

    table->args[0] = malloc(sizeof(char)*3);
    my_strcpy(table->args[0], "cd");

    while (index < table->env_length){
        if (check_variable_exist("HOME", table->env[index]) == 1){
            table->args[1] = cut_variable(table->env[index]);
            break;
        }
        index++;
    }
    table->args[2] = NULL;

    return table->args;
}

status_t cd(argument *table)
{

    char cwd[MAX_STR_LEN];
    static char prev_dir[MAX_STR_LEN];

    if(!table->args[1] || !my_strcmp(table->args[1], "~") ){
        table->args = get_home(table);
    }

    if (!my_strcmp(table->args[1], "-"))
    {
        chdir(prev_dir);
        print_current_dir();
        return SUCCESS;
    }
    getcwd(prev_dir, MAX_STR_LEN);


    DIR *dir = opendir(table->args[1]);

    if (!dir)
    {
        perror("dir");
        return ERROR;
    }

    if (table->args[1][0] != '/')
    {
        getcwd(cwd, sizeof(cwd));
        my_strcat(cwd, "/");
        my_strcat(cwd, table->args[1]);
        chdir(cwd);
    }
    else
        chdir(table->args[1]);

    print_current_dir();
    closedir(dir);

    return SUCCESS;
}
