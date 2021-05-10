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

Test(export, search)
{
	char *expected = "MAIL";
	t_prompt prompt = create_prompt_with_env();
	t_env *find = search_min(prompt.env);
	int diff = ft_strcmp(expected, find->name);
	freelstenv(prompt.env);
	cr_expect(diff == 0);
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

Test(prompt, buffer)
{
	t_prompt prompt;

	prompt.indice = 2;
	char *str = ft_strdup("bonjour");
	int len = 40;
	char *output = new_size_buffer(&prompt, 'i', str, len);
	char *expected = "boinjour";
	int diff = strcmp(expected, output);
	cr_expect(!diff);
	free(output);
}

Test(export, strcmp)
{
	char s1[] = "USER";
	char s2[] = "MAIL";
	int diff = ft_strcmp(s1, s2);
	//printf("diff : %d\n", diff);
	cr_expect(diff > 0);
}

Test(env, create_env_null)
{
	t_env *head;

	head = NULL;
	char str[] = "RA";
	addlstenv(&head, ft_strdup(str));
	if (head == NULL)
		cr_assert(0);
	//printf("name : %s value : %s\n", head->name, head->value);
	int diff = ft_strcmp(head->name, str);
	cr_expect(diff == 0);
	free(head->name);
	free(head);
}

Test(lexer_token, create_token_simple)
{
    char str[] = "< Makefile cat | cat";
	char *expected[] = { "<",  "Makefile", 
						"cat", "|", "cat", NULL };
    t_lexer *head = lexer(str);
    //printlstlexer(head);
	t_lexer *tmp = head;
	for (int i = 0; expected[i]; i++)
	{
		//printf("s : %s tok : %s\n", expected[i], tmp->token);
		if (ft_strcmp(expected[i], tmp->token) != 0)
			cr_expect(0);
		tmp = tmp->next;
	}
	cr_expect(1);
    freelstlexer(&head);
}

Test(lexer_token, create_token_difficutl)
{
    char str[] = "ls bon\" jour\" 'je suis la''oui' \"moi    aussi\"";
	char *expected[] = { "ls",  "bon\" jour\"", 
						"'je suis la''oui'", "\"moi    aussi\"", NULL };
    t_lexer *head = lexer(str);
    //printlstlexer(head);
	t_lexer *tmp = head;
	for (int i = 0; expected[i]; i++)
	{
		//printf("s : %s tok : %s\n", expected[i], tmp->token);
		if (ft_strcmp(expected[i], tmp->token) != 0)
			cr_expect(0);
		tmp = tmp->next;
	}
	cr_expect(1);
    freelstlexer(&head);
}