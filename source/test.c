#include <criterion/criterion.h>
#include "../include/minishell.h"
#include <string.h>

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
