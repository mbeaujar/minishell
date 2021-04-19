#include <criterion/criterion.h>
#include "../include/minishell.h"
#include <signal.h>

/*
Test(category, nom, .signal = SIGSEGV)
{
	// .signal = SIGSEGV , pour compter les segfaults comme valide
}
*/

Test(env, name)
{
	char *name;
	char *env;
	int diff;

	env = "USER=mbeaujar";
	name = return_env_name(env);
	diff = strcmp(name, "USER");
	free(name);
	cr_assert(!diff);
}

Test(env, value)
{
	char *value;
	char *env;
	int diff;

	env = "USER=mbeaujar";
	value = return_env_value(env);
	diff = strcmp(value, "mbeaujar");
	free(value);
	cr_assert(!diff);
}

Test(env, search)
{
	char *expected;
	t_env *head;
	t_env *pwd;
	char *output;
	int diff;

	head = newlstenv("USER=mbeaujar");
	addlstenv(&head, "PWD=/Users/toto/minishell");
	addlstenv(&head, "EMAIL=toto@gmail.com");

	expected = "/Users/toto/minishell";
	pwd = search_env(head, "PWD");
	output = pwd->value;
	diff = strcmp(expected, output);
	if (diff != 0)
		printf("env, search : %s\n", output);
	cr_assert(!diff);
}

Test(path, absolu)
{
	char cwd[PATH_MAX];
	int diff;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		diff = 0;
	else
	{
		//printf("%s\n", cwd);
		diff = 1;
	}
	cr_assert(diff);
}

Test(path, max)
{
	#ifndef PATH_MAX
		cr_asser(0);
	#endif
	cr_assert(1); 
}

Test(search, replace)
{
	char *s;
	char *search;
	char *replace;
	char *expected;
	int diff;

	search = "$USER";
	replace = "mbeaujar";
	s = ft_strdup("je suis $USER.");
	expected = "je suis mbeaujar.";
	s = search_and_replace(s, search, replace, 1);
	if (s == NULL)
		cr_assert(0);
	printf("str : %s\n", s);
	diff = strcmp(expected, s);
	free(s);
	cr_assert(!diff);
}

Test(search, where)
{
	int expected;
	int output;
	char *s;
	char *search;

	s = "Je suis $USER.";
	search = "$USER";
	output = search_where(s, search);
	expected = 8;
	cr_assert(expected == output);
}
