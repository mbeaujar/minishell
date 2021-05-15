#include "minishell.h"


t_command *newlstcommand(char **args)
{
    t_command *new;


    if (!(new = malloc(sizeof(t_command) * 1)))
        return (NULL);
    new->args = args;
    new->std_err = STDERR_FILENO;
    new->std_in = STDIN_FILENO;
    new->std_out = STDOUT_FILENO;
    new->key = DEFAULT;
    new->next = NULL;
    new->previous = NULL;
    return (new);
}

void lstaddbackcommand(t_command **list, t_command *new)
{
    t_command *ptr;

    if(!*list) {
        *list = new;
        return;
    }

    ptr = *list;
    while(ptr->next != NULL)
        ptr = ptr->next;
    ptr->next = new;
    new->previous = ptr;

    // *list = ptr;
}

void printlstcommand(t_command *list) 
{

    t_command *ptr;

    ptr = list;

    if(!list)
        return;

    while(ptr->previous != NULL)
        ptr = ptr->previous;

    while(ptr != NULL) 
    {
        ft_printtab(ptr->args);
        ft_printf("\nstd err: %d\nstd in: %d\nstd out: %d\n", ptr->std_err, ptr->std_in, ptr->std_out);
        ptr = ptr->next;
    }


    
}