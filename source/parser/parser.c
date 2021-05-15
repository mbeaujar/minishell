/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 20:18:04 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/14 21:28:13 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
 #include <sys/stat.h>

/*
** check file -- stat
** LEFT = stdin
** RIGHT = stdout
*/

int open_path(char *path, type key)
{
    int fd;
    int tmp;

    fd = -1;
    tmp = -1;
    if (key == RIGHT) {
        tmp = open(path, O_CREAT | O_RDWR, S_IRWXU);
        if(tmp == -1)
            fd = open(path, O_RDWR);
        else
            fd = tmp;
    }
    else if (key == LEFT)
        fd = open(path, O_RDONLY);
    return (fd);
}

t_command *create_token_range(t_lexer **start)
{
    char *args;
    t_command *list;
    
    args = NULL;
    list = newlstcommand(NULL);
    while ((*start) != NULL && (*start)->key != COMAT && (*start)->key != PIP)
    {
        if ((*start)->key == DEFAULT)
        {
            ft_unleak_strjoin(&args, (*start)->token);
            if ((*start)->next != NULL && (*start)->next->key == DEFAULT)
                ft_unleak_strjoin(&args, " ");
        }
        if ((*start)->key == RIGHT)
        {
            list->std_out = open_path((*start)->next->token, (*start)->key);
            (*start) = (*start)->next;
        }
        if ((*start)->key == LEFT)
        {
            list->std_in = open_path((*start)->next->token, (*start)->key);
            (*start) = (*start)->next;
        }
        (*start) = (*start)->next;
    }
    list->args = ft_split(args, ' ');
    free(args);
    return (list);
}

void parse(t_lexer *tokens)
{
    t_lexer *ptr;
    t_command *list = NULL;
    t_command *current = NULL;
    char *args;

    ptr = tokens;

    args = NULL;
    while (ptr != NULL)
    {
        current = create_token_range(&ptr);
        // echo salut < file1 | cat
        if (ptr && ptr->key == PIP)
            current->key = PIP;
        if (ptr && (ptr->key == PIP || ptr->key == COMAT))
            ptr = ptr->next;


            
        lstaddbackcommand(&list, current);
       
        printf("-----COMMAND LIST-----\n");
        printlstcommand(list);
    }
}