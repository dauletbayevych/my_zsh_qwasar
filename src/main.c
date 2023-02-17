/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  My_zsh is A unix_shell 
 *
 *        Version:  1.0
 *        Created:  11/09/2021 02:23:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chris Dallat , Khalil Masree 
 *   Organization:  ELU 
 *
 * =====================================================================================
 */

#include "../include/include.h"

int main(int argc, char *argv[], char **envi)
{
    if (argc > 1)
    {
        *argv = NULL;
        my_putstr("my_zsh: can't take input.\n");
        return 0;
    }

    char *std_in;
    status_t status = 0;
    argument *table = malloc(sizeof(argument));
    table->env = get_env(table, envi);
    table->paths = get_paths(table);
    print_current_dir();

    while (status != QUIT)
    {
        std_in = NULL;
        display_prompt();
        std_in = my_readline();
        table->size = arg_count(std_in);
        if ((table->args = parse_input(table, std_in)) == NULL)
            continue;
        status = my_zsh(table);

        free_argument(table);
        free(std_in);
    }

    free_table(table);

    return 0;
}
