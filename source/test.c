#include <criterion/criterion.h>
#include "../include/minishell.h"
#include <signal.h>

/*
Test(category, nom, .signal = SIGSEGV)
{
	// .signal = SIGSEGV , pour compter les segfaults comme valide
	cr_assert(0 == false);
}
*/

t_prompt create_prompt_with_env(void)
{
	t_prompt prompt;
	prompt.env = NULL;
	char *expected[] = { "USER=mbeaujar",  "MAIL=user@user.ft", 
						"TERM=iterm2leplusbeau", "PWD=jesuisla", NULL };

	addlstenv(&prompt.env, expected[0]);
	addlstenv(&prompt.env, expected[1]);
	addlstenv(&prompt.env, expected[2]);
	addlstenv(&prompt.env, expected[3]);
	return (prompt);
}

Test(env, delete)
{
	
}

Test(env, strjoin)
{
	char *expected = "USER=mbeaujar";
	char *output = ft_strjoin_env("USER", "mbeaujar");
	int diff = strcmp(expected, output);
	cr_expect(diff == 0);
	free(output);
}

Test(env, strjoin_seg)
{
	char *expected = "ENV=";
	char *output = ft_strjoin_env("ENV", "");
	int diff = strcmp(expected, output);
	cr_expect(diff == 0);
	free(output);
}

Test(env, strjoin_segfault)
{
	char *expected = "=maison";
	char *output = ft_strjoin_env("", "maison");
	int diff = strcmp(expected, output);
	cr_expect(diff == 0);
	free(output);
}

Test(env, strjoin_segfault_again)
{
	char *expected = "NAME=";
	char *output = ft_strjoin_env("NAME", NULL);
	int diff = strcmp(expected, output);
	cr_expect(diff == 0);
	free(output);
}

Test(env, new_table_env)
{
	int i = 0;
	t_prompt prompt = create_prompt_with_env();
	char *expected[] = { "USER=mbeaujar",  "MAIL=user@user.ft", 
						"TERM=iterm2leplusbeau", "PWD=jesuisla", NULL };
	char **envp = new_table_env(prompt.env);
	while (envp[i])
	{
		if ((strcmp(envp[i], expected[i])) != 0)
		{
			free_tab(envp);
			freelstenv(prompt.env);
			cr_assert(0);
		}
		i++;
	}
	freelstenv(prompt.env);
	free_tab(envp);
	cr_assert(1);
}

Test(env, create_env)
{
	char *s1 = "PWD";
	char *s2 = "/vivelavie";
	char *expected = "PWD=/vivelavie";
	char *env = ft_create_env(s1, s2, FREE_NOT);
	int diff = strcmp(expected, env);
	free(env);
	cr_expect(!diff);
}