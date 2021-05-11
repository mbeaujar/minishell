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
	char *expected[] = {"USER=mbeaujar", "MAIL=user@user.ft",
						"TERM=iterm2leplusbeau", "PWD=jesuisla", NULL};

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
	char *expected[] = {"USER=mbeaujar", "MAIL=user@user.ft",
						"TERM=iterm2leplusbeau", "PWD=jesuisla", NULL};
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

//-----------------------------------------------------------------------------------//


int ft_strcmp_lexer(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s2[i] < 0)
			s2[i] = -s2[i];
		if (s2[i] != s1[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

int test_token(char *str, char *expected[])
{
	t_lexer *head = lexer(str);
	t_lexer *tmp = head;
	int len = ft_strlen_tab(expected);
	if (len != lstsizelexer(head))
	{
		freelstlexer(&head);
		return (0);
	}
	for (int i = 0; i < len; i++)
	{
		if (ft_strcmp_lexer(expected[i], tmp->token) != 0)
		{
			freelstlexer(&head);
			return (0);
		}
		tmp = tmp->next;
	}
	freelstlexer(&head);
	return (1);
}


Test(lexer_token, create_token_difficutl)
{
	char str[] = "ls bon\" jour\" 'je suis la''oui' \"moi    aussi\"";
	char *expected[] = {"ls", "bon jour",
						"je suis laoui", "moi    aussi", NULL};
	cr_expect(test_token(str, expected));
}

Test(lexer_token, create_token_simple)
{
	char str[] = "< Makefile cat | cat";
	char *expected[] = {"<", "Makefile",
						"cat", "|", "cat", NULL};
	cr_expect(test_token(str, expected));
}


Test(lexer_token, create_token_1)
{
	char str[] = "echo \\b";
	char *expected[] = {"echo", "b", NULL};
	cr_expect(test_token(str, expected));
}

Test(lexer_token, create_token_2)
{
	char str[] = "echo \"\\b\"";
	char *expected[] = {"echo", "\\b", NULL};
	cr_expect(test_token(str, expected));
}

Test(lexer_token, create_token_3)
{
	char str[] = "echo '\\b'";
	char *expected[] = {"echo", "\\b", NULL};
	cr_expect(test_token(str, expected));
}

Test(lexer_token, create_token_4)
{
	char str[] = "'je suis la''oui'";
	char *expected[] = {"je suis laoui", NULL};
	cr_expect(test_token(str, expected));
}

Test(lexer_token, create_token_5)
{
	// \e"xp"'o'\rt
	char str[] = "\\e\"xp\"'o'\\rt";
	char *expected[] = {"export", NULL};
	cr_expect(test_token(str, expected));
}

Test(lexer_token, create_token_6)
{
	// echo "quatre"\ 'arguments'\ \en" un"
	char str[] = "echo \"quatre\"\\ 'arguments'\\ \\en\" un\"";
	char *expected[] = {"echo", "quatre arguments en un", NULL};
	cr_expect(test_token(str, expected));
}

Test(lexer_token, create_token_7)
{
	// "e""c""h""o"
	char str[] = "\"e\"\"c\"\"h\"\"o\"";
	char *expected[] = {"echo", NULL};
	cr_expect(test_token(str, expected));
}

Test(lexer_token, create_token_8)
{
	char str[] = "          echo";
	char *expected[] = {"echo", NULL};
	cr_expect(test_token(str, expected));
}

Test(lexer_token, create_token_9)
{
	char str[] = "echo           ";
	char *expected[] = {"echo", NULL};
	cr_expect(test_token(str, expected));
}

Test(lexer_token, create_token_10)
{
	char str[] = "echo\\ a";
	char *expected[] = {"echo a", NULL};
	cr_expect(test_token(str, expected));
}

Test(lexer_token, create_token_11)
{
	char str[] = "ls \"\" bonjour";
	char *expected[] = {"ls", "", "bonjour", NULL};
	cr_expect(test_token(str, expected));
}

Test(lexer_token, create_token_12)
{
	char str[] = "ls";
	char *expected[] = {"ls", NULL};
	cr_expect(test_token(str, expected));
}




