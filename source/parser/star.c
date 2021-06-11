#include "minishell.h"
#include <dirent.h>

t_dir *lst_dir_create(struct dirent *d, char *path)
{
    t_dir *dir;

    dir = malloc(sizeof(t_dir));
    dir->dir = d;
    dir->path = path;
    dir->next = NULL;
    dir->previous = NULL;

    return (dir);
}


void lst_dir_push_back(t_dir **current, t_dir *new)
{
    t_dir *ptr;

    ptr = *current;
    if(!*current)
    {
        *current = new;
        return;
    }
    while(ptr->next)
        ptr = ptr->next;
    ptr->next = new;
}

t_dir *list_file_in_dir(char *path) {
    DIR *d;
    struct dirent *dir = NULL;
    t_dir *list = NULL;

    d = opendir(path);
    if(d)
    {
        while((dir = readdir(d)) != NULL)
            lst_dir_push_back(&list, lst_dir_create(dir, path));
    }
    return (list);
}

void parse_star(char *cmd)
{
    int i;
    int star_count;
    int dir_count;

    struct s_dir *list;

    list = list_file_in_dir("./include");
    while(list)
    {
        printf("%s\n", list->dir->d_name);
        list = list->next; 
    }
 

    star_count = 0;
    dir_count = 0;
    i = 0;
    while(cmd[i])
    {
        if(cmd[i] == '*')
        {
            while(cmd[i] == '*' || cmd[i] == '/')
            {
              
                if(cmd[i] == '*')
                    star_count++;
                if(cmd[i] == '/')
                    dir_count++;

                if((cmd[i + 1] != '*' && cmd[i + 1] != '/') || i == (int)ft_strlen(cmd) - 1)
                    printf("end by: %c\n", cmd[i]);

                i++;
            }
        }

        i++;
    }


    exit(0);
}


