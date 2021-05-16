#include <criterion/criterion.h>
#include "../include/minishell.h"
#include <signal.h>

// cr_assert , cr_except

Test(parser, parser_1)
{

    char *str = "salut tout le monde";
    char *dup = NULL;

    dup = ft_secure_strdup(str);
    cr_assert(strcmp(dup, str) == 0);
    cr_assert(dup != NULL);
}

Test(parser, parser_2)
{

    char *str = ft_strdup("salut");
    char *dup = NULL;

    str[0] = -str[0];

    dup = ft_secure_strdup(str);

    
    ft_printf("%s\n", dup);
    ft_printf("%s", str);


    cr_assert_arr_eq_cmp(dup, "alut", 4, strcmp, "expected: |alut|, returned |%s|", dup);
    cr_assert(dup != NULL);
}