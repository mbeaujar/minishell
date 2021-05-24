/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 20:18:04 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/21 22:49:35 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** check file -- stat
** LEFT = stdin
** RIGHT = stdout
*/

int open_path(char *path, type key, int curr_fd)
{
    int fd;
    struct stat file;
    int tmp;

    fd = -1;
    tmp = -1;
    if (key == RIGHT || key == DRIGHT)
    {
        if (curr_fd != 1)
            close(curr_fd);
        if(key == DRIGHT)
            tmp = open(path, O_CREAT | O_RDWR, S_IRWXU, O_APPEND);
        if(key == RIGHT)
            tmp = open(path, O_CREAT | O_RDWR, S_IRWXU);
        if(tmp == -1) {
            if(key == DRIGHT)
                fd = open(path, O_RDWR | O_APPEND);
            if(key == RIGHT)
                fd = open(path, O_RDWR);
        } 
        else
            fd = tmp;
    }
    else if (key == LEFT)
    {
        if (curr_fd != 0)
            close(curr_fd);
        if (stat(path, &file) == -1)
            return (-1);
        fd = open(path, O_RDONLY);
    }
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
            list->std_out = open_path((*start)->next->token, (*start)->key, list->std_out);
            (*start) = (*start)->next;
        }
        if ((*start)->key == LEFT)
        {
            list->std_in = open_path((*start)->next->token, (*start)->key, list->std_in);
            (*start) = (*start)->next;
        }
        (*start) = (*start)->next;
    }
    list->args = args;
    return (list);
}

t_command *parse(t_lexer *tokens)
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
        if (ptr && ptr->key == PIP)
            current->key = PIP;
        if (ptr && (ptr->key == PIP || ptr->key == COMAT))
            ptr = ptr->next;

        lstaddbackcommand(&list, current);
    }

    return (list);
}