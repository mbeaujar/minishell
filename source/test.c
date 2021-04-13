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
