#include "../include/include.h"

char *get_bin(argument *table)
{
    int i = 0;
    DIR *dir;
    char *bin = malloc(sizeof(char) * MAX_STR_LEN);

    while (i < table->paths_size)
    {
        dir = opendir(table->paths[i]);

        if (!dir)
            return NULL;
            
        struct dirent *current_file;
        current_file = readdir(dir);

        for (; current_file; current_file = readdir(dir))
        {
            if (my_strcmp(table->args[0], current_file->d_name) == 0)
            {
                my_strcpy(bin, table->paths[i]);
                my_strcat(bin, "/");
                my_strcat(bin, current_file->d_name);
                closedir(dir);
                goto found;
            }
        }
        i++;
        closedir(dir);
    }
    free(bin);
    return NULL;
found:

    return bin;
}

char *get_run(argument *table)
{
    unsigned long i = 1, j = 0;
    char *run = malloc(sizeof(char) * MAX_STR_LEN);
    getcwd(run, MAX_STR_LEN);
    j = my_strlen(run) - 1;
    while (table->args[0][i] != '\0')
    {
        run[j] = table->args[0][i];
        i++;
        j++;
    }
    run[j] = '\0';
    return run;
}

status_t execute(argument *table)
{
    char *run;
    pid_t pid, wpid; 
    int status;

    if(table->command == RUN)
        run = get_run(table);
    else
        run = get_bin(table);
 
    if (run == NULL){
        my_putstr("my_zsh: command not found: ");
        my_putstr(table->args[0]);
        my_putstr("\n");
        free(run);
        return ERROR;
    }

    pid = fork();

    if (pid == 0){
        if (execve(run, table->args, table->env) == -1){
            my_putstr("my_zsh: no such file or directory: ");
            my_putstr(table->args[0]);
            my_putstr("\n");
            free(run);
            return ERROR;
        }
    }else{
        do{
            wpid = waitpid(pid, &status, WUNTRACED);
            if(handle_signal(table->args[0],status) != SUCCESS){
                free(run);
                return ERROR;
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status) && wpid > 0);
    }

    free(run);
    return SUCCESS;
}

