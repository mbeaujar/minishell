#include <criterion/criterion.h>
#include "../include/minishell.h"
#include <signal.h>

// cr_assert , cr_except

Test(parser, ft_secure_strdup_1)
{

    char *str = "salut tout le monde";
    char *dup = NULL;

    dup = ft_secure_strdup(str);
    cr_assert(strcmp(dup, str) == 0);
    cr_assert(dup != NULL);
}

Test(parser, ft_secure_strdup_2)
{

    char *str = ft_strdup("salut");
    char *dup = NULL;

    str[0] = -str[0];

    dup = ft_secure_strdup(str);

    
    printf("%s\n", dup);
    printf("%s", str);


    cr_assert_arr_eq_cmp(dup, "alut", 4, strcmp, "expected: |alut|, returned |%s|", dup);
    cr_assert(dup != NULL);
}

Test(parser, ft_strfrom_tab_1)
{

    char *_1 = "salut tout le monde";
    char *_2 = "echo salut $ARG bonsoir";
    char *str = NULL;
    char **tabs;

    tabs = ft_split(_1, ' ');
    str = ft_strfrom_tab(tabs, " ");
    cr_assert_arr_eq_cmp(str, _1, ft_strlen(_1), strcmp, "expected: |%s|, returned |%s|",_1, str);


    tabs = ft_split(_2, ' ');
    str = ft_strfrom_tab(tabs, " ");
    cr_assert_arr_eq_cmp(str, _2, ft_strlen(_2), strcmp, "expected: |%s|, returned |%s|",_2, str);


}